// Chapter 12. Client/Server. SERVER PROGRAM.  SOCKET VERSION.	
// Execute the command in the request and return a response.	
// Commands will be exeuted in process if a shared library 	
// entry point can be located, and out of process otherwise	
// ADDITIONAL FEATURE: args[1] can be the name of a DLL supporting 
// in process services 

#include "winsock2.h"
#include "windows.h"

#include "sockets_client_server.h"	// Defines the request and response records.
#include "chapter_02/2_1_report_error.c"
#include "windows_version_ok.c"

#include <wchar.h>

#include "LAL.h"

typedef enum
{
    SERVER_SLOT_FREE,
    SERVER_THREAD_STOPPED, 
    SERVER_THREAD_RUNNING,
    SERVER_SLOT_INVALID
}Server_thread_status;

// Server thread arguments
typedef struct
{ 
	CRITICAL_SECTION thread_crit_sec;
	u32	   number;
	SOCKET	socket;
	Server_thread_status thread_status; 	
	HANDLE	server_thread;
	HINSTANCE dll_handle; // Shared libary handle
} Server_context;

internal b32 Server_receive_request(Request  *req, SOCKET);
internal b32 Server_send_response  (Response *res, SOCKET);

internal u32  WINAPI Server_serve_client_on_new_thead (PVOID);
internal u32  WINAPI Server_accept_thread (PVOID);
internal BOOL WINAPI Server_handler (u32);

volatile internal int g_shutdown_flag = 0;

struct sockaddr_in g_server_address;		   // Server's Socket address structure
struct sockaddr_in g_connected_client_address; // Connected socket with client details
WSADATA            g_socket_start_data;	    // Socket library data structure

internal SOCKET g_server_socket           = INVALID_SOCKET;
internal SOCKET g_connected_client_socket = INVALID_SOCKET;

