#include "..\Public\Layer.h"


CLayer::CLayer()
{
}

HRESULT CLayer::Initialize()
{
	return S_OK;
}

HRESULT CLayer::Add_GameObject(CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_GameObjects.push_back(pGameObject);

	return S_OK;
}

void CLayer::Tick(_float fTimeDelta)
{
	for (auto& pGameObject : m_GameObjects)
	{
		if (nullptr != pGameObject)
			pGameObject->Tick(fTimeDelta);
	}
}

void CLayer::Late_Tick(_float fTimeDelta)
{
	for (auto& pGameObject = m_GameObjects.begin(); pGameObject != m_GameObjects.end();)
	{
		if ((*pGameObject)->Get_Dead())
		{
			Safe_Release(*pGameObject);
			pGameObject = m_GameObjects.erase(pGameObject);
		}
		else if(nullptr != *pGameObject&&!(*pGameObject)->Get_Dead())
		{
			(*pGameObject)->Late_Tick(fTimeDelta);
			++pGameObject;
		}
	}
}

CLayer * CLayer::Create()
{
	CLayer*	pInstance = new CLayer();

	if (FAILED(pInstance->Initialize()))
	{
		ERR_MSG(TEXT("Failed to Created : CLayer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLayer::Free()
{
	for (auto& pGameObject : m_GameObjects)
		Safe_Release(pGameObject);

	m_GameObjects.clear();
}

