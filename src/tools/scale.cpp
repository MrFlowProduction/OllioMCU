#include <tools/scale.h>

HX711 scale;
//LINKEK
//https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all
//https://github.com/sparkfun/HX711-Load-Cell-Amplifier/tree/master/firmware

// 1. HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 25;
const int LOADCELL_SCK_PIN = 33;

// 2. Adjustment settings
long ZERO_FACTOR = 2117;
long LOADCELL_OFFSET = -7070 / 0.45359237; //LBS HELYETT KG-BAN KAPJUK AZ ÉRTÉKET
const long LOADCELL_DIVIDER = 0.45359237;

float calibration_factor = 56;

/* Inicializálás */
void INIT_SCALE(){
    printinit("SCALE");
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN, 64);
    scale.set_scale(calibration_factor);
    scale.tare();

    if(!scale.wait_ready_timeout(1000)){
        dropFaulty("ADC not available", 103);
        return;
    }

    Serial.println(scale.get_units(SCALE_SAMPLE));
   
    printdone();
}


/* Kalibráció */
void calibrateScale(){

    Serial.println("Calibrating scale, so have to clear everything from scale!");

    Serial.println("Reset Scale");
    scale.set_scale();
    scale.tare();

    Serial.println("Read avarage...");

    long b = scale.read_average(); //Get a baseline reading
    Serial.print("Zero factor (B): "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
    Serial.println(b);

    Serial.println("Press key for continue");

    while(!Serial.available()){ delay(1000); }


    long x = scale.read_average();
    long y = 86000;

    double m = (double)(y-b)/x;

    Serial.print("x: ");
    Serial.println(x);

    Serial.print("y: ");
    Serial.println(y);

    Serial.print("m: ");
    Serial.println(m);

    scale.set_offset(b);
    scale.set_scale(m);
    
}


/* Mérleg olvasása */
float read_scale(){

    float value, counter;

    unsigned long timer = millis() + 1000;

    while(timer > millis()){
        value += scale.read()/100.0;

        counter++;
    }

    return value / counter;
    
    return scale.get_units(SCALE_SAMPLE);
}


/* Refrenciapont mentése */
void scaleZeroPoint(){
    scaleReferencePoint = read_scale();
}


/* Mérleg adatok kiprintelése */
void print_scale_values(){

    Serial.println("Before setting up the scale:");

    //Serial.print("read average: \t\t");
    //Serial.println(scale.read_average(SCALE_SAMPLE));  	// print the average of 20 readings from the ADC

    Serial.print("get units: \t\t");
    Serial.println(read_scale(), 2);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
                            // by the SCALE parameter (not set yet)

    //scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
    //scale.tare();				        // reset the scale to 0

}
