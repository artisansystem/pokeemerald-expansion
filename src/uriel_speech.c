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
#include "scanline_effect.h"
#include "sound.h"
#include "strings.h"
#include "trainer_pokemon_sprites.h"
#include "pokeball.h"
#include "naming_screen.h"
#include "overworld.h"
#include "uriel_speech.h"
#include "constants/rgb.h"
#include "constants/songs.h"

/*! @brief
 * This file controls Elder Kaba's speech sequence, made
 * seperately from src/main_menu.c to avoid too big of
 * conflicts and just makes the sequence much cleaner to
 * read.
 *
 * Below is the order of functions that'll run the intro.
 * 
 * DoUrielSpeech
 *      Move the game state into Elder Kaba's Speech.
 * 
 * Task_UrielSpeech_Begin
 *      Basic UI-loading code, so stuff like initializing
 *      registers settings, bgs, windows and sprites goes
 *      here.
 *      There's two functions that do this, but
 *      Task_UrielSpeech_Begin is only for loading
 *      the intro the first time.
 * 
 * Task_UrielSpeech_FadeInEverything
 *      Waits for the palette fading from black
 *      (by Task_UrielSpeech_Begin) to slowly
 *      fades in Kaba's mugshot and the messagebox
 *      Also delays by 30 frames to perfectly
 *      prints sUrielSpeech_Greetings.
 * 
 * Task_UrielSpeech_GreetingsTraveler
 *      Waits for sUrielSpeech_Greetings to be done
 *      printing. When its completely done, it'll
 *      print sUrielSpeech_AndThis and continue to the
 *      next function below.
 * 
 * Task_UrielSpeech_AndThis
 *      Waits for sUrielSpeech_AndThis to be done
 *      printing. When its completely done, it'll
 *      starts the Joltik sequence.
 * 
 * Task_UrielSpeech_ReleaseJoltikFromPokeball
 *      Delay 30 frames before releasing Joltik.
 * 
 * Task_UrielSpeech_JoltikAPokemon
 *      Wait for Joltik's cry finished and delay for
 *      192+ frames. After that, it'll print
 *      sUrielSpeech_JoltikAPokemon and continue on.
 * 
 * Task_UrielSpeech_MainTalk
 *      Waits for sUrielSpeech_JoltikAPokemon to be
 *      done printing. When its completely done,
 *      it'll print sUrielSpeech_MainTalk.
 * 
 * Task_UrielSpeech_ReturnJoltik
 *      Waits for sUrielSpeech_MainTalk to be done
 *      printing, Once its completely done, it'll
 *      begin to do Joltik returning to its
 *      Pokeball's sequence.
 * 
 * Task_UrielSpeech_FadeOutPokeball
 *      Waits for the Joltik returning to its
 *      Pokeball's sequence to be done. Once the
 *      Pokeball sprite has SpriteCallbackDummy as
 *      its sprite callback, begin fading out everything.
 *      (except the background, of course)
 * 
 * Task_UrielSpeech_FadeOutEverything
 *      Waits for sUrielSpeech->fadeFinished to be TRUE.
 *      Once it is TRUE, it'll remove the Joltik and
 *      Pokeball sprites, messagebox and Kaba's mugshot.
 *      It'll also spawn Ao and Aka's mugshots. Everything
 *      currently is faded out at this point aka unseen so
 *      its "safe" to do.
 * 
 * Task_UrielSpeech_FadeInPlayerMugshotChoice
 *      Starts fading in the player gender choice with a
 *      delay of 60 frames. Also sets up delay to 60 frames.
 * 
 * Task_UrielSpeech_SetupPlayerMugshotChoice
 *      Waits for the previous fade to finish with
 *      fadeFinished. Once it is done, it'll first delay
 *      by 60 frames and then prints sUrielSpeech_GenderChoice,
 *      set MUGSHOT_AO as the chosenMugshot and set delay to 30
 *      frames.
 * 
 * Task_UrielSpeech_WaitForPlayerMugshotChoice
 *      Waits for player's input for selecting the gender.
 *      However, it'll first delay by 30 frames prior once.
 *      DPAD_LEFT/RIGHT for selecting between Ao and Aka
 *      (wrapped selection so if you go DPAD_LEFT from Ao,
 *      it'll go to Aka etc), and A_BUTTON to confirm
 *      selection.
 * 
 * Task_UrielSpeech_MoveChosenMugshot
 *      Move and fade away the unchosen mugshot, while also
 *      moving the chosen mugshot to the center of the screen.
 *      After all that cool jazz is done, print
 *      sUrielSpeech_ConfirmChosenGender.
 * 
 * Task_UrielSpeech_SpawnYesNoMenuForPlayerMugshot
 *      Spawns in the Yes/No menu for confirming chosen
 *      gender mugshot, with a delay for 15 frames first.
 *      Also sets sUrielSpeech->playerHasName to FALSE
 *      for "safety".
 * 
 * Task_UrielSpeech_HandleConfirmChosenMugshotInput
 *      Handles the Yes/No menu input. if YES, continue
 *      to naming the player. Otherwise if NO/pressed B,
 *      go back to the choosing gender mugshot sequence.
 * 
 * Task_UrielSpeech_AskForName
 *      Either prints sUrielSpeech_ThisIsChildhoodFriend or
 *      sUrielSpeech_AskPlayerName depending if the player
 *      has already been named or not.
 * 
 * Task_UrielSpeech_MoveMugshotsBack
 *      Similar to Task_UrielSpeech_MoveChosenMugshot, but
 *      it restores back to the original position of the
 *      character's pics for gender selection.
 * 
 * Task_UrielSpeech_WaitBeforeNamingScreen
 *      Waits for the player to press the A/B button. If one
 *      of them pressed, it'll fade the screen to back
 * 
 * Task_UrielSpeech_DoNamingScreen
 *      Waits for the fade to black to be finished to
 *      call the naming screen for either rival or player
 *      depending if the player has a name yet, also sets
 *      a default name for both to avoid having a null name
 *      when the player is not writing anything in the
 *      naming screen. This also destroys the platform
 *      sprites and destroys the entire task.
 * 
 * Task_UrielSpeech_ConfirmChosenName
 *      Returns from the naming screen, print either
 *      sUrielSpeech_SoThisIsRival or sUrielSpeech_SoYourePlayer
 *      depending on who is being named. Also creates the
 *      Yes/No menu again, this time for confirming the
 *      player's name.
 * 
 * Task_UrielSpeech_HandleConfirmNameInput
 *      Handles player's input for confirming the rival/
 *      player's name choice.
 *      If YES, continue to name Rival or finishing both.
 *      Otherwise if NO/B button pressed, do naming
 *      sequence from the start again
 * 
 * Task_UrielSpeech_ConfirmPlayerName
 *      Waits for sUrielSpeech_ConfirmPlayerName to be finished
 *      AND also pressing either the A/B button. If conditions
 *      were met, clear the messagebox and fade out player to
 *      name rival.
 * 
 * Task_UrielSpeech_YourJourneyStartsHere
 *      Delays for 30 frames, and then starts to print
 *      sUrielSpeech_YourJourneyStartsHere.
 * 
 * Task_UrielSpeech_CloseMsgbox
 *      Waits for sUrielSpeech_YourJourneyStartsHere to be
 *      finished AND also pressing either the A/B button. If
 *      conditions were met, clear the messagebox and fade
 *      away.
 * 
 * Task_UrielSpeech_FadeAwayEverything
 *      Waits for 40 frames delay, then fade everything
 *      to black whilst playing SE_EXIT.
 * 
 * Task_UrielSpeech_Cleanup
 *      When the fading is done, waits for 30 frames and
 *      clean up everything and warp to new game to finish
 *      off the intro.
 * 
 * Finally, here is the helper functions.
 * 
 * UrielSpeech_DrawCharacterMugshot (u8 id)
 *      Draws the mugshot of either Kaba, Ao and Aka
 *      depending on the `id` argument.
 *      The way I did them is making them tilemaps.
 * 
 * UrielSpeech_PrintMessageBox (const u8 *str)
 *      Prints a message from `str` to the messagebox's
 *      window (WIN_TEXT) and copy everything to VRAM.
 * 
 * UrielSpeech_CreateMonSprite (void)
 *      Creates a sprite of Joltik and hides it.
 * 
 * UrielSpeech_CreatePlatformSprites (bool32 hide)
 *      Creates a platform consisting of 2 64x32 sprites.
 *      Set `hide` to TRUE to hide these sprites, the reason
 *      is because they can be both visible and invisible.
 * 
 * UrielSpeech_DestroyPlatformSprites (void)
 *      Destroys the platform sprites, and set the spriteIds
 *      to SPRITE_NONE.
 * 
 * UrielSpeech_BeginFade (u8 fadeOut, u8 delay, u8 spriteType)
 *      A basic function taken from FRLG to either fade in or
 *      fade out depending if `fadeOut` is set. It can also
 *      delays for several frames before the fading. `spriteType`
 *      indicates what value to be used for the
 *      REG_OFFSET_BLDCNT register.
 * 
 * UrielSpeech_SetDefaultName
 *      Sets a default name for both Player and Rival.
 *      "Aka" for male, "Ao" for female.
 * 
 * CB2_UrielSpeech_ReturnFromNamingScreen
 *      This basically does what Task_UrielSpeech_Begin did,
 *      but as a callback2 and returns with either Aka/Ao
 *      shown on a platform instead of Kaba.
 * 
 */

