#include "stdafx.h"
#include "..\Public\Litening_Effect.h"
#include "GameInstance.h"

CLitening_Effect::CLitening_Effect(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CLitening_Effect::CLitening_Effect(const CLitening_Effect & rhs)
	: CGameObject(rhs)
{
}

HRESULT CLitening_Effect::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CLitening_Effect::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;


	m_fSizeX = 15.0f;
	m_fSizeY = 15.0f;
	/*m_fX = 10.f;
	m_fY = 10.f;*/

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_vEffectPos, pArg, sizeof(_float3));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vEffectPos);

	//m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));

	//m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));

	return S_OK;
}

void CLitening_Effect::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	//m_Skill_Time_L += fTimeDelta;

	m_EffectFrame += fTimeDelta + 0.2f;

	if (m_EffectFrame <= 0 || m_EffectFrame >= 4)
	{
		m_EffectFrame = 0;

	}
	if (m_EffectFrame == 4)
	{
		Free();
	}

	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);



}

void CLitening_Effect::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CLitening_Effect::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;



	if (FAILED(m_pTextureCom->Bind_OnGraphicDev(m_EffectFrame)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;



	return S_OK;
}

HRESULT CLitening_Effect::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_LiteNing_Effect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;


	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;


	return S_OK;
}

HRESULT CLitening_Effect::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return S_OK;
}

HRESULT CLitening_Effect::Release_RenderState()
{
	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	return S_OK;
}

CLitening_Effect * CLitening_Effect::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLitening_Effect*	pInstance = new CLitening_Effect(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CLitening_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CLitening_Effect::Clone(void* pArg)
{
	CLitening_Effect*	pInstance = new CLitening_Effect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CLitening_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLitening_Effect::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}
