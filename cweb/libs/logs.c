//
//  logs.c
//  cweb
//
//  Created by Oleh Yashnyi on 04.03.2023.
//

#include "logs.h"

#include <stdio.h>
#include <stdarg.h>


void info(char* fmt, ...)
{
    char buf[100];

    va_list vl;
    va_start(vl, fmt);

    vsnprintf(buf, sizeof(buf), fmt, vl);

    va_end(vl);

    printf("%s %s\n", PREFIX_INFO, buf);
}

void error(char* fmt, ...)
{
    char buf[100];

    va_list vl;
    va_start(vl, fmt);

    vsnprintf(buf, sizeof(buf), fmt, vl);

    va_end(vl);

    printf("%s %s\n", PREFIX_ERROR, buf); //TODO make use of perror
}
