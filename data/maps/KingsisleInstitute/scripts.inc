KingsisleInstitute_MapScripts::
	.byte 0


DormSign::
# 4 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox DormSign_Text_0, MSGBOX_SIGN
	return


NadiaLab::
# 8 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox NadiaLab_Text_0, MSGBOX_SIGN
	return


SecurityOffice::
# 12 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox SecurityOffice_Text_0, MSGBOX_SIGN
	return


AcademySign::
# 16 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox AcademySign_Text_0, MSGBOX_SIGN
	return


Kingsisle_MagicGuy::
# 20 "data/maps/KingsisleInstitute/scripts.pory"
	setspeaker SP_NAME_STUDENT
# 21 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox MagicIsAmazing, MSGBOX_NPC
	return


DormSign_Text_0:
# 4 "data/maps/KingsisleInstitute/scripts.pory"
	.string "SOLGALEO HALL$"

NadiaLab_Text_0:
# 8 "data/maps/KingsisleInstitute/scripts.pory"
	.string "PROFESSOR NADIA'S LAB$"

SecurityOffice_Text_0:
# 12 "data/maps/KingsisleInstitute/scripts.pory"
	.string "KINGSISLE SECURITY OFFICE$"

AcademySign_Text_0:
# 16 "data/maps/KingsisleInstitute/scripts.pory"
	.string "ACADEMY THIS WAY$"

MagicIsAmazing::
# 24 "data/maps/KingsisleInstitute/scripts.pory"
	.string "Magic is amazing!\p"
	.string "I heard that students at the top of\n"
	.string "their class are able to travel to other\l"
	.string "Underground sectors using\l"
	.string "teleportation circles!$"
