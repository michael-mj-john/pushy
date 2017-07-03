void ledUpdate ( void ) {
  
  // update left player
  for( int i=0; i< 120; i++ ) {
      if( i > leftPixel ) { strand.setPixelColor(i, 0, 0, 0); }
      else { strand.setPixelColor( i, 255, 0, 0 ); }
    }

  // update right player
  for( int i=119; i >=0 ; i-- ) {
    if( i < rightPixel ) { strand.setPixelColor(i, 0, 0, 0); }
    else { strand.setPixelColor( i, 0, 255, 0 ); }
  }
  // if the two players' lines have met, turn that point white
  if( leftPixel == rightPixel ) {
    strand.setPixelColor(leftPixel, 255, 255, 255 );
  }

  strand.show();
}
