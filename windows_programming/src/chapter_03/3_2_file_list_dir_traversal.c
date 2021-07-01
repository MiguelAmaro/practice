#include "windows_programming/chapter_02/2_1_report_error.c"
#include "windows_programming/options.c"
//#include "string.c"
#include <windows.h>
#include <string.h>

#define MAX_OPTIONS   (20)
#define MAX_PATH_LONG (32767)
#define TYPE_FILE (1)
#define TYPE_DIR  (2)
#define TYPE_DOT  (3)

internal b32 process_item      (WIN32_FIND_DATA *file_data, u32 num_flags, b32 *flags);
internal b32 traverse_directory(u8 * parent_path, u8 * search_pattern, u32 num_flags, b32 *flags);
internal u32 get_file_type     (WIN32_FIND_DATA *file_data);

u32 file_list_dir_traversal(u32 arg_count, u8 *command_line[])
{
    b32 flags[MAX_OPTIONS];
    b32 ok = TRUE;
	u8 search_pattern[MAX_PATH      + 1];
    u8 current_path  [MAX_PATH_LONG + 1];
    u8 parent_path   [MAX_PATH_LONG + 1];
    
	u8 *slash;
    u8 *search_pathern_ptr;
    u32 file_index;
	u32 path_len;
    
	file_index = options(arg_count, command_line, "Rl", &flags[0], &flags[1], NULLPTR);
    
	/* "Parse" the search pattern into two parts: the "parent"
		and the file name or wild card expression. The file name
		is the longest suffix not containing a slash.
		The parent is the remaining prefix with the slash.
		This is performed for all command line search patterns.
		If no file is specified, use * as the search pattern. */
    
	path_len = GetCurrentDirectory(MAX_PATH_LONG, current_path); 
    
	if (path_len == 0 || path_len >= MAX_PATH_LONG)
    { 
        /// path_len >= MAX_PATH_LONG (32780) should be impossible */
		report_error("GetCurrentDirectory failed", 1, TRUE);
	}
    
	if (arg_count < file_index + 1) 
    {
		ok = traverse_directory(current_path, "*", MAX_OPTIONS, flags);
    }
	else 
    {
        for (u32 i = file_index; i < arg_count; i++) 
        {
            if (strlen(command_line[i]) >= MAX_PATH)
            {
                report_error("The command line argument is longer than the maximum this program supports", 2, FALSE);
            }
            
            strcpy(search_pattern, command_line[i]);
            strcpy(parent_path, command_line[i]);
            
            /* Find the rightmost slash, if any.
                Set the path and use the rest as the search pattern. */
            slash = strchr(parent_path, '\\'); 
            
            if (slash != NULL)
            {
                *slash = '\0';
                
                strcat(parent_path, "\\");         
                
                SetCurrentDirectory(parent_path);
                
                slash = strrchr(search_pattern, '\\');  
                search_pathern_ptr = slash + 1;
            }
            else
            {
                strcpy(parent_path, ".\\");
                search_pathern_ptr = search_pattern;
            }
            ok = traverse_directory(parent_path, search_pathern_ptr, MAX_OPTIONS, flags) && ok;
            SetCurrentDirectory(current_path);	 /* Restore working directory. */
        }
    }
    
	return ok ? 0 : 1;
}


/* Traverse a directory, carrying out an implementation specific "action" for every
	name encountered. The action in this version is "list, with optional attributes". */
