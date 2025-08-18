#ifndef GUARD_POKEDEX_AREA_SCREEN_H
#define GUARD_POKEDEX_AREA_SCREEN_H

#include "rtc.h"
#include "seasons.h"

extern u8 gAreaTimeOfDay;
extern u8 gAreaSeason;

enum PokedexAreaScreenState
{
    DEX_SHOW_AREA_SCREEN,
    DEX_UPDATE_AREA_SCREEN
};

void DisplayPokedexAreaScreen(u16 species, u8 *screenSwitchState, enum Seasons season, enum TimeOfDay timeOfDay, enum PokedexAreaScreenState areaState);
void ShowPokedexAreaScreen(u16 species, u8 *screenSwitchState);

#endif // GUARD_POKEDEX_AREA_SCREEN_H
