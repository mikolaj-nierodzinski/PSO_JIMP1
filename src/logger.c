#include <stdio.h>
#include <stdlib.h>
#include "logger.h"

void loggerLog(int partId, double x, double y, FILE *Log) {
    fprintf(Log, "Particle no.; %d; ", partId);
    fprintf(Log, " %g; %g;\n", x, y);
}

void loggerSep(int iter, FILE *Log){
	fprintf(Log, "iteration no.; %d; x coordinate; y coordinate; \n", iter);
}

