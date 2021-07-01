#include "chapter_04/4_4_filter.c"
#include "chapter_04/4_1_report_exception.c"
#include <float.h>
#include <stdio.h>
#include <wchar.h>
#include "windows.h"

f64 x = 1.0f;
f64 y = 0.0f;

u32 exception_and_termination_processing(u32 arg_count, u8 *command_line[])
{
    DWORD eCategory, i = 0, ix, iy = 0;
	LPDWORD pNull = NULL;
	BOOL done     = FALSE;
	DWORD fpOld, fpNew, fpOldDummy;
	
    
    //__try { /* Try-Finally block.
    // Save old control mask.
	_controlfp_s (&fpOld, 0, 0);
    
    // Enable floating-point exceptions.
	fpNew = fpOld & ~(EM_OVERFLOW   |
                      EM_UNDERFLOW  |
                      EM_INEXACT    |
                      EM_ZERODIVIDE |
                      EM_DENORMAL   |
                      EM_INVALID    );
    
    /* Set new control mask. */
	_controlfp_s (&fpOldDummy, fpNew, MCW_EM);
	
    while (!done) __try
    { 
		wprintf(L"Enter exception type:\n");
		wprintf(L"1: Mem, 2: Int, 3: Flt 4: User 5: _leave 6: return\n");
		wscanf_s(L"%d", &i);
		
        __try
        { /* Try-Except block. */
			switch (i)
            {
                case 1: /* Memory reference. */
				ix = *pNull;
				*pNull = 5;
				break;
                case 2: /* Integer arithmetic. */
				ix = ix / iy;
				break;
                case 3: /* floating-point exception. */
				x = x / y;
				wprintf(L"x = %20e\n", x);
				break;
                case 4: /* User generated exception. */
                report_exception_utf16(L"Raising user exception.\n", 1);
				break;
                case 5: /* Use the _leave statement to terminate. */
				done = TRUE;
				__leave;
                case 6: /* Use the return statement to terminate. */
				return 1;
                default: done = TRUE;
			}
		}
        
		__except (filter(GetExceptionInformation (), &eCategory))
        {
			switch (eCategory)
            {
                case 0:	wprintf (L"Unknown exception.\n");
				break;
                
                case 1:	wprintf (L"Memory ref exception.\n");
				break;
                
                case 2:	wprintf (L"Integer arithmetic exception.\n");
				break;
                
                case 3:	wprintf (L"floating-point exception.\n");
				break;
                
                case 10: wprintf (L"User generated exception.\n");
				break; 
                
                default: wprintf (L"Unknown exception.\n");
				break;
			}
            
			wprintf (L"End of handler.\n");
		}
        
        
        
        //} /* End of exception generation loop. */
        
        //return; /* Cause an abnormal termination. */
        
	} /* End of outer __try __finally */
	__finally
    {
		BOOL AbTerm; /* Restore the old mask value. */
		_controlfp_s (&fpOldDummy, fpOld, MCW_EM);
		AbTerm = AbnormalTermination();
		wprintf (L"Abnormal Termination?: %d\n", AbTerm);
    }
	return 0;
}

