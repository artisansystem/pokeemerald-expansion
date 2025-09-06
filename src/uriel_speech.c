#include "global.h"
#include "main.h"
#include "bg.h"
#include "gpu_regs.h"
#include "sprite.h"
#include "window.h"
#include "decompress.h"
#include "text.h"
#include "constants/characters.h"
#include "string_util.h"
#include "palette.h"
#include "palette_util.h"
#include "malloc.h"
#include "task.h"
#include "menu.h"
#include "main_menu.h"
#include "random.h"
#include "scanline_effect.h"
#include "sound.h"
#include "strings.h"
#include "trainer_pokemon_sprites.h"
#include "pokeball.h"
#include "pokemon.h"
#include "naming_screen.h"
#include "overworld.h"
#include "uriel_speech.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "title_screen.h"
#include "stddef.h"
#include "string.h"
#include "stdint.h"
#include "field_effect.h"

// Define, enum, struct definitions

#define MON_POS_X 100 
#define MON_POS_Y 75

// bg pos
#define JACOB_MUGSHOT_CENTER_POS 30
#define EMILY_MUGSHOT_CENTER_POS  29
#define BRIAR_MUGSHOT_CENTER_POS  28

#define tWindowId data[1]
#define tPlayerSpriteId data[2]
#define tPrevCursorPos data[3]
#define tIsDoneFadingSprites data[4]
#define tNextSpriteId data[5]
#define tPlayerGender data[6]

#define WINDOWID_YES_NO 1
#define NUM_PRESET_NAMES 8

// tSpriteType, for fade in/out
enum SpriteTypes
{
    // these arent technically sprites but close nuff :)
    SPRITE_TYPE_MUGSHOT_1 = 0,
    SPRITE_TYPE_MUGSHOT_2,
    SPRITE_TYPE_MUGSHOT_3,
    // similar to above but not quite
    SPRITE_TYPE_PLAYER,
    SPRITE_TYPE_NONE,
};

enum Bgs
{
    // self explanatory
    BG_TEXT = 0,
    // generic names as their usage is both for
    // kaba and player/rival sprites
    BG_MUGSHOT_1,
    BG_MUGSHOT_2,
    // BG_MUGSHOT_3,
    // BG_BG feels stupid but this isn't any better either,
    // suggestions welcome (for context this is for the red bg)
    BG_INTRO,
    BG_COUNT,
};

enum WindowIds
{
    WIN_TEXT = 0,
    WIN_COUNT,
};

enum SpeechLoadStates
{
    STATE_RESET = 0,
    STATE_ALLOC,
    STATE_REGS,
    STATE_BGS,
    STATE_BG_GFX,
    STATE_WINDOWS,
    STATE_FINISH,
    STATE_COUNT,
};

enum PicIds
{
    MUGSHOT_MALE_STUDENT = 0,
    MUGSHOT_FEMALE_STUDENT,
    MUGSHOT_ENBY_STUDENT,
    MUGSHOT_URIEL,
    MUGSHOT_COUNT
};

struct UrielSpeech
{
    u16 introTilemapBuffer[0x800];
    u16 pic1TilemapBuffer[0x800];
    u16 pic2TilemapBuffer[0x800];
    // u16 pic3TilemapBuffer[0x800];
    u8 monSpriteId;
    u8 urielSpriteId;
    u8 platformSpriteIdLeft;
    u8 platformSpriteIdRight;
    u8 maleStudentSpriteId;
    u8 femaleStudentSpriteId;
    u8 enbyStudentSpriteId;
    s16 alphaCoeff;
    s16 alphaCoeff2;
    s16 timer;
    s16 fadeTimer;
    s16 counter;
    bool32 fadeFinished:1;
    bool32 playerHasName:1;
    bool32 playerHasLastName:1;
};

// EWRAM data
static EWRAM_DATA struct UrielSpeech *sUrielSpeech = NULL;

// Globals
static u8 sDebugWindowId;

// Function declarations
static void Task_UrielSpeech_Begin(u8);
static void Task_UrielSpeech_FadeInEverything(u8);
static void Task_UrielSpeech_Welcome(u8);
static void Task_UrielSpeech_Acceptance(u8);
static void Task_UrielSpeech_ThisIs(u8);
static void Task_UrielSpeech_ReleaseAlakazamFromPokeball(u8);
static void Task_UrielSpeech_AlakazamAPokemon(u8);
static void Task_UrielSpeech_MainSpeech(u8);
static void Task_UrielSpeech_Registration(u8);
static void Task_UrielSpeech_PlatformFade(u8);
static void Task_UrielSpeech_SlidePlatformAway(u8);
static void Task_UrielSpeech_StartPlayerFadeIn(u8);
static void Task_UrielSpeech_GenderSelect(u8);
static void Task_UrielSpeech_WaitToShowGenderMenu(u8);
static void UrielSpeech_ShowGenderMenu(u8);
static void Task_UrielSpeech_ChooseGender(u8);
static void Task_UrielSpeech_SwitchGenderSprite(u8);
static void Task_UrielSpeech_SlideOutOldGenderSprite(u8);
static void Task_UrielSpeech_SlideInNewGenderSprite(u8);
static s8 UrielSpeech_ProcessGenderMenuInput(void);
static void Task_UrielSpeech_YourName(u8);
static void Task_UrielSpeech_WaitForWhatsYourNameToPrint(u8);
static void Task_UrielSpeech_WaitPressBeforeNameChoice(u8);
static void Task_UrielSpeech_StartNamingScreen(u8);
static void Task_UrielSpeech_ReturnFromNamingScreenShowTextbox(u8);
static void Task_UrielSpeech_ConfirmFirstName(u8);
static void Task_UrielSpeech_CreateFirstNameYesNo(u8);
static void Task_UrielSpeech_ProcessFirstNameYesNoMenu(u8);
static void Task_UrielSpeech_YourLastName(u8);
static void Task_UrielSpeech_WaitForWhatsYourLastNameToPrint(u8);
static void Task_UrielSpeech_WaitPressBeforeLastNameChoice(u8);
static void Task_UrielSpeech_StartNamingScreen2(u8);
static void Task_UrielSpeech_ReturnFromNamingScreen2ShowTextbox(u8);
static void Task_UrielSpeech_ConfirmLastName(u8);
static void Task_UrielSpeech_CreateLastNameYesNo(u8);
static void Task_UrielSpeech_ProcessLastNameYesNoMenu(u8);
static void Task_UrielSpeech_SlidePlatformAway2(u8);
static void Task_UrielSpeech_ReshowUriel(u8);
static void Task_UrielSpeech_NiceToMeetYou(u8);
static void Task_UrielSpeech_CloseMsgbox(u8);
static void Task_UrielSpeech_FadeAwayEverything(u8);
static void Task_UrielSpeech_Cleanup(u8);

// Helper Functions
static void UrielSpeech_DrawCharacterMugshot(u8);
static inline void UrielSpeech_PrintMessageBox(const u8 *);
static void UrielSpeech_CreateMonSprite(void);
static void UrielSpeech_CreateUrielSprite(void);
static void UrielSpeech_CreatePlatformSprite(void);
static void UrielSpeech_CreatePlayerSprites(void);
static void Task_UrielSpeech_FadeOut(u8);
static void Task_UrielSpeech_FadeIn(u8);
static void UrielSpeech_BeginFade(u8, u8, u8);
static void UrielSpeech_SetDefaultName(u8);
static void CB2_UrielSpeech_ReturnFromNamingScreen(void);
static void UrielSpeech_SetDefaultLastName(u8);
static void CB2_UrielSpeech_ReturnFromNamingScreen2(void);
static void WindowFunc_DrawStandardFrame(u8 bg, u8 tilemapLeft, u8 tilemapTop, u8 width, u8 height, u8 paletteNum);

// Debug Functions
// static void DebugPrintOnScreen(const char *str);
// static void DebugPrintHexPointerWithPrefix(const char *prefix, const void *ptr);
// static void AsciiToGameText(const char *ascii, u8 *dest);
// static void Debug_SetMainCallback2(MainCallback callback);
// static void DebugPrintPointer(const u8 *label, void *ptr);
// static void DebugPrintU8(const u8 *label, u8 value);



// Const data
extern const struct SpriteTemplate sSpriteTemplate_NewGamePlatformLeft;
extern const struct SpriteTemplate sSpriteTemplate_NewGamePlatformRight;

static const u8 *const sMalePresetNames[] = {
    COMPOUND_STRING("Jacob"),
    COMPOUND_STRING("Joshua"),
    COMPOUND_STRING("Daniel"),
    COMPOUND_STRING("Andrew"),
    COMPOUND_STRING("Ethan"),
    COMPOUND_STRING("Dylan"),
    COMPOUND_STRING("Elijah"),
    COMPOUND_STRING("Caleb")
};

static const u8 *const sFemalePresetNames[] = {
    COMPOUND_STRING("Rachel"),
    COMPOUND_STRING("Sydney"),
    COMPOUND_STRING("Emily"),
    COMPOUND_STRING("Eliza"),
    COMPOUND_STRING("Grace"),
    COMPOUND_STRING("Ava"),
    COMPOUND_STRING("Allison"),
    COMPOUND_STRING("Zoey")
};

