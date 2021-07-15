#include <windows.h>
#include <stdio.h>
#include "LAL.h"

#define BUFFER_SIZE (256)

// TODO(MIGUEL): Look up windows status codes

u32 copy_file_win32(int arg_counter, u8 *command_line[])
{
    HANDLE handle_in ;
    HANDLE handle_out;
    
    // NOTE(MIGUEL): or bytes_read | bytes_written
    u32 bytes_read   ;
    u32 bytes_written;
    
    // NOTE(MIGUEL): the size is arbitrary
    u8 recieve_buffer[BUFFER_SIZE];
    
    if(arg_counter != 3)
    {
        printf("This app requires two files.\n");
        printf("Usage: copy <file 1> into <file 2>\n");
        return 1;
    }
    
    handle_in = CreateFile(command_line[1]              , 
                           GENERIC_READ         ,
                           FILE_SHARE_READ      ,
                           NULLPTR              ,
                           OPEN_EXISTING        ,
                           FILE_ATTRIBUTE_NORMAL,
                           NULLPTR);
    
    if(handle_in == INVALID_HANDLE_VALUE)
    {
        printf("Cannot open input file. Error: %x\n", GetLastError());
        return 2;
    }
    
    handle_out = CreateFile(command_line[2]              , 
                            GENERIC_WRITE        ,
                            0                    ,
                            NULLPTR              ,
                            CREATE_ALWAYS        ,
                            FILE_ATTRIBUTE_NORMAL,
                            NULLPTR);
    
    if(handle_out == INVALID_HANDLE_VALUE)
    {
        printf("Cannot open output file. Error: %x\n", GetLastError());
    }
    
    while((ReadFile(handle_in, recieve_buffer, BUFFER_SIZE, &bytes_read, NULLPTR) && bytes_read) > 0)
    {
        WriteFile(handle_out    ,
                  recieve_buffer,
                  bytes_read    , 
                  &bytes_written,
                  NULLPTR);
        
        if(bytes_written != bytes_read)
        {
            printf("Fatal write error: %x\n", GetLastError());
            return 4; // NOTE(MIGUEL): wtf??
        }
        
    }
    
    CloseHandle(handle_in );
    CloseHandle(handle_out);
    
    return 0;
}