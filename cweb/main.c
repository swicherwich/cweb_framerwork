//
//  main.c
//  cweb
//
//  Created by Oleh Yashnyi on 04.03.2023.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "http_server.h"
#include "request.h"

char* say_hello(HTTP_Request* req)
{
    return "HTTP/1.0 200 OK\r\nContent-Type: application/json\r\nContent-Length: 23\r\n\r\n{\"TestHello\":\"Success\"}\r\n";
}

char* say_bye(HTTP_Request* req)
{
    return "HTTP/1.0 200 OK\r\nContent-Type: application/json\r\nContent-Length: 23\r\n\r\n{\"TestBye\":\"Success\"}\r\n";
}

char* fav_ico(HTTP_Request* req)
{
    return "HTTP/1.0 200 OK\r\nContent-Type: application/json\r\nContent-Length: 23\r\n\r\n{\"TestBye\":\"Success\"}\r\n";
}


int main(int argc, const char* argv[]) {
    HTTP_Server* server = (HTTP_Server*) malloc(sizeof(HTTP_Server));
    init_http_server(server, 8080);
    
    bind_route(server, "GET", "/hello", say_hello);
    bind_route(server, "GET", "/bye", say_hello);
    
    start_server(server, 5);
    
    return 0;
}
