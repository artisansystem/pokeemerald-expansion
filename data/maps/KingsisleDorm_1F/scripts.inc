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
	goto KingsisleDorm_EventScript_AnyQuestions
	return


KingsisleDorm_EventScript_AnyQuestions::
# 21 "data/maps/KingsisleDorm_1F/scripts.pory"
	compare VAR_TEMP_1, 0
	goto_if_eq KingsisleDorm_EventScript_AnyQuestions_2
KingsisleDorm_EventScript_AnyQuestions_1:
# 24 "data/maps/KingsisleDorm_1F/scripts.pory"
	compare VAR_TEMP_0, 0
	goto_if_eq KingsisleDorm_EventScript_AnyQuestions_5
KingsisleDorm_EventScript_AnyQuestions_4:
# 27 "data/maps/KingsisleDorm_1F/scripts.pory"
	dynmultipush KingsisleDorm_EventScript_AnyQuestions_Text_2, 2
# 28 "data/maps/KingsisleDorm_1F/scripts.pory"
	dynmultistack 0, 0, TRUE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 30 "data/maps/KingsisleDorm_1F/scripts.pory"
	switch VAR_RESULT
# 31 "data/maps/KingsisleDorm_1F/scripts.pory"
	case 0, KingsisleDorm_EventScript_AnyQuestions_8
# 32 "data/maps/KingsisleDorm_1F/scripts.pory"
	case 1, KingsisleDorm_EventScript_AnyQuestions_9
# 33 "data/maps/KingsisleDorm_1F/scripts.pory"
	case 2, KingsisleDorm_EventScript_AnyQuestions_10
	return

KingsisleDorm_EventScript_AnyQuestions_2:
# 22 "data/maps/KingsisleDorm_1F/scripts.pory"
	dynmultipush KingsisleDorm_EventScript_AnyQuestions_Text_0, 0
	goto KingsisleDorm_EventScript_AnyQuestions_1

KingsisleDorm_EventScript_AnyQuestions_5:
# 25 "data/maps/KingsisleDorm_1F/scripts.pory"
	dynmultipush KingsisleDorm_EventScript_AnyQuestions_Text_1, 1
	goto KingsisleDorm_EventScript_AnyQuestions_4

KingsisleDorm_EventScript_AnyQuestions_8:
# 31 "data/maps/KingsisleDorm_1F/scripts.pory"
	goto KingsisleDorm_EventScript_VeryFunny
	return

KingsisleDorm_EventScript_AnyQuestions_9:
# 32 "data/maps/KingsisleDorm_1F/scripts.pory"
	goto KingsisleDorm_EventScript_ClassesStart
	return

KingsisleDorm_EventScript_AnyQuestions_10:
# 33 "data/maps/KingsisleDorm_1F/scripts.pory"
	goto KingsisleDorm_EventScript_Reminder
	return


KingsisleDorm_EventScript_VeryFunny::
# 38 "data/maps/KingsisleDorm_1F/scripts.pory"
	speakername UniqueName_Text_Mercury
# 39 "data/maps/KingsisleDorm_1F/scripts.pory"
	msgbox KingsisleDorm_Text_VeryFunny, MSGBOX_DEFAULT
# 40 "data/maps/KingsisleDorm_1F/scripts.pory"
	setvar VAR_TEMP_1, 1
# 41 "data/maps/KingsisleDorm_1F/scripts.pory"
	goto KingsisleDorm_EventScript_AnyQuestions
	return


KingsisleDorm_EventScript_ClassesStart::
# 45 "data/maps/KingsisleDorm_1F/scripts.pory"
	speakername UniqueName_Text_Mercury
# 46 "data/maps/KingsisleDorm_1F/scripts.pory"
	msgbox KingsisleDorm_Text_ClassesStart, MSGBOX_DEFAULT
# 47 "data/maps/KingsisleDorm_1F/scripts.pory"
	setvar VAR_TEMP_0, 1
