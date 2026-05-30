import json
import re

IS_TIME_ENABLED       = False
IS_SEASONS_ENABLED    = False
DEXNAV_ENABLED        = False

# C string vars
define                = "#define"
ENCOUNTER_CHANCE      = "ENCOUNTER_CHANCE"
SLOT                  = "SLOT"
TOTAL                 = "TOTAL"
NULL                  = "NULL"
UNDEFINED             = "UNDEFINED"
MAP_UNDEFINED         = "MAP_UNDEFINED"

# encounter group header types, filled out programmatically
MON_HEADERS = []

# mon encounter group types
fieldData = []
fieldInfoStrings = []
fieldStrings = []

#season encounter data
SEASON_DEFAULT     = ""
SEASON_DEFAULT_LABEL = "SEASON_DEFAULT"
SEASON_DEFAULT_INDEX = 0
SEASONS_COUNT = SEASON_DEFAULT_INDEX + 1

# time of day encounter data
TIME_DEFAULT       = ""
TIME_DEFAULT_LABEL = "TIME_OF_DAY_DEFAULT"
TIME_DEFAULT_INDEX = 0
TIMES_OF_DAY_COUNT = TIME_DEFAULT_INDEX + 1

# struct building blocks
baseStruct          = "const struct WildPokemon"
structLabel         = ""
structMonType       = ""
structSeason        = ""
structTime          = ""
structMap           = ""

structInfo          = "Info"
structHeader        = "Header"
structArrayAssign   = "[] ="

baseStructLabel     = ""
baseStructContent   = []
infoStructString    = ""
infoStructRate      = 0
infoStructContent   = []
headerStructLabel   = ""
headerStructContent = {}
headerStructTable   = {}
headerIndex = 0

# map header data variables
hLabel       = ""
hForMaps     = True
headersArray = [headerIndex]

# debug output control
mainSwitch                      = True
printWarningAndInclude          = mainSwitch
printEncounterHeaders           = mainSwitch
printEncounterRateMacros        = mainSwitch
printEncounterStructsInfoString = mainSwitch
printEncounterStructs           = mainSwitch

class Seasons():
    def __init__(self):
        self.vals = []
        self.lvals = []
        self.fvals = []
        self.count = 0

    def __len__(self):
        return self.count
    
    # for debugging purposes
    def __str__(self):
        return str([self.vals, self.lvals, self.fvals, self.count])

    def add(self, val):
        self.vals.append(val)
        self.lvals.append(val.lower())
        self.fvals.append(GetSeasonLabelFromString(val).capitalize())
        self.count += 1
    
    def indexOf(self, val):
        tempArr = [self.vals, self.lvals, self.fvals]

        for tvals in tempArr:
            i = 0
            for season in tvals:
                if val in season:
                    return i

                i += 1
        # return -1 here so it returns a consistent type and can be checked against < 0
        return -1

class TimeOfDay():
    def __init__(self):
        self.vals = []
        self.lvals = []
        self.fvals = []
        self.count = 0

    def __len__(self):
        return self.count
    
    # for debugging purposes
    def __str__(self):
        return str([self.vals, self.lvals, self.fvals, self.count])

    def add(self, val):
        self.vals.append(val)
        self.lvals.append(val.lower())
        self.fvals.append(GetTimeLabelFromString(val).capitalize())
        self.count += 1
    
    def indexOf(self, val):
        tempArr = [self.vals, self.lvals, self.fvals]

        for tvals in tempArr:
            i = 0
            for time in tvals:
                if val in time:
                    return i

                i += 1
        # return -1 here so it returns a consistent type and can be checked against < 0
        return -1


