#include <tools/expander.h>

// MCP Library
Adafruit_MCP23017 mcp;

// MCP Connection state
bool isMcpConnected;


/* Init expander */
void INIT_EXTERNAL_PORTS(){
    
    printinit("MCP23017 I/O Expander");

    Wire.begin();

    if(i2c_address_check(0x20) != 0){
        dropFaulty("I/O not available",102);
        return;
    }

    // Init connection
    mcp.begin();
    mcp.setupInterrupts(true,true,LOW);

    // Init pin directions
    mcp.pinMode(BUTTON_LED,     OUTPUT);
    mcp.pinMode(SERVICE_LED,    OUTPUT);
    mcp.pinMode(TANK_SENSOR,    INPUT);
    mcp.pinMode(USER_BUTTON,    INPUT);
    mcp.pinMode(DOOR_SENSOR,    INPUT);
    mcp.pinMode(SERVICE_BUTTON, INPUT);
    mcp.pinMode(DC_EN,          OUTPUT);
    mcp.pinMode(DC_IN1,         OUTPUT);
    mcp.pinMode(DC_IN2,         OUTPUT);

    // turn on a 100K pullup internally
    mcp.pullUp(TANK_SENSOR, HIGH);  
    mcp.pullUp(USER_BUTTON, HIGH);  
    mcp.pullUp(DOOR_SENSOR, HIGH);
    mcp.pullUp(SERVICE_BUTTON, HIGH);  

    mcp.digitalWrite(BUTTON_LED, HIGH);
    mcp.digitalWrite(SERVICE_LED, HIGH);
    //mcp.setupInterruptPin(USER_BUTTON, FALLING);

    // Set Native interrupt pin and callback
    //pinMode(EXP_INTB, INPUT_PULLUP);
    //attachInterrupt(EXP_INTB, handlingExpInterrupt, FALLING);

    isMcpConnected = true;

    // Init States
    InitExpanderStates();

    printdone();
}


/* Init Default States */
void InitExpanderStates(){
    
    // Tank állapota
    isTankFull = tankState();
    
    // Fedél nyitás
    if(doorOpened() != isDoorOpened){
        isDoorChanged = true;
        isDoorOpened = doorOpened();
    }

    // Felhasználói gomb
    if(userButton()){
        isButtonPressed = true;
    }

    // Szerviz gomb
    if(serviceButton()){
        isServiceButtonPressed = true;
    }
}


/* Handling Interrupts 
void IRAM_ATTR handlingExpInterrupt(){
    
    Serial.println(F("Expander interrupt detected"));

    // Get more information from the MCP from the INT
    uint8_t pin=mcp.getLastInterruptPin();
    uint8_t val=mcp.getLastInterruptPinValue();

    // Handling user button
    if (pin == USER_BUTTON){
        isButtonPressed = true;
        Serial.println("Button pressed");
    }

    // Handling water tank
    if(pin == TANK_SENSOR){
        if(val == 0) {isTankFull = true; }
        else{ isTankFull = false; }
        Serial.println("Tank: "+ String(isTankFull));
    }

    // Handling Door sensor
    if(pin == DOOR_SENSOR){
        if(val == 0) { 
            isDoorOpened = false; }
        else{ isDoorOpened = true; }
         Serial.println("Door state: "+String(isDoorOpened));
    }
}
*/




/* Felhasználói gomb megvilágítása */
void setButtonLight(bool state){

    if(!isMcpConnected){ return; }

    mcp.digitalWrite(BUTTON_LED, state);

}

/* Szervigomb háttérvilágítása */
void setServiceLight(bool state){
    if(!isMcpConnected){ return; }

    mcp.digitalWrite(SERVICE_LED, state);
}


/* Reads a digital input */
int getSensValue(int pin)
{
    return mcp.digitalRead(pin);
}


/* Szonda anód tápfeszültség */
void setProbeSupply(bool state){

    mcp.digitalWrite(PROBE_SUPPLY, state);
}


/* Az ajtó nyitva?? */
bool doorOpened(){
    return mcp.digitalRead(DOOR_SENSOR);
}

/* Tartály tele?? */
bool tankState(){
    return !mcp.digitalRead(TANK_SENSOR);
}

/* Gomb benyomva?? */
bool userButton(){
    return !mcp.digitalRead(USER_BUTTON);
}

/* Szervizgomb benyomva?? */
bool serviceButton(){
    return !mcp.digitalRead(SERVICE_BUTTON);
}


/* Set DC Motor driver pins */
void setDcMotorPins(bool in1, bool in2, bool enable){

    if(!isMcpConnected){ return; }

    mcp.digitalWrite(DC_IN1, in1);
    mcp.digitalWrite(DC_IN2, in2);
    mcp.digitalWrite(DC_EN, enable);

}


/* DC Motor beállítása */
void setDcMotor(MotorState state){
    
    switch (state)
    {
        // Kikapcsolt állapot
        case MotorState::STOP:
            setDcMotorPins(false, false, false);
            break;

        // Befékezett állapot
        case MotorState::BRAKE:
            setDcMotorPins(true, true, true);
            break;

        // Előre tekerés
        case MotorState::FORWARD:
            setDcMotorPins(true, false, true);
            break;

        // Hátra tekerés
        case MotorState::BACKWARD:
            setDcMotorPins(false, true, true);
            break;
        
        
        default:
            setDcMotorPins(false, false, false);
            break;
    }

}




