#include "windows.h"
#include "stdio.h"
#include "LAL.h"

// ************************************************************
// TIME: 30 min
// 
// GOAL:
// Do the Windows Sys programming tutorial then ... 
// Write an anonymouse pipe that takes two programs and transfers data
//
// LOG:
// 03/27/2021 -
// 
// ************************************************************

// TODO(MIGUEL): implement process 1 & 2

VOID   ReportError (LPCSTR userMessage, DWORD exitCode, BOOL printErrorMessage);
LPCSTR SkipArg     (LPCSTR cLine, int argn, int argc, LPCSTR argv[]);


void ic_create_and_manage_pipes(u32 argc, LPCSTR *argv)
{
    HANDLE read_pipe;
    HANDLE write_pipe;
    
    u8 commands[MAX_PATH];
    SECURITY_ATTRIBUTES pipe_SA = 
    {
        sizeof(SECURITY_ATTRIBUTES),
        (void *)0x00,
        TRUE
    };
    
    PROCESS_INFORMATION proc_info_1;
    PROCESS_INFORMATION proc_info_2;
    
    STARTUPINFO start_info_ch_1;
    STARTUPINFO start_info_ch_2;
    
    LPCSTR cl_args = GetCommandLine();
    
    GetStartupInfo(&start_info_ch_1);
    GetStartupInfo(&start_info_ch_2);
    
    cl_args = SkipArg(cl_args, 1, argc, argv);
    u32 cl_index = 0; // NOTE(MIGUEL): Get 2 commands
    while(*cl_args != '=' && *cl_args != ('\0'))
    {
        commands[cl_index] = *cl_args;
        
        cl_args++ ; cl_index++;
    }
    commands[cl_index] = '\0';
    if(*cl_args == '\0')
    {
        ReportError("No command seperator found.", 2, FALSE);
    }
    cl_args = SkipArg(cl_args, 1, argc, argv);
    
    CreatePipe(&read_pipe, &write_pipe, &pipe_SA, 0);
    
    start_info_ch_1.hStdInput  = GetStdHandle(STD_INPUT_HANDLE);
    start_info_ch_1.hStdError  = GetStdHandle(STD_ERROR_HANDLE);
    start_info_ch_1.hStdOutput = write_pipe;
    start_info_ch_1.dwFlags    = STARTF_USESTDHANDLES;
    
    CreateProcessA(0, commands, 0, 0, TRUE, 0, 0, 0, &start_info_ch_1, &proc_info_1);
    
    CloseHandle(proc_info_1.hThread); 
    CloseHandle(write_pipe);
    
    
    start_info_ch_1.hStdInput  = read_pipe;
    start_info_ch_1.hStdError  = GetStdHandle(STD_ERROR_HANDLE);
    start_info_ch_1.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    start_info_ch_1.dwFlags    = STARTF_USESTDHANDLES;
    
    CreateProcessA(0, (u8 *)cl_args, 0, 0, TRUE, 0, 0, 0, &start_info_ch_2, &proc_info_2);
    
    
    CloseHandle(proc_info_2.hThread); 
    CloseHandle(read_pipe);
    
    // TODO(MIGUEL): Do more shit...
    
    return;
}

VOID ReportError (LPCSTR userMessage, DWORD exitCode, BOOL printErrorMessage)
{
	DWORD eMsgLen, errNum = GetLastError ();
	LPCSTR lpvSysMsg;
	fprintf (stderr, ("%s\n"), userMessage);
	if (printErrorMessage) {
		eMsgLen = FormatMessageA (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                                  NULL, errNum, MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
                                  (LPSTR) &lpvSysMsg, 0, NULL);
		if (eMsgLen > 0)
		{
			fprintf (stderr, ("%s\n"), lpvSysMsg);
		}
		else
		{
			fprintf (stderr, ("Last Error Number; %d.\n"), errNum);
		}
        
		if (lpvSysMsg != NULL) LocalFree((u8 *)lpvSysMsg); /* Explained in Chapter 5. */
	}
    
	if (exitCode > 0)
		ExitProcess (exitCode);
    
	return;
}


LPCSTR SkipArg(LPCSTR cLine, int argn, int argc, LPCSTR argv[])
{
	LPCSTR pArg = cLine, cEnd = pArg + _tcslen(cLine);
	int iArg;
    
	if (argn >= argc) return NULL;
    
	for (iArg = 0; iArg < argn && pArg < cEnd; iArg++)
	{
		// NOTE(MIGUEL): _tcslen... wide char fuckery in here
        if ('"' == *pArg)
		{ pArg += _tcslen(argv[iArg]) + 2; /* Skip over the argument and the enclosing quotes */ }
		else
		{ pArg += _tcslen(argv[iArg]); /* Skip over the argument */ }
        
		while ( (pArg < cEnd) && ( ((' ') == *pArg) || (('\t')) == *pArg) ) pArg++;
	}
    
	if (pArg >= cEnd) return NULL;
	return pArg;
}