static const u8 *const sNonbinaryPresetNames[] = {
    COMPOUND_STRING("Alex"),
    COMPOUND_STRING("Rowan"),
    COMPOUND_STRING("River"),
    COMPOUND_STRING("Avery"),
    COMPOUND_STRING("Skylar"),
    COMPOUND_STRING("Parker"),
    COMPOUND_STRING("Briar"),
    COMPOUND_STRING("Taylor")
};

static const u8 *const sPresetLastNames[] = {
    COMPOUND_STRING("Jones"),
    COMPOUND_STRING("Brown"),
    COMPOUND_STRING("Johnson"),
    COMPOUND_STRING("Miller"),
    COMPOUND_STRING("Davis"),
    COMPOUND_STRING("Wilson"),
    COMPOUND_STRING("Moore"),
    COMPOUND_STRING("Jackson")
};

static const u8 sUrielSpeech_Boy[] = _("BOY");
static const u8 sUrielSpeech_Girl[] = _("GIRL");
static const u8 sUrielSpeech_Nonbinary[] = _("NON-BINARY");

static const struct MenuAction sMenuActions_GenderSelect[] =
{
    { sUrielSpeech_Boy,       { .void_u8 = NULL } },
    { sUrielSpeech_Girl,      { .void_u8 = NULL } },
    { sUrielSpeech_Nonbinary, { .void_u8 = NULL } },
};

static const u8 sUrielSpeech_Welcome[] = _(
    "Hello. My name is Uriel Dawnsinger.\p"
	"I am the headmaster of the prestigious\n"
	"Kingsisle Institute.\p"
);
 
static const u8 sUrielSpeech_Acceptance[] = _(
    "Please allow me to offer you this letter\n"
	"of acceptance for our upcoming fall\l"
    "term.\p"
);

static const u8 sUrielSpeech_ThisIs[] = _(
    "The world of the Institute, known as\n"
    "the Underground, is inhabited by\l"
	"creatures known as Pokémon.\p"
    "Let me show you what we call a\n" 
    "Pokémon.\p"
);

static const u8 sUrielSpeech_AlakazamAPokemon[] = _(
    "This Alakazam is my personal partner\n"
    "Pokémon.\p"
);

static const u8 sUrielSpeech_MainSpeech[] = _(
    "When the Gods brought us to this world,\n"
	"they also trusted us with caring for\p"
	"its creatures. The Underground is a\n"
	"place of various cultures and species,\p"
	"but caring for Pokémon is something we\n"
	"all have in common.\p"
	"While we live alongside Pokémon, there\n"
	"is still much we do not know about them.\p"
	"This is why the Kingsisle Institute was\n"
	"founded: to unravel the mysteries\l"
	"surrounding Pokémon.\p"
);

static const u8 sUrielSpeech_Registration[] = _(
    "Now, let's get your papers in order.\p"
);

static const u8 sUrielSpeech_GenderSelect[] = _(
	"How do you identify?\p"
);

static const u8 sUrielSpeech_HowDoYouLook[] = _(
    "For the purposes of your ID card,\n"
    "how do you look?\p"
);

static const u8 sUrielSpeech_AskPlayerName[] = _(
    "And your first name?\p"
);

static const u8 sUrielSpeech_ConfirmFirstName[] = _(
    "So it's {PLAYER}?\p"
);

static const u8 sUrielSpeech_AskPlayerLastName[] = _(
    "All right. What about your last name?\p"
);

static const u8 sUrielSpeech_ConfirmPlayerLastName[] = _(
    "{PLAYER_LAST_NAME}, is it?\p"
);

static const u8 sUrielSpeech_NiceToMeetYou[] = _(
    "Nice to meet you, {PLAYER} {PLAYER_LAST_NAME}.\n"
    "There's a lot to prepare before your\l"
	"first day, so how about we get going?\p"
	"I'll be expecting you later. Come see me\n"
	"once you've settled in.\p"
);

static const u16 sUrielSpeech_BgGfx[] = INCBIN_U16("graphics/uriel_speech/bg.4bpp");
static const u16 sUrielSpeech_BgPal[] = INCBIN_U16("graphics/uriel_speech/bg.gbapal");
static const u32 sUrielSpeech_BgMap[] = INCBIN_U32("graphics/uriel_speech/bg.bin.smolTM");

static const u16 sUrielSpeech_UrielPicGfx[] = INCBIN_U16("graphics/uriel_speech/pics/uriel.4bpp");
static const u16 sUrielSpeech_UrielPicPal[] = INCBIN_U16("graphics/uriel_speech/pics/uriel.gbapal");
static const u32 sUrielSpeech_UrielPicMap[] = INCBIN_U32("graphics/uriel_speech/pics/uriel.bin.smolTM");

static const struct BgTemplate sUrielSpeech_BgTemplates[BG_COUNT] =
{
    [BG_TEXT] = {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 0,
        // other unspecified attributes defaults to 0
    },
    [BG_MUGSHOT_1] = {
        .bg = 1,
        .charBaseIndex = 2,
        .mapBaseIndex = 30,
        .priority = 1,
    },
    [BG_MUGSHOT_2] = {
        .bg = 2,
        .charBaseIndex = 2,
        .mapBaseIndex = 28,
        .priority = 2,
    },
    // [BG_MUGSHOT_3] = {
    //     .bg = 2,
    //     .charBaseIndex = 2,
    //     .mapBaseIndex = 26,
    //     .priority = 2,
    // },
    [BG_INTRO] = {
        .bg = 3,
        .charBaseIndex = 3,
        .mapBaseIndex = 25,
        .priority = 3,
    },
};

static const struct WindowTemplate sUrielSpeech_WindowTemplates[] =
{
    [WIN_TEXT] =
    {
        .bg = BG_TEXT,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x1,
    },
    DUMMY_WIN_TEMPLATE,
};

static const struct WindowTemplate sUrielSpeech_YesNoWindow =
{
    .bg = BG_TEXT,
    .tilemapLeft = 21,
    .tilemapTop = 9,
    .width = 5,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = (26*4)+1,
};

static const struct WindowTemplate sUrielSpeech_GenderWindow =
{
    .bg = BG_TEXT,
    .tilemapLeft = 4,
    .tilemapTop = 5,
    .width = 9,
    .height = 6,
    .paletteNum = 15,
    .baseBlock = (26*4)+2,
};

// Code
void CB2_UrielSpeech(void)
{
    RunTasks();
    RunTextPrinters();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

void VBlankCB_UrielSpeech(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void DoUrielSpeech(void)
{
    CreateTask(Task_UrielSpeech_Begin, 0);
    SetMainCallback2(CB2_UrielSpeech);
}

static void Task_UrielSpeech_Begin(u8 taskId)
{
    switch(gMain.state)
    {
        case STATE_RESET:
            // DebugPrintOnScreen("STATE RESET");
            SetVBlankCallback(NULL);
            SetHBlankCallback(NULL);
            DmaFill16(3, 0, VRAM, VRAM_SIZE);
            ResetPaletteFade();
            ScanlineEffect_Stop();
            ResetSpriteData();
            FreeAllSpritePalettes();
            ResetTempTileDataBuffers(); 
            break;
        case STATE_ALLOC:
            // DebugPrintOnScreen("STATE ALLOC");
            sUrielSpeech = AllocZeroed(sizeof(*sUrielSpeech));
            // if (!sUrielSpeech)
            // {
            //     DebugPrintOnScreen("ALLOC FAILED");
            // }
            // DebugPrintOnScreen("ALLOC OK");
            break;
        case STATE_REGS:
            // DebugPrintOnScreen("STATE REGS");
            SetGpuReg(REG_OFFSET_WIN0H, 0);
            SetGpuReg(REG_OFFSET_WIN0V, 0);
            SetGpuReg(REG_OFFSET_WIN1H, 0);
            SetGpuReg(REG_OFFSET_WIN1V, 0);
            SetGpuReg(REG_OFFSET_WININ, 0);
            SetGpuReg(REG_OFFSET_WINOUT, 0);
            SetGpuReg(REG_OFFSET_BLDCNT, 0);
            SetGpuReg(REG_OFFSET_BLDALPHA, 0);
            SetGpuReg(REG_OFFSET_BLDY, 0);
            SetGpuReg(REG_OFFSET_DISPCNT, 0);
            // DebugPrintOnScreen("STATE REGS COMPLETE");
            break;
        case STATE_BGS:
            // DebugPrintOnScreen("STATE_BGS");
            ResetBgsAndClearDma3BusyFlags(0);
            InitBgsFromTemplates(0, sUrielSpeech_BgTemplates, ARRAY_COUNT(sUrielSpeech_BgTemplates));
            SetBgTilemapBuffer(BG_INTRO, sUrielSpeech->introTilemapBuffer);
            SetBgTilemapBuffer(BG_MUGSHOT_1, sUrielSpeech->pic1TilemapBuffer);
            SetBgTilemapBuffer(BG_MUGSHOT_2, sUrielSpeech->pic2TilemapBuffer);
            // SetBgTilemapBuffer(BG_MUGSHOT_3, sUrielSpeech->pic3TilemapBuffer);
            ResetBgPositions();
            break;
        case STATE_BG_GFX:
            // DebugPrintOnScreen("STATE BG GFX");
            UrielSpeech_CreateMonSprite();
            UrielSpeech_CreateUrielSprite();
            UrielSpeech_CreatePlatformSprite();
            UrielSpeech_CreatePlayerSprites();
            LoadPalette(sUrielSpeech_BgPal, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
            LoadBgTiles(BG_INTRO, sUrielSpeech_BgGfx, sizeof(sUrielSpeech_BgGfx), 0);
            CopyToBgTilemapBuffer(BG_INTRO, sUrielSpeech_BgMap, 0, 0); 
            CopyBgTilemapBufferToVram(BG_INTRO);
            // UrielSpeech_DrawCharacterMugshot(MUGSHOT_URIEL);
            break;
        case STATE_WINDOWS:
            // DebugPrintOnScreen("STATE WINDOWS");
            InitWindows(sUrielSpeech_WindowTemplates);
            InitTextBoxGfxAndPrinters();
            Menu_LoadStdPalAt(BG_PLTT_ID(13));
            DrawDialogueFrame(WIN_TEXT, TRUE);
            BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
            break;
        case STATE_FINISH:
            // DebugPrintOnScreen("STATE FINISH");
            BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
            SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
            SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG1 | BLDCNT_TGT1_BG2 | BLDCNT_TGT1_OBJ | BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND);
            SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 16));
            SetGpuReg(REG_OFFSET_BLDY, 0);
            ShowBg(BG_INTRO);
            ShowBg(BG_MUGSHOT_1);
            ShowBg(BG_MUGSHOT_2);
            // ShowBg(BG_MUGSHOT_3);
            ShowBg(BG_TEXT);
            SetVBlankCallback(VBlankCB_UrielSpeech);
            PlayBGM(MUS_GSC_ROUTE38);
            gTasks[taskId].func = Task_UrielSpeech_FadeInEverything;
            gMain.state = 0;
            return;
    }
    DebugPrintf("state: %d", gMain.state);
    gMain.state++;
}

