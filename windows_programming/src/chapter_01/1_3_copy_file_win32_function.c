//************************************************************
// TIME: 30 min
// 
// GOAL:
// Use the copy file funciton in the win32 api
//
// Use the timep.exe in Dev\Study\WindowSystemsProgramming to time-
// this funciton and compare it with the other copy fucntions when 
// handling large files
//
// LOG:
// 4/1/2021 - folllowing the windows systems programming book
//
// ************************************************************

#include <windows.h>
#include <stdio.h>

u32 copy_file_win32(int argc,u8 *argv[])
{
    if(argc != 3)
    {
        printf("This app requires two files.\n");
        printf("Usage: copy <file 1> into <file 2>\n");
        return 1;
    }
    
    if(!CopyFile(argv[1], argv[2], FALSE))
    {
        printf("CopyFile Error: %x\n", GetLastError());
        return 2;
    }
    
    return 0;
}