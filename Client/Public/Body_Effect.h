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

class CBody_Effect final : public CGameObject
{
private:
	CBody_Effect(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBody_Effect(const CBody_Effect& rhs);
	virtual ~CBody_Effect() = default;

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
	_float					m_EffectFrame = 0.f;
	_float					m_Skill_Time_L = 0.f;
	CGameObject* pPlayer = nullptr;
	_float3					m_vEffectPos;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_RenderState();
	HRESULT Release_RenderState();

public:
	void LiteNing_Skill(_float _Player_Skill, _float fTimeDelta);
	void Fireball_Skill(_float _Player_Skill, _float fTimeDelta);
	/*void LiteNing_Skill(_float _Player_Skill, _float fTimeDelta);
	void LiteNing_Skill(_float _Player_Skill, _float fTimeDelta);
	*/

public:
	static CBody_Effect* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;
};

END