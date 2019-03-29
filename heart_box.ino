//We always have to include the library
#include "LedControl.h"
#include "binary.h";

/*
  Now we need a LedControl to work with.
  pin 12 is connected to the DataIn
  pin 11 is connected to the CLK
  pin 10 is connected to LOAD
 */
LedControl display = LedControl(12, 11, 10, 1);
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
  }, {
    B00000000,
    B00000000,
    B00110000,
    B01111000,
    B01111000,
    B00110000,
    B00000000,
    B00000000
  }, {
    B00000000,
    B00110000,
    B01111000,
    B11111100,
    B11111100,
    B01111000,
    B00110000,
    B00000000
  }, {
    B00011100,
    B00111110,
    B01111110,
    B11111100,
    B11111100,
    B01111110,
    B00111110,
    B00011100
  }, {
    B00001110,
    B00011111,
    B00111111,
    B01111110,
    B01111110,
    B00111111,
    B00011111,
    B00001110
  }, {
    B00011100,
    B00111110,
    B01111110,
    B11111100,
    B11111100,
    B01111110,
    B00111110,
    B00011100
  }, {
    B00011100,
    B00111110,
    B01111110,
    B11111100,
    B11111100,
    B01111110,
    B00111110,
    B00011100
  }, {
    B00001110,
    B00011111,
    B00111111,
    B01111110,
    B01111110,
    B00111111,
    B00011111,
    B00001110
  }, {
    B00011100,
    B00111110,
    B01111110,
    B11111100,
    B11111100,
    B01111110,
    B00111110,
    B00011100
  }, {
    B00011100,
    B00111110,
    B01111110,
    B11111100,
    B11111100,
    B01111110,
    B00111110,
    B00011100
  }, {
    B00000000,
    B00110000,
    B01111000,
    B11111100,
    B11111100,
    B01111000,
    B00110000,
    B00000000
  }, {
    B00000000,
    B00000000,
    B00110000,
    B01111000,
    B01111000,
    B00110000,
    B00000000,
    B00000000
  }
};
const int BEATING_HEART_LEN = sizeof(BEATING_HEART) / 8;

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
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000
  }, {
    B00000000,
    B00000000,
    B00011000,
    B00111100,
    B00111100,
    B00011000,
    B00000000,
    B00000000
  }, {
    B00000000,
    B00001000,
    B00011000,
    B01111100,
    B00111110,
    B00011000,
    B00010000,
    B00000000
  }, {
    B00001000,
    B01001010,
    B00111100,
    B11111100,
    B00111111,
    B00111100,
    B01010010,
    B00010000
  }, {
    B10011011,
    B11001010,
    B00111100,
    B11100101,
    B10100111,
    B00111100,
    B01010011,
    B11011001
  }, {
    B10111011,
    B11111110,
    B01000011,
    B11000011,
    B11000011,
    B11000010,
    B01111111,
    B11011101
  }, {
    B11111111,
    B11100111,
    B11000011,
    B10000001,
    B10000001,
    B11000011,
    B11100111,
    B11111111
  }, {
    B01100110,
    B10000001,
    B10000001,
    B00000000,
    B00000000,
    B10000001,
    B10000001,
    B01100110
  }
};
const int EXPLOSION_LEN = sizeof(EXPLOSION) / 8;

