KingsisleInstitute_MapScripts::
# 2 "data/maps/KingsisleInstitute/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, KingsisleInstitute_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

KingsisleInstitute_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
# 3 "data/maps/KingsisleInstitute/scripts.pory"
	map_script_2 VAR_KINGSISLE_INTRO_STATE, 1, KingsisleInstitute_EventScript_StepOffTruck
	.2byte 0


# 7 "data/maps/KingsisleInstitute/scripts.pory"

# 8 "data/maps/KingsisleInstitute/scripts.pory"
CommonName_Text_Student:
# 9 "data/maps/KingsisleInstitute/scripts.pory"
    .string "Student$"
# 10 "data/maps/KingsisleInstitute/scripts.pory"

# 11 "data/maps/KingsisleInstitute/scripts.pory"
UniqueName_Text_Mercury:
# 12 "data/maps/KingsisleInstitute/scripts.pory"
    .string "Mercury$"

DormSign::
# 16 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox DormSign_Text_0, MSGBOX_SIGN
	return


NadiaLab::
# 20 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox NadiaLab_Text_0, MSGBOX_SIGN
	return


SecurityOffice::
# 24 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox SecurityOffice_Text_0, MSGBOX_SIGN
	return


Kingsisle_MagicGuy::
# 28 "data/maps/KingsisleInstitute/scripts.pory"
	speakername CommonName_Text_Student
# 29 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox MagicIsAmazing, MSGBOX_NPC
	return


KingsisleInstitute_EventScript_StepOffTruck::
# 37 "data/maps/KingsisleInstitute/scripts.pory"
	lockall
# 38 "data/maps/KingsisleInstitute/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleInstitute_EventScript_StepOffTruck_Movement_0
# 39 "data/maps/KingsisleInstitute/scripts.pory"
	call KingsisleInstitute_EventScript_GoInsideWithMercury
# 40 "data/maps/KingsisleInstitute/scripts.pory"
	setflag FLAG_HIDE_KINGSISLE_TRUCK
# 41 "data/maps/KingsisleInstitute/scripts.pory"
	warpsilent MAP_KINGSISLE_DORM_1F, 9, 9
# 42 "data/maps/KingsisleInstitute/scripts.pory"
	waitstate
# 43 "data/maps/KingsisleInstitute/scripts.pory"
	releaseall
	end


KingsisleInstitute_EventScript_GoInsideWithMercury::
# 48 "data/maps/KingsisleInstitute/scripts.pory"
	delay 15
# 49 "data/maps/KingsisleInstitute/scripts.pory"
	playse SE_LEDGE
# 50 "data/maps/KingsisleInstitute/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleInstitute_Movement_PlayerStepOffTruck
# 51 "data/maps/KingsisleInstitute/scripts.pory"
	waitmovement 0
# 52 "data/maps/KingsisleInstitute/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY, KingsisleInstitute_Movement_MercuryWalkToPlayer
# 53 "data/maps/KingsisleInstitute/scripts.pory"
	waitmovement 0
# 54 "data/maps/KingsisleInstitute/scripts.pory"
	speakername UniqueName_Text_Mercury
# 55 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox KingsisleInstitute_Text_YourNewHome, MSGBOX_DEFAULT
# 56 "data/maps/KingsisleInstitute/scripts.pory"
	closemessage
# 57 "data/maps/KingsisleInstitute/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY, KingsisleInstitute_Movement_MercuryWalkInside
# 58 "data/maps/KingsisleInstitute/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleInstitute_Movement_PlayerWalkInside
# 59 "data/maps/KingsisleInstitute/scripts.pory"
	waitmovement 0
# 60 "data/maps/KingsisleInstitute/scripts.pory"
	setflag FLAG_HIDE_MERCURY_OUTSIDE
# 61 "data/maps/KingsisleInstitute/scripts.pory"
	setvar VAR_KINGSISLE_INTRO_STATE, 2
# 62 "data/maps/KingsisleInstitute/scripts.pory"
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return


# 66 "data/maps/KingsisleInstitute/scripts.pory"
KingsisleInstitute_Movement_PlayerStepOffTruck:
# 67 "data/maps/KingsisleInstitute/scripts.pory"
	set_visible
# 68 "data/maps/KingsisleInstitute/scripts.pory"
	jump_right
# 69 "data/maps/KingsisleInstitute/scripts.pory"
	delay_16
# 70 "data/maps/KingsisleInstitute/scripts.pory"
	delay_16
# 71 "data/maps/KingsisleInstitute/scripts.pory"
	delay_16
# 72 "data/maps/KingsisleInstitute/scripts.pory"
	step_end

# 75 "data/maps/KingsisleInstitute/scripts.pory"
KingsisleInstitute_Movement_MercuryWalkToPlayer:
# 76 "data/maps/KingsisleInstitute/scripts.pory"
	walk_down
# 77 "data/maps/KingsisleInstitute/scripts.pory"
	walk_down
# 78 "data/maps/KingsisleInstitute/scripts.pory"
	walk_in_place_fast_left
# 79 "data/maps/KingsisleInstitute/scripts.pory"
	step_end

# 86 "data/maps/KingsisleInstitute/scripts.pory"
KingsisleInstitute_Movement_MercuryWalkInside:
# 87 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 87 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 87 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 88 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 88 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 88 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 89 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 89 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 90 "data/maps/KingsisleInstitute/scripts.pory"
	set_invisible
# 91 "data/maps/KingsisleInstitute/scripts.pory"
	step_end

# 94 "data/maps/KingsisleInstitute/scripts.pory"
KingsisleInstitute_Movement_PlayerWalkInside:
# 95 "data/maps/KingsisleInstitute/scripts.pory"
	delay_16
# 96 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 96 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 96 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 97 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 97 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 97 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 97 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 98 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 98 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 99 "data/maps/KingsisleInstitute/scripts.pory"
	step_end

# 38 "data/maps/KingsisleInstitute/scripts.pory"
KingsisleInstitute_EventScript_StepOffTruck_Movement_0:
# 38 "data/maps/KingsisleInstitute/scripts.pory"
	set_invisible
	step_end

DormSign_Text_0:
# 16 "data/maps/KingsisleInstitute/scripts.pory"
	.string "SOLGALEO HALL$"

NadiaLab_Text_0:
# 20 "data/maps/KingsisleInstitute/scripts.pory"
	.string "PROFESSOR NADIA'S LAB$"

SecurityOffice_Text_0:
# 24 "data/maps/KingsisleInstitute/scripts.pory"
	.string "KINGSISLE SECURITY OFFICE$"

MagicIsAmazing::
# 32 "data/maps/KingsisleInstitute/scripts.pory"
	.string "Magic is amazing!\p"
	.string "I heard that students at the top of\n"
	.string "their class are able to travel to other\l"
	.string "Underground sectors using\l"
	.string "teleportation circles!$"

KingsisleInstitute_Text_YourNewHome::
# 82 "data/maps/KingsisleInstitute/scripts.pory"
	.string "Alright, kid, we're here.\p"
	.string "This is the first-year dorm, you'll stay\n"
	.string "here until you pick a college. Let's head\l"
	.string "inside, yeah?$"
