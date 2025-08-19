#include "global.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "event_data.h"
#include "seasons.h"
#include "constants/vars.h"

void AdvanceSeason(void) 
{
    CurrentSeasonSet(NextSeasonGet(CurrentSeasonGet()));
}

enum Seasons CurrentSeasonGet(void) 
{
    return VarGet(VAR_CURRENT_SEASON);
}

enum Seasons CurrentSeasonGetForDex(void)
{
    return OW_SEASONAL_ENCOUNTERS ? CurrentSeasonGet() : OW_SEASON_FALLBACK;
}

void CurrentSeasonSet(enum Seasons new_season) 
{
    VarSet(VAR_CURRENT_SEASON, new_season);
}

enum Seasons NextSeasonGet(enum Seasons current_season) {
    current_season++;
    if (current_season >= SEASONS_COUNT)
        return SEASON_SPRING;
    return current_season;
}

enum Seasons TryIncrementSeason(enum Seasons season)
{
    return season == SEASON_WINTER ? SEASON_SPRING : season + 1;
}

enum Seasons TryDecrementSeason(enum Seasons season)
{
    return season == SEASON_SPRING ? SEASON_WINTER : season - 1;
}