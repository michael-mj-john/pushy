#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strand( 120, 7, NEO_GRB+NEO_KHZ800);
int sensorValue;
int normalValue=0;
int leftPixel = 0;
int rightPixel = 119;
bool flashOn = 0;

void setup() {
  Serial.begin(9600);
  pinMode(4,INPUT);
  pinMode(7,OUTPUT);
  strand.begin();
}

void loop() {

  sensorValue = analogRead(A0);

  if( digitalRead( 4 ) == LOW ) {
    normalValue = sensorValue;
    leftPixel = 0;
  }
  Serial.print(sensorValue-normalValue);
  Serial.print(", ");

  if( normalValue == 0 ) { // button hasn't been pressed yet.
    if( flashOn == 0 ) { strand.setPixelColor( 0, 0, 0, 255 ); flashOn = 1; }
    else { strand.setPixelColor( 0, 0, 0, 0 ); flashOn = 0; }
  }
  else {
    ledUpdate();
  }

  if( sensorValue - normalValue > 100 ) { leftPixel = min(leftPixel + 1, 120); }
  if( sensorValue - normalValue > 200 ) { leftPixel = min(leftPixel + 1, 120); }
  if( sensorValue - normalValue > 250 ) { leftPixel = min(leftPixel + 1, 120); }
  else { leftPixel = max(leftPixel-1, 0 ); }
  if( leftPixel >= rightPixel ) { 
    sensorValueL > sensorValueR ? rightPixel = leftPixel : leftPixel = rightPixel;
  }

  Serial.print( normalValue );
  Serial.print( "\n" );

  delay(40);
  

}
