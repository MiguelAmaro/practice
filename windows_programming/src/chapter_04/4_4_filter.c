

/*
Categorize the exception and decide whether to continue execution or
execute the handler or to continue the search for a handler that
can process this exception type. The exception category is only used
by the exception handler.
*/

u32 filter (LPEXCEPTION_POINTERS exception, LPDWORD eCategory)
{
	DWORD exCode;
    
    u32 readWrite, virtAddr;
	exCode = exception->ExceptionRecord->ExceptionCode;
	
    wprintf(L"Filter. exCode: %x\n", exCode);
	
    if ((0x20000000 & exCode) != 0)
    {
        /* User Exception. */
		*eCategory = 10;
		return EXCEPTION_EXECUTE_HANDLER;
	}
    
	switch (exCode)
    {
		case EXCEPTION_ACCESS_VIOLATION:
        /*
        Determine whether it was a read, write, or execute
                    and give the virtual address.
        */
        readWrite = (DWORD)(exception->ExceptionRecord->ExceptionInformation [0]);
        virtAddr  = (DWORD)(exception->ExceptionRecord->ExceptionInformation [1]);
        
        wprintf(L"Access Violation. Read/Write/Execute: %d. Address: %x\n", readWrite, virtAddr);
        
        *eCategory = 1;
        return EXCEPTION_EXECUTE_HANDLER;
        
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        *eCategory = 1;
        return EXCEPTION_EXECUTE_HANDLER;
        
        /* Integer arithmetic exception. Halt execution. */
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
		case EXCEPTION_INT_OVERFLOW:
        *eCategory = 2;
        return EXCEPTION_EXECUTE_HANDLER;
        
        /* Float exception. Attempt to continue execution. */
        /* Return the maximum floating value. */
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		case EXCEPTION_FLT_OVERFLOW:
        wprintf (L"Flt Exception - Large result.\n");
        
        *eCategory = 3;
        _clearfp();
        return EXCEPTION_EXECUTE_HANDLER;
        
		case EXCEPTION_FLT_DENORMAL_OPERAND:
		case EXCEPTION_FLT_INEXACT_RESULT:
		case EXCEPTION_FLT_INVALID_OPERATION:
		case EXCEPTION_FLT_STACK_CHECK:
        wprintf (L"Flt Exception - Unknown result.\n");
        *eCategory = 3;
        return EXCEPTION_CONTINUE_EXECUTION;
        
        /* Return the minimum floating value. */
		case EXCEPTION_FLT_UNDERFLOW:
        wprintf (L"Flt Exception - Small result.\n");
        *eCategory = 3;
        return EXCEPTION_CONTINUE_EXECUTION;
        
		case EXCEPTION_DATATYPE_MISALIGNMENT:
        *eCategory = 4;
        return EXCEPTION_CONTINUE_SEARCH;
        
		case STATUS_NONCONTINUABLE_EXCEPTION:
        *eCategory = 5;
        return EXCEPTION_EXECUTE_HANDLER;
        
		case EXCEPTION_ILLEGAL_INSTRUCTION:
		case EXCEPTION_PRIV_INSTRUCTION:
        *eCategory = 6;
        return EXCEPTION_EXECUTE_HANDLER;
        
		case STATUS_NO_MEMORY:
        *eCategory = 7;
        return EXCEPTION_EXECUTE_HANDLER;
        
		default:
        *eCategory = 0;
        return EXCEPTION_CONTINUE_SEARCH;
        
    }
}