static void Task_UrielSpeech_FadeInEverything(u8 taskId)
{
    u32 spriteId;

    if (!gPaletteFade.active)
    {
        sUrielSpeech->timer = 30;
        UrielSpeech_BeginFade(FALSE, 0, SPRITE_TYPE_NONE);
        spriteId = sUrielSpeech->urielSpriteId;
        gSprites[spriteId].x = 136;
        gSprites[spriteId].y = 60;
        gSprites[spriteId].invisible = FALSE;
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_BLEND;
        spriteId = sUrielSpeech->platformSpriteIdLeft;
        gSprites[spriteId].x = 90;
        gSprites[spriteId].y = 95;
        gSprites[spriteId].invisible = FALSE;
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_BLEND;
        spriteId = sUrielSpeech->platformSpriteIdRight;
        gSprites[spriteId].x = 154;
        gSprites[spriteId].y = 95;
        gSprites[spriteId].invisible = FALSE;
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_BLEND;
        gTasks[taskId].func = Task_UrielSpeech_Welcome;
    }
}

static void Task_UrielSpeech_Welcome(u8 taskId)
{
    if (sUrielSpeech->fadeFinished)
    {
        if (sUrielSpeech->timer)
        {
            sUrielSpeech->timer--;
            return;
        }
        
        UrielSpeech_PrintMessageBox(sUrielSpeech_Welcome);
        gTasks[taskId].func = Task_UrielSpeech_Acceptance;
    }
}

static void Task_UrielSpeech_Acceptance(u8 taskId)
{
    if (!IsTextPrinterActive(WIN_TEXT))
    {
        UrielSpeech_PrintMessageBox(sUrielSpeech_Acceptance);
        gTasks[taskId].func = Task_UrielSpeech_ThisIs;
    }
}

static void Task_UrielSpeech_ThisIs(u8 taskId)
{
    if (!IsTextPrinterActive(WIN_TEXT))
    {
        UrielSpeech_PrintMessageBox(sUrielSpeech_ThisIs);
        sUrielSpeech->timer = 30;
        gTasks[taskId].func = Task_UrielSpeech_ReleaseAlakazamFromPokeball;
    }
}

static void Task_UrielSpeech_ReleaseAlakazamFromPokeball(u8 taskId)
{
    u32 spriteId;
    if (!IsTextPrinterActive(WIN_TEXT))
    {
        if (sUrielSpeech->timer)
        {
            sUrielSpeech->timer--;
            return;
        }

        spriteId = sUrielSpeech->monSpriteId;
        gSprites[spriteId].invisible = FALSE;
        CreatePokeballSpriteToReleaseMon(spriteId, gSprites[spriteId].oam.paletteNum, 112, 58, 0, 0, 32, 0x00007FFF, SPECIES_ALAKAZAM);
        gTasks[taskId].func = Task_UrielSpeech_AlakazamAPokemon;
        sUrielSpeech->timer = 0;
    }
}

static void Task_UrielSpeech_AlakazamAPokemon(u8 taskId)
{
   sUrielSpeech->timer++;
   if (IsCryFinished())
    {
        if (sUrielSpeech->timer >= 192)
        {
            UrielSpeech_PrintMessageBox(sUrielSpeech_AlakazamAPokemon);
            gTasks[taskId].func = Task_UrielSpeech_MainSpeech;
        }
   }
}

static void Task_UrielSpeech_MainSpeech(u8 taskId)
{
    if (!IsTextPrinterActive(WIN_TEXT))
    {
        UrielSpeech_PrintMessageBox(sUrielSpeech_MainSpeech);
        gTasks[taskId].func = Task_UrielSpeech_Registration;
    }
}

static void Task_UrielSpeech_Registration(u8 taskId)
{
    if (!IsTextPrinterActive(WIN_TEXT))
    {
        UrielSpeech_PrintMessageBox(sUrielSpeech_Registration);
        gTasks[taskId].func = Task_UrielSpeech_PlatformFade;
    }
}

static void Task_UrielSpeech_PlatformFade(u8 taskId)
{

    if(!IsTextPrinterActive(WIN_TEXT))
    {
        // make the sprites fade out somehow
        gSprites[sUrielSpeech->platformSpriteIdLeft].oam.priority  = 1;
        gSprites[sUrielSpeech->platformSpriteIdRight].oam.priority = 1;
        // Uriel and mon in front
        gSprites[sUrielSpeech->urielSpriteId].oam.priority = 0;
        gSprites[sUrielSpeech->monSpriteId].oam.priority   = 0;

        // Setup blending: fade OBJ (sprites) into BG
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_OBJ | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ | BLDCNT_EFFECT_BLEND);

        // Initial coefficients: fully visible OBJ
        sUrielSpeech->alphaCoeff = 16;
        sUrielSpeech->alphaCoeff2 = 0;
        sUrielSpeech->fadeTimer = 0;
        SetGpuReg(REG_OFFSET_BLDALPHA, (sUrielSpeech->alphaCoeff2 << 8) | sUrielSpeech->alphaCoeff);
        SetGpuReg(REG_OFFSET_BLDY, 0);

        gSprites[sUrielSpeech->urielSpriteId].oam.objMode = ST_OAM_OBJ_BLEND;
        gSprites[sUrielSpeech->monSpriteId].oam.objMode   = ST_OAM_OBJ_BLEND;
        
        gTasks[CreateTask(Task_UrielSpeech_FadeOut, 0)];
        
        sUrielSpeech->timer = 64;
        gTasks[taskId].func = Task_UrielSpeech_SlidePlatformAway;
    }
}

static void Task_UrielSpeech_SlidePlatformAway(u8 taskId)
{
    // Convenience aliases for readability
    u8 leftId  = sUrielSpeech->platformSpriteIdLeft;
    u8 rightId = sUrielSpeech->platformSpriteIdRight;

    // Move both halves left until the left half’s x <= -100
    if (gSprites[leftId].x > -100)
    {
        gSprites[leftId].x  -= 2;
        gSprites[rightId].x -= 2;
    }
    else
    {
        // Clamp to final position
        gSprites[leftId].x  = -100;
        gSprites[rightId].x = gSprites[leftId].x + 64; // keep them aligned

        // Switch to next task phase
        gTasks[taskId].func = Task_UrielSpeech_StartPlayerFadeIn;
    }
}

