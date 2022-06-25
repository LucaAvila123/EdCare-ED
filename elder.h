#ifndef ELDER_H
#define ELDER_H
#include "sensor.h"
#include "carer.h"

typedef struct elder Elder;


/*-----------CarerInit----------------
* Cria uma instancia de um idoso, com todos os atributos e nome determinados
*-------------------------------------------
*  - inputs: nome do idoso 
*  
*  - output: ponteiro para o idoso alocado e com nome e valores determinados
*
*  - pre-condicao: nenhuma
*
*  - pos-condicao: idoso alocado*/
Elder* ElderInit(const char* name);

/*-----------ElderGetReadings----------------
* Retorna o ponteiro para o sensor do idoso
*-------------------------------------------
*  - inputs: ponteiro para o idoso 
*  
*  - output: ponteiro para o sensor do idoso
*
*  - pre-condicao: idoso alocado
*
*  - pos-condicao: sensor retornado pertence ao idoso*/
Sensor* ElderGetReadings(Elder* elder);

/*-----------ElderGetReadings----------------
* Retorna o ponteiro para um amigo do idoso
*-------------------------------------------
*  - inputs: ponteiro para o idoso e nome do amigo
*  
*  - output: ponteiro para o amigo determinado ou NULL caso nao exista
*
*  - pre-condicao: idoso alocado
*
*  - pos-condicao: idoso retornado e amigo do idoso*/
Elder* ElderGetFriend(Elder* elder, const char* friendName);

/*-----------ElderGetCarer----------------
* Retorna o ponteiro para um cuidador do idoso
*-------------------------------------------
*  - inputs: ponteiro para o idoso e nome do cuidador
*  
*  - output: ponteiro para o cuidador determinado ou NULL caso nao exista
*
*  - pre-condicao: idoso alocado
*
*  - pos-condicao: cuidador retornado e cuidador do idoso*/
Carer* ElderGetCarer(Elder* elder, const char* carerName);

/*-----------ElderAddFriend----------------
* Adiciona um amigo na lista de amigos do idoso
*-------------------------------------------
*  - inputs: ponteiro para o idoso e ponteiro para o amigo
*  
*  - output: nenum;
*
*  - pre-condicao: idoso alocado e amigo alocado
*
*  - pos-condicao: amigo determinado e amigo do idoso*/
void ElderAddFriend(Elder* elder, Elder* friend);

/*----------- ElderUpdateCloserFriend----------------
* Encontra o amigo mais proximo do idoso
*-------------------------------------------
*  - inputs: ponteiro para o idoso
*  
*  - output: ponteiro para o amigo mais proximo do idoso;
*
*  - pre-condicao: idoso alocado
*
*  - pos-condicao: amigo mais proximo determinado*/
Elder* ElderUpdateCloserFriend(Elder* elder);

/*-----------ElderGetCloserFriend----------------
* Retorna o amigo mais proximo do idoso
*-------------------------------------------
*  - inputs: ponteiro para o idoso
*  
*  - output: ponteiro para o amigo mais proximo do idoso;
*
*  - pre-condicao: idoso alocado
*
*  - pos-condicao: amigo mais proximo alocado*/
Elder* ElderGetCloserFriend(Elder* elder);

/*-----------ElderUpdateCloserCarer----------------
* Encontra o cuidador mais proximo do idoso
*-------------------------------------------
*  - inputs: ponteiro para o idoso
*  
*  - output: ponteiro para o cuidador mais proximo do idoso;
*
*  - pre-condicao: idoso alocado
*
*  - pos-condicao: cuidador mais proximo determinado*/
Carer* ElderUpdateCloserCarer(Elder* elder);

/*-----------ElderGetCloserCarer----------------
* Retorna o cuidador mais proximo do idoso
*-------------------------------------------
*  - inputs: ponteiro para o idoso
*  
*  - output: ponteiro para o cuidador mais proximo do idoso;
*
*  - pre-condicao: idoso alocado
*
*  - pos-condicao: cuidador mais proximo alocado*/
Carer* ElderGetCloserCarer(Elder* elder);

/*-----------ElderAddCarer----------------
* Adiciona um cuidador na lista de amigos do idoso
*-------------------------------------------
*  - inputs: ponteiro para o idoso e ponteiro para o cuidador
*  
*  - output: nenum;
*
*  - pre-condicao: idoso alocado e cuidador alocado
*
*  - pos-condicao: cuidador determinado e cuidador do idoso*/
void ElderAddCarer(Elder* elder, Carer* carer);

/*-----------ElderRemoveFriend----------------
* Retira uma amigo da lista de amigos do idoso
*-------------------------------------------
*  - inputs: ponteiro para o idoso e nome do amigo a retirar
*  
*  - output: ponteiro para o amigo retirado ou NULL caso nao exista;
*
*  - pre-condicao: idoso alocado e nome do amigo valido
*
*  - pos-condicao: amigo removido da lista do idoso*/
Elder* ElderRemoveFriend(Elder* elder, const char* friendName);

/*-----------ElderRemoveCarer----------------
* Retira uma cuidador da lista de cuidadores do idoso
*-------------------------------------------
*  - inputs: ponteiro para o idoso e nome do cuidador a retirar
*  
*  - output: ponteiro para o cuidador retirado ou NULL caso nao exista;
*
*  - pre-condicao: idoso alocado e nome do cuidador valido
*
*  - pos-condicao: cuidador removido da lista do idoso*/
Carer* ElderRemoveCarer(Elder* elder, const char* carerName);

/*-----------ElderGetName----------------
* Retorna o nome do idoso
*-------------------------------------------
*  - inputs: ponteiro para o idoso
*  
*  - output: ponteiro para o nome do idoso;
*
*  - pre-condicao: idoso alocado
*
*  - pos-condicao: valor do ponteiro retornado nao pode ser alterado*/
const char* ElderGetName(Elder* elder);

/*----------- ElderDelete----------------
* Libera o idoso da memoria
*-------------------------------------------
*  - inputs: ponteiro para o idoso
*  
*  - output: nenhum
*
*  - pre-condicao: idoso alocado
*
*  - pos-condicao: idoso liberado*/
void ElderDelete(void* elder);

/*-----------ElderPrint----------------
* imprime os atributos do idoso na saida padrao
*-------------------------------------------
*  - inputs: ponteiro para o idoso
*  
*  - output: nenhum
*
*  - pre-condicao: idoso alocado
*
*  - pos-condicao: nenhuma*/
void ElderPrint(Elder* elder);

#endif /*ELDER_H*/