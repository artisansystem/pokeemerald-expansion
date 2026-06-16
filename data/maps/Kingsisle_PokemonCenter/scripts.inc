Kingsisle_PokemonCenter_MapScripts::
# 2 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Kingsisle_PokemonCenter_OnTransition
	.byte 0


Kingsisle_PokemonCenter_OnTransition::
# 6 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	setrespawn HEAL_LOCATION_KINGSISLE_INSTITUTE
	end


Kingisle_PokemonCenter_EventScript_Nurse::
# 11 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	setvar VAR_0x800B, LOCALID_KINGSISLE_NURSE
	getpartysize
# 0 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Kingisle_PokemonCenter_EventScript_Nurse_1
	getpartysize
# 0 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_gt Kingisle_PokemonCenter_EventScript_Nurse_2
	return

Kingisle_PokemonCenter_EventScript_Nurse_1:
# 14 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	lock
# 15 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	faceplayer
# 16 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	msgbox Kingsisle_PkmnCenterNurse_Text_NoPokemon, MSGBOX_DEFAULT
# 17 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	applymovement LOCALID_KINGSISLE_NURSE, Kingisle_PokemonCenter_EventScript_Nurse_Movement_0
# 18 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	msgbox Kingsisle_PkmnCenterNurse_Text_SeeYouAgain, MSGBOX_DEFAULT
# 19 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	waitmovement
# 20 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	release
	end

Kingisle_PokemonCenter_EventScript_Nurse_2:
# 26 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	call Common_EventScript_PkmnCenterNurse
# 27 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	waitmessage
# 28 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	waitbuttonpress
# 29 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	release
	end


# 17 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
Kingisle_PokemonCenter_EventScript_Nurse_Movement_0:
# 17 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	nurse_joy_bow
# 17 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	delay_4
	step_end

Kingsisle_PkmnCenterNurse_Text_NoPokemon::
# 35 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	.string "Hello, and welcome to the Pokémon\n"
	.string "Center. I can't help but notice that you\l"
	.string "don't have any Pokémon with you. We\l"
	.string "would be happy to serve you once you\l"
	.string "obtain a Pokémon.$"

Kingsisle_PkmnCenterNurse_Text_SeeYouAgain::
# 40 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	.string "We hope to see you again!$"
