#pragma once
#include <string>
#include <vector>
using namespace std;
#define Property_Zero 0
#define Property_NoSeed 1
#define Property_Dropless 2
#define Property_Beta 4
#define Property_Mod 8
#define Property_Chemical 12
#define Property_Untradable 16
#define Property_Wrenchable 32
#define Property_MultiFacing 64
#define Property_Permanent 128
#define Property_AutoPickup 256
#define Property_WorldLock 512
#define Property_NoSelf 1024
#define Property_RandomGrow 2048
#define Property_Public 4096
#define Property_Foreground 8192
enum ClothTypes {
	HAIR,
	SHIRT,
	PANTS,
	FEET,
	FACE,
	HAND,
	BACK,
	MASK,
	NECKLACE,
	ANCES,
	NONE
};
enum BlockTypes
{
	FOREGROUND,
	BACKGROUND,
	CONSUMABLE,
	SEED,
	PAIN_BLOCK,
	BEDROCK,
	MAIN_DOOR,
	SIGN,
	DOOR,
	CLOTHING,
	FIST,
	WRENCH,
	CHECKPOINT,
	LOCK,
	GATEWAY,
	TREASURE,
	WEATHER,
	TRAMPOLINE,
	TOGGLE_FOREGROUND,
	CHEMICAL_COMBINER,
	SWITCH_BLOCK,
	SFX_FOREGROUND,
	RANDOM_BLOCK,
	PORTAL,
	PLATFORM,
	MAILBOX,
	MAGIC_EGG,
	CRYSTAL,
	GEMS,
	DEADLY,
	CHEST,
	FACTION,
	BULLETIN_BOARD,
	BOUNCY,
	ANIM_FOREGROUND,
	COMPONENT,
	SUCKER,
	FISH,
	STEAM,
	GROUND_BLOCK,
	DISPLAY,
	STORAGE,
	VENDING,
	DONATION,
	PHONE,
	SEWINGMACHINE,
	CRIME_VILLAIN,
	PROVIDER,
	UNKNOWN
};
struct ItemDB
{
	bool farmable = false;
	int textureHash = 0;
	int val1;
	int dropChance = 0;
	int seedColor = 0;
	int seedOverlayColor = 0;
	int extraFileHash = 0;
	int audioVolume = 0;
	int effect = 0;
	int id = 0;
	int untradeable = 0;
	int breakHits = 0;
	int actionType = 0;
	int chi = 4;
	int growTime = 0;
	int properties = 0;
	int multiple_sides = 0;
	int spirit = 0;
	int solid = 0;
	int infinitymachine = 0;
	int entrance = 0;
	int timer = 0;
	int trans = 0;
	int charger = 0;
	int magplant = 0;
	int item_sucker = 0;
	int mag_multiple = 0;
	int can_be_changed_to_public = 0;
	int can_be_changed_two_types = 0;
	int toggleable = 0;
	int trickster = 0;
	char seedBase = 0;
	char seedOverlay = 0;
	char treeBase = 0;
	char treeLeaves = 0;
	char editableType = 0;
	char hitSoundType = 0;
	char itemCategory = 0;
	char itemKind = 0;
	char textureX = 0;
	char textureY = 0;
	char spreadType = 0;
	char isStripeyWallpaper = 0;
	int collisionType = 0; // buvo char collisionType = 0;
	char clothingType = 0;
	short val2;
	short isRayman = 0;
	int r_1 = 0, r_2 = 0, max_gems = 0;
	unsigned char maxAmount = 0;
	string on_equip = "", on_remove = "", playmod = "";
	string extraFile = "";
	string petName = "";
	string petPrefix = "";
	string petSuffix = "";
	string petAbility = "";
	string extraOptions = "";
	string texture2 = "";
	string extraOptions2 = "";
	string punchOptions = "";
	string name = "";
	string texture = "";
	string description = "This item has no description.";
	string MultiFacing = "This item can be placed in both directions.";
	int16_t rarity = 0;
	ClothTypes clothType{};
	BlockTypes blockType{};
};
vector<ItemDB> items;