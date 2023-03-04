//
//  request.h
//  cweb
//
//  Created by Oleh Yashnyi on 04.03.2023.
//

#ifndef request_h
#define request_h

#define MAX_HEADERS 50
#define MAX_HEADER_KEY_LENGTH 50
#define MAX_HEADER_VALUE_LENGTH 500

#define HEADER_DELIMITER "\r\n"
#define BODY_DELIMITER "\r\n\r\n"

typedef struct {
    char key[MAX_HEADER_KEY_LENGTH];
    char value[MAX_HEADER_VALUE_LENGTH];
} Request_Header;

typedef struct {
    char method[8];
    char route[32];
    Request_Header headers[MAX_HEADERS];
    int headers_count;
    char body[2048];
} HTTP_Request;

HTTP_Request* parse_req(char* req_raw_data);
char* get_header_value(HTTP_Request* request, char* key);

#endif /* request_h */