// Define, enum, struct definitions

// If you want to edit these sprite pos defines, dont touch the `+ 32`!
// positions for joltik + pokeball
#define MON_POS_X 100 
#define MON_POS_Y 75
// positions for platform (they're split into two sprites!)
#define PLAT_POS_X 56 + 32
#define PLAT_POS_Y 83 + 16
// this is pos difference for the second platform sprite
#define PLAT_POS_X2 64

// bg pos
#define JACOB_MUGSHOT_CENTER_POS 30
#define EMILY_MUGSHOT_CENTER_POS  29
#define BRIAR_MUGSHOT_CENTER_POS  28

#define PLAT_SPRITE_ID_COUNT 2

// tSpriteType, for fade in/out
enum SpriteTypes
{
    SPRITE_TYPE_PLATFORM = 0,
    SPRITE_TYPE_POKE_BALL,
    // these arent technically sprites but close nuff :)
    SPRITE_TYPE_MUGSHOT_1,
    SPRITE_TYPE_MUGSHOT_2,
//    SPRITE_TYPE_MUGSHOT_3,
    // similar to above but not quite
    SPRITE_TYPE_PLAYER,
    SPRITE_TYPE_RIVAL,
    SPRITE_TYPE_NONE,
};

enum SpriteTags
{
    TAG_PLATFORM = 0x9000,
};

