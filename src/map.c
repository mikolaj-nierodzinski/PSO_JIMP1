#include <stdio.h>
#include <stdlib.h>
#include "map.h"

map* map_init(int h, int w){
	map *map1=malloc(sizeof(map));
	if(map1==NULL)return NULL;
	map1->h = h;
	map1->w = w;
	map1->data = malloc(h*sizeof(double*));

	for(int i=0;i<h;i++){
		map1->data[i]=malloc(w*sizeof(double));
	}
	return map1;
}

void map_free(map *map1){
    	for(int i=0;i<map1->h;i++){
		free(map1->data[i]);
	}
	free(map1->data);
	free(map1);
}

map* readfile(char *fname){
	FILE *in = fopen(fname, "r");
	if(in == NULL)return NULL;
	int h,w;
	double x;
	if(fscanf(in, "%d", &h)!=1)return NULL;
	if(fscanf(in, "%d", &w)!=1)return NULL;
	map *map1 = map_init(h,w);
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(fscanf(in, "%lf", &x)!=1)return NULL;
			map1->data[i][j]=x;
		}
	}
	return map1;
}

