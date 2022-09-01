#include "stdafx.h"
#include "..\Public\Level_GamePlay.h"

#include "GameInstance.h"
#include "Camera_Dynamic.h"
#include "Player.h"
#include "Layer.h"
#include "ItemInfoUI.h"
CLevel_GamePlay::CLevel_GamePlay(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel(pGraphic_Device)
{
}

HRESULT CLevel_GamePlay::Initialize()
{

	if (FAILED(__super::Initialize()))
		return E_FAIL;

	LoadMapData();

	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_TestBox(TEXT("Layer_TestBox"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
		return E_FAIL;

	/*
	for (int i = 0; i < 1; ++i)
	{
		if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster"))))
			return E_FAIL;
	}
	*/
	if (FAILED(Ready_Layer_UI(TEXT("Layer_UI"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	POINT pt = {};
	GetCursorPos(&pt);					//마우스 받아오기
	ScreenToClient(g_hWnd, &pt);

	auto Quick = pGameInstance->Find_Layer(LEVEL_GAMEPLAY, TEXT("Layer_UI"));  //퀵슬록 기능위한 유아이 레이어 받기

	if (pt.y > 550)			//퀵슬롯 기능 구간
	{
		_uint iIndex = 0;
		for (auto& col : m_eQuickInfo)
		{
			if (PtInRect(&col.rc, pt) && pGameInstance->Key_Down(VK_LBUTTON)) //이러면 인덱스는 충돌된 아이템 퀵슬롯의 인덱스임
			{
				_uint iCheck = 0;
				for (auto& iter : Quick->Get_ObjectList())
				{
					if (iCheck - 13 == iIndex)
					{
						dynamic_cast<CItemInfoUI*>(iter)->Set_QuickItem();
						break;
					}
					++iCheck;
				}
				break;
			}
			++iIndex;
		}
	}
	//충돌처리 구간

	auto Player = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Player"));      //플레이어 찾아오기

	_float3 vPlayerPos = Player->Get_Transform()->Get_State(CTransform::STATE_POSITION); //플레이어 위치

	//vPlayerPos.x = round(vPlayerPos.x);
	//vPlayerPos.y = round(vPlayerPos.y);//플레이어 위치 반올림
	//vPlayerPos.z = round(vPlayerPos.z);

	_float3 vPpos;
	vPpos.x = round(vPlayerPos.x);
	vPpos.y = round(vPlayerPos.y);
	vPpos.z = round(vPlayerPos.z);

	for (int i = -1; i < 2; ++i) //x
	{
		for (int j = -1; j < 2; ++j) //z
		{
			for (int k = -1; k < 2; ++k) //y
			{
				/*if (_uint(vPlayerPos.x + i)<0)
				{
					if (_uint(vPlayerPos.y) + k < 0)
					{
						if (_uint(vPlayerPos.z + j)<0)
						{
							continue;
						}
						continue;
					}
					continue;
				}*/

				if (m_fLayerPos[_uint(vPpos.x + i)][_uint(vPpos.y) + k][_uint(vPpos.z + j)] == 1)
				{
					pGameInstance->Collision_Rect_Cube(LEVEL_GAMEPLAY, Player->Get_Transform(), vPlayerPos,
						_float3(vPpos.x + i, vPpos.y + k, vPpos.z + j), fTimeDelta, _float3(0.2f, 0.3f, 0.2f));
				}
			}
		}
	}	
	/*
	auto Monster1 = pGameInstance->Find_Layer(LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster"));      //플레이어 찾아오기

	for (auto& mObj : Monster1->Get_ObjectList())
	{
		_float3 vMonsterPos = mObj->Get_Transform()->Get_State(CTransform::STATE_POSITION); //플레이어 위치

		_float3 vMpos;
		vMpos.x = round(vMonsterPos.x);
		vMpos.y = round(vMonsterPos.y);
		vMpos.z = round(vMonsterPos.z);

		for (int i = -1; i < 2; ++i) //x
		{
			for (int j = -1; j < 2; ++j) //z
			{
				for (int k = -1; k < 2; ++k) //y
				{
					if (m_fLayerPos[_uint(vMpos.x + i)][_uint(vMpos.y) + k][_uint(vMpos.z + j)] == 1)
					{
						pGameInstance->Collision_Rect_Cube(LEVEL_GAMEPLAY, mObj->Get_Transform(), vMonsterPos,
							_float3(vMpos.x + i, vMpos.y + k, vMpos.z + j), fTimeDelta, _float3(0.5f, 0.5f, 0.5f));
					}
				}
			}
		}
	}

	auto Monster2 = pGameInstance->Find_Layer(LEVEL_GAMEPLAY, TEXT("Layer_BellaMonster"));      //플레이어 찾아오기

	for (auto& mObj : Monster2->Get_ObjectList())
	{
		_float3 vMonsterPos = mObj->Get_Transform()->Get_State(CTransform::STATE_POSITION); //플레이어 위치

		_float3 vMpos;
		vMpos.x = round(vMonsterPos.x);
		vMpos.y = round(vMonsterPos.y);
		vMpos.z = round(vMonsterPos.z);

		for (int i = -1; i < 2; ++i) //x
		{
			for (int j = -1; j < 2; ++j) //z
			{
				for (int k = -1; k < 2; ++k) //y
				{
					if (m_fLayerPos[_uint(vMpos.x + i)][_uint(vMpos.y) + k][_uint(vMpos.z + j)] == 1)
					{
						pGameInstance->Collision_Rect_Cube(LEVEL_GAMEPLAY, mObj->Get_Transform(), vMonsterPos,
							_float3(vMpos.x + i, vMpos.y + k, vMpos.z + j), fTimeDelta, _float3(0.5f, 0.5f, 0.5f));
					}
				}
			}
		}
	}

	auto Monster3 = pGameInstance->Find_Layer(LEVEL_GAMEPLAY, TEXT("Layer_YetiMonster"));      //플레이어 찾아오기

	for (auto& mObj : Monster3->Get_ObjectList())
	{
		_float3 vMonsterPos = mObj->Get_Transform()->Get_State(CTransform::STATE_POSITION); //플레이어 위치

		_float3 vMpos;
		vMpos.x = round(vMonsterPos.x);
		vMpos.y = round(vMonsterPos.y);
		vMpos.z = round(vMonsterPos.z);

		for (int i = -1; i < 2; ++i) //x
		{
			for (int j = -1; j < 2; ++j) //z
			{
				for (int k = -1; k < 2; ++k) //y
				{
					if (m_fLayerPos[_uint(vMpos.x + i)][_uint(vMpos.y) + k][_uint(vMpos.z + j)] == 1)
					{
						pGameInstance->Collision_Rect_Cube(LEVEL_GAMEPLAY, mObj->Get_Transform(), vMonsterPos,
							_float3(vMpos.x + i, vMpos.y + k, vMpos.z + j), fTimeDelta, _float3(0.5f, 0.5f, 0.5f));
					}
				}
			}
		}
	}
	*/
	//pGameInstance->Collision_Rect_Cube(LEVEL_GAMEPLAY, TEXT("Layer_Monster"), TEXT("Layer_TestBox"), fTimeDelta, _float3(0.15f, 0.3f, 0.15f));

	//pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Player"), TEXT("Layer_Monster"), fTimeDelta, 2, _float3(0.15f, 0.3f, 0.15f), _float3(0.45f, 0.45f, 0.45f));
	
	//pGameInstance->Collision(LEVEL_GAMEPLAY, TEXT("Layer_Player"), TEXT("Layer_CubeTerrain"), fTimeDelta);


											//프레임 띄우는 구간
	++m_iNumRender;

	if (m_fTimeAcc > 1.0f)
	{
		wsprintf(m_szFPS, TEXT("FPS : %d"), m_iNumRender);

		OutputDebugString(m_szFPS);

		m_fTimeAcc = 0.f;
		m_iNumRender = 0;
	}

	Safe_Release(pGameInstance);
}

void CLevel_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	//SetWindowText(g_hWnd, TEXT("게임플레이레벨입니다."));
}

HRESULT CLevel_GamePlay::Ready_Layer_Player(const _tchar * pLayerTag)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_Player"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))
		return E_FAIL;	

	Safe_Release(pGameInstance);

	
	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Monster(const _tchar * pLayerTag)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	/* 원숭이 몬스터 */
	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_MonkeyMonster"), LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster"), nullptr)))
		return E_FAIL;

	/* 뱀 몬스터 */
	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_BellaMonster"), LEVEL_GAMEPLAY, TEXT("Layer_BellaMonster"), nullptr)))
		return E_FAIL;

	/* 설인 몬스터 */
	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_YetiMonster"), LEVEL_GAMEPLAY, TEXT("Layer_YetiMonster"), nullptr)))
		return E_FAIL;

	auto pPlayer = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Player"));

	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_TestBox(const _tchar * pLayerTag)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	for (auto& mapCube : m_CubeInfoList)
	{
		if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_TestBox"), LEVEL_GAMEPLAY, pLayerTag, &mapCube)))
			return E_FAIL;
	}

	Safe_Release(pGameInstance);
}

HRESULT CLevel_GamePlay::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_Sky"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_CubeTerrain(const _tchar * pLayerTag)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_CubeTerrain"), LEVEL_GAMEPLAY, pLayerTag, nullptr)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CCamera_Dynamic::CAMERADESC_DERIVED				CameraDesc;
	ZeroMemory(&CameraDesc, sizeof(CCamera_Dynamic::CAMERADESC_DERIVED));

	CameraDesc.iTest = 10;
	
	CameraDesc.CameraDesc.vEye = _float3(0.f, 10.f, -10.f);

	CameraDesc.CameraDesc.fFovy = D3DXToRadian(60.0f);
	CameraDesc.CameraDesc.fAspect = (_float)g_iWinSizeX / g_iWinSizeY;
	CameraDesc.CameraDesc.fNear = 0.2f;
	CameraDesc.CameraDesc.fFar = 500.f;

	CameraDesc.CameraDesc.TransformDesc.fSpeedPerSec = 10.f;
	CameraDesc.CameraDesc.TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_Camera_Dynamic"), LEVEL_GAMEPLAY, pLayerTag, &CameraDesc)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_InventoryUI"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_PlayerInfoUI"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_SkillbookUI"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_ExpBarUI"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_HpbarUI"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	for (_uint i = 0; i < 8; ++i)
	{
		_float3 vPos = {};

		if (i < 4)
		{
			vPos.x = 70.f * i;
			vPos.y = 600.f;
		}
		else if (i >= 4)
		{
			vPos.x = 70.f * i - 270.f;
			vPos.y = 670.f;
		}
		vPos.z = 0.f;

		if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_SkillInfoUI"), LEVEL_GAMEPLAY, pLayerTag, &vPos)))
			return E_FAIL;
	}

	for (_uint i = 0; i < 8; ++i)
	{
		_float3 vPos = {};

		if (i < 4)
		{
			vPos.x = 70.f * i;
			vPos.y = 600.f;
		}
		else if (i >= 4)
		{
			vPos.x = 70.f * i - 290.f;
			vPos.y = 670.f;
		}
		vPos.z = 0.f;

		if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_ItemInfoUI"), LEVEL_GAMEPLAY, pLayerTag, &vPos)))
			return E_FAIL;

		RECT rc = {};

		SetRect(&rc, vPos.x - 33 + 770.f , vPos.y - 33, vPos.x + 33 + 770.f, vPos.y + 33);

		m_eQuickInfo[i].iIndex = i;
		m_eQuickInfo[i].rc = rc;
	}
	Safe_Release(pGameInstance);
}

