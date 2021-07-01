#ifndef REPORT_ERROR_2_1
#define REPORT_ERROR_2_1

#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include "LAL.h"

void report_error_ansi(u8 *user_message, u32 exit_code, b32 print_error_message)
{
    u32 error_message_length;
    u32 error_code          ;
    u8 *system_message      ;
    
    error_code = GetLastError();
    
    // NOTE(MIGUEL): Generic text. windows macro dependent functions. UTF8 or UTF16
    
    fprintf(stderr, ("%s"), user_message);
    
    if(print_error_message)
    {
        error_message_length = FormatMessageA(
                                              FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                              FORMAT_MESSAGE_FROM_SYSTEM     ,
                                              NULL                           ,
                                              error_code                     ,
                                              MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                              (u8 *)&system_message, 0, NULLPTR);
        
        if(error_message_length > 0)
        {
            fprintf(stderr, "%s\n", system_message);
        }
        else
        {
            fprintf(stderr, "Last Error Number; %d.\n", error_code);
        }
        if(system_message != NULLPTR)
        {
            LocalFree(system_message); /// See Ch. 5
        }
    }
    
    if(exit_code > 0)
    {
        ExitProcess(exit_code);
    }
    
    return;
}

void report_error_utf16(u16 *user_message, u32 exit_code, b32 print_error_message)
{
    //decode the first 16 bits to see if its 16 bit wide of 32 bit widde
    
    u32 error_message_length;
    u32 error_code          ;
    u16 *system_message      ;
    
    error_code = GetLastError();
    
    // NOTE(MIGUEL): Generic text. windows macro dependent functions. UTF8 or UTF16
    
    fwprintf(stderr, (L"%s\n"), user_message);
    
    if(print_error_message)
    {
        error_message_length = FormatMessageA(
                                              FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                              FORMAT_MESSAGE_FROM_SYSTEM     ,
                                              NULL                           ,
                                              error_code                     ,
                                              MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                              (u8 *)&system_message, 0, NULLPTR);
        
        if(error_message_length > 0)
        {
            fwprintf(stderr, L"%s\n", system_message);
        }
        else
        {
            fwprintf(stderr, L"Last Error Number; %d.\n", error_code);
        }
        if(system_message != NULLPTR)
        {
            LocalFree(system_message); /// See Ch. 5
        }
    }
    
    if(exit_code > 0)
    {
        ExitProcess(exit_code);
    }
    
    return;
}

#endif