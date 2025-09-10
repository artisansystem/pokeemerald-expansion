Kingsisle_Nadia_Lab_MapScripts::
	.byte 0


# 3 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"

# 4 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
UniqueName_Text_Nadia:
# 5 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
    .string "Nadia$"

Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft::
# 9 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setflag FLAG_TEMP_HIDE_FOLLOWER == FALSE
# 10 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_SayHelloToFollower_TopLeft
# 11 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	delay 30
# 12 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_FOLLOWING_POKEMON, Kingsisle_NadiaLab_FollowerReactToBulbasaur_TopLeft
# 13 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 14 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_SayHelloToPlayer_TopLeft
# 15 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 16 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_GoToNadia_TopLeft
# 17 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_0
# 18 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 19 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 20 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Text_0
# 21 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	closemessage
# 22 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_1
# 23 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_2
# 24 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 25 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 26 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_HaveAPokemon, MSGBOX_DEFAULT
# 27 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_3
# 28 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 29 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 30 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_InThatCase, MSGBOX_DEFAULT
# 31 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_4
# 32 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 33 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 34 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_Pokedex, MSGBOX_DEFAULT
# 35 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions
	return


Kingsisle_NadiaLab_EventScript_PokedexReactions::
# 39 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	compare VAR_TEMP_1, 0
	goto_if_eq Kingsisle_NadiaLab_EventScript_PokedexReactions_2
Kingsisle_NadiaLab_EventScript_PokedexReactions_1:
# 42 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	compare VAR_TEMP_2, 0
	goto_if_eq Kingsisle_NadiaLab_EventScript_PokedexReactions_5
Kingsisle_NadiaLab_EventScript_PokedexReactions_4:
# 45 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	compare VAR_TEMP_1, 1
	goto_if_eq Kingsisle_NadiaLab_EventScript_PokedexReactions_8
Kingsisle_NadiaLab_EventScript_PokedexReactions_7:
# 48 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	dynmultistack 0, 0, TRUE, 3, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 50 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	switch VAR_RESULT
# 51 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	case 0, Kingsisle_NadiaLab_EventScript_PokedexReactions_11
# 52 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	case 1, Kingsisle_NadiaLab_EventScript_PokedexReactions_12
# 53 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	case 2, Kingsisle_NadiaLab_EventScript_PokedexReactions_13
	return

Kingsisle_NadiaLab_EventScript_PokedexReactions_2:
# 40 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	dynmultipush Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_0, 0
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions_1

Kingsisle_NadiaLab_EventScript_PokedexReactions_5:
# 43 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	dynmultipush Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_1, 1
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions_4

Kingsisle_NadiaLab_EventScript_PokedexReactions_8:
# 46 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	dynmultipush Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_2, 2
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions_7

Kingsisle_NadiaLab_EventScript_PokedexReactions_11:
# 51 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_RewardPromise
	return

Kingsisle_NadiaLab_EventScript_PokedexReactions_12:
# 52 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_UrielJudgement
	return

Kingsisle_NadiaLab_EventScript_PokedexReactions_13:
# 53 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_AcceptedPokedex
	return


Kingsisle_NadiaLab_EventScript_RewardPromise::
# 58 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 59 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_RewardPromise
# 60 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setvar VAR_TEMP_1, 1
# 61 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions
	return


Kingsisle_NadiaLab_EventScript_UrielJudgement::
# 65 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 66 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_UrielJudgement
# 67 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setvar VAR_TEMP_2, 1
# 68 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions
	return


Kingsisle_NadiaLab_EventScript_AcceptedPokedex::
# 72 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_0
# 73 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 74 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_GoodLuck
# 75 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	closemessage
# 76 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_1
# 77 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setvar VAR_KINGSISLE_INTRO_STATE, 7
	end


# 81 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_SayHelloToFollower_TopLeft:
# 82 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	emote_exclamation_mark
# 83 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_down
# 83 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_down
# 83 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_down
# 84 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_left
# 84 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_left
# 85 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	jump_in_place_up_down
# 86 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	emote_heart
# 87 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	step_end

# 90 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_SayHelloToPlayer_TopLeft:
# 91 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_up
# 92 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_player
# 93 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	emote_question_mark
# 94 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	step_end

# 97 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_GoToNadia_TopLeft:
# 98 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_up
# 98 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_up
# 98 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_up
# 98 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_up
# 99 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_left
# 99 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_left
# 99 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_left
# 100 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	step_end

# 103 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_FollowerReactToBulbasaur_TopLeft:
# 104 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_right
# 105 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	emote_exclamation_mark
# 106 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	jump_in_place_up_down
# 107 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	step_end

# 17 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_0:
# 17 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_right
	step_end

# 22 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_1:
# 22 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_down
# 22 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 22 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 22 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 22 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_down
	step_end

# 23 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_2:
# 23 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	delay_8
# 23 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 23 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 23 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 23 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_down
	step_end

# 27 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_3:
# 27 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_left
	step_end

# 31 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_4:
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

# 72 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_0:
# 72 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 72 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 72 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 72 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_down
	step_end

# 76 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_1:
# 76 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 76 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 76 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 76 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 76 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
	step_end

Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Text_0:
# 20 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "...$"

Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_0:
# 40 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "What's in it for me?$"

Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_1:
# 43 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Why me?$"

Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_2:
# 46 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Sure, I guess?$"

Kingsisle_NadiaLab_Text_HaveAPokemon::
# 110 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "So, Mr. Uriel Dawnsinger gave you a\n"
	.string "Pokémon?\p"
	.string "... Hm. He doesn't usually have such an...\n"
	.string "interest in students. You must show\l"
	.string "some real promise.$"

Kingsisle_NadiaLab_Text_InThatCase::
# 114 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Well... If that's the case, how 'bout you\n"
	.string "help me with a little project?$"

Kingsisle_NadiaLab_Text_Pokedex::
# 118 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "This device is called a Pokédex. It's\n"
	.string "got a fascinating history, but the\l"
	.string "electronic version of it you see here\l"
	.string "was developed in-house for the purpose\l"
	.string "of aiding students in their research.\l"
	.string "That's where you come in. I'd like you to\l"
	.string "record data on as many types of\l"
	.string "Pokémon as you can find. Understood?$"

Kingsisle_NadiaLab_Text_RewardPromise::
# 122 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Look, I'll level with you, {PLAYER_LAST_NAME}. I'm\n"
	.string "not a fieldwork sort of gal. And I've got\l"
	.string "classes to teach. So if you do this for\l"
	.string "me, I'll make sure to reward you. Let's\l"
	.string "start small... catch ten species and\l"
	.string "we'll talk, okay?$"

Kingsisle_NadiaLab_Text_UrielJudgement::
# 126 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "I don't always trust Uriel's judgement.\n"
	.string "But only time will tell if he's right\l"
	.string "about you. So consider this me throwing\l"
	.string "you a bone.$"

Kingsisle_NadiaLab_Text_GoodLuck::
# 130 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Alright, then, glad we could come to an\n"
	.string "agreement. Good luck out there,\l"
	.string "{PLAYER_LAST_NAME}.$"
