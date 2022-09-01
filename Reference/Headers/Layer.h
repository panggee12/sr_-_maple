#pragma once

#include "GameObject.h"

/* ��ü���� ��� ���´�. */
BEGIN(Engine)

class CLayer final : public CBase
{
private:
	CLayer();
	virtual ~CLayer() = default;

public:
	HRESULT Initialize();
	HRESULT Add_GameObject(class CGameObject* pGameObject);
	void Tick(_float fTimeDelta);
	void Late_Tick(_float fTimeDelta);
public:
	list<class CGameObject*> Get_ObjectList() { return m_GameObjects; }
	class CGameObject* Get_FirstObject() { return m_GameObjects.front(); }
	class CGameObject* Get_BackObject() { return m_GameObjects.back(); }
private:
	list<class CGameObject*>			m_GameObjects;
	typedef list<class CGameObject*>	GAMEOBJECTS;

public:
	static CLayer* Create();
	virtual void Free() override;
};

END