static void Task_UrielSpeech_StartPlayerFadeIn(u8 taskId)
{
    // fade in platform and male player sprite
    u32 spriteId;

    if (sUrielSpeech->fadeFinished)
    {
        spriteId = sUrielSpeech->urielSpriteId;
        gSprites[spriteId].invisible = TRUE;
        spriteId = sUrielSpeech->monSpriteId;
        gSprites[spriteId].invisible = TRUE;
        
        if (sUrielSpeech->timer)
        {
            sUrielSpeech->timer--;
        }
        else
        {
            SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_OBJ | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ | BLDCNT_EFFECT_BLEND);
            sUrielSpeech->alphaCoeff  = 0;   // target1 (player) starts invisible
            sUrielSpeech->alphaCoeff2 = 16;  // target2 (background/platform) fully visible
            sUrielSpeech->fadeTimer   = 0;
            SetGpuReg(REG_OFFSET_BLDALPHA, (sUrielSpeech->alphaCoeff2 << 8) | sUrielSpeech->alphaCoeff);
            SetGpuReg(REG_OFFSET_BLDY, 0);
            gTasks[CreateTask(Task_UrielSpeech_FadeIn, 0)];
            spriteId = sUrielSpeech->maleStudentSpriteId;
            gSprites[spriteId].x = 180;
            gSprites[spriteId].y = 60;
            gSprites[spriteId].invisible = FALSE;
            gSprites[spriteId].oam.objMode = ST_OAM_OBJ_BLEND;
            gTasks[taskId].tPlayerSpriteId = spriteId;
            gTasks[taskId].tPlayerGender = MALE;
            spriteId = sUrielSpeech->platformSpriteIdLeft;
            gSprites[spriteId].x = 155;
            gSprites[spriteId].y = 95;
            gSprites[spriteId].invisible = FALSE;
            gSprites[spriteId].oam.objMode = ST_OAM_OBJ_BLEND;
            spriteId = sUrielSpeech->platformSpriteIdRight;
            gSprites[spriteId].x = 200;
            gSprites[spriteId].y = 95;
            gSprites[spriteId].invisible = FALSE;
            gSprites[spriteId].oam.objMode = ST_OAM_OBJ_BLEND;
            
            gTasks[taskId].func = Task_UrielSpeech_GenderSelect;
        }
    }
}

static void Task_UrielSpeech_GenderSelect(u8 taskId)
{
    UrielSpeech_PrintMessageBox(sUrielSpeech_GenderSelect);
    gTasks[taskId].func = Task_UrielSpeech_WaitToShowGenderMenu;
}

static void Task_UrielSpeech_WaitToShowGenderMenu(u8 taskId)
{
    if(!IsTextPrinterActive(WIN_TEXT))
    {
        UrielSpeech_ShowGenderMenu(taskId);
    }
}

static void UrielSpeech_ShowGenderMenu(u8 taskId)
{
    u8 windowId;

    // Create window
    windowId = AddWindow(&sUrielSpeech_GenderWindow);
    gTasks[taskId].tWindowId = windowId;

    // Draw frame around it
    DrawStdWindowFrame(windowId, FALSE);

    // Print options
    AddTextPrinterParameterized(windowId, 1, sUrielSpeech_Boy,        8, 1, TEXT_SKIP_DRAW, NULL);
    AddTextPrinterParameterized(windowId, 1, sUrielSpeech_Girl,       8, 17, TEXT_SKIP_DRAW, NULL);
    AddTextPrinterParameterized(windowId, 1, sUrielSpeech_Nonbinary,  8, 33, TEXT_SKIP_DRAW, NULL);

    // Initialize cursor
    InitMenuInUpperLeftCorner(windowId, 3, 0, TRUE);

    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);

    gTasks[taskId].func = Task_UrielSpeech_ChooseGender;

}

static void Task_UrielSpeech_ChooseGender(u8 taskId)
{
    int gender = UrielSpeech_ProcessGenderMenuInput();

    // Handle confirmation (A press)
    if (gender == MALE || gender == FEMALE || gender == NONBINARY)
    {
        PlaySE(SE_SELECT);
        gSaveBlock2Ptr->playerGender = gender;
        gTasks[taskId].func = Task_UrielSpeech_YourName;
        return;
    }
    // Handle cursor movement → sprite swap
    Task_UrielSpeech_SwitchGenderSprite(taskId);
}

static void Task_UrielSpeech_SwitchGenderSprite(u8 taskId)
{
    u8 cursorPos = Menu_GetCursorPos();
    u8 oldSpriteId = gTasks[taskId].tPlayerSpriteId;
    u8 newSpriteId = SPRITE_NONE;

    // Determine which sprite to show based on cursor
    switch (cursorPos)
    {
        case 0: newSpriteId = sUrielSpeech->maleStudentSpriteId; break;
        case 1: newSpriteId = sUrielSpeech->femaleStudentSpriteId; break;
        case 2: newSpriteId = sUrielSpeech->enbyStudentSpriteId; break;
        default: newSpriteId = sUrielSpeech->maleStudentSpriteId; break;
    }

    // Safety check: do nothing if the sprite ID is invalid
    if (newSpriteId >= MAX_SPRITES || !gSprites[newSpriteId].inUse)
        return;

    // If the selected sprite is already active, skip
    if (oldSpriteId == newSpriteId)
        return;

    // Fade out old sprite
    gSprites[oldSpriteId].oam.objMode = ST_OAM_OBJ_BLEND;
    gSprites[oldSpriteId].invisible = FALSE;
    sUrielSpeech->alphaCoeff = 16;       // starting alpha
    sUrielSpeech->alphaCoeff2 = 0;
    gTasks[taskId].tIsDoneFadingSprites = 0;
    gTasks[taskId].tNextSpriteId = newSpriteId;

    // Change task to handle slide/fade animation
    gTasks[taskId].func = Task_UrielSpeech_SlideOutOldGenderSprite;
}


static void Task_UrielSpeech_SlideOutOldGenderSprite(u8 taskId)
{
    u8 oldSpriteId = gTasks[taskId].tPlayerSpriteId;
    u8 newSpriteId = gTasks[taskId].tNextSpriteId;

    if (gTasks[taskId].tIsDoneFadingSprites == 0)
    {
        // Slide old sprite out to the right while fading
        gSprites[oldSpriteId].x += 4;
        sUrielSpeech->alphaCoeff--;
        sUrielSpeech->alphaCoeff2++;
        SetGpuReg(REG_OFFSET_BLDALPHA, (sUrielSpeech->alphaCoeff2 << 8) + sUrielSpeech->alphaCoeff);

        if (sUrielSpeech->alphaCoeff == 0)
            gTasks[taskId].tIsDoneFadingSprites = 1;
    }
    else
    {
        // Hide old sprite
        gSprites[oldSpriteId].invisible = TRUE;

        // Show new sprite
        gSprites[newSpriteId].x = DISPLAY_WIDTH;
        gSprites[newSpriteId].y = 60;  // Adjust as needed
        gSprites[newSpriteId].invisible = FALSE;
        gSprites[newSpriteId].oam.objMode = ST_OAM_OBJ_BLEND;

        // Update task to handle sliding new sprite in
        gTasks[taskId].tPlayerSpriteId = newSpriteId;
        gTasks[taskId].func = Task_UrielSpeech_SlideInNewGenderSprite;
    }
}

static void Task_UrielSpeech_SlideInNewGenderSprite(u8 taskId)
{
    u8 spriteId = gTasks[taskId].tPlayerSpriteId;

    // Slide sprite in from right
    if (gSprites[spriteId].x > 180) // target x position
    {
        gSprites[spriteId].x -= 4;

        // Fade in
        if (sUrielSpeech->alphaCoeff < 16)
        {
            sUrielSpeech->alphaCoeff++;
            sUrielSpeech->alphaCoeff2--;
            SetGpuReg(REG_OFFSET_BLDALPHA, (sUrielSpeech->alphaCoeff2 << 8) + sUrielSpeech->alphaCoeff);
        }
    }
    else
    {
        // Snap to final position
        gSprites[spriteId].x = 180;
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_NORMAL; // normal rendering after blend
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0)); // optional: reset alpha

        // Mark fade complete
        gTasks[taskId].tIsDoneFadingSprites = 1;

        // Switch back to normal menu handling or next task
        gTasks[taskId].func = Task_UrielSpeech_ChooseGender;
    }
}

static s8 UrielSpeech_ProcessGenderMenuInput(void)
{
    return Menu_ProcessInputNoWrap();
}

static void Task_UrielSpeech_YourName(u8 taskId)
{
    UrielSpeech_PrintMessageBox(sUrielSpeech_AskPlayerName);
    gTasks[taskId].func = Task_UrielSpeech_WaitForWhatsYourNameToPrint;
}

static void Task_UrielSpeech_WaitForWhatsYourNameToPrint(u8 taskId)
{
    if(!IsTextPrinterActive(WIN_TEXT))
    {
        gTasks[taskId].func = Task_UrielSpeech_WaitPressBeforeNameChoice;
    }
}

static void Task_UrielSpeech_WaitPressBeforeNameChoice(u8 taskId)
{
    if ((JOY_NEW(A_BUTTON)) || (JOY_NEW(B_BUTTON)))
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_UrielSpeech_StartNamingScreen;
    }
}

static void Task_UrielSpeech_StartNamingScreen(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        UrielSpeech_SetDefaultName(Random() % NUM_PRESET_NAMES);
        DoNamingScreen(NAMING_SCREEN_PLAYER, gSaveBlock2Ptr->playerName, 0, 0, 0, CB2_UrielSpeech_ReturnFromNamingScreen);
        FreeAllWindowBuffers();
        DestroyTask(taskId);
    }
}

static void Task_UrielSpeech_ReturnFromNamingScreenShowTextbox(u8 taskId)
{
    gTasks[taskId].func = Task_UrielSpeech_ConfirmFirstName;
}

