// UTFT_Converter_Test.ino

#include <UTFT.h>
#include <avr/pgmspace.h>

//UTFT myGLCD(LPH9135,6,5,2,3,4);   // Remember to change the model parameter to suit your display module!
UTFT myGLCD(ITDB32S,38,39,40,41);

extern uint8_t SmallFont[];
//extern unsigned int cat_01_bmp_120x120[14400];
//extern unsigned int cat_01_gif_120x120[14400];
//extern unsigned int cat_01_jpg_120x120[14400];
extern unsigned int cat_01_png_120x120[14400];
extern unsigned int cat_01_tga_120x120[14400];

void setup()
{
  myGLCD.InitLCD(PORTRAIT);
  myGLCD.setFont(SmallFont);

}

void loop()
{
// BMP
//  myGLCD.fillScr(255, 255, 255);
//  myGLCD.drawBitmap (0, 0, 120, 120, cat_01_bmp_120x120, 1);
//  myGLCD.print("This is a BMP", CENTER, 160);
//  delay(5000);

// JPG
//   myGLCD.fillScr(255, 255, 255);
//   myGLCD.drawBitmap (0, 0, 120, 120, cat_01_jpg_120x120, 1);
//   myGLCD.print("This is a JPG", CENTER, 160);
//   delay(5000);

// GIF
//  myGLCD.fillScr(255, 255, 255);
//  myGLCD.drawBitmap (0, 0, 120, 120, cat_01_gif_120x120, 1);
//  myGLCD.print("This is a GIF", CENTER, 160);
//  delay(5000);

// // PNG
   myGLCD.fillScr(255, 255, 255);
   myGLCD.drawBitmap (0, 0, 120, 120, cat_01_png_120x120, 1);
   myGLCD.print("This is a PNG", CENTER, 160);
   delay(5000);

// TGA
  myGLCD.fillScr(255, 255, 255);
  myGLCD.drawBitmap (0, 0, 120, 120, cat_01_tga_120x120, 1);
  myGLCD.print("This is a TGA", CENTER, 160);
  delay(5000);


}

