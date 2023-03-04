//
//  http_server.c
//  cweb
//
//  Created by Oleh Yashnyi on 04.03.2023.
//

#include "http_server.h"
#include "routes.h"
#include "logs.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>


void start_server(HTTP_Server* server, u_int backlog);

void init_http_server(HTTP_Server* server, u_int port)
{
    int srv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (srv_socket < 0)
    {
        error("Error creating server socket! Shutdown.");
        exit(1);
    }
    info("Socket created.");

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    server->port = port;
    server->socket = srv_socket;
    server->start_server = start_server;
    server->http_router = init();

    if (bind(srv_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
    {
        error("Could not bind socket");
        exit(1);
    }
    info("Socket binded.");
    
}

void bind_route(HTTP_Server* server, char* method, char* route, Controller controller)
{
    server->http_router->add_handler(server->http_router, method, route, controller);
    info("Route %s for %s configured.", route, method);
}

void bind_404_route(HTTP_Server* server, char* method, Controller controller)
{
    server->http_router->add_handler(server->http_router, method, NULL, controller);
    info("Route 404 for %s configured.", route, method);
}

void start_server(HTTP_Server* server, u_int backlog)
{
    if (listen(server->socket, backlog) < 0)
    {
        error("Server start failed.");
        error("Shutdown.");
        exit(1);
    }
    
    info("Server started.");
    info("Listenning for connections on port: %d", server->port);
    
    while (1)
    {
        int client_socket = accept(server->socket, NULL, NULL);
        
        char buff[1024];
        recv(client_socket, buff, 1024, 0);
        
        HTTP_Request* http_req = parse_req(buff);
        
        send(client_socket, call_handler(server->http_router, http_req), 128, 0);
        
    }
}