static void Task_UrielSpeech_ConfirmFirstName(u8 taskId)
{
    UrielSpeech_PrintMessageBox(sUrielSpeech_ConfirmFirstName);
    gTasks[taskId].func = Task_UrielSpeech_CreateFirstNameYesNo;
}

static void Task_UrielSpeech_CreateFirstNameYesNo(u8 taskId)
{
    if(!IsTextPrinterActive(WIN_TEXT))
    {
        CreateYesNoMenuParameterized(5, 3, 0xF3, 0xDF, 2, 15);
        CallWindowFunction(WINDOWID_YES_NO, WindowFunc_DrawStandardFrame);
        CopyWindowToVram(WINDOWID_YES_NO, COPYWIN_FULL);
        gTasks[taskId].func = Task_UrielSpeech_ProcessFirstNameYesNoMenu;
    }
}

static void Task_UrielSpeech_ProcessFirstNameYesNoMenu(u8 taskId)
{
    s32 input = Menu_ProcessInputNoWrapClearOnChoose();

    switch(input)
    {
    case 0: // YES
    {
        PlaySE(SE_SELECT);
        sUrielSpeech->timer = 40;
        
        sUrielSpeech->playerHasName = TRUE;
        gTasks[taskId].func = Task_UrielSpeech_YourLastName;
        
        break;
    }
    case 1: // NO
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        gTasks[taskId].func = Task_UrielSpeech_YourName;
        break;
    }
}

static void Task_UrielSpeech_YourLastName(u8 taskId)
{
    UrielSpeech_PrintMessageBox(sUrielSpeech_AskPlayerLastName);
    gTasks[taskId].func = Task_UrielSpeech_WaitForWhatsYourLastNameToPrint;
}

static void Task_UrielSpeech_WaitForWhatsYourLastNameToPrint(u8 taskId)
{
    if(!IsTextPrinterActive(WIN_TEXT))
    {
        gTasks[taskId].func = Task_UrielSpeech_WaitPressBeforeLastNameChoice;
    }
}

static void Task_UrielSpeech_WaitPressBeforeLastNameChoice(u8 taskId)
{
    if ((JOY_NEW(A_BUTTON)) || (JOY_NEW(B_BUTTON)))
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_UrielSpeech_StartNamingScreen2;
    }
}

static void Task_UrielSpeech_StartNamingScreen2(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        UrielSpeech_SetDefaultLastName(Random() % NUM_PRESET_NAMES);
        DoNamingScreen(NAMING_SCREEN_PLAYER, gSaveBlock2Ptr->playerLastName, 0, 0, 0, CB2_UrielSpeech_ReturnFromNamingScreen2);
        FreeAllWindowBuffers();
        DestroyTask(taskId);
    }
}

static void Task_UrielSpeech_ReturnFromNamingScreen2ShowTextbox(u8 taskId)
{
    gTasks[taskId].func = Task_UrielSpeech_ConfirmLastName;
}

static void Task_UrielSpeech_ConfirmLastName(u8 taskId)
{
    UrielSpeech_PrintMessageBox(sUrielSpeech_ConfirmPlayerLastName);
    gTasks[taskId].func = Task_UrielSpeech_CreateLastNameYesNo;
}

static void Task_UrielSpeech_CreateLastNameYesNo(u8 taskId)
{
    if(!IsTextPrinterActive(WIN_TEXT))
    {
        CreateYesNoMenuParameterized(5, 3, 0xF3, 0xDF, 2, 15);
        CallWindowFunction(WINDOWID_YES_NO, WindowFunc_DrawStandardFrame);
        CopyWindowToVram(WINDOWID_YES_NO, COPYWIN_FULL);
        gTasks[taskId].func = Task_UrielSpeech_ProcessLastNameYesNoMenu;
    }
}

static void Task_UrielSpeech_ProcessLastNameYesNoMenu(u8 taskId)
{
    s32 input = Menu_ProcessInputNoWrapClearOnChoose();

    switch(input)
    {
    case 0: // YES
    {
        PlaySE(SE_SELECT);
        sUrielSpeech->timer = 40;
        
        sUrielSpeech->playerHasLastName = TRUE;
        gTasks[taskId].func = Task_UrielSpeech_SlidePlatformAway2;
        
        break;
    }
    case 1: // NO
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        gTasks[taskId].func = Task_UrielSpeech_YourLastName;
        break;
    }
}

static void Task_UrielSpeech_SlidePlatformAway2(u8 taskId)
{
    // Convenience aliases for readability
    u8 leftId  = sUrielSpeech->platformSpriteIdLeft;
    u8 rightId = sUrielSpeech->platformSpriteIdRight;

    // Move both halves left until the left half’s x <= -100
    if (gSprites[leftId].x > 200)
    {
        gSprites[leftId].x  += 2;
        gSprites[rightId].x += 2;
    }
    else
    {
        // Clamp to final position
        gSprites[leftId].x  = 200;
        gSprites[rightId].x = gSprites[leftId].x + 64; // keep them aligned

        // Switch to next task phase
        gTasks[taskId].func = Task_UrielSpeech_ReshowUriel;
    }
}

static void Task_UrielSpeech_ReshowUriel(u8 taskId)
{
    // reshow uriel, then
    UrielSpeech_BeginFade(FALSE, 0, SPRITE_TYPE_NONE);
    gSprites[sUrielSpeech->maleStudentSpriteId].invisible = TRUE;
    gSprites[sUrielSpeech->femaleStudentSpriteId].invisible = TRUE;
    gSprites[sUrielSpeech->enbyStudentSpriteId].invisible = TRUE;
    gSprites[sUrielSpeech->urielSpriteId].x = 136;
    gSprites[sUrielSpeech->urielSpriteId].y = 60;
    gSprites[sUrielSpeech->urielSpriteId].invisible = FALSE;
    gSprites[sUrielSpeech->urielSpriteId].oam.objMode = ST_OAM_OBJ_BLEND;
    gSprites[sUrielSpeech->platformSpriteIdLeft].x = 90;
    gSprites[sUrielSpeech->platformSpriteIdLeft].y = 95;
    gSprites[sUrielSpeech->platformSpriteIdLeft].invisible = FALSE;
    gSprites[sUrielSpeech->platformSpriteIdLeft].oam.objMode = ST_OAM_OBJ_BLEND;
    gSprites[sUrielSpeech->platformSpriteIdRight].x = 154;
    gSprites[sUrielSpeech->platformSpriteIdRight].y = 95;
    gSprites[sUrielSpeech->platformSpriteIdRight].invisible = FALSE;
    gSprites[sUrielSpeech->platformSpriteIdRight].oam.objMode = ST_OAM_OBJ_BLEND;
    gTasks[taskId].func = Task_UrielSpeech_NiceToMeetYou;
}

static void Task_UrielSpeech_NiceToMeetYou(u8 taskId)
{
    UrielSpeech_PrintMessageBox(sUrielSpeech_NiceToMeetYou);
    gTasks[taskId].func = Task_UrielSpeech_CloseMsgbox;
}

static void Task_UrielSpeech_CloseMsgbox(u8 taskId)
{
    if ((!IsTextPrinterActive(WIN_TEXT)) && (JOY_NEW(A_BUTTON) || JOY_NEW(B_BUTTON)))
    {
        ClearDialogWindowAndFrameToTransparent(WIN_TEXT, TRUE);
        gTasks[taskId].func = Task_UrielSpeech_FadeAwayEverything;
    }
}

static void Task_UrielSpeech_FadeAwayEverything(u8 taskId)
{
    if (sUrielSpeech->timer)
    {
        sUrielSpeech->timer--;
    }
    else
    {
        PlaySE(SE_M_TELEPORT);
        sUrielSpeech->timer = 60;
        BeginNormalPaletteFade(0xEFFFEFFF, 0, 0, 16, RGB_WHITE);
        gTasks[taskId].func = Task_UrielSpeech_Cleanup;
    }
}

static void Task_UrielSpeech_Cleanup(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        if (sUrielSpeech->timer)
        {
            sUrielSpeech->timer--;
        }
        else
        {
            SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
            FreeAllWindowBuffers();
            FREE_AND_SET_NULL(sUrielSpeech);
            SetMainCallback2(CB2_NewGame);
            DestroyTask(taskId);
        }
    }
}

// misc. helper functions

