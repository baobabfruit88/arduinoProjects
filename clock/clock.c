#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;
int seconds = 0;
int minutes = 0;
int hours = 0;
void setup() {
  Serial.begin(115200);
  matrix.begin();
}


//Default frame is 8 by 12
uint8_t frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};


/*
* This empties the "snake" or seconds indicator
*/
void empty(){
  frame[0][0] = 0;
  frame[0][1] = 0;
  frame[0][2] = 0;
  frame[0][3] = 0;
  frame[0][4] = 0;
  frame[0][5] = 0;
  frame[0][6] = 0;
  frame[0][7] = 0;
  frame[0][8] = 0;
  frame[0][9] = 0;
  frame[0][10] = 0;
  frame[0][11] = 0;
  matrix.renderBitmap(frame, 8, 12);
}

/*
* Here we empty the rows that are indicating the past minutes
*/
void emptyMinutes(){
  for (int i = 1; i < 6; ++i){
      for (int a = 0; a < 12; a++){
      frame[i][a] = 0;
      matrix.renderBitmap(frame, 8, 12);
      }
  }
}

/**
* Every twelve seconds we check if a minute has past, if it has then we add a minute led, 
* we do this 5 times (so 5 rows will be filled as 5* 12 == 60)
*/
void minute(){
  int overflow = 1; //We thought we needed this, but default behaviour seems to be that when there is spillover it goes to the next row by default
  if (seconds == 60) {
    if(minutes == 60){
      hours++;
      minutes = 0;
      hour();
      emptyMinutes();
    }
    frame[overflow][minutes] = 1;
    matrix.renderBitmap(frame, 8, 12);
    minutes++;
    seconds = 0;
  }
}

void hour (){
  frame[7][hours -1] = 1;
  matrix.renderBitmap(frame, 8, 12);
  if(hours == 12) {
    frame[7][0] = 0;
    frame[7][1] = 0;
    frame[7][2] = 0;
    frame[7][3] = 0;
    frame[7][4] = 0;
    frame[7][5] = 0;
    frame[7][6] = 0;
    frame[7][7] = 0;
    frame[7][8] = 0;
    frame[7][9] = 0;
    frame[7][10] = 0;
    frame[7][11] = 0;
    hours = 0;
  }
}
/**
*   We use a "snake" to fill the first row (0) 5 times as 5 * 12 == 60
*   After every cycle we empty the row. 
*/
void snake(){
  for (int i = 0; i < 13; ++i){
    frame[0][i] = 1;
    delay(1000); //1000 ms = 1 second
    matrix.renderBitmap(frame, 8, 12);
  }
  seconds += 12;
  minute(); 
  empty();
}

void loop(){
snake();
}