u32 socket_based_server(int arg_count, u8 *args [])
{
	// Server listening and connected sockets.
	u32 thread_index;
    u32 thread_status;
    
	Server_context server_context[MAX_CLIENTS];
	HANDLE hAcceptThread = NULL;
	HINSTANCE dll_handle = NULL;
    
	if (!windows_version_ok(3, 1)) 
    {
		report_error_utf16 (L"This program requires Windows NT 3.1 or greater", 1, FALSE);
    }
    
	// Console control handler to permit server shutdown 
	if(!SetConsoleCtrlHandler((PHANDLER_ROUTINE)Server_handler, 1))
    {
        report_error_utf16 (L"Cannot create Ctrl handler", 1, TRUE);
    }
    
    //	Initialize the WS library. Ver 2.0
    if (WSAStartup(MAKEWORD(2, 0), &g_socket_start_data) != 0)
    {
        report_error_utf16 (L"Cannot support sockets", 1, TRUE);
        
    }
    
    // Open the shared command library DLL if it is specified on command line 
    if (arg_count > 1)
    {
        dll_handle = LoadLibrary (args[1]);
        if (dll_handle == NULL)
        {
            report_error_ansi(args[1], 0, 1);
        }
    }
    
    // Intialize thread arg array 
    for (thread_index = 0; thread_index < MAX_CLIENTS; thread_index++)
    {
        InitializeCriticalSection (&server_context[thread_index].thread_crit_sec);
        server_context[thread_index].number = thread_index;
        server_context[thread_index].thread_status = SERVER_SLOT_FREE;
        server_context[thread_index].socket = 0;
        server_context[thread_index].dll_handle = dll_handle;
        server_context[thread_index].server_thread = NULL;
    }
    
    
    //	Follow the standard server socket/bind/listen/accept sequence 
    g_server_socket = socket(PF_INET, SOCK_STREAM, 0);
    
    if (g_server_socket == INVALID_SOCKET) 
    {
		report_error_utf16 (L"Failed server socket() call", 1, TRUE);
    }
    
    /*
Prepare the socket address structure for binding the
            server socket to port number "reserved" for this service.
            Accept requests from any client machine.
*/
    
    g_server_address.sin_family = AF_INET;	
    g_server_address.sin_addr.s_addr = htonl( INADDR_ANY );    
    g_server_address.sin_port = htons( SERVER_PORT );	
    
    if (bind (g_server_socket, (struct sockaddr *)&g_server_address, sizeof(g_server_address)) == SOCKET_ERROR)
    {
		report_error_utf16 (L"Failed server bind() call", 2, TRUE);
    }
    if (listen (g_server_socket, MAX_CLIENTS) != 0) 
    {
		report_error_utf16 (L"Server listen() error", 3, TRUE);
    }
    
    // Main thread becomes listening/connecting/monitoring thread 
    // Find an empty slot in the server thread arg array 
    while (!g_shutdown_flag)
    {
        thread_index = 0;
        
        while (!g_shutdown_flag)
        {
            // Continously poll the thread thread_state of all server slots in the server_context table 
            EnterCriticalSection(&server_context[thread_index].thread_crit_sec);
            
            __try
            {
                if (server_context[thread_index].thread_status == SERVER_THREAD_STOPPED)
                {
                    // This thread stopped, either normally or there's a shutdown request 
                    // Wait for it to stop, and make the slot free for another thread 
                    thread_status = WaitForSingleObject (server_context[thread_index].server_thread, INFINITE);
                    
                    if (thread_status != WAIT_OBJECT_0)
                    {
                        report_error_utf16 (L"Server thread wait error", 4, TRUE);
                    }
                    
                    CloseHandle (server_context[thread_index].server_thread);
                    
                    server_context[thread_index].server_thread = NULL;
                    server_context[thread_index].thread_status = SERVER_SLOT_FREE;
                }				
                // Free slot identified or shut down. Use a free slot for the next connection 
                if (server_context[thread_index].thread_status == SERVER_SLOT_FREE || g_shutdown_flag)
                {
                    break;
                }
            }
            __finally
            {
                LeaveCriticalSection (&server_context[thread_index].thread_crit_sec); 
            }
            
            // Fixed July 25, 2014: thread_index = (thread_index++) % MAX_CLIENTS; 
            thread_index = (thread_index + 1) % MAX_CLIENTS;
            
            if (thread_index == 0)
            {
                Sleep(50); // Break the polling loop 
            }
            // An alternative would be to use an event to signal a free slot 
        }
        
        if (g_shutdown_flag)
        {
            break;
        }
        
        // server_context[thread_index] == SERVER_SLOT_FREE 
        // Wait for a connection on this socket 
        // Use a separate thread so that we can poll the g_shutdown_flag flag 
        hAcceptThread = (HANDLE)_beginthreadex(NULL, 0, Server_accept_thread, &server_context[thread_index], 0, NULL);
        
        if (hAcceptThread == NULL)
        {
            report_error_utf16 (L"Error creating AcceptThreadread.", 1, TRUE);
        }
        
        while (!g_shutdown_flag)
        {
            thread_status = WaitForSingleObject (hAcceptThread, CS_TIMEOUT);
            if (thread_status == WAIT_OBJECT_0)
            {
                // Connection is complete. server_context[thread_index] == SERVER_THREAD_RUNNING
                if (!g_shutdown_flag)
                {
                    CloseHandle (hAcceptThread);
                    hAcceptThread = NULL;
                }
                
                break;
            }
        }
    }  // OUTER while (!g_shutdown_flag)
    
    // g_shutdown_flag == TRUE 
    wprintf (L"Server shutdown in process. Wait for all server threads\n");
    
    // Wait for any active server threads to terminate 
    // Try continuously as some threads may be long running. 
    while (TRUE)
    {
        int nRunningThreads = 0;
        for (thread_index = 0; thread_index < MAX_CLIENTS; thread_index++)
        {
            EnterCriticalSection(&server_context[thread_index].thread_crit_sec);
            __try
            {
                if (server_context[thread_index].thread_status == SERVER_THREAD_RUNNING || server_context[thread_index].thread_status == SERVER_THREAD_STOPPED)
                {
                    if (WaitForSingleObject (server_context[thread_index].server_thread, 10000) == WAIT_OBJECT_0)
                    {
                        wprintf (L"Server thread on slot %d stopped.\n", thread_index);
                        
                        CloseHandle (server_context[thread_index].server_thread);
                        
                        server_context[thread_index].server_thread = NULL;
                        server_context[thread_index].thread_status = SERVER_SLOT_INVALID;
                    }
                    else
                    {
                        if (WaitForSingleObject (server_context[thread_index].server_thread, 10000) == WAIT_TIMEOUT)
                        {
                            wprintf (L"Server thread on slot %d still running.\n", thread_index);
                            nRunningThreads++;
                        }
                        else 
                        {
                            wprintf (L"Error waiting on server thread in slot %d.\n", thread_index);
                            report_error_utf16 (L"Thread wait failure", 0, TRUE);
                        }
                    }
                }
            }
            __finally
            {
                LeaveCriticalSection(&server_context[thread_index].thread_crit_sec);
            }
        }
        
        if (nRunningThreads == 0)
        {
            break;
        }
    }
    
    if (dll_handle != NULL)
    {
        FreeLibrary (dll_handle);	
    }
    
    // Redundant shutdown
    shutdown (g_server_socket, SD_BOTH);
    closesocket (g_server_socket);
    WSACleanup();
    
    if (hAcceptThread != NULL && WaitForSingleObject(hAcceptThread, INFINITE) != WAIT_OBJECT_0)
    {
        report_error_utf16 (L"Failed waiting for accept thread to terminate.", 7, FALSE);
    }
    
    return 0;
}

