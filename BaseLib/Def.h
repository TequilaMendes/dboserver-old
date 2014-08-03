#ifndef _DEF_H
#define _DEF_H

#include <Windows.h>

#define SAFE_DELETE_ARRAY(p)	if(p) { delete[] p; p = 0; }
#define SAFE_FREE(p)			if(p) { free(p); p = 0; }

typedef char SBYTE;
typedef unsigned char BYTE;
typedef short SWORD;
typedef unsigned short WORD;
typedef long SDWORD;
typedef unsigned long DWORD;
typedef long long SQWORD;
typedef unsigned long long QWORD;
#define pi 3.1415926535897932384626433832795
#define r2d pi/180

#define SERVER_PORT 50200
#define MAX_BUFFER_SIZE 7048

#define MAX_USERNAME_SIZE (12)
#define MAX_PASSWORD_SIZE (12)
#define MAX_AUTHKEY_SIZE (16)
#define MAX_SRVADDR_SIZE (64)
#define MAX_CHARSRV_COUNT (10)
#define MAX_MAC_ADDR_SIZE (6)
#define INVALID_SERVERID (0xFF)
#define INVALID_SLOTID (0xFF)
#define MAX_SERVERNAME_SIZE (32)
#define MAX_CHANNEL_COUNT (10)
#define MAX_CHARNAME_SIZE (16)
#define MAX_ITEM_OPTION (2)
#define INVALID_MARKING_TYPE (0xffui8)
#define INVALID_BYTE (0xffui8)
#define MAX_CHARSLOT_COUNT (8)
#define ALLRACES (0xFF)

static wchar_t* charToWChar(const char* text)
{
	size_t conv, size = strlen(text) + 1;
	wchar_t* wa = new wchar_t[size];
	mbstowcs_s(&conv, wa, size, text, size);
	return wa;
}

enum ResultCodes
{
	// BASE
	RESULT_SUCCESS = 0,
	RESULT_FAIL,
	// AUTHSERVER
	AUTH_SUCCESS = 100,
	AUTH_FAIL,
	AUTH_VERSION_FAIL,
	AUTH_TOO_LONG_ACCOUNT,
	AUTH_TOO_LONG_PASSWORD,
	AUTH_AUTHKEY_FAIL,
	AUTH_USER_SAMENAME_EXIST,
	AUTH_WRONG_PASSWORD,
	AUTH_USER_NOT_FOUND,
	AUTH_USER_EXIST,
	AUTH_USER_EXIST_IN_CHARACTER_SERVER,
	AUTH_DB_FAIL,
	AUTH_NO_AVAILABLE_CHARACTER_SERVER,
	AUTH_USER_BLOCK,
	AUTH_USER_TEMPORARY_BLOCK,
	AUTH_SERVER_LOCKED,
	AUTH_COMMON_CANT_DO_THAT_FOR_SOME_REASON,
	AUTH_INVALID_CJI_KOR_COOKIE,
	AUTH_IP_BLOCK,
	AUTH_USER_KICKOUT_WAIT_PLZ,
	// CHARSERVER
	CHARACTER_SUCCESS = 200,
	CHARACTER_FAIL,
	CHARACTER_AUTHKEY_FAIL,
	CHARACTER_TOO_LONG_NAME,
	CHARACTER_TOO_SHORT_NAME,
	CHARACTER_SAMENAME_EXIST,
	CHARACTER_COUNT_OVER,
	CHARACTER_NAME_NOT_EXIST,
	CHARACTER_CREATE_VALUE_FAIL,
	CHARACTER_USER_EXIST,
	CHARACTER_USER_EXIST_IN_GAME_SERVER,
	CHARACTER_USER_ITEM_CREATE_FAIL,
	CHARACTER_USER_SKILL_CREATE_FAIL,
	CHARACTER_USER_QUICK_SLOT_CREATE_FAIL,
	CHARACTER_DB_QUERY_FAIL,
	CHARACTER_WRONG_SERVER_FARM_SELECTED,
	CHARACTER_USER_BLOCK,
	CHARACTER_BLOCK_STRING_INCLUDED,
	CHARACTER_TEMPORARY_BLOCK,
	CHARACTER_AUTHKEY_MISMATCH,
	CHARACTER_AUTHKEY_CREATE_FAIL,
	CHARACTER_AUTHKEY_NOT_FOUND,
	CHARACTER_DELETE_GUILD_LEADER_FAIL,
	CHARACTER_DELETE_BUDOKAI_REGISTER_FAIL,
	CHARACTER_SERVER_LOCKED,
	CHARACTER_DISCONNECTED_FORCEDLY,
	CHARACTER_DISCONNECTED_TEMPORARILY,
	CHARACTER_RACE_NOT_ALLOWED,
	CHARACTER_COMMON_CANT_DO_THAT_FOR_SOME_REASON,
	CHARACTER_USER_SHOULD_WAIT_FOR_CONNECT,
	CHARACTER_SERVER_IS_UNDER_CONSTRUCTION,
	CHARACTER_DELETE_CHAR_FAIL,
};

