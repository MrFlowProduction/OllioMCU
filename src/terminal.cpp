#include <terminal.h>
#include <string.h>
#include <tools/scale.h>
#include <time.h>

void INIT_TERMINAL()
{
  Serial.begin(BAUDRATE);
}


void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void terminal_handler()
{

  if (Serial.available() > 0)
  {

    String temp = "";

    while (Serial.available() > 0)
    {

      temp = Serial.readStringUntil('\n');
      temp.trim();

      delay(1);
    }

    // ========================== System ==================================

    if (temp == "setup system")
    {
    }

    else if (temp == "clear memory")
    {
      mem_clear();
      printdone();
    }

    else if (temp == "reset block number")
    {
      setBlockNumber(100000);
      printdone();
    }

    else if (temp == "get id")
    {
      Serial.printf("ID: %d\n", get_id());
    }

    else if (temp == "buttonled on")
    {

      Serial.println("Button Led On");
      //setButtonLight(true);
    }

    else if (temp == "buttonled off")
    {

      Serial.println("Button Led Off");
      //setButtonLight(false);
    }

    else if (temp == "print scale")
    {
      print_scale_values();
    }

    else if (temp == "set date"){
      dateTimeTerminal();
    }

    else if(temp == "print date"){
      showDate("Now:", now());
    }

    else if(temp == "ntp date"){
      printLocalTime();
    }

    else if (temp == "printer test")
    {
      print_test();
    }

    else if (temp == "scale calibrate")
    {
      calibrateScale();
    }

    else if (temp == "forward"){
      setDcMotor(MotorState::FORWARD);
    }

    else if (temp == "backward"){
      setDcMotor(MotorState::BACKWARD);
    }

    else if (temp == "stop"){
      setDcMotor(MotorState::STOP);
    }

    else if (temp == "brake"){
      setDcMotor(MotorState::BRAKE);
    }

    else if(temp == "barrel"){
      Serial.println("MOVING...");
      if(SetTap(TapState::BARREL)) printdone();
      printfail();
    }

    else if(temp == "close"){
       Serial.println("MOVING...");
      if(SetTap(TapState::CLOSE)) printdone();
      printfail();
    }

    else if(temp == "watertank"){
       Serial.println("MOVING...");
      if(SetTap(TapState::WATERTANK)) printdone();
      printfail();
    }

    else if(temp == "tap current state"){
      Serial.printf("Tap angle: %d\n", readTapAngle());
      Serial.println(getTapStateString(tapState));
    }

    else if(temp == "save angle to barrel"){
      saveTapAngleTo(TapState::BARREL);
    }

    else if(temp == "save angle to close"){
      saveTapAngleTo(TapState::CLOSE);
    }

    else if(temp == "save angle to watertank"){
      saveTapAngleTo(TapState::WATERTANK);
    }

    else if(temp == "tap enable init"){
      changeTapInitEn(true);
    }

    else if(temp == "tap disable init"){
      changeTapInitEn(false);
    }

    else if(temp == "service mode"){
      ChangeState(MachineState::SERVICE);
    }

    else if(temp == "set empty barrel"){
      saveEmptyBarrelPoint();
    }

    else if(temp == "reset scale"){
      resetScale();
    }

    else if(temp == "read scale"){
      Serial.printf("Weight: %f Kg", read_scale());
    }

    else if(temp == "print scale values"){
      print_scale_values();
    }

    else if(temp == "reboot" || temp == "reset"){
      ESP.restart();
    }

    else
    {
      Serial.printf("Unknown command: %s\n", temp);
    }
  }
}



/* várakozás a terminálra */
void waitToAnsware() {

  while (Serial.available() == 0) {
    delay(10);
  }

}


/* Egy sor beolvasása a terminálból */
String readLine() {
  waitToAnsware();

  String line = "";
  char c;

  while (Serial.available() > 0) {
    c = (char)Serial.read();
    if (c == '\r') {
      continue;
    }
    if (c == '\n') {
      return line;
    }

    line += c;

    delay(1);
    
  }

  return line;
}


/* Karakterből byte szám */
byte charToByte(char c) {

  switch (c) {

    case '0':
      return 0;
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;

  }

  return 0;

}






/* DateTime terminál */
void dateTimeTerminal(){
  Serial.print("\nPlease add current datetime!\nYear:");

  String row;
  uint16_t y,M,d,h,m;
  byte indexer = 0;

  while (true)
  {
    row = readLine();

    // Exit point
    if(row == "#") break;

    switch (indexer++)
    {
      case 0:
        y = row.toInt();
        Serial.println(y);
        Serial.println("Month:");
        break;

      case 1:
        M = row.toInt();
        Serial.println(M);
        Serial.print("Day:");
        break;

      case 2:
        d = row.toInt();
        Serial.println(d);
        Serial.print("Hour:");
        break;

      case 3:
        h = row.toInt();
        Serial.println(y);
        Serial.print("Min:");
        break;

      case 4:
        m = row.toInt();
        Serial.println(y);
        Serial.println("Saving...");
        setDate(DateTime(y,M,d,h,m,0));
        printdone();
        return;
      
      default:
        indexer = 0;
        break;
    }


  }
  
}