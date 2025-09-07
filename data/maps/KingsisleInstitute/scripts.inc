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


AcademySign::
# 28 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox AcademySign_Text_0, MSGBOX_SIGN
	return


Kingsisle_MagicGuy::
# 32 "data/maps/KingsisleInstitute/scripts.pory"
	speakername CommonName_Text_Student
# 33 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox MagicIsAmazing, MSGBOX_NPC
	return


KingsisleInstitute_EventScript_StepOffTruck::
# 41 "data/maps/KingsisleInstitute/scripts.pory"
	lockall
# 42 "data/maps/KingsisleInstitute/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleInstitute_EventScript_StepOffTruck_Movement_0
# 43 "data/maps/KingsisleInstitute/scripts.pory"
	call KingsisleInstitute_EventScript_GoInsideWithMercury
# 44 "data/maps/KingsisleInstitute/scripts.pory"
	setflag FLAG_HIDE_KINGSISLE_TRUCK
# 45 "data/maps/KingsisleInstitute/scripts.pory"
	warpsilent MAP_KINGSISLE_DORM_1F, 9, 9
# 46 "data/maps/KingsisleInstitute/scripts.pory"
	waitstate
# 47 "data/maps/KingsisleInstitute/scripts.pory"
	releaseall
	end


KingsisleInstitute_EventScript_GoInsideWithMercury::
# 52 "data/maps/KingsisleInstitute/scripts.pory"
	delay 15
# 53 "data/maps/KingsisleInstitute/scripts.pory"
	playse SE_LEDGE
# 54 "data/maps/KingsisleInstitute/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleInstitute_Movement_PlayerStepOffTruck
# 55 "data/maps/KingsisleInstitute/scripts.pory"
	waitmovement 0
# 56 "data/maps/KingsisleInstitute/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY, KingsisleInstitute_Movement_MercuryWalkToPlayer
# 57 "data/maps/KingsisleInstitute/scripts.pory"
	waitmovement 0
# 58 "data/maps/KingsisleInstitute/scripts.pory"
	speakername UniqueName_Text_Mercury
# 59 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox KingsisleInstitute_Text_YourNewHome, MSGBOX_DEFAULT
# 60 "data/maps/KingsisleInstitute/scripts.pory"
	closemessage
# 61 "data/maps/KingsisleInstitute/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY, KingsisleInstitute_Movement_MercuryWalkInside
# 62 "data/maps/KingsisleInstitute/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleInstitute_Movement_PlayerWalkInside
# 63 "data/maps/KingsisleInstitute/scripts.pory"
	waitmovement 0
# 64 "data/maps/KingsisleInstitute/scripts.pory"
	setflag FLAG_HIDE_MERCURY_OUTSIDE
# 65 "data/maps/KingsisleInstitute/scripts.pory"
	setvar VAR_KINGSISLE_INTRO_STATE, 2
# 66 "data/maps/KingsisleInstitute/scripts.pory"
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return


# 70 "data/maps/KingsisleInstitute/scripts.pory"
KingsisleInstitute_Movement_PlayerStepOffTruck:
# 71 "data/maps/KingsisleInstitute/scripts.pory"
	set_visible
# 72 "data/maps/KingsisleInstitute/scripts.pory"
	jump_right
# 73 "data/maps/KingsisleInstitute/scripts.pory"
	delay_16
# 74 "data/maps/KingsisleInstitute/scripts.pory"
	delay_16
# 75 "data/maps/KingsisleInstitute/scripts.pory"
	delay_16
# 76 "data/maps/KingsisleInstitute/scripts.pory"
	step_end

# 79 "data/maps/KingsisleInstitute/scripts.pory"
KingsisleInstitute_Movement_MercuryWalkToPlayer:
# 80 "data/maps/KingsisleInstitute/scripts.pory"
	walk_down
# 81 "data/maps/KingsisleInstitute/scripts.pory"
	walk_down
# 82 "data/maps/KingsisleInstitute/scripts.pory"
	walk_in_place_fast_left
# 83 "data/maps/KingsisleInstitute/scripts.pory"
	step_end

# 90 "data/maps/KingsisleInstitute/scripts.pory"
KingsisleInstitute_Movement_MercuryWalkInside:
# 91 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 91 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 91 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 92 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 92 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 92 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 93 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 93 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 94 "data/maps/KingsisleInstitute/scripts.pory"
	set_invisible
# 95 "data/maps/KingsisleInstitute/scripts.pory"
	step_end

# 98 "data/maps/KingsisleInstitute/scripts.pory"
KingsisleInstitute_Movement_PlayerWalkInside:
# 99 "data/maps/KingsisleInstitute/scripts.pory"
	delay_16
# 100 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 100 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 100 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 101 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 101 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 101 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 101 "data/maps/KingsisleInstitute/scripts.pory"
	walk_right
# 102 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 102 "data/maps/KingsisleInstitute/scripts.pory"
	walk_up
# 103 "data/maps/KingsisleInstitute/scripts.pory"
	step_end

# 42 "data/maps/KingsisleInstitute/scripts.pory"
KingsisleInstitute_EventScript_StepOffTruck_Movement_0:
# 42 "data/maps/KingsisleInstitute/scripts.pory"
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

AcademySign_Text_0:
# 28 "data/maps/KingsisleInstitute/scripts.pory"
	.string "ACADEMY THIS WAY$"

MagicIsAmazing::
# 36 "data/maps/KingsisleInstitute/scripts.pory"
	.string "Magic is amazing!\p"
	.string "I heard that students at the top of\n"
	.string "their class are able to travel to other\l"
	.string "Underground sectors using\l"
	.string "teleportation circles!$"

KingsisleInstitute_Text_YourNewHome::
# 86 "data/maps/KingsisleInstitute/scripts.pory"
	.string "Alright, kid, we're here.\p"
	.string "This is the first-year dorm, you'll stay\n"
	.string "here until you pick a college. Let's head\l"
	.string "inside, yeah?$"
