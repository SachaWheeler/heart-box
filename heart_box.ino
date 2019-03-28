//We always have to include the library
#include "LedControl.h"
#include "binary.h";

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 */
LedControl display=LedControl(12, 11, 10, 1);
const int buttonPin = 5; 
int buttonStage = 0;

const byte BEATING_HEART[][8] = {
{
  B00000000,
  B00000000,
  B00000000,
  B00110000,
  B00110000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00110000,
  B01111000,
  B01111000,
  B00110000,
  B00000000,
  B00000000
},{
  B00000000,
  B00110000,
  B01111000,
  B11111100,
  B11111100,
  B01111000,
  B00110000,
  B00000000
},{
  B00011100,
  B00111110,
  B01111110,
  B11111100,
  B11111100,
  B01111110,
  B00111110,
  B00011100
},{
  B00001110,
  B00011111,
  B00111111,
  B01111110,
  B01111110,
  B00111111,
  B00011111,
  B00001110
},{
  B00011100,
  B00111110,
  B01111110,
  B11111100,
  B11111100,
  B01111110,
  B00111110,
  B00011100
},{
  B00011100,
  B00111110,
  B01111110,
  B11111100,
  B11111100,
  B01111110,
  B00111110,
  B00011100
},{
  B00001110,
  B00011111,
  B00111111,
  B01111110,
  B01111110,
  B00111111,
  B00011111,
  B00001110
},{
  B00011100,
  B00111110,
  B01111110,
  B11111100,
  B11111100,
  B01111110,
  B00111110,
  B00011100
},{
  B00011100,
  B00111110,
  B01111110,
  B11111100,
  B11111100,
  B01111110,
  B00111110,
  B00011100
},{
  B00000000,
  B00110000,
  B01111000,
  B11111100,
  B11111100,
  B01111000,
  B00110000,
  B00000000
},{
  B00000000,
  B00000000,
  B00110000,
  B01111000,
  B01111000,
  B00110000,
  B00000000,
  B00000000
}};
const int BEATING_HEART_LEN = sizeof(BEATING_HEART)/8;

// explosion
const byte EXPLOSION[][8] = {
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00011000,
  B00111100,
  B00111100,
  B00011000,
  B00000000,
  B00000000
},{
  B00000000,
  B00001000,
  B00011000,
  B01111100,
  B00111110,
  B00011000,
  B00010000,
  B00000000
},{
  B00001000,
  B01001010,
  B00111100,
  B11111100,
  B00111111,
  B00111100,
  B01010010,
  B00010000
},{
  B10011011,
  B11001010,
  B00111100,
  B11100101,
  B10100111,
  B00111100,
  B01010011,
  B11011001
},{
  B10111011,
  B11111110,
  B01000011,
  B11000011,
  B11000011,
  B11000010,
  B01111111,
  B11011101
},{
  B11111111,
  B11100111,
  B11000011,
  B10000001,
  B10000001,
  B11000011,
  B11100111,
  B11111111
},{
  B01100110,
  B10000001,
  B10000001,
  B00000000,
  B00000000,
  B10000001,
  B10000001,
  B01100110
}};
const int EXPLOSION_LEN = sizeof(EXPLOSION)/8;




/* we always wait a bit between updates of the display */
unsigned long delaytime=300;


void setup() {
  Serial.begin(9600); 
  pinMode(buttonPin, INPUT);
    
  display.clearDisplay(0);
  display.shutdown(0, false);
  display.setIntensity(0, 10);
}

void displayImage(const byte* image) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bitRead(image[i], 7 - j));
    }
  }
}

int animFrame = 0;

unsigned long animTime = 0;   // the last time we processed doBlink()
unsigned long animDelay = 333;  // milliseconds between animation calls
unsigned long millisecs = 0;    // a millis() time-slice

int firsttime = 1;
unsigned long startTime;
unsigned long pressTime;

void loop() {
  millisecs = millis();
  // read the state of the pushbutton value:
  int  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    if(firsttime == 1){
      startTime = millisecs;
      firsttime=0;
     }
     pressTime = millisecs - startTime;
     if(pressTime >= 1){
      Serial.print("Time: ");
      Serial.print(pressTime);
      Serial.print(" milliseconds ");
      Serial.print(int(pressTime/1000));
      Serial.println(" seconds");
     }
     if(pressTime >3000){
      Serial.println(">3 seconds");
     }    
    //Serial.print("Pressed\n");      
  } else {
    if(firsttime == 0){
      firsttime = 1;
      Serial.println("Time: 0 milleseconds; 0 seconds");
    }
  }

  if ( animTime + animDelay < millisecs ) {
    animTime = millisecs;

    // animate
    displayImage(BEATING_HEART[animFrame]);
    if (++animFrame >= BEATING_HEART_LEN ) {
      animFrame = 0;
    }
  }
}
