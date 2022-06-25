#ifndef SENSOR_H
#define SENSOR_H

//latitude e longitude marcam a posicao
//temperature marca a temperatura
//accelerometer marca uma queda
typedef struct sensor Sensor;

/*-----------SensorInit----------------
*Cria uma instancia de um sensor, com todos os atributos em valor padrao
*-------------------------------------------
*  - inputs: posicao (latitude e longitude), temperatura e aceleracao 
*  
*  - output: sensor alocado e com valores padrao
*
*  - pre-condicao: nenhuma
*
*  - pos-condicao: sensor alocado*/
Sensor* SensorInit(double latitude, double longitude, double temperature, int acceleration);

/*-----------SensorUpdateAll----------------
* Atualiza todos os atributos do sensor
*--------------------------------------------
*  - inputs: ponteiro para o sensor, posicao (latitude e longitude), temperatura e aceleracao  
*  
*  - output: nenhum
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: sensor ainda alocado e com valores atualizados*/
void SensorUpdateAll(Sensor* sensor, double latitude, double longitude, double temperature, int acceleration);

/*-----------SensorUpdatePosition----------------
* Atualiza o valor de posicao do sensor
*----------------------------------------------------
*  - inputs: ponteiro para o sensor, temperatura
*  
*  - output: nenhum
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: sensor ainda alocado e com valores atualizados*/
void SensorUpdatePosition(Sensor* sensor,double latitude, double longitude);

/*-----------SensorUpdateTemperature----------------
* Atualiza o valor de tempratura do sensor
*----------------------------------------------------
*  - inputs: ponteiro para o sensor, temperatura
*  
*  - output: nenhum
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: sensor ainda alocado e com valores atualizados*/
void SensorUpdateTemperature(Sensor* sensor,double temperature);

/*-----------SensorUpdateAcceleration------------
* Atualiza o valor de aceleracao do sensor
*----------------------------------------------------
*  - inputs: ponteiro para o sensor, aceleracao
*  
*  - output: nenhum
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: sensor ainda alocado e com valores atualizados*/
void SensorUpdateAcceleration(Sensor* sensor,int acceleration);


/*---------------SensorGetCounter--------------
* Retorna o valor atual do contador do sensor
*---------------------------------------------------------
*  - inputs: ponteiro para o sensor
*  
*  - output: valor inteiro do contador
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: nenhuma*/
int SensorGetCounter(Sensor* sensor);

/*---------------SensorIncrementCounter--------------
* Incrementa em uma unidade o valor atual do contador do sensor
*---------------------------------------------------------
*  - inputs: ponteiro para o sensor
*  
*  - output: valor inteiro do contador apos o incremento
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: valor do contador incrementado em uma unidade*/
int SensorIncrementCounter(Sensor* sensor);

/*---------------SensorDecrementCounter--------------
* Decrementa em uma unidade o valor atual do contador do sensor
*---------------------------------------------------------
*  - inputs: ponteiro para o sensor
*  
*  - output: valor inteiro do contador apos o decremento
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: valor do contador decrementado em uma unidade*/
int SensorDecrementCounter(Sensor* sensor);

/*---------------SensorDecrementCounter--------------
* Reinicia o valor do contador do sensor
*---------------------------------------------------------
*  - inputs: ponteiro para o sensor
*  
*  - output: nenhum
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: valor do contador igual a 0 (zero)*/
void SensorResetCounter(Sensor* sensor);

/*---------------SensorReadLatitude--------------
* Retorna o valor de latitude do sensor
*---------------------------------------------------------
*  - inputs: ponteiro para o sensor
*  
*  - output: latitude (double)
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: nenhuma*/
double SensorReadLatitude(Sensor* sensor);

/*---------------SensorReadLongitude--------------
* Retorna o valor de longitude do sensor
*---------------------------------------------------------
*  - inputs: ponteiro para o sensor
*  
*  - output: longitude (double)
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: nenhuma*/
double SensorReadLongitude(Sensor* sensor);

/*---------------SensorReadTemperature--------------
* Retorna o valor de temperatura do sensor
*---------------------------------------------------------
*  - inputs: ponteiro para o sensor
*  
*  - output: temperatura (double)
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: nenhuma*/
double SensorReadTemperature(Sensor* sensor);

/*---------------SensorReadTemperature--------------
* Retorna o valor de aceleracao do sensor
*---------------------------------------------------------
*  - inputs: ponteiro para o sensor
*  
*  - output: aceleracao (int)
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: nenhuma*/
int SensorReadAcceleration(Sensor* sensor);

/*---------------SensorPrintReadings--------------
* Imprime os valores de leitura do sensor na saida padrao
*---------------------------------------------------------
*  - inputs: ponteiro para o sensor
*  
*  - output: nenhum
*
*  - pre-condicao: sensor alocado
*
*  - pos-condicao: nenhuma*/
void SensorPrintReadings(Sensor* sensor);

/*---------------SensorDelete--------------
* Libera o sensor da memoria
*---------------------------------------------------------
*  - inputs: ponteiro para o sensor
*  
*  - output: nenhum
*
*  - pre-condicao: nenhuma
*
*  - pos-condicao: nenhuma*/
void SensorDelete(Sensor* sensor);

#endif /*SENSOR_H*/