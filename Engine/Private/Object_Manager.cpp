#include "..\Public\Object_Manager.h"
#include "Layer.h"


IMPLEMENT_SINGLETON(CObject_Manager)

CObject_Manager::CObject_Manager()
{
	m_pCollisionMgr = CCollisionMgr::Get_Instance();
	Safe_AddRef(m_pCollisionMgr);
}

HRESULT CObject_Manager::Reserve_Container(_uint iNumLevels)
{
	if (nullptr != m_pLayers)
		return E_FAIL;

	m_pLayers = new LAYERS[iNumLevels];

	m_iNumLevels = iNumLevels;

	return S_OK;
}

HRESULT CObject_Manager::Add_Prototype(const _tchar * pPrototypeTag, CGameObject * pPrototype)
{
	if (nullptr != Find_Prototype(pPrototypeTag))
		return E_FAIL;

	m_Prototypes.emplace(pPrototypeTag, pPrototype);	

	return S_OK;
}

HRESULT CObject_Manager::Add_GameObject(const _tchar * pPrototypeTag, _uint iLevelIndex, const _tchar * pLayerTag, void* pArg)
{
	CGameObject*		pPrototype = Find_Prototype(pPrototypeTag);
	if (nullptr == pPrototype)
		return E_FAIL;

	CGameObject*		pGameObject = pPrototype->Clone(pArg);
	if (nullptr == pGameObject)
		return E_FAIL;

	CLayer*			pLayer = Find_Layer(iLevelIndex, pLayerTag);

	if (nullptr == pLayer)
	{
		pLayer = CLayer::Create();
		pLayer->Add_GameObject(pGameObject);

		m_pLayers[iLevelIndex].emplace(pLayerTag, pLayer);
	}
	else
	{
		pLayer->Add_GameObject(pGameObject);
	}

	return S_OK;
}

void CObject_Manager::Tick(_float fTimeDelta)
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			Pair.second->Tick(fTimeDelta);			
		}
	}
}

void CObject_Manager::Late_Tick(_float fTimeDelta)
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			Pair.second->Late_Tick(fTimeDelta);
		}
	}
}

void CObject_Manager::Clear(_uint iLevelIndex)
{
	if (iLevelIndex >= m_iNumLevels || 
		nullptr == m_pLayers)
		return;

	for (auto& Pair : m_pLayers[iLevelIndex])	
		Safe_Release(Pair.second);

	m_pLayers[iLevelIndex].clear();
	
}

//bool CObject_Manager::Collision(_uint iLevelIndex, const _tchar * col1, const _tchar * col2,_float fTimeDelta, _float3 f1Scale, _float3 f2Scale)
//{
//	if (iLevelIndex >= m_iNumLevels)
//		return false;
//
//	auto iter1 = Find_Layer(iLevelIndex, col1);
//	auto iter2 = Find_Layer(iLevelIndex, col2);
//
//	for (auto& P1 : iter1->Get_ObjectList())
//	{
//		for (auto& P2 : iter2->Get_ObjectList())
//		{
//			if (m_pCollisionMgr->CollisionCheck(P1->Get_Transform(), P2->Get_Transform(), fTimeDelta, f1Scale, f2Scale))
//			{
//				return true;
//			}
//		}
//	}
//
//	return false;
//}
//
//bool CObject_Manager::Collision_Attacked(_uint iLevelIndex, const _tchar * col1, const _tchar * col2, _float fTimeDelta, int ioption, _float3 f1Scale, _float3 f2Scale)
//{
//	if (iLevelIndex >= m_iNumLevels)
//		return false;
//
//	auto iter1 = Find_Layer(iLevelIndex, col1);
//	auto iter2 = Find_Layer(iLevelIndex, col2);
//
//	for (auto& P1 : iter1->Get_ObjectList())
//	{
//		for (auto& P2 : iter2->Get_ObjectList())
//		{
//			if (m_pCollisionMgr->CollisionCheck(P1->Get_Transform(),P2->Get_Transform(),fTimeDelta,f1Scale,f2Scale))
//			{
//				if (ioption == 0)
//					P1->Get_Transform()->Attacked_Move(P2->Get_Transform()->Get_State(CTransform::STATE_POSITION), fTimeDelta);
//				else if (ioption == 1)
//					P2->Set_Dead(true);
//					return true;
//			}
//		}
//	}
//
//	return false;
//}
//
//int CObject_Manager::Collision_Rect_Cube(_uint iLevelIndex, const _tchar * col1, const _tchar * col2, _float fTimeDelta)
//{
//	if (iLevelIndex >= m_iNumLevels)
//		return false;
//
//	int iReturn = 0;
//
//	auto iter1 = Find_Layer(iLevelIndex, col1);
//	auto iter2 = Find_Layer(iLevelIndex, col2);
//
//	for (auto& P1 : iter1->Get_ObjectList())
//	{
//		for (auto& P2 : iter2->Get_ObjectList())
//		{
//			if (m_pCollisionMgr->Collision_Rect_Cube(P1->Get_Transform(), P2->Get_Transform(), fTimeDelta))
//			{
//				iReturn = 1;
//			}
//		}
//	}
//
//	return iReturn;
//}

CGameObject * CObject_Manager::Find_Target(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (iLevelIndex >= m_iNumLevels)
		return nullptr;

	auto	iter = find_if(m_pLayers[iLevelIndex].begin(), m_pLayers[iLevelIndex].end(), CTag_Finder(pLayerTag));
	if (iter == m_pLayers[iLevelIndex].end())
		return nullptr;

	return iter->second->Get_FirstObject();
}

CGameObject * CObject_Manager::Get_BackObject(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (iLevelIndex >= m_iNumLevels)
		return nullptr;

	auto	iter = find_if(m_pLayers[iLevelIndex].begin(), m_pLayers[iLevelIndex].end(), CTag_Finder(pLayerTag));
	if (iter == m_pLayers[iLevelIndex].end())
		return nullptr;

	return iter->second->Get_BackObject();
}

bool CObject_Manager::Check_Layer(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (iLevelIndex >= m_iNumLevels)
		return nullptr;

	auto	iter = find_if(m_pLayers[iLevelIndex].begin(), m_pLayers[iLevelIndex].end(), CTag_Finder(pLayerTag));
	if (iter->second->Get_ObjectList().empty())
		return false;

	return true;
}

CGameObject * CObject_Manager::Find_Prototype(const _tchar * pPrototypeTag)
{
	auto	iter = find_if(m_Prototypes.begin(), m_Prototypes.end(), CTag_Finder(pPrototypeTag));

	if (iter == m_Prototypes.end())
		return nullptr;

	return iter->second;
}

CLayer * CObject_Manager::Find_Layer(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (iLevelIndex >= m_iNumLevels)
		return nullptr;

	auto	iter = find_if(m_pLayers[iLevelIndex].begin(), m_pLayers[iLevelIndex].end(), CTag_Finder(pLayerTag));
	if (iter == m_pLayers[iLevelIndex].end())
		return nullptr;

	return iter->second;
}

void CObject_Manager::Free()
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])	
			Safe_Release(Pair.second);

		m_pLayers[i].clear();	
	}

	for (auto& Pair : m_Prototypes)
		Safe_Release(Pair.second);

	m_Prototypes.clear();

	Safe_Delete_Array(m_pLayers);

	Safe_Release(m_pCollisionMgr);
}
