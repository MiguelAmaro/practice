#include "windows.h"
#include "stdio.h"
#include "LAL.h"

#include "chapter_02\2_1_report_error.c"

#define MAX_PATH_LONG (32767)

global u8 g_working_directory[MAX_PATH_LONG];
global u8 g_working_directory_len;

typedef enum
{
    file,
    dir,
    dot,
}File_type;

File_type get_file_type(WIN32_FIND_DATA *data)
{
    b32 is_directory = false;
    File_type result = file;
	
    is_directory =(data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    
	if (is_directory)
	{
		if (strcmp(data->cFileName, "." ) == 0 ||
            strcmp(data->cFileName, "..") == 0)
		{
			result = dot;
		}
		else
		{
			result = dir;
		}
	}
    
	return result;
}


// NOTE(MIGUEL): 
//parse all chapter folders
//bundle chpater file data = inportant info needed:
//file name
//entry function name
//chapter number 
//example number

// NOTE(MIGUEL): I KNOW THIS FUNCTION IS JANKY AS FUCK
void meta_update_example_switches(HANDLE file_handle)
{
    WIN32_FIND_DATAA data = { 0 };
    HANDLE           search_handle;
    u8               sub_directory[MAX_PATH];
    
    u8 header[] = 
        "#ifndef EXAMPLE_SWITCH_H\n"
        "#define EXAMPLE_SWITCH_H\n\n"
        "#include \"LAL.h\"\n\n"
        "global u32 g_selected_example = WIN32_EXAMPLE_SELECT;\n\n"
        "#define WIN32_EXAMPLE(example_number, function_call) \\\n"
        "if(g_selected_example == (example_number)) return (function_call)\n";
    
    
    u8 chapter_divider[] = "//- ";
    
    // es: expample switch
    u8 es_template[] = 
        "#if WIN32_EXAMPLE_SELECT == (  )\n"
        "#include \"\"\n"
        "#else\n"
        "u32 (u32 arg_count, u8 *command_line[])\n"
        "{ return 1; }\n"
        "#endif\n\n";
    
    u32 es_offset_example_num  = sizeof("#if WIN32_EXAMPLE_SELECT == (") - 1;
    
    u32 es_offset_file_include = sizeof("#if WIN32_EXAMPLE_SELECT == (  )\n"
                                        "#include \"") - 1;
    
    // NOTE(MIGUEL): useles because the offset above is variable length
    u32 es_offset_func_name    = sizeof("#if WIN32_EXAMPLE_SELECT == (  )\n"
                                        "#include \"\"\n"
                                        "#else\n""u32 ") - 1;
    
    u8 footer[] = "#endif // EXAMPLE_SWITCH_H";
    
    
    strcpy(sub_directory, g_working_directory);
    strcat(sub_directory, "src\\*");
    
    printf("sub dir:  %s\n", sub_directory);
    
    search_handle = FindFirstFileA(sub_directory, &data);
    
    if(search_handle == INVALID_HANDLE_VALUE)
    {
        report_error_ansi("FindFirstFile: ", 1, 1 );
    }
    
    u8 buffer[1024];
    u32 str_len = 0;
    u32 bytes_written;
    
    memset(buffer, 0, sizeof(buffer));
    
    WriteFile(file_handle,  header, sizeof(header) - 1, &bytes_written, 0);
    WriteFile(file_handle,  "\n\n", sizeof("\n\n") - 1, &bytes_written, 0);
    
    while(FindNextFileA(search_handle, &data))
    {
        
        File_type file_type = get_file_type(&data);
        
        
        if(file_type == file)
        {
            printf("Not an example");
        }
        else if(file_type == dir && (strncmp(data.cFileName, "chapter_", (sizeof("chapter_") - 1)) == 0))
        {
            u8 chapter_number[8];
            
            strcpy(chapter_number, data.cFileName + (sizeof("chapter_") - 1));
            
            u32 divider_size = 0;
            strcpy(buffer, chapter_divider);
            strcat(buffer, "CHAPTER ");
            strcat(buffer, chapter_number);
            strcat(buffer, " \n\r");
            divider_size = (u32)strlen(buffer);
            
            WriteFile(file_handle,
                      buffer,
                      divider_size,
                      &bytes_written, 0);
            
            printf("strlen: %d | str: %s\n", divider_size, buffer);
            memset(buffer, 0, strlen(buffer));
            
            // NOTE(MIGUEL): charpter dir concat doest account previous chapter concat
            HANDLE chapter_search_handle;
            u8 chapter_directory[512];
            
            strncpy(chapter_directory, sub_directory, sizeof(chapter_directory));
            
            chapter_directory[strlen(sub_directory) - 1] = '\0'; // get rid of wild card
            strcat(chapter_directory, data.cFileName);
            strcat(chapter_directory, "\\*");
            printf("new sub dir:  %s\n", chapter_directory);
            
            SetCurrentDirectory(sub_directory); //enter the chapter n folder
            
            chapter_search_handle = FindFirstFileA(chapter_directory, &data);
            
            while(FindNextFileA(chapter_search_handle, &data))
            {
                File_type file_type = get_file_type(&data);
                
                if(file_type == file)
                {
                    u8 function_name[256];
                    
                    //DEBUG
                    printf("including: %s\n", data.cFileName);
                    strcpy(buffer, es_template);
                    
                    //EXAMPLE NUMBER
                    buffer[es_offset_example_num    ] = *(data.cFileName);
                    buffer[es_offset_example_num + 1] = *(data.cFileName + 2);
                    
                    //INCLUDE FILE
                    //strcpy(&buffer[es_offset_file_include], "chapter_");
                    //strcat(&buffer[es_offset_file_include + sizeof("chapter_")], chapter_number);
                    strcpy(&buffer[es_offset_file_include], "chapter_");
                    strcat(buffer, chapter_number);
                    strcat(buffer, "\\");
                    strcat(buffer, data.cFileName);
                    strcat(buffer, &es_template[es_offset_file_include]);
                    
                    //FUNCTION SYMBOL
                    strcpy(function_name, (data.cFileName + 4)); // eliminate leading example numbers
                    strcpy(&function_name[strlen(function_name) - 2], "  ");
                    strcpy(&buffer[es_offset_func_name + sizeof("chapter_")+ strlen(chapter_number) + strlen(data.cFileName)], function_name);
                    strcat(buffer, &es_template[es_offset_func_name]);
                    
                    WriteFile(file_handle, buffer, strlen(buffer), &bytes_written, 0);
                    
                    memset(buffer, 0, strlen(buffer));
                }
                else
                {
                    printf("No examples found!!!!\n");
                }
            }
            
            FindClose(chapter_search_handle);
        }
        else
        {
            printf("not chapter folder!!");
        }
    }
    
    FindClose(search_handle);
    
    return;
}

u32 main(u32 arg_count, u8 *args[])
{
    g_working_directory_len = GetCurrentDirectoryA(MAX_PATH_LONG, g_working_directory); 
    
    strcat(g_working_directory, "\\");
    g_working_directory_len += 2;
    
    printf("working dir:  %s\n", g_working_directory);
    
    HANDLE file_handle = CreateFileW(L".\\src\\example_switch.h",
                                     GENERIC_READ | GENERIC_WRITE,
                                     0,
                                     NULLPTR,
                                     OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL,
                                     0);
    
    meta_update_example_switches(file_handle);
    
    CloseHandle(file_handle);
    
    return 0;
}
