#pragma once

#include "Item.h"

BEGIN(Client)

class CConsumItem final : public CItem
{

private:
	CConsumItem(LPDIRECT3DDEVICE9 pGraphic_Device);
	CConsumItem(const CConsumItem& rhs);
	virtual ~CConsumItem() = default;

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

private:
	_float3 m_vPosition;
	_int	m_iTextureNum;
	_float m_iHeight = 0.1f;
	_int	m_bHeightCheck = 0;
public:
	static CConsumItem* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr);
	virtual void Free() override;
};

END