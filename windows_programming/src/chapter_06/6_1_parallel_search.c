#include <windows.h>

typedef struct
{
    u8 temp_file[MAX_PATH];
} PROCFILE;


u32 main(u32 arg_count, command_line[])
{
    HANDLE temp_file;
	SECURITY_ATTRIBUTES stdOutSA = 
    {
        sizeof (SECURITY_ATTRIBUTES), NULL, TRUE
    };
    
    u8 commands[MAX_PATH + 100];
	
  STARTUPINFO startup_search;
	STARTUPINFO startup;
    
	PROCESS_INFORMATION proc_info;
	DWORD exitCodedwCreationFlags = 0;
	DWORD dwCreationFlags = 0;
    
	HANDLE *proc_handle;  /* Pointer to an array of proc_handle handles. */
    
	PROCFILE *proc_file_handle; /* Pointer to array of temp file names. */
    
    
	if (arg_count < 3)
		ReportError (_T ("Usage: grepMP pattern files."), 1, FALSE);
    
	/* Startup info for each child search proc_handleess as well as
		the child proc_handleess that will display the results. */
    
	GetStartupInfo (&startup_search);
	GetStartupInfo (&startup);
    
	/* Allocate storage for an array of proc_handleess data structures,
		each containing a proc_handleess handle and a temporary file name. */
    
	proc_file_handle = malloc ((arg_count - 2) * sizeof (PROCFILE));
	proc_handle      = malloc ((arg_count - 2) * sizeof (HANDLE));
    
	/* Create a separate "grep" proc_handleess for each file on the
		command line. Each proc_handleess also gets a temporary file
		name for the results; the handle is communicated through
		the STARTUPINFO structure. command_line[1] is the search pattern. */
    
	for (proc_index = 0; proc_index < arg_count - 2; proc_index++)
    {
        
		/* Create a command line of the form: grep command_line[1] command_line[proc_index + 2] */
		/* Allow spaces in the file names. */
		_stprintf (commands,
                   "grep \"%s\" \"%s\"",
                   command_line[1],
                   command_line[proc_index + 2]);
        
		/* Create the temp file name for std output. */
        
		if (GetTempFileName (_T ("."), _T ("gtm"), 0, proc_file_handle[proc_index].tempFile) == 0)
			report_error (_T ("Temp file failure."), 2, TRUE);
        
		/* Set the std output for the search proc_handleess. */
        
		temp_file = /* This handle is inheritable */
			CreateFile (proc_file_handle[proc_index].tempFile,
                        GENERIC_WRITE,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        &stdOutSA,
                        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        
		if (temp_file == INVALID_HANDLE_VALUE)
        {
			report_error (_T ("Failure opening temp file."), 3, TRUE);
        }
        
		/* Specify that the new proc_handleess takes its std output
			from the temporary file's handles. */
        
		startup_search.dwFlags    = STARTF_USESTDHANDLES;
		startup_search.hStdOutput = temp_file;
		startup_search.hStdError  = temp_file;
		startup_search.hStdInput  = GetStdHandle (STD_INPUT_HANDLE);
		/* Create a proc_handleess to execute the command line. */
        
		if (!CreateProcess (NULL, commands, NULL, NULL,
                            TRUE, dwCreationFlags, NULL, NULL, &startup_search, &proc_info))
        {
			report_error (_T ("ProcCreate failed."), 4, TRUE);
        }
		/* Close unwanted handles */
		CloseHandle (temp_file); CloseHandle (proc_info.hThread);
        
		/* Save the proc_handleess handle. */
        
		proc_handle[proc_index] = proc_info.proc_handleess;
	}
    
	/* Processes are all running. Wait for them to complete, then output
		the results - in the order of the command line file names. */
	for (proc_index = 0; proc_index < arg_count-2; proc_index += MAXIMUM_WAIT_OBJECTS)
    {
		WaitForMultipleObjects (min(MAXIMUM_WAIT_OBJECTS,arg_count - 2 - proc_index), 
                                &proc_handle[proc_index],
                                TRUE, INFINITE);
        
    }
    
	/* Result files sent to std output using "cat".
		Delete each temporary file upon completion. */
    
	for (proc_index = 0; proc_index < arg_count - 2; proc_index++) 
    { 
		if (GetExitCodeProcess (proc_handle[proc_index], &exitCode) && exitCode == 0) 
        {
			/* Pattern was detected - List results. */
			/* List the file name if there is more than one file to search */
			if (arg_count > 3)
            {
                _tprintf (_T("%s:\n"), command_line[proc_index+2]);
            }
			_stprintf (commands, _T ("cat \"%s\""), proc_file_handle[proc_index].tempFile);
            
			if (!CreateProcess (NULL, commands, NULL, NULL,
                                TRUE, dwCreationFlags, NULL,
                                NULL, &startup,
                                &proc_info))
            {
				report_error ("Failure executing cat."), 0, TRUE);
            }
			else
            { 
				WaitForSingleObject (proc_info.proc_handleess, INFINITE);
				CloseHandle         (proc_info.proc_handleess);
				CloseHandle         (proc_info.hThread);
			}
		}
        
		CloseHandle (proc_handle[proc_index]);
		
        if (!DeleteFile (proc_file_handle[proc_index].tempFile))
        {
			report_error (_T ("Cannot delete temp file."), 6, TRUE);
        }
	}
    
	free (proc_file_handle);
    free (proc_handle);
	
    return 0;
}
