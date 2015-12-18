// eeprom_math_parser.ino

// #include "Parser.c"

#define RED 9

// char* input;


void setup() {

  Serial.begin( 9600 );
  pinMode( RED, OUTPUT);

//  input = malloc ( 10 * sizeof(char) );
}

void loop() {

  // if( Serial.available() ){

  //   Serial.readString().toCharArray( input, 10 );

  //   int result = parse( input );

  //   while( result != 0 ){
  //     blink( RED );
  //     result--;
  //   }

  // }

}


void blink( int pin ){

  analogWrite( pin, HIGH );
  delay( 100 );
  analogWrite( pin, LOW );

}