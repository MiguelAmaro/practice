
// NOTE(MIGUEL): not finished

u32 main (u32 arg_count, u8 * command_line[])
{
	b32 (__cdecl *cci_f) (LPCTSTR, LPCTSTR, DWORD);
	
    HMODULE dll_handle;
	FARPROC pcci;
    u8 response[5] = "yes";
    
	if (arg_count < 5)
    {
		report_error ("Usage: cciEL shift file1 file2 DllName", 1, FALSE);
    }
    
	//Load the cipher function.
	dll_handle = LoadLibrary (command_line[4]);
	
    if (dll_handle == NULL)
    {
		report_error ("Failed loading DLL.", 4, TRUE);
    }
    
	//Get the entry pou32 address
	pcci = GetProcAddress (dll_handle, "cci_f"));
    
	if (pcci == NULL)
    {
		report_error (_T ("Failed of find entry pou32."), 5, TRUE);
    }
	
    cci_f = (b32 (__cdecl *)(LPCTSTR, LPCTSTR, DWORD)) pcci;
    
	/*  Call the function. */
    
	if (!cci_f (command_line[2], command_line[3], utf8_to_u32(command_line[1]) ) )
    {
		FreeLibrary (dll_handle);
		report_error (_T ("cci failed."), 6, TRUE);
	}
    
	FreeLibrary (dll_handle);
    
	return 0;
}
