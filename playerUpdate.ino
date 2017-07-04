void playerUpdate( void ) {

// update left player
  if( sensorValueL - normalValueL > 100 ) { leftPixel = min(leftPixel + 1, 119); }
  if( sensorValueL - normalValueL > 200 ) { leftPixel = min(leftPixel + 1, 119); }
  if( sensorValueL - normalValueL > 250 ) { leftPixel = min(leftPixel + 1, 119); }
  if( sensorValueL - normalValueL < 100 ) { leftPixel = max(leftPixel - 1, 0 ); }
// update right player
  if( sensorValueR - normalValueR > 100 ) { rightPixel = max(rightPixel - 1, 0); }
  if( sensorValueR - normalValueR > 200 ) { rightPixel = max(rightPixel - 1, 0); }
  if( sensorValueR - normalValueR > 250 ) { rightPixel = max(rightPixel - 1, 0); }
  if( sensorValueR - normalValueR < 100 ) { rightPixel = min(rightPixel +1, 119); }
  if( leftPixel >= rightPixel ) { 
    sensorValueL - normalValueL > sensorValueR - normalValueR ? rightPixel = leftPixel : leftPixel = rightPixel;
  }

  Serial.print( leftPixel );
  Serial.print( ", " );
  Serial.print( rightPixel);
  Serial.print( "\n" );
}
