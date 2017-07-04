#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strand( 120, 7, NEO_GRB+NEO_KHZ800);

int leftPixel = 0;
int rightPixel = 119;
int sensorValueL;
int sensorValueR;
int normalValueL = 0;
int normalValueR = 0;

bool flashOn = 0;

void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT); // button L
  pinMode(4, INPUT); // button R
  pinMode(7,OUTPUT); // lights
  strand.begin();
}

void loop() {

  // read sensor input
  sensorValueL = analogRead(A0);
  sensorValueR = analogRead(A1);

  // left button is pressed, set normal value at left end
  if( digitalRead(3) == LOW ) {
    normalValueL = sensorValueL;
    leftPixel = 0;
  }

  // right button is pressed, set normal value at right end
  if( digitalRead(4) == LOW) {
    normalValueR = sensorValueR;
    rightPixel = 119;
  }
  
  Serial.print(sensorValueL-normalValueL);
  Serial.print(", ");
  Serial.print(sensorValueR-normalValueR); 
  Serial.print("\n");

  // buttons have not been pressed, blink light at each end
  if( normalValueL == 0  && normalValueR ==0) { 
    if( flashOn == 0 ) { 
      strand.setPixelColor( 0, 0, 0, 255 ); 
      strand.setPixelColor( 119, 0, 0, 255);
      flashOn = 1; 
    }
    else  { 
      strand.setPixelColor( 0, 0, 0, 0 ); 
      strand.setPixelColor(119, 0, 0, 0);
      flashOn = 0; 
    }
  }
  else {
    playerUpdate(); // update the state of both players
    ledUpdate(); // Pixels update
  }

  delay(200);
  
}
