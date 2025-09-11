Kingsisle_Nadia_Lab_MapScripts::
	.byte 0


# 3 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"

# 4 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
UniqueName_Text_Nadia:
# 5 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
    .string "Nadia$"

Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft::
# 9 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	lockall
# 10 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
# 11 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_SayHelloToFollower_TopLeft
# 12 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	delay 55
# 13 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_FOLLOWING_POKEMON, Kingsisle_NadiaLab_FollowerReactToBulbasaur_TopLeft
# 14 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement LOCALID_NADIA_BULBASAUR
# 15 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_SayHelloToPlayer_TopLeft
# 16 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_PLAYER, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_0
# 17 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement LOCALID_NADIA_BULBASAUR
# 18 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	delay 30
# 19 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_GoToNadia_TopLeft
# 20 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 21 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_0
# 22 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 23 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Text_0
# 24 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	closemessage
# 25 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_1
# 26 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_2
# 27 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 28 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_PLAYER, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_3
# 29 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_FOLLOWING_POKEMON, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_3
# 30 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 31 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_HaveAPokemon, MSGBOX_DEFAULT
# 32 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_4
# 33 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 34 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 35 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_InThatCase, MSGBOX_DEFAULT
# 36 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_5
# 37 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement 0
# 38 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 39 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_Pokedex1, MSGBOX_DEFAULT
# 40 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_0
# 41 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 42 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_Pokedex2, MSGBOX_DEFAULT
# 43 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions
	return


Kingsisle_NadiaLab_EventScript_PokedexReactions::
# 47 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	compare VAR_TEMP_1, 0
	goto_if_eq Kingsisle_NadiaLab_EventScript_PokedexReactions_2
Kingsisle_NadiaLab_EventScript_PokedexReactions_1:
# 50 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	compare VAR_TEMP_2, 0
	goto_if_eq Kingsisle_NadiaLab_EventScript_PokedexReactions_5
Kingsisle_NadiaLab_EventScript_PokedexReactions_4:
# 53 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	compare VAR_TEMP_1, 1
	goto_if_eq Kingsisle_NadiaLab_EventScript_PokedexReactions_8
Kingsisle_NadiaLab_EventScript_PokedexReactions_7:
# 56 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	dynmultistack 0, 0, TRUE, 3, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 58 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	switch VAR_RESULT
# 59 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	case 0, Kingsisle_NadiaLab_EventScript_PokedexReactions_11
# 60 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	case 1, Kingsisle_NadiaLab_EventScript_PokedexReactions_12
# 61 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	case 2, Kingsisle_NadiaLab_EventScript_PokedexReactions_13
	return

Kingsisle_NadiaLab_EventScript_PokedexReactions_2:
# 48 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	dynmultipush Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_0, 0
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions_1

Kingsisle_NadiaLab_EventScript_PokedexReactions_5:
# 51 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	dynmultipush Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_1, 1
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions_4

Kingsisle_NadiaLab_EventScript_PokedexReactions_8:
# 54 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	dynmultipush Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_2, 2
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions_7

Kingsisle_NadiaLab_EventScript_PokedexReactions_11:
# 59 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_RewardPromise
	return

Kingsisle_NadiaLab_EventScript_PokedexReactions_12:
# 60 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_UrielJudgement
	return

Kingsisle_NadiaLab_EventScript_PokedexReactions_13:
# 61 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_AcceptedPokedex
	return


Kingsisle_NadiaLab_EventScript_RewardPromise::
# 66 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 67 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_RewardPromise
# 68 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setvar VAR_TEMP_1, 1
# 69 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions
	return


Kingsisle_NadiaLab_EventScript_UrielJudgement::
# 73 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 74 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_UrielJudgement
# 75 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setvar VAR_TEMP_2, 1
# 76 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	goto Kingsisle_NadiaLab_EventScript_PokedexReactions
	return


Kingsisle_NadiaLab_EventScript_AcceptedPokedex::
# 80 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_0
# 81 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	speakername UniqueName_Text_Nadia
# 82 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	msgbox Kingsisle_NadiaLab_Text_GoodLuck
# 83 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	closemessage
# 84 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_LAB, Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_1
# 85 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	applymovement LOCALID_NADIA_BULBASAUR, Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_2
# 86 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	waitmovement LOCALID_NADIA_LAB
# 87 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setvar VAR_KINGSISLE_INTRO_STATE, 7
# 88 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	startquest QUEST_COMPLETE_REGIONAL_POKEDEX
# 89 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	setflag FLAG_SYS_POKEDEX_GET
# 90 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	releaseall
	end