enum Bgs
{
    // self explanatory
    BG_TEXT = 0,
    // generic names as their usage is both for
    // kaba and player/rival sprites
    BG_MUGSHOT_1,
    BG_MUGSHOT_2,
//    BG_MUGSHOT_3,
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
//    u16 pic3TilemapBuffer[0x800];
    u8 monSpriteId;
    u8 ballSpriteId;
    u8 platformSpriteIds[PLAT_SPRITE_ID_COUNT]; // the platform is made out of 2 64x32sprites
    s16 alphaCoeff;
    s16 alphaCoeff2;
    s16 timer;
    s16 fadeTimer;
    s16 counter;
    bool32 fadeFinished:1;
    bool32 playerHasName:1;
    u8 chosenMugshot;
};

// EWRAM data
static EWRAM_DATA struct UrielSpeech *sUrielSpeech = NULL;

// Function declarations
static void Task_UrielSpeech_Begin(u8);
static void Task_UrielSpeech_FadeInEverything(u8);
static void Task_UrielSpeech_Welcome(u8);
static void Task_UrielSpeech_ThisIs(u8);
static void Task_UrielSpeech_ReleaseAlakazamFromPokeball(u8);
static void Task_UrielSpeech_AlakazamAPokemon(u8);
static void Task_UrielSpeech_MainSpeech(u8);
static void Task_UrielSpeech_ReturnJoltik(u8);
static void Task_UrielSpeech_FadeOutPokeball(u8);
static void Task_UrielSpeech_FadeOutEverything(u8);
static void Task_UrielSpeech_FadeInPlayerMugshotChoice(u8);
static void Task_UrielSpeech_SetupPlayerMugshotChoice(u8);
static void Task_UrielSpeech_WaitForPlayerMugshotChoice(u8);
static void Task_UrielSpeech_MoveChosenMugshot(u8);
static void Task_UrielSpeech_SpawnYesNoMenuForPlayerMugshot(u8);
static void Task_UrielSpeech_HandleConfirmChosenMugshotInput(u8);
static void Task_UrielSpeech_MoveMugshotsBack(u8);
static void Task_UrielSpeech_AskForName(u8);
static void Task_UrielSpeech_WaitBeforeNamingScreen(u8);
static void Task_UrielSpeech_DoNamingScreen(u8);
static void Task_UrielSpeech_ConfirmChosenName(u8);
static void Task_UrielSpeech_HandleConfirmNameInput(u8);
static void Task_UrielSpeech_ConfirmPlayerName(u8);
static void Task_UrielSpeech_YourJourneyStartsHere(u8);
static void Task_UrielSpeech_CloseMsgbox(u8);
static void Task_UrielSpeech_FadeAwayEverything(u8);
static void Task_UrielSpeech_Cleanup(u8);

