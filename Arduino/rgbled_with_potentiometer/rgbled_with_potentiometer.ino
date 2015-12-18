// rgbled_with_potentiometer.ino

// #include <UTFT.h>
// #include <memorysaver.h>

#define RED   9
#define GREEN 10
#define BLUE  11

typedef struct{
  float r;
  float g;
  float b;
} RGB;

RGB* rgbsX;


void setup() {

  pinMode( RED  , OUTPUT );
  pinMode( GREEN, OUTPUT );
  pinMode( BLUE , OUTPUT );

  rgbsX = (RGB*) malloc( sizeof( RGB ) );

}


void loop() {

  // changed to fit for MEGA

  int serial = analogRead( 8 );
  setColor( toRGB ( (float) serial, rgbsX ));

}


void blink( int pin ){

  analogWrite( pin, 100 );
  delay( 100 );
  analogWrite( pin, 0 );

}


void setColor( RGB* rgbs ){

  analogWrite(RED,   (int) rgbs -> r);
  analogWrite(GREEN, (int) rgbs -> g);
  analogWrite(BLUE,  (int) rgbs -> b);

}

/*
 * 0   - 255         -> red   (0 - 255)
 * 255 - 405 - (510) -> green (0 - 150)
 * 510 - 655 - (765) -> blue  (0 - 150)
 * 765 - 1030        -> only green & blue
 */
RGB* toRGB( float serial, RGB* rgbValue ){

  if (serial <= 255) {
    rgbValue -> r = serial;
    rgbValue -> g = 0;
    rgbValue -> b = 0;
    return rgbValue;
  }

  if (serial <= 510) {
    rgbValue -> r = 255;
    rgbValue -> g = ( serial - 255 ) ;
    rgbValue -> b = 0;
    return rgbValue;
  }

  if (serial <= 765) {
    rgbValue -> r = 255;
    rgbValue -> g = 255;
    rgbValue -> b = ( serial - 510 ) ;
    return rgbValue;
  }

  if (serial <= 1020) {
    rgbValue -> r = 255 - ( serial - 765 );
    rgbValue -> g = 255;
    rgbValue -> b = 255;
    return rgbValue;
  }

    rgbValue -> r = 0;
    rgbValue -> g = 127;
    rgbValue -> b = 127;
    return rgbValue;

  //rgbValue -> r = (min( serial,255 ) / 255) * 255;
  //rgbValue -> g = (min( serial,510 ) / 510) * 255;
  //rgbValue -> b = (min( serial,765 ) / 765) * 255;
}