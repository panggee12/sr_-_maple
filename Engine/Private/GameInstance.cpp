#include "..\Public\GameInstance.h"


IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
	: m_pGraphic_Device(CGraphic_Device::Get_Instance())
	, m_pInput_Device(CInput_Device::Get_Instance())
	, m_pLevel_Manager(CLevel_Manager::Get_Instance())
	, m_pObject_Manager(CObject_Manager::Get_Instance())
	, m_pTimer_Manager(CTimer_Manager::Get_Instance())
	, m_pComponent_Manager(CComponent_Manager::Get_Instance())
	, m_pCollision_Manager(CCollisionMgr::Get_Instance())
	, m_pKey_Manager(CKeyMgr::Get_Instance())

{

	Safe_AddRef(m_pKey_Manager);
	Safe_AddRef(m_pComponent_Manager);
	Safe_AddRef(m_pTimer_Manager);
	Safe_AddRef(m_pObject_Manager);
	Safe_AddRef(m_pLevel_Manager);
	Safe_AddRef(m_pInput_Device);
	Safe_AddRef(m_pCollision_Manager);
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CGameInstance::Initialize_Engine(HINSTANCE hInst, _uint iNumLevels, const GRAPHIC_DESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	if (nullptr == m_pGraphic_Device ||
		nullptr == m_pObject_Manager)
		return E_FAIL;

	/* �׷��� ����̽��� �ʱ�ȭ�Ѵ�. */
	if (FAILED(m_pGraphic_Device->InitDevice(GraphicDesc, ppOut)))
		return E_FAIL;

	/* �Է� ����̽��� �ʱ�ȭ�Ѵ�. */
	if (FAILED(m_pInput_Device->Initialize(hInst, GraphicDesc.hWnd)))
		return E_FAIL;


	/* ���� ����̽��� �ʱ�ȭ�Ѵ�. */


	/* �����̳��� ������ Ȯ���صд�. */
	if (FAILED(m_pObject_Manager->Reserve_Container(iNumLevels)))
		return E_FAIL;

	if (FAILED(m_pComponent_Manager->Reserve_Container(iNumLevels)))
		return E_FAIL;




	return S_OK;
}

void CGameInstance::Tick_Engine(_float fTimeDelta)
{
	if (nullptr == m_pLevel_Manager ||
		nullptr == m_pObject_Manager)
		return;

	m_pInput_Device->Update();

	m_pLevel_Manager->Tick(fTimeDelta);
	m_pObject_Manager->Tick(fTimeDelta);


	m_pLevel_Manager->Late_Tick(fTimeDelta);
	m_pObject_Manager->Late_Tick(fTimeDelta);
}

void CGameInstance::Clear(_uint iLevelIndex)
{
	if (nullptr == m_pObject_Manager ||
		nullptr == m_pComponent_Manager)
		return;

	m_pComponent_Manager->Clear(iLevelIndex);
	m_pObject_Manager->Clear(iLevelIndex);
}

void CGameInstance::Render_Begin(void)
{
	if (nullptr == m_pGraphic_Device)
		return;

	m_pGraphic_Device->Render_Begin();
}

void CGameInstance::Render_End(HWND hWnd)
{
	if (nullptr == m_pGraphic_Device)
		return;

	m_pGraphic_Device->Render_End(hWnd);
}

_char CGameInstance::Get_DIKState(_uchar eKeyID)
{
	if (nullptr == m_pInput_Device)
		return 0;

	return m_pInput_Device->Get_DIKState(eKeyID);
}

_char CGameInstance::Get_DIMKeyState(DIMK eMouseKeyID)
{
	if (nullptr == m_pInput_Device)
		return 0;

	return m_pInput_Device->Get_DIMKeyState(eMouseKeyID);
}

_long CGameInstance::Get_DIMMoveState(DIMM eMouseMoveID)
{
	if (nullptr == m_pInput_Device)
		return 0;

	return m_pInput_Device->Get_DIMMoveState(eMouseMoveID);
}

HRESULT CGameInstance::Add_Timer(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimer_Manager)
		return E_FAIL;

	return m_pTimer_Manager->Add_Timer(pTimerTag);
}

_float CGameInstance::Get_TimeDelta(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimer_Manager)
		return 0.0f;

	return m_pTimer_Manager->Get_TimeDelta(pTimerTag);
}

void CGameInstance::Update(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimer_Manager)
		return;

	m_pTimer_Manager->Update(pTimerTag);
}

HRESULT CGameInstance::Open_Level(unsigned int iLevelIndex, CLevel * pNewLevel)
{
	if (nullptr == m_pLevel_Manager)
		return E_FAIL;

	return m_pLevel_Manager->Open_Level(iLevelIndex, pNewLevel);
}

HRESULT CGameInstance::Add_Prototype(const _tchar * pPrototypeTag, CGameObject * pPrototype)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Add_Prototype(pPrototypeTag, pPrototype);
}

HRESULT CGameInstance::Add_GameObject(const _tchar * pPrototypeTag, _uint iLevelIndex, const _tchar * pLayerTag, void* pArg)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;



	return m_pObject_Manager->Add_GameObject(pPrototypeTag, iLevelIndex, pLayerTag, pArg);
}

class CGameObject* CGameInstance::Find_Target(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (nullptr == m_pObject_Manager)
		return nullptr;

	return m_pObject_Manager->Find_Target(iLevelIndex, pLayerTag);
}

CGameObject * CGameInstance::Get_BackObject(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (nullptr == m_pObject_Manager)
		return nullptr;

	return m_pObject_Manager->Get_BackObject(iLevelIndex, pLayerTag);
}

