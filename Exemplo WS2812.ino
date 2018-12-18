
#include <NeoPixelBus.h>

const uint16_t PixelCount = 64; // matriz possui 64 leds
const uint8_t PixelPin = 4;  // DIN ligado no pino 4

#define colorSaturation 128

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> matriz_led(PixelCount, PixelPin);

RgbColor cor(0, 85, 1);
RgbColor matriz[8*8];
char bitmap[8*8] = { // um desenho aleatório só para descobrir a orientação da matriz
  0,0,0,1,1,1,1,1,
  0,0,0,0,1,1,1,1,
  0,0,0,0,1,1,1,1,
  0,0,0,1,1,1,1,1,
  0,0,1,1,1,0,0,1,
  0,1,1,1,0,0,0,0,
  1,1,1,0,0,0,0,1,
  0,1,0,0,0,0,1,1  
};

char bitmap_2[8*8] = {
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1  
};

char* bitmaps[2] = {bitmap,bitmap_2};

void setup()
{
    Serial.begin(115200);
    Serial.println("Inicializando...");

    // Desliga todos os leds
    matriz_led.Begin();
    matriz_led.Show();

    Serial.println("Rodando...");
    
}

void loop()
{
    int x,y;
    static float angulo_r=0;
    static float angulo_g=120;
    static float angulo_b=240;
    static int potencia=0;
    static char direcao=1;
    static unsigned long contador=0;
    static char atual=0;
    static char tics=0;

    for(x=0;x<8;x++){
      for(y=0;y<8;y++){
        matriz[x*8+y].R = float(bitmaps[atual][x*8+y]) * float(potencia) * abs(sin(angulo_r*(x+y+1)/4));
        matriz[x*8+y].G = float(bitmaps[atual][x*8+y]) * float(potencia) * abs(sin(angulo_g*(x+y+1)/4));
        matriz[x*8+y].B = float(bitmaps[atual][x*8+y]) * float(potencia) * abs(sin(angulo_b*(x+y+1)/4));
      };
    };

    if(millis()>=contador+10){
      angulo_r+=0.1;
      angulo_g+=0.1;
      angulo_b+=0.1;
      tics++;
      if(tics==50){ // alterna o padrão de meio em meio segundo
        tics=0;
        atual=1-atual;
      };
  
      if(angulo_r>=360.0f) angulo_r -= 360.0f;
      if(angulo_g>=360.0f) angulo_g -= 360.0f;
      if(angulo_b>=360.0f) angulo_b -= 360.0f;
      
      potencia+=direcao;
      if(potencia==0) direcao*=-1;
      if(potencia==64) direcao*=-1;

      contador=millis();
      
      for(x=0;x<8;x++){
        for(y=0;y<8;y++){
          matriz_led.SetPixelColor(x*8 + y, matriz[x*8+y]);
        };
      };
      matriz_led.Show();
    };    
}
