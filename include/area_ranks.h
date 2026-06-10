#ifndef GUARD_AREA_RANKS_H
#define GUARD_AREA_RANKS_H

#include "global.h"
#include "rtc.h"
#include "seasons.h"

enum AreaRank
{
    AREA_RANK_STARTER,
    AREA_RANK_STANDARD,
    AREA_RANK_ADVANCED,
    AREA_RANK_COUNT,
};

#define AREA_RANK_DEFAULT 0

struct SeasonTimeRank
{
    enum Seasons season;
    enum TimeOfDay timeOfDay;
    enum AreaRank areaRank;
};

// Increase Area Rank, Per Sector
void IncreaseDawnsingerAreaRank(void);
void IncreaseLockwoodAreaRank(void);
void IncreaseSummerspellAreaRank(void);
void IncreaseWillowbloomAreaRank(void);
void IncreaseTitanblazeAreaRank(void);
void IncreaseRosesongAreaRank(void);
void IncreaseWisemoreAreaRank(void);
void IncreaseAuberonAreaRank(void);

// Get Current Rank, Per Sector
enum AreaRank CurrentDawnsingerRankGet(void);
enum AreaRank CurrentLockwoodRankGet(void);
enum AreaRank CurrentSummerspellRankGet(void);
enum AreaRank CurrentWillowbloomRankGet(void);
enum AreaRank CurrentTitanblazeRankGet(void);
enum AreaRank CurrentRosesongRankGet(void);
enum AreaRank CurrentWisemoreRankGet(void);
enum AreaRank CurrentAuberonRankGet(void);

// Set Area Rank, Per Sector
void CurrentDawnsingerRankSet(enum AreaRank new_rank);
void CurrentLockwoodRankSet(enum AreaRank new_rank);
void CurrentSummerspellRankSet(enum AreaRank new_rank);
void CurrentWillowbloomRankSet(enum AreaRank new_rank);
void CurrentTitanblazeRankSet(enum AreaRank new_rank);
void CurrentRosesongRankSet(enum AreaRank new_rank);
void CurrentWisemoreRankSet(enum AreaRank new_rank);
void CurrentAuberonRankSet(enum AreaRank new_rank);

enum AreaRank NextRankGet(enum AreaRank current_rank);
enum AreaRank PreviousRankGet(enum AreaRank current_rank);
enum AreaRank CurrentAreaRankGet(void);

#endif // GUARD_AREA_RANKS_H