def ImportWildEncounterFile():
    # make sure we're in the right directory before anything else
    if not os.path.exists("Makefile"):
        print("Please run this script from the project's root folder.")
        quit()

    global MON_HEADERS

    global SEASONS
    SEASONS= SetupUserSeasonsEnum(Seasons())

    global TIME_OF_DAY
    TIME_OF_DAY = SetupUserTimeEnum(TimeOfDay())

    global IS_SEASONS_ENABLED
    global SEASONS_COUNT
    if IsSeasonsEnabled():
        IS_SEASONS_ENABLED = True
        SEASONS_COUNT = len(SEASONS)

    global IS_TIME_ENABLED
    global TIMES_OF_DAY_COUNT
    if IsTimeEnabled():
        IS_TIME_ENABLED = True
        TIMES_OF_DAY_COUNT = len(TIME_OF_DAY)
    
    global DEXNAV_ENABLED
    DEXNAV_ENABLED = IsDexnavEnabled()

    global fieldInfoStrings
    global fieldStrings
    global structLabel
    global structMonType
    global structSeason
    global structTime
    global structMap
    global baseStructLabel
    global baseStructContent
    global infoStructString
    global infoStructRate
    global headerStructLabel
    global headerStructContent
    global hLabel
    global headersArray
    global encounterTotalCount
    global encounterCount
    global headerIndex
    global fieldData
    global tabStr
    tabStr = "    "

    wFile = open("src/data/wild_encounters.json")
    wData = json.load(wFile)

    encounterTotalCount = []
    encounterCount = []
    groupCount = 0
    while groupCount < len(wData["wild_encounter_groups"]):
        encounterTotalCount.append(0)
        encounterCount.append(0)
        groupCount += 1

    for data in wData["wild_encounter_groups"]:
        wEncounters = wData["wild_encounter_groups"][headerIndex]["encounters"]
        headerSuffix = structHeader + "s"

        if data["label"]:
            hLabel = wData["wild_encounter_groups"][headerIndex]["label"]
            if headerSuffix in hLabel:
                hLabel = hLabel[:len(hLabel) - len(headerSuffix)]
            MON_HEADERS.append(hLabel)

        if data["for_maps"]:
            hForMaps = wData["wild_encounter_groups"][headerIndex]["for_maps"]

        if headerIndex == 0:
            wFields = wData["wild_encounter_groups"][headerIndex]["fields"]
            fieldCounter = 0
            for field in wFields:
                if not CheckFieldDataDupes(field["type"]):
                    AddFieldData(fieldCounter, field["type"], field["encounter_rates"])

                if "groups" in field:
                    fieldData[fieldCounter]["groups"] = field["groups"]

                """ 
                    hidden mons need a special bit of logic since they're not in the vanilla
                    wild_encounters.json file, but the code expects them to be there
                """
                hidden_mons = "hidden_mons"
                if (fieldCounter == len(wFields) - 1) and not CheckFieldDataDupes(hidden_mons):
                    hidden_dummy_rates = [1, 0]
                    AddFieldData(fieldCounter + 1, hidden_mons, hidden_dummy_rates)

                fieldCounter += 1

            if printWarningAndInclude:
                PrintGeneratedWarningText()
                print('#include "rtc.h"')
                print('#include "seasons.h"')
                print("\n")

            PrintEncounterRateMacros()

        for encounter in wEncounters:
            if "map" in encounter:
                structMap = encounter["map"]
            else:
                structMap = encounter["base_label"]

            structLabel = encounter["base_label"]

            if encounterTotalCount[headerIndex] != len(wEncounters):
                encounterTotalCount[headerIndex] = len(wEncounters)

            encounterCount[headerIndex] += 1
            headersArray = []

            structSeason = SEASON_DEFAULT_INDEX
            if IS_SEASONS_ENABLED:
                seasonCounter = 0
                while seasonCounter < SEASONS_COUNT:
                    tempfSeason = f"_{SEASONS.fvals[seasonCounter]}"
                    tempSeason = SEASONS.vals[seasonCounter]
                    if tempfSeason in structLabel or tempSeason in structLabel:
                        structSeason = seasonCounter

                    seasonCounter += 1
            
            structTime = TIME_DEFAULT_INDEX
            if IS_TIME_ENABLED:
                timeCounter = 0
                while timeCounter < TIMES_OF_DAY_COUNT:
                    tempfTime = f"_{TIME_OF_DAY.fvals[timeCounter]}"
                    tempTime = TIME_OF_DAY.vals[timeCounter]
                    if tempfTime in structLabel or tempTime in structLabel:
                        structTime = timeCounter

                    timeCounter += 1
                    
            fieldCounter = 0
            fieldInfoStrings = []
            while fieldCounter < len(fieldData):
                fieldInfoStrings.append("")
                fieldStrings.append("")
                fieldCounter += 1

            fieldCounter = 0
            while fieldCounter < len(fieldData):
                for areaTable in encounter:
                    if fieldData[fieldCounter]["name"] in areaTable:
                        structMonType = fieldData[fieldCounter]["pascalName"]
                        if f"_{SEASONS.fvals[structTime]}" and f"_{TIME_OF_DAY.fvals[structTime]}" in structLabel:
                            fieldInfoStrings[fieldCounter] = f"{structLabel}_{structMonType}{structInfo}"
                            fieldStrings[fieldCounter] = f"{structLabel}_{structMonType}"
                        else:
                            fieldInfoStrings[fieldCounter] = f"{structLabel}_{SEASONS.fvals[structSeason]}_{TIME_OF_DAY.fvals[structTime]}_{structMonType}{structInfo}"
                            fieldStrings[fieldCounter] = f"{structLabel}_{SEASONS.fvals[structSeason]}_{TIME_OF_DAY.fvals[structTime]}_{structMonType}"
                    else:
                        structMonType = ""
                        continue
                
                    baseStructContent = []
                    for group in encounter[areaTable]:
                        if "mons" in group:
                            for mon in encounter[areaTable][group]:
                                baseStructContent.append(list(mon.values()))

                        if "encounter_rate" in group:
                            infoStructRate = encounter[areaTable][group]
                    
                    baseStructLabel = f"{baseStruct} {fieldStrings[fieldCounter]}{structArrayAssign}"
                    if printEncounterStructs:
                        print()
                        print(baseStructLabel)
                        print("{")
                        PrintStructContent(baseStructContent)
                        print("};")

                    if printEncounterStructsInfoString:
                        infoStructString = f"{baseStruct}{structInfo} {fieldInfoStrings[fieldCounter]} = {{ {infoStructRate}, {fieldStrings[fieldCounter]} }};"
                        print(infoStructString)

                fieldCounter += 1
            AssembleMonHeaderContent()
        headerIndex += 1
    PrintWildMonHeadersContent()


