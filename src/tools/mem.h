#define MEM_H
#ifdef MEM_H

#include <Arduino.h>
#include <Preferences.h>
#include <general/settings.h>

#define MEM_APPID   "ollio"

#define MEM_BLOCKID "blockid"


/* Következő blokk sorszámát adja vissza */
uint32_t getNextBlockNumber();

/* Blokk sorszámának beállítása */
void setBlockNumber(uint32_t);

/* Memória tisztítása */
void mem_clear();

/* Ellenőrzi a memórába meglévő adatokat, ha hiányoznak beírja az alapértéküket */
void mem_init();

#endif