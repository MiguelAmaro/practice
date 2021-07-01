
#include "winsock2.h"
#include "windows.h"


#include "LAL.h"

struct sockaddr_in g_server_address;		   // Server's Socket address structure
struct sockaddr_in g_connected_client_address; // Connected socket with client details
WSADATA            g_socket_start_data;	    // Socket library data structure

int main(int arg_count, char *args)
{
    
    //	Initialize the WS library. Ver 2.0
    if (WSAStartup(MAKEWORD(2, 0), &g_socket_start_data) != 0)
    {
        printf("Cannot support sockets");
    }
    
    g_server_socket = socket(PF_INET, SOCK_STREAM, 0);
    
    
    if (g_server_socket == INVALID_SOCKET) 
    {
		printf(L"Failed server socket() call");
    }
    
    g_server_address.sin_family      = AF_INET;	
    g_server_address.sin_addr.s_addr = htonl( INADDR_ANY );    
    g_server_address.sin_port        = htons( SERVER_PORT );	
    
    if (bind (g_server_socket, (struct sockaddr *)&g_server_address, sizeof(g_server_address)) == SOCKET_ERROR)
    {
		printf(L"Failed server bind() call");
    }
    if (listen (g_server_socket, MAX_CLIENTS) != 0) 
    {
		printf(L"Server listen() error");
    }
    
    /// Server loop
    while(g_running)
    {
        
    }
    
    return 0;
}
