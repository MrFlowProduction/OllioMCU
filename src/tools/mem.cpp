#include <tools/mem.h>

Preferences preferences;

/* Következő blokk sorszámát adja vissza */
uint32_t getNextBlockNumber(){

    preferences.begin(MEM_APPID, false);
    uint32_t blockid = preferences.getUInt(MEM_BLOCKID, 0);
    blockid++;    
    preferences.putUInt(MEM_BLOCKID, blockid);
    preferences.end();

    return blockid;
}

/* Blokk sorszámának beállítása */
void setBlockNumber(uint32_t value){
    preferences.begin(MEM_APPID, false);
    preferences.putUInt(MEM_BLOCKID, value);
    preferences.end();
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

/* Ellenőrzi a memórába meglévő adatokat, ha hiányoznak beírja az alapértéküket */
void mem_init(){
    if(!mem_check_key(MEM_BLOCKID)){
        setBlockNumber(BLOCK_NUMBER);
        Serial.println("MEM - Set new block number is OK!");
    }
}
