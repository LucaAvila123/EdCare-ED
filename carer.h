#ifndef CARER_H
#define CARER_H

typedef struct carer Carer;

/*-----------CarerInit----------------
*Cria uma instancia de um cuidador, com todos os atributos e nome determinados
*-------------------------------------------
*  - inputs: nome e posicao(latutude e longitude) 
*  
*  - output: ponteiro para o cuidador alocado e com nome e valores determinados
*
*  - pre-condicao: nenhuma
*
*  - pos-condicao: cuidador alocado*/
Carer* CarerInit(const char* name, double latitude, double longitude);

/*----------- CarerDelete----------------
*Libera o cuidador da memoria
*-------------------------------------------
*  - inputs: ponteiro para o cuidador
*  
*  - output: nenhum
*
*  - pre-condicao: cuidador alocado
*
*  - pos-condicao: cuidador liberado*/
void CarerDelete(void* carer);

/*----------- CarerGetName----------------
*Retorna um ponteiro para o nome do cuidador
*-------------------------------------------
*  - inputs: ponteiro para o cuidador
*  
*  - output: ponteiro para o nome do cuidador
*
*  - pre-condicao: cuidador alocado
*
*  - pos-condicao: conteudo do ponteiro retornado nao pode ser alterado*/
const char* CarerGetName(Carer* carer);

/*-----------CarerSetName----------------
* Modifica o nome do cuidador
*-------------------------------------------
*  - inputs: ponteiro para o cuidador e nome para alterar
*  
*  - output: nenhum
*
*  - pre-condicao: cuidador alocado e ponteiro para nome valido
*
*  - pos-condicao: nome do cuidador alterado*/
void CarerSetName(Carer* carer, const char* name);

/*-----------CarerGetLatitude----------------
* Retorna o valor de latitude do cuidador
*-------------------------------------------
*  - inputs: ponteiro para o cuidador
*  
*  - output: valor de latitude do cuidador
*
*  - pre-condicao: cuidador alocado
*
*  - pos-condicao: nenhuma*/
double CarerGetLatitude(Carer* carer);

/*-----------CarerSetLatitude----------------
* Modifica o valor de latitude do cuidador
*-------------------------------------------
*  - inputs: ponteiro para o cuidador e valor de latitude
*  
*  - output: nenhum
*
*  - pre-condicao: cuidador alocado
*
*  - pos-condicao: valor de latitude do cuidador alterado*/
void CarerSetLatitude(Carer* carer, double latitude);

/*-----------CarerGetLongitude----------------
* Retorna o valor de longitude do cuidador
*-------------------------------------------
*  - inputs: ponteiro para o cuidador
*  
*  - output: valor de longitude do cuidador
*
*  - pre-condicao: cuidador alocado
*
*  - pos-condicao: nenhuma*/
double CarerGetLongitude(Carer* carer);

/*-----------CarerSetLongitude----------------
* Modifica o valor de longitude do cuidador
*-------------------------------------------
*  - inputs: ponteiro para o cuidador e valor de longitude
*  
*  - output: nenhum
*
*  - pre-condicao: cuidador alocado
*
*  - pos-condicao: valor de longitude do cuidador alterado*/
void CarerSetLongitude(Carer* carer, double longitude);

/*-----------CarerPrint----------------
* imprime os atributos do cuidador na saida padrao
*-------------------------------------------
*  - inputs: ponteiro para o cuidador
*  
*  - output: nenhum
*
*  - pre-condicao: cuidador alocado
*
*  - pos-condicao: nenhuma*/
void CarerPrint(Carer* carer);

#endif /*CARER_H*/