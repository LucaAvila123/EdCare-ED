#include "elder.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "sensor.h"
#include "carer.h"

//o nome do idoso é const para evitar mudanças
//o idoso leva consigo um sensor com seus dados
//cada idoso tem uma lista de amigos e outra de cuidadores
//são determinados um amigo e um cuidador mais perto fisicamente
struct elder {
    const char* name;
    Sensor* sensor;
    List* friendList;
    List* carerList;

    Elder* closerFriend;
    Carer* closerCarer;
};

Elder* ElderInit(const char* name){

    if(!name){
        printf("\n\nERRO: ElderInit -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    Elder* newElder = (Elder*) malloc(sizeof(Elder));
    newElder -> name = strdup(name);
    newElder -> sensor = SensorInit(0.0, 0.0, 36.9, 0); 
    newElder -> friendList = ListInit(NULL);
    newElder -> carerList = ListInit(NULL);

    return newElder;
}

Sensor* ElderGetReadings(Elder* elder){

    if(!elder){
        printf("\n\nERRO: ElderGetReadings -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    return elder -> sensor;
}

Elder* ElderGetFriend(Elder* elder, const char* friendName){


    if(!elder || !friendName){
        printf("\n\nERRO: ElderGetFriend -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }
    //percorre a lista de amigos procurando pelo nome
    Node* friendNode = ListSearchKey(elder -> friendList, friendName);

    if(!friendNode){
        return NULL;
    }

    Elder* friend = (Elder*) NodeGetData(friendNode);

    return friend;
}

Elder* ElderUpdateCloserFriend(Elder* elder){

    if(!elder){
        printf("\n\nERRO: ElderUpdateCloserFriend -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    //ponto de referência de localização para cálculos de distância
    double x0 = SensorReadLatitude(elder->sensor);
    double y0 = SensorReadLongitude(elder->sensor);

    double shorterDistance = -1; //condição inicial para a menor distância usando um valor impossível
    int drawCounter = 0;

    for(Node* currentNode = ListGetHead(elder -> friendList); currentNode != NULL; currentNode = ListGetNextNode(elder -> friendList, currentNode)){
        Elder* currentElder = (Elder*) NodeGetData(currentNode);

        double x = SensorReadLatitude(currentElder->sensor) - x0;
        double y = SensorReadLongitude(currentElder->sensor) - y0;

        //quadrado da distância entre o idoso e seu amigo (a raiz não foi extraída)
        double currentDistance = x*x + y*y; 

        if(shorterDistance == -1 || currentDistance < shorterDistance){
            shorterDistance = currentDistance;
            elder -> closerFriend = currentElder;
            drawCounter = 0;
        }

        else if(currentDistance == shorterDistance){
            drawCounter++;
        }
    }

    //casos de um idoso não ter amigos
    if(shorterDistance == -1){
        elder -> closerFriend = NULL;
    }
    
    return elder -> closerFriend;
}

Carer* ElderUpdateCloserCarer(Elder* elder){

    if(!elder){
        printf("\n\nERRO: ElderUpdateCloserCarer -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }
    
    double x0 = SensorReadLatitude(elder->sensor);
    double y0 = SensorReadLongitude(elder->sensor);

    double shorterDistance = -1;
    int drawCounter = 0; 

    for(Node* currentNode = ListGetHead(elder -> carerList); currentNode != NULL; currentNode = ListGetNextNode(elder -> carerList, currentNode)){
        Carer* currentCarer = (Carer*) NodeGetData(currentNode);

        double x = CarerGetLatitude(currentCarer) - x0;
        double y = CarerGetLongitude(currentCarer) - y0;

        double currentDistance = x*x + y*y;

        if(currentDistance < shorterDistance || shorterDistance == -1){
            shorterDistance = currentDistance;
            elder -> closerCarer = currentCarer;
            drawCounter = 0;
        }

    }

    //para o caso de não haver cuidadores para um idoso (é mais difícil)
    if(shorterDistance == -1){
        elder -> closerCarer = NULL;
    }

    return elder->closerCarer;
}

Elder* ElderGetCloserFriend(Elder* elder){

    if(!elder){
        printf("\n\nERRO: ElderGetCloserFriend -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    return elder -> closerFriend;
}

Carer* ElderGetCloserCarer(Elder* elder){
    
    if(!elder){
        printf("\n\nERRO: ElderGetCloserCarer -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    return elder -> closerCarer;
}

Carer* ElderGetCarer(Elder* elder, const char* carerName){

    if(!elder || !carerName){
        printf("\n\nERRO: ElderGetCarer -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    Node* carerNode = ListSearchKey(elder -> carerList, carerName);
    Carer* carer = (Carer*) NodeGetData(carerNode);

    return carer;
}

void ElderAddFriend(Elder* elder, Elder* friend){

    if(!elder || !friend){
        printf("\n\nERRO: ElderGetCarer -> ponteiro ou argumento invalido\n\n");
        return;
    }

    Node* friendNode = NodeCreate(ElderGetName(friend), friend);
    ListAddNodeTail(elder -> friendList, friendNode);    
}

void ElderAddCarer(Elder* elder, Carer* carer){

    if(!elder || !carer){
        printf("\n\nERRO: ElderGetCarer -> ponteiro ou argumento invalido\n\n");
        return;
    }

    Node* carerNode = NodeCreate(CarerGetName(carer), carer);
    ListAddNodeTail(elder -> carerList, carerNode);
}

//remove um amigo da lista de amigos de um idoso 
Elder* ElderRemoveFriend(Elder* elder, const char* friendName){
    
    Node* friendNode = ListSearchKey(elder -> friendList, friendName);
    
    if(friendNode == NULL) return NULL;

    Elder* friend = (Elder*) NodeGetData(friendNode);
    ListRemoveNode(elder -> friendList, friendNode);
    return friend;
}

//remove um cuidador da lista de um idoso
Carer* ElderRemoveCarer(Elder* elder, const char* carerName){

    if(!elder || !carerName){
        printf("\n\nERRO: ElderRemoveCarer -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    Node* carerNode = ListSearchKey(elder -> carerList, carerName);
    Carer* carer = (Carer*) NodeGetData(carerNode);

    ListRemoveNode(elder -> carerList, carerNode);

    return carer;
}

const char* ElderGetName(Elder* elder){
    
    if(!elder){
        printf("\n\nERRO: ElderGetName -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    return elder -> name;
}
//libera a memória alocada para o idoso
void ElderDelete(void* elder){

    if(!elder){
        return;
    }
    free((void*)((Elder*)elder) -> name);
    SensorDelete(((Elder*)elder) -> sensor);

    //esvazia a lista e depois libera
    ListEmpty(((Elder*)elder) -> friendList);
    ListDelete(((Elder*)elder) -> friendList);

    ListEmpty(((Elder*)elder) -> carerList);
    ListDelete(((Elder*)elder) -> carerList);

    free(elder);
}

//imprime os dados de um idoso na saída do sistema (não em arquivos específicos de saída)
void ElderPrint(Elder* elder){

    if(!elder){
        printf("\n\nERRO: ElderPrint -> ponteiro ou argumento invalido\n\n");
        return;
    }

    printf("Elder: %s\n", elder -> name);
    SensorPrintReadings(elder -> sensor);
    printf("Amigos:\n");

    int i = 0;
    for(Node* currentNode = ListGetHead(elder->friendList); currentNode != NULL; currentNode = ListGetNextNode(elder->friendList, currentNode), i++){

        printf("\t - Amigo (%d): %s\n", i, NodeGetKey(currentNode));
        printf("\n"); 
    }

    if(ListGetHead(elder->friendList) == NULL){
        printf("\n\nLista de amigos vazia!!!\n\n");
    }

    if(ElderGetCloserFriend(elder) != NULL){
        printf("Amigo mais próximo: - %s\n", ElderGetName(ElderGetCloserFriend(elder)));
        printf("\n");
    }

    printf("Cuidadores:\n");

    i = 0;
    for(Node* currentNode = ListGetHead(elder->carerList); currentNode != NULL; currentNode = ListGetNextNode(elder->carerList, currentNode), i++){

        printf("\t - Cuidador (%d): %s\n", i, NodeGetKey(currentNode));
        printf("\n"); 
    }

    if(ListGetHead(elder->carerList) == NULL){
        printf("\n\nLista de cuidadores vazia!!!\n\n");
    }

    if(ElderGetCloserCarer(elder) != NULL){
        printf("Cuidador mais próximo: - %s\n", CarerGetName(ElderGetCloserCarer(elder)));
        printf("\n");
    }

    printf("\n");
}
