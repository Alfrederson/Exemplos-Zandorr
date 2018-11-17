#include <Wire.h>
#include "Adafruit_VL53L0X.h"

// endereço padrão do módulo é 0x29, mesmo do módulo da Adafruit
float distancia; // valor lido a partir do 53L0XV2

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup(){
  Serial.begin(115200);
  //while(!(Serial.available()));
  Serial.println("Comecando...");
   Wire.begin();
  if(!lox.begin()){
    Serial.println("Nao deu pra inicializar o sensor");
    while(1);
  }else{
    Serial.println("Sensor inicializado");
  };  
  delay(1000);
}

void loop(){
  VL53L0X_RangingMeasurementData_t medida;
  lox.rangingTest(&medida,false);
  if(medida.RangeStatus !=4){
    distancia = medida.RangeMilliMeter;
    Serial.println(medida.RangeMilliMeter);
    
  }else{
    distancia = 0;
  };
  
  delay(100);
}
