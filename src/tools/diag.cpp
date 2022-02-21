#include <tools/diag.h>

#include <tools/expander.h>


void printSysData(char *version)
{

  Serial.print(F("\nOllio Firmware "));
  Serial.println(version);
}

void printtestpassed()
{
  Serial.println(F("[TEST PASSED]\n"));
}

void printtestfailed()
{
  Serial.println(F("[TEST FAILED]\n"));
}

void printready()
{
  Serial.println(F("[RDY]"));
}

void printdone()
{
  Serial.println(F("[DONE]"));
}

void printfail()
{
  Serial.println(F("[FAIL]"));
}

void printok()
{
  Serial.println(F("[OK]"));
}

void printerror()
{
  Serial.println(F("[ERROR]"));
}



void printinit(String text, bool withNewLine)
{

  Serial.print(F("\n[INIT]\n"));
  Serial.print(text);
  Serial.print("...");

  if (withNewLine)
  {
    Serial.println();
  }
}

void printreason(String text, bool withFail)
{

  if (withFail)
  {
    printfail();
  }

  Serial.print(F("[REASON]: "));
  Serial.print(text);
  Serial.println();
}



/* Rendszerhiba dobása, üzemképtelen állapot */
void dropFaulty(String text, int code, bool loopForever){

    Serial.println("System Fault");
    Serial.print("Message: ");
    Serial.println(text);

    setFaultScreen(text, code);

    while(loopForever){
        delay(500);
    }

}


void syscheck(){
    if(isTankFull){
        setButtonLight(OFF);
        dropFaulty("Watertank is full", 41);
    }
}