static u32 Server_accept_thread(void *thread_arg)
{
    s32 addrLen;
	Server_context *context = (Server_context *)thread_arg;
	
	addrLen = sizeof(g_connected_client_address);
    
	context->socket = accept(g_server_socket, (struct sockaddr *)&g_connected_client_address, &addrLen);
	
    if (context->socket == INVALID_SOCKET) 
    {
		report_error_utf16 (L"accept: invalid socket error", 1, TRUE);
		return 1;
	}
    
	// A new connection. Create a server thread
	EnterCriticalSection(&(context->thread_crit_sec));
	__try 
    {
		context->server_thread = (HANDLE)_beginthreadex (NULL, 0, Server_accept_thread, context, 0, NULL);
		if (context->server_thread == NULL)
        {
			report_error_utf16 (L"Failed creating server thread", 1, TRUE);
        }
        
		context->thread_status = SERVER_THREAD_RUNNING; 
		wprintf (L"Client accepted on slot: %d, using server thread %d.\n", context->number, GetThreadId (context->server_thread));
		// Exercise: Display client machine and process information
	}
	__finally
    {
        LeaveCriticalSection(&(context->thread_crit_sec));
    }
    
	return 0;
}

b32 Server_handler(u32 CtrlEvent)
{
	// Recives ^C. Shutdown the system
	wprintf(L"In console control handler\n");
	InterlockedIncrement (&g_shutdown_flag);
	
    return TRUE;
}