def PrintStructContent(contentList):
    for monList in contentList:
        print(f"{tabStr}{{ {monList[0]}, {monList[1]}, {monList[2]} }},")
    return

def GetStructLabelWithoutSeason(label):
    labelLength = len(label)
    seasonLength = 0

    if not IS_SEASONS_ENABLED:
        return label
    
    seasonCounter = 0
    while seasonCounter < SEASONS_COUNT:
        tempSeason = SEASONS.fvals[seasonCounter]
        if tempSeason in label:
            seasonLength = len(tempSeason)
            return label[:(labelLength - (seasonLength + 1))]

        seasonCounter += 1
    return label

def GetStructSeasonWithoutLabel(label):
    if not IS_SEASONS_ENABLED:
        return SEASON_DEFAULT_INDEX
    
    seasonCounter = 0
    while seasonCounter < SEASONS_COUNT:
        tempSeason = f"_{SEASONS.fvals[seasonCounter]}"
        if tempSeason in label:
            return seasonCounter

        seasonCounter += 1
    return SEASON_DEFAULT_INDEX

def GetStructLabelWithoutTime(label):
    labelLength = len(label)
    timeLength = 0

    if not IS_TIME_ENABLED:
        return label
    
    timeCounter = 0
    while timeCounter < TIMES_OF_DAY_COUNT:
        tempTime = TIME_OF_DAY.fvals[timeCounter]
        if tempTime in label:
            timeLength = len(tempTime)
            return label[:(labelLength - (timeLength + 1))]

        timeCounter += 1
    return label

def GetStructTimeWithoutLabel(label):
    if not IS_TIME_ENABLED:
        return TIME_DEFAULT_INDEX
    
    timeCounter = 0
    while timeCounter < TIMES_OF_DAY_COUNT:
        tempTime = f"_{TIME_OF_DAY.fvals[timeCounter]}"
        if tempTime in label:
            return timeCounter

        timeCounter += 1
    return TIME_DEFAULT_INDEX

