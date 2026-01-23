#include <stdio.h>
#include <stdlib.h>

#ifndef MAP_H
#define MAP_H

typedef struct m{
	int h;
	int w;
	double **data;
}map;

map* map_init(int h, int w);
void map_free(map *map1);
map* readfile(char *fname);

#endif
