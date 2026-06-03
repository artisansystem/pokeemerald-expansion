KingsisleDorm_2F_MapScripts::
	.byte 0


KingsisleDorm_2F_NeedSetClock::
# 4 "data/maps/KingsisleDorm_2F/scripts.pory"
	lockall
# 5 "data/maps/KingsisleDorm_2F/scripts.pory"
	msgbox KingsisleDorm_2F_Text_NeedSetClock, MSGBOX_DEFAULT
# 6 "data/maps/KingsisleDorm_2F/scripts.pory"
	closemessage
# 7 "data/maps/KingsisleDorm_2F/scripts.pory"
	applymovement LOCALID_PLAYER, KingsisleDorm_2F_NeedSetClock_Movement_0
# 8 "data/maps/KingsisleDorm_2F/scripts.pory"
	waitmovement 0
# 9 "data/maps/KingsisleDorm_2F/scripts.pory"
	releaseall
	return


# 7 "data/maps/KingsisleDorm_2F/scripts.pory"
KingsisleDorm_2F_NeedSetClock_Movement_0:
# 7 "data/maps/KingsisleDorm_2F/scripts.pory"
	face_down
# 7 "data/maps/KingsisleDorm_2F/scripts.pory"
	walk_down
	step_end

KingsisleDorm_2F_Text_NeedSetClock::
# 12 "data/maps/KingsisleDorm_2F/scripts.pory"
	.string "I should probably set my clock first.$"