const byte MESSAGE[][8] = {
  {
    B00000000,
    B00001000,
    B00101010,
    B00011100,
    B01110111,
    B00011100,
    B00101010,
    B00001000
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00001110,
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00001110,
    B00011110,
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00001110,
    B00011110,
    B11110000,
    B11110000,
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00001110,
    B00011110,
    B11110000,
    B11110000,
    B00011110,
  }, {
    B00000000,
    B00000000,
    B00001110,
    B00011110,
    B11110000,
    B11110000,
    B00011110,
    B00001110,
  }, {
    B00000000,
    B00001110,
    B00011110,
    B11110000,
    B11110000,
    B00011110,
    B00001110,
    B00000000,
  }, {
    B00001110,
    B00011110,
    B11110000,
    B11110000,
    B00011110,
    B00001110,
    B00000000,
    B01110000,
  }, {
    B00011110,
    B11110000,
    B11110000,
    B00011110,
    B00001110,
    B00000000,
    B01110000,
    B11111000,
  }, {
    B11110000,
    B11110000,
    B00011110,
    B00001110,
    B00000000,
    B01110000,
    B11111000,
    B10001000,
  }, {
    B11110000,
    B00011110,
    B00001110,
    B00000000,
    B01110000,
    B11111000,
    B10001000,
    B10001000,
  }, {
    B00011110,
    B00001110,
    B00000000,
    B01110000,
    B11111000,
    B10001000,
    B10001000,
    B11111000,
  }, {
    B00001110,
    B00000000,
    B01110000,
    B11111000,
    B10001000,
    B10001000,
    B11111000,
    B01110000,
  }, {
    B00000000,
    B01110000,
    B11111000,
    B10001000,
    B10001000,
    B11111000,
    B01110000,
    B00000000,
  }, {
    B01110000,
    B11111000,
    B10001000,
    B10001000,
    B11111000,
    B01110000,
    B00000000,
    B01111000,
  }, {
    B11111000,
    B10001000,
    B10001000,
    B11111000,
    B01110000,
    B00000000,
    B01111000,
    B11111000,
  }, {
    B10001000,
    B10001000,
    B11111000,
    B01110000,
    B00000000,
    B01111000,
    B11111000,
    B10000000,
  }, {
    B10001000,
    B11111000,
    B01110000,
    B00000000,
    B01111000,
    B11111000,
    B10000000,
    B10000000,
  }, {
    B11111000,
    B01110000,
    B00000000,
    B01111000,
    B11111000,
    B10000000,
    B10000000,
    B11111000,
  }, {
    B01110000,
    B00000000,
    B01111000,
    B11111000,
    B10000000,
    B10000000,
    B11111000,
    B11111000,
  }, {
    B00000000,
    B01111000,
    B11111000,
    B10000000,
    B10000000,
    B11111000,
    B11111000,
    B00000010,
  }, {
    B01111000,
    B11111000,
    B10000000,
    B10000000,
    B11111000,
    B11111000,
    B00000010,
    B00001110,
  }, {
    B11111000,
    B10000000,
    B10000000,
    B11111000,
    B11111000,
    B00000010,
    B00001110,
    B00000000,
  }, {
    B10000000,
    B10000000,
    B11111000,
    B11111000,
    B00000010,
    B00001110,
    B00000000,
    B11111000,
  }, {
    B10000000,
    B11111000,
    B11111000,
    B00000010,
    B00001110,
    B00000000,
    B11111000,
    B11111000,
  }, {
    B11111000,
    B11111000,
    B00000010,
    B00001110,
    B00000000,
    B11111000,
    B11111000,
    B00001000,
  }, {
    B11111000,
    B00000010,
    B00001110,
    B00000000,
    B11111000,
    B11111000,
    B00001000,
    B00001000,
  }, {
    B00000010,
    B00001110,
    B00000000,
    B11111000,
    B11111000,
    B00001000,
    B00001000,
    B00111000,
  }, {
    B00001110,
    B00000000,
    B11111000,
    B11111000,
    B00001000,
    B00001000,
    B00111000,
    B00110000,
  }, {
    B00000000,
    B11111000,
    B11111000,
    B00001000,
    B00001000,
    B00111000,
    B00110000,
    B00000000,
  }, {
    B11111000,
    B11111000,
    B00001000,
    B00001000,
    B00111000,
    B00110000,
    B00000000,
    B01110000,
  }, {
    B11111000,
    B00001000,
    B00001000,
    B00111000,
    B00110000,
    B00000000,
    B01110000,
    B11111000,
  }, {
    B00001000,
    B00001000,
    B00111000,
    B00110000,
    B00000000,
    B01110000,
    B11111000,
    B10101000,
  }, {
    B00001000,
    B00111000,
    B00110000,
    B00000000,
    B01110000,
    B11111000,
    B10101000,
    B10101000,
  }, {
    B00111000,
    B00110000,
    B00000000,
    B01110000,
    B11111000,
    B10101000,
    B10101000,
    B00111000,
  }, {
    B00110000,
    B00000000,
    B01110000,
    B11111000,
    B10101000,
    B10101000,
    B00111000,
    B00110000,
  }, {
    B00000000,
    B01110000,
    B11111000,
    B10101000,
    B10101000,
    B00111000,
    B00110000,
    B00000000,
  }, {
    B01110000,
    B11111000,
    B10101000,
    B10101000,
    B00111000,
    B00110000,
    B00000000,
    B00000000,
  }, {
    B11111000,
    B10101000,
    B10101000,
    B00111000,
    B00110000,
    B00000000,
    B00000000,
    B00000000,
  }, {
    B10101000,
    B10101000,
    B00111000,
    B00110000,
    B00000000,
    B00000000,
    B00000000,
    B11111110,
  }, {
    B10101000,
    B00111000,
    B00110000,
    B00000000,
    B00000000,
    B00000000,
    B11111110,
    B11111110,
  }, {
    B00111000,
    B00110000,
    B00000000,
    B00000000,
    B00000000,
    B11111110,
    B11111110,
    B10010000,
  }, {
    B00110000,
    B00000000,
    B00000000,
    B00000000,
    B11111110,
    B11111110,
    B10010000,
    B10010000,
  }, {
    B00000000,
    B00000000,
    B00000000,
    B11111110,
    B11111110,
    B10010000,
    B10010000,
    B11110000,
  }, {
    B00000000,
    B00000000,
    B11111110,
    B11111110,
    B10010000,
    B10010000,
    B11110000,
    B01100000,
  }, {
    B00000000,
    B11111110,
    B11111110,
    B10010000,
    B10010000,
    B11110000,
    B01100000,
    B00000000,
  }, {
    B11111110,
    B11111110,
    B10010000,
    B10010000,
    B11110000,
    B01100000,
    B00000000,
    B01110000,
  }, {
    B11111110,
    B10010000,
    B10010000,
    B11110000,
    B01100000,
    B00000000,
    B01110000,
    B11111000,
  }, {
    B10010000,
    B10010000,
    B11110000,
    B01100000,
    B00000000,
    B01110000,
    B11111000,
    B10101000,
  }, {
    B10010000,
    B11110000,
    B01100000,
    B00000000,
    B01110000,
    B11111000,
    B10101000,
    B10101000,
  }, {
    B11110000,
    B01100000,
    B00000000,
    B01110000,
    B11111000,
    B10101000,
    B10101000,
    B00111000,
  }, {
    B01100000,
    B00000000,
    B01110000,
    B11111000,
    B10101000,
    B10101000,
    B00111000,
    B00110000,
  }, {
    B00000000,
    B01110000,
    B11111000,
    B10101000,
    B10101000,
    B00111000,
    B00110000,
    B00000000,
  }, {
    B01110000,
    B11111000,
    B10101000,
    B10101000,
    B00111000,
    B00110000,
    B00000000,
    B01000000,
  }, {
    B11111000,
    B10101000,
    B10101000,
    B00111000,
    B00110000,
    B00000000,
    B01000000,
    B11101000,
  }, {
    B10101000,
    B10101000,
    B00111000,
    B00110000,
    B00000000,
    B01000000,
    B11101000,
    B10101000,
  }, {
    B10101000,
    B00111000,
    B00110000,
    B00000000,
    B01000000,
    B11101000,
    B10101000,
    B10101000,
  }, {
    B00111000,
    B00110000,
    B00000000,
    B01000000,
    B11101000,
    B10101000,
    B10101000,
    B11111000,
  }, {
    B00110000,
    B00000000,
    B01000000,
    B11101000,
    B10101000,
    B10101000,
    B11111000,
    B11110000,
  }, {
    B00000000,
    B01000000,
    B11101000,
    B10101000,
    B10101000,
    B11111000,
    B11110000,
    B00000000,
  }, {
    B01000000,
    B11101000,
    B10101000,
    B10101000,
    B11111000,
    B11110000,
    B00000000,
    B01111000,
  }, {
    B11101000,
    B10101000,
    B10101000,
    B11111000,
    B11110000,
    B00000000,
    B01111000,
    B11111000,
  }, {
    B10101000,
    B10101000,
    B11111000,
    B11110000,
    B00000000,
    B01111000,
    B11111000,
    B10000000,
  }, {
    B10101000,
    B11111000,
    B11110000,
    B00000000,
    B01111000,
    B11111000,
    B10000000,
    B10000000,
  }, {
    B11111000,
    B11110000,
    B00000000,
    B01111000,
    B11111000,
    B10000000,
    B10000000,
    B11111000,
  }, {
    B11110000,
    B00000000,
    B01111000,
    B11111000,
    B10000000,
    B10000000,
    B11111000,
    B11111000,
  }, {
    B00000000,
    B01111000,
    B11111000,
    B10000000,
    B10000000,
    B11111000,
    B11111000,
    B00000000,
  }, {
    B01111000,
    B11111000,
    B10000000,
    B10000000,
    B11111000,
    B11111000,
    B00000000,
    B00010000,
  }, {
    B11111000,
    B10000000,
    B10000000,
    B11111000,
    B11111000,
    B00000000,
    B00010000,
    B00010000,
  }, {
    B10000000,
    B10000000,
    B11111000,
    B11111000,
    B00000000,
    B00010000,
    B00010000,
    B11111100,
  }, {
    B10000000,
    B11111000,
    B11111000,
    B00000000,
    B00010000,
    B00010000,
    B11111100,
    B11111100,
  }, {
    B11111000,
    B11111000,
    B00000000,
    B00010000,
    B00010000,
    B11111100,
    B11111100,
    B00010000,
  }, {
    B11111000,
    B00000000,
    B00010000,
    B00010000,
    B11111100,
    B11111100,
    B00010000,
    B00010000,
  }, {
    B00000000,
    B00010000,
    B00010000,
    B11111100,
    B11111100,
    B00010000,
    B00010000,
    B00000000,
  }, {
    B00010000,
    B00010000,
    B11111100,
    B11111100,
    B00010000,
    B00010000,
    B00000000,
    B10000000,
  }, {
    B00010000,
    B11111100,
    B11111100,
    B00010000,
    B00010000,
    B00000000,
    B10000000,
    B11110100,
  }, {
    B11111100,
    B11111100,
    B00010000,
    B00010000,
    B00000000,
    B10000000,
    B11110100,
    B11110100,
  }, {
    B11111100,
    B00010000,
    B00010000,
    B00000000,
    B10000000,
    B11110100,
    B11110100,
    B10000000,
  }, {
    B00010000,
    B00010000,
    B00000000,
    B10000000,
    B11110100,
    B11110100,
    B10000000,
    B00000000,
  }, {
    B00010000,
    B00000000,
    B10000000,
    B11110100,
    B11110100,
    B10000000,
    B00000000,
    B00100000,
  }, {
    B00000000,
    B10000000,
    B11110100,
    B11110100,
    B10000000,
    B00000000,
    B00100000,
    B11111100,
  }, {
    B10000000,
    B11110100,
    B11110100,
    B10000000,
    B00000000,
    B00100000,
    B11111100,
    B11111110,
  }, {
    B11110100,
    B11110100,
    B10000000,
    B00000000,
    B00100000,
    B11111100,
    B11111110,
    B00100010,
  }, {
    B11110100,
    B10000000,
    B00000000,
    B00100000,
    B11111100,
    B11111110,
    B00100010,
    B00100110,
  }, {
    B10000000,
    B00000000,
    B00100000,
    B11111100,
    B11111110,
    B00100010,
    B00100110,
    B00000100,
  }, {
    B00000000,
    B00100000,
    B11111100,
    B11111110,
    B00100010,
    B00100110,
    B00000100,
    B00000000,
  }, {
    B00100000,
    B11111100,
    B11111110,
    B00100010,
    B00100110,
    B00000100,
    B00000000,
    B01111000,
  }, {
    B11111100,
    B11111110,
    B00100010,
    B00100110,
    B00000100,
    B00000000,
    B01111000,
    B11111000,
  }, {
    B11111110,
    B00100010,
    B00100110,
    B00000100,
    B00000000,
    B01111000,
    B11111000,
    B10000000,
  }, {
    B00100010,
    B00100110,
    B00000100,
    B00000000,
    B01111000,
    B11111000,
    B10000000,
    B10000000,
  }, {
    B00100110,
    B00000100,
    B00000000,
    B01111000,
    B11111000,
    B10000000,
    B10000000,
    B11111000,
  }, {
    B00000100,
    B00000000,
    B01111000,
    B11111000,
    B10000000,
    B10000000,
    B11111000,
    B11111000,
  }, {
    B00000000,
    B01111000,
    B11111000,
    B10000000,
    B10000000,
    B11111000,
    B11111000,
    B00000000,
  }, {
    B01111000,
    B11111000,
    B10000000,
    B10000000,
    B11111000,
    B11111000,
    B00000000,
    B11111110,
  }, {
    B11111000,
    B10000000,
    B10000000,
    B11111000,
    B11111000,
    B00000000,
    B11111110,
    B11111110,
  }, {
    B10000000,
    B10000000,
    B11111000,
    B11111000,
    B00000000,
    B11111110,
    B11111110,
    B00000000,
  }, {
    B10000000,
    B11111000,
    B11111000,
    B00000000,
    B11111110,
    B11111110,
    B00000000,
    B00000000,
  }, {
    B11111000,
    B11111000,
    B00000000,
    B11111110,
    B11111110,
    B00000000,
    B00000000,
    B00000000,
  }, {
    B11111000,
    B00000000,
    B11111110,
    B11111110,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  }, {
    B00000000,
    B11111110,
    B11111110,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  }, {
    B11111110,
    B11111110,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  }, {
    B11111110,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  }
};
const int MESSAGE_LEN = sizeof(MESSAGE) / 8;

