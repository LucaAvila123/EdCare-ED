
#ifndef SYSTEM_H
#define SYSTEM_H

typedef struct system System;

/*-----------SystemInit----------------
* Cria uma instancia do sistema e inicializa usando os arquivos de input
*-------------------------------------------
*  - inputs: nenhum 
*  
*  - output: ponteiro para o sistema alocado ou NULL caso um erro ocorra
*
*  - pre-condicao: arquivos de input existem e estao formatados corretamente
*
*  - pos-condicao: sistema alocado e com listas inicializadas*/
System* SystemInit(void);

/*-----------SystemUpdate----------------
* Atualiza os atributos do sistema usando os arquivos de leitura
*-------------------------------------------
*  - inputs: ponteiro para o sistema e numero da linha a ser lida dos arquivos de leitura
*  
*  - output: nenhum
*
*  - pre-condicao: sistema alocado, arquivos de leitura existem e estao formatados corretamente
*
*  - pos-condicao: atributos do sistema atualizados*/
void SystemUpdate(System* system, int n);

/*-----------SystemTakeActions----------------
* Atualiza os arquivos de saída usando os atributos do sistema
*-------------------------------------------
*  - inputs: ponteiro para o sistema
*  
*  - output: nenhum
*
*  - pre-condicao: sistema alocado, pasta dos arquivos de saída existe 
*
*  - pos-condicao: arquivos de saída criados e atualizados*/
void SystemTakeActions(System* system);
/*-----------SystemCheckElder----------------
* Faz um checkup da situacao de um idoso baseado na leitura de seus sensores
*-------------------------------------------
*  - inputs: ponteiro para o sistema e ponteiro para o nome do idoso
*  
*  - output: 0 para tudo ok, 1 para febre baixa, 2 para febre alta, 
*            3 para multiplos casos de febre baixa e 4 para queda
*
*  - pre-condicao: sistema alocado e nome do idoso valido
*
*  - pos-condicao: nenhum*/
int SystemCheckElder(System* system, const char* elderName);

/*-----------SystemRemoveElder----------------
* Remove um idoso do sistema e declara falecimento do mesmo
*-------------------------------------------
*  - inputs: ponteiro para o sistema e ponteiro para o nome do idoso
*  
*  - output: nenhum;
*
*  - pre-condicao: sistema alocado, arquivos de saida existem;
*
*  - pos-condicao: idoso removido do sistema e tambem das listas de amigos*/
void SystemRemoveElder(System* system, const char* elderName);

/*-----------SystemEnd----------------
* Libera toda a memoria do sistema
*-------------------------------------------
*  - inputs: ponteiro para o sistema
*  
*  - output: nenhum;
*
*  - pre-condicao: nenhum;
*
*  - pos-condicao: sistema liberado da memoria*/
void SystemEnd(System* system);

/*-----------SystemPrint----------------
* Imprime todas as informacoes do sistema na saida padrao
*-------------------------------------------
*  - inputs: ponteiro para o sistema
*  
*  - output: nenhum;
*
*  - pre-condicao: sistema alocado;
*
*  - pos-condicao: nenhum*/
void SystemPrint(System* system);

#endif /*SYSTEM_H*/