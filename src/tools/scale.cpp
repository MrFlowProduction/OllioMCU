#include <tools/scale.h>

HX711 scale;
//LINKEK
//https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all
//https://github.com/sparkfun/HX711-Load-Cell-Amplifier/tree/master/firmware

// 1. HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 25;
const int LOADCELL_SCK_PIN = 33;

#define LB2KG  0.45352

/* Inicializálás */
void INIT_SCALE(){
    printinit("SCALE", true);

    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN, 64);
    scale.set_scale(scale_calib_factor / LB2KG);
    
    // Még nincs offset, akkor az aktuálist veszi annak
    if(scale_last_offset == 0){
        saveEmptyBarrelPoint();
    }

    // Már van mentve offset, akkor azt állítja be
    else 
        scale.set_offset(scale_last_offset);
    

    if(!scale.wait_ready_timeout(1000)){
        dropFaulty("ADC not available", 103);
        return;
    }

    Serial.printf("Calib factor: %f\n", scale_calib_factor);
    Serial.println(scale.get_units(SCALE_SAMPLE));
   
    printdone();
}


/* Mérleg kalibrálása */
void calibrateScale(){
    // calibiation
    float CALWEIGHT = 4.0;
    float calibration_factor = -7050;
    boolean done = false;
    uint8_t flipDirCount = 0;
    int8_t direction = 1;
    uint8_t dirScale = 100;
    double data = abs(scale.get_units());
    double prevData = data;
    

    while (!done)
    {
      // get data
      data = abs(scale.get_units());
      Serial.println("data = " + String(data, 2));
      Serial.println("abs = " + String(abs(data - CALWEIGHT), 4));
      Serial.println("calibration_factor = " + String(calibration_factor));
      // if not match
      if (abs(data - CALWEIGHT) >= 0.01)
      {
        if (abs(data - CALWEIGHT) < abs(prevData - CALWEIGHT) && direction != 1 && data < CALWEIGHT)
        {
          direction = 1;
          flipDirCount++;
        }
        else if (abs(data - CALWEIGHT) >= abs(prevData - CALWEIGHT) && direction != -1 && data > CALWEIGHT)
        {
          direction = -1;
          flipDirCount++;
        }

        if (flipDirCount > 2)
        {
          if (dirScale != 1)
          {
            dirScale = dirScale / 10;
            flipDirCount = 0;
            Serial.println("dirScale = " + String(dirScale));
          }
        }
        // set new factor 
        calibration_factor += direction * dirScale;
        scale.set_scale(calibration_factor / LB2KG);
        //short delay
        delay(5);
        // keep old data 
        prevData = data;
      }
      // if match
      else
      {
        Serial.println("NEW currentOffset = " + String(scale_last_offset));
        Serial.println("NEW calibration_factor = " + String(calibration_factor));
        done = true;
      }

    } // end while

  scale.set_offset(scale_last_offset);
  saveScaleCalibFactor(calibration_factor);
  Serial.println("setup done ...");
}

/* Mérleg olvasása */
float read_scale(){
    return scale.get_units(SCALE_SAMPLE);
}

/* Refrenciapont mentése */
void scaleZeroPoint(){
    scale.tare();
}

/* Üres hordó offset mentése */
void saveEmptyBarrelPoint(){
    scale.tare();
    scale_last_offset = scale.get_offset();
    saveScaleOffset(scale_last_offset);
}

/* Mérleg alaphelyzetbe állítása */
void resetScale(){
    scale.set_offset(scale_last_offset);
}


/* Mérleg adatok kiprintelése */
void print_scale_values(){

    Serial.printf("Scale calib: %d\n", scale_calib_factor);
    Serial.printf("Scale offset: %d\n", scale_last_offset);

    Serial.print("get units: \t\t");
    Serial.println(read_scale(), 2);	// print the average of 5 readings from the ADC minus tare weight (not set) divided

}
