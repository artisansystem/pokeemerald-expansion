HeadmastersHouse_1F_MapScripts::
	.byte 0


KingsisleInstitute_HeadmastersHouse_Cyrus::
# 5 "data/maps/HeadmastersHouse_1F/scripts.pory"
	lock
# 6 "data/maps/HeadmastersHouse_1F/scripts.pory"
	faceplayer
# 7 "data/maps/HeadmastersHouse_1F/scripts.pory"
	goto_if_unset FLAG_MET_CYRUS, KingsisleInstitute_HeadmastersHouse_Cyrus_2
# 14 "data/maps/HeadmastersHouse_1F/scripts.pory"
	setspeaker SP_NAME_CYRUS
# 15 "data/maps/HeadmastersHouse_1F/scripts.pory"
	msgbox HeadmastersHouse_Text_MuchToDo, MSGBOX_DEFAULT
# 16 "data/maps/HeadmastersHouse_1F/scripts.pory"
	closemessage
# 17 "data/maps/HeadmastersHouse_1F/scripts.pory"
	msgbox HeadmastersHouse_Text_ShouldntBother, MSGBOX_DEFAULT
# 19 "data/maps/HeadmastersHouse_1F/scripts.pory"
	release
	end

KingsisleInstitute_HeadmastersHouse_Cyrus_2:
# 8 "data/maps/HeadmastersHouse_1F/scripts.pory"
	setspeaker SP_NAME_CYRUS
# 9 "data/maps/HeadmastersHouse_1F/scripts.pory"
	msgbox HeadmastersHouse_Text_CyrusIntroduction, MSGBOX_DEFAULT
# 10 "data/maps/HeadmastersHouse_1F/scripts.pory"
	setflag FLAG_MET_CYRUS
# 11 "data/maps/HeadmastersHouse_1F/scripts.pory"
	release
	end


HeadmastersHouse_Text_CyrusIntroduction::
# 23 "data/maps/HeadmastersHouse_1F/scripts.pory"
	.string "Oh, hello there. Are you one of the new\n"
	.string "students? I don't believe we've met. My\l"
	.string "name's Cyrus. If you're looking for my\l"
	.string "father, he should be in his study, down\l"
	.string "the hall.$"

HeadmastersHouse_Text_MuchToDo::
# 28 "data/maps/HeadmastersHouse_1F/scripts.pory"
	.string "I need to revise tomorrow's lesson\n"
	.string "plan... and grade last week's papers...\l"
	.string "and find a time for dinner with Sylvie...$"

HeadmastersHouse_Text_ShouldntBother::
# 34 "data/maps/HeadmastersHouse_1F/scripts.pory"
	.string "He seems wound up. You probably\n"
	.string "shouldn't bother him.$"