// Server thread function. There is a thread for every potential client.
static u32 WINAPI server_serve_client_on_new_thread (void *thread_arg)
{
	
    // Each thread keeps its own request, response,
    // and bookkeeping data structures on the stack.
    
	/* NOTE: All messages are in 8-bit characters */
    
	b32 done = FALSE;
    
	STARTUPINFO startInfoCh;
	
    SECURITY_ATTRIBUTES tempSA = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	
    PROCESS_INFORMATION procInfo;
	
    SOCKET g_connected_client_socket;
	int    commandLen;
	
    Request  request;	
	Response response;
	
    char sysCommand[MAX_REQ_RES_LEN];
    
    u8 tempFile[100];
	HANDLE hTmpFile;
	
    FILE *fp = NULL;
	
    int (__cdecl *dl_addr)(char *, char *);
	
    Server_context *context = (Server_context *)thread_arg;
	Server_thread_status thread_status;
    
	GetStartupInfo (&startInfoCh);
	
	g_connected_client_socket = context->socket;
    
	//Create a temp file name
	tempFile[sizeof(tempFile)/sizeof(WCHAR) - 1] = '\0';
	_stprintf_s (tempFile, sizeof(tempFile)/sizeof(TCHAR) - 1, L"ServerTemp%d.tmp", context->number);
    
	while (!done && !g_shutdown_flag)
    {
        // Main Server Command Loop. 
		
        done = server_receive_request (&request, g_connected_client_socket);
        
		request.record[sizeof(request.record)-1] = '\0';
		commandLen = (int)(strcspn (request.record, "\n\t"));
		memcpy (sysCommand, request.record, commandLen);
		sysCommand[commandLen] = '\0';
		wprintf (L"Command received on server slot %d: %hs\n", context->number, sysCommand);
        
		// Restest g_shutdown_flag, as it can be set from the console control handler. 
		done = done || (strcmp (request.record, "$Quit") == 0) || g_shutdown_flag;
		
        if (done)
        {
            continue;	
        }
        
		// Open the temporary results file. 
		hTmpFile = CreateFile (tempFile, GENERIC_READ | GENERIC_WRITE,
                               FILE_SHARE_READ | FILE_SHARE_WRITE, &tempSA,
                               CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		
        if (hTmpFile == INVALID_HANDLE_VALUE)
        {
			report_error_utf16 (L"Cannot create temp file", 1, TRUE);
        }
        
		// Check for a shared library command. For simplicity, shared 	
		// library commands take precedence over process commands 	
		// First, extract the command name (space delimited) 
		
        dl_addr = NULL; // will be set if GetProcAddress succeeds 
		
        if (context->dll_handle != NULL)
        {
            // Try Server "In process"
			char commandName[256] = "";
			int commandNameLength = (int)(strcspn (sysCommand, " "));
			
            strncpy_s (commandName, sizeof(commandName), sysCommand, min(commandNameLength, sizeof(commandName) - 1));
            
            dl_addr = (int (*)(char *, char *))GetProcAddress (context->dll_handle, commandName);
            
            // You really need to trust this DLL not to corrupt the server
            // This assumes that we don't allow the DLL to generate known exceptions
            
            if (dl_addr != NULL)
            {
                __try
                { 
                    (*dl_addr)(request.record, tempFile);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                { 
                    // Exception in the DLL
                    wprintf (L"Unhandled Exception in DLL. Terminate server. There may be orphaned processes.");
                    return 1;
                }
            }
		}
        
		if (dl_addr == NULL)
        { 
            // No inprocess support 
			// Create a process to carry out the command. 
            
			startInfoCh.hStdOutput = hTmpFile;
			startInfoCh.hStdError  = hTmpFile;
			startInfoCh.hStdInput  = GetStdHandle (STD_INPUT_HANDLE);
			startInfoCh.dwFlags    = STARTF_USESTDHANDLES;
			
            if (!CreateProcess (NULL, request.record, NULL,
                                NULL, TRUE, // Inherit handles. 
                                0, NULL, NULL, &startInfoCh, &procInfo))
            {
				PrintMsg(hTmpFile, L"ERR: Cannot create process.");
				
                procInfo.hProcess = NULL;
			}
			
            CloseHandle (hTmpFile);
			
            if (procInfo.hProcess != NULL )
            {
				CloseHandle (procInfo.hThread);
                
				WaitForSingleObject (procInfo.hProcess, INFINITE);
				
                CloseHandle (procInfo.hProcess);
			}
		}
        
		// Respond a line at a time. It is convenient to use
		// C library line-oriented routines at this point. 
        
        // Send the temp file, one line at a time, with header, to the client. 		
        if(fopen_s(&fp, tempFile, "r") == 0)
        {
			{	
				response.length = MAX_REQ_RES_LEN;
				while ((fgets (response.record, MAX_REQ_RES_LEN, fp) != NULL)) 
                {
					server_send_response (&response, g_connected_client_socket);
                }
			}
            
			// Send a zero length message. Messages are 8-bit characters, not UNICODE. 
			response.record[0] = '\0';
			
            server_send_response (&response, g_connected_client_socket);
			
            fclose (fp); fp = NULL;
			DeleteFile (tempFile); 
		}
		else
        {
			report_error_utf16(L"Failed to open temp file with command results", 0, TRUE);
		}
        
	}// End of main command loop. Get next command 
	
	// done || g_shutdown_flag 
	// End of command processing loop. Free resources and exit from the thread. 
	wprintf (L"Shuting down server thread number %d\n", context->number);
	
    // Redundant shutdown. There are no further attempts to send or receive 
	shutdown (g_connected_client_socket, SD_BOTH); 
	closesocket (g_connected_client_socket);
    
	EnterCriticalSection(&(context->thread_crit_sec));
	
    __try
    {
		thread_status = context->thread_status = SERVER_THREAD_STOPPED;
	}
	__finally
    {
        LeaveCriticalSection(&(context->thread_crit_sec));
    }
    
	return thread_status;	
}

b32 Server_receive_request (Request *pRequest, SOCKET sd)
{
	b32 disconnect = FALSE;
	LONG32 nRemainRecv = 0, nXfer;
	LPBYTE pBuffer;
    
	//	Read the request. First the header, then the request text. 
	nRemainRecv = REQ_HEADER_LEN; 
	pBuffer = (LPBYTE)pRequest;
    
	while (nRemainRecv > 0 && !disconnect)
    {
		nXfer = recv (sd, pBuffer, nRemainRecv, 0);
		
        if (nXfer == SOCKET_ERROR) 
        {
			report_error_utf16 (L"server request recv() failed", 11, TRUE);
        }
        
		disconnect = (nXfer == 0);
		nRemainRecv -=nXfer; pBuffer += nXfer;
	}
	
	//	Read the request record 
	nRemainRecv = pRequest->length;
	// Exclude buffer overflow 
	nRemainRecv = min(nRemainRecv, MAX_REQ_RES_LEN);
    
	pBuffer = (LPSTR)pRequest->record;
    
	while (nRemainRecv > 0 && !disconnect)
    {
		nXfer = recv (sd, pBuffer, nRemainRecv, 0);
		
        if (nXfer == SOCKET_ERROR) 
        {
			report_error_utf16 (L"server request recv() failed", 12, TRUE);
        }
        
		disconnect = (nXfer == 0);
		nRemainRecv -=nXfer; pBuffer += nXfer;
	}
    
	return disconnect;
}

b32 Server_send_response (Response *res, SOCKET socket)
{
	b32 disconnect = FALSE;
	
    s32 nRemainRecv = 0;
	s32 transfer_count;
	s32 nRemainSend;
    
    u8 *buffer;
    
    //Send the response up to the string end. Send in 
    //two parts - header, then the response string.
	
    nRemainSend = RES_HEADER_LEN; 
	res->length = (long)(strlen (res->record)+1);
    
	buffer = (u8 *)res;
	
    //SEND HEADER
    while (nRemainSend > 0 && !disconnect)
    {
		transfer_count = send(socket, buffer, nRemainSend, 0);
		
        if (transfer_count == SOCKET_ERROR)
        {
            report_error_utf16 (L"server send() failed", 13, TRUE);
        }
		
        disconnect = (transfer_count == 0);
		nRemainSend -=transfer_count; buffer += transfer_count;
	}
    
	nRemainSend = res->length;
	buffer = (LPSTR)res->record;
    
	//SEND BODY
    while (nRemainSend > 0 && !disconnect)
    {
		transfer_count = send (socket, buffer, nRemainSend, 0);
		if (transfer_count == SOCKET_ERROR)
        {
            report_error_utf16 (L"server send() failed", 14, TRUE);
        }
		
        disconnect = (transfer_count == 0);
		nRemainSend -=transfer_count; buffer += transfer_count;
	}
	
    return disconnect;
}
