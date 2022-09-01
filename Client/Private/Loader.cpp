#include "stdafx.h"
#include "..\Public\Loader.h"
#include "GameInstance.h"
#include "Camera_Dynamic.h"
#include "BackGround.h"
#include "Terrain.h"
#include "Player.h"
#include "Monster.h"
#include "LupangMonster.h"
#include "BellaMonster.h"
#include "YetiMonster.h"
#include "Sky.h"
#include "TestBox.h"
#include "CubeTerrain.h"
#include "LupangSkill.h"
#include "YetiSkill.h"
#include "LogoUI.h"
#include "InventoryUI.h"
#include "PlayerInfoUI.h"
#include "SkillbookUI.h"
#include "HpBarUI.h"
#include "ExpBarUI.h"
#include "SkillInfoUI.h"
#include "ItemInfoUI.h"
#include "Player_Skill.h"
#include "Player_Attack.h"
#include "Effect.h"



CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

unsigned int APIENTRY Thread_Main(void* pArg)
{
	CLoader*		pLoader = (CLoader*)pArg;

	EnterCriticalSection(&pLoader->Get_CriticalSection());

	switch (pLoader->Get_NextLevelID())
	{
	case LEVEL_LOGO:
		pLoader->Loading_ForLogoLevel();
		break;
	case LEVEL_GAMEPLAY:
		pLoader->Loading_ForGamePlayLevel();
		break;
	}

	LeaveCriticalSection(&pLoader->Get_CriticalSection());

	return 0;
}

HRESULT CLoader::Initialize(LEVEL eNextLevel)
{
	m_eNextLevel = eNextLevel;

	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, Thread_Main, this, 0, nullptr);
	if (0 == m_hThread)
		return E_FAIL;
		
	return S_OK;
}

