#include "windows_programming/chapter_02/2_1_report_error.c"
#include <stdarg.h>
#include <windows.h>
#include "LAL.h"

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
#define BUFFER_SIZE (256)

// NOTE(MIGUEL): only supports possitive shifts
u32 print_strings(HANDLE output_handle, ...)
{
    u32 message_length;
    u32 count;
    
    u8     *message     ;
    va_list message_list;
    
    
    va_start(message_list, output_handle);
    
    while((message = va_arg(message_list, u8 *)) != NULLPTR)
    {
        message_length = strlen(message);
        
        if(!WriteConsole(output_handle, message, message_length, &count, NULL) &&
           !WriteFile   (output_handle, message, message_length * sizeof(u8), &count, NULL))
        {
            va_end(message_list);
            
            return FALSE;
        }
    }
    
    va_end(message_list);
    
    return TRUE;
}

internal b32 print_messsage(HANDLE output_handle, u8 * message)
{
    return print_strings(output_handle, message, NULLPTR);
}

// NOTE(MIGUEL): USED IN EXAMPLE OF CHAPTERS 11 & 15
u32 console_prompt(u8 *prompt_message, u8 *response, u32 max_char, b32 echo)
{
    HANDLE  input_handle;
    HANDLE output_handle;
    
    u32 input_char;
    u32 echo_flag ;
    
    b32 success;
    
    input_handle = CreateFileA("CONIN$",
                               GENERIC_READ | GENERIC_WRITE,
                               0, NULLPTR,
                               OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,
                               NULL);
    
    output_handle = CreateFileA("CONOUT$",
                                GENERIC_WRITE,
                                0, NULLPTR,
                                OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,
                                NULL);
    
    echo_flag = echo ? ENABLE_ECHO_INPUT : 0;
    
    success = (SetConsoleMode(input_handle,
                              ENABLE_LINE_INPUT     |
                              echo_flag             |
                              ENABLE_PROCESSED_INPUT)
               && 
               SetConsoleMode(input_handle,
                              ENABLE_LINE_INPUT     |
                              echo_flag             |
                              ENABLE_PROCESSED_INPUT)
               &&
               print_strings (output_handle,
                              prompt_message,
                              NULLPTR)
               &&
               ReadConsole   (input_handle,
                              response,
                              (max_char - 2),
                              &input_char, NULLPTR));
    
    if(success)
    {
        response[input_char - 2] = '\0';
    }
    else
    {
        report_error("Console Prompt failiure.", 0, TRUE);
    }
    
    CloseHandle(input_handle);
    CloseHandle(output_handle);
    
    return success;
}

