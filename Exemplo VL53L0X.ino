#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include "SevenSegmentTM1637.h"
const byte PIN_CLK = 11;   // pino CLK do TM1637
const byte PIN_DIO = 10;   // pino DIO do TM1637
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);


// endereço padrão do módulo é 0x29, mesmo do módulo da Adafruit
float distancia; // valor lido a partir do 53L0XV2

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  display.begin();            // Inicializa o display
  display.setBacklight(100);
  Serial.begin(115200);
  //while(!(Serial.available()));
  Serial.println("Comecando...");
  Wire.begin();
  if (!lox.begin()) {
    Serial.println("Sensor nao inicializado");
    display.print("OPS");
    while (1);
  } else {
    Serial.println("Sensor inicializado!");
    display.print("tdb");
  };
  delay(1000);
}

void loop() {
  VL53L0X_RangingMeasurementData_t medida;
  lox.rangingTest(&medida, false);
  display.clear();
  if (medida.RangeStatus != 4) {
    distancia = medida.RangeMilliMeter;
    display.print((int)medida.RangeMilliMeter);
    Serial.print("Distancia: ");
    Serial.print(medida.RangeMilliMeter);
    Serial.println(" mm");
  } else {
    distancia = 0;
  };
  delay(100);
}