static void UrielSpeech_DrawCharacterMugshot(u8);
static inline void UrielSpeech_PrintMessageBox(const u8 *);
static void UrielSpeech_CreateMonSprite(void);
static void UrielSpeech_CreatePlatformSprites(bool32 hide);
static void UrielSpeech_DestroyPlatformSprites(void);
static void UrielSpeech_BeginFade(u8, u8, u8);
static void UrielSpeech_SetDefaultName(void);
static void CB2_UrielSpeech_ReturnFromNamingScreen(void);

// Const data
static const u8 sUrielSpeech_Aka[] = _("Aka");
static const u8 sUrielSpeech_Ao[]  = _("Ao");

static const u8 sUrielSpeech_Welcome[] = _(
    "Hello. My name is Uriel Dawnsinger.\p"
	"I am the headmaster of the prestigious\n"
	"Kingsisle Institute.\n"
	"Please allow me to offer you this letter\n"
	"of acceptance for our upcoming fall term.\p"
);

static const u8 sUrielSpeech_ThisIs[] = _(
    "The world of the Institute is inhabited\n"
	"by creatures known as Pokémon.\p"
    "Let me show you what we call a Pokémon.\p"
);

static const u8 sUrielSpeech_AlakazamAPokemon[] = _(
    "This Alakazam is my personal partner Pokémon.\p"
);

static const u8 sUrielSpeech_MainSpeech[] = _(
    "When the Gods brought us to this world,\n"
	"they also trusted us with caring for its\n"
	"creatures. The Undergound is a place of\l"
	"various cultures and species, but\l"
	"caring for Pokémon is something we all\l"
	"have in common.\p"
	"While we live alongside Pokémon, there\n"
	"is still much we do not know about them.\n"
	"This is why the Kingsisle Institute was\l"
	"founded: to unravel the mysteries\l"
	"surrounding Pokémon.\p"
);

static const u8 sUrielSpeech_Registration[] = _(
    "Now, let's get your papers in order.\p"
	"How do you identify?\p"
);

static const u8 sUrielSpeech_HowDoYouLook[] = _(
    "For the purposes of your ID card,\n"
    "how do you look?\p"
);

static const u8 sUrielSpeech_AskPlayerName[] = _(
    "And your full name?\p"
);

static const u8 sUrielSpeech_NiceToMeetYou[] = _(
    "Nice to meet you, {PLAYER} {PLAYER_LAST_NAME}.\n"
    "There's a lot to prepare before your\n"
	"first day, so how about we get going?\n"
	"I'll be expecting you later. Come see me\l"
	"once you've settled in.\p"
);

static const u16 sUrielSpeech_BgGfx[] = INCBIN_U16("graphics/uriel_speech/bg.4bpp");
static const u16 sUrielSpeech_BgPal[] = INCBIN_U16("graphics/uriel_speech/bg.gbapal");
static const u32 sUrielSpeech_BgMap[] = INCBIN_U32("graphics/uriel_speech/bg.bin");

static const u16 sUrielSpeech_UrielPicGfx[] = INCBIN_U16("graphics/uriel_speech/pics/uriel.4bpp");
static const u16 sUrielSpeech_UrielPicPal[] = INCBIN_U16("graphics/uriel_speech/pics/uriel.gbapal");
static const u32 sUrielSpeech_UrielPicMap[] = INCBIN_U32("graphics/uriel_speech/pics/uriel.bin");

//! NOTE: both aka and ao has the same palette as of writing
static const u16 sUrielSpeech_PlayerPicPal[] = INCBIN_U16("graphics/uriel_speech/pics/ao.gbapal");

