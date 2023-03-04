//
//  routes.h
//  cweb
//
//  Created by Oleh Yashnyi on 04.03.2023.
//

#ifndef routes_h
#define routes_h

#include "request.h"

#define HTTP_METHODS_COUNT 39

typedef struct HTTP_Router HTTP_Router;
typedef struct Request_Handler Request_Handler;

typedef char* (*Controller)(HTTP_Request*);
typedef void (*Add_Handler)(HTTP_Router* http_router, char* method, char* route, Controller controller);

struct Request_Handler {
    char* key_route;
    Controller controller;
    struct Request_Handler* next;
};

struct HTTP_Router {
    Add_Handler add_handler;
    Request_Handler* handlers[39];
};

HTTP_Router* init(void);
//void add_handler(HTTP_Router* http_router, char* method, char* route, Controller controller);
char* call_handler(HTTP_Router* http_router, HTTP_Request* req);

#endif /* routes_h */
