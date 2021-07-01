//************************************************************
// TIME: 30 min
// 
// GOAL:
// Create a function that copies a file using the c standard library

// EXERCISES:
// Use the file api in binary mode for input and text mode for output
// write about the results.
// Do the same thing running this on linux on a virtual machine
// 
// Use the timep.exe in Dev\Study\WindowSystemsProgramming to time-
// this funciton and compare it with the other copy fucntions when 
// handling large files
// 
// 
// LOG:
// 4/01/2021 - folllowing the windows systems programming book
//
// ************************************************************

#include <stdio.h>
#include <errno.h>
#include "LAL.h"

#define BUFFER_SIZE (256)

// TODO(MIGUEL): Look up windows status codes

u32 copy_file_stdlib(int arg_count,u8 *command_line[])
{
    FILE *file_in ;
    FILE *file_out;
    
    u8 recieve_buffer[BUFFER_SIZE]; // NOTE(MIGUEL): why such a big buffer???
    
    size_t bytes_read   ;
    size_t bytes_written;
    
    if(arg_count != 3)
    {
        printf("This app requires two files.\n");
        printf("Usage: copy <file 1> into <file 2>\n");
        return 1;
    }
    
    file_in = fopen(command_line[1], "rb");
    
    if(file_in == NULLPTR)
    {
        perror(command_line[1]);
        return 2; // NOTE(MIGUEL): what is this status code?
    }
    
    file_out = fopen(command_line[2], "wb");
    
    if(file_out == NULLPTR)
    {
        perror(command_line[2]);
        return 3;
    }
    
    /// Read one byte from input file store it in the buffer then write it to the output file
    while((bytes_read = fread(recieve_buffer, 1, BUFFER_SIZE, file_in)) > 0)
    {
        bytes_written  = fwrite(recieve_buffer, 1, bytes_read, file_out);
        
        if(bytes_written != bytes_read)
        {
            perror("Fatal write error.");
            return 4; // NOTE(MIGUEL): wtf??
        }
    }
    
    fclose(file_in );
    fclose(file_out);
    
    return 0;
}