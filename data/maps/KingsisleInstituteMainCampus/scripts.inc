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
	applymovement LOCALID_PLAYER, KingsisleInstitute_EventScript_StepOffTruck_Movement_0
# 18 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	call KingsisleInstitute_EventScript_GoInsideWithMercury
# 19 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	setflag FLAG_HIDE_KINGSISLE_TRUCK
# 20 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	warpsilent MAP_KINGSISLE_DORM_1F, 9, 9
# 21 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	waitstate
# 22 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	releaseall
	end


KingsisleInstitute_EventScript_GoInsideWithMercury::
# 27 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay 15
# 28 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	playse SE_LEDGE
# 29 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleInstitute_Movement_PlayerStepOffTruck
# 30 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	waitmovement 0
# 31 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY, KingsisleInstitute_Movement_MercuryWalkToPlayer
# 32 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	waitmovement 0
# 33 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	speakername UniqueName_Text_Mercury
# 34 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	msgbox KingsisleInstitute_Text_YourNewHome, MSGBOX_DEFAULT
# 35 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	closemessage
# 36 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY, KingsisleInstitute_Movement_MercuryWalkInside
# 37 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleInstitute_Movement_PlayerWalkInside
# 38 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	waitmovement 0
# 39 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	setflag FLAG_HIDE_MERCURY_OUTSIDE
# 40 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	setvar VAR_KINGSISLE_INTRO_STATE, 2
# 41 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return


# 45 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_Movement_PlayerStepOffTruck:
# 46 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	set_visible
# 47 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	jump_right
# 48 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay_16
# 49 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay_16
# 50 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay_16
# 51 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	step_end

# 54 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_Movement_MercuryWalkToPlayer:
# 55 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_down
# 56 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_down
# 57 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_in_place_fast_left
# 58 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	step_end

# 65 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_Movement_MercuryWalkInside:
# 66 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 66 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 66 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 67 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 67 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 67 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 68 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 68 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 69 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	set_invisible
# 70 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	step_end

# 73 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_Movement_PlayerWalkInside:
# 74 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay_8
# 75 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 75 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 75 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 76 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 76 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 76 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 76 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 77 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 77 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 78 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	step_end

# 17 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_EventScript_StepOffTruck_Movement_0:
# 17 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	set_invisible
	step_end

KingsisleInstitute_Text_YourNewHome::
# 61 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	.string "Alright, kid, we're here.\p"
	.string "This is the first-year dorm, you'll stay\n"
	.string "here until you pick a college. Let's head\l"
	.string "inside, yeah?$"
