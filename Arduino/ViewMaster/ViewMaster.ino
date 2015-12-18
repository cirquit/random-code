// ViewMaster.ino

#include "ESP8266.h"
#include <UTFT.h>
#include <avr/pgmspace.h>

/*
 * Global data & definitions for GUI
 */

extern unsigned int wifiOff[0x1024];        // 32x32
extern unsigned int wifiOn[0x1024];         // 32x32
//extern unsigned int bird2[14400];           // 120x120
extern unsigned int optogram_low[12360];    // 120x103
extern unsigned int redhat[15795];          // 117x135
//extern unsigned int window_low[14400];      // 120x120
//extern unsigned int tollwood_low[14280];      // 120x119

#define ENCP1 2  // interrupt
#define ENCP2 3  // interrupt

volatile int lastEncoded = 0;
volatile int encoderValue = 0;

/*
 * Global data & definitions for the parsing
 */

// Format:
// #red$green$blue$x-coord$y-coord*&

typedef enum{
  redTurn,
  greenTurn,
  blueTurn,
  xCoordTurn,
  yCoordTurn,
  pauseTurn
} ParseState;

ParseState pstate    = pauseTurn;
ParseState tempstate = pauseTurn;

unsigned long parseTime = 0;      // to track if there is currently a picture being parsed via millis()

String red;
String green;
String blue;
String x;
String y;
int displacementX = 0;       // to set custom displacements on the x-axis for pictures
//int displacementBetween = 0; // to set custom space between the two pictures

int scale = 1;

/*
 * Global data for WiFi Communication
 */

typedef enum {
   enabled
 , disabled
} WifiState;

typedef enum {
    startScreen
  , prerenderedPic1
  , prerenderedPic2
  , prerenderedPic3
  , requestPic1
  , requestPic2
  , requestPic3
  , requestPic4
  , pauseRequests
} State;

#define esp8266 Serial1
#define SSID        "swh"
#define PASSWORD    "swhswhswh"
#define IP          "141.84.8.123"
ESP8266 wifi(Serial1);
String comdata       = "";               // buffers everything the WiFi shield sends
WifiState wifistate  = disabled;
State state          = startScreen;      // starting state
State nextState      = prerenderedPic1;  // used to define a loop within the enumeration by 'startNextState'
int numberOfConnects = 0;                // if this goes over 1, restart

/*
 * Global data for the 3.2" Display
 */
#define RS 38
#define WR 39
#define CS 40
#define RSET 41

extern uint8_t SmallFont[];              // which font to use
UTFT myGLCD(ITDB32S, RS, WR, CS, RSET);  // PIN Setup (<model code>, SDA, SCL, CS, RST)

/***************************
 *                         *
 *        MAIN SETUP       *
 *                         *
 ***************************/

void setup(){

  Serial.begin(115200);

/*******************
 * Network - Setup *
 *******************/

/*
 * Look up version - only to test if the wifi is visible
 * -> if this doesn't work, nothing's going to work
 */

 Serial.println(F("Setup begin"));
 Serial.print(F("FW Version: "));
 Serial.println(wifi.getVersion().c_str());


/*
 * Look up if the setup as a client was successfull
 * -> doesn't mean anything
 */

  if (wifi.setOprToStation()) {
    Serial.println(F("Setting ESP up as a client: Ok"));
  } else {
    Serial.println(F("Setting ESP up as a client: Error"));
  }

/*
 * Joining the local WiFi with preset SSID and Password
 * -> if this doesn't work, nothing's going to work
 */

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.println(F("Join AP success"));
    Serial.print(F("IP: "));
    Serial.println(wifi.getLocalIP().c_str());
    wifistate = enabled;
    wifi.enableMUX(); // multiple connection mode
    esp8266.println("AT+CIPMUX=1");
  } else {
    Serial.println(F("Join AP failure"));
  }

/*******************
 * Display - Setup *
 *******************/

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


/*********************
 *      Controls     *
 *********************/

  pinMode(ENCP1, INPUT);
  pinMode(ENCP2, INPUT);

  digitalWrite(ENCP1, HIGH); //turn pullup resistor on
  digitalWrite(ENCP2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);

  Serial.println(F("I'm done with the setup..."));
}

/***************************
 *         Parser          *
 ***************************/

/*
 * Main entry point for the parser
 */

void parseData( String data ){

  for( int i = 0; i < data.length(); i++){
    char ic = data[i];

    if (ic == '\n'){ continue; }
    if (ic == '\r'){ continue; }
    if (ic == 'O') { continue; }
    if (ic == 'K') { continue; }
    if (ic == '+') { tempstate = pstate; pstate = pauseTurn; continue; }
    if (ic == ':') { pstate = tempstate;                     continue; }

// RGB - Format

// start with a pixel-definition
    if (ic == '#'){ pstate = redTurn; continue; }

// red-part - if '$' then parse green-part
    if (pstate == redTurn){
      if (ic == '$') { pstate = greenTurn; continue; }
      else           { red += ic;          continue; }
    }

// green-part - if '$' then parse blue-part
    if (pstate == greenTurn){
      if (ic == '$') { pstate = blueTurn; continue; }
      else           { green += ic;       continue; }
    }

// blue-part - if '$' then parse x-Coordinates
    if (pstate == blueTurn){
      if (ic == '$') { pstate = xCoordTurn; continue; }
      else           { blue += ic;          continue; }
    }

// x-Coordinates  - if '$' then parse y-Coordinates
    if (pstate == xCoordTurn){
      if (ic == '$') { pstate = yCoordTurn;  continue; }
      else           { x += ic;              continue; }
    }

// y-Coordinates  - if '*' then draw a pixel with the color and reset the strings
    if (pstate == yCoordTurn){
      if (ic == '*') {
        pstate = pauseTurn;
        setPixRGB(x, y);
        red   = "";
        green = "";
        blue  = "";
        x     = "";
        y     = "";
        continue;
      } else { y += ic; continue; }
    }

   }

}

