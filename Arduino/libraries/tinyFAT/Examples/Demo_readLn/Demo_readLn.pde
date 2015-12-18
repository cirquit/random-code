// Demo_readLn 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of the readLn()-function.
//
// This demo will open a textfile named 'TEXTFILE.TXT'
// and display its contents in the Serial Monitor.
//
// SD card must be connected to the SPI port of your Arduino.
//
// Remember to select 115200 baud in the Serial Monitor.
//
#include <UTFT.h>
#include <tinyFAT.h>
#include <avr/pgmspace.h>

typedef enum{
  redTurn,
  greenTurn,
  blueTurn,
  xCoordTurn,
  yCoordTurn,
  pauseTurn
} ParseState;

/*
 * Global data for the 3.2" Display
 */
#define RS 38
#define WR 39
#define CS 40
#define RSET 41

extern uint8_t SmallFont[];              // which font to use
UTFT myGLCD(ITDB32S, RS, WR, CS, RSET);  // PIN Setup (<model code>, SDA, SCL, CS, RST)



byte res;
word result;
char textBuffer[81];

char *verboseError(byte err)
{
	switch (err)
	{
	case ERROR_MBR_READ_ERROR:
		return "Error reading MBR";
		break;
	case ERROR_MBR_SIGNATURE:
		return "MBR Signature error";
		break;
	case ERROR_MBR_INVALID_FS:
		return "Unsupported filesystem";
		break;
	case ERROR_BOOTSEC_READ_ERROR:
		return "Error reading Boot Sector";
		break;
	case ERROR_BOOTSEC_SIGNATURE:
		return "Boot Sector Signature error";
		break;
	default:
		return "Unknown error";
		break;
	}
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

    // Serial.print("R:");
    // Serial.print(red);

    // Serial.print(" G:");
    // Serial.print(green);

    // Serial.print(" B:");
    // Serial.print(blue);

    // Serial.print(" x:");
    // Serial.print(x);

    // Serial.print(" y:");
    // Serial.println(y);

    // globalRed   = red_i;
    // globalGreen = green_i;
    // globalBlue  = blue_i;
    // globalX     = x_i;
    // globalY     = y_i;
  //}
}




void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
  Serial.println();

/*
 * Setup the LCD
 */

  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  myGLCD.clrScr();

/*
 * Enable the I/O pins for the LCD
 */

  pinMode(RS,   OUTPUT);
  pinMode(WR,   OUTPUT);
  pinMode(CS,   OUTPUT);
  pinMode(RSET, OUTPUT);


  String red;
  String green;
  String blue;
  String x;
  String y;

  ParseState pstate = pauseTurn;

  // Initialize tinyFAT 
  // You might need to select a lower speed than the default SPISPEED_HIGH
  res=file.initFAT(); 
  if (res!=NO_ERROR)
  {
    Serial.print("***** ERROR: ");
    Serial.println(verboseError(res));
    while (true) {};
  }

  Serial.println("This demo will display a textfile called 'TEXTFILE.TXT'");
  Serial.println();
  Serial.println("***** Send any character to start *****");
  while (!Serial.available()) {};
  Serial.flush();
  Serial.println();
  Serial.println();
  
  if (file.exists("clouds2.txt"))
  {  
    res=file.openFile("clouds2.txt", FILEMODE_TEXT_READ);
    if (res==NO_ERROR)
    {
      result=0;
      while ((result!=EOF) and (result!=FILE_IS_EMPTY))
      {
        result=file.readLn(textBuffer, 80);
        if (result!=FILE_IS_EMPTY){

            for(int i = 0; i < 80; i++){
              char ic = textBuffer[i];
            // start with a pixel-definition
                if (ic == '#'){ pstate = redTurn; /*delay(1);*/ continue; }

            // red-part - if '$' then parse green-part
                if (pstate == redTurn){
                  if (ic == '$') { pstate = greenTurn; /*delay(1);*/ continue; }
                  else           { red += ic;          /*delay(1);*/ continue;}
                }

            // green-part - if '$' then parse blue-part
                if (pstate == greenTurn){
                  if (ic == '$') { pstate = blueTurn; /*delay(1);*/ continue; }
                  else           { green += ic;       /*delay(1);*/ continue; }
                }

            // blue-part - if '$' then parse x-Coordinates
                if (pstate == blueTurn){
                  if (ic == '$') { pstate = xCoordTurn; /*delay(1);*/ continue; }
                  else           { blue += ic;          /*delay(1);*/ continue; }
                }

            // x-Coordinates  - if '$' then parse y-Coordinates
                if (pstate == xCoordTurn){
                  if (ic == '$') { pstate = yCoordTurn; /*delay(1);*/ continue; }
                  else           { x += ic;             /*delay(1);*/ continue; }
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
              //    delay(1);
                  continue;
                } else {
                    y += ic;
              //      delay(1);
                    continue;
                  }
              }

          }






          if (result==BUFFER_OVERFLOW)
            Serial.print(textBuffer);
          else
            Serial.println(textBuffer);
        }
        else
          Serial.println("** ERROR: File is empty...");
      }
      Serial.println();
      file.closeFile();
    }
    else
    {
      switch(res)
      {
        case ERROR_ANOTHER_FILE_OPEN:
          Serial.println("** ERROR: Another file is already open...");
          break;
        default:
          Serial.print("** ERROR: ");
          Serial.println(res, HEX);
          break;
      }
    }
  }
  else
    Serial.println("** ERROR: 'TEXTFILE.TXT' does not exist...");
    
  Serial.println();
  Serial.println();
  Serial.println("***** All done... *****");
  
}  

void loop() 
{
}
