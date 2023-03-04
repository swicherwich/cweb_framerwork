//
//  routes.c
//  cweb
//
//  Created by Oleh Yashnyi on 04.03.2023.
//

#include "routes.h"
#include "logs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


unsigned int hashed_index(char* key);
void add_handler(HTTP_Router* http_router, char* method, char* route, Controller controller);

HTTP_Router* init(void)
{
    HTTP_Router* router = (HTTP_Router*) malloc(sizeof(HTTP_Router));
    router->add_handler = add_handler;
    return router;
}

void add_handler(HTTP_Router* http_router, char* method, char* route, Controller controller)
{
    unsigned int index = hashed_index(method);
    Request_Handler* req_handler = http_router->handlers[index];
    
    if (req_handler == NULL)
    {
        req_handler = (Request_Handler*) malloc(sizeof(Request_Handler));
        req_handler->key_route = malloc(strlen(route));
        req_handler->key_route = route;
        req_handler->controller = controller;
        req_handler->next = NULL;
        
        http_router->handlers[index] = req_handler;
    }
    else
    {
        Request_Handler* curr = req_handler;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = (Request_Handler*) malloc(sizeof(Request_Handler));
        curr->next->key_route = malloc(strlen(route));
        curr->next->key_route = route;
        curr->next->controller = controller;
    }
}

//TODO add route does not exists exception handler
char* call_handler(HTTP_Router* http_router, HTTP_Request* req)
{
    unsigned int index = hashed_index(req->method);
    Request_Handler* req_handler = http_router->handlers[index];
    
    if (req_handler == NULL)
    {
        error("HTTP method is not implemented: %s", req->method);
        return NULL;
    }
    
    if (req_handler->key_route == NULL)

    while (req_handler != NULL)
    {
        if (strncmp(req->route, req_handler->key_route, strlen(req_handler->key_route)) == 0)
        {
            break;
        }
        req_handler = req_handler->next;
    }
    
    return req_handler->controller(req);
    
}

unsigned int hashed_index(char* key)
{
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash = hash * 33 + key[i];
    }
    return hash % HTTP_METHODS_COUNT;
}
