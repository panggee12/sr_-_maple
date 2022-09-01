#pragma once

#include "Monster.h"

BEGIN(Client)

class CBellaMonster final : public CMonster
{

private:
	CBellaMonster(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBellaMonster(const CBellaMonster& rhs);
	virtual ~CBellaMonster() = default;

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
<<<<<<< HEAD

=======
>>>>>>> aa192b3238a5dae7f5a2cf8c530fc184cccd860b
public:
	static CBellaMonster* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr);
	virtual void Free() override;
};

END