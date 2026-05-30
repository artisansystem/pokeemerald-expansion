#include "global.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "event_data.h"
#include "area_ranks.h"
#include "constants/vars.h"
#include "region_map.h"
#include "fieldmap.h"
#include "regions.h"

void IncreaseDawnsingerAreaRank(void)
{
    CurrentDawnsingerRankSet(NextRankGet(CurrentDawnsingerRankGet()));
}

void IncreaseLockwoodAreaRank(void)
{
    CurrentLockwoodRankSet(NextRankGet(CurrentLockwoodRankGet()));
}

void IncreaseSummerspellAreaRank(void)
{
    CurrentSummerspellRankSet(NextRankGet(CurrentSummerspellRankGet()));
}

void IncreaseWillowbloomAreaRank(void)
{
    CurrentWillowbloomRankSet(NextRankGet(CurrentWillowbloomRankGet()));
}

void IncreaseTitanblazeAreaRank(void)
{
    CurrentTitanblazeRankSet(NextRankGet(CurrentTitanblazeRankGet()));
}

void IncreaseRosesongAreaRank(void)
{
    CurrentRosesongRankSet(NextRankGet(CurrentRosesongRankGet()));
}

void IncreaseWisemoreAreaRank(void)
{
    CurrentWisemoreRankSet(NextRankGet(CurrentWisemoreRankGet()));
}

void IncreaseAuberonAreaRank(void)
{
    CurrentAuberonRankSet(NextRankGet(CurrentAuberonRankGet()));
}

enum AreaRank CurrentDawnsingerRankGet(void)
{
    return VarGet(VAR_DAWNSINGER_SECTOR_RANK);
}

enum AreaRank CurrentLockwoodRankGet(void)
{
    return VarGet(VAR_LOCKWOOD_SECTOR_RANK);
}

enum AreaRank CurrentSummerspellRankGet(void)
{
    return VarGet(VAR_SUMMERSPELL_SECTOR_RANK);
}

enum AreaRank CurrentWillowbloomRankGet(void)
{
    return VarGet(VAR_WILLOWBLOOM_SECTOR_RANK);
}

enum AreaRank CurrentTitanblazeRankGet(void)
{
    return VarGet(VAR_TITANBLAZE_SECTOR_RANK);
}

enum AreaRank CurrentRosesongRankGet(void)
{
    return VarGet(VAR_ROSESONG_SECTOR_RANK);
}

enum AreaRank CurrentWisemoreRankGet(void)
{
    return VarGet(VAR_WISEMORE_SECTOR_RANK);
}

enum AreaRank CurrentAuberonRankGet(void)
{
    return VarGet(VAR_AUBERON_SECTOR_RANK);
}

void CurrentDawnsingerRankSet(enum AreaRank new_rank)
{
    VarSet(VAR_DAWNSINGER_SECTOR_RANK, new_rank);
}

void CurrentLockwoodRankSet(enum AreaRank new_rank)
{
    VarSet(VAR_LOCKWOOD_SECTOR_RANK, new_rank);
}

void CurrentSummerspellRankSet(enum AreaRank new_rank)
{
    VarSet(VAR_SUMMERSPELL_SECTOR_RANK, new_rank);
}

void CurrentWillowbloomRankSet(enum AreaRank new_rank)
{
    VarSet(VAR_WILLOWBLOOM_SECTOR_RANK, new_rank);
}

void CurrentTitanblazeRankSet(enum AreaRank new_rank)
{
    VarSet(VAR_TITANBLAZE_SECTOR_RANK, new_rank);
}

void CurrentRosesongRankSet(enum AreaRank new_rank)
{
    VarSet(VAR_ROSESONG_SECTOR_RANK, new_rank);
}

void CurrentWisemoreRankSet(enum AreaRank new_rank)
{
    VarSet(VAR_WISEMORE_SECTOR_RANK, new_rank);
}

void CurrentAuberonRankSet(enum AreaRank new_rank)
{
    VarSet(VAR_AUBERON_SECTOR_RANK, new_rank);
}

enum AreaRank NextRankGet(enum AreaRank current_rank)
{
    current_rank++;
    if (current_rank >= AREA_RANK_COUNT)
        return AREA_RANK_ADVANCED;
    return current_rank;
}

enum AreaRank PreviousRankGet(enum AreaRank current_rank)
{
    current_rank--;
    if (current_rank <= AREA_RANK_STARTER)
        return AREA_RANK_STARTER;
    return current_rank;
}

enum AreaRank CurrentAreaRankGet(void)
{
    enum GardenSubRegion gardenSubRegion = GetGardenSubregion(gMapHeader.regionMapSectionId); 

    switch(gardenSubRegion)
        {
            case GARDEN_SUBREGION_LOCKWOOD:
                return CurrentLockwoodRankGet();
            case GARDEN_SUBREGION_SUMMERSPELL:
                return CurrentSummerspellRankGet();
            case GARDEN_SUBREGION_WILLOWBLOOM:
                return CurrentWillowbloomRankGet();
            case GARDEN_SUBREGION_TITANBLAZE:
                return CurrentTitanblazeRankGet();
            case GARDEN_SUBREGION_ROSESONG:
                return CurrentRosesongRankGet();
            case GARDEN_SUBREGION_WISEMORE:
                return CurrentWisemoreRankGet();
            case GARDEN_SUBREGION_AUBERON:
                return CurrentAuberonRankGet();
            case GARDEN_SUBREGION_DAWNSINGER:
            default:
                return CurrentDawnsingerRankGet();
        }
}