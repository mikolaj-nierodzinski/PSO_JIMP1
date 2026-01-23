#include <stdio.h>
#include <stdlib.h>
#include "map.h"

map* map_init(int h, int w){
	map *map1=malloc(sizeof(map));
	if(map1==NULL)return NULL;
	map1->h = h;
	map1->w = w;
	map1->data = malloc(h*sizeof(float*));

	for(int i=0;i<h;i++){
		map1->data[i]=malloc(w*sizeof(float));
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

