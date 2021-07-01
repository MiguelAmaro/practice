#include "chapter_02/2_1_report_error.c"
#include <stdio.h>

void report_exception_ansi(u8 *message, u32 exception_code)
{	
    if (strlen(message) > 0)
    {
        report_error_ansi(message, 0, TRUE);
    }
    
	if (exception_code != 0) 
    {
		RaiseException ((0x0FFFFFFF & exception_code) | 0xE0000000, 0, 0, NULL);
    }
	
	return;
}


void report_exception_utf16(u16 *message, u32 exception_code)
{	
    if (wcslen(message) > 0)
    {
        report_error_utf16(message, 0, TRUE);
    }
    
	if (exception_code != 0) 
    {
		RaiseException((0x0FFFFFFF & exception_code) | 0xE0000000, 0, 0, NULL);
    }
	
	return;
}