// sketching_example_v01.ino

typedef struct{
  int red;
  int green;
  int blue;
} RGB;


RGB* rgb = malloc (sizeof(RGB));


int hex(char c){
  if(c == '0'){ return 0;  }
  if(c == '1'){ return 1;  }
  if(c == '2'){ return 2;  }
  if(c == '3'){ return 3;  }
  if(c == '4'){ return 4;  }
  if(c == '5'){ return 5;  }
  if(c == '6'){ return 6;  }
  if(c == '7'){ return 7;  }
  if(c == '8'){ return 8;  }
  if(c == '9'){ return 9;  }
  if(c == 'A'){ return 10; }
  if(c == 'B'){ return 11; }
  if(c == 'C'){ return 12; }
  if(c == 'D'){ return 13; }
  if(c == 'E'){ return 14; }
  if(c == 'F'){ return 15; }

}

RGB* toHex(char* p1, char* p2, char* p3, RGB* storage){

  storage -> red   = 16 * hex(p1[0]) + hex(p1[1]);
  storage -> green = 16 * hex(p2[0]) + hex(p2[1]);
  storage -> blue  = 16 * hex(p3[0]) + hex(p3[1]);

  return storage;
}


void setup(){

  Serial.begin( 9600 );

  char red[2]   = "FF";
  char green[2] = "00";
  char blue[2]  = "FF";

  RGB* blub = toHex(red, green, blue, rgb);
  Serial.println(blub -> red);
  Serial.println(blub -> green);
  Serial.println(blub -> blue);


}



void loop() {

}