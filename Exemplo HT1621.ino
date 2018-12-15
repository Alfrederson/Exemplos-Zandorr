/*
  Baseado no exemplo da biblioteca HT1621.h, disponível neste repositório:

  https://github.com/5N44P/ht1621-7-seg
*/

#include <HT1621.h> // include our library

HT1621 lcd;
void setup(){
  lcd.begin(13, 12, 8, 10); // (cs, wr, Data, backlight)
  lcd.noBacklight(); // É preciso fazer uma modificação no display pra isso funcionar, caso contrário o led fica sempre aceso
  lcd.clear();      
}

void loop(){
  static unsigned long contador=0;
  static unsigned char bateria=0;
  static char direcao_bateria=1;
  static float  numeral=1;
  static float direcao_numeral=7.19f;
  static char tics_bateria=0;
  if(millis()>=contador+100){
    contador=millis();
    tics_bateria++;
    // Faz o nível de bateria subir e descer de 1 em 1 segundo
    if(tics_bateria==10){
      tics_bateria=0;
      bateria+=direcao_bateria;
      if( (bateria==3) || (bateria==0)) direcao_bateria*=-1;
      lcd.setBatteryLevel(bateria);      
    };
    // Aumenta e diminui um contador
    numeral += direcao_numeral;
    if( (numeral>=1000) || (numeral<=-1000) ){
      direcao_numeral *= -1;
    };
    lcd.print(numeral,2);
  };
}
