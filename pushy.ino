#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strand( 120, 7, NEO_GRB+NEO_KHZ800);
int sensorValueL;
int sensorValueR;

int normalValueL = 0;
int normalValueR = 0;

int leftPixel = 0;
int rightPixel = 0;

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

  // left button is pressed, set sensor at left end
  if( digitalRead( 3 ) == LOW ) {
    normalValueL = sensorValueL;
    leftPixel = 0;
  }

  // right button is pressed, set sensor at right end
  if( digitalRead(4) == LOW) {
    normalValueR = sensorValueR;
    rightPixel = 119;
  }
  
  Serial.print(sensorValue-normalValue);
  Serial.print(", ");

  // buttons have not been pressed, blink light at each end
  if( normalValueL == 0  && normalValueR ==0) 
  { 
    if( flashOn == 0 ) 
    { 
      strand.setPixelColor( 0, 0, 0, 255 ); 
      strand.setPixelColor( 119, 0, 0, 255);
      flashOn = 1; 
    }
    else 
    { 
      strand.setPixelColor( 0, 0, 0, 0 ); 
      strand.setPixelColor(119, 0, 0, 0);
      flashOn = 0; 
    }
  }
  else {
    // Pixel update
    for( int i=0; i< 120; i++ ) {
      if( i > topPixel ) { strand.setPixelColor(i, 0, 0, 0); }
      else { strand.setPixelColor( i, 255, 0, 0 ); }
    }
  }
  strand.show();

  if( sensorValue - normalValue > 100 ) { topPixel = min(topPixel + 1, 120); }
  if( sensorValue - normalValue > 200 ) { topPixel = min(topPixel + 1, 120); }
  if( sensorValue - normalValue > 250 ) { topPixel = min(topPixel + 1, 120); }
  else { topPixel = max(topPixel-1, 0 ); }

  Serial.print( normalValue );
  Serial.print( "\n" );

  delay(40);
  

}
