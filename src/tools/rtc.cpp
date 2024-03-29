#include <tools/rtc.h>

RTC_DS3231 rtc;
unsigned long rtc_refresh_timer;

void INIT_RTC(){

    printinit("RTC");

    if(!rtc.begin()){
        dropFaulty("RTC not available", ERROR_RTC);
        return;
    }

    //if(rtc.lostPower()){
    //    dropFaulty("RTC lost power", ERROR_RTC_LOST_POWER);
    //    dateTimeTerminal();
    //}

    // Hőmérséklet kiíratása
    Serial.print("Temperature: ");
    Serial.print(rtcTemp());
    Serial.println("C");

    // Idő kiíratása
    showDate("Now: ", now());

    printdone();
}


void setDate(const DateTime& date){
    rtc.adjust(date);
}

void setDate(int year, int month, int day, int hour, int minute, int second){
    setDate(DateTime(year, month, day, hour, minute, second));
}


DateTime now(){
    return rtc.now();
}


float rtcTemp(){
    return rtc.getTemperature();
}


void showDate(const char* txt, const DateTime& dt) {
    Serial.print(txt);
    Serial.print(' ');
    Serial.print(dt.year(), DEC);
    Serial.print('/');
    Serial.print(dt.month(), DEC);
    Serial.print('/');
    Serial.print(dt.day(), DEC);
    Serial.print(' ');
    Serial.print(dt.hour(), DEC);
    Serial.print(':');
    Serial.print(dt.minute(), DEC);
    Serial.print(':');
    Serial.print(dt.second(), DEC);

    //Serial.print(" = ");
    //Serial.print(dt.unixtime());
    //Serial.print("s / ");
    //Serial.print(dt.unixtime() / 86400L);
    //Serial.print("d since 1970");

    Serial.println();
}


String dateToString(const DateTime dt){
    String str = "";
    str += String(dt.year(), DEC);
    str += '.';

    if(dt.month() < 10) { str += "0"; }
    str += String(dt.month(), DEC);
    str += '.';

    if(dt.day() < 10) { str += "0"; }
    str += String(dt.day(), DEC);

    str += String(' ');

    if(dt.hour() < 10) { str += "0"; }
    str += String(dt.hour(), DEC);

    str += String(':');

    if(dt.minute() < 10) { str += "0"; }
    str += String(dt.minute(), DEC);

    str += String(':');

    if(dt.second() < 10) { str += "0"; }
    str += String(dt.second(), DEC);

    return str;

}



void showTimeSpan(const char* txt, TimeSpan& ts) {
    Serial.print(txt);
    Serial.print(" ");
    Serial.print(ts.days(), DEC);
    Serial.print(" days ");
    Serial.print(ts.hours(), DEC);
    Serial.print(" hours ");
    Serial.print(ts.minutes(), DEC);
    Serial.print(" minutes ");
    Serial.print(ts.seconds(), DEC);
    Serial.print(" seconds (");
    Serial.print(ts.totalseconds(), DEC);
    Serial.print(" total seconds)");
    Serial.println();
}

/* RTC frissítése NTP-ről */
void rtc_refresh(){

    if(RTC_REFRESH == 0) return;

    if(wifiIsConnected && millis() > rtc_refresh_timer){

        struct tm tim;
        if(getLocalTime(&tim)){
            Serial.println("Refresh RTC...");
            setDate(tim.tm_year + 1900, tim.tm_mon + 1, tim.tm_mday, tim.tm_hour, tim.tm_min, tim.tm_sec);
            showDate("RTC Refreshed: ", now());
            rtc_refresh_timer = millis() + (RTC_REFRESH * 1000);
            isRtcOk = true;
        }

        
    }   

}