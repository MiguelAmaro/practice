// Chapter 12. clientSK.c										
// Single threaded command line client	WINDOWS SOCKETS VERSION	
// Reads a sequence of commands to sent to a server process 	
// over a socket connection. Wait for the response and display	
// it.								

/* This program illustrates:
	1. Windows sockets from the client side.
	2. Short-lived connections with a single request but multiple responses.
	3. Reading responses in server messages until the server disconnects. 
*/

#include "winsock2.h"
#include "windows.h"

#include "sockets_client_server.h"	// Defines the request and response records.
#include "chapter_02/2_1_report_error.c"

#include <wchar.h>

#include "LAL.h"

static b32 client_send_request    (Request  *req, SOCKET socket);
static b32 client_receive_response(Response *res, SOCKET socket);

struct sockaddr_in client_address;		// Client Socket address structure

u32 socket_based_client(u32 arg_count, u8 *args[])
{
    SOCKET client_socket = INVALID_SOCKET;
    
    Request request;	
    Response response;  
    
    // Exercise: Can you port this code to UNIX?
    // Are there other sysetm dependencies?
    
    WSADATA WSStartData; // Socket library data structure
    b32 quit = 0;
    
    DWORD connection_status;
    
    // Initialize the WS library. Ver 2.0
    if (WSAStartup (MAKEWORD (2, 0), &WSStartData) != 0)
    {
        report_error_utf16 (L"Cannot support sockets", 1, TRUE);
    }
	// Connect to the server
	// Follow the standard client socket/connect sequence
    
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
    
	if (client_socket == INVALID_SOCKET)
    {
		report_error_utf16 (L"Failed client socket() call", 2, TRUE);
    }
    
    
	memset (&client_address, 0, sizeof(client_address));    
	client_address.sin_family = AF_INET;
	
	if (arg_count >= 2)
    {
		client_address.sin_addr.s_addr = inet_addr (args[1]); 
    }
	else
    {
		client_address.sin_addr.s_addr = inet_addr ("127.0.0.1");
    }
    
	client_address.sin_port = htons(SERVER_PORT);
    
	connection_status = connect (client_socket, (struct sockaddr *)&client_address, sizeof(client_address));
	
    if (connection_status == SOCKET_ERROR)
    {
        report_error_utf16(L"Failed client connect() call)", 3, TRUE);
    }
    
	//  Main loop to prompt user, send request, receive response
	while (!quit)
    {
		wprintf(L"%s", L"\nEnter Command: "); 
		fgets (request.record, MAX_REQ_RES_LEN - 1, stdin); 
		
        // Get rid of the new line at the end
		// Messages use 8-bit characters
        
		request.record[strlen(request.record)-1] = '\0';
		
        if (strcmp(request.record, "$Quit") == 0)
        {
            quit = TRUE;
        }
        
		client_send_request (&request, client_socket);
        
		if (!quit)
        {
            client_receive_response (&response, client_socket);
        }
	}
    
	shutdown(client_socket, SD_BOTH); // Disallow sends and receives
    
	closesocket (client_socket);
	WSACleanup();
    
	wprintf(L"\n****Leaving client\n");
	
    return 0;
}


b32 client_send_request (Request *req, SOCKET socket)
{
	/* Send the the request to the server on socket socket */
	b32 disconnect = FALSE;
	LONG32 nRemainSend, nXfer;
	LPBYTE buffer;
    
	/* 
The request is sent in two parts. First the header, then
	   the command string proper.
*/
	
	nRemainSend = REQ_HEADER_LEN; 
	req->length = (DWORD)(strlen (req->record) + 1);
	buffer = (LPBYTE)req;
    
	while (nRemainSend > 0 && !disconnect)
    {
		/* send does not guarantee that the entire message is sent */
		nXfer = send (socket, buffer, nRemainSend, 0);
		
        if (nXfer == SOCKET_ERROR)
        {
            report_error_utf16 (L"client send() failed", 4, TRUE);
        }
		
        disconnect = (nXfer == 0);
		nRemainSend -=nXfer; buffer += nXfer;
	}
    
	nRemainSend = req->length; 
	buffer = (LPBYTE)req->record;
	
    while (nRemainSend > 0 && !disconnect)
    {
		nXfer = send (socket, buffer, nRemainSend, 0);
        
		if (nXfer == SOCKET_ERROR)
        {
            report_error_utf16 (L"client send() failed", 5, TRUE);
        }
        
		disconnect = (nXfer == 0);
		nRemainSend -=nXfer; buffer += nXfer;
	}
	return disconnect;
}


b32 client_receive_response (Response *res, SOCKET socket)
{
	b32 disconnect = FALSE;
    b32 LastRecord = FALSE;
    
    s32 nRemainRecv, nXfer;
    u8 *buffer;
    
	/*
Read the response records - there may be more than one.
		As each is received, write it to std out.
*/
    
	/*
Read each response and send it to std out. 
		First, read the record header, and then
		read the rest of the record.
*/
    
	while (!LastRecord)
    {
		//  Read the header
		nRemainRecv = RES_HEADER_LEN; buffer = (LPBYTE)res;
		
        while (nRemainRecv > 0 && !disconnect)
        {
			nXfer = recv (socket, buffer, nRemainRecv, 0);
			
            if (nXfer == SOCKET_ERROR)
            {
                report_error_utf16 (L"client header recv() failed", 6, TRUE);
            }
            
			disconnect   = (nXfer == 0);
			nRemainRecv -=nXfer; buffer += nXfer;
		}
        
		//	Read the response record
		nRemainRecv = res->length;
        
		// Exclude buffer overflow
		nRemainRecv = min(nRemainRecv, MAX_REQ_RES_LEN);
		LastRecord  = (nRemainRecv <= 1);  // The terminating null is counted
		buffer      = (LPBYTE)res->record;
		
        while (nRemainRecv > 0 && !disconnect)
        {
			nXfer = recv (socket, buffer, nRemainRecv, 0);
			if (nXfer == SOCKET_ERROR)
            {
                report_error_utf16 (L"client response recv() failed", 7, TRUE);
            }
            
			disconnect = (nXfer == 0);
			nRemainRecv -=nXfer; buffer += nXfer;
		}
        
		if (!disconnect)
        {
			wprintf(L"%hs", res->record);
        }
	}
	return disconnect;	
}