int ANIMATION_LEN = BEATING_HEART_LEN; // starting position

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); // enable pullup resistor

  display.clearDisplay(0);
  display.shutdown(0, false);
  display.setIntensity(0, 10);
}

void displayImage(const byte* image) {
  for (int i = 0; i < 8; i++) {
    display.setRow(0, i, image[i]);
  }
}

// animation variables
int animFrame = 0;
unsigned long animTime = 0;     // the last time we animated
unsigned long animDelay = 250;  // milliseconds between animation calls
unsigned long millisecs = 0;    // a millis() time-slice

// button timing variables
int hold_type = 0;
int firsttime = 1;
unsigned long startTime;
unsigned long pressTime;

void loop() {
  millisecs = millis();

  // read the state of the pushbutton value:
  int  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is LOW:
  if (buttonState == LOW) {
    if (firsttime == 1) {
      startTime = millisecs;
      firsttime = 0;
    }

    pressTime = millisecs - startTime;
    if (pressTime > 3000) {
      // 3 sec hold
      hold_type = 3;
      ANIMATION_LEN = MESSAGE_LEN;
      Serial.println("message");

    } else if (pressTime > 2000) {
      // 2 sec hold
      ANIMATION_LEN = BEATING_HEART_LEN;
      // repeat = 0;
      hold_type = 2;
      Serial.println("beating heart repeat");

    } else if (pressTime > 1000) {
      // 1 sec hold
      ANIMATION_LEN = EXPLOSION_LEN;
      Serial.println("explosion");
      hold_type = 1;

    } else {
      // quick press
      ANIMATION_LEN = BEATING_HEART_LEN;
      Serial.println("beating heart");
      hold_type = 0;
    }
    animFrame = 0;

  } else {
    if (firsttime == 0) {
      firsttime = 1;
    }
  }

  if ( animTime + animDelay < millisecs ) {
    animTime = millisecs;

    // animate
    if (hold_type == 0) {
      displayImage(BEATING_HEART[animFrame]);

    } else if (hold_type == 1) {
      displayImage(EXPLOSION[animFrame]);

    } else if (hold_type == 2) {
      displayImage(BEATING_HEART[animFrame]);

    } else if (hold_type == 3) {
      displayImage(MESSAGE[animFrame]);
    }
    if (++animFrame >= ANIMATION_LEN ) {
      // looping, or not
      animFrame = 0;
    }
  }
}
