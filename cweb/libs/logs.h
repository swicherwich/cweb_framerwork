//
//  logs.h
//  cweb
//
//  Created by Oleh Yashnyi on 04.03.2023.
//

#ifndef logs_h
#define logs_h

#define PREFIX_INFO "[INFO]"
#define PREFIX_ERROR "[ERROR]"

void info(char* fmt, ...);
void error(char* fmt, ...);

#endif /* logs_h */
