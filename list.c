#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "elder.h"

//cada node tem uma chave para facilitar buscas
//a chave tem conteudos constantes para evitar a
//modificacao por parte do cliente
struct node{
    const char* key;
    void* data;
    Node* prev;
    Node* next;
};

//um ponteiro para funcao determina 
//como a liberacao de memoria deve ser
//tratada dentro da lista. Caso ele seja NULL
//a lista NAO libera os dados incluidos nos nodes 
struct list{
    void (*deleteItem)(void*); 
    Node* sentinel;
    int total;
};

//funcoes usadas internamente
int IsNodeinList(List* list, Node* node);
int IsEmpty(List* list);


List* ListInit(void (*DeleteFunction) (void* data)){

   List* newList = (List*) malloc(sizeof(List));
   Node* sentinel = (Node*) malloc(sizeof(Node));

   sentinel -> data = NULL;
   sentinel -> key = NULL;

   //quando a lista e vazia o sentinela aponta para ele mesmo
   sentinel -> next = sentinel -> prev = sentinel;

   newList -> sentinel = sentinel;
   newList -> deleteItem = DeleteFunction;
     
   newList -> total = 0;

   return newList;
}

Node* NodeCreate(const char* key, void* data){

    if(!key){
        printf("\n\nERRO: NodeCreate -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

   Node* newNode = (Node*) malloc(sizeof(Node));

   newNode -> next = NULL;
   newNode -> prev = NULL;

   newNode -> data = data;
   newNode -> key = strdup(key);

   return newNode;
}

void NodeDelete(Node* node){

    if(!node){
        return;
    }

    //casting para contornar o tipo const char*
    free((void*)node -> key);
    free(node); 
}

const char* NodeGetKey(Node* node){

    if(!node){
        printf("\n\nERRO: NodeGetKey -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    return node -> key;
}

void* NodeGetData(Node* node){
    if(!node){
        return NULL;
    }

    return node -> data;
}

Node* ListGetNextNode(List* list, Node* node){

    if(!node || !list){
        printf("\n\nERRO: ListGetNextNode -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    //o sentinela sinaliza o fim da lista
    if(node -> next != list -> sentinel)
        return node -> next;
    else
        return NULL;
}

Node* ListGetPrevNode(List* list, Node* node){

    if(!node || !list){
        printf("\n\nERRO: ListGetPrevNode -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }
    
    //o sentinela sinaliza o inicio da lista
    if(node -> prev != list -> sentinel)
        return node -> prev;
    else
        return NULL;
}

Node* ListGetHead(List* list){

    if(!list){
        printf("\n\nERRO: ListGetHead -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    //limites da lista
    Node* head = list -> sentinel -> next;

    if(head == list -> sentinel){
        return NULL;
    }

    return head;
}

Node* ListGetTail(List* list){

    if(!list){
        printf("\n\nERRO: ListGetTail -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }

    //limites da lista
    Node* tail = list -> sentinel -> prev;

    if(tail == list -> sentinel){
        return NULL;
    }

    return tail;
}

//funcao interna
int IsNodeinList(List* list, Node* node){

    if(!list || !node){
        printf("\n\nERRO: IsNodeinList -> ponteiro ou argumento invalido, retornou -1\n\n");
        return -1;
    }

    //limites da lista
    Node* head = list -> sentinel -> next;

    //percorre a lista ate encontrar o node estabelecido
    for(Node* currentNode = head; currentNode != list -> sentinel; currentNode = currentNode -> next){
          if(currentNode == node)
            return 1;
    }

    return 0;
}

Node* ListSearchKey(List* list, const char* key){

    if(!list || !key){
        printf("\n\nERRO: ListSearchKey -> ponteiro ou argumento invalido, retornou NULL\n\n");
        return NULL;
    }
    if(list -> total == 0) return NULL;
    //limites da lista
    Node* head = list -> sentinel -> next;

    Node* currentNode = head;
    int i = 0;
    while (strcmp(key, currentNode -> key) && currentNode != list -> sentinel){
        i++;
        if(i == list->total) break;
        currentNode = currentNode -> next;
    }
    if(i == list -> total) return NULL;
    return currentNode;
}

void ListAddNodeHead(List* list, Node* node){

    if(!list || !node){
        printf("\n\nERRO: ListAddNodeHead -> ponteiro ou argumento invalido\n\n");
        return;
    }

    //limites da lista
    Node* head = list -> sentinel -> next;

    //encadeia com o primeiro da lista
    node -> next = head;
    head -> prev = node;

    //atualiza o inicio da lista
    list -> sentinel -> next = node;
    node -> prev = list -> sentinel;

    list->total++;
}

void ListAddNodeTail(List* list, Node* node){

    if(!list || !node){
        printf("\n\nERRO: ListAddNodeTail -> ponteiro ou argumento invalido\n\n");
        return;
    }

    //limites da lista
    Node* tail = list -> sentinel -> prev;

    //encadeia com o ultimo da lista
    node -> prev = tail;
    tail -> next = node;

    //atualiza o final da lista
    list -> sentinel -> prev = node;
    node -> next = list -> sentinel;

    list->total++;
}

Node* ListRemoveNode(List* list, Node* node){

    if(!IsNodeinList(list, node) || !list || !node){
        printf("\n\nERRO: ListRemoveNode -> ponteiro ou argumento invalido\n\n");
        return NULL;
    }

    node -> prev -> next = node -> next;
    node -> next -> prev = node -> prev;

    if(list -> deleteItem != NULL)
        list -> deleteItem(NodeGetData(node));

    NodeDelete(node);

    list->total--;

    return node;
}
//função privada para verificar se uma lista está vazia na hora de procurar
int IsEmpty(List* list){
    Node* head = list -> sentinel -> next;
    if(head == NULL) return 1;
    else return 0;
}
void ListEmpty(List* list){

    if(!list){
        printf("\n\nERRO: ListEmpty -> ponteiro ou argumento invalido\n\n");
        return;
    }

    //limites da lista
    Node* head = list -> sentinel -> next;
    
    Node* currentNode = head;

    while(currentNode != list -> sentinel){
        currentNode = currentNode -> next;

        if(list -> deleteItem != NULL)
            list -> deleteItem(NodeGetData(currentNode -> prev));
        
        NodeDelete(currentNode -> prev);
    }

    list -> sentinel -> next = list -> sentinel;
    list -> sentinel -> prev = list -> sentinel;

    list->total = 0;
}

void ListDelete(List* list){

    if(!list){
        printf("\n\nERRO: ListDelete -> ponteiro ou argumento invalido\n\n");
        return;
    }

    //limites da lista
    Node* head = list -> sentinel -> next;

    if (head != list -> sentinel){
        printf("\n\nERRO: ListDelete -> nao e possivel deletar uma lista preenchida, esvazie-a primeiro\n\n");
        return;
    }
    
    free(list -> sentinel);
    free(list);

    list = NULL;   
}