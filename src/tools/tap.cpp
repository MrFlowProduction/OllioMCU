#include <tools/tap.h>

TapState low, med, high;


/* Visszaadja a csapállásokhoz tartozó fokot */
int getAngleByTapState(TapState state){

    switch (state)
    {
        case TapState::CLOSE:
            return tap_closed_angle;

        case TapState::WATERTANK:
            return tap_watertank_angle;

        case TapState::BARREL:
            return tap_barrel_angle;

        default:
            return tap_closed_angle;
    }
}


/* Csap állapotának kiíratása */
void printTapState(){
    Serial.printf("Tap angle: %d\n", readTapAngle());
    Serial.printf("Low state: %s angle: %d\n", getTapStateString(low), getAngleByTapState(low));
    Serial.printf("Med state: %s angle: %d\n", getTapStateString(med), getAngleByTapState(med));
    Serial.printf("High state: %s angle: %d\n", getTapStateString(high), getAngleByTapState(high));
    Serial.printf("Tap state: %s \n", getTapStateString(tapState));
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


/* Csap értékeinek beállítása */
void initTapValues(){
    low = getMinTapState();
    high = getMaxTapState();
    med = getMedTapState();
    tapState = getCurrentTapState();
}


/* Csap állapotának szöveges formája */
char* getTapStateString(TapState state){
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
bool checkAngle(int destAngle, int currentAngle, int startAngle){

    // Ha az eltérés pozitív irányba van
    if(startAngle < destAngle)
        if(currentAngle >= (destAngle - TAP_ANGLE_HIST)) return true;
    
    if(startAngle > destAngle)
        if(currentAngle <= (destAngle + TAP_ANGLE_HIST)) return true;

    
    return false;

}



/* Csap mozgatása */
bool moveTap(int angle){

    int startAngle = readTapAngle();
    int currentAngle = startAngle;

    // Ha épp ott áll ahol kell, akkor a csap beállítása helyes
    if(checkAngle(angle, currentAngle, startAngle)) 
        return true;

    // Időkorlát beállítása
    unsigned long timeout = millis() + TAP_TIMEOUT;

    // Motor indítása a megfelelő irányba
    if(angle > currentAngle)
        setDcMotor(MotorState::FORWARD);
    
    else
        setDcMotor(MotorState::BACKWARD);

    bool isSucceded = false;

    // Időkorlát figyelése
    while(timeout > millis()){

        // Beállított szög ellenőrzése
        if(checkAngle(angle, readTapAngle(), startAngle))
        {
            isSucceded = true;
            break;
        }
    }    

    // Motor befékezése
    setDcMotor(MotorState::BRAKE);

    return isSucceded;
}


/* A csap jelenlegi állásszögének mentése egy adott csapálláshoz */
void saveTapAngleTo(TapState state){
    Serial.printf("Save Tap angle to %s state\n", getTapStateString(state));
    saveAngleToTap(state, readTapAngle());
    Serial.println("Saved");
    initTapValues();
    printTapState();
}


bool moveTap(TapState state){
    return moveTap(getAngleByTapState(state));
}

/* Csap beállítása */
bool SetTap(TapState state){

    // Ha abban a helyzetben van a csap, ahol kell lennie
    if(tapState == state) return true; 

    bool isSucceded;

    // A csap állásához igazítja a motort az előre megadott
    // fok alapján
    isSucceded = moveTap(state);

    // Mentjük az állapotot ha sikerült a beállítás
    if(isSucceded)
        tapState = state;

    return isSucceded;
}


void INIT_TAP(){

    printinit("TAP", true);

    // Csap állapotok rendezése
    initTapValues();

    // Állapot kiíratása
    printTapState();

    if(!tap_init_en) { printdone(); return; }

    // Csap alaphelyzetbe állítása
    if(!SetTap(TapState::CLOSE)){
        dropFaulty("Tap error", ERROR_TAP_DEFAULT_STATE);
        printfail();
        return;
    }

    printdone();

}