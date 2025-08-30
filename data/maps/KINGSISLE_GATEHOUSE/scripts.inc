KINGSISLE_GATEHOUSE_MapScripts::
	.byte 0


JealousStudent::
# 4 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	speakername CommonName_Text_Student
# 5 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	goto_if_set FLAG_RECIEVED_SITRUS_BERRIES, JealousStudent_1
# 7 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	goto_if_set FLAG_BADGE01_GET, JealousStudent_2
# 19 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	msgbox JealousTangent, MSGBOX_NPC
	return

JealousStudent_1:
# 6 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	msgbox LookingForward, MSGBOX_NPC
	return

JealousStudent_2:
# 8 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	msgbox BadgeSurprise, MSGBOX_NPC
# 9 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	lock
# 10 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	giveitem ITEM_SITRUS_BERRY, 3
# 11 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq JealousStudent_7
# 15 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	setflag FLAG_RECIEVED_SITRUS_BERRIES
JealousStudent_6:
# 17 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	release
	return

JealousStudent_7:
# 12 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	speakername CommonName_Text_Student
# 13 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	msgbox BagIsFull
	goto JealousStudent_6


BagIsFull::
# 23 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	.string "Woah, you're carrying way too much\n"
	.string "stuff. Come back after you've stored\l"
	.string "some!$"

JealousTangent::
# 27 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	.string "They're actually letting you leave the\n"
	.string "Institute?\p"
	.string "Lucky! I feel like I've been stuck in\n"
	.string "class since my first day here... two\l"
	.string "years ago!$"

BadgeSurprise::
# 31 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	.string "Wait, you actually got a badge? No way!\n"
	.string "Fine, then, hotshot. Take these.\l"
	.string "Hopefully they'll help you on your climb\l"
	.string "to the top!$"

LookingForward::
# 35 "data/maps/KINGSISLE_GATEHOUSE/scripts.pory"
	.string "Guess there's nowhere to go but up for\n"
	.string "you, huh? I'll be cheering you on!$"