def AssembleMonHeaderContent():
    SetupMonInfoVars()

    tempHeaderLabel = GetWildMonHeadersLabel()
    tempHeaderSeasonIndex = GetStructSeasonWithoutLabel(structLabel)
    tempHeaderTimeIndex = GetStructTimeWithoutLabel(structLabel)
    # structLabelNoTime = GetStructLabelWithoutTime(structLabel)
    # structLabelNoSeason = GetStructLabelWithoutSeason(structLabel)
    mapKey = structMap
    
    if tempHeaderLabel not in headerStructTable:
        headerStructTable[tempHeaderLabel] = {}
        headerStructTable[tempHeaderLabel]["groupNum"] = headerIndex

    if mapKey not in headerStructTable[tempHeaderLabel]:
        headerStructTable[tempHeaderLabel][mapKey] = {}
        headerStructTable[tempHeaderLabel][mapKey]["headerType"] = GetWildMonHeadersLabel()
        headerStructTable[tempHeaderLabel][mapKey]["mapGroup"] = structMap
        headerStructTable[tempHeaderLabel][mapKey]["mapNum"] = structMap
        headerStructTable[tempHeaderLabel][mapKey]["encounterTotalCount"] = encounterTotalCount[headerIndex]
        headerStructTable[tempHeaderLabel][mapKey]["encounter_types"] = []

        seasonCounter = 0
        while seasonCounter < SEASONS_COUNT:
            headerStructTable[tempHeaderLabel][mapKey]["encounter_types"].append([])

            timeCounter = 0
            while timeCounter < TIMES_OF_DAY_COUNT:
                headerStructTable[tempHeaderLabel][mapKey]["encounter_types"][seasonCounter].append([])
                timeCounter += 1
            seasonCounter += 1

    fieldCounter = 0
    while fieldCounter < len(fieldData):
        headerStructTable[tempHeaderLabel][mapKey]["encounter_types"][tempHeaderSeasonIndex][tempHeaderTimeIndex].append(fieldInfoStrings[fieldCounter])
        fieldCounter += 1


def SetupMonInfoVars():
    i = 0
    while i < len(fieldData):
        fieldData[i]["infoStringBase"] = "." + fieldData[i]["snakeName"] + structInfo
        if CheckEmpty(fieldInfoStrings[i]):
            fieldInfoStrings[i] = NULL
        else:
            fieldInfoStrings[i] = "&" + fieldInfoStrings[i]

        i += 1


def PrintWildMonHeadersContent():
    groupCount = 0
    for group in headerStructTable:
        labelCount = 0
        for label in headerStructTable[group]:
            if label != "groupNum":
                if labelCount == 0:
                    PrintEncounterHeaders("\n")
                    PrintEncounterHeaders(headerStructTable[group][label]["headerType"])

                PrintEncounterHeaders(tabStr + "{")

                for stat in headerStructTable[group][label]:
                    mapData = headerStructTable[group][label][stat]

                    if stat == "mapGroup":
                        PrintEncounterHeaders(f"{TabStr(2)}.mapGroup = {GetMapGroupEnum(mapData)},")
                    elif stat == "mapNum":
                        PrintEncounterHeaders(f"{TabStr(2)}.mapNum = {GetMapGroupEnum(mapData, labelCount + 1)},")

                    if type(headerStructTable[group][label][stat]) == list:
                        PrintEncounterHeaders(f"{TabStr(2)}.encounterTypes =")
                        PrintEncounterHeaders(TabStr(2) + "{")

                        seasonCounter = 0

                        while seasonCounter < SEASONS_COUNT:

                            timeCounter = 0
                            
                            while timeCounter < TIMES_OF_DAY_COUNT:
                            
                                monInfo = headerStructTable[group][label][stat][seasonCounter][timeCounter]
                                PrintEncounterHeaders(f"{TabStr(3)}[{SEASONS.vals[seasonCounter]}][{TIME_OF_DAY.vals[timeCounter]}] = ")

                                infoIndex = 0
                                while infoIndex < len(fieldData):
                                    if infoIndex == 0:
                                        PrintEncounterHeaders(TabStr(3) + "{")

                                    if len(monInfo) == 0:
                                        PrintEncounterHeaders(f"{TabStr(4)}{GetIMonInfoStringFromIndex(infoIndex)} = NULL,")
                                    else:
                                        PrintEncounterHeaders(f"{TabStr(4)}{GetIMonInfoStringFromIndex(infoIndex)} = {monInfo[infoIndex]},")

                                    if infoIndex == len(fieldData) - 1:
                                        PrintEncounterHeaders(TabStr(3) + "},")

                                    infoIndex += 1
                                timeCounter += 1
                            seasonCounter += 1
                        
                        PrintEncounterHeaders(TabStr(2) + "},")
                PrintEncounterHeaders(tabStr + "},")

                if labelCount + 1 == headerStructTable[group][label]["encounterTotalCount"]:
                    PrintEncounterHeaders(tabStr + "{")
                    PrintEncounterHeaders(f"{TabStr(2)}.mapGroup = {GetMapGroupEnum(MAP_UNDEFINED)},")
                    PrintEncounterHeaders(f"{TabStr(2)}.mapNum = {GetMapGroupEnum(MAP_UNDEFINED, labelCount + 1)},")

                    nullCountSeason = 0
                    while nullCountSeason < SEASONS_COUNT:

                        nullCountTime   = 0
                        while nullCountTime < TIMES_OF_DAY_COUNT:
                            if nullCountSeason == 0 and nullCountTime == 0:
                                PrintEncounterHeaders(f"{TabStr(2)}.encounterTypes =")
                                PrintEncounterHeaders(TabStr(2)+ "{")

                            PrintEncounterHeaders(f"{TabStr(3)}[{SEASONS.vals[nullCountSeason]}][{TIME_OF_DAY.vals[nullCountTime]}] = ")

                            nullIndex = 0
                            while nullIndex <= len(fieldData) - 1:
                                if nullIndex == 0:
                                    PrintEncounterHeaders(TabStr(3) + "{")

                                PrintEncounterHeaders(f"{TabStr(4)}{GetIMonInfoStringFromIndex(nullIndex)} = NULL,")

                                if nullIndex == len(fieldData) - 1:
                                    PrintEncounterHeaders(TabStr(3) + "},")

                                nullIndex += 1
                            nullCountTime += 1
                        nullCountSeason += 1

                    PrintEncounterHeaders(TabStr(2) + "},")
                    PrintEncounterHeaders(tabStr + "},")
                labelCount += 1
        groupCount += 1
        PrintEncounterHeaders("};")