/*
 * collects everything the WiFi shield sends in a String 'comdata'
 */
void getComdata(){
  while (esp8266.available() > 0) {
    comdata += char(esp8266.read());
    delay(1);
  }
}

/***************************
 *                         *
 *        MAIN LOOP        *
 *                         *
 ***************************/

void loop() {

/*
 * Listen on the value from the rotary encoder ~ 45° rotation CW to trigger the next state
 * if I'm not parsing anything for 5 seconds, allow to switch to the next picture
 */

  if(encoderValue <= -40){

    Serial.println(F("I'm triggered forwards!"));
    if( millis() - parseTime > 5 * 1000 ){
      myGLCD.print(" Next pic in 1...", LEFT, 228);
      myGLCD.print(" Next pic in 1...", RIGHT, 228);
      setNextState();
      delay(2000);
    } else {
      myGLCD.print(" Next is blocked ", LEFT, 228);
      myGLCD.print(" Next is blocked ", RIGHT, 228);
    }
    encoderValue = 0;
  }

/*
 * Listen on the value from the rotary encoder ~ 45° rotation CCW to go back to the start screen
 * if I'm not parsing anything for 5 seconds, allow to switch back to the start screen
 */

  if ( encoderValue >= 40 ){

    Serial.println(F("I'm triggered backwards!"));
    // if I'm not parsing anything for 5 seconds, you can go back to the start screen!
    if( millis() - parseTime > 5 * 1000 ){
        myGLCD.print(" Back!", LEFT, 228);
        myGLCD.print(" Back!", RIGHT, 228);
        state = startScreen;
        nextState = prerenderedPic1;
        delay(2000);
    } else {
        myGLCD.print(" Back is blocked! ", LEFT, 228);
        myGLCD.print(" Back is blocked! ", RIGHT, 228);
    }
    encoderValue = 0;
  }

/*
 * Try to read and parse the incoming data
 */
  getComdata();

/*
 * If there is some data -> show it on the TFT
 */
  if( comdata.length() > 0 ){
     parseData( comdata );
     comdata = "";
  }

/*
 * If number of connects > 1, restart the arduino
 */
  if( numberOfConnects > 2 ){
      myGLCD.print( "No Connection! RSTRT", LEFT, 228);
      myGLCD.print( "No Connection! RSTRT", RIGHT, 228);
      asm volatile ("  jmp 0"); // restarts the arduino (takes ~ 10s)
  }

/*
 * Should show a window picture (prerendered)
 */

  if(state == prerenderedPic1){

    myGLCD.fillScr( 0, 0, 0 );
    myGLCD.drawBitmap(33 , 60, 117, 135, redhat); // + 28 as for the displacement in X
    myGLCD.drawBitmap(153 + 28, 60, 117, 135, redhat); // + 28 as for the displacement in X
    state = pauseRequests;
    return;
  }

/*
 * Send basic request at my server at my IP with
 *
 * route "/static/raw/dos.txt"
 * port 9090
 *
 * should show a 32x32 dos-logo blown up to (twice)
 */

   if (state == requestPic1) {

    delay(1000);

    if (!getHTTP(IP, "/static/raw/dos.txt", 9090)){
      Serial.println("*** Could not connect to the server at");
      Serial.println("*** 141.84.8.119:9090/static/raw/dos.txt");
      Serial.println("*** Retrying...");
      numberOfConnects++;
    } else {
      Serial.println("*** Got a connection for /static/raw/dos.txt...");
      numberOfConnects = 0;
      state = pauseRequests;
      scale = 4;
      displacementX = 28;
      return;
    }
  }

/*
 * Send basic request at my server at my IP with
 *
 * route "/static/raw/cat.txt"
 * port 9090
 *
 * should show a picture of nyancat
 */

 if (state == requestPic2) {

    delay(1000);

    if (!getHTTP(IP, "/static/raw/cat.txt", 9090)){
      Serial.println(F("*** Could not connect to the server at"));
      Serial.println(F("*** IP: 141.84.8.119:9090/static/raw/cat.txt"));
      Serial.println(F("*** Retrying..."));
      numberOfConnects++;
    } else {
      Serial.println(F("*** Got a connection for /cat.txt..."));
      numberOfConnects = 0;
      state = pauseRequests;
      displacementX = 28;
      scale = 4;
      return;
    }
  }

   if (state == requestPic3) {

    delay(1000);

    if (!getHTTP(IP, "/static/raw/netscape.txt", 9090)){
      Serial.println(F("*** Could not connect to the server at"));
      Serial.println(F("*** IP: 141.84.8.119:9090/static/raw/insta.txt"));
      Serial.println(F("*** Retrying..."));
      numberOfConnects++;
    } else {
      Serial.println(F("*** Got a connection for /raw/insta.txt..."));
      state = pauseRequests;
      scale = 4;
      numberOfConnects = 0;
      displacementX = 28;
      return;
    }
  }

  if (state == requestPic4) {

    delay(1000);

    if (!getHTTP(IP, "/static/raw/insta.txt", 9090)){
      Serial.println(F("*** Could not connect to the server at"));
      Serial.println(F("*** IP: 141.84.8.123:9090/static/raw/insta.txt"));
      Serial.println(F("*** Retrying..."));
      numberOfConnects++;
    } else {
      Serial.println(F("*** Got a connection for /raw/insta.txt..."));
      state = pauseRequests;
      scale = 4;
      numberOfConnects = 0;
      displacementX = 0;
      return;
    }
  }

/*
 * Startscreen Definition
 */

  if(state == startScreen){

    myGLCD.fillScr(255, 255, 255);
    myGLCD.setColor(255, 255, 255);

    myGLCD.drawBitmap(20,       60, 120, 103, optogram_low);
    myGLCD.drawBitmap(40 + 120, 60, 120, 103, optogram_low);

    delay(1000); // so the WiFi is not overdrawn by the optogram logo

    if (wifistate == enabled){
      myGLCD.drawBitmap(268, 20, 32, 32, wifiOn);
    } else{
      myGLCD.drawBitmap(268, 20, 32, 32, wifiOff);
      myGLCD.print( "No WiFi! Restarting in 10...", CENTER, 228);
      asm volatile ("  jmp 0"); // restarts the arduino (takes ~ 10s)
    }

    state = pauseRequests;
    return;
  }

  if(state == pauseRequests){
     // do nothing
  }

/*
 * Debug controls through the Serial
 */

//  if (Serial.available()) {
//    esp8266.write(Serial.read());
//  }

}

