KingsisleInstituteMainCampus_MapScripts::
# 2 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, KingsisleInstituteMainCampus_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

KingsisleInstituteMainCampus_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
# 3 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	map_script_2 VAR_KINGSISLE_INTRO_STATE, 1, KingsisleInstitute_EventScript_StepOffTruck
	.2byte 0


KingsisleInstitute_EventScript_StepOffTruck::
# 8 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	lockall
# 9 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	call KingsisleInstitute_EventScript_GoInsideWithMercury
# 10 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	setflag FLAG_HIDE_KINGSISLE_TRUCK
# 11 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	warpsilent MAP_KINGSISLE_DORM_1F, 9, 9
# 12 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	waitstate
# 13 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	releaseall
	end


KingsisleInstitute_EventScript_GoInsideWithMercury::
# 18 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay 15
# 19 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	playse SE_LEDGE
# 20 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleInstitute_Movement_PlayerStepOffTruck
# 21 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	waitmovement 0
# 22 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY, KingsisleInstitute_Movement_MercuryWalkToPlayer
# 23 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	waitmovement 0
# 24 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	setspeaker SP_NAME_MERCURY
# 25 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	msgbox KingsisleInstitute_Text_YourNewHome, MSGBOX_DEFAULT
# 26 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	closemessage
# 27 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY, KingsisleInstitute_Movement_MercuryWalkInside
# 28 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleInstitute_Movement_PlayerWalkInside
# 29 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	waitmovement 0
# 30 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	setflag FLAG_HIDE_MERCURY_OUTSIDE
# 31 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	setvar VAR_KINGSISLE_INTRO_STATE, 2
# 32 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return


# 36 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_Movement_PlayerStepOffTruck:
# 37 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	jump_right
# 38 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay_16
# 39 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay_16
# 40 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay_16
# 41 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	step_end

# 44 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_Movement_MercuryWalkToPlayer:
# 45 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_down
# 46 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_down
# 47 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_in_place_fast_left
# 48 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	step_end

# 55 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_Movement_MercuryWalkInside:
# 56 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 56 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 56 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 57 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 57 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 57 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 58 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 58 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 59 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	set_invisible
# 60 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	step_end

# 63 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
KingsisleInstitute_Movement_PlayerWalkInside:
# 64 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	delay_8
# 65 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 65 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 65 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 66 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 66 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 66 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 66 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_right
# 67 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 67 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	walk_up
# 68 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	step_end

KingsisleInstitute_Text_YourNewHome::
# 51 "data/maps/KingsisleInstituteMainCampus/scripts.pory"
	.string "Alright, kid, we're here.\p"
	.string "This is the first-year dorm, you'll stay\n"
	.string "here until you pick a college. Let's head\l"
	.string "inside, yeah?$"
