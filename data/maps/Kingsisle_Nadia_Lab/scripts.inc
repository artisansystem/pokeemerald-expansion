Kingsisle_Nadia_Lab_MapScripts::
	.byte 0


Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft::
# 4 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	lockall
# 5 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
# 6 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_SayHelloToFollower_TopLeft
# 7 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	delay 55
# 8 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_FOLLOWING_POKEMON, Kingsisle_NadiaLab_FollowerReactToBulbasaur_TopLeft
# 9 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement LOCALID_NADIA_BULBASAUR
# 10 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_SayHelloToPlayer_TopLeft
# 11 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_PLAYER, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_0
# 12 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement LOCALID_NADIA_BULBASAUR
# 13 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	delay 30
# 14 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_GoToNadia_TopLeft
# 15 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 16 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_0
# 17 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setspeaker SP_NAME_NADIA
# 18 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Text_0
# 19 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	closemessage
# 20 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_1
# 21 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_2
# 22 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 23 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_PLAYER, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_3
# 24 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_FOLLOWING_POKEMON, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_3
# 25 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setspeaker SP_NAME_NADIA
# 26 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_HaveAPokemon, MSGBOX_DEFAULT
# 27 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_4
# 28 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 29 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setspeaker SP_NAME_NADIA
# 30 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_InThatCase, MSGBOX_DEFAULT
# 31 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_5
# 32 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 33 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setspeaker SP_NAME_NADIA
# 34 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_Pokedex1, MSGBOX_DEFAULT
# 35 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_0
# 36 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setspeaker SP_NAME_NADIA
# 37 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_Pokedex2, MSGBOX_DEFAULT
# 38 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions
	return


Kingsisle_NadiaLab_EventScript_PokedexReactions::
# 42 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	compare VAR_TEMP_1, 0
	goto_if_eq Kingsisle_NadiaLab_EventScript_PokedexReactions_2
Kingsisle_NadiaLab_EventScript_PokedexReactions_1:
# 45 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	compare VAR_TEMP_2, 0
	goto_if_eq Kingsisle_NadiaLab_EventScript_PokedexReactions_5
Kingsisle_NadiaLab_EventScript_PokedexReactions_4:
# 48 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	compare VAR_TEMP_1, 1
	goto_if_eq Kingsisle_NadiaLab_EventScript_PokedexReactions_8
Kingsisle_NadiaLab_EventScript_PokedexReactions_7:
# 51 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	dynmultistack 0, 0, TRUE, 3, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 53 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	switch VAR_RESULT
# 54 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	case 0, Kingsisle_NadiaLab_EventScript_PokedexReactions_11
# 55 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	case 1, Kingsisle_NadiaLab_EventScript_PokedexReactions_12
# 56 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	case 2, Kingsisle_NadiaLab_EventScript_PokedexReactions_13
	return

Kingsisle_NadiaLab_EventScript_PokedexReactions_2:
# 43 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	dynmultipush Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_0, 0
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions_1

Kingsisle_NadiaLab_EventScript_PokedexReactions_5:
# 46 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	dynmultipush Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_1, 1
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions_4

Kingsisle_NadiaLab_EventScript_PokedexReactions_8:
# 49 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	dynmultipush Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_2, 2
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions_7

Kingsisle_NadiaLab_EventScript_PokedexReactions_11:
# 54 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_RewardPromise
	return

Kingsisle_NadiaLab_EventScript_PokedexReactions_12:
# 55 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_UrielJudgement
	return

Kingsisle_NadiaLab_EventScript_PokedexReactions_13:
# 56 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_AcceptedPokedex
	return


Kingsisle_NadiaLab_EventScript_RewardPromise::
# 61 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setspeaker SP_NAME_NADIA
# 62 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_RewardPromise
# 63 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setvar VAR_TEMP_1, 1
# 64 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions
	return


Kingsisle_NadiaLab_EventScript_UrielJudgement::
# 68 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setspeaker SP_NAME_NADIA
# 69 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_UrielJudgement
# 70 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setvar VAR_TEMP_2, 1
# 71 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions
	return