// static void UrielSpeech_DrawCharacterMugshot(u8 id)
// {
//     switch(id)
//     {
//         case MUGSHOT_MALE_STUDENT: // male
//             LoadPalette(sUrielSpeech_PlayerPicPal, BG_PLTT_ID(3), PLTT_SIZE_4BPP);
//             LoadBgTiles(BG_MUGSHOT_2, sUrielSpeech_AkaPicGfx, sizeof(sUrielSpeech_AkaPicGfx), 0);
//             CopyToBgTilemapBufferRect(BG_MUGSHOT_2, sUrielSpeech_AkaPicMap, 14, 0, 9, 13);
//             CopyBgTilemapBufferToVram(BG_MUGSHOT_2);
//             return;
//         case MUGSHOT_FEMALE_STUDENT: // female
//             LoadPalette(sUrielSpeech_PlayerPicPal, BG_PLTT_ID(3), PLTT_SIZE_4BPP);
//             LoadBgTiles(BG_MUGSHOT_1, sUrielSpeech_AoPicGfx, sizeof(sUrielSpeech_AoPicGfx), 0x50);
//             CopyToBgTilemapBufferRect(BG_MUGSHOT_1, sUrielSpeech_AoPicMap, 7, 0, 9, 13);
//             CopyBgTilemapBufferToVram(BG_MUGSHOT_1);
//             return;
//     //    case MUGSHOT_ENBY_STUDENT: // enby
//     //        LoadPalette(sUrielSpeech_PlayerPicPal, BG_PLTT_ID(3), PLTT_SIZE_4BPP);
//     //        LoadBgTiles(BG_MUGSHOT_3, sUrielSpeech_AoPicGfx, sizeof(sUrielSpeech_AoPicGfx), 0x50);
//     //        CopyToBgTilemapBufferRect(BG_MUGSHOT_3, sUrielSpeech_AoPicMap, 7, 0, 9, 13);
//     //        CopyBgTilemapBufferToVram(BG_MUGSHOT_3);
//     //        return;
//         case MUGSHOT_URIEL:
//             LoadPalette(sUrielSpeech_UrielPicPal, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
//             LoadBgTiles(BG_MUGSHOT_1, sUrielSpeech_UrielPicGfx, sizeof(sUrielSpeech_UrielPicGfx), 0);
//             CopyToBgTilemapBuffer(BG_MUGSHOT_1, sUrielSpeech_UrielPicMap, 0, 0);
//             CopyBgTilemapBufferToVram(BG_MUGSHOT_1);
//             return;
//         default:
//             return;
//     }
// }

static inline void UrielSpeech_PrintMessageBox(const u8 *str)
{
    DrawDialogueFrame(WIN_TEXT, FALSE);
    if (str != gStringVar4)
    {
        StringExpandPlaceholders(gStringVar4, str);
        AddTextPrinterParameterized2(WIN_TEXT, FONT_NORMAL, gStringVar4, GetPlayerTextSpeed(), NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);
    }
    else
    {
        AddTextPrinterParameterized2(WIN_TEXT, FONT_NORMAL, str, GetPlayerTextSpeed(), NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);
    }
    CopyWindowToVram(WIN_TEXT, COPYWIN_FULL);
}

static void UrielSpeech_CreateMonSprite(void)
{
    sUrielSpeech->monSpriteId = CreateMonPicSprite_Affine(SPECIES_ALAKAZAM, FALSE, 0, MON_PIC_AFFINE_FRONT, MON_POS_X, MON_POS_Y, 14, TAG_NONE);
    gSprites[sUrielSpeech->monSpriteId].callback = SpriteCallbackDummy;
    gSprites[sUrielSpeech->monSpriteId].oam.priority = 0;
    gSprites[sUrielSpeech->monSpriteId].invisible = TRUE;
}


static void UrielSpeech_CreateUrielSprite(void)
{
    sUrielSpeech->urielSpriteId = AddNewGameUrielObject(0x88, 0x3C, 1);
    gSprites[sUrielSpeech->urielSpriteId].callback = SpriteCallbackDummy;
    gSprites[sUrielSpeech->urielSpriteId].oam.priority = 0;
    gSprites[sUrielSpeech->urielSpriteId].invisible = TRUE;
    
}

static void UrielSpeech_CreatePlatformSprite(void)
{
    // Left half
    sUrielSpeech->platformSpriteIdLeft = AddNewGamePlatformObjectLeft(130, 60, 2);
    gSprites[sUrielSpeech->platformSpriteIdLeft].callback = SpriteCallbackDummy;
    gSprites[sUrielSpeech->platformSpriteIdLeft].oam.priority = 0;
    gSprites[sUrielSpeech->platformSpriteIdLeft].invisible = TRUE;

    // Right half
    sUrielSpeech->platformSpriteIdRight = AddNewGamePlatformObjectRight(194, 60, 2);
    gSprites[sUrielSpeech->platformSpriteIdRight].callback = SpriteCallbackDummy;
    gSprites[sUrielSpeech->platformSpriteIdRight].oam.priority = 0;
    gSprites[sUrielSpeech->platformSpriteIdRight].invisible = TRUE;
}

static void UrielSpeech_CreatePlayerSprites(void)
{
    sUrielSpeech->maleStudentSpriteId = CreateTrainerSprite(FacilityClassToPicIndex(FACILITY_CLASS_BRENDAN), 120, 60, 0, NULL);
    gSprites[sUrielSpeech->maleStudentSpriteId].callback = SpriteCallbackDummy;
    gSprites[sUrielSpeech->maleStudentSpriteId].oam.priority = 0;
    gSprites[sUrielSpeech->maleStudentSpriteId].invisible = TRUE;
    sUrielSpeech->femaleStudentSpriteId = CreateTrainerSprite(FacilityClassToPicIndex(FACILITY_CLASS_MAY), 120, 60, 0, NULL);
    gSprites[sUrielSpeech->femaleStudentSpriteId].callback = SpriteCallbackDummy;
    gSprites[sUrielSpeech->femaleStudentSpriteId].oam.priority = 0;
    gSprites[sUrielSpeech->femaleStudentSpriteId].invisible = TRUE;
    sUrielSpeech->enbyStudentSpriteId = CreateTrainerSprite(FacilityClassToPicIndex(FACILITY_CLASS_WALLY), 120, 60, 0, NULL);
    gSprites[sUrielSpeech->enbyStudentSpriteId].callback = SpriteCallbackDummy;
    gSprites[sUrielSpeech->enbyStudentSpriteId].oam.priority = 0;
    gSprites[sUrielSpeech->enbyStudentSpriteId].invisible = TRUE;

}

static void UrielSpeech_CreatePlayerAppearanceSprites(void)
{

}

#define tSpriteType data[0]

static void Task_UrielSpeech_FadeOut(u8 taskId)
{
    if (sUrielSpeech->alphaCoeff == 0)
    {
        sUrielSpeech->fadeFinished = TRUE;
        DestroyTask(taskId);
    }
    else if (sUrielSpeech->fadeTimer)
    {
        sUrielSpeech->fadeTimer--;
    }
    else
    {
        sUrielSpeech->fadeTimer = 0;
        sUrielSpeech->alphaCoeff--;
        sUrielSpeech->alphaCoeff2++;

        // Update blend
        SetGpuReg(REG_OFFSET_BLDALPHA,
            (sUrielSpeech->alphaCoeff2 << 8) | sUrielSpeech->alphaCoeff);
    }
}

static void Task_UrielSpeech_FadeIn(u8 taskId)
{
    if (sUrielSpeech->alphaCoeff == 16)
    {
        // Done fading in
        sUrielSpeech->fadeFinished = TRUE;
        DestroyTask(taskId);
    }
    else
    {
        if (sUrielSpeech->fadeTimer != 0)
        {
            sUrielSpeech->fadeTimer--;
        }
        else
        {
            sUrielSpeech->fadeTimer = 0;
            sUrielSpeech->alphaCoeff++;   // player gets stronger
            sUrielSpeech->alphaCoeff2--;  // background fades slightly

            SetGpuReg(REG_OFFSET_BLDALPHA,
                (sUrielSpeech->alphaCoeff2 << 8) | sUrielSpeech->alphaCoeff);
        }
    }
}

static void UrielSpeech_BeginFade(u8 fadeOut, u8 delay, u8 spriteType)
{
    u32 taskId;
    u32 bldTarget1, bldTarget2;

    sUrielSpeech->fadeFinished = FALSE;
    if (spriteType == SPRITE_TYPE_MUGSHOT_1 || spriteType == SPRITE_TYPE_MUGSHOT_2) // || spriteType == SPRITE_TYPE_MUGSHOT_3)
    {
        bldTarget1 = fadeOut ? 8 : 0;
        bldTarget2 = fadeOut ? 8 : 16;
    }
    else
    {
        bldTarget1 = fadeOut ? 16 : 0;
        bldTarget2 = fadeOut ? 0 : 16;
    }
    sUrielSpeech->alphaCoeff = bldTarget1;
    sUrielSpeech->alphaCoeff2 = bldTarget2;
    sUrielSpeech->fadeTimer = delay;

    switch(spriteType)
    {
    case SPRITE_TYPE_MUGSHOT_1:
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG1 | BLDCNT_TGT2_OBJ | BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND);
        break;
    case SPRITE_TYPE_MUGSHOT_2:
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG2 | BLDCNT_TGT2_OBJ | BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND);
        break;
