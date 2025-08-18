#ifndef GUARD_SEASONS_H
#define GUARD_SEASONS_H

#include "global.h"
#include "rtc.h"
#include "config/overworld.h"

// SEASONS_COUNT must be last
enum Seasons
{
    SEASON_SPRING,
    SEASON_SUMMER,
    SEASON_AUTUMN,
    SEASON_WINTER,
    SEASONS_COUNT,
};

#define SEASON_DEFAULT   0

struct SeasonTime
{
    enum Seasons season;
    enum TimeOfDay timeOfDay;
};

void AdvanceSeason(void);
enum Seasons CurrentSeasonGet(void);
enum Seasons CurrentSeasonGetForDex(void);
void CurrentSeasonSet(enum Seasons new_season);
enum Seasons NextSeasonGet(enum Seasons current_season);
enum Seasons TryIncrementSeason(enum Seasons season);
enum Seasons TryDecrementSeason(enum Seasons season);

#endif // GUARD_SEASONS_H