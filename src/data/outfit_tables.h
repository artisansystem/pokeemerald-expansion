#include "constants/global.h"
#include "constants/event_objects.h"

#if MODERN == 0
static const u8 sText_OutfitName_UsualGreen[] = _("USUAL GREEN");
static const u8 sText_OutfitDesc_UsualGreen[] = _(
    "The usual, but basic OUTFIT.");
#endif

static const u16 sRegionMapPlayerIcon_BrendanGfx[] = INCBIN_U16("graphics/pokenav/region_map/brendan_icon.4bpp");

static const u16 sRegionMapPlayerIcon_RSBrendanGfx[] = INCBIN_U16("graphics/pokenav/region_map/rs_brendan_icon.4bpp");

static const u16 sRegionMapPlayerIcon_MayGfx[] = INCBIN_U16("graphics/pokenav/region_map/may_icon.4bpp");

static const u16 sRegionMapPlayerIcon_RSMayGfx[] = INCBIN_U16("graphics/pokenav/region_map/rs_may_icon.4bpp");

//! TODO: Should the gfx here be seperated?

static const u8 sFrontierPassPlayerIcons_BrendanMay_Gfx[] = INCBIN_U8("graphics/frontier_pass/map_heads.4bpp");

static const u8 sFrontierPassPlayerIcons_RSBrendanMay_Gfx[] = INCBIN_U8("graphics/frontier_pass/rs_map_heads.4bpp");

#define REGION_MAP_GFX(m, f) { sRegionMapPlayerIcon_ ## m ## Gfx, sRegionMapPlayerIcon_ ## f ## Gfx }

// bandaids to avoid adding unnecessary merge conflicts
// remove these if you have them added/renamed yourself.
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_NORMAL     OBJ_EVENT_GFX_LINK_RS_BRENDAN
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_ACRO_BIKE  OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_SURFING    OBJ_EVENT_GFX_BRENDAN_SURFING
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_UNDERWATER OBJ_EVENT_GFX_BRENDAN_UNDERWATER
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FIELD_MOVE OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FISHING    OBJ_EVENT_GFX_BRENDAN_FISHING
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_WATERING   OBJ_EVENT_GFX_BRENDAN_WATERING
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_DECORATING OBJ_EVENT_GFX_BRENDAN_DECORATING
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FIELD_MOVE OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE

#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_NORMAL     OBJ_EVENT_GFX_LINK_RS_MAY
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_ACRO_BIKE  OBJ_EVENT_GFX_MAY_ACRO_BIKE
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_SURFING    OBJ_EVENT_GFX_MAY_SURFING
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_UNDERWATER OBJ_EVENT_GFX_MAY_UNDERWATER
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_FIELD_MOVE OBJ_EVENT_GFX_MAY_FIELD_MOVE
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_FISHING    OBJ_EVENT_GFX_MAY_FISHING
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_WATERING   OBJ_EVENT_GFX_MAY_WATERING
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_DECORATING OBJ_EVENT_GFX_MAY_DECORATING
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_FIELD_MOVE OBJ_EVENT_GFX_MAY_FIELD_MOVE

