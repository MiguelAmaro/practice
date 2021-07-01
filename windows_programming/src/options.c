#include <windows.h>
#include <stdarg.h>
#include <tchar.h>
//#include <windows.h>


/*************************************************************
/* It looks for any cl flags specified in the arguments and sets
/* the each flags respective option state(just a boolean). Then
/* return the index 
/* 
/*
/* The options, if any, start with a '-' in argv[1], argv[2], ...
	/* options_set is a text string containing all possible options,
	/* in one-to-one correspondence with the addresses of Boolean variables
	/* in the variable argument list (...).
	/* These flags are set if and only if the corresponding option
	/* character occurs in argv [1], argv [2], ...
	/* The return value is the argv index of the first argument beyond the options.
/* argv is the command line.
/*
/**************************************`***********************/

u32 options(u32 arg_count, u8 *command_line[], u8 *options_set, ...)
{
    b32     *flag     ;
	va_list  flag_list;
    
    u32 flag_index = 0;
    u32 arg_index  = 0;
    
	va_start(flag_list, options_set);
    
	while((( flag = va_arg(flag_list, b32 *) ) != NULLPTR) && (flag_index < (u32)strlen(options_set)) )
    {
        *flag = FALSE;
        
        for (arg_index = 1; 
             !(*flag) && (arg_index < arg_count) && (command_line [arg_index] [0] == '-'); 
             arg_index++)
        {
            b32 *result = memchr(       command_line[ arg_index]  ,
                                 options_set        [flag_index]  ,
                                 strlen(command_line[ arg_index]));
            
            *flag = result != NULLPTR;
        }
        
        flag_index++;
    }
    
    va_end(flag_list);
    
    for(arg_index = 1; (arg_index < arg_count) && (command_line [arg_index][0] == '-'); arg_index++);
    
    return arg_index;
}

u32 options_tchar(u32 arg_count, LPCTSTR command_line[], LPCTSTR options_set, ...)
{
    b32     *flag     ;
	va_list  flag_list;
    
    u32 flag_index = 0;
    u32 arg_index  = 0;
    
	va_start(flag_list, options_set);
    
	while((( flag = va_arg(flag_list, b32 *) ) != NULLPTR) && (flag_index < (u32)_tslen(options_set)) )
    {
        *flag = FALSE;
        
        for (arg_index = 1; 
             !(*flag) && (arg_index < arg_count) && (command_line [arg_index] [0] == _T('-')); 
             arg_index++)
        {
            b32 *result;
            *result = _memtchr(       command_line[ arg_index]  ,
                               options_set        [flag_index]  ,
                               _tcslen(command_line[ arg_index]));
            
            *flag = result != NULLPTR;
        }
        
        flag_index++;
    }
    
    va_end(flag_list);
    
    for(arg_index = 1; (arg_index < arg_count) && (command_line [arg_index][0] == _T('-')); arg_index++);
    
    return arg_index;
}


