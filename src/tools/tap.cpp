#include <tools/tap.h>

TapState low, med, high;


/* Visszaadja a csapállásokhoz tartozó fokot */
int getAngleByTapState(TapState state){

    switch (state)
    {
        case TapState::CLOSE:
            return TAP_CLOSED;

        case TapState::WATERTANK:
            return TAP_WATERTANK;

        case TapState::BARREL:
            return TAP_BARREL;

        default:
            return TAP_BARREL;
    }
}

/* Középső állásszögű csap állapot */
TapState getMedTapState(){

    if(high != TapState::BARREL && low != TapState::BARREL) return TapState::BARREL;
    if(high != TapState::CLOSE && low != TapState::CLOSE) return TapState::CLOSE;
    return TapState::WATERTANK;
}


/* Legkisebb állásszögű csap állapot */
TapState getMinTapState(){
    TapState state = TapState::BARREL;
    int value = getAngleByTapState(TapState::BARREL);
    int angle = value;

    value = getAngleByTapState(TapState::CLOSE);
    if(value <= angle) { angle = value; state = TapState::CLOSE; } 

    value = getAngleByTapState(TapState::WATERTANK);
    if(value <= angle) { angle = value; state = TapState::WATERTANK; } 

    return state; 
}


/* Legnagyobb állásszögű csap állapot */
TapState getMaxTapState(){
    TapState state = TapState::BARREL;   
    int value = getAngleByTapState(TapState::BARREL);
    int angle = value;

    value = getAngleByTapState(TapState::CLOSE);
    if(value >= angle) { angle = value; state = TapState::CLOSE; } 

    value = getAngleByTapState(TapState::WATERTANK);
    if(value >= angle) { angle = value; state = TapState::WATERTANK; } 

    return state; 
}


/* Aktuális csap állapot */
TapState getCurrentTapState(){
    int currentAngle = readTapAngle();

    if(currentAngle <= getAngleByTapState(low) + TAP_ANGLE_HIST) return low;
    if(currentAngle >= getAngleByTapState(high) - TAP_ANGLE_HIST) return high;

    return med;
}


/* Csap állapotának szöveges formája */
char* getTaspStateString(TapState state){
    switch (state)
    {
        case TapState::CLOSE:
            return "Closed";

        case TapState::WATERTANK:
            return "Watertank";

        case TapState::BARREL:
            return "Barrel";

        default:
            return "Unknown";
    }
}



/* Szög helyességének ellenőrzése */
bool checkAngle(int destAngle, int currentAngle){

    if(destAngle <= (currentAngle + TAP_ANGLE_HIST) && 
       destAngle >= (currentAngle - TAP_ANGLE_HIST))
        return true;
    else
        return false;

}



/* Csap mozgatása */
bool moveTap(int angle){

    int currentAngle = readTapAngle();

    // Ha épp ott áll ahol kell, akkor a csap beállítása helyes
    if(checkAngle(angle, currentAngle)) 
        return true;

    // Időkorlát beállítása
    unsigned long timeout = millis() + TAP_TIMEOUT;

    // Motor indítása a megfelelő irányba
    if(currentAngle > angle)
        setDcMotor(MotorState::FORWARD);
    
    else
        setDcMotor(MotorState::BACKWARD);

    bool isSucceded = false;

    // Időkorlát figyelése
    while(timeout > millis()){

        // Beállított szög ellenőrzése
        if(checkAngle(angle, readTapAngle()))
        {
            isSucceded = true;
            break;
        }
    }    

    // Motor befékezése
    setDcMotor(MotorState::BRAKE);

    return isSucceded;
}

/* Csap beállítása */
bool SetTap(TapState state){

    // Ha abban a helyzetben van a csap, ahol kell lennie
    if(tapState == state) return true; 

    bool isSucceded;

    // A csap állásához igazítja a motort az előre megadott
    // fok alapján
    isSucceded = moveTap(getAngleByTapState(state));

    // Mentjük az állapotot ha sikerült a beállítás
    if(isSucceded)
        tapState = state;

    return isSucceded;
}


void INIT_TAP(){

    printinit("TAP", true);

    // Csap állapotok rendezése
    low = getMinTapState();
    high = getMaxTapState();
    med = getMedTapState();
    tapState = getCurrentTapState();

    Serial.printf("Low state: %s\n", getTaspStateString(low));
    Serial.printf("Med state: %s\n", getTaspStateString(med));
    Serial.printf("High state: %s\n", getTaspStateString(high));

    Serial.printf("Tap state: %s\n", getTaspStateString(tapState));

    printdone();

}