static const u16 sUrielSpeech_AkaPicGfx[] = INCBIN_U16("graphics/uriel_speech/pics/aka.4bpp");
static const u8 sUrielSpeech_AkaPicMap[] = INCBIN_U8("graphics/uriel_speech/pics/aka.bin");

static const u16 sUrielSpeech_AoPicGfx[] = INCBIN_U16("graphics/uriel_speech/pics/ao.4bpp");
static const u8 sUrielSpeech_AoPicMap[] = INCBIN_U8("graphics/uriel_speech/pics/ao.bin");

static const u16 sUrielSpeech_PlatformGfx[] = INCBIN_U16("graphics/uriel_speech/platform.4bpp");
static const u16 sUrielSpeech_PlatformPal[] = INCBIN_U16("graphics/uriel_speech/platform.gbapal");

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
//    [BG_MUGSHOT_3] = {
//        .bg = 3,
//        .charBaseIndex = 2,
//        .mapBaseIndex = 26,
//        .priority = 3,
//    },
    [BG_INTRO] = {
        .bg = 3,
        .charBaseIndex = 3,
        .mapBaseIndex = 27,
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

static const struct SpriteSheet sUrielSpeech_PlatformSpriteSheet = 
{
    .data = sUrielSpeech_PlatformGfx,
    .size = 2048, // 64x128/2
    .tag = TAG_PLATFORM,
};

static const struct SpritePalette sUrielSpeech_PlatformSpritePalette =
{
    .data = sUrielSpeech_PlatformPal,
    .tag = TAG_PLATFORM,
};

static const struct OamData sUrielSpeech_PlatformOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 3,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sUrielSpeech_PlatformLeft[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END,
};

static const union AnimCmd sUrielSpeech_PlatformRight[] =
{
    ANIMCMD_FRAME(32, 1),
    ANIMCMD_END,
};

static const union AnimCmd *const sUrielSpeech_PlatformAnims[] =
{
    sUrielSpeech_PlatformLeft,
    sUrielSpeech_PlatformRight
};

static const struct SpriteTemplate sUrielSpeech_PlatformTemplate =
{
    .tileTag = TAG_PLATFORM,
    .paletteTag = TAG_PLATFORM,
    .oam = &sUrielSpeech_PlatformOamData,
    .anims = sUrielSpeech_PlatformAnims,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
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
            sUrielSpeech = AllocZeroed(sizeof(*sUrielSpeech));
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
//            SetBgTilemapBuffer(BG_MUGSHOT_3, sUrielSpeech->pic3TilemapBuffer);
            ResetBgPositions();
            break;
        case STATE_BG_GFX:
            UrielSpeech_CreateMonSprite();
            UrielSpeech_CreatePlatformSprites(TRUE);
            LoadPalette(sUrielSpeech_BgPal, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
            LoadBgTiles(BG_INTRO, sUrielSpeech_BgGfx, sizeof(sUrielSpeech_BgGfx), 0);
            CopyToBgTilemapBuffer(BG_INTRO, sUrielSpeech_BgMap, 0, 0);
            CopyBgTilemapBufferToVram(BG_INTRO);
            UrielSpeech_DrawCharacterMugshot(MUGSHOT_URIEL);
            break;
        case STATE_WINDOWS:
            InitWindows(sUrielSpeech_WindowTemplates);
            InitTextBoxGfxAndPrinters();
            Menu_LoadStdPalAt(BG_PLTT_ID(13));
            DrawDialogueFrame(WIN_TEXT, TRUE);
            BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
            break;
        case STATE_FINISH:
            BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
            SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
            SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG1 | BLDCNT_TGT1_BG2 | BLDCNT_TGT1_OBJ | BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND);
            SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 16));
            SetGpuReg(REG_OFFSET_BLDY, 0);
            ShowBg(BG_INTRO);
            ShowBg(BG_MUGSHOT_1);
            ShowBg(BG_MUGSHOT_2);
//            ShowBg(BG_MUGSHOT_3);
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
    if (!gPaletteFade.active)
    {
        sUrielSpeech->timer = 30;
        UrielSpeech_BeginFade(FALSE, 0xd8, SPRITE_TYPE_NONE);
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
        gTasks[taskId].func = Task_UrielSpeech_ThisIs;
    }
}

