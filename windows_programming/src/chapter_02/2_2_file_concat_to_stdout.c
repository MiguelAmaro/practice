#include <windows.h>
#include "LAL.h"
#include "windows_programming/options.c"
#include "windows_programming/2_1_report_error.c"
//************************************************************
// TIME: 30 min
// 
// GOAL:
// Create a function that copies a file using the win32 api
// 
// Use the timep.exe in Dev\Study\WindowSystemsProgramming to time-
// this funciton and compare it with the other copy fucntions when 
// handling large files
//
// LOG:
// 4/1/2021 - folllowing the windows systems programming book
//
// ************************************************************

#define BUFFER_SIZE 0x200

void cat_file (HANDLE file_in, HANDLE file_out)
{
    u32 bytes_read   ;
    u32 bytes_written;
    
    u8 buffer[BUFFER_SIZE];
    
    while (ReadFile(file_in    ,
                    buffer     ,
                    BUFFER_SIZE,
                    &bytes_read,
                    NULLPTR    ) 
           
           && (bytes_written != 0) &&  
           
           WriteFile (file_out      ,
                      buffer        ,
                      bytes_read    ,
                      &bytes_written,
                      NULLPTR));
    
    return;
}


u32 file_concat_to_stdout(u32 arg_count, u8 *command_line[])
{
    HANDLE file_in ;
    HANDLE file_out;
    
    HANDLE console_in ;
    HANDLE console_out;
    
    console_in  = GetStdHandle( STD_INPUT_HANDLE);
    console_out = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // NOTE(MIGUEL): Commandline Option State
    b32 dash_s;
    
    u32 arg_index;
    u32 first_file_index;
    
    first_file_index = options(arg_count, command_line, "s", &dash_s, NULLPTR);
    
    if(first_file_index == arg_count)
    {
        cat_file(console_in, console_out);
        return 0;
    }
    
    for(arg_index = first_file_index; arg_index < arg_count; arg_index++)
    {
        file_in = CreateFile(command_line[arg_index],
                             GENERIC_READ           ,
                             0 , NULLPTR            , 
                             OPEN_EXISTING          ,
                             FILE_ATTRIBUTE_NORMAL  ,
                             NULLPTR)               ;
        
        if(file_in == INVALID_HANDLE_VALUE)
        {
            if(!dash_s)
            {
                report_error("Error: File does not exist.", 0, TRUE);
            }
        }
        else
        {
            cat_file(file_in, console_out);
            
            if(GetLastError() != 0 && !dash_s)
            {
                report_error("Error: file concat failed.", 0, TRUE);
            }
            
            CloseHandle(file_in);
        }
    }
    
    return 0;
}
