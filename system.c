#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "system.h"
#include "elder.h"
#include "carer.h"
#include "sensor.h"
#include "list.h"

struct system {
    List* elderList; //o sistema é baseado em uma lista de idosos e outra de cuidadores
    List* carerList;
};


System* SystemInit(void){
    System* newSystem = (System*) malloc(sizeof(System));

    newSystem -> elderList = ListInit(ElderDelete); //declaração de início de sistema com função de callback
    newSystem -> carerList = ListInit(CarerDelete);

    //abrindo os arquivos para inserir os elementos nas listas
    FILE* friendsFile = fopen("Entradas/apoio.txt", "r");
    FILE* carersFile = fopen("Entradas/cuidadores.txt", "r");

    if(!friendsFile || !carersFile){
        printf("\n\nERRO: SystemInit -> arquivos de inicializacao nao encontrados, retornou NULL\n\n");
        return NULL;
    }

    char* carersFileLine;
    char* friendsFileLine;
    
    fscanf(carersFile, "%m[^\n]\n", &carersFileLine);
    fscanf(friendsFile, "%m[^\n]\n", &friendsFileLine);
    sscanf(friendsFileLine, "%s", friendsFileLine); //%s acaba em '\0'
    sscanf(carersFileLine, "%s", carersFileLine);  // espaços antes e depois das letras são ignorados
    
    //strtok: função da string.h para dividir uma string com base em uma parte da string que se repete
    for(char* currentName = strtok(carersFileLine, ";"); currentName != NULL; currentName = strtok(NULL, ";")){
        if(!currentName){
            printf("\n\nERRO: SystemInit -> mal formatacao dos arquivos de inicializacao, retornou NULL\n\n");
            return NULL;
        }

        ListAddNodeTail(newSystem -> carerList, NodeCreate(currentName, CarerInit(currentName, 0.0, 0.0)));
    }   

    for(char* currentName = strtok(friendsFileLine, ";"); currentName != NULL; currentName = strtok(NULL, ";")){

        if(!currentName){
            printf("\n\nERRO: SystemInit -> mal formatacao dos arquivos de inicializacao, retornou NULL\n\n");
            return NULL;
        }

        ListAddNodeTail(newSystem -> elderList, NodeCreate(currentName, ElderInit(currentName)));
    }
    //libera a primeira linha de cada arquivo 
    free(carersFileLine);
    free(friendsFileLine);

    //extrai das linhas depois da primeira
    while(fscanf(friendsFile, "%m[^\n]\n", &friendsFileLine) != EOF){
        char* name1 = strtok(friendsFileLine, ";");
        char* name2 = strtok(NULL, ";");

        
        if(!name1 || !name2){
            printf("\n\nERRO: SystemInit -> mal formatacao dos arquivos de inicializacao, retornou NULL\n\n");
            return NULL;
        }

        //extrai dois idosos da lista (os dois da linha do arquivo apoio.txt)
        Elder* elder1 = (Elder*) NodeGetData(ListSearchKey(newSystem -> elderList, name1));
        Elder* elder2 = (Elder*) NodeGetData(ListSearchKey(newSystem -> elderList, name2));

        //associa o idoso ao seu amigo e vice-versa
        ElderAddFriend(elder1, elder2);
        ElderAddFriend(elder2, elder1);
        free(friendsFileLine);
    }
    
    while(fscanf(carersFile, "%m[^\n]\n", &carersFileLine) != EOF){
        //extrai o nome do idoso: o primeiro da linha
        char* elderName = strtok(carersFileLine, ";");

        if(!elderName){
            printf("\n\nERRO: SystemInit -> mal formatacao dos arquivos de inicializacao, retornou NULL\n\n");
            return NULL;
        }

        Elder* currentElder = (Elder*) NodeGetData(ListSearchKey(newSystem -> elderList, elderName));
        //extrai o nome de cada cuidador que venha depois do idoso
        for(char* carerName = strtok(NULL, ";"); carerName != NULL; carerName = strtok(NULL, ";")){

            if(!carerName){
                printf("\n\nERRO: SystemInit -> mal formatacao dos arquivos de inicializacao, retornou NULL\n\n");
                return NULL;
            }
            //associa o cuidador que já está na lista a um idoso
            Carer* currentCarer = (Carer*) NodeGetData(ListSearchKey(newSystem -> carerList, carerName));
            ElderAddCarer(currentElder, currentCarer);
        }

        free(carersFileLine);
    }

    fclose(friendsFile);
    fclose(carersFile);

    return newSystem;
}

