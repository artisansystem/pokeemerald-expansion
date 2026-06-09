#ifndef GUARD_POKEDEX_AREA_SCREEN_H
#define GUARD_POKEDEX_AREA_SCREEN_H

#include "rtc.h"
#include "seasons.h"
#include "area_ranks.h"

extern u8 gAreaSeason;
extern u8 gAreaTimeOfDay;
extern u8 gAreaRank;

enum PokedexAreaScreenState
{
    DEX_SHOW_AREA_SCREEN,
    DEX_UPDATE_AREA_SCREEN
};

void DisplayPokedexAreaScreen(enum Species species, u8 *screenSwitchState, enum Seasons season, enum TimeOfDay timeOfDay, enum AreaRank areaRank, enum PokedexAreaScreenState areaState);
void ShowPokedexAreaScreen(enum Species species, u8 *screenSwitchState);

#endif // GUARD_POKEDEX_AREA_SCREEN_H
