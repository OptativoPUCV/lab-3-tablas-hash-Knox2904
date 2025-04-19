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
    long auxCapacidad = map->capacity ;
    Pair** auxBuckets = map->buckets ; 

    map->capacity *=2 ; 
    map->buckets = (Pair**)calloc(map->capacity , sizeof(Pair*)) ; 
    map->size = 0 ;

    for(long i = 0 ;i< auxCapacidad ;i++){
        if(auxBuckets[i] != NULL && auxBuckets[i]->key != NULL){
            insertMap(map , auxBuckets[i]->key  ,auxBuckets[i]->value) ; 
        }
    }
    free(auxBuckets) ; 

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
    long hashkey = hash(key , map->capacity) ; 
    long inicio = hashkey ; 
    while(map->buckets[hashkey] != NULL){

        if(map->buckets[hashkey]->key != NULL && strcmp(map->buckets[hashkey]->key, key) == 0){
            map->buckets[hashkey]->key = NULL ; 
            map->size-- ; 
            return;
        }

        hashkey = (hashkey + 1) % map->capacity;

        if(hashkey == inicio) break; 
    }
}

Pair * searchMap(HashMap * map,  char * key) {   
    long hashkey = hash(key , map->capacity) ; 
    long inicio = hashkey ; 
    while(map->buckets[hashkey] != NULL){

        if(map->buckets[hashkey]->key != NULL && strcmp(map->buckets[hashkey]->key, key) == 0){
            map->current = hashkey ;
            return map->buckets[hashkey] ; 
        }

        hashkey = (hashkey + 1) % map->capacity;

        if(hashkey == inicio) break; //nose si alguien revise esto pero le recomiendo lonely as a stranger de galneryus 
    }
        
    return NULL;
}

Pair * firstMap(HashMap * map)  {   
    for(long i = 0 ; i < map->capacity ;i++){
        if(map->buckets[i] != NULL && map->buckets[i]->key != NULL){
            map->current = i ;
            return map->buckets[i] ; 
        }
    }

    return NULL;
}

Pair * nextMap(HashMap * map) {   
    for(long i = map->current + 1  ; i < map->capacity ;i++){
        if(map->buckets[i] != NULL && map->buckets[i]->key != NULL){
            map->current = i ;
            return map->buckets[i] ; 
        }
    }

    return NULL;
}
