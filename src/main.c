#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "pso.h"
#include "logger.h"
#include "utils.h"

int main(int argc, char **argv) {
    srand(time(NULL));

    int maxIterations, numParticles, n, logFrequency;
    double w = 0.7, c1 = 1.5, c2 = 1.5; // algorithm's parameters
    numParticles = argc > 2 ? atoi(argv[2]) : 30; // 30 is by default
    maxIterations = argc > 3 ? atoi(argv[3]) : 100; // 100 is by default
    logFrequency = argc > 5 ? atoi(argv[5]) : 0;

    map_t *map = mapLoad(argv[1]);

    if (!map) {
        fprintf(stderr, "cannot read map file %s\n", argv[1]);
        return 1;
    }


    FILE *fiParams =  fopen(argv[4], "r");
    FILE *log = fopen("log.csv", "w");

    if (!fiParams) {
        printf("Didn't provide algorith's parameters, default ones are used\n");
    } else {
        fscanf(fiParams, "%lf", &w);
        fscanf(fiParams, "%lf", &c1);
        fscanf(fiParams, "%lf", &c2);
        fclose(fiParams);
    }


    pso_params_t params = {w, c1, c2};
    pso_t *pso = psoCreate(numParticles, maxIterations, logFrequency, params);

    if (!pso) {
        fprintf(stderr, "bad alloc at psoCreate, main\n");
        return 1;
    }

    psoRun(pso, map, log);

    printf("Best position found: (%.3f, %.3f) with value %.3f\n", pso->globalBestX, pso->globalBestY, pso->globalBestValue);

    psoFree(pso);
    mapFree(map);

    return 0;
}
