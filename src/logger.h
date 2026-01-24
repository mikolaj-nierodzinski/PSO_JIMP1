#ifndef _LOGGER_H
#define _LOGGER_H

typedef struct {
    char **logs;
} logger_t;

void loggerLog(int idx);

#endif