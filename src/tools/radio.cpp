#include <tools/radio.h>

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

/* Beállítja a jelszót és az ssid-t */
void init_wifi(){
    Serial.print("Connecting to WiFi ..");
    Serial.printf("SSID: %s\nPASS: %s\n", ssid, pass);
    WiFi.begin(ssid, pass);
}

/* Wifi status változás beállítása */
void setWiFiStat(WifiState state){
  
  wifiStat = state;
  
  if(state == WifiState::CONNECTED){
     wifiIsConnected = true;
  }
  else{
    wifiIsConnected = false;
  }
 
  wifiStateHandled = false;
}

/* Wifi Event Handler */
void WiFiEvent(WiFiEvent_t event){
    switch(event) {
        
        case SYSTEM_EVENT_AP_START:
            #ifdef DEBUG
            Serial.println("AP Started");
            #endif
            WiFi.softAPsetHostname(WIFI_AP_SSID);
            break;
            
        case SYSTEM_EVENT_AP_STOP:
            #ifdef DEBUG
            Serial.println("AP Stopped");
            #endif
            break;
            
        case SYSTEM_EVENT_STA_START:
            #ifdef DEBUG
            //Serial.println("\nSTA Started");
            #endif
            Serial.println("\nSTA Started");
            setWiFiStat(WifiState::CONNECTING);
            break;
            
        case SYSTEM_EVENT_STA_CONNECTED:
            #ifdef DEBUG
            Serial.println("\nSTA Connected"); 
            #endif           
            //wifiLed(HIGH);

            Serial.println("\nSTA Connected");
            setWiFiStat(WifiState::CONNECTING);
            
            break;
            
        case SYSTEM_EVENT_AP_STA_GOT_IP6:
            #ifdef DEBUG
            Serial.print("STA IPv6: ");
            Serial.println(WiFi.localIPv6());
            #endif
            break;

        case SYSTEM_EVENT_STA_LOST_IP:
           setWiFiStat(WifiState::DISCONNECTED);
           break;
        
        case SYSTEM_EVENT_STA_GOT_IP:
            Serial.print("\nSTA IPv4: ");
            Serial.println(WiFi.localIP());
            Serial.print("RSSI: ");
            Serial.println(WiFi.RSSI(), DEC);

            setWiFiStat(WifiState::CONNECTED);

            break;
        
        case SYSTEM_EVENT_STA_DISCONNECTED:

            #ifdef DEBUG
            if(wifiIsConnected){            
              Serial.println(F("STA Disconnected"));
            }
            #endif

            setWiFiStat(WifiState::DISCONNECTED);

            break;
        
        case SYSTEM_EVENT_STA_STOP:
            #ifdef DEBUG
            Serial.println("STA Stopped");
            #endif
            setWiFiStat(WifiState::NORADIO);
            break;
        default:
            break;
    }
}



// Print to Serial every available stations
void Wifi_PrintStations(){
  
  Serial.print(F("\nScan Wifi Stations..."));

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  yield();
  
  printdone();
  
    if (n == 0) {
       Serial.println(F("No available station!"));
    } else {
        Serial.print(n);
        Serial.println(F(" station found"));
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(1);
        }
    }
    Serial.println("\n");
  
}


void waitForWifi(int timebox){

    unsigned long timeout = millis() + timebox;

    while(timeout > millis()){
        if(wifiIsConnected) break;
    }

    delay(100);
}


void INIT_RADIO(){
    printinit("WIFI", true);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(false, true);
    delay(100);
    WiFi.onEvent(WiFiEvent);
    init_wifi();    
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    waitForWifi(5000);

    printdone();
}


