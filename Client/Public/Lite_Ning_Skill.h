#pragma once

#include "Skill.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CLite_Ning_Skill final : public CSkill
{
	enum STATE { STATE_IDLE, STATE_LEFT, STATE_RIGHT, STATE_ATTACK, STATE_END };

private:
	CLite_Ning_Skill(LPDIRECT3DDEVICE9 pGraphic_Device);
	CLite_Ning_Skill(const CLite_Ning_Skill& rhs);
	virtual ~CLite_Ning_Skill() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta)override;
	virtual void Late_Tick(_float fTimeDelta)override;
	virtual HRESULT Render() override;

private: /* For.Components */
	CTexture*				m_pTextureCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CVIBuffer_Rect*	m_pVIBufferCom = nullptr;
	CGameInstance*	m_pGameInstance = nullptr;

private:
	STATE m_eState = STATE_IDLE;
	STATE m_ePrevState = STATE_IDLE;
	_float m_iTextureCount = 0.f;
	_float m_iTextureMaxCount = 10.f;
	_bool m_bChase = false;
	CGameObject* pPlayer = nullptr;

	_bool m_bMotionCheck = false;
	_float3 m_vPosition;
	_float3 m_vTartget_Monster;
	_float3 m_vMyLook;
	_float	m_fDistance = 0.f;
	_float  m_Skill_Daed = 0.f;


public:
	virtual HRESULT SetUp_Components();
	virtual HRESULT SetUp_RenderState();
	HRESULT Lite_Ning_Effect_On(const _tchar * pLayerTag, _float fTimeDelta);
	virtual HRESULT Release_RenderState();

public:
	static CLite_Ning_Skill* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;
};

END
