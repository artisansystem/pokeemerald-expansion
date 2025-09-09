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
# 12 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	call Common_EventScript_PkmnCenterNurse
# 13 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	waitmessage
# 14 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	waitbuttonpress
# 15 "data/maps/Kingsisle_PokemonCenter/scripts.pory"
	release
	end

