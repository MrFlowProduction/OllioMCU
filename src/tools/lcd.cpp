#include <tools/lcd.h>
#include <general/globals.h>
#include <general/enum.h>
#include <tools/adc.h>
#include <tools/scale.h>
#include <stdlib.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

LiquidCrystal_I2C lcd(0x27,20,4);

int prevStatePoint = 1000;

uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t full[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

uint8_t arrow[8] = {
  B11111,
  B10111,
  B10011,
  B10001,
  B10001,
  B10011,
  B10111,
  B11111,
};


uint8_t rd[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
};

uint8_t ry[8] = {
  B11000,
  B11000,
  B11000,
  B11111,
  B11111,
  B00011,
  B00011,
  B00011,
};

uint8_t rh[8] = {
  B11011,
  B11011,
  B11011,
  B11111,
  B11111,
  B11011,
  B11011,
  B11011,
};

void INIT_LCD() {

  printinit("LCD");

    lcd.init();                      // initialize the lcd 
    lcd.backlight();

    lcd.createChar(0, bell);
    lcd.createChar(1, full);
    lcd.createChar(2, arrow);
    lcd.createChar(3, rd);
    lcd.createChar(4, ry);
    lcd.createChar(5, rh);

    setNoneScreen();

  printdone();
}



// --------------------  Screen State Handler  --------------------

/* Következő állapot */
bool nextScreenState(){
  if(screen_state_delay == 0){ return false; }

  if(screen_update_timer > millis()){ return false; }

  setNextScreen();

  screen_update_timer = millis() + screen_state_delay;

  return true;
}



/* Következő állapot */
bool nextScreenState(int delay){

  if(screen_state_delay == 0){ return false; }

  if(screen_update_timer > millis()){ return false; }

  setNextScreen();

  screen_update_timer = millis() + delay;

  return true;
}

void setNextScreen(){
  if(++screen_state >= screen_max_state_number){
      screen_state = 0;
  }
}

/* Kijelző állapotmotor alaphelyzetbe állítása */
void resetScreenStates(){
  screen_state_delay = 0;
  screen_state = 0;
  screen_update_timer = 0;
  screen_max_state_number = 0;
  screen_first_update = true;
}

/* Kijelző állapotkezelés */
void setScreenStates(byte stateNum, int delay){

  resetScreenStates();

  screen_state_delay = delay;
  screen_max_state_number = stateNum;  

}

/* Kijelző állapotfrissítés ideje */
void setScreenDelay(int delay){
    screen_state_delay = delay;
}


void printTag(String text){
  lcd.setCursor(0,3);
  lcd.print("                    ");
  lcd.setCursor(0,3);
  lcd.print(text);
}



// --------------------  Screen Animation Methods  --------------------

void printRow(byte row, char ch, int interval = 5) {

  for(int c = 0; c < 20; c++){

      lcd.setCursor(c, row);
      lcd.print(ch);
      delay(interval);
  }
  
}

void printByteRow(byte row, byte ch, int interval = 5) {

  for(int c = 0; c < 20; c++){

      lcd.setCursor(c, row);
      lcd.printByte(ch);
      delay(interval);
  }
  
}

void percentAnimation(byte row) {

  while (progress < 100) {
    lcd.setCursor(7, row);
    lcd.print(progress, 1);
    lcd.print("%");

    for (int i = 0; i < abs(progress/10); i++) {
      if ((i < 7 || i > 13) && i >= 0) {
        lcd.setCursor(i, row);
        lcd.printByte(1);
      }
    }

    delay(300);
  }
}

void printingAnimation(byte row) {

  printByteRow(row, 3, 5);

  double percent = 0;

  for(int i = 0; i < 21; i++){
     lcd.setCursor(i, row);
     
     if(i < 20) { lcd.printByte(1); }
     
     if(i > 0){
        lcd.setCursor(i - 1, row);
        lcd.printByte(4);

        percent += 2.5;
        lcd.setCursor(7, row + 1);
        lcd.print(percent, 1);
        lcd.print("%");
     }

     
     delay(150);
  }

  delay(50);

  for(int i = 19; i >= -1; i--){
     lcd.setCursor(i, row);
     
     if(i >= 0) { lcd.printByte(1); }
     
     if(i < 19){
       lcd.setCursor(i + 1, row);
        lcd.printByte(5);

        percent += 2.5;
        lcd.setCursor(7, row + 1);
        lcd.print(percent, 1);
        lcd.print("%");
     }

     delay(150);
  }
  
}




void slideUpEffect() {
  
  for(int c = 0; c < 20; c++){

    for(byte r = 0; r < 4; r++){
    
      lcd.setCursor(c, r);
      lcd.printByte(1);
      delay(3);
    }
  }
  
}

void slideDownEffect() {

  for(int c = 0; c < 20; c++){

    for(byte r = 0; r < 4; r++){
    
      lcd.setCursor(c, r);
      lcd.print(" ");
      delay(3);
    }
  }
  
}


void clearScreen(){
  slideUpEffect();
  delay(50);
  slideDownEffect();
}


// --------------------  Screen Animation Methods  -------------------- END


// --------------------  Set Screen Methods  -------------------- START


/* Tilos a fedél felnyitása screen */
void noOpenLidScreen(){
    lcd.setCursor(0,1);
    lcd.print("Tilos a fedel fel-");
    lcd.setCursor(0,2);
    lcd.print("nyitasa!");
}


void closeDownScreen(){
  
  clearScreen();

  lcd.setCursor(0,0);
  lcd.print("Toltse be az olajat!");

  lcd.setCursor(0,2);
  lcd.print("Majd csukja le a");
  lcd.setCursor(0,3);
  lcd.print("fedelet!");
}



void defaultScreen(){

  clearScreen();

  lcd.setCursor(0,1);
  lcd.print("Nyomja meg a start");
  lcd.setCursor(0,2);
  lcd.print("gombot a mereshez!");
}


void setNoneScreen() {
  lcd.setCursor(3,1);
  lcd.print("OllioFirmware");

  lcd.setCursor(3,2);
  lcd.print(VERSION);
}


void setStartScreen() {
  lcd.setCursor(3,1);
  lcd.print("OllioFirmware");

  delay(200);

  lcd.setCursor(7,2);
  lcd.print("v0.1");
}

void setShortingScreen() {
  clearScreen();
  setScreenStates(2, 2000);
}

void updateShortingScreen(){

  if(!nextScreenState()){ return; }

  lcd.clear();

  switch (screen_state)
  {

    case 0:
      lcd.setCursor(0,1);
      lcd.print("Minosites");
      lcd.setCursor(0,2);
      lcd.print("folyamatban...");
      break;

    case 1:
      noOpenLidScreen();
      break;
    
    default:
      break;
  }

}


/* Folyadék szeparálás kijelző */
void setSeparateScreen() {
  clearScreen();
  setScreenStates(2, 2000);
}


/* Szeparációs kijelző frissítése */
void updateSeparateScreen(){

  if(!nextScreenState()){ return; }

  lcd.clear();

  switch (screen_state)
  {

    case 0:
      lcd.setCursor(0,1);
      lcd.print("Tisztitas...");
      break;

    case 1:
      noOpenLidScreen();
      break;
    
    default:
      break;
  }

}


/* Mérés kijelző betöltése */
void setMeasureScreen() {
   clearScreen();
    setScreenStates(2, 2000);
}


/* Mérés kijelző frissítése */
void updateMeasureScreen(){
  if(!nextScreenState()){ return; }

  lcd.clear();

  switch (screen_state)
  {

    case 0:
      lcd.setCursor(0,1);
      lcd.print("Meres....");
      break;

    case 1:
      noOpenLidScreen();
      break;
    
    default:
      break;
  }
}


/* Mérés frissítése */
void updateMeasure(float value){

  lcd.setCursor(0,0);
  lcd.print("          ");

  lcd.setCursor(0,0);
  lcd.print(value);
  lcd.print("kg");

}



void setPrintingScreen() {
  clearScreen();

  lcd.setCursor(0,1);
  lcd.print("Blokk nyomtatasa...");
}


void serviceScreen1(){
  lcd.setCursor(0,0);
    lcd.print("D:");
    if(isDoorOpened) lcd.print("O");
    else lcd.print("C");

    lcd.setCursor(4,0);
    lcd.print("T:");
    if(isTankFull) lcd.print("F");
    else lcd.print("E");

    lcd.setCursor(8,0);
    lcd.print("B:");
    lcd.print(isButtonPressed);

    lcd.setCursor(12,0);
    lcd.print("R:");
    lcd.print(isServiceButtonPressed);

    lcd.setCursor(0,1);
    lcd.print("                    ");
    lcd.setCursor(0,1);
    lcd.print("Probe: ");
    lcd.print(readProbeVoltage(), 3);
    lcd.print("V");

    lcd.setCursor(0,2);
    lcd.print("                    ");
    lcd.setCursor(0,2);
    lcd.print("Tap: ");
    lcd.print(readTapAngle());

    lcd.print("  ");
    lcd.print(readTapVoltage(), 3);

    lcd.setCursor(0,3);
    lcd.print("Scale: ");
    lcd.print(read_scale());

}


void serviceScreen2(){

  // WIFI
  lcd.setCursor(0,0);
  if(wifiIsConnected)
     lcd.print("Connected   ");
  else lcd.print("Disconnected");

  // RTC
  lcd.setCursor(0,1);
  if(isRtcOk) lcd.print("RTC OK  ");
  else lcd.print("RTC FAIL"); 
  lcd.print(rtcTemp(), 1);

  lcd.setCursor(0,2);

  delay(1500);

}


/* Szervizképernyő mindenféle finomsággal */
void setServiceScreen(){
    clearScreen();
    setScreenStates(2, 0);
    serviceScreen1();
}

void updateServiceScreen(){

  lcd.clear();

  switch (screen_state)
  {

    case 0:
      serviceScreen1();
      break;

    case 1:
      serviceScreen2();
      break;
    
    default:
      break;
  }
}


void setClosingScreen() {
  lcd.setCursor(4,1);
  lcd.print("Finishing up");
    
  printingAnimation(2);
}

void setDemoScreen() {
  while (statePoint == DEMO) {
    slideUpEffect();
    delay(100);
    slideDownEffect();
    

    printRow(0, '/');

    printRow(3, '/');

    delay(200);
    lcd.setCursor(3,1);
    lcd.print("Ollio Automata");
    delay(200);
    lcd.setCursor(3,2);
    lcd.print("Revolution 1."); 

    delay(3000);

    slideDownEffect();

    lcd.setCursor(2,0);
    lcd.print("Clean");
    delay(1000);
    lcd.setCursor(4,1);
    lcd.print("Reliable");
    delay(1000);
    lcd.setCursor(6,2);
    lcd.print("Powerful");
    delay(1000);
    lcd.setCursor(8,3);
    lcd.print("Easy to use");

    delay(2000);

    slideDownEffect();

    printRow(0, '/');
    printRow(3, '/');

    lcd.setCursor(5,1);
    lcd.print("Filling...");

    

    for(double i = 0; i < 11; i = i + 0.1){
      lcd.setCursor(5,2);
      lcd.print(i, 1);
      lcd.print("L");
      delay(50);
    }

    lcd.print(" DONE");

    delay(2000);

    lcd.setCursor(5,1);
    lcd.print("Printing...");
    
    printingAnimation(2);

    delay(2000);
  }
}

/* Hibaképernyő */
void setFaultScreen(String text, int code) {

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Uzemen kivul");

  delay(200);

  lcd.setCursor(0,2);
  lcd.print(text);
  lcd.setCursor(0,3);
  lcd.print("Code: ");
  lcd.print(code);
}


void setSyscheckScreen(){
    clearScreen();

    lcd.setCursor(0,1);
    lcd.print("   Ellenorzes...");
}


void lcdPrintBool(bool value){
  if(value) lcd.print("True");
  else lcd.print("False");

}