//    case SPRITE_TYPE_MUGSHOT_3:
//        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG3 | BLDCNT_TGT2_OBJ | BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND);
//        break;
    case SPRITE_TYPE_NONE:
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG1 | BLDCNT_TGT1_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND);
        break;
    case SPRITE_TYPE_PLAYER:
        switch (gSaveBlock2Ptr->playerGender)
        {
            case MALE:
                gSprites[sUrielSpeech->maleStudentSpriteId].x = 180;
                gSprites[sUrielSpeech->maleStudentSpriteId].y = 60;
                gSprites[sUrielSpeech->maleStudentSpriteId].oam.objMode = ST_OAM_OBJ_BLEND;
                gSprites[sUrielSpeech->maleStudentSpriteId].invisible = FALSE;
                break;
            case FEMALE:
                gSprites[sUrielSpeech->femaleStudentSpriteId].x = 180;
                gSprites[sUrielSpeech->femaleStudentSpriteId].y = 60;
                gSprites[sUrielSpeech->femaleStudentSpriteId].oam.objMode = ST_OAM_OBJ_BLEND;
                gSprites[sUrielSpeech->femaleStudentSpriteId].invisible = FALSE;
                break;
            case NONBINARY:
                gSprites[sUrielSpeech->enbyStudentSpriteId].x = 180;
                gSprites[sUrielSpeech->enbyStudentSpriteId].y = 60;
                gSprites[sUrielSpeech->enbyStudentSpriteId].oam.objMode = ST_OAM_OBJ_BLEND;
                gSprites[sUrielSpeech->enbyStudentSpriteId].invisible = FALSE;
                break;
            default:
                break;
        }
    }

    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(bldTarget1, bldTarget2));
    SetGpuReg(REG_OFFSET_BLDY, 0);

    DebugPrintf("fadeOut: %d", fadeOut);
    taskId = CreateTask(fadeOut ? Task_UrielSpeech_FadeOut : Task_UrielSpeech_FadeIn, 0);
    gTasks[taskId].tSpriteType = spriteType;
}

static void UrielSpeech_SetDefaultName(u8 nameId)
{
    const u8 *name;
    u8 i;

    if (gSaveBlock2Ptr->playerGender == MALE)
        name = sMalePresetNames[nameId];
    else if (gSaveBlock2Ptr->playerGender == FEMALE)
        name = sFemalePresetNames[nameId];
    else 
        name = sNonbinaryPresetNames[nameId];
    for (i = 0; i < PLAYER_NAME_LENGTH; i++)
        gSaveBlock2Ptr->playerName[i] = name[i];
    gSaveBlock2Ptr->playerName[PLAYER_NAME_LENGTH] = EOS;
}

static void UrielSpeech_SetDefaultLastName(u8 nameId)
{
    const u8 *name;
    u8 i;

    name = sPresetLastNames[nameId];

    for (i = 0; i < PLAYER_NAME_LENGTH; i++)
        gSaveBlock2Ptr->playerLastName[i] = name[i];
    gSaveBlock2Ptr->playerLastName[PLAYER_NAME_LENGTH] = EOS;
}