# 48 "data/maps/KingsisleDorm_1F/scripts.pory"
	goto KingsisleDorm_EventScript_AnyQuestions
	return


KingsisleDorm_EventScript_Reminder::
# 53 "data/maps/KingsisleDorm_1F/scripts.pory"
	speakername UniqueName_Text_Mercury
# 54 "data/maps/KingsisleDorm_1F/scripts.pory"
	msgbox KingsisleDorm_Text_Reminder, MSGBOX_DEFAULT
# 55 "data/maps/KingsisleDorm_1F/scripts.pory"
	applymovement LOCALID_KINGSISLE_MERCURY_DORM, KingsisleDorm_EventScript_Reminder_Movement_0
# 56 "data/maps/KingsisleDorm_1F/scripts.pory"
	waitmovement 0
# 57 "data/maps/KingsisleDorm_1F/scripts.pory"
	setflag FLAG_HIDE_MERCURY_INSIDE
# 58 "data/maps/KingsisleDorm_1F/scripts.pory"
	releaseall
	end


# 10 "data/maps/KingsisleDorm_1F/scripts.pory"
KingsisleDorm_EventScript_DormExplanation_Movement_0:
# 10 "data/maps/KingsisleDorm_1F/scripts.pory"
	walk_up
# 10 "data/maps/KingsisleDorm_1F/scripts.pory"
	walk_up
# 10 "data/maps/KingsisleDorm_1F/scripts.pory"
	face_down
	step_end

# 55 "data/maps/KingsisleDorm_1F/scripts.pory"
KingsisleDorm_EventScript_Reminder_Movement_0:
# 55 "data/maps/KingsisleDorm_1F/scripts.pory"
	walk_down
# 55 "data/maps/KingsisleDorm_1F/scripts.pory"
	walk_down
# 55 "data/maps/KingsisleDorm_1F/scripts.pory"
	set_invisible
	step_end

KingsisleDorm_EventScript_AnyQuestions_Text_0:
# 22 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "Are you also a student?$"

KingsisleDorm_EventScript_AnyQuestions_Text_1:
# 25 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "When do classes start?$"

KingsisleDorm_EventScript_AnyQuestions_Text_2:
# 27 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "I'm good.$"

KingsisleDorm_Text_ThisIsIt::
# 62 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "Huh, not bad. They must've renovated\n"
	.string "recently.\p"
	.string "Well, this is it. Your home away from\n"
	.string "home for the next year or two. Your\l"
	.string "room's on the second floor, last door on\l"
	.string "the right. So, any questions for me\l"
	.string "before I send you on your merry way?$"

KingsisleDorm_Text_VeryFunny::
# 66 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "Ha. If I had a nickel for every time\n"
	.string "someone asked me that question, I\l"
	.string "could afford to quit this job.\p"
	.string "No, I'm the Dawnsinger family's head of\n"
	.string "security. Feel free to stop by my\l"
	.string "office, if you ever need anything.$"

KingsisleDorm_Text_ClassesStart::
# 70 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "Should be about a week or so of\n"
	.string "orientation-related activities until\l"
	.string "classes are fully underway.$"

KingsisleDorm_Text_Reminder::
# 74 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "Alright. In that case, I'll head out and\n"
	.string "let you get settled. I bought you a\l"
	.string "clock, should be up in your room. Don't\l"
	.string "forget to set it. And remember to go see\l"
	.string "Headmaster Dawnsinger at some point.\l"
	.string "Special request from the man himself.$"

KingsisleDorm_Text_Reminder_Alt::
# 78 "data/maps/KingsisleDorm_1F/scripts.pory"
	.string "Alright, well, I'll head out and let you\n"
	.string "get settled. I bought you a clock,\l"
	.string "should be up in your room. Don't forget\l"
	.string "to set it. And remember to go see\l"
	.string "Headmaster Dawnsinger at some point.\l"
	.string "Special request from the man himself.$"
