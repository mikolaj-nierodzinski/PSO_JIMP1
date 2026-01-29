#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "map.h"
#include "pso.h"
#include "logger.h"
#include "utils.h"

int main(int argc, char **argv) {
    srand(time(NULL));

    // default values
    int maxIterations = 100;
    int numParticles = 30, n;
    int logFrequency = 0;
    char *paramsFile = NULL;
    char *mapFile = argv[1];

    // parse flags 
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc ) {
            numParticles = atoi(argv[++i]);
        } else if(strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            maxIterations = atoi(argv[++i]);
        } else if(strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            paramsFile = argv[++i];
        } else if(strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            logFrequency = atoi(argv[++i]);
        }
    }

    double w = 0.7, c1 = 1.5, c2 = 1.5; // algorithm's default parameters

    map_t *map = mapLoad(mapFile);

    if (!map) {
        fprintf(stderr, "cannot read map file %s\n", argv[1]);
        return 1;
    }


    // read parameters from file
    FILE *fiParams =  fopen(paramsFile, "r");

    if (!fiParams) {
        printf("Didn't provide algorith's parameters, default ones are used\n");
    } else {
        fscanf(fiParams, "%lf%lf%lf", &w, &c1, &c2);
        fclose(fiParams);
        printf("using parameters: w = %lf, c1 = %lf, c2 = %lf\n", w, c1, c2);
    }


    // Initialize the pso 
    pso_params_t params = {w, c1, c2};
    pso_t *pso = psoCreate(numParticles, maxIterations, params, logFrequency);

    if (!pso) {
        fprintf(stderr, "bad alloc at psoCreate, main\n");
        return 1;
    }

    FILE *log = fopen("log.txt", "w");
    if (!log) return 1;

    psoRun(pso, map, log);

    printf("Best position found: (%.3f, %.3f) with value %.3f\n", pso->globalBestX, pso->globalBestY, pso->globalBestValue);

    psoFree(pso);
    mapFree(map);

    return 0;
}