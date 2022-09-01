#include "stdafx.h"
#include "..\Public\Skill.h"


CSkill::CSkill(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CSkill::CSkill(const CSkill & rhs)
	: CGameObject(rhs)
{
}

HRESULT CSkill::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSkill::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CSkill::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

}

void CSkill::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

}

HRESULT CSkill::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

}

void CSkill::MonsterMove()
{
}

HRESULT CSkill::SetUp_Components()
{

	return S_OK;
}

HRESULT CSkill::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 100);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	return S_OK;
}

HRESULT CSkill::Release_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}


void CSkill::Free()
{
	__super::Free();

	//Safe_Release(m_pTransformCom);
	//Safe_Release(m_pVIBufferCom);
	//Safe_Release(m_pRendererCom);
	//Safe_Release(m_pTextureCom);
}