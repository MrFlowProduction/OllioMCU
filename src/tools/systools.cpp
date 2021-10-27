#include <tools/systools.h>

// Checking address and return error code
byte i2c_address_check(byte address){
  Wire.beginTransmission(address);
  delay(2);
  return Wire.endTransmission();
}


// I2C address scanner (Serial)
void i2c_scanner(){
  byte error, address;
  uint8_t nDevices;
  
  delay(15); // Sensors PowerUp Time
  Wire.begin();

  Serial.println(F("\nScanning..."));

  nDevices = 0;
   for(address = 0; address <= 127; address++ )
  {
     error = i2c_address_check(address);

    if (error == 0)
    {
      Serial.print(F("I2C device found at address 0x"));
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(" !");

      nDevices++;
    }
    else if (error==4)
    {
       Serial.print(F("Unknow error at address 0x"));
       if (address<16)
        Serial.print("0");
       Serial.println(address,HEX);
     }
     delay(20);
   }
   if (nDevices == 0)
     printfail();
   else
     printdone();
}


/* ESP32 CHIP ID lekérdezése (MAC) */
uint32_t get_id(){

  uint32_t chipId;

  for(int i=0; i<17; i=i+8) {
	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}

  return chipId;
}


/* Kiprinteli pár rendszer infót soros portra */
void print_sysinfo(){
  Serial.println(F("\n===== System Info ====="));
  Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
	Serial.printf("This chip has %d cores\n", ESP.getChipCores());
}