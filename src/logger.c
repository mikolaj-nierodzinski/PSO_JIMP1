#include <stdio.h>
#include <stdlib.h>
#include "logger.h"

void loggerLog(int partId, double x, double y, FILE *log) {
    fprintf(log, "Particle no.; %d; ", partId);
    fprintf(log, " %g; %g;\n", x, y);
}

void loggerSep(int iter, FILE *log){
	fprintf(log, "iteration no.; %d; x coordinate; y coordinate; \n", iter);
}