static void Task_UrielSpeech_ThisIs(u8 taskId)
{
    if (!IsTextPrinterActive(WIN_TEXT))
    {
        UrielSpeech_PrintMessageBox(sUrielSpeech_ThisIs);
        sUrielSpeech->timer = 60;
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
        CreatePokeballSpriteToReleaseMon(spriteId, gSprites[spriteId].oam.paletteNum, MON_POS_X, MON_POS_Y, 0, 0, 32, 0x00007FFF, SPECIES_ALAKAZAM);
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
        //gTasks[taskId].func = Task_UrielSpeech_ReturnJoltik;
    }
}

// misc. helper functions

static void UrielSpeech_DrawCharacterMugshot(u8 id)
{
    switch(id)
    {
        case MUGSHOT_MALE_STUDENT: // male
            LoadPalette(sUrielSpeech_PlayerPicPal, BG_PLTT_ID(3), PLTT_SIZE_4BPP);
            LoadBgTiles(BG_MUGSHOT_2, sUrielSpeech_AkaPicGfx, sizeof(sUrielSpeech_AkaPicGfx), 0);
            CopyToBgTilemapBufferRect(BG_MUGSHOT_2, sUrielSpeech_AkaPicMap, 14, 0, 9, 13);
            CopyBgTilemapBufferToVram(BG_MUGSHOT_2);
            return;
        case MUGSHOT_FEMALE_STUDENT: // female
            LoadPalette(sUrielSpeech_PlayerPicPal, BG_PLTT_ID(3), PLTT_SIZE_4BPP);
            LoadBgTiles(BG_MUGSHOT_1, sUrielSpeech_AoPicGfx, sizeof(sUrielSpeech_AoPicGfx), 0x50);
            CopyToBgTilemapBufferRect(BG_MUGSHOT_1, sUrielSpeech_AoPicMap, 7, 0, 9, 13);
            CopyBgTilemapBufferToVram(BG_MUGSHOT_1);
            return;
//        case MUGSHOT_ENBY_STUDENT: // enby
//            LoadPalette(sUrielSpeech_PlayerPicPal, BG_PLTT_ID(3), PLTT_SIZE_4BPP);
//            LoadBgTiles(BG_MUGSHOT_3, sUrielSpeech_AoPicGfx, sizeof(sUrielSpeech_AoPicGfx), 0x50);
//            CopyToBgTilemapBufferRect(BG_MUGSHOT_3, sUrielSpeech_AoPicMap, 7, 0, 9, 13);
//            CopyBgTilemapBufferToVram(BG_MUGSHOT_3);
//            return;
        case MUGSHOT_URIEL:
            LoadPalette(sUrielSpeech_UrielPicPal, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
            LoadBgTiles(BG_MUGSHOT_1, sUrielSpeech_UrielPicGfx, sizeof(sUrielSpeech_UrielPicGfx), 0);
            CopyToBgTilemapBuffer(BG_MUGSHOT_1, sUrielSpeech_UrielPicMap, 0, 0);
            CopyBgTilemapBufferToVram(BG_MUGSHOT_1);
            return;
        default:
            return;
    }
}


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

static void UrielSpeech_CreatePlatformSprites(bool32 hide)
{
    u32 leftSpriteId, rightSpriteId;
    LoadSpriteSheet(&sUrielSpeech_PlatformSpriteSheet);
    LoadSpritePalette(&sUrielSpeech_PlatformSpritePalette);
    leftSpriteId = CreateSprite(&sUrielSpeech_PlatformTemplate, PLAT_POS_X, PLAT_POS_Y, 0);
    rightSpriteId = CreateSprite(&sUrielSpeech_PlatformTemplate, PLAT_POS_X, PLAT_POS_Y, 0);
    gSprites[rightSpriteId].x2 = PLAT_POS_X2;
    StartSpriteAnim(&gSprites[leftSpriteId], 0);
    StartSpriteAnim(&gSprites[rightSpriteId], 1);
    gSprites[leftSpriteId].invisible = hide;
    gSprites[rightSpriteId].invisible = hide;
    sUrielSpeech->platformSpriteIds[0] = leftSpriteId;
    sUrielSpeech->platformSpriteIds[1] = rightSpriteId;
}

static void UrielSpeech_DestroyPlatformSprites(void)
{
    DestroySprite(&gSprites[sUrielSpeech->platformSpriteIds[1]]);
    DestroySpriteAndFreeResources(&gSprites[sUrielSpeech->platformSpriteIds[0]]);
    sUrielSpeech->platformSpriteIds[0] = SPRITE_NONE;
    sUrielSpeech->platformSpriteIds[1] = SPRITE_NONE;
}

#define tSpriteType data[0]

static void Task_UrielSpeech_FadeOut(u8 taskId)
{
    u32 i = 0;
    if (sUrielSpeech->alphaCoeff == 0)
    {
        sUrielSpeech->fadeFinished = TRUE;
        switch (gTasks[taskId].tSpriteType)
        {
            case SPRITE_TYPE_PLATFORM:
            {
                for (i = 0; i < PLAT_SPRITE_ID_COUNT; i++)
                    gSprites[sUrielSpeech->platformSpriteIds[i]].invisible = TRUE;
            }
                break;
            case SPRITE_TYPE_POKE_BALL:
                gSprites[sUrielSpeech->ballSpriteId].invisible = TRUE;
                break;
            default:
            case SPRITE_TYPE_NONE:
                break;
        }
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
            sUrielSpeech->alphaCoeff--;
            sUrielSpeech->alphaCoeff2++;
            if (sUrielSpeech->alphaCoeff == 8)
            {
                switch (gTasks[taskId].tSpriteType)
                {
                    case SPRITE_TYPE_PLATFORM:
                    {
                        for (i = 0; i < PLAT_SPRITE_ID_COUNT; i++)
                            gSprites[sUrielSpeech->platformSpriteIds[i]].invisible ^= TRUE;
                    }
                        break;
                    case SPRITE_TYPE_POKE_BALL:
                        gSprites[sUrielSpeech->ballSpriteId].invisible ^= TRUE;
                        break;
                    default:
                    case SPRITE_TYPE_NONE:
                        break;
                }
            }
            SetGpuReg(REG_OFFSET_BLDALPHA, (sUrielSpeech->alphaCoeff2 * 256) + sUrielSpeech->alphaCoeff);
        }
    }
}

