#pragma once

#include "Monster.h"

BEGIN(Client)

class CYetiMonster final : public CMonster
{

private:
	CYetiMonster(LPDIRECT3DDEVICE9 pGraphic_Device);
	CYetiMonster(const CYetiMonster& rhs);
	virtual ~CYetiMonster() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta)override;
	virtual void Late_Tick(_float fTimeDelta)override;
	virtual HRESULT Render() override;

protected:
	virtual HRESULT SetUp_Components();
	virtual HRESULT SetUp_RenderState();
	virtual HRESULT Release_RenderState();
	virtual void MonsterMove();
	virtual void HitCheck(_float fTimeDelta);
	virtual void CreateItem();


public:
	static CYetiMonster* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr);
	virtual void Free() override;
};

END