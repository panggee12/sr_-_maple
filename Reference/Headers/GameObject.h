#pragma once

#include "Base.h"
#include "Transform.h"
/* ���Ӱ�ü���� �θ𰡵Ǵ� Ŭ������. */

BEGIN(Engine)

class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	CGameObject(const CGameObject& rhs);
	virtual ~CGameObject() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void Late_Tick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	virtual CTransform* Get_Transform() { return m_pTransformCom; }
	virtual void		Set_Dead(_bool bDead) { m_bDead = bDead; }
	virtual _bool		Get_Dead() { return m_bDead; }
protected:
	LPDIRECT3DDEVICE9			m_pGraphic_Device = nullptr;

protected:
	map<const _tchar*, class CComponent*>				m_Components;

protected:
	HRESULT Add_Components(const _tchar* pComponentTag, _uint iLevelIndex, const _tchar* pPrototypeTag, CComponent** ppOut, void* pArg = nullptr);

protected:
	class CComponent* Find_Component(const _tchar* pComponentTag);

protected:
	CTransform*				m_pTransformCom = nullptr;
	_bool					m_bDead = false;

public:	
	virtual CGameObject* Clone(void* pArg = nullptr) = 0;
	virtual void Free() override;
};

END

