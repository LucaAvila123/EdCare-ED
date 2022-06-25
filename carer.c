#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carer.h"

//---------CHECK--------------------//
//TODAS AS FUNCOES JA FORAM TESTADAS E FUNCIONAM PERFEITAMENTE ENTRE SI//

struct carer{
    const char* name;
    double latitude;
    double longitude;
};

Carer* CarerInit(const char* name, double latitude, double longitude){

    if(!name){
        printf("\n\nERRO: CarerInit -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    Carer* newCarer = (Carer*) malloc(sizeof(Carer));

    newCarer -> name = strdup(name);
    newCarer -> latitude = latitude;
    newCarer -> longitude = longitude;

    return newCarer;
}

void CarerDelete(void* carer){

    if(!carer){
        return;
    }

    free((void*)(((Carer*)carer) -> name));
    free(carer);
}

const char* CarerGetName(Carer* carer){

    if(!carer){
        printf("\n\nERRO: CarerGetName -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    return carer -> name;
}

void CarerSetName(Carer* carer, const char* name){

    if(!carer || !name){
        printf("\n\nERRO: CarerSetName -> ponteiro ou argumento invalido\n\n");
        return;
    }

    free((void*)carer -> name);
    carer -> name = strdup(name);
}

double CarerGetLatitude(Carer* carer){
    if(!carer){
        printf("\n\nERRO: CarerGetLatitude -> ponteiro ou argumento invalido, retornou (double)0.0\n\n");
        return 0.0;
    }

    return carer -> latitude;
}

void CarerSetLatitude(Carer* carer, double latitude){

    if(!carer){
        printf("\n\nERRO: CarerSetLatitude -> ponteiro ou argumento invalido\n\n");
        return;
    }

    carer -> latitude = latitude;
}

double CarerGetLongitude(Carer* carer){

    if(!carer){
        printf("\n\nERRO: CarerGetLongitude -> ponteiro ou argumento invalido, retornou (double)0.0\n\n");
        return 0.0;
    }

    return carer -> longitude;
}

void CarerSetLongitude(Carer* carer, double longitude){

    if(!carer){
        printf("\n\nERRO: CarerSetLongitude -> ponteiro ou argumento invalido\n\n");
        return;
    }

    carer -> longitude = longitude;
}

void CarerPrint(Carer* carer){

    if(!carer){
        printf("\n\nERRO: CarerPrint -> ponteiro ou argumento invalido\n\n");
        return;
    }

    printf("Carer: \"%s\" Position: (lat:%.0f, long:%.0f)\n", carer -> name, carer -> latitude, carer -> longitude);
}