enum SERVERSTATUS
{
	SERVERSTATUS_UP = 0,
	SERVERSTATUS_DOWN,
	SERVERSTATUS_LOCKED
};

enum EQUIP_SLOTTYPE
{
	EQUIP_SLOT_TYPE_HAND,
	EQUIP_SLOT_TYPE_SUB_WEAPON,
	EQUIP_SLOT_TYPE_JACKET,
	EQUIP_SLOT_TYPE_PANTS,
	EQUIP_SLOT_TYPE_BOOTS,
	EQUIP_SLOT_TYPE_SCOUTER,
	EQUIP_SLOT_TYPE_COSTUME,
	EQUIP_SLOT_TYPE_NECKLACE,
	EQUIP_SLOT_TYPE_EARRING_1,
	EQUIP_SLOT_TYPE_EARRING_2,
	EQUIP_SLOT_TYPE_RING_1,
	EQUIP_SLOT_TYPE_RING_2,

	EQUIP_SLOT_TYPE_COUNT,
	EQUIP_SLOT_TYPE_UNKNOWN = 0xFF,

	EQUIP_SLOT_TYPE_FIRST = EQUIP_SLOT_TYPE_HAND,
	EQUIP_SLOT_TYPE_LAST = EQUIP_SLOT_TYPE_RING_2,
};

#pragma pack(1)

struct SRVINFO
{
	BYTE CharServerIP[MAX_SRVADDR_SIZE + 1];
	WORD CharServerPort;
	DWORD Load;
};

struct GAMESERVER_INFO
{
	GAMESERVER_INFO() :
		serverId(INVALID_SERVERID),
		ServerStatus(SERVERSTATUS_DOWN),
		MaxLoad(0),
		Load(0)
	{
		::ZeroMemory(ServerName, sizeof(ServerName));
	};

	BYTE serverId;
	WCHAR ServerName[MAX_SERVERNAME_SIZE + 1];
	BYTE ServerStatus;
	DWORD MaxLoad;
	DWORD Load;
};

struct GAMECHANNEL_INFO
{
	GAMECHANNEL_INFO() :
		serverId(INVALID_SERVERID),
		ChannelId(INVALID_SLOTID),
		IsVisible(true),
		ServerStatus(SERVERSTATUS_DOWN),
		MaxLoad(0),
		Load(0)
	{
	};

	BYTE serverId;
	BYTE ChannelId;
	bool IsVisible;
	BYTE ServerStatus;
	DWORD MaxLoad;
	DWORD Load;
};

struct ITEMDATA
{
	unsigned int tblidx;
	BYTE Rank;
	BYTE Grade;
	BYTE BattleAttribute;
	unsigned int OptionTblidx[MAX_ITEM_OPTION];
};

struct MARKING
{
	BYTE Code;
public:
	MARKING()
		: Code(INVALID_MARKING_TYPE)
	{
	}
};

struct DOGIDATA
{
	bool IsIntialized;
	int guildId;
	BYTE Type;
	BYTE GuildColor;
	BYTE DojoColor;
};

struct CHARDATA
{
	unsigned int charId; //
	WCHAR Name[MAX_CHARNAME_SIZE + 1]; //
	BYTE Race; //
	BYTE Class; //
	bool IsAdult; //
	BYTE Gender; // 
	BYTE Face; //
	BYTE Hair; //
	BYTE HairColor; //
	BYTE SkinColor; //
	BYTE Level; //
	unsigned int worldTblidx;
	unsigned int worldId;
	float PositionX;
	float PositionY;
	float PositionZ;
	DWORD Money;
	DWORD MoneyBank;
	ITEMDATA Item[EQUIP_SLOT_TYPE_COUNT];
	DWORD MapInfoId;
	bool TutorialFlag;
	MARKING Marking;
	bool NeedNameChange; //
	DOGIDATA Dogi;
};

struct TODEL_CHARINFO
{
	int charId;
	DWORD PastTick;
};

#pragma pack()

#endif