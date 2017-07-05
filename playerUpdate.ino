void playerUpdate( void ) {

  int playerL = sensorValueL - normalValueL;
  int playerR = sensorValueR - normalValueR;

// update left player
  if( playerL < 100 ) { leftPixel = max(leftPixel - 1, 0 ); } 
  else {
    if( playerL > 100 ) { leftPixel = min(leftPixel + 1, 119); }
    if( playerL > 200 ) { leftPixel = min(leftPixel + 1, 119); }
    if( playerL > 250 ) { leftPixel = min(leftPixel + 1, 119); }
  }


// update right player
  if( playerR < 100 ) { rightPixel = min(rightPixel +1, 119); }
  else {
    if( playerR > 100 ) { rightPixel = max(rightPixel - 1, 0); }
    if( playerR > 200 ) { rightPixel = max(rightPixel - 1, 0); }
    if( playerR > 250 ) { rightPixel = max(rightPixel - 1, 0); }    
  }

  if( leftPixel >= rightPixel ) { 
    playerL > playerR ? rightPixel = leftPixel : leftPixel = rightPixel;
  }

  Serial.print( leftPixel );
  Serial.print( ", " );
  Serial.print( rightPixel);
  Serial.print( "\n" );
}
