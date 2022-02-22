#define MEM_H
#ifdef MEM_H

#include <Arduino.h>
#include <Preferences.h>
#include <general/settings.h>
#include <general/globals.h>
#include <tools/diag.h>


/* Következő blokk sorszámát adja vissza */
uint32_t getNextBlockNumber();

/* Memória írása (UINT32) */
void setMem(const char*, uint32_t);

/* Memória írása (INT) */
void setMem(const char*, int);

/* Memória írása (BOOL) */
void setMem(const char*, bool);

/* Blokk sorszámának beállítása */
void setBlockNumber(uint32_t);

/* Memória tisztítása */
void mem_clear(void);

/* Beállítás inicializálása, ha még nem létezik létrehozza */
void saveAngleToTap(TapState, int);

/* Csap alaphelyzetbe állítás paraméterének változtatása */
void changeTapInitEn(bool);

/* Mérleg kalibráció érték módosítása */
void saveScaleCalibFactor(float value);

/* Mérleg offset mentése */
void saveScaleOffset(long offset);

/* Ellenőrzi a memórába meglévő adatokat, ha hiányoznak beírja az alapértéküket */
void mem_init(void);

#endif