static void Task_UrielSpeech_FadeIn(u8 taskId)
{
    u32 i = 0;

    if (sUrielSpeech->alphaCoeff == 16)
    {
        if (!gPaletteFade.active)
        {
            sUrielSpeech->fadeFinished = TRUE;
            DestroyTask(taskId);
        }
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
            sUrielSpeech->alphaCoeff++;
            sUrielSpeech->alphaCoeff2--;
            if (sUrielSpeech->alphaCoeff == 8)
            {
                switch (gTasks[taskId].tSpriteType)
                {
                    case SPRITE_TYPE_PLATFORM:
                    {
                        for (i = 0; i < PLAT_SPRITE_ID_COUNT; i++)
                            gSprites[sUrielSpeech->platformSpriteIds[i]].invisible ^= TRUE;
                    }
                        break;
                    case SPRITE_TYPE_POKE_BALL:
                        gSprites[sUrielSpeech->ballSpriteId].invisible ^= TRUE;
                        break;
                    default:
                    case SPRITE_TYPE_NONE:
                        break;
                }
            }
            SetGpuReg(REG_OFFSET_BLDALPHA, (sUrielSpeech->alphaCoeff2 * 256) + sUrielSpeech->alphaCoeff);
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

//    if (spriteType == SPRITE_TYPE_PLAYER)
//    {
//        spriteType = (sUrielSpeech->chosenMugshot == MUGSHOT_AO) ? SPRITE_TYPE_MUGSHOT_1 : SPRITE_TYPE_MUGSHOT_2;
//    }
//    else if (spriteType == SPRITE_TYPE_RIVAL)
//    {
//        spriteType = (sUrielSpeech->chosenMugshot == MUGSHOT_AO) ? SPRITE_TYPE_MUGSHOT_2 : SPRITE_TYPE_MUGSHOT_1;
//    }

    switch(spriteType)
    {
    case SPRITE_TYPE_PLATFORM:
    case SPRITE_TYPE_POKE_BALL:
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG1 | BLDCNT_TGT1_BG2 | BLDCNT_TGT1_OBJ | BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND);
        break;
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
    default:
        break;
    }

    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(bldTarget1, bldTarget2));
    SetGpuReg(REG_OFFSET_BLDY, 0);

    DebugPrintf("fadeOut: %d", fadeOut);
    taskId = CreateTask(fadeOut ? Task_UrielSpeech_FadeOut : Task_UrielSpeech_FadeIn, 0);
    gTasks[taskId].tSpriteType = spriteType;
}

