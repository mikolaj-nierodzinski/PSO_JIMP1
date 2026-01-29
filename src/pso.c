#include "pso.h"
#include "map.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

pso_t *psoCreate(int numParticles, int maxIterations, pso_params_t params, int logFrequency) {
    pso_t *pso = malloc(sizeof(pso_t));
    if (!pso) {
        fprintf(stderr, "bad alloc at pso, psoCreate\n");
        exit(EXIT_FAILURE);
    }

    pso->numParticles = numParticles;
    pso->maxIterations = maxIterations;
    pso->params = params;
    pso->logFrequency = logFrequency;
    pso->globalBestX = 0.0;
    pso->globalBestY = 0.0;
    pso->globalBestValue = -1e9;

    pso->particles = malloc(numParticles * sizeof(particle_t));
    if (!pso->particles) {
        fprintf(stderr, "bad alloc at particles, psoCreate\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numParticles; i++) {
        particle_t *p = &pso->particles[i];
        
        p->x = 0.0;
        p->y = 0.0;
        p->vx = 0;
        p->vy = 0;
        p->bestX = 0.0;
        p->bestY = 0.0;
        p->bestValue = -1e9;
    }

    return pso;
}

void psoFree(pso_t *pso) {
    free(pso->particles);
    free(pso);
}

void psoRun(pso_t *pso, const map_t *map, FILE *Log) {
    for (int i = 0; i < pso->numParticles; i++) {
        particle_t *p = &pso->particles[i];

        p->x = (double)rand() / RAND_MAX * map->width;
        p->y = (double)rand() / RAND_MAX * map->height;

        p->vx = ((double)rand() / RAND_MAX - 0.5) * 0.5; // [-0.25, 0.25]
        p->vy = ((double)rand() / RAND_MAX - 0.5) * 0.5;

        p->bestX = p->x;
        p->bestY = p->y;
        p->bestValue = mapGetValue(map, (int)p->y, (int)p->x);

        if (p->bestValue > pso->globalBestValue) {
            pso->globalBestValue = p->bestValue;
            pso->globalBestX = p->bestX;
            pso->globalBestY = p->bestY;
        }
    }


    for (int iter = 0; iter < pso->maxIterations; iter++) {
        for (int i = 0; i < pso->numParticles; i++) {
            particle_t *p = &pso->particles[i];
            pso_params_t params = pso->params;

            // update velocity
            p->vx = params.w * p->vx + params.c1 * params.r1 * (p->bestX - p->x) + params.c2 * params.r2 * (pso->globalBestX - p->x);
            p->vy = params.w * p->vy + params.c1 * params.r1 * (p->bestY - p->y) + params.c2 * params.r2 * (pso->globalBestY - p->y);

            //update position
            p->x += p->vx;
            p->y += p->vy;

            if (p->x < 0) p->x = 0;
            if (p->y < 0) p->y = 0;
            if (p->x >= (double) map->height)  p->x = (double) map->height - 1e-6;
            if (p->y >= (double) map->width) p->y = (double) map->width - 1e-6;


            int row = (int)round(p->x);
            int col = (int)round(p->y);
            if (row < 0) row = 0;
            if (row >= map->height) row = map->height - 1;
            if (col < 0) col = 0;
            if (col >= map->width) col = map->width - 1;
            
            // evaluate fitness
            double fitness = mapGetValue(map, row, col);

            // update personal best
            if (fitness > p->bestValue) {
                p->bestValue = fitness;
                p->bestX = p->x;
                p->bestY = p->y;
            }

            if (pso->logFrequency != 0 && (iter + 1) % pso->logFrequency == 0) {
                loggerLog(i, p->x, p->y, Log);
            }
        }

        // update global best
        for (int i = 0; i < pso->numParticles; i++) {
            particle_t *p = &pso->particles[i];

            if (p->bestValue > pso->globalBestValue) {
                pso->globalBestValue = p->bestValue;
                pso->globalBestX = p->bestX;
                pso->globalBestY = p->bestY;
            }
        }
    }
}