bool CGameInstance::Collision(_uint iLevelIndex, const _tchar * col1, const _tchar * col2, _float fTimeDelta, _float3 f1Scale, _float3 f2Scale)
{
	if (nullptr == m_pObject_Manager ||
		nullptr == m_pCollision_Manager)
		return false;

	auto Col1Target = m_pObject_Manager->Find_Layer(iLevelIndex, col1);
	auto Col2Target = m_pObject_Manager->Find_Layer(iLevelIndex, col2);

	for (auto& Target1 : Col1Target->Get_ObjectList())
	{
		for (auto& Target2 : Col2Target->Get_ObjectList())
		{
			if (m_pCollision_Manager->CollisionCheck(Target1->Get_Transform(), Target2->Get_Transform(), fTimeDelta, f1Scale, f2Scale))
			{
				return true;
			}
		}
	}
	return false;
}

int CGameInstance::Collision_Rect_Cube(_uint iLevelIndex, CTransform* p1Trans, _float3 vPos1, _float3 vPos2, _float fTimeDelta, _float3 fScale)
{
	if (nullptr == m_pObject_Manager ||
		nullptr == m_pCollision_Manager)
		return false;

	int iReturn = 0;

	if (m_pCollision_Manager->Collision_Rect_Cube(p1Trans,vPos1, vPos2, fTimeDelta, fScale))
	{
		iReturn = 1;
	}

	return iReturn;
}

bool CGameInstance::Collision_Attacked(_uint iLevelIndex, const _tchar * col1, const _tchar * col2, _float fTimeDelta, int ioption, _float3 f1Scale, _float3 f2Scale)
{
	if (nullptr == m_pObject_Manager ||
		nullptr == m_pCollision_Manager)
		return false;

	auto Col1Target = m_pObject_Manager->Find_Layer(iLevelIndex, col1);
	auto Col2Target = m_pObject_Manager->Find_Layer(iLevelIndex, col2);

	for (auto& Target1 : Col1Target->Get_ObjectList())
	{
		for (auto& Target2 : Col2Target->Get_ObjectList())
		{
			if (m_pCollision_Manager->CollisionCheck(Target1->Get_Transform(), Target2->Get_Transform(), fTimeDelta, f1Scale, f2Scale))
			{
				if (ioption == 0)
					Target1->Get_Transform()->Attacked_Move(Target2->Get_Transform()->Get_State(CTransform::STATE_POSITION), fTimeDelta);
				else if (ioption == 1)
					Target2->Set_Dead(true);
				else if (ioption == 2)
				{
					if (!Target2->Get_Hit())
					{
						Target1->Get_Transform()->Attacked_Move(Target2->Get_Transform()->Get_State(CTransform::STATE_POSITION), fTimeDelta);
						Target2->Set_Hit(true);
						Target2->Set_Hp(1);
					}
				}
				return true;
			}
		}
	}

	return false;
}

bool CGameInstance::Check_Layer(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (nullptr == m_pObject_Manager)
		return false;

	return m_pObject_Manager->Check_Layer(iLevelIndex, pLayerTag);
}

CLayer * CGameInstance::Find_Layer(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (nullptr == m_pObject_Manager)
		return false;

	return m_pObject_Manager->Find_Layer(iLevelIndex, pLayerTag);
}

HRESULT CGameInstance::Add_Prototype(_uint iLevelIndex, const _tchar * pPrototypeTag, CComponent * pPrototype)
{
	if (nullptr == m_pComponent_Manager)
		return E_FAIL;

	return m_pComponent_Manager->Add_Prototype(iLevelIndex, pPrototypeTag, pPrototype);
}

CComponent * CGameInstance::Clone_Component(_uint iLevelIndex, const _tchar * pPrototypeTag, void * pArg)
{
	if (nullptr == m_pComponent_Manager)
		return nullptr;

	return m_pComponent_Manager->Clone_Component(iLevelIndex, pPrototypeTag, pArg);
}

bool CGameInstance::Key_Pressing(int _Key)
{
	if (nullptr == m_pKey_Manager)
		return false;

	return m_pKey_Manager->Key_Pressing(_Key);
}

bool CGameInstance::Key_Up(int _Key)
{
	if (nullptr == m_pKey_Manager)
		return false;

	return m_pKey_Manager->Key_Up(_Key);
}

bool CGameInstance::Key_Down(int _Key)
{
	if (nullptr == m_pKey_Manager)
		return false;

	return m_pKey_Manager->Key_Down(_Key);
}

void CGameInstance::Release_Engine()
{
	CGameInstance::Get_Instance()->Destroy_Instance();

	CLevel_Manager::Get_Instance()->Destroy_Instance();

	CObject_Manager::Get_Instance()->Destroy_Instance();

	CCollisionMgr::Get_Instance()->Destroy_Instance();

	CComponent_Manager::Get_Instance()->Destroy_Instance();

	CTimer_Manager::Get_Instance()->Destroy_Instance();

	CInput_Device::Get_Instance()->Destroy_Instance();

	CKeyMgr::Get_Instance()->Destroy_Instance();

	CGraphic_Device::Get_Instance()->Destroy_Instance();
}

void CGameInstance::Free()
{
	Safe_Release(m_pKey_Manager);
	Safe_Release(m_pComponent_Manager);
	Safe_Release(m_pTimer_Manager);
	Safe_Release(m_pObject_Manager);
	Safe_Release(m_pLevel_Manager);
	Safe_Release(m_pInput_Device);
	Safe_Release(m_pCollision_Manager);
	Safe_Release(m_pGraphic_Device);


}
