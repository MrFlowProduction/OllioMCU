#include <tools/tap.h>


/* Csap beállítása */
bool SetTap(TapState state){

    if(tapState == state) { return; }

    bool isSucceded;

    switch (state)
    {
        case TapState::CLOSE:
            isSucceded = moveTap(TAP_CLOSED);
            break;

        case TapState::WATERTANK:
            isSucceded = moveTap(TAP_WATERTANK);
            break;

        case TapState::BARREL:
            isSucceded = moveTap(TAP_BARREL);
            break;
        
        default:
            break;
    }

    // Mentjük az állapotot ha sikerült a beállítás
    if(isSucceded)
        tapState = state;

    return isSucceded;
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
    if(currentAngle > angle){
        setDcMotor(MotorState::FORWARD);
    }
    else{
        setDcMotor(MotorState::BACKWARD);
    }

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