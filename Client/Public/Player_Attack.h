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

class CPlayer_Attack final : public CGameObject
{
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
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;

private:
	_float4x4				m_ProjMatrix;
	_float					m_fX, m_fY, m_fSizeX, m_fSizeY;
	_float					m_fAttack_Frame = 0.f;
	_float					m_SkillTime = 0.f;
<<<<<<< .merge_file_hZSdy5

	_float3					m_vSkillPosition;

=======
	CGameObject*			m_pTarget=nullptr;
	_float3					m_vPosition;

>>>>>>> .merge_file_PUopjQ
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_RenderState();
	HRESULT Release_RenderState();
	HRESULT Fire_Efect_On(const _tchar * pLayerTag, _float fTimeDelta);


public:
	static CPlayer_Attack* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;
};

END