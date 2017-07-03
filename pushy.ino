#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strand( 120, 7, NEO_GRB+NEO_KHZ800);
int sensorValue;
int normalValue=0;
int topPixel = 0;
bool flashOn = 0;

void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT);
  pinMode(7,OUTPUT);
  strand.begin();
}

void loop() {

  sensorValue = analogRead(A0);

  if( digitalRead( 3 ) == LOW ) {
    normalValue = sensorValue;
    topPixel = 0;
  }
  Serial.print(sensorValue-normalValue);
  Serial.print(", ");

  if( normalValue == 0 ) { // button hasn't been pressed yet.
    if( flashOn == 0 ) { strand.setPixelColor( 0, 0, 0, 255 ); flashOn = 1; }
    else { strand.setPixelColor( 0, 0, 0, 0 ); flashOn = 0; }
  }
  else {
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
