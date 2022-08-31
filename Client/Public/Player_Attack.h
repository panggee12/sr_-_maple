#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "GameInstance.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CPlayer_Attack final : public CGameObject
{
	enum STATE { STATE_IDLE, STATE_LEFT, STATE_RIGHT, STATE_ATTACK, STATE_END };

private:
	CPlayer_Attack(LPDIRECT3DDEVICE9 pGraphic_Device);
	CPlayer_Attack(const CPlayer_Attack& rhs);
	virtual ~CPlayer_Attack() = default;

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
	_float3 m_vMyLook;
	_float	m_fDistance = 0.f;

public:
	virtual HRESULT SetUp_Components();
	virtual HRESULT SetUp_RenderState();
	HRESULT Fire_Efect_On(const _tchar * pLayerTag, _float fTimeDelta);
	virtual HRESULT Release_RenderState();

public:
	static CPlayer_Attack* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;
};

END




//#pragma once

//
//#include "Client_Defines.h"
//#include "GameObject.h"
//
//BEGIN(Engine)
//class CTexture;
//class CRenderer;
//class CTransform;
//class CVIBuffer_Rect;
//END
//
//BEGIN(Client)
//
//class CPlayer_Attack final : public CGameObject
//{
//private:
//	CPlayer_Attack(LPDIRECT3DDEVICE9 pGraphic_Device);
//	CPlayer_Attack(const CPlayer_Attack& rhs);
//	virtual ~CPlayer_Attack() = default;
//
//public:
//	virtual HRESULT Initialize_Prototype() override;
//	virtual HRESULT Initialize(void* pArg)override;
//	virtual void Tick(_float fTimeDelta)override;
//	virtual void Late_Tick(_float fTimeDelta)override;
//	virtual HRESULT Render() override;
//
//private: /* For.Components */
//	CTexture*				m_pTextureCom = nullptr;
//	CRenderer*				m_pRendererCom = nullptr;
//	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;
//
//private:
//	_float4x4				m_ProjMatrix;
//	_float					m_fX, m_fY, m_fSizeX, m_fSizeY;
//	_float					m_fAttack_Frame = 0.f;
//	_float					m_SkillTime = 0.f;
//
//	_float3					m_vSkillPosition;
//
//private:
//	HRESULT SetUp_Components();
//	HRESULT SetUp_RenderState();
//	HRESULT Release_RenderState();
//	HRESULT Fire_Efect_On(const _tchar * pLayerTag, _float fTimeDelta);
//
//
//public:
//	static CPlayer_Attack* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
//	virtual CGameObject* Clone(void* pArg = nullptr) override;
//	virtual void Free() override;
//};
//
//END