HRESULT CLoader::Loading_ForLogoLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	if (nullptr == pGameInstance)
		return E_FAIL;

	Safe_AddRef(pGameInstance);

	/* 텍스쳐 로딩 중. */
	//lstrcpy(m_szLoadingText, TEXT("텍스쳐 로딩 중."));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Component_Texture_LogoUI"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Logo/LogoBack_%d.png"), 1))))
		return E_FAIL;
	
	/* 모델 로딩 중. */
	//lstrcpy(m_szLoadingText, TEXT("모델 로딩 중."));
	

	/* 셰이더 로딩 중. */
	//lstrcpy(m_szLoadingText, TEXT("셰이더 로딩 중."));
	

	/* 객체 원형 생성 중. */
	//lstrcpy(m_szLoadingText, TEXT("객체 생성 중."));
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LogoUI"),
		CLogoUI::Create(m_pGraphic_Device))))
		return E_FAIL;
	

	//lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader::Loading_ForGamePlayLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	if (nullptr == pGameInstance)
		return E_FAIL;

	Safe_AddRef(pGameInstance);

	/* 텍스쳐 로딩 중. */
	//zzlstrcpy(m_szLoadingText, TEXT("텍스쳐 로딩 중."));

	/*For.Prototype_Component_Texture_UI */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_HpbarUI"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/UI/HpBarMold%d.png"), 1))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_ExpbarUI"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/UI/ExpBarUI%d.png"), 1))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_SkillInfoUI"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/UI/PlayerInfo%d.png"), 1))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_ItemInfoUI"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Icon/Item/Quick/Quick_Item_%d.png"), 3))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_InventoryUI"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/UI/Inventory_%d.png"), 1))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_PlayerInfoUI"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/UI/PlayerInfoUI%d.png"), 1))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_SkillbookUI"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/UI/SkillBook%d.png"), 1))))
		return E_FAIL;


	/*For.Prototype_Component_Texture_Terrain*/
	/*if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Terrain"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Terrain/Grass_%d.tga"), 2))))
		return E_FAIL;*/

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player"),
<<<<<<< HEAD
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/C_%d.png"), 152))))
=======
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/C_%d.png"),200))))
>>>>>>> BaeH
		return E_FAIL;



	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Skill_Litening"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Skill/LT_%d.dds"), 8))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Player_Attack/FB_%d.dds"), 16))))
		return E_FAIL;

	/*For.Prototype_Component_Texture_Efect */

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Skill_Fire_Effect"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Player_Attack/Efect_Fire/Explosion%d.png"), 9))))
		return E_FAIL;

	/*For.Prototype_Component_Texture_Sky */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Sky"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBEMAP, TEXT("../Bin/Resources/Textures/SkyBox/Sky_%d.dds"), 19))))
		return E_FAIL;

	/*For.Prototype_Component_Texture_Monster */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Monster"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Monster/NornilAttack%d.png"), 20))))
		return E_FAIL;

	//if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Monster2"),
	//	CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Monster/monster%d.png"), 1))))
	//	return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Monster3"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Monster/cow/M_%d.png"), 32))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Equip"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Icon/Equip/Equip_%d.png"), 14)))) //장비
		return E_FAIL;

	//스킬 아이콘 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Skill_Icon"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Icon/Skill/Skill_%d.png"), 2))))
		return E_FAIL;

	/*루팡몬스터 (원숭이) 텍스쳐*/

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_MonkeyMonster"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Monster/Monkey/monkey%d.png"), 17))))
		return E_FAIL;

	/*벨라모아 몬스터(뱀) 텍스쳐*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_BellaMonster"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Monster/Bella/Bam%d.png"), 15))))
		return E_FAIL;

	/*예티 몬스터 텍스쳐*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_YetiMonster"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Monster/Yeti/yeti%d.png"), 26))))
		return E_FAIL;

	/*루팡스킬 바나나던지기*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_MonkeySkill"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Monster/Monkey/Skill/banana%d.png"), 6))))
		return E_FAIL;

	/* 예티 스킬*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_YetiSkill"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Monster/Yeti/Skill/YetiSkill%d.png"), 4))))
		return E_FAIL;

	/* 모델 로딩 중. */
	//lstrcpy(m_szLoadingText, TEXT("모델 로딩 중."));

	/*For.Prototype_Component_VIBuffer_CubeTerrain*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_CubeTerrain"),
		CVIBuffer_CubeTerrain::Create(m_pGraphic_Device, 10, 10))))
		return E_FAIL;

	/*For.Prototype_Component_VIBuffer_Cube */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Cube"),
		CVIBuffer_Cube::Create(m_pGraphic_Device))))
		return E_FAIL;
	

	/* 셰이더 로딩 중. */
	//lstrcpy(m_szLoadingText, TEXT("셰이더 로딩 중."));
	

	/* 객체 생성 중. */
	//lstrcpy(m_szLoadingText, TEXT("객체 생성 중."));

	/*For.Prototype_GameObject_UI */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_InventoryUI"),
		CInventoryUI::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PlayerInfoUI"),
		CPlayerInfoUI::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_SkillbookUI"),
		CSkillbookUI::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_HpbarUI"),
		CHpbarUI::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ExpBarUI"),
		CExpBarUI::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_SkillInfoUI"),
		CSkillInfoUI::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ItemInfoUI"),
		CItemInfoUI::Create(m_pGraphic_Device))))
		return E_FAIL;

	/*For.Prototype_GameObject_Sky */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Sky"),
		CSky::Create(m_pGraphic_Device))))
		return E_FAIL;

	/*For.Prototype_GameObject_Player*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player"),
		CPlayer::Create(m_pGraphic_Device))))
		return E_FAIL;

	///*For.Prototype_GameObject_Efect*/
	//if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Effect"),
	//	CEffect::Create(m_pGraphic_Device))))
	//	return E_FAIL;

	/*For.Prototype_GameObject_Player_Skill*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player_Skill"),
		CPlayer_Litening::Create(m_pGraphic_Device))))
		return E_FAIL;
	
	/*For.Prototype_GameObject_Player_Attack*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player_Attack"),
		CPlayer_Attack::Create(m_pGraphic_Device))))
		return E_FAIL;


	/*For.Prototype_GameObject_Player_Attack_Efect*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fire_Effect"),
		CEffect::Create(m_pGraphic_Device))))
		return E_FAIL;


	/*For.Prototype_GameObject_MonkeyMonster 루팡(원숭이몬스터)*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MonkeyMonster"),
		CLupangMonster::Create(m_pGraphic_Device))))
		return E_FAIL;

	/*For.Prototype_GameObject_BellaMonster 벨라(뱀몬스터)*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BellaMonster"),
		CBellaMonster::Create(m_pGraphic_Device))))
		return E_FAIL;


	/*For.Prototype_GameObject_YetiMonster 예티(설인몬스터)*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_YetiMonster"),
		CYetiMonster::Create(m_pGraphic_Device))))
		return E_FAIL;


	/*For.Prototype_GameObject_MonkeySkill*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MonkeySkill"),
		CLupangSkill::Create(m_pGraphic_Device))))
		return E_FAIL;

	/*For.Prototype_GameObject_YetiSkill 예티스킬*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_YetiSkill"),
		CYetiSkill::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_TestBox"),
		CTestBox::Create(m_pGraphic_Device))))
		return E_FAIL;

	/*For.Prototype_GameObject_Terrain*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Terrain"),
		CTerrain::Create(m_pGraphic_Device))))
		return E_FAIL;

	/*For.Prototype_GameObject_Terrain*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CubeTerrain"),
		CCubeTerrain::Create(m_pGraphic_Device))))
		return E_FAIL;

	/*For.Prototype_GameObject_Camera_Dynamic */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Camera_Dynamic"),
		CCamera_Dynamic::Create(m_pGraphic_Device))))
		return E_FAIL;
	

	//lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

	Safe_Release(pGameInstance);

	m_isFinished = true;


	return S_OK;
}

CLoader * CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLoader*	pInstance = new CLoader(pGraphic_Device);

	if (FAILED(pInstance->Initialize(eNextLevel)))
	{
		ERR_MSG(TEXT("Failed to Created : CLoader"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoader::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);

	CloseHandle(m_hThread);

	DeleteCriticalSection(&m_CriticalSection);

	Safe_Release(m_pGraphic_Device);
}
