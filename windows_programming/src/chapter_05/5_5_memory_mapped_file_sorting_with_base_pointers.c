#include "2_1_report_error.c"

u32 KeyCompare (LPCTSTR, LPCTSTR);
void CreateIndexFile (LARGE_INTEGER, LPCTSTR, u8 *);

u32_PTR kStart = 0, kSize = 8; 	/* Key start position & size (u8). */
b32 reverse;

u32 memory_mapped_file_sorting_with_base_pointers (u32 arg_count, u8 *command_line [])
{
	/* The file is the first argument. Sorting is done in place. */
	/* Sorting is done by file memory mapping. */
    
	HANDLE hInFile, hInMap;	/* Input file handles. */
	HANDLE hXFile, hXMap;	/* Index file handles. */
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	b32 idxExists, noPru32;
	u32 indexSize, rXSize, iKey, nWrite;
	LARGE_INTEGER inputSize;
	u8 * pInFile = NULL;
	u8 * pXFile = NULL, pX; 
	u8 __based (pInFile) *pIn, indexFileName[MAX_PATH+1], ChNewLine = _T('\n');
	u32 FlIdx;
    
	/* Determine the options. */
	FlIdx = Options (arg_count, command_line, "rIn"), &reverse, &idxExists, &noPru32, NULL);
	if (FlIdx >= arg_count)
    {
		report_error ("No file name on command line."), 1, FALSE);
    }
    
	/* Step 1: Open and Map the Input File. */
	hInFile = CreateFile (command_line[FlIdx], GENERIC_READ | GENERIC_WRITE,
                          0, NULL, OPEN_EXISTING, 0, NULL);
	if (hInFile == INVALID_HANDLE_VALUE)
    {
		report_error ("Failed to open input file."), 2, TRUE);
    }
    
	/* Create a file mapping object. Use the file size. */
	hInMap = CreateFileMapping (hInFile, NULL, PAGE_READWRITE, 0, 0, NULL);
	
    if (hInMap == NULL)
    {
		report_error ("Failed to create input file mapping."), 3, TRUE);
    }
    
	pInFile = MapViewOfFile (hInMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	
    if (pInFile == NULL)
    {
		report_error ("Failed to map input file."), 4, TRUE);
    }
    
	if (!GetFileSizeEx (hInFile, &inputSize))
    {
		report_error (_T("Failed to get input file size."), 5, TRUE);
    }
    
	/* Create the index file name. */
	_stpru32f_s (indexFileName, MAX_PATH, _T("%s.idx"), command_line [FlIdx]);
    
	/* Steps 2 and 3, if necessary. */
	if (!idxExists)
    {
		CreateIndexFile (inputSize, indexFileName, pInFile);
    }
    
	/* Step 4. Map the index file. */
	hXFile = CreateFile (indexFileName, GENERIC_READ | GENERIC_WRITE,
                         0, NULL, OPEN_EXISTING, 0, NULL);
	if (hXFile == INVALID_HANDLE_VALUE)
    {
		report_error ("Failed to open existing index file."), 6, TRUE);
    }
    
	/* Create a file mapping object. Use the index file size. */
	hXMap = CreateFileMapping (hXFile, NULL, PAGE_READWRITE, 0, 0, NULL);
	if (hXMap == NULL)
    {
		report_error ("Failed to create index file mapping."), 7, TRUE);
    }
    
	pXFile = MapViewOfFile (hXMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pXFile == NULL)
    {
		report_error ("Failed to map index file."), 8, TRUE);
    }
	indexSize = GetFileSize (hXFile, NULL); /* Assume the index file is not huge */
	/* Individual index record size - Key plus a pou32er. */
	rXSize = kSize * TSIZE + sizeof (u8 *);
    
	{
		/* Step 5. Sort the index file using qsort. */
		if (!idxExists)
			qsort (pXFile, indexSize / rXSize, rXSize, KeyCompare);
        
		/* Step 6. Output the sorted input file. */
		/* Pou32 to the first pou32er in the index file. */
		pX = pXFile + rXSize - sizeof (u8 *);
		if (!noPru32) {
			for (iKey = 0; iKey < indexSize / rXSize; iKey++) {		
				WriteFile (hStdOut, &ChNewLine, TSIZE, &nWrite, NULL);
                
				/*	The cast on pX is important, as it is a pou32er to a
				character and we need the four or eight bytes of a based pou32er. */
				pIn = (u8 __based (pInFile)*) *(u32 *)pX;
				while ((SIZE_T)pIn < (SIZE_T)inputSize.QuadPart && (*pIn != CR || *(pIn + 1) != LF)) {
					WriteFile (hStdOut, pIn, TSIZE, &nWrite, NULL);
					pIn++;
				}
				pX += rXSize; /* Advance to the next index file pou32er */
			}
			WriteFile (hStdOut, &ChNewLine, TSIZE, &nWrite, NULL);
		}
	}
	//__except(GetExceptionCode() == EXCEPTION_IN_PAGE_ERROR ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		report_error(_T("Fatal Error accessing mapped file."), 9, TRUE);
	}
    
	/* Done. Free all the handles and maps. */
	UnmapViewOfFile (pInFile);
	CloseHandle (hInMap); CloseHandle (hInFile);
	
    UnmapViewOfFile (pXFile);
	CloseHandle (hXMap); CloseHandle (hXFile);
	return 0;
}