/* search_pattern: Relative or absolute search_pattern to traverse in the parent_path.  */
/* On entry, the current direcotry is parent_path, which ends in a \ */
internal b32 traverse_directory(u8 * parent_path, u8 * search_pattern, u32 num_flags, b32 *flags)
{
	HANDLE searchHandle;
	WIN32_FIND_DATA findData;
	b32 recursive = flags[0];
	u32 fType, iPass;
    u32 lenParentPath;
    u8 subdirectoryPath[MAX_PATH + 1];
    
	/* Open up the directory search handle and get the
		first file name to satisfy the path name.
		Make two passes. The first processes the files
		and the second processes the directories. */
    
	if ( _tcslen(search_pattern) == 0 ) {
		strcat(search_pattern, "*");
	}
	/* Add a backslash, if needed, at the end of the parent path */
	if (parent_path[strlen(parent_path)-1] != '\\') 
    { /* Add a \ to the end of the parent path, unless there already is one */
		strcat (parent_path, "\\");
	}
    
    
	/* Open up the directory search handle and get the
		first file name to satisfy the path name. Make two passes.
		The first processes the files and the second processes the directories. */
    
	for (iPass = 1; iPass <= 2; iPass++)
    {
		searchHandle = FindFirstFile(search_pattern, &findData);
        
		if (searchHandle == INVALID_HANDLE_VALUE)
        {
			report_error("Error opening Search Handle.", 0, TRUE);
			
            return FALSE;
		}
        
		/* Scan the directory and its subdirectories for files satisfying the pattern. */
		do
        {
            
            /* For each file located, get the type. List everything on pass 1.
                On pass 2, display the directory name and recursively process
                the subdirectory contents, if the recursive option is set. */
			fType = get_file_type(&findData);
			if (iPass == 1) /* ProcessItem is "print attributes". */
				process_item(&findData, MAX_OPTIONS, flags);
            
			lenParentPath = (u32)strlen(parent_path);
			/* Traverse the subdirectory on the second pass. */
			if (fType == TYPE_DIR && iPass == 2 && recursive)
            {
				printf("\n%s%s:", parent_path, findData.cFileName);
                
				SetCurrentDirectory(findData.cFileName);
                
				if (strlen(parent_path) + strlen(findData.cFileName) >= MAX_PATH_LONG-1)
                {
					report_error("Path Name is too long", 10, FALSE);
				}
				strcpy(subdirectoryPath, parent_path);
				strcat (subdirectoryPath, findData.cFileName); /* The parent path terminates with \ before the strcat call */
				
                traverse_directory(subdirectoryPath, "*", num_flags, flags);
				SetCurrentDirectory(".."); /* Restore the current directory */
			}
            
			/* Get the next file or directory name. */
            
		} while (FindNextFile(searchHandle, &findData));
        
		FindClose(searchHandle);
	}
    
	return TRUE;
}



/* Return file type from the find data structure.
	Types supported:
		TYPE_FILE:	If this is a file
		TYPE_DIR:	If this is a directory other than . or ..
		TYPE_DOT:	If this is . or .. directory */

internal u32 get_file_type(WIN32_FIND_DATA *file_data)
{
	b32 is_dir;
	u32 file_type;
	
    file_type = TYPE_FILE;
	
    is_dir =(file_data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	if (is_dir)
    {
		if ((strcmp(file_data->cFileName, "." ) == 0) ||
            (strcmp(file_data->cFileName, "..") == 0))
        {
            file_type = TYPE_DOT;
        }
    }
    else 
    {
        file_type = TYPE_DIR;
    }
    
	return file_type;
}

/* 
Function to process(list attributes, in this case)
	the file or directory. This implementation only shows
	the low order part of the file size. 
*/
internal b32 process_item(WIN32_FIND_DATA *file_data, u32 num_flags, b32 *flags)
{
    readonly u8 fileTypeChar[] = {' ', 'd'};
    
	u32 file_type = get_file_type(file_data);
	b32 long_list = flags[1];
	
    SYSTEMTIME last_write;
    
	if (file_type != TYPE_FILE && file_type != TYPE_DIR) return FALSE;
    
	printf("\n");
	
    if (long_list)
    {
		printf("%c", fileTypeChar[file_type - 1]);
        printf("%10d", file_data->nFileSizeLow);
		
        FileTimeToSystemTime(&(file_data->ftLastWriteTime), &last_write);
        
		printf("	%02d/%02d/%04d %02d:%02d:%02d",
               last_write.wMonth, last_write.wDay,
               last_write.wYear, last_write.wHour,
               last_write.wMinute, last_write.wSecond);
	}
    
	printf(" %s", file_data->cFileName);
    
	return TRUE;
}
