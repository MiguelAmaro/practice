#include "chapter_02/2_1_report_error.c"
#include "chapter_04/4_1_report_exception.c"
#include "windows_version_ok.c"
#include "string.h"
#include <stdio.h>

u32 to_upper (u32 arg_count, u8 * command_line [])
{
	HANDLE input_file_handle = INVALID_HANDLE_VALUE, output_file_handle = INVALID_HANDLE_VALUE;
	u32 bytes_read;
    u8 output_file_name[256] =  "";
    u8 *buffer = NULL;
	OVERLAPPED ov = { 0, 0, 0, 0, NULL};
	LARGE_INTEGER file_size;
    
	if (!windows_version_ok(3, 1)) 
    {
        
		report_error ("This program requires Windows NT 3.1 or greater"
                      " to support LockFileEx",1, FALSE);
    }
    
	if (arg_count <= 1)
    {
		report_error ("Usage: toupper files", 1, FALSE);
    }
    /* Process all files on the command line. */
	for (u32 file_index = 1; file_index < arg_count; file_index++)
        __try
    { 
        /*
Exception block
            All file handles are invalid, buffer == NULL, and 
            output_file_name is empty. This is assured by the handlers
*/
        if (string_get_length(command_line[file_index]) > 250)
        {
            report_exception("The file name is too long.", 1);
        }
        
        printf(output_file_name, "UC_%s", command_line[file_index]);
        
        __try
        {   // Inner try-finally block
            // Create the output file name, and create it (fail if file exists) */
            // The file can be shared by other processes or threads */
            input_file_handle  = CreateFile (command_line [file_index],
                                             GENERIC_READ, 
                                             0, NULL, OPEN_EXISTING, 0, NULL);
            
            if (input_file_handle == INVALID_HANDLE_VALUE)
            {
                report_exception (command_line[file_index], 1);
            }
            
            if (!GetFileSizeEx (input_file_handle, &file_size) || file_size.HighPart > 0)
            {
                report_exception("This file is too large for this program.", 1);
            }
            
            output_file_handle = CreateFile (output_file_name,
                                             GENERIC_READ | GENERIC_WRITE, 
                                             0, NULL, CREATE_NEW, 0, NULL);
            
            if (output_file_handle == INVALID_HANDLE_VALUE)
            {
                report_exception (output_file_name, 1);
            }
            
            /* Allocate memory for the file contents */
            buffer = malloc (file_size.LowPart); 
            
            if (buffer == NULL) 
            {
                report_exception ("Memory allocation error", 1);
            }
            
            /* Read the data, convert it, and write to the output file */
            /* Free all resources upon completion, and then process the next file */
            /* Files are not locked, as the files are open with 0
             *     for the share mode. However, in a more general situation, you
             *     might have a process (Chapter 7) inherit the file handle or a 
             *     thread (Chapter 7) might access the handle. Or, you might
             *     actually want to open the file in share mode                    */
            
            if (!ReadFile (input_file_handle, buffer, file_size.LowPart, &bytes_read, NULL)
                || (bytes_read != file_size.LowPart))
            {
                report_exception ("ReadFile error", 1);
            }
            
            for (u32 j = 0; j < file_size.LowPart; j++) /* Convert data */
            {
                if (isalpha(buffer[j])) buffer[j] = toupper(buffer[j]);
            }
            
            if (!WriteFile (output_file_handle, buffer, file_size.LowPart, &bytes_read, NULL)
                || (bytes_read != file_size.LowPart))
            {
                report_exception ("WriteFile error", 1);
            }
            
        }
        __finally
        { 
            // File handles are always closed
            // memory freed, and handles and pou32er reinitialized
            if (buffer != NULL)
            {
                free(buffer); buffer = NULL;
            }
            
            if (input_file_handle  != INVALID_HANDLE_VALUE)
            {
                CloseHandle (input_file_handle);
                input_file_handle  = INVALID_HANDLE_VALUE;
            }
            
            if (output_file_handle != INVALID_HANDLE_VALUE)
            {
                CloseHandle (output_file_handle);
                output_file_handle = INVALID_HANDLE_VALUE;
            }
            
            string_copy(output_file_name, sizeof(output_file_name),
                        "", 0);
        }
    }
	__except (EXCEPTION_EXECUTE_HANDLER)
    {
		printf ("Error occured processing file %s\n", command_line[file_index]);
		DeleteFile (output_file_name);
	}
	printf ("All files converted, except as noted above\n");
	
    return 0;
}