static void CB2_UrielSpeech_ReturnFromNamingScreen(void)
{
    switch(gMain.state)
    {
        case STATE_RESET:
            SetVBlankCallback(NULL);
            SetHBlankCallback(NULL);
            DmaFill16(3, 0, VRAM, VRAM_SIZE);
            ResetPaletteFade();
            ScanlineEffect_Stop();
            ResetSpriteData();
            ResetTasks();
            FreeAllSpritePalettes();
            ResetTempTileDataBuffers();
            break;
        case STATE_ALLOC: // unused here
            break;
        case STATE_REGS:
            SetGpuReg(REG_OFFSET_WIN0H, 0);
            SetGpuReg(REG_OFFSET_WIN0V, 0);
            SetGpuReg(REG_OFFSET_WIN1H, 0);
            SetGpuReg(REG_OFFSET_WIN1V, 0);
            SetGpuReg(REG_OFFSET_WININ, 0);
            SetGpuReg(REG_OFFSET_WINOUT, 0);
            SetGpuReg(REG_OFFSET_BLDCNT, 0);
            SetGpuReg(REG_OFFSET_BLDALPHA, 0);
            SetGpuReg(REG_OFFSET_BLDY, 0);
            SetGpuReg(REG_OFFSET_DISPCNT, 0);
            break;
        case STATE_BGS:
            ResetBgsAndClearDma3BusyFlags(0);
            InitBgsFromTemplates(0, sUrielSpeech_BgTemplates, ARRAY_COUNT(sUrielSpeech_BgTemplates));
            SetBgTilemapBuffer(BG_INTRO, sUrielSpeech->introTilemapBuffer);
            SetBgTilemapBuffer(BG_MUGSHOT_1, sUrielSpeech->pic1TilemapBuffer);
            SetBgTilemapBuffer(BG_MUGSHOT_2, sUrielSpeech->pic2TilemapBuffer);
            ResetBgPositions();
            break;
        case STATE_BG_GFX:
            // DebugPrintOnScreen("STATE BG GFX");
            UrielSpeech_CreateMonSprite();
            UrielSpeech_CreateUrielSprite();
            UrielSpeech_CreatePlatformSprite();
            UrielSpeech_CreatePlayerSprites();
            LoadPalette(sUrielSpeech_BgPal, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
            LoadBgTiles(BG_INTRO, sUrielSpeech_BgGfx, sizeof(sUrielSpeech_BgGfx), 0);
            CopyToBgTilemapBuffer(BG_INTRO, sUrielSpeech_BgMap, 0, 0); 
            CopyBgTilemapBufferToVram(BG_INTRO);
            // UrielSpeech_DrawCharacterMugshot(MUGSHOT_URIEL);
        case STATE_WINDOWS:
            InitWindows(sUrielSpeech_WindowTemplates);
            InitTextBoxGfxAndPrinters();
            Menu_LoadStdPalAt(BG_PLTT_ID(13));
            BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
            break;
        case STATE_FINISH:
            BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
            SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
            
            UrielSpeech_BeginFade(FALSE, 0, SPRITE_TYPE_NONE);
            UrielSpeech_BeginFade(FALSE, 0, SPRITE_TYPE_PLAYER);

            SetGpuReg(REG_OFFSET_BLDY, 0);
            SetGpuReg(REG_OFFSET_BG1HOFS, -60);
            SetGpuReg(REG_OFFSET_BG2HOFS, 0);
            ShowBg(BG_INTRO);
            ShowBg(BG_TEXT);
            
            gSprites[sUrielSpeech->platformSpriteIdLeft].x = 155;
            gSprites[sUrielSpeech->platformSpriteIdLeft].y = 95;
            gSprites[sUrielSpeech->platformSpriteIdLeft].invisible = FALSE;
            gSprites[sUrielSpeech->platformSpriteIdLeft].oam.objMode = ST_OAM_OBJ_BLEND;
            
            gSprites[sUrielSpeech->platformSpriteIdRight].x = 200;
            gSprites[sUrielSpeech->platformSpriteIdRight].y = 95;
            gSprites[sUrielSpeech->platformSpriteIdRight].invisible = FALSE;
            gSprites[sUrielSpeech->platformSpriteIdRight].oam.objMode = ST_OAM_OBJ_BLEND;
            
            SetVBlankCallback(VBlankCB_UrielSpeech);
            SetMainCallback2(CB2_UrielSpeech);
            sUrielSpeech->timer = 30;
            CreateTask(Task_UrielSpeech_ConfirmFirstName, 0);
            gMain.state = 0;
            return;
    }

    DebugPrintf("state: %d", gMain.state);
    gMain.state++;
}

static void CB2_UrielSpeech_ReturnFromNamingScreen2(void)
{
    switch(gMain.state)
    {
        case STATE_RESET:
            SetVBlankCallback(NULL);
            SetHBlankCallback(NULL);
            DmaFill16(3, 0, VRAM, VRAM_SIZE);
            ResetPaletteFade();
            ScanlineEffect_Stop();
            ResetSpriteData();
            ResetTasks();
            FreeAllSpritePalettes();
            ResetTempTileDataBuffers();
            break;
        case STATE_ALLOC: // unused here
            break;
        case STATE_REGS:
            SetGpuReg(REG_OFFSET_WIN0H, 0);
            SetGpuReg(REG_OFFSET_WIN0V, 0);
            SetGpuReg(REG_OFFSET_WIN1H, 0);
            SetGpuReg(REG_OFFSET_WIN1V, 0);
            SetGpuReg(REG_OFFSET_WININ, 0);
            SetGpuReg(REG_OFFSET_WINOUT, 0);
            SetGpuReg(REG_OFFSET_BLDCNT, 0);
            SetGpuReg(REG_OFFSET_BLDALPHA, 0);
            SetGpuReg(REG_OFFSET_BLDY, 0);
            SetGpuReg(REG_OFFSET_DISPCNT, 0);
            break;
        case STATE_BGS:
            ResetBgsAndClearDma3BusyFlags(0);
            InitBgsFromTemplates(0, sUrielSpeech_BgTemplates, ARRAY_COUNT(sUrielSpeech_BgTemplates));
            SetBgTilemapBuffer(BG_INTRO, sUrielSpeech->introTilemapBuffer);
            SetBgTilemapBuffer(BG_MUGSHOT_1, sUrielSpeech->pic1TilemapBuffer);
            SetBgTilemapBuffer(BG_MUGSHOT_2, sUrielSpeech->pic2TilemapBuffer);
            ResetBgPositions();
            break;
        case STATE_BG_GFX:
            // DebugPrintOnScreen("STATE BG GFX");
            UrielSpeech_CreateMonSprite();
            UrielSpeech_CreateUrielSprite();
            UrielSpeech_CreatePlatformSprite();
            UrielSpeech_CreatePlayerSprites();
            LoadPalette(sUrielSpeech_BgPal, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
            LoadBgTiles(BG_INTRO, sUrielSpeech_BgGfx, sizeof(sUrielSpeech_BgGfx), 0);
            CopyToBgTilemapBuffer(BG_INTRO, sUrielSpeech_BgMap, 0, 0); 
            CopyBgTilemapBufferToVram(BG_INTRO);
            // UrielSpeech_DrawCharacterMugshot(MUGSHOT_URIEL);
        case STATE_WINDOWS:
            InitWindows(sUrielSpeech_WindowTemplates);
            InitTextBoxGfxAndPrinters();
            Menu_LoadStdPalAt(BG_PLTT_ID(13));
            BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
            break;
        case STATE_FINISH:
            BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
            SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
            
            UrielSpeech_BeginFade(FALSE, 0, SPRITE_TYPE_NONE);
            UrielSpeech_BeginFade(FALSE, 0, SPRITE_TYPE_PLAYER);

            SetGpuReg(REG_OFFSET_BLDY, 0);
            SetGpuReg(REG_OFFSET_BG1HOFS, -60);
            SetGpuReg(REG_OFFSET_BG2HOFS, 0);
            ShowBg(BG_INTRO);
            ShowBg(BG_TEXT);
            
            gSprites[sUrielSpeech->platformSpriteIdLeft].x = 155;
            gSprites[sUrielSpeech->platformSpriteIdLeft].y = 95;
            gSprites[sUrielSpeech->platformSpriteIdLeft].invisible = FALSE;
            gSprites[sUrielSpeech->platformSpriteIdLeft].oam.objMode = ST_OAM_OBJ_BLEND;
            
            gSprites[sUrielSpeech->platformSpriteIdRight].x = 200;
            gSprites[sUrielSpeech->platformSpriteIdRight].y = 95;
            gSprites[sUrielSpeech->platformSpriteIdRight].invisible = FALSE;
            gSprites[sUrielSpeech->platformSpriteIdRight].oam.objMode = ST_OAM_OBJ_BLEND;
            
            SetVBlankCallback(VBlankCB_UrielSpeech);
            SetMainCallback2(CB2_UrielSpeech);
            sUrielSpeech->timer = 30;
            CreateTask(Task_UrielSpeech_ConfirmLastName, 0);
            gMain.state = 0;
            return;
    }

    DebugPrintf("state: %d", gMain.state);
    gMain.state++;
}

static void WindowFunc_DrawStandardFrame(u8 bg, u8 tilemapLeft, u8 tilemapTop, u8 width, u8 height, u8 paletteNum)
{
    int i;

    FillBgTilemapBufferRect(bg,
                            STD_WINDOW_BASE_TILE_NUM + 0,
                            tilemapLeft - 1,
                            tilemapTop - 1,
                            1,
                            1,
                            STD_WINDOW_PALETTE_NUM);
    FillBgTilemapBufferRect(bg,
                            STD_WINDOW_BASE_TILE_NUM + 1,
                            tilemapLeft,
                            tilemapTop - 1,
                            width,
                            1,
                            STD_WINDOW_PALETTE_NUM);
    FillBgTilemapBufferRect(bg,
                            STD_WINDOW_BASE_TILE_NUM + 2,
                            tilemapLeft + width,
                            tilemapTop - 1,
                            1,
                            1,
                            STD_WINDOW_PALETTE_NUM);

    for (i = tilemapTop; i < tilemapTop + height; i++)
    {
        FillBgTilemapBufferRect(bg,
                                STD_WINDOW_BASE_TILE_NUM + 3,
                                tilemapLeft - 1,
                                i,
                                1,
                                1,
                                STD_WINDOW_PALETTE_NUM);
        FillBgTilemapBufferRect(bg,
                                STD_WINDOW_BASE_TILE_NUM + 5,
                                tilemapLeft + width,
                                i,
                                1,
                                1,
                                STD_WINDOW_PALETTE_NUM);
    }

    FillBgTilemapBufferRect(bg,
                            STD_WINDOW_BASE_TILE_NUM + 6,
                            tilemapLeft - 1,
                            tilemapTop + height,
                            1,
                            1,
                            STD_WINDOW_PALETTE_NUM);
    FillBgTilemapBufferRect(bg,
                            STD_WINDOW_BASE_TILE_NUM + 7,
                            tilemapLeft,
                            tilemapTop + height,
                            width,
                            1,
                            STD_WINDOW_PALETTE_NUM);
    FillBgTilemapBufferRect(bg,
                            STD_WINDOW_BASE_TILE_NUM + 8,
                            tilemapLeft + width,
                            tilemapTop + height,
                            1,
                            1,
                            STD_WINDOW_PALETTE_NUM);
}

// // Debug Functions

// static void DebugPrintOnScreen(const char *str)
// {
//     static u8 converted[64]; // enough for our debug messages
//     sDebugWindowId = 0xFF;

//     if (sDebugWindowId == 0xFF)
//     {
//         struct WindowTemplate template = {
//             .bg = 0,
//             .tilemapLeft = 1,
//             .tilemapTop = 1,
//             .width = 28,
//             .height = 2,
//             .paletteNum = 15,
//             .baseBlock = 1,
//         };
//         sDebugWindowId = AddWindow(&template);
//         PutWindowTilemap(sDebugWindowId);
//         FillWindowPixelBuffer(sDebugWindowId, PIXEL_FILL(0));
//     }

//     FillWindowPixelBuffer(sDebugWindowId, PIXEL_FILL(0));

//     AsciiToGameText(str, converted);
//     AddTextPrinterParameterized(sDebugWindowId, FONT_NORMAL, converted, 0, 0, 0, NULL);

//     CopyWindowToVram(sDebugWindowId, COPYWIN_GFX | COPYWIN_MAP);
// }

// static void DebugPrintHexPointerWithPrefix(const char *prefix, const void *ptr)
// {
//     char buf[20]; // enough for prefix + "0xXXXXXXXX" + null
//     int i = 0;

//     // Copy prefix
//     while (*prefix && i < 8) // limit to 8 chars for safety
//         buf[i++] = *prefix++;

//     // Add "0x"
//     buf[i++] = '0';
//     buf[i++] = 'x';

//     // Convert pointer to 8-digit hex
//     u32 val = (u32)ptr;
//     for (int j = 0; j < 8; j++)
//     {
//         u8 nibble = (val >> ((7 - j) * 4)) & 0xF;
//         if (nibble < 10)
//             buf[i++] = '0' + nibble;
//         else
//             buf[i++] = 'A' + (nibble - 10);
//     }

//     buf[i] = '\0'; // null-terminate
//     DebugPrintOnScreen(buf);
// }

// static void AsciiToGameText(const char *ascii, u8 *dest)
// {
//     while (*ascii)
//     {
//         char c = *ascii++;
//         if (c >= '0' && c <= '9')
//             *dest++ = CHAR_0 + (c - '0');
//         else if (c >= 'A' && c <= 'Z')
//             *dest++ = CHAR_A + (c - 'A');
//         else if (c >= 'a' && c <= 'z')
//             *dest++ = CHAR_a + (c - 'a'); // if lowercase exists
//         else if (c == 'x')
//             *dest++ = CHAR_x; // you’ll need to define CHAR_x in your font table
//         else
//             *dest++ = CHAR_SPACE;
//     }
//     *dest = EOS; // End of string marker
// }

// static void Debug_SetMainCallback2(MainCallback callback)
// {
//     DebugPrintHexPointerWithPrefix("SetMCB2:", callback);
//     SetMainCallback2(callback); // call the real one
// }

// static void DebugPrintPointer(const u8 *label, void *ptr)
// {
//     u8 buf[32];
//     u32 val = (u32)ptr;

//     // Convert pointer to hex string in buf[0..7]
//     for (int i = 0; i < 8; i++)
//     {
//         u8 nibble = (val >> ((7-i)*4)) & 0xF;
//         buf[i] = nibble < 10 ? '0'+nibble : 'A'+(nibble-10);
//     }
//     buf[8] = EOS; // terminate string

//     // Copy label into a separate buffer to avoid overlap
//     u8 final[40];
//     StringCopy(final, label);
//     StringAppend(final, (const u8 *)":0x");
//     StringAppend(final, buf);

//     DebugPrintOnScreen((const char *)final);
// }

// static void DebugPrintU8(const u8 *label, u8 value)
// {
//     static char buf[32]; // ensure big enough
//     int i = 0;

//     // Copy the label (as proper ASCII string)
//     while (*label && i < (int)(sizeof(buf) - 4)) {
//         buf[i++] = *label++;
//     }

//     // Append ":<value>"
//     buf[i++] = ':';
//     buf[i++] = '0' + (value / 10);
//     buf[i++] = '0' + (value % 10);
//     buf[i] = '\0';  // <- CRITICAL: null terminate

//     DebugPrintOnScreen(buf);
// }