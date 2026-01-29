#include <stdlib.h>
#include <stdio.h>
#include "map.h"

#define INF 1000.0

map_t *mapLoad(const char *fileName) {
    FILE *fi = fopen(fileName, "r");
    if (!fi) {
        fprintf(stderr, "can not open file %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    int W, H;
    if(fscanf(fi, "%d%d", &W, &H)!=2){
	    fprintf(stderr, "map height or width not type int\n");
	    return NULL;
    }

    map_t *Map = malloc(sizeof(map_t));
    if (!Map) {
        fprintf(stderr, "bad alloc at Map, initMap\n");
        exit(EXIT_FAILURE);
    }
    
    Map->width = W, Map->height = H;

    Map->signal = malloc(H * sizeof(double*));
    if (!Map->signal) {
        fprintf(stderr, "bad alloc at signal, initMap\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < H; i++) {
        Map->signal[i] = malloc(W * sizeof(double));

        if (!Map->signal[i]) {
            fprintf(stderr, "bad alloc at signal[%d], initMap", i);
            // có cần phải thu dọn hết free hết mỗi lần malloc lỗi không nhỉ
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < W; j++) {
            if(fscanf(fi, "%lf", &Map->signal[i][j])!=1){
		    fprintf(stderr, "map data not type double\n");
		    return NULL;
	    }
            // Map->signal[i][j] = rand();
        }
    }

    fclose(fi);

    return Map;
}

void mapFree(map_t *map) {
    int W = map->width, H = map->height;

    for (int i = 0; i < H; i++) {
        free(map->signal[i]);
    }

    free(map->signal);
    free(map);
}

double mapGetValue(const map_t *map, int row, int col) {
    if (row < 0 || row >= map->height || col < 0 || col >= map->width) {
        return -INF;
    }
    
    return map->signal[row][col];
}