void SystemUpdate(System* system, int n){

    if(!system || n < 0){
        printf("\n\nERRO: SystemUpdate -> ponteiro ou argumento invalido\n\n");
        return;
    }
    
    FILE* currentFile;

    //percorre a lista inteira uma vez, usando o for para percorrer cada célula
    for(Node* currentNode = ListGetHead(system -> elderList); currentNode != NULL; currentNode = ListGetNextNode(system -> elderList, currentNode)){
        Elder* currentElder = (Elder*) NodeGetData(currentNode);

        //forma o nome do arquivo para abrir e atualizar os dados
        char* fileName = (char*) malloc(100*sizeof(char));
        strcpy(fileName, "Entradas/");
        strcat(fileName, ElderGetName(currentElder));
        strcat(fileName, ".txt");

        currentFile = fopen(fileName, "r");

        free(fileName);
        
        if(!currentFile){
            printf("\n\nERRO: SystemUpdate -> arquivo de leitura \"%s\" nao encontrados\n\n", fileName);
            fclose(currentFile);
            return;
        }
        
        char* readingsFileLine;

        //extrai a linha n-1 do arquivo
        for (int i = 0; i < n; i++){
            if(fscanf(currentFile, "%m[^\n]\n", &readingsFileLine) == EOF) break;
            if(i != n-1) free(readingsFileLine);         
        }
        fclose(currentFile);
        

        if(!(strcmp(readingsFileLine, "falecimento"))){
            //assim que lê a palavra "falecimento" como linha de atualização, ele remove o idoso da lista
            SystemRemoveElder(system, ElderGetName(currentElder));
            free(readingsFileLine);
            continue; //antes estava break
        }

        double latitude, longitude, temperature;
        int acceleration;

        //extrai os valores da linha de atualização para atualizar os sensores dos idosos
        sscanf(readingsFileLine, "%lf;%lf;%lf;%d", &temperature, &latitude, &longitude, &acceleration);
        SensorUpdateAll(ElderGetReadings(currentElder), latitude, longitude, temperature, acceleration);

        //liberação da linha de leitura do arquivo é importante porque fscanf também pode gerar vazamento de memória
        free(readingsFileLine);
    }

    //a lógica de atualização dos dados dos cuidadores é a mesma da atualização dos idosos
    for(Node* currentNode = ListGetHead(system -> carerList); currentNode != NULL; currentNode = ListGetNextNode(system -> carerList, currentNode)){
        Carer* currentCarer = (Carer*) NodeGetData(currentNode);
        
        char* fileName = (char*) malloc(100*sizeof(char));

        strcpy(fileName, "Entradas/");
        strcat(fileName, CarerGetName(currentCarer));
        strcat(fileName, ".txt");

        currentFile = fopen(fileName, "r");
        
        free(fileName);

        if(!currentFile){
            printf("\n\nERRO: SystemUpdate -> arquivo de leitura \"%s\" nao encontrados\n\n", fileName);
            return;
        }
        
        char* readingsFileLine;

        //le o arquivo ate a linha n
        for (int i = 0; i != n; i++){
            if(fscanf(currentFile, "%m[^\n]\n", &readingsFileLine) == EOF) break;
            if(i == n-1) break;
            free(readingsFileLine);
        }

        double latitude, longitude;

        sscanf(readingsFileLine, "%lf;%lf", &latitude, &longitude);
        CarerSetLatitude(currentCarer, latitude);
        CarerSetLongitude(currentCarer, longitude);
        
        fclose(currentFile);
        free(readingsFileLine);
    }

    for(Node* currentNode = ListGetHead(system -> elderList); currentNode != NULL; currentNode = ListGetNextNode(system -> elderList, currentNode)){
        Elder* currentElder = NodeGetData(currentNode);
        ElderUpdateCloserCarer(currentElder);
        ElderUpdateCloserFriend(currentElder);
    }

    
}

void SystemTakeActions(System* system){

    if(!system){
        printf("\n\nERRO: SystemTakeActions -> ponteiro ou argumento invalido\n\n");
        return;
    }
    
    for(Node* currentNode = ListGetHead(system -> elderList); currentNode != NULL; currentNode = ListGetNextNode(system -> elderList, currentNode)){
        Elder* currentElder = (Elder*) NodeGetData(currentNode);

        //pegando o valor que o idoso dessa iteração está condicionado
        int elderSituation = SystemCheckElder(system, ElderGetName(currentElder));

        char* outputFileName = (char*) malloc(100*sizeof(char));
        
        strcpy(outputFileName, "Saidas/");
        strcat(outputFileName, ElderGetName(currentElder));
        strcat(outputFileName, "-saida.txt");
        
        FILE* outputFile = fopen(outputFileName, "a");
        
        if(!outputFile){
            printf("\n\nERRO: SystemTakeActions -> arquivo de saida \"%s\" nao encontrado\n\n", outputFileName);
            fclose(outputFile);
            free(outputFileName);
            return;
        }

        free(outputFileName);

        //aqui só imprime o correspondente ao que foi conseguido na função SystemCheckElder
        //a impressão de falecimento é a única que não está aqui, já que ela acontece antes de a atualização ser finalizada
        if(elderSituation == 4)
            fprintf(outputFile, "queda, acionou %s\n", CarerGetName(ElderGetCloserCarer(currentElder)));

        else if(elderSituation == 3)
            fprintf(outputFile, "febre alta, acionou %s\n", CarerGetName(ElderGetCloserCarer(currentElder)));
        
        else if(elderSituation == 2)
            fprintf(outputFile, "febre baixa pela quarta vez, acionou %s\n", CarerGetName(ElderGetCloserCarer(currentElder))); 
        
        else if(elderSituation == 1)
            fprintf(outputFile, "febre baixa, acionou amigo %s\n", ElderGetName(ElderGetCloserFriend(currentElder)));

        else if(elderSituation == 0)
            fprintf(outputFile, "tudo ok\n");

        else if(elderSituation == 6)
            fprintf(outputFile, "Febre baixa mas, infelizmente, o idoso está sem amigos na rede\n"); //ESSE IDOSO NÃO TEM AMIGOS, O POBI
        
        else fprintf(outputFile, "ERRO: ALGO DE ERRADO NAO ESTA CERTO\n");

        fclose(outputFile);
    }
}

