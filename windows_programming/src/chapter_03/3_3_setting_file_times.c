#include "chapter_02/2_1_report_error.c"
#include "options.c"

u32 setting_file_times(u32 arg_count, LPTSTR command_line[])
{
	FILETIME new_file_time;
    
	FILETIME *access_time = NULLPTR;
    FILETIME *modify_time = NULLPTR;
	
    HANDLE file_handle;
	
    b32 set_access_time;
	b32 set_mod_time;
	b32 not_create_new;
	
    u32 create_flag;
	s32 file_index;
    
	/// Determine the options
    
	if (arg_count < 2)
    {
        printf("Usage: touch[options] files");
		
        return 1;
	}
    
	file_index = options(arg_count,
                         command_line, "amc",
                         &set_access_time,
                         &set_mod_time,
                         &not_create_new, NULLPTR);
    
	create_flag = not_create_new ? OPEN_EXISTING : OPEN_ALWAYS;
    
	for (u32 i = file_index; i < arg_count; i++)
    {
		file_handle = CreateFile(command_line[i],
                                 GENERIC_READ | GENERIC_WRITE,
                                 0, NULLPTR,
                                 create_flag, FILE_ATTRIBUTE_NORMAL, NULL);
		if (file_handle == INVALID_HANDLE_VALUE)
        {
			if (!not_create_new) 
            {
                report_error("touch error: Cannot open file.", 0, TRUE);
            }
			
            continue;
		}
        
		/* Get current system time and convert to a file time.
			Do not change the create time. */
        
		GetSystemTimeAsFileTime(&new_file_time);
        
		if (set_access_time) { access_time = &new_file_time; }
		if (set_mod_time)    { modify_time = &new_file_time; }
        
		if (!SetFileTime(file_handle, NULL, access_time, modify_time))
        {
			report_error("Failure setting file times.", 2, TRUE);
        }
        
		CloseHandle(file_handle);
	}
    
	return 0;
}
