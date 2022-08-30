#pragma once

#include "Base.h"
#include "CollisionMgr.h"

/*  ������ ���ӿ�����Ʈ���� ��Ƽ� �����Ѵ�. : ����ڰ� ������ ���� ���ؿ� ����. */

BEGIN(Engine)

class CObject_Manager final : public CBase
{
	DECLARE_SINGLETON(CObject_Manager)
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	HRESULT Reserve_Container(_uint iNumLevels);
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObject(const _tchar* pPrototypeTag, _uint iLevelIndex, const _tchar* pLayerTag, void* pArg = nullptr);
	void Tick(_float fTimeDelta);
	void Late_Tick(_float fTimeDelta);
	void Clear(_uint iLevelIndex);
public:
	bool Collision(_uint iLevelIndex, const _tchar* col1, const _tchar* col2, _float fTimeDelta);
	bool Collision_Attacked(_uint iLevelIndex, const _tchar* col1, const _tchar* col2, _float fTimeDelta, int ioption);
	int Collision_Rect_Cube(_uint iLevelIndex, const _tchar* col1, const _tchar* col2, _float fTimeDelta);
	class CGameObject* Find_Target(_uint iLevelIndex, const _tchar* pLayerTag);
	class CGameObject* Get_BackObject(_uint iLevelIndex, const _tchar* pLayerTag);
private:
	map<const _tchar*, class CGameObject*>			m_Prototypes;
	typedef map<const _tchar*, class CGameObject*>	PROTOTYPES;

private: /* ���� �����ϰ� ���� ��� �׷��� ���� �������� ��ü�� �߰��Ѵ�. */	
	_uint										m_iNumLevels = 0;
	map<const _tchar*, class CLayer*>*			m_pLayers = nullptr;
	typedef map<const _tchar*, class CLayer*>	LAYERS;

private:
	class CGameObject* Find_Prototype(const _tchar* pPrototypeTag);
	class CLayer* Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag);

public:
	virtual void Free() override;
};

END