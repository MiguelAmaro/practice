
VOID CreateIndexFile (LARGE_INTEGER inputSize, LPCTSTR indexFileName, LPTSTR pInFile)

/* Perform Steps 2-3 as defined in program description. */
/* This step will be skipped if the options specify use of an existing index file. */
{
	HANDLE hXFile;
	TCHAR __based (pInFile) *pInScan = 0;
	DWORD nWrite;
    
	/* Step 2: Create an index file.
	Do not map it yet as its length is unknown. */
	hXFile = CreateFile (indexFileName, GENERIC_READ | GENERIC_WRITE,
                         FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL);
	if (hXFile == INVALID_HANDLE_VALUE)
		ReportError (_T ("Failure to create index file."), 10, TRUE);
    
	/* Step 3. Scan the complete file, writing keys
	   and record pointers to the key file. */
	while ((DWORD_PTR) pInScan < inputSize.QuadPart) {
		WriteFile (hXFile, pInScan + kStart, kSize * TSIZE, &nWrite, NULL);
		WriteFile (hXFile, &pInScan, sizeof (LPTSTR), &nWrite, NULL);
		while ((DWORD) (DWORD_PTR)pInScan < inputSize.QuadPart - sizeof(TCHAR) && 
               ((*pInScan != CR) || (*(pInScan + 1) != LF))) {
			pInScan++; /* Skip to end of line. */
		}
		pInScan += 2; /* Skip past CR, LF. */
	}
	CloseHandle (hXFile);
	return;
}

int KeyCompare (LPCTSTR pKey1, LPCTSTR pKey2)

/* Compare two records of generic characters.
The key position and length are global variables. */
{
	DWORD i;
	TCHAR t1, t2;
	int Result = 0;
	for (i = kStart; i < kSize + kStart && Result == 0; i++) {
		t1 = *pKey1;
		t2 = *pKey2;
		if (t1 < t2)
			Result = -1;
		if (t1 > t2) 
			Result = +1;
		pKey1++;
		pKey2++;
	}
	return reverse ? -Result : Result;
}
