#ifndef _PSO_H
#define _PSO_H
#include "map.h"
#include <stdio.h>

typedef struct {
    double x, y; // current cordinate
    double vx, vy; // velocity
    double bestX, bestY; // pBest position
    double bestValue; // pBest fitness
} particle_t;

typedef struct {
    double w, c1, r1, c2, r2; // w: inertia, c1: cognitive, c2: social
} pso_params_t;

typedef struct {
    int numParticles, maxIterations, logFrequency;

    int logFrequency;//how often particle positions logged

    particle_t *particles;

    double globalBestX, globalBestY, globalBestValue;

    pso_params_t params;
} pso_t;

pso_t *psoCreate(int numParticles, int maxIteration, pso_params_t params, int logFrequency);
void psoFree(pso_t *pso);

void psoRun(pso_t *pso, const map_t *map, FILE *log);

#endif
