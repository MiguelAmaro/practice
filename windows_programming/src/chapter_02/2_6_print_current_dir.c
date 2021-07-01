#include "windows_programming/chapter_02/2_1_report_error.c"
#include "windows_programming/chapter_02/2_5_console_prompt_print_utils.c"
#include <stdarg.h>
#include <windows.h>
#include "LAL.h"

#define DIRNAME_LEN (MAX_PATH + 2)

u32 print_current_dir(u32 arg_count, u8 *command_line[])
{
    u8  buffer[DIRNAME_LEN];
    u32 current_dir_str_len;
    
    current_dir_str_len = GetCurrentDirectory(DIRNAME_LEN, buffer);
    
    if(current_dir_str_len == 0)
    {
        report_error("Error: Failed to get pathname.\n", 1, TRUE);
    }
    if(current_dir_str_len > DIRNAME_LEN)
    {
        report_error("Failure: pathname is too long.\n", 2, FALSE);
    }
    
    print_messsage(GetStdHandle(STD_OUTPUT_HANDLE), buffer);
    
    return 0;
}