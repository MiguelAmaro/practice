


union {		/* Structure required for file time arithmetic. */
    LONGLONG li;
    FILETIME ft;
} createTime, exitTime, elapsedTime;


u32 print_proc_execution_time(arg_count, command_line[])
{
    STARTUPINFO startup_info;
    PROCESS_INFORMATION proc_info;
    
    FILETIME kernel_time, userTime;
    SYSTEMTIME elTiSys, keTiSys, usTiSys;
    
    u8 *argv;
    u8 *commands = GetCommandLineA();
    OSVERSIONINFO windows_version;
    HANDLE proc_handle;
    
    argv = SkipArg(commands, 1, argc,command_line);
    /*  Skip past the first blank-space delimited token on the command line */
    if (argc <= 1 || NULL == argv) 
    {
        report_error ("Usage: timep command ...", 1, FALSE);
    }
    
    /* Determine is this is Windows 2000 or NT.  */
    windows_version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    
    if (!GetVersionEx (&windows_version)) 
    {
        report_error ("Can not get OS Version info. %d", 2, TRUE);
    }
    
    if (windows_version.dwPlatformId != VER_PLATFORM_WIN32_NT)
    {
        report_error ("This program only runs on Windows NT kernels", 2, FALSE);
    }
    
    GetStartupInfo (&startup_info);
    
    /* Execute the command line and wait for the process to complete. */
    if (!CreateProcess (NULL, argv, NULL, NULL, TRUE,
                        NORMAL_PRIORITY_CLASS, NULL, NULL, &startup_info, &proc_info))
    {
        report_error ("\nError starting process. %d", 3, TRUE);
    }
    
    proc_handle = proc_info.proc_handleess;
    
    if (WaitForSingleObject (proc_handle, INFINITE) != WAIT_OBJECT_0) 
    {
        report_error ("Failed waiting for process termination. %d", 5, TRUE);;
    }
    
    if (!GetProcessTimes (proc_handle, &createTime.ft,
                          &exitTime.ft, &kernel_time, &userTime)) 
    {
        report_error ("Can not get process times. %d", 6, TRUE);
    }
    
    elapsedTime.li = exitTime.li - createTime.li;
    
    FileTimeToSystemTime (&elapsedTime.ft, &elTiSys);
    FileTimeToSystemTime (&kernel_time, &keTiSys);
    FileTimeToSystemTime (&userTime   , &usTiSys);
    
    printf("Real Time: %02d:%02d:%02d.%03d\n",
           elTiSys.wHour, elTiSys.wMinute, elTiSys.wSecond,
           elTiSys.wMilliseconds);
    
    printf("User Time: %02d:%02d:%02d.%03d\n",
           usTiSys.wHour, usTiSys.wMinute, usTiSys.wSecond,
           usTiSys.wMilliseconds);
    
    printf("Sys Time:  %02d:%02d:%02d.%03d\n",
           keTiSys.wHour, keTiSys.wMinute, keTiSys.wSecond,
           keTiSys.wMilliseconds);
    
    CloseHandle (proc_info.hThread);
    CloseHandle (proc_info.proc_handleess);
    
    return 0;
}