void CLevel_GamePlay::LoadMapData()
{

	HANDLE		hFile = CreateFile(L"../Data/Map/MapData.dat",			// 파일 경로와 이름 명시
		GENERIC_READ,				// 파일 접근 모드 (GENERIC_WRITE 쓰기 전용, GENERIC_READ 읽기 전용)
		NULL,						// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가, NULL인 경우 공유하지 않는다
		NULL,						// 보안 속성, 기본값	
		OPEN_EXISTING,				// 생성 방식, CREATE_ALWAYS는 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXISTING 파일이 있을 경우에면 열기
		FILE_ATTRIBUTE_NORMAL,		// 파일 속성(읽기 전용, 숨기 등), FILE_ATTRIBUTE_NORMAL 아무런 속성이 없는 일반 파일 생성
		NULL);						// 생성도리 파일의 속성을 제공할 템플릿 파일, 우리는 사용하지 않아서 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// 팝업 창을 출력해주는 기능의 함수
		// 1. 핸들 2. 팝업 창에 띄우고자하는 메시지 3. 팝업 창 이름 4. 버튼 속성
		MessageBox(g_hWnd, L"Load File", L"Fail", MB_OK);
		return;
	}

	// 2. 파일 쓰기

	DWORD		dwByte = 0;
	CTestBox::CUBEDESC		tInfo{};
	_tchar tPos = {};

	//wchar_t* FileName = CImGui_Manager::Get_Instance()->GetFileNames();

	//ReadFile(hFile, FileName, sizeof(wchar_t) * 256, &dwByte, nullptr);

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(CTestBox::CUBEDESC), &dwByte, nullptr);

		if (0 == dwByte)	// 더이상 읽을 데이터가 없을 경우
			break;

		//-28 0 -12 x, y, z가 각각 모든 블럭중 최소값을 가짐 모든 블럭 불러올때 +28, +12 해주자

		tInfo.vPos.x += 28.f;
		tInfo.vPos.y += 0.5f;
		tInfo.vPos.z += 12.f;

		m_fLayerPos[_uint(tInfo.vPos.x)][_uint(tInfo.vPos.y)][_uint(tInfo.vPos.z)] = 1;
		
		m_CubeInfoList.push_back(tInfo);
	}
	
	// 3. 파일 소멸
	CloseHandle(hFile);


	//DrawAll_Cube();
}


CLevel_GamePlay * CLevel_GamePlay::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_GamePlay*	pInstance = new CLevel_GamePlay(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		ERR_MSG(TEXT("Failed to Created : CLevel_GamePlay"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_GamePlay::Free()
{
	__super::Free();

}
