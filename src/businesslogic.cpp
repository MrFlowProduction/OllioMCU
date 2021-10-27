#include <businesslogic.h>


enum _ErrorSource{
    Unknown,
    Lid
};

_ErrorSource _source = Unknown;


/* Állapot váltása */
void ChangeState(MachineState newState){

    if(statePoint == newState){
        stateChanged = false;
        return;
    }

    statePoint = newState;
    stateChanged = true;
}



/* Alapállapot csak kizárólag az indító állapotot figyeli */
void DefaultState(){
    
    // Állapotváltozás
    if(stateChanged){
        
        isButtonPressed = false;
        isDoorChanged = true;
        stateChanged = false;
        setServiceLight(OFF);
    }

    // Fedél figyelése
    if(isDoorChanged){

        if(isDoorOpened){   // Fedél nyitva
            setButtonLight(OFF);
            closeDownScreen();
            isButtonPressed = false;
        }
        else{               // Fedél csukva
            defaultScreen();
            setButtonLight(ON);
        }

        isDoorChanged = false;
    }

    // Szervizmódba lépés
    if(isServiceButtonPressed){
        ChangeState(MachineState::SERVICE);
        isServiceButtonPressed = false;
    }

    // Mérés indítása
    if(!isDoorOpened && isButtonPressed && !isTankFull){
        ChangeState(MachineState::SHORTING);
        isButtonPressed = false;
    }

    isButtonPressed = false;
}


/* Zárás Állapot */
void ClosingState(){
    task_scale_isEnabled = false;
    task_ads_isEnabled = false;
    SetTap(TapState::CLOSE);
    meas = Measurement();
}


/* Indulási Állapot */
void NoneState(){

    setNoneScreen();
    setButtonLight(ON);

    delay(3000);

    ChangeState(MachineState::DEF);
    setButtonLight(OFF);
}

/* Betöltött Olaj osztályozása */
void ShortingState(){
    
    // Állapotváltozás
    if(stateChanged){
        setShortingScreen();
        setButtonLight(OFF);
        globalTimer = millis() + MEAS_TIME;
        stateChanged = false;
    }

    // Kijelző frissítése
    updateShortingScreen();

    // DELAY a rendszerben
    if(globalTimer > millis()){ return; }

    setProbeSupply(ON);

    delay(1000);

    // Olaj minőségének ellenőrzése
    meas.quality = readProbeVoltage();
    meas.isGoodQuality = readProbeVoltage() < QLTY_VOLTAGE;

    if(meas.isGoodQuality){
        ChangeState(MachineState::MEASURE);
    }
    else{
        ChangeState(MachineState::SEPARATE);
    }

    setProbeSupply(OFF);

}


/* Beöltött olaj tisztítása */
void SeparateState(){

    // Állapotváltozás
    if(stateChanged){
        setProbeSupply(ON);
        setSeparateScreen();

        /* Csap beállítása */
        SetTap(TapState::TANK);

        // Időzítés (Timeout)
        globalTimer = millis() + SEPARATE_TIMEOUT;
        stateChanged = false;
    }

    updateSeparateScreen();

    // Timeout (időtúllépés)
    if(globalTimer < millis()){ return; }    

    // Olaj minőségének ellenőrzése
    if(readProbeVoltage() < QLTY_VOLTAGE){
        ChangeState(MachineState::MEASURE);
    }

}

/* Mérés */
void MeasState(){
   
   // Állapotváltozás
    if(stateChanged){
        setProbeSupply(ON);
        setMeasureScreen();

        last_meas = 0;

        // Mérleg referenciapont
        scaleZeroPoint();

        /* Csap beállítása */
        SetTap(TapState::BARREL);

        // Időzítés (Timeout)
        globalTimer = millis() + SEPARATE_TIMEOUT;
        stateChanged = false;
    }

    float result = read_scale();

    // Mérés kiértékelése, kevesebb nem lehet
    if(result > last_meas){
        last_meas = result;
    }

    // Mérleg értékének kiírása
    updateMeasure(last_meas);

    // Ha már üres a felső edény, akkor lezárjuk a folyamatot
    if(readProbeVoltage() < NO_LIQUID_VOLT){
        /* Csap Zárása */
        SetTap(TapState::BARREL);
        setProbeSupply(OFF);
        // TODO: Read Weight and save

        meas.weight = last_meas;

        // Nyomtatás
        ChangeState(MachineState::PRINTING);
    }
}


/* Nyomtatás */
void PrintingState(){

    // Állapotváltozás
    if(stateChanged){
        setPrintingScreen();
        stateChanged = false;
    }

    // Nyomtatás
    printBlock();

    // Visszaállás alapállapotra
    ChangeState(MachineState::SYSCHECK);

}


void ServiceState(){

    // Állapotváltozás
    if(stateChanged){
        //setServiceScreen();
        lcd.clear();
        stateChanged = false;
    }

    blink = !blink;
    setServiceLight(blink);
    setButtonLight(blink);

    setServiceScreen();

    if(isServiceButtonPressed){
        isServiceButtonPressed = false;
    }

    if(isButtonPressed)
        isButtonPressed = false;
}


void FaultState(){

}


void SystemCheckState(){

    // Állapotváltozás
    if(stateChanged){
        setSyscheckScreen();
        stateChanged = false;
        return;
    }

    // Rendszerteszt indítása
    syscheck();

    ChangeState(MachineState::DEF);
}



void Reset(){
    error_code = ERROR_NONE;
}


/* Hibaállapot, amit üzemközben jön elő */
void ErrorState(){
   
}



void stateMachine(){

    switch (statePoint)
    {

        case NONE:
            NoneState();
            break;

        case DEF:
            DefaultState();
            break;

        case SHORTING:
            ShortingState();
            break;

        case SEPARATE:
            SeparateState();
            break;

        case MEASURE:
            MeasState();
            break;
        
        case PRINTING:
            PrintingState();
            break;
        
        case CLOSING:
            ClosingState();
            break;

        case SERVICE:
            ServiceState();
            break;

        case SYSCHECK:
            SystemCheckState();
            break;
        
        case FAULT: // Fedél nyitva üzem közben, szenzor hiba, szelep hiba, kijelző hiba, rendszer hiba
            ErrorState();
            break;

        default:
            break;
    }

}


/* Alapvető rendszer cuccok inicializálása */
void INIT_MACHINE(){
    Serial.println(F("\n================= Ollio Firmware =================\nVersion: "));
    Serial.println(VERSION);
    Serial.print(F("Creator: "));
    Serial.println(CREATOR);
    print_sysinfo();
    mem_init();
}