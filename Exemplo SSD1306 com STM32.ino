#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306_STM32.h>
/*
 * Nota: este exemplo usa a biblioteca SoftWire no lugar da HardWire pra rodar na Black Pill usando
 * o mesmo barramento I2C da memória EEPROM que tem na placa. Na Maple Mini basta ligar os pinos
 * onde estiver marcado I2C1, sem modificar nenhum arquivo.
 * Pra usar o I2C1 hardware (PB6 SCL e PB7 SDA) pode pular essa parte, mas são necessários dois resistores de 
 * pull up de 10k nessas duas linhas
 * 
 * Pra funcionar, é necessário editar o arquivo
 * Adafruit_SSD1306_STM32.cpp dessa forma:
 * 
 * #include <SoftWire.h>
 * SoftWire SW(PB4,PB6,SOFT_STANDARD); // mesmos pinos da EEPROM da Black Pill
 * #define Wire SW
 *
 * esse define faz com que a biblioteca utilize a interface I2C soft no lugar da hardware
 * também podem ser utilizados quaisquer outros pinos
 */
unsigned char invertido=0;
unsigned int contador_a=12345;
unsigned int contador_b=31345;
char rolante_x=0;
char rolante_dir=4;
Adafruit_SSD1306 display(4); // 4 é um pino de reset que a biblioteca pede, que no caso não é utilizado por este módulo
void desenhaCabecalho(){
  if(invertido){
    display.fillRect(0,0,128,16,WHITE);
    display.setTextColor(BLACK);
  }else{
    display.fillRect(0,0,128,16,BLACK);
    display.setTextColor(WHITE);
  };
  display.setTextSize(2);
  display.setCursor(1,1);
  display.println("CABECALHO");
}
void desenhaNumeros(){
  if(invertido){
    display.fillRect(0,16,128,48,WHITE);
    display.setTextColor(BLACK);    
  }else{
    display.fillRect(0,16,128,48,BLACK);
    display.setTextColor(WHITE);    
  };
  display.setTextSize(2);
  display.setCursor(1,18);
  display.print("VarA h"); display.println(contador_a,HEX);  
  display.setCursor(1,34);
  display.print("VarB h"); display.println(contador_b,HEX);  
  display.setTextSize(1);
  display.setCursor(1-rolante_x,51);
  display.print("Texto rolando aqui em baixo");
  
}
void cls(){
  display.clearDisplay();
}
void flip(){
  display.display();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PA0,INPUT); // entrada flutuando pra ter valores aleatorios
  Serial.begin(115200); // na maple mini / black pill tanto importa o baud
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.setTextWrap(false);

  cls();
  desenhaCabecalho();
  desenhaNumeros();
  flip();
};

void loop() {
  static unsigned long temporizador_display=0;
  // put your main code here, to run repeatedly:
  contador_b = analogRead(PA0);
  if(millis() >= temporizador_display + 25){
    rolante_x = rolante_x + rolante_dir;
    if( (rolante_x > 40)  | (rolante_x < 1)){
      rolante_dir *= -1;
      invertido=1-invertido;
      desenhaCabecalho();
    };
    contador_a = random(32000);
    desenhaNumeros();
    flip();
    temporizador_display=millis();
  }
}
