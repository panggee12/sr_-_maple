#pragma once

namespace Client
{
	//const unsigned int g_iWinSizeX = 1280;
	//const unsigned int g_iWinSizeY = 720;
	const unsigned int g_iWinSizeX = 1280;
	const unsigned int g_iWinSizeY = 720;
	enum LEVEL { LEVEL_STATIC, LEVEL_LOADING, LEVEL_LOGO, LEVEL_GAMEPLAY, LEVEL_END };

<<<<<<< HEAD
	enum EQUIP_ITEM {
		Equip_Helmet, Equip_Necklace, Equip_Cloak, Equip_Pants, Equip_Belt,
		Equip_Glove, Equip_Shoes, Equip_Ring, Equip_Weapon, Equip_End
	};

	enum CONSUMABLE_ITEM { Consume_Hp, Consume_Mp, Consume_Money_0, Consume_Money_1, Consume_End };

	enum QUICK_ITEM { Quick_Normal, Quick_HP, Quick_MP, Quick_End };
=======
	enum EQUIP_ITEM { Equip_Helmet, Equip_Necklace, Equip_Cloak, Equip_Pants, Equip_Belt, 
					 Equip_Glove, Equip_Shoes, Equip_Ring, Equip_Weapon, Equip_End };

	enum CONSUMABLE_ITEM { Consume_Hp, Consume_Mp, Consume_Money_0, Consume_Money_1, Consume_End };

	enum QUICK_ITEM {Quick_Normal, Quick_HP, Quick_MP, Quick_End};
>>>>>>> aa192b3238a5dae7f5a2cf8c530fc184cccd860b
}

#include <process.h>
#include <ctime>

// Client_Defines.h

extern HWND         g_hWnd;
extern HINSTANCE   g_hInst;

using namespace Client;