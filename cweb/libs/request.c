//
//  request.c
//  cweb
//
//  Created by Oleh Yashnyi on 04.03.2023.
//

#include "request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** split(char* str, char delim);
void get_header(HTTP_Request* http_req, char* line);

HTTP_Request* parse_req(char* req_raw_data)
{
    HTTP_Request* http_req = (HTTP_Request*) malloc(sizeof(HTTP_Request));
    http_req->headers_count = 0;
    
    // Parse first line of request to get method and path
    sscanf(req_raw_data, "%s %s", http_req->method, http_req->route);
    
    // Parse body if present
    char* body = strstr(req_raw_data, BODY_DELIMITER);
    if (body != NULL)
    {
        strncpy(http_req->body, body + 4, sizeof(http_req->body));
    }
    req_raw_data[strlen(req_raw_data) - strlen(body)] = '\0'; // remove body part from raw request data
    
    // Parse headers
    char* line = strtok(req_raw_data, HEADER_DELIMITER);
    line = strtok(NULL, HEADER_DELIMITER); // skipping first header line
    
    while (line != NULL && http_req->headers_count < MAX_HEADERS)
    {
        get_header(http_req, line);
        
        // get next token (header line)
        line = strtok(NULL, HEADER_DELIMITER);
    }
    
    return http_req;
}

char* get_header_value(HTTP_Request* request, char* key) {
    for (int i = 0; i < request->headers_count; ++i) {
        if (strcmp(request->headers[i].key, key) == 0) {
            return request->headers[i].value;
        }
    }
    return NULL;
}

char** split(char* str, char delim)
{
    int length_before_delim = 0; // header line key string length
    int delim_occur = 0;
    char* splits[2];
    
    for (int i = 0; i < strlen(str); ++i)
    {
        if (str[i] == delim)
        {
            delim_occur++;
            break;
        }
        length_before_delim++;
    }
    
    splits[0] = (char*) malloc(length_before_delim * sizeof(char));
    splits[1] = (char*) malloc(strlen(str) - length_before_delim * sizeof(char));
    
    // (header line key)
    strncpy(splits[0], str, length_before_delim);
    
    // str + 2 in order to skip ': ' char sequesnce (header line value)
    strncpy(splits[1], str + length_before_delim + 2, strlen(str) - length_before_delim);
    
    return splits;
}

void get_header(HTTP_Request* http_req, char* line)
{
    char** res = split(line, ':');
    char* key = res[0];
    char* value = res[1];

    if (key != NULL && value != NULL)
    {
        strncpy(http_req->headers[http_req->headers_count].key, key, MAX_HEADER_KEY_LENGTH);
        strncpy(http_req->headers[http_req->headers_count].value, value, MAX_HEADER_VALUE_LENGTH);
        http_req->headers_count++;
    }
}
