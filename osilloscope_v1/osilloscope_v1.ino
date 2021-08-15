#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <IRremote.h>
int IR_RECEIVE_PIN = 15;
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define VOL1BUTT 2
#define VOL2BUTT 3
#define probepin 34
#define PLAY_BUTT 49
#define STOP_BUTT 57
#define OLED_RESET 4
#define UP_BUTT 71
#define LEFT_BUTT 89
#define RIGHT_BUTT 90
#define DOWN_BUTT 72
#define ENTER_BUTT 88
int probvalue;
int res=4095;
int x=0;
int i=0;
int y;
int volt;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void setup() {
  Serial.begin(9600);
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver, enable feedback LED, take LED feedback pin from the internal boards definition

    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);
display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
display.clearDisplay();
delay(1);

}

void loop() {
probvalue = analogRead(probepin);
probvalue = map(probvalue, 0, res, 63, 10);//4095
volt = map(y, 63, 10, 0, 5);
y=probvalue;
if( IrReceiver.decodedIRData.command == PLAY_BUTT  ){
display.drawPixel(x,y, WHITE);
x=x+1;
display.display();
}
if(x==128){
x=0;
display.setCursor(0,0);
if( IrReceiver.decodedIRData.command == PLAY_BUTT  ){
display.clearDisplay(); 
   
}
if(IrReceiver.decodedIRData.command == VOL1BUTT){
res=res+500;
   
}
if(IrReceiver.decodedIRData.command == VOL2BUTT){
res=res-500;
   
}
display.setTextColor(WHITE);
display.setTextSize(1);
display.println(volt);
Serial.println(res);
  }

if(res<4095){
res=4095;  
  }
if (IrReceiver.decode()) { 
      IrReceiver.resume();                             
}    
}
