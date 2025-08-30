KingsisleInstitute_MapScripts::
	.byte 0


# 3 "data/maps/KingsisleInstitute/scripts.pory"

# 4 "data/maps/KingsisleInstitute/scripts.pory"
CommonName_Text_Student:
# 5 "data/maps/KingsisleInstitute/scripts.pory"
    .string "Student$"

DormSign::
# 9 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox DormSign_Text_0, MSGBOX_SIGN
	return


NadiaLab::
# 13 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox NadiaLab_Text_0, MSGBOX_SIGN
	return


SecurityOffice::
# 17 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox SecurityOffice_Text_0, MSGBOX_SIGN
	return


Kingsisle_MagicGuy::
# 21 "data/maps/KingsisleInstitute/scripts.pory"
	speakername CommonName_Text_Student
# 22 "data/maps/KingsisleInstitute/scripts.pory"
	msgbox MagicIsAmazing, MSGBOX_NPC
	return


DormSign_Text_0:
# 9 "data/maps/KingsisleInstitute/scripts.pory"
	.string "SOLGALEO HALL$"

NadiaLab_Text_0:
# 13 "data/maps/KingsisleInstitute/scripts.pory"
	.string "PROFESSOR NADIA'S LAB$"

SecurityOffice_Text_0:
# 17 "data/maps/KingsisleInstitute/scripts.pory"
	.string "KINGSISLE SECURITY OFFICE$"

MagicIsAmazing::
# 25 "data/maps/KingsisleInstitute/scripts.pory"
	.string "Magic is amazing!\p"
	.string "I heard that students at the top of\n"
	.string "their class are able to travel to other\l"
	.string "Underground sectors using\l"
	.string "teleportation circles!$"
