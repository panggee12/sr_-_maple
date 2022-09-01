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
	GetCursorPos(&pt);					//���콺 �޾ƿ���
	ScreenToClient(g_hWnd, &pt);

	auto Quick = pGameInstance->Find_Layer(LEVEL_GAMEPLAY, TEXT("Layer_UI"));  //������ ������� ������ ���̾� �ޱ�

	if (pt.y > 550)			//������ ��� ����
	{
		_uint iIndex = 0;
		for (auto& col : m_eQuickInfo)
		{
			if (PtInRect(&col.rc, pt) && pGameInstance->Key_Down(VK_LBUTTON)) //�̷��� �ε����� �浹�� ������ �������� �ε�����
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
	//�浹ó�� ����

	auto Player = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Player"));      //�÷��̾� ã�ƿ���

	_float3 vPlayerPos = Player->Get_Transform()->Get_State(CTransform::STATE_POSITION); //�÷��̾� ��ġ

	//vPlayerPos.x = round(vPlayerPos.x);
	//vPlayerPos.y = round(vPlayerPos.y);//�÷��̾� ��ġ �ݿø�
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
	auto Monster1 = pGameInstance->Find_Layer(LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster"));      //�÷��̾� ã�ƿ���

	for (auto& mObj : Monster1->Get_ObjectList())
	{
		_float3 vMonsterPos = mObj->Get_Transform()->Get_State(CTransform::STATE_POSITION); //�÷��̾� ��ġ

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

	auto Monster2 = pGameInstance->Find_Layer(LEVEL_GAMEPLAY, TEXT("Layer_BellaMonster"));      //�÷��̾� ã�ƿ���

	for (auto& mObj : Monster2->Get_ObjectList())
	{
		_float3 vMonsterPos = mObj->Get_Transform()->Get_State(CTransform::STATE_POSITION); //�÷��̾� ��ġ

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

	auto Monster3 = pGameInstance->Find_Layer(LEVEL_GAMEPLAY, TEXT("Layer_YetiMonster"));      //�÷��̾� ã�ƿ���

	for (auto& mObj : Monster3->Get_ObjectList())
	{
		_float3 vMonsterPos = mObj->Get_Transform()->Get_State(CTransform::STATE_POSITION); //�÷��̾� ��ġ

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


											//������ ���� ����
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

	//SetWindowText(g_hWnd, TEXT("�����÷��̷����Դϴ�."));
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

	/* ������ ���� */
	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_MonkeyMonster"), LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster"), nullptr)))
		return E_FAIL;

	/* �� ���� */
	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_BellaMonster"), LEVEL_GAMEPLAY, TEXT("Layer_BellaMonster"), nullptr)))
		return E_FAIL;

	/* ���� ���� */
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

	HANDLE		hFile = CreateFile(L"../Data/Map/MapData.dat",			// ���� ��ο� �̸� ���
		GENERIC_READ,				// ���� ���� ��� (GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�, NULL�� ��� �������� �ʴ´�
		NULL,						// ���� �Ӽ�, �⺻��	
		OPEN_EXISTING,				// ���� ���, CREATE_ALWAYS�� ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);						// �������� ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʾƼ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// �˾� â�� ������ִ� ����� �Լ�
		// 1. �ڵ� 2. �˾� â�� �������ϴ� �޽��� 3. �˾� â �̸� 4. ��ư �Ӽ�
		MessageBox(g_hWnd, L"Load File", L"Fail", MB_OK);
		return;
	}

	// 2. ���� ����

	DWORD		dwByte = 0;
	CTestBox::CUBEDESC		tInfo{};
	_tchar tPos = {};

	//wchar_t* FileName = CImGui_Manager::Get_Instance()->GetFileNames();

	//ReadFile(hFile, FileName, sizeof(wchar_t) * 256, &dwByte, nullptr);

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(CTestBox::CUBEDESC), &dwByte, nullptr);

		if (0 == dwByte)	// ���̻� ���� �����Ͱ� ���� ���
			break;

		//-28 0 -12 x, y, z�� ���� ��� ���� �ּҰ��� ���� ��� �� �ҷ��ö� +28, +12 ������

		tInfo.vPos.x += 28.f;
		tInfo.vPos.y += 0.5f;
		tInfo.vPos.z += 12.f;

		m_fLayerPos[_uint(tInfo.vPos.x)][_uint(tInfo.vPos.y)][_uint(tInfo.vPos.z)] = 1;
		
		m_CubeInfoList.push_back(tInfo);
	}
	
	// 3. ���� �Ҹ�
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
