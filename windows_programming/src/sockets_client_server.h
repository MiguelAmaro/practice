/* date = June 13th 2021 1:39 pm */

#ifndef SOCKETS_CLIENT_SERVER_H
#define SOCKETS_CLIENT_SERVER_H

#include "LAL.h"

#define SERVER_PORT 50000 // Well known port.

#define MAX_REQ_RES_LEN 0x1000
#define MAX_MESSAGE_LEN MAX_REQ_RES_LEN


#define REQ_SIZE sizeof (Request)
#define REQ_HEADER_LEN  (REQ_SIZE - MAX_REQ_RES_LEN)
#define RES_SIZE sizeof (Response)
#define RES_HEADER_LEN  (RES_SIZE - MAX_REQ_RES_LEN)

#define MAX_CLIENTS    (4)   // //**10 // Maximum number of clients for serverNP
#define MAX_SERVER_TH  (4)   // Maximum number of server threads for serverNPCP
#define MAX_CLIENTS_CP (128) // Maximum number of clients for serverNPCP

#define CS_TIMEOUT 5000

// Same as a message; only the length field has a different name
// Generic message.
typedef struct
{	
	u32 length; // Total length of request, not including this field
    u8  record [MAX_REQ_RES_LEN];
} Message;

typedef struct
{	
	u32 length;	// Total length of request, not including this field
    u8  record [MAX_REQ_RES_LEN];
} Request;

// Same as a message; only the length field has a different name
typedef struct
{
	u32 length;	// Total length of response, not including this field
    u8  record [MAX_REQ_RES_LEN];
} Response;



#endif //SOCKETS_CLIENT_SERVER_H
