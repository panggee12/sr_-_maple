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

class CMeteo_Effect final : public CGameObject
{
private:
	CMeteo_Effect(LPDIRECT3DDEVICE9 pGraphic_Device);
	CMeteo_Effect(const CMeteo_Effect& rhs);
	virtual ~CMeteo_Effect() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta)override;
	virtual void Late_Tick(_float fTimeDelta)override;
	virtual HRESULT Render() override;

private: /* For.Components */
	CTexture*				m_pTextureCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;

private:
	_float4x4				m_ProjMatrix;
	_float					m_fX, m_fY, m_fSizeX, m_fSizeY;
<<<<<<< HEAD:Client/Public/Meteo_Effect.h
	_float					m_EffectFrame = 0.f;
	_float					m_Skill_Time_L = 0.f;
=======
	_uint					m_iIconNum = 0;
	_bool					m_bOnCheck = false;
	_bool					m_bMoveUi = false;
	_float2					m_fMousePos;
	_float2					m_fDifDis;
	RECT					m_rcRect;
	_bool					m_bRectInCheck = false;
	_bool					m_bCheckIn = false;
>>>>>>> 763671df696a78e2247104d8f8547f8d45e72ab2:Client/Public/IconUI.h

	_float3					m_vEffectPos;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_RenderState();
	HRESULT Release_RenderState();


public:
	static CMeteo_Effect* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;
};

END