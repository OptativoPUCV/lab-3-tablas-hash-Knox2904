#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long hashkey = hash(key , map->capacity) ; 

    while(map->buckets[hashkey] != NULL && map->buckets[hashkey]->key !=  NULL && strcmp(map->buckets[hashkey]->key , key) != 0 ){
        hashkey = (hashkey + 1) % map->capacity ; 
    }

    if(map->buckets[hashkey] == NULL|| map->buckets[hashkey]->key == NULL){
        if(map->buckets[hashkey] == NULL) (map->buckets[hashkey] = malloc(sizeof(Pair))) ; //hola :D
        
        map->buckets[hashkey]->key = key ; 
        map->buckets[hashkey]->value=value ; 
        map->size++;
    }
    else{
        map->buckets[hashkey]->value = value ; 
    }
    map->current = hashkey ; 
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap)) ;
    if (map == NULL) exit(EXIT_FAILURE) ; 
    map->buckets = (Pair**)calloc(capacity , sizeof(Pair*)) ; 
    if(map->buckets == NULL) {
        free(map) ;
        exit(EXIT_FAILURE) ; 
    }
    map->capacity = capacity; 
    map->size = 0 ; 
    map->current = -1 ;

    return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
