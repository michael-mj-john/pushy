#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strand( 120, 7, NEO_GRB+NEO_KHZ800);

int leftPixel = 0;    // index of left pixel
int leftSensor;       // input from left sensor
int leftNormal = 0;   // normal value for left player

int rightPixel = 119; // index of right pixel
int rightSensor;      // input from right sensor
int rightNormal = 0;  // normal value for right player 

bool gameStart = 0; // game state
bool flashOn = 0; // flash indicator

void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT); // left button 
  pinMode(4, INPUT); // right button
  pinMode(7,OUTPUT); // lights
  strand.begin();
}

void loop() {

  // read sensor input
  leftSensor = analogRead(A0);
  rightSensor = analogRead(A1);

  Serial.print( leftSensor - leftNormal );
  Serial.print( ", " );
  Serial.print( rightSensor - rightNormal);
  Serial.print( "\n" );
  
  if(!gameStart)
  {
     // set normal values with button presses
    if( digitalRead(3) == LOW ) leftNormal = leftSensor;
    if( digitalRead(4) == LOW) rightNormal = rightSensor;

    // flash pixels at each end
    if(flashOn)
    {
      if(leftNormal == 0) strand.setPixelColor( 0, 0, 0, 255 ); 
      if(rightNormal == 0) strand.setPixelColor( 119, 0, 0, 255);
      flashOn = 0; 
    } else  { 
      if(leftNormal == 0) strand.setPixelColor( 0, 0, 255, 255 ); 
      if(rightNormal == 0) strand.setPixelColor(119, 0, 255, 255);
      flashOn = 1; 
    }

    // if a button has been pressed, stop flashing
    if(leftNormal != 0) strand.setPixelColor(0, 255, 0, 0);
    if(rightNormal != 0) strand.setPixelColor(119, 0, 255, 0);

    // both buttons have been pressed
    if(leftNormal != 0 && rightNormal != 0) gameStart = 1;
  } 
  else {
    playerUpdate(); // update the state of both players
    ledUpdate(); // Pixels update

    /* NEEDS FIXING --------------------------------------------------------------------
    // check for win
    if(leftPixel == 119 || rightPixel == 0)
    {
      if(flashOn)
      {
        for(int i = 0; i < 119; ++i) strand.setPixelColor(i, 0, 0, 0);
      } else {
        if(leftPixel == 119) //left side wins 
        {
          for(int i = 0; i < 119; ++i) strand.setPixelColor(i, 255, 0, 0);
        } 
        else if (rightPixel == 0) //right side wins
        {
          for(int i = 0; i < 119; ++i) strand.setPixelColor(i, 0, 255, 0);
        }
      }
  
    gameStart = 0;
    leftNormal = 0;
    rightNormal = 0;      
    }

    */ ----------------------------------------------------------------------------------
  }

  strand.show();
  delay(200);
  
}
