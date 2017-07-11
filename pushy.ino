#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strand( 120, 7, NEO_GRB+NEO_KHZ800);

int leftPixel = 0;    // index of left pixel
int leftSensor;       // input from left sensor
int leftNormal = 0;   // normal value for left player

int rightPixel = 119; // index of right pixel
int rightSensor;      // input from right sensor
int rightNormal = 0;  // normal value for right player 

enum gameStates { PREP, PLAY, POST };
enum gameStates gameState = PREP; // game state

bool flashOn = 0; // flash indicator

void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT); // left button 
  pinMode(4, INPUT); // right button
  pinMode(5, INPUT); // reset button
  
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

  // if reset button has been pressed, reset
  if(digitalRead(5) == LOW) reset();
 

  if(gameState == PREP) // game prep state
  {    
    // set normal values with button presses
    if( digitalRead(3) == LOW ) leftNormal = leftSensor;
    if( digitalRead(4) == LOW) rightNormal = rightSensor;

    ledUpdate();

    // both buttons have been pressed, start game
    if(leftNormal != 0 && rightNormal != 0) gameState = PLAY;
  } 
  else if (gameState == PLAY) // play state
  {
    playerUpdate();
    ledUpdate();

    // a player has won the game
    if(leftPixel == 119 || rightPixel == 0) gameState = POST;
  } 
  else if (gameState == POST) // post game state
  {
    ledUpdate();
    
    reset();
  }

  strand.show();
  delay(200);
}

// reset game and enter PREP state
void reset()
{
  leftPixel = 0;
  rightPixel = 119;
  leftNormal = 0;
  rightNormal = 0;
  gameState = PREP;
}