# 94 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_SayHelloToFollower_TopLeft:
# 95 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	emote_exclamation_mark
# 96 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_down
# 96 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_down
# 96 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_fast_down
# 97 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 97 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 98 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	jump_in_place_left
# 99 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	emote_heart
# 100 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	step_end

# 103 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_SayHelloToPlayer_TopLeft:
# 104 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 105 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_player
# 106 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	emote_question_mark
# 107 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	step_end

# 110 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_GoToNadia_TopLeft:
# 111 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 111 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 111 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 112 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 112 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 112 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 113 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	step_end

# 116 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_FollowerReactToBulbasaur_TopLeft:
# 117 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_right
# 118 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	emote_exclamation_mark
# 119 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	jump_in_place_right
# 120 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	step_end

# 16 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_0:
# 16 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_right
	step_end

# 25 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_1:
# 25 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_down
# 25 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 25 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 25 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 25 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_down
	step_end

# 26 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_2:
# 26 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	delay_8
# 26 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 26 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 26 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 26 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_down
	step_end

# 28 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_3:
# 28 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_up
	step_end

# 32 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_4:
# 32 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_left
	step_end

# 36 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Movement_5:
# 36 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 36 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 36 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 36 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_down
# 36 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_left
# 36 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	delay_8
	step_end

# 80 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_0:
# 80 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 80 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 80 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 80 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	face_down
	step_end

# 84 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_1:
# 84 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 84 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 84 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 84 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
# 84 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_left
	step_end

# 85 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
Kingsisle_NadiaLab_EventScript_AcceptedPokedex_Movement_2:
# 85 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_up
# 85 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
# 85 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	walk_right
	step_end

Kingsisle_NadiaLab_EventScript_RecievePokedex_TopLeft_Text_0:
# 23 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "...$"

Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_0:
# 48 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "What's in it for me?$"

Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_1:
# 51 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Why me?$"

Kingsisle_NadiaLab_EventScript_PokedexReactions_Text_2:
# 54 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Sure, I guess?$"

Kingsisle_NadiaLab_Text_HaveAPokemon::
# 123 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "So, his Holiness, Uriel Dawnsinger,\n"
	.string "actually gave you a Pokémon?\p"
	.string "... Hm. He doesn't usually have such an...\n"
	.string "interest in students. You must show\l"
	.string "some real promise.$"

Kingsisle_NadiaLab_Text_InThatCase::
# 127 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Well... If that's the case, how 'bout you\n"
	.string "help me with a little project?$"

Kingsisle_NadiaLab_Text_Pokedex1::
# 131 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "This device is called a Pokédex. It's\n"
	.string "got a fascinating history, but the\l"
	.string "electronic version of it you see here\l"
	.string "was developed in-house for the purpose\l"
	.string "of aiding students in their research.\l"
	.string "That's where you come in.$"

Kingsisle_NadiaLab_Text_Pokedex2::
# 135 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "I'd like you to record data on as many\n"
	.string "types of Pokémon as you can find.\l"
	.string "Understood?$"

Kingsisle_NadiaLab_Text_RewardPromise::
# 139 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Look, I'll level with you, {PLAYER_LAST_NAME}. I'm\n"
	.string "not a fieldwork sort of gal. And I've got\l"
	.string "classes to teach. So if you do this for\l"
	.string "me, I'll make sure to reward you. Let's\l"
	.string "start small... catch ten species and\l"
	.string "we'll talk, okay?$"

Kingsisle_NadiaLab_Text_UrielJudgement::
# 143 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "I don't always trust Uriel's judgement.\n"
	.string "But only time will tell if he's right\l"
	.string "about you. So consider this me throwing\l"
	.string "you a bone.$"

Kingsisle_NadiaLab_Text_GoodLuck::
# 147 "data/maps/Kingsisle_Nadia_Lab/scripts.pory"
	.string "Alright, then, glad we could come to an\n"
	.string "agreement. Good luck out there,\l"
	.string "{PLAYER_LAST_NAME}.$"
