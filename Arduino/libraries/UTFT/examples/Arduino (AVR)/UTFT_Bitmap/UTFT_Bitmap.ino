// UTFT_Bitmap 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of the drawBitmap()-function.
//
// This demo was made to work on the 320x240 modules.
// Any other size displays may cause strange behaviour.
//
// This program requires the UTFT library.
//

#include <UTFT.h>
#include <avr/pgmspace.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];

// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Arduino Uno / 2009:
// -------------------
// Standard Arduino Uno/2009 shield            : <display model>,A5,A4,A3,A2
// DisplayModule Arduino Uno TFT shield        : <display model>,A5,A4,A3,A2
//
// Arduino Mega:
// -------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Mega      : <display model>,38,39,40,41
//
// Remember to change the model parameter to suit your display module!
//UTFT myGLCD(ITDB32S,A5,A4,A3,A2);
UTFT myGLCD(ITDB32S,38,39,40,41);


extern unsigned int info[0x400];
extern unsigned int icon[0x400];
extern unsigned int tux[0x400];

typedef enum{
  redTurn,
  greenTurn,
  blueTurn,
  xCoordTurn,
  yCoordTurn,
  pauseTurn
} ParseState;


void setup()
{
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
}

void setPixRGB(String red, String green, String blue, String x, String y){

  int x_i     = x.toInt();
  int y_i     = y.toInt();

  // if( red.length()   > 3 ||
  //     green.length() > 3 ||
  //     blue.length()  > 3 ||
  //     x_i > 320          ||
  //     x_i < 0            ||
  //     x.length()     > 3 ||
  //     y_i > 320          ||
  //     y_i < 0            ||
  //     y.length()     > 3 ){

  //    myGLCD.setColor(globalRed, globalGreen, globalBlue);
  //    myGLCD.drawPixel(globalX, globalY);

  // }
  // else {
    int red_i   = red.toInt();
    int green_i = green.toInt();
    int blue_i  = blue.toInt();

    myGLCD.setColor(red_i ,green_i, blue_i);
    myGLCD.drawPixel(x_i, y_i);

  //  Serial.print("R:");
  //  Serial.print(red);
//
//  //  Serial.print(" G:");
//  //  Serial.print(green);
//
//  //  Serial.print(" B:");
//  //  Serial.print(blue);
//
//  //  Serial.print(" x:");
//  //  Serial.print(x);
//
//  //  Serial.print(" y:");
//  //  Serial.println(y);
//





  }
}



void loop(){

  ParseState pstate = pauseTurn;


  for( int i = 0; i < data.length(); i++){
// start with a pixel-definition
    if (ic == '#'){ pstate = redTurn; delay(1); continue; }

// red-part - if '$' then parse green-part
    if (pstate == redTurn){
      if (ic == '$') { pstate = greenTurn; delay(1); continue; }
      else           { red += ic;          delay(1); continue;}
    }

// green-part - if '$' then parse blue-part
    if (pstate == greenTurn){
      if (ic == '$') { pstate = blueTurn; delay(1); continue; }
      else           { green += ic;       delay(1); continue; }
    }

// blue-part - if '$' then parse x-Coordinates
    if (pstate == blueTurn){
      if (ic == '$') { pstate = xCoordTurn; delay(1); continue; }
      else           { blue += ic;          delay(1); continue; }
    }

// x-Coordinates  - if '$' then parse y-Coordinates
    if (pstate == xCoordTurn){
      if (ic == '$') { pstate = yCoordTurn; delay(1); continue; }
      else           { x += ic;             delay(1); continue; }
    }

// y-Coordinates  - if '*' then draw a pixel with the color and reset the Strings

    if (pstate == yCoordTurn){
      if (ic == '*') {
        pstate = pauseTurn;
        setPixRGB(red, green, blue, x, y);
        red = "";
        green = "";
        blue = "";
        x = "";
        y = "";
        delay(1);
        continue;
      } else {
          y += ic;
          delay(1);
          continue;
        }
    }

   }

//   myGLCD.fillScr(255, 255, 255);
//   myGLCD.setColor(255, 255, 255);
//   myGLCD.print(" *** A 10 by 7 grid of a 32x32 icon *** ", CENTER, 228);
//   for (int x=0; x<10; x++)
//     for (int y=0; y<7; y++)
//       myGLCD.drawBitmap (x*32, y*32, 32, 32, info);

//   delay(5000);
  
//   myGLCD.fillScr(255, 255, 255);
//   myGLCD.setColor(255, 255, 255);
//   myGLCD.print("   Two different icons in scale 1 to 4  ", CENTER, 228);
//   int x=0;
//   for (int s=0; s<4; s++)
//   {
//     x+=(s*32);
//     myGLCD.drawBitmap (x, 0, 32, 32, tux, s+1);
//   }
//   x=0;
//   for (int s=4; s>0; s--)
//   {
//     myGLCD.drawBitmap (x, 224-(s*32), 32, 32, icon, s);
//     x+=(s*32);
//   }

  delay(100000);
}


