#pragma once

#include "Base.h"
#include "Transform.h"
/* 게임객체들의 부모가되는 클래스다. */

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

	virtual void		Set_Hit(_bool bHit) { m_bHit = bHit; }
	virtual _bool		Get_Hit() { return m_bHit; }

	virtual void		Set_Hp(_int iAttack) { m_iHp -= iAttack; }
	virtual _int		Get_Hp() { return m_iHp; }

	virtual _int		Get_iAttack() { return m_iAttack; }

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
	_bool							m_bDead = false;
	_bool							m_bHit = false;
	_int								m_iHp = 5;
	_int								m_iAttack = 5;

public:	
	virtual CGameObject* Clone(void* pArg = nullptr) = 0;
	virtual void Free() override;
};

END

