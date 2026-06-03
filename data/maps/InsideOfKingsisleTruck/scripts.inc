InsideOfKingsisleTruck_MapScripts::
	.byte 0


InsideOfKingsisleTruck_EventScripts_SetIntroFlags::
# 4 "data/maps/InsideOfKingsisleTruck/scripts.pory"
	lockall
# 5 "data/maps/InsideOfKingsisleTruck/scripts.pory"
	setflag FLAG_HIDE_MAP_NAME_POPUP
# 6 "data/maps/InsideOfKingsisleTruck/scripts.pory"
	setvar VAR_KINGSISLE_INTRO_STATE, 1
# 7 "data/maps/InsideOfKingsisleTruck/scripts.pory"
	setdynamicwarp MAP_KINGSISLE_INSTITUTE, 24, 16
# 8 "data/maps/InsideOfKingsisleTruck/scripts.pory"
	releaseall
	end

