#ifndef _MAP_H
#define _MAP_H

typedef struct {
    int width, height; // W and H
    double **signal;
} map_t;

map_t *mapLoad(const char *fileName);
void mapFree(map_t *map);
double mapGetValue(const map_t *map, int row, int col);

#endif