def GetWildMonHeadersLabel():
        return f"{baseStruct}{structHeader} {MON_HEADERS[headerIndex]}{structHeader}s{structArrayAssign}" + "\n{"


def PrintEncounterHeaders(content):
    if printEncounterHeaders:
        print(content)


def PrintEncounterRateMacros():
    if not printEncounterRateMacros:
        return

    fieldCounter = 0
    while fieldCounter < len(fieldData): 
        tempName = fieldData[fieldCounter]["name"].upper()
        if "groups" not in fieldData[fieldCounter]:
            rateCount = 0
            if fieldData[fieldCounter]["encounter_rates"]:
                for percent in fieldData[fieldCounter]["encounter_rates"]:
                    if not DEXNAV_ENABLED and tempName == "HIDDEN_MONS":
                        break

                    if rateCount == 0:
                        print(f"{define} {ENCOUNTER_CHANCE}_{tempName}_{SLOT}_{rateCount} {percent}")
                    else:
                        print(
                            f"{define} {ENCOUNTER_CHANCE}_{tempName}_{SLOT}_{rateCount} {ENCOUNTER_CHANCE}_{tempName}_{SLOT}_{rateCount - 1} + {percent}"
                        )

                    if rateCount + 1 == len(fieldData[fieldCounter]["encounter_rates"]):
                        print(
                            f"{define} {ENCOUNTER_CHANCE}_{tempName}_{TOTAL} ({ENCOUNTER_CHANCE}_{tempName}_{SLOT}_{rateCount})"
                        )

                    rateCount += 1
        else:
            rates = fieldData[fieldCounter]["encounter_rates"]
            groups = fieldData[fieldCounter]["groups"]

            for method in groups:
                method_indices = groups[method]
                if not method_indices:
                    continue
                self.WriteLine(f"[{time}] =", 3)
                self.WriteLine("{", 3)
                for mon_type in self.config.mon_types:
                    member_name = mon_type.title().replace("_", "")
                    member_name = member_name[0].lower() + member_name[1:] + "Info"
                    value = "NULL"
                    if time in encounter_data and mon_type in encounter_data[time]:
                        value = encounter_data[time][mon_type]
                    if value != "NULL":
                        value = "&" + value
                    self.WriteLine(f".{member_name} = {value},", 4)

                self.WriteLine("},", 3)

            self.WriteLine("},", 2)
            self.WriteLine("},", 1)
            self.WriteLine(f"#endif")
        self.WriteTerminator()
        self.WriteLine("};")


    def WriteEncounters(self):
        wild_encounter_groups = self.json_data["wild_encounter_groups"]
        for wild_encounter_group in wild_encounter_groups:
            headers = {}
            headers["label"] = wild_encounter_group["label"]
            headers["data"] = {}
            for_maps = False
            map_num_counter = 1
            if "for_maps" in wild_encounter_group:
                for_maps = wild_encounter_group["for_maps"]
            encounters = wild_encounter_group["encounters"]

            for map_encounters in encounters:
                map_group = "0"
                map_num = str(map_num_counter)
                if for_maps:
                    map_name = map_encounters["map"]
                    map_group = f"MAP_GROUP({map_name})"
                    map_num = f"MAP_NUM({map_name})"
                map_num_counter += 1
                base_label = map_encounters["base_label"]
                shared_label = base_label
                time = self.config.time_fallback

                for time_ident in self.config.times_of_day:
                    if self.config.times_of_day[time_ident] in base_label:
                        time = time_ident
                        shared_label = shared_label.replace('_' + self.config.times_of_day[time_ident], '')

                if shared_label not in headers["data"]:
                    headers["data"][shared_label] = {}
                if time not in headers["data"][shared_label]:
                    headers["data"][shared_label][time] = {}
                headers["data"][shared_label]["mapGroup"] = map_group
                headers["data"][shared_label]["mapNum"] = map_num

                version = "EMERALD"
                if "FireRed" in shared_label:
                    version = "FIRERED"
                elif "LeafGreen" in shared_label:
                    version = "LEAFGREEN"
                self.WriteLine(f"#ifdef {version}")
                for mon_type in self.config.mon_types:
                    if mon_type not in map_encounters:
                        headers["data"][shared_label][mon_type] = "NULL"
                        continue

                    mons_entry = map_encounters[mon_type]
                    encounter_rate = mons_entry["encounter_rate"]
                    mons = mons_entry["mons"]

                    mon_array_name = base_label + "_" + mon_type.title().replace("_", "")
                    self.WriteMonInfos(mon_array_name, mons, encounter_rate)
                    headers["data"][shared_label][time][mon_type] = mon_array_name + "Info"
                self.WriteLine(f"#endif")

            self.WritePokemonHeaders(headers)

