#include <stdio.h>
#include <stdlib.h>
#include "carer.h"
#include "system.h"
//adicionados pra propósitos de teste
#include "elder.h"
#include "list.h"

int main (int argc, char* argv[]){

    int total = 15;
    //sscanf(argv[argc-1], "%d", &total);

    System* mySystem = SystemInit();

    int i = 1;

    //faz a atualização do sistema para cada momento dos sensores
    while(i <= total){
        SystemUpdate(mySystem, i);
        SystemTakeActions(mySystem);
        i++;
    }
    
    //imprime a última atualização
    SystemPrint(mySystem);

    SystemEnd(mySystem);

    return 0;
}