const struct Outfit gOutfits[OUTFIT_COUNT] =
{
    [OUTFIT_NONE] = {
        .isHidden = TRUE
    },
    [OUTFIT_USUAL_GREEN] = {
        //! DESC: if sets to TRUE, it will not be shown in the OUTFIT menu if it's locked.
        .isHidden = FALSE,

        //! DESC: prices for purchasing them.
        .prices = { 0, 0 },

        //! agbcc doesnt like COMPOUND_STRING on my end
        //! DESC: outfit's name
        #if MODERN == 1
        .name = COMPOUND_STRING("USUAL GREEN"),
        #else
        .name = sText_OutfitName_UsualGreen,
        #endif

        //! DESC: outfit's description
        #if MODERN == 1
        .desc = COMPOUND_STRING("The usual, but basic OUTFIT."),
        #else
        .desc = sText_OutfitDesc_UsualGreen,
        #endif

        //! DESC: trainer front & back pic index
        //! (see include/constants/trainers.h)
        .trainerPics = {
            [MALE] = {
                [APPEARANCE_LIGHT] =   { TRAINER_PIC_BRENDAN, TRAINER_BACK_PIC_BRENDAN, },
                [APPEARANCE_OLIVE] =   { TRAINER_PIC_BRENDAN, TRAINER_BACK_PIC_BRENDAN, },
                [APPEARANCE_BROWN] =   { TRAINER_PIC_BRENDAN, TRAINER_BACK_PIC_BRENDAN, },
                [APPEARANCE_DARK] =   { TRAINER_PIC_BRENDAN, TRAINER_BACK_PIC_BRENDAN, },
            },
            [FEMALE] = {
                [APPEARANCE_LIGHT] = { TRAINER_PIC_MAY, TRAINER_BACK_PIC_MAY, },
                [APPEARANCE_OLIVE] = { TRAINER_PIC_MAY, TRAINER_BACK_PIC_MAY, },
                [APPEARANCE_BROWN] = { TRAINER_PIC_MAY, TRAINER_BACK_PIC_MAY, },
                [APPEARANCE_DARK] = { TRAINER_PIC_MAY, TRAINER_BACK_PIC_MAY, },
            }, 
            [NONBINARY] = {
                [APPEARANCE_LIGHT] = {TRAINER_PIC_WALLY, TRAINER_BACK_PIC_WALLY, },
                [APPEARANCE_OLIVE] = {TRAINER_PIC_WALLY, TRAINER_BACK_PIC_WALLY, },
                [APPEARANCE_BROWN] = {TRAINER_PIC_WALLY, TRAINER_BACK_PIC_WALLY, },
                [APPEARANCE_DARK] = {TRAINER_PIC_WALLY, TRAINER_BACK_PIC_WALLY, },
            }        
        },

        //! DESC: overworld avatars, consisting of: walking, cycling,
        //! surfing, and underwater. (see include/constants/event_object.h)
        .avatarGfxIds = {
           [MALE] = {
                [APPEARANCE_LIGHT] = {
                    [PLAYER_AVATAR_STATE_NORMAL] =     OBJ_EVENT_GFX_BRENDAN_NORMAL,
                    [PLAYER_AVATAR_STATE_BIKE] =       OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE,
                    [PLAYER_AVATAR_STATE_SURFING] =    OBJ_EVENT_GFX_BRENDAN_SURFING,
                    [PLAYER_AVATAR_STATE_UNDERWATER] = OBJ_EVENT_GFX_BRENDAN_UNDERWATER
                },
                [APPEARANCE_OLIVE] = {
                    [PLAYER_AVATAR_STATE_NORMAL] =     OBJ_EVENT_GFX_BRENDAN_NORMAL,
                    [PLAYER_AVATAR_STATE_BIKE] =       OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE,
                    [PLAYER_AVATAR_STATE_SURFING] =    OBJ_EVENT_GFX_BRENDAN_SURFING,
                    [PLAYER_AVATAR_STATE_UNDERWATER] = OBJ_EVENT_GFX_BRENDAN_UNDERWATER
                },
                [APPEARANCE_BROWN] = {
                    [PLAYER_AVATAR_STATE_NORMAL] =     OBJ_EVENT_GFX_BRENDAN_NORMAL,
                    [PLAYER_AVATAR_STATE_BIKE] =       OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE,
                    [PLAYER_AVATAR_STATE_SURFING] =    OBJ_EVENT_GFX_BRENDAN_SURFING,
                    [PLAYER_AVATAR_STATE_UNDERWATER] = OBJ_EVENT_GFX_BRENDAN_UNDERWATER
                },
                [APPEARANCE_DARK] = {
                    [PLAYER_AVATAR_STATE_NORMAL] =     OBJ_EVENT_GFX_BRENDAN_NORMAL,
                    [PLAYER_AVATAR_STATE_BIKE] =       OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE,
                    [PLAYER_AVATAR_STATE_SURFING] =    OBJ_EVENT_GFX_BRENDAN_SURFING,
                    [PLAYER_AVATAR_STATE_UNDERWATER] = OBJ_EVENT_GFX_BRENDAN_UNDERWATER
                }             
           },
           [FEMALE] = {
                [APPEARANCE_LIGHT] = {
                    [PLAYER_AVATAR_STATE_NORMAL] =     OBJ_EVENT_GFX_MAY_NORMAL,
                    [PLAYER_AVATAR_STATE_BIKE] =       OBJ_EVENT_GFX_MAY_ACRO_BIKE,
                    [PLAYER_AVATAR_STATE_SURFING] =    OBJ_EVENT_GFX_MAY_SURFING,
                    [PLAYER_AVATAR_STATE_UNDERWATER] = OBJ_EVENT_GFX_MAY_UNDERWATER
                },
                [APPEARANCE_OLIVE] = {
                    [PLAYER_AVATAR_STATE_NORMAL] =     OBJ_EVENT_GFX_MAY_NORMAL,
                    [PLAYER_AVATAR_STATE_BIKE] =       OBJ_EVENT_GFX_MAY_ACRO_BIKE,
                    [PLAYER_AVATAR_STATE_SURFING] =    OBJ_EVENT_GFX_MAY_SURFING,
                    [PLAYER_AVATAR_STATE_UNDERWATER] = OBJ_EVENT_GFX_MAY_UNDERWATER
                },
                [APPEARANCE_BROWN] = {
                    [PLAYER_AVATAR_STATE_NORMAL] =     OBJ_EVENT_GFX_MAY_NORMAL,
                    [PLAYER_AVATAR_STATE_BIKE] =       OBJ_EVENT_GFX_MAY_ACRO_BIKE,
                    [PLAYER_AVATAR_STATE_SURFING] =    OBJ_EVENT_GFX_MAY_SURFING,
                    [PLAYER_AVATAR_STATE_UNDERWATER] = OBJ_EVENT_GFX_MAY_UNDERWATER
                },
                [APPEARANCE_DARK] = {
                    [PLAYER_AVATAR_STATE_NORMAL] =     OBJ_EVENT_GFX_MAY_NORMAL,
                    [PLAYER_AVATAR_STATE_BIKE] =       OBJ_EVENT_GFX_MAY_ACRO_BIKE,
                    [PLAYER_AVATAR_STATE_SURFING] =    OBJ_EVENT_GFX_MAY_SURFING,
                    [PLAYER_AVATAR_STATE_UNDERWATER] = OBJ_EVENT_GFX_MAY_UNDERWATER
                }
           },
           [NONBINARY] = {
                [APPEARANCE_LIGHT] = {
                    [PLAYER_AVATAR_STATE_NORMAL] =     OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_STATE_BIKE] =       OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_STATE_SURFING] =    OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_STATE_UNDERWATER] = OBJ_EVENT_GFX_WALLY
                },
                [APPEARANCE_OLIVE] = {
                    [PLAYER_AVATAR_STATE_NORMAL] =     OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_STATE_BIKE] =       OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_STATE_SURFING] =    OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_STATE_UNDERWATER] = OBJ_EVENT_GFX_WALLY
                },
                [APPEARANCE_BROWN] = {
                    [PLAYER_AVATAR_STATE_NORMAL] =     OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_STATE_BIKE] =       OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_STATE_SURFING] =    OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_STATE_UNDERWATER] = OBJ_EVENT_GFX_WALLY
                },
                [APPEARANCE_DARK] = {
                    [PLAYER_AVATAR_STATE_NORMAL] =     OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_STATE_BIKE] =       OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_STATE_SURFING] =    OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_STATE_UNDERWATER] = OBJ_EVENT_GFX_WALLY
                }
            },
        },

        //! DESC: overworld anims, consisting of: field move, fishing,
        //! water, and decorating. (see include/constants/event_object.h)
        .animGfxIds = {
            [MALE] = {
                [APPEARANCE_LIGHT] = {
                    [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE,
                    [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_BRENDAN_FISHING,
                    [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_BRENDAN_WATERING,
                    [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_BRENDAN_DECORATING,
                    [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE
                },
                [APPEARANCE_OLIVE] = {
                    [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE,
                    [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_BRENDAN_FISHING,
                    [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_BRENDAN_WATERING,
                    [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_BRENDAN_DECORATING,
                    [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE
                },
                [APPEARANCE_BROWN] = {
                    [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE,
                    [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_BRENDAN_FISHING,
                    [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_BRENDAN_WATERING,
                    [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_BRENDAN_DECORATING,
                    [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE
                },
                [APPEARANCE_DARK] = {
                    [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE,
                    [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_BRENDAN_FISHING,
                    [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_BRENDAN_WATERING,
                    [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_BRENDAN_DECORATING,
                    [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE
                },
            },
            [FEMALE] = {
                [APPEARANCE_LIGHT] = {
                    [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_MAY_FIELD_MOVE,
                    [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_MAY_FISHING,
                    [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_MAY_WATERING,
                    [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_MAY_DECORATING,
                    [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_MAY_FIELD_MOVE
                },
                [APPEARANCE_OLIVE] = {
                    [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_MAY_FIELD_MOVE,
                    [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_MAY_FISHING,
                    [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_MAY_WATERING,
                    [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_MAY_DECORATING,
                    [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_MAY_FIELD_MOVE
                },
                [APPEARANCE_BROWN] = {
                    [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_MAY_FIELD_MOVE,
                    [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_MAY_FISHING,
                    [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_MAY_WATERING,
                    [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_MAY_DECORATING,
                    [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_MAY_FIELD_MOVE
                },
                [APPEARANCE_DARK] = {
                    [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_MAY_FIELD_MOVE,
                    [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_MAY_FISHING,
                    [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_MAY_WATERING,
                    [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_MAY_DECORATING,
                    [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_MAY_FIELD_MOVE
                },
            },
            [NONBINARY] = {
                [APPEARANCE_LIGHT] = {
                    [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_WALLY
                },
                [APPEARANCE_OLIVE] = {
                    [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_WALLY
                },
                [APPEARANCE_BROWN] = {
                    [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_WALLY
                },
                [APPEARANCE_DARK] = {
                    [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_WALLY,
                    [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_WALLY
                },
            },
      
        },

        //! DESC: head icons gfx&pal for region map
        .iconsRM = {
            [MALE] = {
                [APPEARANCE_LIGHT] = sRegionMapPlayerIcon_BrendanGfx,
                [APPEARANCE_OLIVE] = sRegionMapPlayerIcon_BrendanGfx,
                [APPEARANCE_BROWN] = sRegionMapPlayerIcon_BrendanGfx,
                [APPEARANCE_DARK] = sRegionMapPlayerIcon_BrendanGfx,
            },
            [FEMALE] = {
                [APPEARANCE_LIGHT] = sRegionMapPlayerIcon_MayGfx,
                [APPEARANCE_OLIVE] = sRegionMapPlayerIcon_MayGfx,
                [APPEARANCE_BROWN] = sRegionMapPlayerIcon_MayGfx,
                [APPEARANCE_DARK] = sRegionMapPlayerIcon_MayGfx,
            },
            [NONBINARY] = {
                [APPEARANCE_LIGHT] = sRegionMapPlayerIcon_BrendanGfx,
                [APPEARANCE_OLIVE] = sRegionMapPlayerIcon_BrendanGfx,
                [APPEARANCE_BROWN] = sRegionMapPlayerIcon_BrendanGfx,
                [APPEARANCE_DARK] = sRegionMapPlayerIcon_BrendanGfx,
            },
        },

        //! DESC: head icons gfx&pal for frontier pass
        //! note that frontier pass needs to be in one sprite instead of two,
        //! unlike region map. (probably should split them tbh)
        .iconsFP = sFrontierPassPlayerIcons_BrendanMay_Gfx,
    }
};