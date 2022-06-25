#ifndef LIST_H
#define LIST_H


typedef struct node Node;
typedef struct list List;

/*-----------ListInit----------------
* Cria uma instancia de uma lista vazia
*-------------------------------------------
*  - inputs: ponteiro para a funcao de liberacao de memoria do TAD usado na lista
*  
*  - output: ponteiro para a lista alocado
*
*  - pre-condicao: nenhuma
*
*  - pos-condicao: lista alocada e vazia*/
List* ListInit(void (*DeleteFunction) (void* data));

/*-----------NodeCreate----------------
* Cria uma celula que pode ser inserida em uma lista
*-------------------------------------------
*  - inputs: string chave da celula e ponteiro para o TAD usado na celula
*  
*  - output: ponteiro para uma celula alocada e com dados atribuidos
*
*  - pre-condicao: string chave valida
*
*  - pos-condicao: celula alocada e inicializada*/
Node* NodeCreate(const char* key, void* data);

/*-----------NodeDelete----------------
* Libera da memoria uma celula previamente alocada
*-------------------------------------------
*  - inputs: ponteiro para a celula a ser liberada
*  
*  - output: nenhum
*
*  - pre-condicao: celula alocada
*
*  - pos-condicao: celula liberada da memoria e dados da celula ainda alocados*/
void NodeDelete(Node* node);

/*-------------NodeGetKey--------------
* Retorna a string chave de uma celula
*-------------------------------------------
*  - inputs: ponteiro para a celula
*  
*  - output: ponteiro para a string chave da celula
*
*  - pre-condicao: celula alocada
*
*  - pos-condicao: conteudos do ponteiro retornado nao podem ser alterados*/
const char* NodeGetKey(Node* node);

/*-------------NodeGetData--------------
* Retorna o ponteiro para o TAD contido dentro da celula
*-------------------------------------------
*  - inputs: ponteiro para a celula
*  
*  - output: ponteiro para o tad inserido na celula
*
*  - pre-condicao: celula alocada e tipo de dado contido na celula conhecido
*
*  - pos-condicao: ponteiro generico de retorno aponta para o TAD contido na celula*/
void* NodeGetData(Node* node);

/*-------------ListGetNextNode--------------
* Retorna a proxima celula de uma celula ja conhecida dentro de uma lista
*-------------------------------------------
*  - inputs: ponteiro para a lista e ponteiro para a celula
*  
*  - output: ponteiro para a proxima celula ou NULL para o fim da lista
*
*  - pre-condicao: lista e celula alocados e celula esta contida na lista
*
*  - pos-condicao: ponteiro de retorno aponta para a proxima celula*/
Node* ListGetNextNode(List* list, Node* node);

/*-------------ListGetPrevNode--------------
* Retorna a celula anterior de uma celula ja conhecida dentro de uma lista
*-------------------------------------------
*  - inputs: ponteiro para a lista e ponteiro para a celula
*  
*  - output: ponteiro para a celula anterior ou NULL para o inicio da lista
*
*  - pre-condicao: lista e celula alocados e celula esta contida na lista
*
*  - pos-condicao: ponteiro de retorno aponta para a celula anterior*/
Node* ListGetPrevNode(List* list, Node* node);

/*-------------ListGetHead--------------
* Retorna a primeira celula de uma lista
*-------------------------------------------
*  - inputs: ponteiro para a lista
*  
*  - output: ponteiro para a primeira celula da lista ou NULL para listas vazias
*
*  - pre-condicao: lista alocada
*
*  - pos-condicao: ponteiro de retorno aponta para a primeira celula da lista*/
Node* ListGetHead(List* list);

/*-------------ListGetTail--------------
* Retorna a ultima celula de uma lista
*-------------------------------------------
*  - inputs: ponteiro para a lista
*  
*  - output: ponteiro para a ultima celula da lista ou NULL para listas vazias
*
*  - pre-condicao: lista alocada
*
*  - pos-condicao: ponteiro de retorno aponta para a ultima celula da lista*/
Node* ListGetTail(List* list);

/*-------------ListSearchKey--------------
* Retorna a primeira celula com uma certa chave de busca
*-------------------------------------------
*  - inputs: ponteiro para a lista e string chave de busca
*  
*  - output: ponteiro para a celula determinada ou NULL caso nao seja encontrada
*
*  - pre-condicao: lista alocada e string chave valida
*
*  - pos-condicao: ponteiro de retorno aponta para a celula que possui a chave determinada*/
Node* ListSearchKey(List* list, const char* key);

/*-------------ListAddNodeHead--------------
* Adiciona uma celula no inicio de uma lista
*-------------------------------------------
*  - inputs: ponteiro para a lista e ponteiro para a celula
*  
*  - output: nenhum
*
*  - pre-condicao: lista alocada, celula alocada e ja inicializada com o mesmo tipo contido na lista
*
*  - pos-condicao: celula adicionada ao inicio da lista*/
void ListAddNodeHead(List* list, Node* node);

/*-------------ListAddNodeTail--------------
* Adiciona uma celula no final de uma lista
*-------------------------------------------
*  - inputs: ponteiro para a lista e ponteiro para a celula
*  
*  - output: nenhum
*
*  - pre-condicao: lista alocada, celula alocada e ja inicializada com o mesmo tipo contido na lista
*
*  - pos-condicao: celula adicionada ao final da lista*/
void ListAddNodeTail(List* list, Node* node);

/*-------------ListRemoveNode--------------
* Retira uma celula da lista liberando a celula e seus conteudos da memoria
*-------------------------------------------
*  - inputs: ponteiro para a lista e ponteiro para a celula
*  
*  - output: nenhum
*
*  - pre-condicao: lista alocada, celula alocada e contida na lista
*
*  - pos-condicao: celula retirada da lista e liberada da memoria junto com os dados inclusos nela*/
Node* ListRemoveNode(List* list, Node* node);

/*-------------ListEmpty--------------
* Retira todas as celulas de uma lista junto com os dados inclusos nelas
*-------------------------------------------
*  - inputs: ponteiro para a lista
*  
*  - output: nenhum
*
*  - pre-condicao: lista alocada
*
*  - pos-condicao: todas as celulas da lista liberadas junto com os dados inclusos nelas*/
void ListEmpty(List* list);

/*-------------ListDelete--------------
* Libera uma lista ja vazia da memoria
*-------------------------------------------
*  - inputs: ponteiro para a lista
*  
*  - output: nenhum
*
*  - pre-condicao: lista alocada e vazia
*
*  - pos-condicao: lista liberada da memoria*/
void ListDelete(List* list);

#endif /*LIST_H*/