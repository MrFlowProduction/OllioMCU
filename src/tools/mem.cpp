#include <tools/mem.h>

Preferences preferences;


#define MEM_APPID           "ollio"
#define MEM_VERSION         "version"
#define MEM_BLOCKID         "blockid"
#define MEM_TAP_CLOSE       "tap_close"
#define MEM_TAP_BARREL      "tap_barrel"
#define MEM_TAP_WATERTANK   "tap_watertank"
#define MEM_TAP_INIT_EN     "tap_init_en"
#define MEM_SCALE_FACTOR    "scale_factor"
#define MEM_SCALE_OFFSET    "scale_offset"



/* Következő blokk sorszámát adja vissza */
uint32_t getNextBlockNumber(){

    preferences.begin(MEM_APPID, false);
    uint32_t blockid = preferences.getUInt(MEM_BLOCKID, 0);
    blockid++;    
    preferences.putUInt(MEM_BLOCKID, blockid);
    preferences.end();

    return blockid;
}

/* Memóriából kiolvas egy int-es értéket */
int getMemInt(const char* key){
    int value;

    preferences.begin(MEM_APPID, true);
    value = preferences.getInt(key);
    preferences.end();

    return value;
}

/* Memóriából kiolvas egy int-es értéket */
uint32_t getMemUint(const char* key){
    uint32_t value;

    preferences.begin(MEM_APPID, true);
    value = preferences.getUInt(key);
    preferences.end();

    return value;
}


/* Memóriából kiolvas egy int-es értéket */
bool getMemBool(const char* key){
    bool value;

    preferences.begin(MEM_APPID, true);
    value = preferences.getBool(key);
    preferences.end();

    return value;
}


/* Memóriából kiolvas egy int-es értéket */
float getMemFloat(const char* key){
    float value;

    preferences.begin(MEM_APPID, true);
    value = preferences.getFloat(key);
    preferences.end();

    return value;
}

/* Memóriából kiolvas egy int-es értéket */
long getMemLong(const char* key){
    long value;

    preferences.begin(MEM_APPID, true);
    value = preferences.getLong(key);
    preferences.end();

    return value;
}


void setMem(const char* key, uint32_t value){
    preferences.begin(MEM_APPID, false);
    preferences.putUInt(key, value);
    preferences.end();
}

void setMem(const char* key, int value){
    preferences.begin(MEM_APPID, false);
    preferences.putInt(key, value);
    preferences.end();
}

void setMem(const char* key, bool value){
    preferences.begin(MEM_APPID, false);
    preferences.putBool(key, value);
    preferences.end();
}

void setMem(const char* key, float value){
    preferences.begin(MEM_APPID, false);
    preferences.putFloat(key, value);
    preferences.end();
}

void setMem(const char* key, long value){
    preferences.begin(MEM_APPID, false);
    preferences.putLong(key, value);
    preferences.end();
}


/* Blokk sorszámának beállítása */
void setBlockNumber(uint32_t value){
    setMem(MEM_BLOCKID, value);
}

/* Memória tisztítása */
void mem_clear(){
    preferences.begin(MEM_APPID, false);
    preferences.clear();
    preferences.end();
}

/* Ellenőrzi, hogy létezik-e a megadott kulcsal adat */
bool mem_check_key(const char* key){
    preferences.begin(MEM_APPID, true);
    bool result = preferences.isKey(key);
    preferences.end();

    return result;
}


/* Beállítás inicializálása, ha még nem létezik létrehozza */
int mem_init_setting(const char* key, int def_value){
    if(!mem_check_key(key)){
        setMem(key, def_value);
        Serial.printf("Creater new setting where KEY: %s and VALUE %d\n", key, def_value);
        return def_value;
    }

    return getMemInt(key);
}


/* Beállítás inicializálása, ha még nem létezik létrehozza */
uint32_t mem_init_setting(const char* key, uint32_t def_value){
    if(!mem_check_key(key)){
        setMem(key, def_value);
        Serial.printf("Creater new setting where KEY: %s and VALUE %d\n", key, def_value);
        return def_value;
    }

    return getMemUint(key);
}


/* Beállítás inicializálása, ha még nem létezik létrehozza */
bool mem_init_setting(const char* key, bool def_value){
    if(!mem_check_key(key)){
        setMem(key, def_value);
        Serial.printf("Creater new setting where KEY: %s and VALUE %d\n", key, def_value);
        return def_value;
    }

    return getMemBool(key);
}


/* Beállítás inicializálása, ha még nem létezik létrehozza */
float mem_init_setting(const char* key, float def_value){
    if(!mem_check_key(key)){
        setMem(key, def_value);
        Serial.printf("Creater new setting where KEY: %s and VALUE %d\n", key, def_value);
        return def_value;
    }

    return getMemFloat(key);
}


/* Beállítás inicializálása, ha még nem létezik létrehozza */
long mem_init_setting(const char* key, long def_value){
    if(!mem_check_key(key)){
        setMem(key, def_value);
        Serial.printf("Creater new setting where KEY: %s and VALUE %d\n", key, def_value);
        return def_value;
    }

    return getMemLong(key);
}



/* Csap állásokhoz tartozó Kulcs a memóriában */
const char* tapMemKey(TapState state){

    switch (state)
    {
        case TapState::CLOSE:
            return MEM_TAP_CLOSE;

        case TapState::WATERTANK:
            return MEM_TAP_WATERTANK;

        case TapState::BARREL:
            return MEM_TAP_BARREL;

        default:
            return "";
    }
}


/* Beállítás inicializálása, ha még nem létezik létrehozza */
void saveAngleToTap(TapState state, int angle){
    Serial.printf("Angle: %d\n", angle);
    setMem(tapMemKey(state), angle);
    mem_init();
}

/* Csap init paraméterének módosítása */
void changeTapInitEn(bool enable){
    setMem(MEM_TAP_INIT_EN, enable);
    printdone();
}

/* Csap init paraméterének módosítása */
void saveScaleCalibFactor(float value){
    setMem(MEM_SCALE_FACTOR, value);
}

void saveScaleOffset(long offset){
    setMem(MEM_SCALE_OFFSET, offset);
}


/* Ellenőrzi a memórába meglévő adatokat, ha hiányoznak beírja az alapértéküket */
void mem_init(){

    if(!mem_check_key(MEM_BLOCKID)){
        setBlockNumber(BLOCK_NUMBER);
        Serial.println("Block ID set to default");
    }

    // Tap close
    tap_closed_angle = mem_init_setting(MEM_TAP_CLOSE, tap_closed_angle);

    // Tap barrel
    tap_barrel_angle = mem_init_setting(MEM_TAP_BARREL, tap_barrel_angle);

    // Tap watertank
    tap_watertank_angle = mem_init_setting(MEM_TAP_WATERTANK, tap_watertank_angle);

    // Tap init enable
    tap_init_en = mem_init_setting(MEM_TAP_INIT_EN, tap_init_en);

    // Scale calib factor
    scale_calib_factor = mem_init_setting(MEM_SCALE_FACTOR, scale_calib_factor);

    // Scale last offset
    scale_last_offset = mem_init_setting(MEM_SCALE_OFFSET, scale_last_offset);

}
