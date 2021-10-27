#include <tools/diag.h>

#include <tools/expander.h>

/* Rendszerhiba dobása, üzemképtelen állapot */
void dropFaulty(String text, int code){

    Serial.println("System Fault");
    Serial.print("Message: ");
    Serial.println(text);

    setFaultScreen(text, code);

    while(true){
        delay(500);
    }

}


void syscheck(){
    if(isTankFull){
        setButtonLight(OFF);
        dropFaulty("Watertank is full", 41);
    }
}