/***************************
 *                         *
 * Wifi Shield Definitions *
 *                         *
 ***************************/

/*
 * send a GET request at
 *
 * IP      ~ server  -- could be "127.0.0.1"
 * subdirs ~ route   -- could be "/static"
 * port    ~ port    -- could be "80"
 *
 * returns if the request was successfull
 */
boolean getHTTP(String server, String subdirs, int port ){

  if (wifi.createTCP(1, server, port)) {

    String getReq = "GET " + subdirs + " HTTP/1.0\r\n\r\n";

    char data[getReq.length() + 1];
    getReq.toCharArray(data, getReq.length() + 1); // Converted String to char.

    boolean success = wifi.send(1, (uint8_t *)data, sizeof(data));

    if (success) { Serial.println(F("*** Connection successfull"));   }
    else         { Serial.println(F("*** Connection didn't happen")); }

    return success;
  }

  Serial.println(F("*** TCP Connection didn't happen..."));
  return false;

}

/*
 * Closes TCP Connection (still bugs and is not currently needed)
 */

void closeServer() {
  esp8266.println("AT+CIPCLOSE");
}


/*******************
 *                 *
 * LCD Definitions *
 *                 *
 ******************/

void setPixRGB(String x, String y){

  parseTime = millis();

  int x_i   = x.toInt();
  int y_i   = y.toInt();
  int new_x = scale * x_i;
  int new_y = scale * y_i + 40;

  myGLCD.setColor(red.toInt(), green.toInt(), blue.toInt());

  for(int i = 0; i < scale; i++){
      for(int j=0; j< scale; j++){
          myGLCD.drawPixel(new_x + i       + displacementX, new_y + j);
          myGLCD.drawPixel(new_x + i + 160 + displacementX, new_y + j); // mirror effect
      }
  }

}


/*******************
 *                 *
 * GUI Definitions *
 *                 *
 ******************/


/*
 * updates the value for the rotary encoder
 *
 */

int updateEncoder(){

  int MSB = digitalRead(ENCP1); //MSB = most significant bit
  int LSB = digitalRead(ENCP2); //LSB = least significant bit

  int encoded =         (MSB << 1) | LSB;     //converting the 2 pin value to single number
  int sum     = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++; // cw-rotation
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --; // ccw-rotation

  lastEncoded = encoded; //store this value for next time

}

/*
 * custom loop through the possible states
 */

void setNextState(){

  state = nextState;

  switch (nextState){
    case startScreen:     nextState = prerenderedPic1; break;
    case prerenderedPic1: nextState = requestPic1;     break;
    case requestPic1:     nextState = requestPic2;     break;
    case requestPic2:     nextState = requestPic3;     break;
    case requestPic3:     nextState = requestPic4;     break;
    case requestPic4:     nextState = startScreen;     break;
    default: Serial.println(F("*** 'nextState' was called and was given an invalid state..."));
  }
  myGLCD.clrScr();
}
