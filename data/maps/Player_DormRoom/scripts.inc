Player_DormRoom_MapScripts::
	.byte 0


Player_DormRoom_ClockIsStopped::
# 4 "data/maps/Player_DormRoom/scripts.pory"
	goto_if_unset FLAG_SET_WALL_CLOCK, Player_DormRoom_ClockIsStopped_1
# 12 "data/maps/Player_DormRoom/scripts.pory"
	call Player_DormRoom_EventScript_CheckWallClock
	return

Player_DormRoom_ClockIsStopped_1:
# 5 "data/maps/Player_DormRoom/scripts.pory"
	msgbox Player_DormRoom_Text_ClockIsStopped, MSGBOX_DEFAULT
# 6 "data/maps/Player_DormRoom/scripts.pory"
	call Player_DormRoom_EventScript_SetWallClock
# 7 "data/maps/Player_DormRoom/scripts.pory"
	delay 30
# 8 "data/maps/Player_DormRoom/scripts.pory"
	setvar VAR_KINGSISLE_INTRO_STATE, 4
# 9 "data/maps/Player_DormRoom/scripts.pory"
	setflag FLAG_SET_WALL_CLOCK
	return


Player_DormRoom_EventScript_SetWallClock::
# 17 "data/maps/Player_DormRoom/scripts.pory"
	fadescreen FADE_TO_BLACK
# 18 "data/maps/Player_DormRoom/scripts.pory"
	special StartWallClock
# 19 "data/maps/Player_DormRoom/scripts.pory"
	waitstate
	return


Player_DormRoom_EventScript_CheckWallClock::
# 24 "data/maps/Player_DormRoom/scripts.pory"
	fadescreen FADE_TO_BLACK
# 25 "data/maps/Player_DormRoom/scripts.pory"
	special Special_ViewWallClock
# 26 "data/maps/Player_DormRoom/scripts.pory"
	waitstate
# 27 "data/maps/Player_DormRoom/scripts.pory"
	releaseall
	end


Player_DormRoom_EventScript_CheckPC::
# 32 "data/maps/Player_DormRoom/scripts.pory"
	special DoPCTurnOnEffect
# 33 "data/maps/Player_DormRoom/scripts.pory"
	playse SE_PC_ON
# 34 "data/maps/Player_DormRoom/scripts.pory"
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
# 35 "data/maps/Player_DormRoom/scripts.pory"
	special BedroomPC
# 36 "data/maps/Player_DormRoom/scripts.pory"
	waitstate
# 37 "data/maps/Player_DormRoom/scripts.pory"
	releaseall
	end


Player_DormRoom_EventScript_TurnOffPC::
# 42 "data/maps/Player_DormRoom/scripts.pory"
	playse SE_PC_OFF
# 43 "data/maps/Player_DormRoom/scripts.pory"
	special DoPCTurnOffEffect
# 44 "data/maps/Player_DormRoom/scripts.pory"
	releaseall
	end


Player_DormRoom_Text_ClockIsStopped::
# 48 "data/maps/Player_DormRoom/scripts.pory"
	.string "The clock is stopped...\p"
	.string "Better set it and start it.$"
