#ifndef _LOGGER_H
#define _LOGGER_H
#include <stdio.h>

typedef struct {
    char **logs;
} logger_t;

void loggerLog(int partId, double x, double y, FILE *log);
void loggerSep(int iter, FILE *log);

#endif