#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CItemInfoUI final : public CGameObject
{
private:
	CItemInfoUI(LPDIRECT3DDEVICE9 pGraphic_Device);
	CItemInfoUI(const CItemInfoUI& rhs);
	virtual ~CItemInfoUI() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta)override;
	virtual void Late_Tick(_float fTimeDelta)override;
	virtual HRESULT Render() override;

public:
	void		Set_QuickItem() { m_iCheck++; }//아이템 충돌 변환 체크용 
	void		Use_Item();

private: /* For.Components */
	CTexture*				m_pTextureCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;

private:
	_float4x4						m_ProjMatrix;
	_float							m_fX, m_fY, m_fSizeX, m_fSizeY;	
	QUICK_ITEM						m_eQuick_Item = Quick_Normal;
	_uint							m_iCheck = 0;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_RenderState();
	HRESULT Release_RenderState();

public:
	static CItemInfoUI* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;
};

END