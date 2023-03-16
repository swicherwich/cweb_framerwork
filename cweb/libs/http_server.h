//
//  http_server.h
//  cweb
//
//  Created by Oleh Yashnyi on 04.03.2023.
//

#ifndef http_server_h
#define http_server_h

#include "routes.h"

#include <stdio.h>

typedef struct _HTTP_Server HTTP_Server;

typedef unsigned int u_int;

struct _HTTP_Server {
    u_int socket;
    u_int port;    HTTP_Router* http_router;
};

void init_http_server(HTTP_Server* server, u_int port);
void bind_route(HTTP_Server* server, char* method, char* route, Controller controller);
void start_server(HTTP_Server* server, u_int backlog);

#endif /* http_server_h */