int SystemCheckElder(System* system, const char* elderName){

    if(!system || !elderName){
        printf("\n\nERRO: SystemCheckElder -> ponteiro ou argumento invalido\n\n");
        return -2; //valor arbitrário de erro 
    }

    Elder* elder = (Elder*) NodeGetData(ListSearchKey(system -> elderList, elderName));

    if(elder == NULL){
        return -1; //nao existe
    }

    double temperature = SensorReadTemperature(ElderGetReadings(elder));
    int acceleration = SensorReadAcceleration(ElderGetReadings(elder));

    if (acceleration == 1){
        return 4; //queda
    }

    if(temperature >= 38){
        SensorResetCounter(ElderGetReadings(elder));
        return 3; //febre alta
    }

    if(temperature >= 37){
        SensorIncrementCounter(ElderGetReadings(elder));
        
        if(ElderGetCloserFriend(elder) == NULL) return 6; //esse idoso não tem amigos para chamar
        
        if(SensorGetCounter(ElderGetReadings(elder)) == 4){
            SensorResetCounter(ElderGetReadings(elder));
            return 2; //4 casos de febre baixa seguidos
        }
        return 1; //febre baixa
        
    }

    return 0; //tudo ok
}

void SystemRemoveElder(System* system, const char* elderName){

    if(!system || !elderName){
        printf("\n\nERRO: SystemRemoveElder -> ponteiro ou argumento invalido\n\n");
        return;
    }

    Node* removingNode = ListSearchKey(system->elderList, elderName);
    Elder* elder = (Elder*) NodeGetData(removingNode);
    
    char* outputFileName = (char*) malloc(100*sizeof(char));
    strcpy(outputFileName, "Saidas/");
    
    strcat(outputFileName, ElderGetName(elder));
    strcat(outputFileName, "-saida.txt");
    
    FILE* outputFile = fopen(outputFileName, "a");
    free(outputFileName);
    
    if(!outputFile){
        printf("\n\nERRO: SystemTakeActions -> arquivo de saida \"%s\" nao encontrado\n\n", outputFileName);
        return;
    }
    
    fprintf(outputFile, "falecimento\n");
    fclose(outputFile);
    
    //percorre a lista inteira e vai tirando o idoso de cada lista de amigos de cada idoso
    for(Node* currentNode = ListGetHead(system -> elderList); currentNode != NULL; currentNode = ListGetNextNode(system -> elderList, currentNode)){
        Elder* currentElder = (Elder*) NodeGetData(currentNode);
        if(currentElder == elder){
            continue;
        }

        ElderRemoveFriend(currentElder, elderName);
    }
    //finalmente, remove o idoso da lista  
    ListRemoveNode(system->elderList, removingNode); //a função de tirar um Node da lista já deleta o node e o que tem dentro dele com o callback
}

void SystemEnd(System* system){

    if(!system){
        printf("\n\nERRO: SystemEnd -> ponteiro ou argumento invalido\n\n");
        return;
    }

    //esvazia e libera cada lista principal do sistema
    ListEmpty(system -> carerList);
    ListDelete(system -> carerList);

    ListEmpty(system -> elderList);
    ListDelete(system -> elderList);

    free(system);
}

void SystemPrint(System* system){

    if(!system){
        printf("\n\nERRO: SystemPrint -> ponteiro ou argumento invalido\n\n");
        return;
    }

    Node* elderNode = ListGetHead(system->elderList);
    Elder* elder;

    //percorre a lista inteira
    while(elderNode != NULL){
        elder = NodeGetData(elderNode);
        ElderPrint(elder);
        printf("\n");    
        elderNode = ListGetNextNode(system->elderList, elderNode);
    }
    
    Node* carerNode = ListGetHead(system->carerList);
    Carer* carer;

    while(carerNode != NULL){
        carer = NodeGetData(carerNode);
        CarerPrint(carer);
        printf("\n");
        carerNode = ListGetNextNode(system->carerList, carerNode);
    }
}
