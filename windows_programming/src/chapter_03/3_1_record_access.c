#include "chapter_02/2_1_report_error.c"
#include <windows.h>
#include "LAL.h"
#include <stdlib.h>
#include <stdio.h>

#define STRING_SIZE (256)

typedef struct
{
    u32 reference_count;
    SYSTEMTIME time_created;
    SYSTEMTIME time_last_refrenced;
    SYSTEMTIME time_updated;
    u8 data_string[STRING_SIZE];
} record_t;

typedef struct
{
    u32 num_records;
    u32 num_records_non_empty;
} header_t;

u32 record_access(u32 arg_count, u8 *command_line[])
{
    HANDLE        file_handle;
    LARGE_INTEGER file_pointer;
    
    u32 open_option;
    u32 transfer_count;
    u32 record_number;
    
    record_t record;
    u8 string [STRING_SIZE];
    u8 command;
    u8 extra   ; // NOTE(MIGUEL): da fuck is this????
    
    OVERLAPPED overlapped      = { 0, 0, 0, 0, NULLPTR};
    OVERLAPPED overlapped_zero = { 0, 0, 0, 0, NULLPTR}; // NOTE(MIGUEL): whats the difffreaence
    
    header_t header = { 0 , 0};
    
    SYSTEMTIME current_time;
    
    b32 header_changed;
    b32 record_changed; // NOTE(MIGUEL): how is this used?????
    
    s32 prompt = (arg_count <= 3) ? 1 : 0; // NOTE(MIGUEL): wtf
    
    if(arg_count < 2)
    {
        // NOTE(MIGUEL): THIS MAKES NO FUCKING SENSE
        report_error_ansi("Prams: [name of record file] [record number [prompt]]", 1, FALSE);
        // NOTE(MIGUEL): FIRST CL ARG IS PROGRAM
        // NOTE(MIGUEL): SECONDE CL ARG IS FILE
        // NOTE(MIGUEL): THIRD CL OPTION MUST BE A NUMBER OF ????
    }
    
    open_option = (((arg_count > 2 && strtol(command_line[2], NULL, 10) <= 0) || arg_count <= 2) ?
                   OPEN_EXISTING :
                   CREATE_ALWAYS );
    
    file_handle = CreateFileA(command_line[1],
                              GENERIC_READ | GENERIC_WRITE,
                              0, NULLPTR,
                              open_option,
                              FILE_FLAG_RANDOM_ACCESS,
                              NULLPTR);
    
    if(file_handle == INVALID_HANDLE_VALUE)
    {
        report_error_ansi("Record access error: cannot open existiong file", 2, TRUE);
    }
    
    if(arg_count >= 3 && strtol(command_line[2], NULL, 10) > 0)
    {
        
#if CHALLENGE
        if(!GetVolumeInformationA("C:\\", NULLPTR, 0, NULLPTR, NULLPTR, &fs_flags, NULLPTR, 0))
        {
            report_error_ansi("Record Access Error: GetVolumeInformationA.\n", 3, TRUE);
        }
        
        if(fs_flags & FILE_SUPPORTS_SPARSE_FILES)
        {
            if((fs_flags & FILE_SUPPORTS_SPARSE_FILES) && 
               (!DeviceToControl(file_handle, FSCTL_SET_SPARSE,
                                 NULLPTR, 0, NULLPTR, 0,
                                 &transfer_count, NULLPTR)))
            {
                report_error_ansi("Record Access error: Making new file sparse.", 0, TRUE);
            }
        }
        
        printf("Is it sparse? %x\n", GetFileAttributes(command_line[1]) & FILE_ATTRIBUTE_SPARSE_FILE);
#endif
        
        header.num_records   = strtol(command_line[2], NULL, 10);
        
        if(!WriteFile(file_handle, &header, sizeof(header), &transfer_count, &overlapped_zero))
        {
            report_error_ansi("RecordAccess Error: WriteFile header", 4, TRUE);
        }
        
        
        file_pointer.QuadPart = ((u64)sizeof(record_t) *
                                 strtol(command_line[2], NULL, 10) *
                                 sizeof     (header_t));
        
        if(!SetFilePointerEx(file_handle, file_pointer, NULLPTR, FILE_BEGIN))
        {
            report_error_ansi("RecordAccess Error: SetFilePointer", 4, TRUE);
        }
        
        if(!SetEndOfFile(file_handle))
        {
            report_error_ansi("RecordAccess Error: Set End of File", 5, TRUE);
        }
        
        if(prompt)
        {
            printf("Empty file with %d records created.\n", header.num_records);
        }
        
        return 0;
    }
    
    if(!ReadFile(file_handle, &header, sizeof(header_t), &transfer_count, &overlapped_zero))
    {
        report_error_ansi("RecordAccess Error: ReadFile header.\n", 6, TRUE);
    }
    if(prompt)
    {
        printf("File %s contains %d non-empty record of size %zd.\n"
               "Total capacity: %d\n",
               command_line[1],
               header.num_records_non_empty,
               sizeof(record_t),
               header.num_records);
    }
    
    
    while(TRUE)
    {
        header_changed = FALSE;
        record_changed = FALSE;
        if(prompt)
        {
            printf("Enter r(ead)/w(rite)/d(elete)/qu(it) record#\n");
        }
        
        scanf("%c%u%c", &command, &record_number ,&extra);
        
        if(command == 'q')
        { break; }
        
        if(record_number >= header.num_records)
        {
            if(prompt)
            {
                printf("record Number is too large. Try again.\n");
            }
            
            continue;
        }
        
        file_pointer.QuadPart = ((u64)record_number *
                                 (sizeof(record_t) +
                                  sizeof(header_t)));
        // NOTE(MIGUEL): what does this do???
        overlapped.Offset     = file_pointer.LowPart;
        overlapped.OffsetHigh = file_pointer.HighPart;
        
        
        if(!ReadFile(file_handle, &record,
                     sizeof(record_t), &transfer_count,
                     &overlapped))
        {
            report_error_ansi("Record Access: ReadFile faliur.\n", 7, FALSE);
        }
        
        GetSystemTime(&current_time);
        record.time_last_refrenced = current_time;
        
        /// READ or DELETE
        if(command == 'r' || command == 'd')
        {
            if(record.reference_count == 0)
            {
                if(prompt)
                {
                    printf("record number %d is empty.\n", record_number);
                    continue;
                }
            }
            else
            {
                if(prompt)
                {
                    printf("Record Number: %d. Reference count: %d\n", record_number, record.reference_count);
                }
                if(prompt)
                {
                    printf("Data: %s\n", record.data_string);
                }
                /* Exercise: Display times. See ls.c for an example */
            }
            
            
            if(command == 'd')
            {
                record.reference_count = 0;
                header.num_records_non_empty--;
                header_changed = TRUE;
                record_changed = TRUE;
            }
        }
        /// WRITE
        else if (command == 'w')
        {
            if(prompt)
            {
                printf("Enter new data string for the record.\n");
            }
            
            fgets(string, sizeof(string), stdin);
            
            string[strlen(string) - 1] = ('\0');
            
            if(record.reference_count == 0)
            {
                record.time_created = current_time;
                header_changed      = TRUE;
                header.num_records_non_empty++;
            }
            
            record.time_updated = current_time;
            record.reference_count++;;
            
            strncpy(record.data_string, string, (STRING_SIZE - 1));
            
            record_changed = TRUE;
        }
        else
        {
            if(prompt)
            {
                printf("command must be r, w, or, d. Try again.\n");
            }
        }
        
        if(record_changed && !WriteFile(file_handle, &record, sizeof(record_t),
                                        &transfer_count, &overlapped))
        {
            report_error_ansi("Record Access: WriteFile update failure.\n", 8, FALSE);
        }
        
        if(header_changed)
        {
            if(!WriteFile(file_handle, &header, sizeof(header_t),
                          &transfer_count, &overlapped_zero))
            {
                report_error_ansi("Record Access: WriteFile update failure.\n", 9, FALSE);
            }
        }
    }
    
    if(prompt)
    {
        printf("Computed number of non-empty records is: %d\n",
               header.num_records_non_empty);
    }
    
    if(!ReadFile(file_handle    , &header, sizeof(header_t),
                 &transfer_count, &overlapped_zero))
    {
        report_error_ansi("Record Access Error: ReadFile header.\n", 10, TRUE);
    }
    
    if(prompt)
    {
        printf("File %s NOW contains %d non-empty records.\n"
               "Total capacity is: %d\n",
               command_line[1],
               header.num_records_non_empty,
               header.num_records);
    }
    
    CloseHandle(file_handle);
    
    return 0;
}
