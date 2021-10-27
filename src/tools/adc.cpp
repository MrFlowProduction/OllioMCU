#include <tools/adc.h>

ADS1115 ads(0x48);

/* INIT adc module */
void INIT_ADC(){
    
    printinit("ADS1115 ADC Module", true);
    Serial.print("ADS1X15_LIB_VERSION: ");
    Serial.println(ADS1X15_LIB_VERSION);

    ads.begin();
    

    if(!ads.isConnected()){
        dropFaulty("ADC not available", 101);
        return;
    }

    ads.setGain(0);      // 6.144 volt
    ads.setDataRate(0);  // SLOW
    ads.setMode(1);      // continuous mode
    ads.readADC(0);      // first read to trigger

    isAdcReady = true;
    printdone();
}


/* Olaj szonda voltban */
float readProbeVoltage(){

    // Check State
    if(!isAdcReady) { return 0.0; }

    // Convert to voltage and return
    return ads.readADC(PROBE_PIN) * ads.toVoltage(1);
}


/* Csap elfordálását adja vissza szögben */
int readTapAngle(){
    // Check State
    if(!isAdcReady) { return 0.0; }

    // Read analog voltage
    int voltage = ads.readADC(TAP_PIN) * ads.toVoltage(1) * 1000;

    // Convert to angle
    return map(voltage, 0, 2460, 0, 180);
}

/* Csap jeladó feszültsége */
float readTapVoltage(){
    // Check State
    if(!isAdcReady) { return 0.0; }

    // Convert to voltage and return
    return ads.readADC(TAP_PIN) * ads.toVoltage(1);
}


/* Read ADC Values*/
void adc_reading(){
    probe_votlage = readProbeVoltage();
}