def GetSeasonLabelFromString(string):
    season = "SEASON"
    season_ = "SEASON_"

    if string == "SEASONS_COUNT":
        return string
    
    if season_ in string.upper():
        return string[len(season_):len(string)]
    elif season in string.upper():
        return string[len(season):len(string)]
    return string


def GetTimeLabelFromString(string):
    time = "TIME"
    time_ = "TIME_"

    if string == "TIMES_OF_DAY_COUNT":
        return string

    if time_ in string.upper():
        return string[len(time_):len(string)]
    elif time in string.upper():
        return string[len(time):len(string)]
    return string


def GetIMonInfoStringFromIndex(index):
    return fieldData[index]["infoStringBase"]


def GetMapGroupEnum(string, index = 0):
    if "MAP_" in string and index == 0:
        return "MAP_GROUP(" + string + ")"
    elif "MAP_" in string and index != 0:
        return "MAP_NUM(" + string + ")"
    return index


"""
get copied lhea :^ ) 
- next four functions copied almost verbatim from @lhearachel's python scripts in tools/learnset_helpers
"""
def PrintGeneratedWarningText():
    print("//")
    print("// DO NOT MODIFY THIS FILE! It is auto-generated by tools/wild_encounters/wild_encounters_to_header.py")
    print("//")
    print("\n")

def IsTimeEnabled():
    TIME_ENABLED_PAT = re.compile(r"#define OW_TIME_OF_DAY_ENCOUNTERS\s+(?P<cfg_val>[^ ]*)")

    with open("./include/config/overworld.h", "r") as overworld_config_file:
        config_overworld = overworld_config_file.read()
        config_setting = TIME_ENABLED_PAT.search(config_overworld)
        return config_setting is not None and config_setting.group("cfg_val") in ("TRUE", "1")
    
def IsSeasonsEnabled():
    SEASONS_ENABLED_PAT = re.compile(r"#define OW_SEASONAL_ENCOUNTERS\s+(?P<cfg_val>[^ ]*)")

    with open("./include/config/overworld.h", "r") as overworld_config_file:
        config_overworld = overworld_config_file.read()
        config_setting = SEASONS_ENABLED_PAT.search(config_overworld)
        return config_setting is not None and config_setting.group("cfg_val") in ("TRUE", "1")

