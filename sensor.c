#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sensor.h"

struct sensor {
    double latitude;
    double longitude;
    double temperature;
    int acceleration; //queda?
    int counter;
};

Sensor* SensorInit(double latitude, double longitude, double temperature, int acceleration){
    Sensor* newSensor = (Sensor*) malloc(sizeof(Sensor));

    newSensor -> latitude = latitude;
    newSensor -> longitude = longitude;
    newSensor -> temperature = temperature;
    newSensor -> acceleration = acceleration;
    newSensor -> counter = 0;

    return newSensor;
}

void SensorUpdateAll(Sensor* sensor, double latitude, double longitude, double temperature, int acceleration){
    sensor -> latitude = latitude;
    sensor -> longitude = longitude;
    sensor -> temperature = temperature;
    sensor -> acceleration = acceleration;    
}

void SensorUpdatePosition(Sensor* sensor,double latitude, double longitude){
    sensor -> latitude = latitude;
    sensor -> longitude = longitude;
}

void SensorUpdateTemperature(Sensor* sensor,double temperature){
    sensor -> temperature = temperature;
}

void SensorUpdateAcceleration(Sensor* sensor,int acceleration){
    sensor -> acceleration = acceleration;    
}

int SensorGetCounter(Sensor* sensor){
    return sensor -> counter;
}

int SensorIncrementCounter(Sensor* sensor){
    (sensor -> counter)++;
    return sensor -> counter;
}

int SensorDecrementCounter(Sensor* sensor){
    (sensor -> counter)--;

    if(sensor -> counter < 0){
        sensor -> counter = 0;
    }
    
    return sensor -> counter;
}

void SensorResetCounter(Sensor* sensor){
    sensor -> counter = 0;
}

double SensorReadLatitude(Sensor* sensor){
    return sensor -> latitude;
}

double SensorReadLongitude(Sensor* sensor){
    return sensor -> longitude;
}

double SensorReadTemperature(Sensor* sensor){
    return sensor -> temperature;
}

int SensorReadAcceleration(Sensor* sensor){
    return sensor -> acceleration;
}

void SensorPrintReadings(Sensor* sensor){
    printf("Readings: Position(lat:%.0f, long:%.0f), Temperature(%.1f), Acceleration(%d)\n", 
    sensor -> latitude,
    sensor -> longitude,
    sensor -> temperature,
    sensor -> acceleration);
}

void SensorDelete(Sensor* sensor){
    free(sensor);    
}
