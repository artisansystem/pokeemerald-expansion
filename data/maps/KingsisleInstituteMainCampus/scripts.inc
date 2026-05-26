KingsisleInstituteMainCampus_MapScripts::
# 2 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, KingsisleInstituteMainCampus_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

KingsisleInstituteMainCampus_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
# 3 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	map_script_2 VAR_KINGSISLE_INTRO_STATE, 1, KingsisleInstitute_EventScript_StepOffTruck
	.2byte 0


# 7 "data/maps/KingsisleInstituteMainCampus/scripts.pory"

# 8 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
CommonName_Text_Student:
# 9 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
    .string "Student$"
# 10 "data/maps/KingsisleInstituteMainCampus/scripts.pory"

# 11 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
UniqueName_Text_Mercury:
# 12 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
    .string "Mercury$"

KingsisleInstitute_EventScript_StepOffTruck::
# 16 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	lockall
# 17 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	call KingsisleInstitute_EventScript_GoInsideWithMercury
# 18 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	setflag FLAG_HIDE_KINGSISLE_TRUCK
# 19 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	warpsilent MAP_KINGSISLE_DORM_1F, 9, 9
# 20 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	waitstate
# 21 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	releaseall
	end


KingsisleInstitute_EventScript_GoInsideWithMercury::
# 26 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay 15
# 27 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	playse SE_LEDGE
# 28 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleInstitute_Movement_PlayerStepOffTruck
# 29 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	waitmovement 0
# 30 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY, KingsisleInstitute_Movement_MercuryWalkToPlayer
# 31 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	waitmovement 0
# 32 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	speakername UniqueName_Text_Mercury
# 33 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	msgbox KingsisleInstitute_Text_YourNewHome, MSGBOX_DEFAULT
# 34 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	closemessage
# 35 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY, KingsisleInstitute_Movement_MercuryWalkInside
# 36 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleInstitute_Movement_PlayerWalkInside
# 37 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	waitmovement 0
# 38 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	setflag FLAG_HIDE_MERCURY_OUTSIDE
# 39 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	setvar VAR_KINGSISLE_INTRO_STATE, 2
# 40 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return


# 44 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_Movement_PlayerStepOffTruck:
# 45 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	jump_right
# 46 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay_16
# 47 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay_16
# 48 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay_16
# 49 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	step_end

# 52 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_Movement_MercuryWalkToPlayer:
# 53 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_down
# 54 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_down
# 55 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_in_place_fast_left
# 56 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	step_end

# 63 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_Movement_MercuryWalkInside:
# 64 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 64 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 64 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 65 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 65 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 65 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 66 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 66 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 67 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	set_invisible
# 68 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	step_end

# 71 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_Movement_PlayerWalkInside:
# 72 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay_8
# 73 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 73 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 73 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 74 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 74 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 74 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 74 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 75 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 75 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 76 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	step_end

KingsisleInstitute_Text_YourNewHome::
# 59 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	.string "Alright, kid, we're here.\p"
	.string "This is the first-year dorm, you'll stay\n"
	.string "here until you pick a college. Let's head\l"
	.string "inside, yeah?$"
