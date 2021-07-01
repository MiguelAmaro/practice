#include "windows_programming/2_1_report_error.c"
#include <windows.h>
#include "string.c"
#include "LAL.h"

#define BUFFER_SIZE (256)

u32 utf8_to_u32(u8 *string);

internal b32 ceaser_cipher(u8 *str_input, u8 *str_output, u32 shift );

// NOTE(MIGUEL): only supports possitive shifts
u32 file_encryption(u32 arg_count, u8 *command_line[])
{
    if(arg_count != 4)
    {
        report_error_ansi("Usage: [cipher shift] [file 1] [file 2]", 1, FALSE);
    }
    
    if(!ceaser_cipher(command_line[2], command_line[3], utf8_to_u32(command_line[1])))
    {
        report_error_ansi("Encryption Failed.", 4, TRUE);
    }
    
    return 0;
}

// NOTE(MIGUEL): 2_4_ceaser_cipher
internal b32 ceaser_cipher(u8 *str_input, u8 *str_output, u32 shift )
{
    b32 write_successful = TRUE;
    
    HANDLE file_in ;
    HANDLE file_out;
    
    u32 bytes_read   ;
    u32 bytes_written;
    u32 copy_index   ;
    
    u8 read_buffer  [BUFFER_SIZE];
    u8 cipher_buffer[BUFFER_SIZE];
    
    file_in = CreateFile(str_input            ,
                         GENERIC_READ         ,
                         0                    ,
                         NULL                 ,
                         OPEN_EXISTING        ,
                         FILE_ATTRIBUTE_NORMAL,
                         NULLPTR)             ;
    
    if(file_in == INVALID_HANDLE_VALUE)
    { 
        return FALSE;
    }
    
    file_out = CreateFile(str_output           ,
                          GENERIC_WRITE        ,
                          0                    ,
                          NULL                 ,
                          CREATE_ALWAYS        ,
                          FILE_ATTRIBUTE_NORMAL,
                          NULLPTR)             ;
    
    if(file_out == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }
    
    while(ReadFile(file_in, read_buffer, BUFFER_SIZE, &bytes_read, NULLPTR) 
          && (bytes_read > 0) && write_successful)
    {
        for(copy_index = 0; copy_index < bytes_read; copy_index++)
        {
            cipher_buffer[copy_index] = (read_buffer[copy_index] + shift) % 256;
        }
        
        write_successful = WriteFile(file_out, cipher_buffer, bytes_read, &bytes_written, NULLPTR);
    }
    
    return write_successful;
}
