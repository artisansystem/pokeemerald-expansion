KingsisleDorm_1F_MapScripts::
# 2 "data/maps/KingsisleDorm_1F/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, KingsisleDorm_1F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

KingsisleDorm_1F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
# 3 "data/maps/KingsisleDorm_1F/scripts.pory"
	map_script_2 VAR_KINGSISLE_INTRO_STATE, 2, KingsisleDorm_EventScript_DormExplanation
	.2byte 0


KingsisleDorm_EventScript_DormExplanation::
# 8 "data/maps/KingsisleDorm_1F/scripts.pory"
	delay 15
# 9 "data/maps/KingsisleDorm_1F/scripts.pory"
	setvar VAR_KINGSISLE_INTRO_STATE, 3
# 10 "data/maps/KingsisleDorm_1F/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY_DORM, KingsisleDorm_EventScript_DormExplanation_Movement_0
# 11 "data/maps/KingsisleDorm_1F/scripts.pory"
	waitmovement 0
# 12 "data/maps/KingsisleDorm_1F/scripts.pory"
	lockall
# 13 "data/maps/KingsisleDorm_1F/scripts.pory"
	speakername UniqueName_Text_Mercury
# 14 "data/maps/KingsisleDorm_1F/scripts.pory"
	msgbox KingsisleDorm_Text_ThisIsIt, MSGBOX_DEFAULT
# 15 "data/maps/KingsisleDorm_1F/scripts.pory"
	dynmultichoice 0, 0, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, KingsisleDorm_EventScript_DormExplanation_Text_0, KingsisleDorm_EventScript_DormExplanation_Text_1, KingsisleDorm_EventScript_DormExplanation_Text_2
# 17 "data/maps/KingsisleDorm_1F/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq KingsisleDorm_EventScript_DormExplanation_2
# 24 "data/maps/KingsisleDorm_1F/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq KingsisleDorm_EventScript_DormExplanation_3
# 32 "data/maps/KingsisleDorm_1F/scripts.pory"
	speakername UniqueName_Text_Mercury
# 33 "data/maps/KingsisleDorm_1F/scripts.pory"
	msgbox KingsisleDorm_Text_Reminder, MSGBOX_DEFAULT
# 34 "data/maps/KingsisleDorm_1F/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY_DORM, KingsisleDorm_EventScript_DormExplanation_Movement_1
# 35 "data/maps/KingsisleDorm_1F/scripts.pory"
	waitmovement 0
# 36 "data/maps/KingsisleDorm_1F/scripts.pory"
	setflag FLAG_HIDE_MERCURY_INSIDE
# 37 "data/maps/KingsisleDorm_1F/scripts.pory"
	releaseall
	end

KingsisleDorm_EventScript_DormExplanation_1:
# 41 "data/maps/KingsisleDorm_1F/scripts.pory"
FinalReminder:
# 42 "data/maps/KingsisleDorm_1F/scripts.pory"
	msgbox KingsisleDorm_Text_Reminder_Alt, MSGBOX_DEFAULT
# 43 "data/maps/KingsisleDorm_1F/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY_DORM, KingsisleDorm_EventScript_DormExplanation_Movement_1
# 44 "data/maps/KingsisleDorm_1F/scripts.pory"
	waitmovement 0
# 45 "data/maps/KingsisleDorm_1F/scripts.pory"
	setflag FLAG_HIDE_MERCURY_INSIDE
# 46 "data/maps/KingsisleDorm_1F/scripts.pory"
	releaseall
	end

KingsisleDorm_EventScript_DormExplanation_2:
# 19 "data/maps/KingsisleDorm_1F/scripts.pory"
	speakername UniqueName_Text_Mercury
# 20 "data/maps/KingsisleDorm_1F/scripts.pory"
	msgbox KingsisleDorm_Text_VeryFunny, MSGBOX_DEFAULT
# 21 "data/maps/KingsisleDorm_1F/scripts.pory"
	goto FinalReminder
	goto KingsisleDorm_EventScript_DormExplanation_1

KingsisleDorm_EventScript_DormExplanation_3:
# 26 "data/maps/KingsisleDorm_1F/scripts.pory"
	speakername UniqueName_Text_Mercury
# 27 "data/maps/KingsisleDorm_1F/scripts.pory"
	msgbox KingsisleDorm_Text_ClassesStart, MSGBOX_DEFAULT
# 28 "data/maps/KingsisleDorm_1F/scripts.pory"
	goto FinalReminder
	goto KingsisleDorm_EventScript_DormExplanation_1


# 10 "data/maps/KingsisleDorm_1F/scripts.pory"
KingsisleDorm_EventScript_DormExplanation_Movement_0:
# 10 "data/maps/KingsisleDorm_1F/scripts.pory"
	walk_up
# 10 "data/maps/KingsisleDorm_1F/scripts.pory"
	walk_up
# 10 "data/maps/KingsisleDorm_1F/scripts.pory"
	face_down
	step_end

# 34 "data/maps/KingsisleDorm_1F/scripts.pory"
KingsisleDorm_EventScript_DormExplanation_Movement_1:
# 34 "data/maps/KingsisleDorm_1F/scripts.pory"
	walk_down
# 34 "data/maps/KingsisleDorm_1F/scripts.pory"
	walk_down
# 34 "data/maps/KingsisleDorm_1F/scripts.pory"
	set_invisible
	step_end

KingsisleDorm_EventScript_DormExplanation_Text_0:
# 15 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "Are you also a student?$"

KingsisleDorm_EventScript_DormExplanation_Text_1:
# 15 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "When do classes start?$"

KingsisleDorm_EventScript_DormExplanation_Text_2:
# 15 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "I'm good.$"

KingsisleDorm_Text_ThisIsIt::
# 50 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "Huh, not bad. They must've renovated\n"
	.string "recently.\p"
	.string "Well, this is it. Your home away from\n"
	.string "home for the next year or two. Your\l"
	.string "room's on the second floor, last door on\l"
	.string "the right. So, any questions for me\l"
	.string "before I send you on your merry way?$"

KingsisleDorm_Text_VeryFunny::
# 54 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "Ha. If I had a nickel for every time\n"
	.string "someone asked me that question, I\l"
	.string "could afford to quit this job.\p"
	.string "No, I'm the Dawnsinger family's head of\n"
	.string "security. Feel free to stop by my\l"
	.string "office, if you ever need anything.$"

KingsisleDorm_Text_ClassesStart::
# 58 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "Should be about a week or so of\n"
	.string "orientation-related activities until\l"
	.string "classes are fully underway.$"

KingsisleDorm_Text_Reminder::
# 62 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "Alright. In that case, I'll head out and\n"
	.string "let you get settled. I bought you a\l"
	.string "clock, should be up in your room. Don't\l"
	.string "forget to set it. And remember to go see\l"
	.string "Headmaster Dawnsinger at some point.\l"
	.string "Special request from the man himself.$"

KingsisleDorm_Text_Reminder_Alt::
# 66 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "Alright, well, I'll head out and let you\n"
	.string "get settled. I bought you a clock,\l"
	.string "should be up in your room. Don't forget\l"
	.string "to set it. And remember to go see\l"
	.string "Headmaster Dawnsinger at some point.\l"
	.string "Special request from the man himself.$"