def IsDexnavEnabled():
    CONFIG_ENABLED_PAT = re.compile(r"#define DEXNAV_ENABLED\s+(?P<cfg_val>[^ ]*)")

    with open("./include/config/dexnav.h", "r") as overworld_config_file:
        config_overworld = overworld_config_file.read()
        config_setting = CONFIG_ENABLED_PAT.search(config_overworld)
        return config_setting is not None and config_setting.group("cfg_val") in ("TRUE", "1")
    
def GetSeasonsEnum():
    DEFAULT_SEASON_PAT = re.compile(r"enum\s+Seasons\s*\{(?P<seasons_val>[\s*\w+,\=\d*]+)\s*\}\s*\;")

    with open("./include/seasons.h", "r") as seasons_include_file:
        include_seasons = seasons_include_file.read()
        include_enum = DEFAULT_SEASON_PAT.search(include_seasons)
        return include_enum.group("seasons_val")

def GetTimeEnum():
    DEFAULT_TIME_PAT = re.compile(r"enum\s+TimeOfDay\s*\{(?P<rtc_val>[\s*\w+,\=\d*]+)\s*\}\s*\;")

    with open("./include/constants/rtc.h", "r") as rtc_include_file:
        include_rtc = rtc_include_file.read()
        include_enum = DEFAULT_TIME_PAT.search(include_rtc)
        return include_enum.group("rtc_val")

def CheckEmpty(string):
    return string == "" or string.isspace() or string == "\n"

def SetupUserSeasonsEnum(season):
    enum_string = GetSeasonsEnum()
    enum_string = enum_string.split(",")

    # check for extra element from trailing comma
    if CheckEmpty(enum_string[-1]):
        enum_string.pop(-1)

    # we don't need the `TIMES_OF_DAY_COUNT` value, so - 1 from the value of len(enum_string)
    strCount = 0
    while strCount < len(enum_string) - 1:
        tempStr = enum_string[strCount].strip("\n ")

        """
        we need to ignore any value assignments, as the times will need to correspond
        with the elements in the array.
        """
        if "=" in tempStr:
            tempStr = tempStr[0:tempStr.index("=")]
            tempStr = tempStr.strip(" ")

        #double check we didn't catch any empty values
        if not CheckEmpty(enum_string[strCount]):
            season.add(tempStr)

        strCount += 1
    return season

def SetupUserTimeEnum(timeOfDay):
    enum_string = GetTimeEnum()
    enum_string = enum_string.split(",")

    # check for extra element from trailing comma
    if CheckEmpty(enum_string[-1]):
        enum_string.pop(-1)

    # we don't need the `TIMES_OF_DAY_COUNT` value, so - 1 from the value of len(enum_string)
    strCount = 0
    while strCount < len(enum_string) - 1:
        tempStr = enum_string[strCount].strip("\n ")

        """
        we need to ignore any value assignments, as the times will need to correspond
        with the elements in the array.
        """
        if "=" in tempStr:
            tempStr = tempStr[0:tempStr.index("=")]
            tempStr = tempStr.strip(" ")

        #double check we didn't catch any empty values
        if not CheckEmpty(enum_string[strCount]):
            timeOfDay.add(tempStr)

        strCount += 1
    return timeOfDay


def TabStr(amount):
    return tabStr * amount


def GetPascalCase(string):
    stringArray = string.split("_")
    pascalString = ""

    for string in stringArray:
        pascalString += string.capitalize()
    return pascalString


def GetSnakeCase(string):
    stringArray = string.split("_")
    snakeString = ""

    i = 0
    for string in stringArray:
        if i == 0:
            snakeString += string
        else:
            snakeString += string.capitalize()

        i += 1
    return snakeString


def CheckFieldDataDupes(name):
    for field in fieldData:
        if field["name"] == name:
            return True
    return False


def AddFieldData(index, fieldType, fieldRates):
    fieldData.append({})
    fieldData[index]["name"] = fieldType
    fieldData[index]["pascalName"] = GetPascalCase(fieldType)
    fieldData[index]["snakeName"] = GetSnakeCase(fieldType)
    fieldData[index]["encounter_rates"] = fieldRates


def main():
    with open('src/data/wild_encounters.json', 'r') as json_file:
        json_data = json.load(json_file)
        ConvertToHeaderFile(json_data)


if __name__ == '__main__':
    main()