Kingsisle_NadiaLab_EventScript_AcceptedPokedex::
# 75 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_0
# 76 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setspeaker SP_NAME_NADIA
# 77 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_GoodLuck
# 78 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	closemessage
# 79 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_1
# 80 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_2
# 81 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement LOCALID_NADIA_LAB
# 82 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setvar VAR_KINGSISLE_INTRO_STATE, 7
# 83 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	startquest QUEST_COMPLETE_REGIONAL_POKEDEX
# 84 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setflag FLAG_SYS_POKEDEX_GET
# 85 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	releaseall
	end


# 89 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_SayHelloToFollower_TopLeft:
# 90 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	emote_exclamation_mark
# 91 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_down
# 91 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_down
# 91 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_down
# 92 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 92 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 93 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	jump_in_place_left
# 94 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	emote_heart
# 95 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	step_end

# 98 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_SayHelloToPlayer_TopLeft:
# 99 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 100 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_player
# 101 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	emote_question_mark
# 102 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	step_end

# 105 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_GoToNadia_TopLeft:
# 106 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 106 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 106 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 107 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 107 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 107 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 108 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	step_end

# 111 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_FollowerReactToBulbasaur_TopLeft:
# 112 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_right
# 113 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	emote_exclamation_mark
# 114 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	jump_in_place_right
# 115 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	step_end

# 11 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_0:
# 11 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_right
	step_end

# 20 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_1:
# 20 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_down
# 20 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 20 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 20 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 20 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_down
	step_end

# 21 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_2:
# 21 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	delay_8
# 21 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 21 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 21 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 21 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_down
	step_end

# 23 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_3:
# 23 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_up
	step_end

# 27 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_4:
# 27 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_left
	step_end

# 31 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_5:
# 31 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 31 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 31 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 31 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_down
# 31 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_left
# 31 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	delay_8
	step_end

# 75 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_0:
# 75 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 75 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 75 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 75 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_down
	step_end

# 79 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_1:
# 79 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 79 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 79 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 79 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 79 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
	step_end

# 80 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_2:
# 80 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 80 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 80 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
	step_end

Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Text_0:
# 18 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "...$"

Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_0:
# 43 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "What's in it for me?$"

Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_1:
# 46 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Why me?$"

Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_2:
# 49 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Sure, I guess?$"

Kingsisle_NadiaLab_Text_HaveAPokemon::
# 118 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "So, his Holiness, Uriel Dawnsinger,\n"
	.string "actually gave you a Pokémon?\p"
	.string "... Hm. He doesn't usually have such an...\n"
	.string "interest in students. You must show\l"
	.string "some real promise.$"

Kingsisle_NadiaLab_Text_InThatCase::
# 122 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Well... If that's the case, how 'bout you\n"
	.string "help me with a little project?$"

Kingsisle_NadiaLab_Text_Pokedex1::
# 126 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "This device is called a Pokédex. It's\n"
	.string "got a fascinating history, but the\l"
	.string "electronic version of it you see here\l"
	.string "was developed in-house for the purpose\l"
	.string "of aiding students in their research.\l"
	.string "That's where you come in.$"

Kingsisle_NadiaLab_Text_Pokedex2::
# 130 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "I'd like you to record data on as many\n"
	.string "types of Pokémon as you can find.\l"
	.string "Understood?$"

Kingsisle_NadiaLab_Text_RewardPromise::
# 134 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Look, I'll level with you, {PLAYER_LAST_NAME}. I'm\n"
	.string "not a fieldwork sort of gal. And I've got\l"
	.string "classes to teach. So if you do this for\l"
	.string "me, I'll make sure to reward you. Let's\l"
	.string "start small... catch ten species and\l"
	.string "we'll talk, okay?$"

Kingsisle_NadiaLab_Text_UrielJudgement::
# 138 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "I don't always trust Uriel's judgement.\n"
	.string "But only time will tell if he's right\l"
	.string "about you. So consider this me throwing\l"
	.string "you a bone.$"

Kingsisle_NadiaLab_Text_GoodLuck::
# 142 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Alright, then, glad we could come to an\n"
	.string "agreement. Good luck out there,\l"
	.string "{PLAYER_LAST_NAME}.$"
