#include "stdafx.h"
#include "..\Public\Effect.h"
#include "GameInstance.h"

CEffect::CEffect(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CEffect::CEffect(const CEffect & rhs)
	: CGameObject(rhs)
{
}

HRESULT CEffect::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CEffect::Initialize(void* pArg)
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

void CEffect::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	//m_Skill_Time_L += fTimeDelta;

	m_EffectFrame += m_EffectFrame + 0.2f;

	if (m_EffectFrame <= 0 || m_EffectFrame >= 4)
	{
		m_EffectFrame = 0;

	}
	//_float MonsterPosx = Monster->CMonster::Get_Transform()->Get_State(CTransform::STATE_POSITION).x;
	//_float MonsterPosy = Monster->CMonster::Get_Transform()->Get_State(CTransform::STATE_POSITION).y;
	//_float MonsterPosz = Monster->CMonster::Get_Transform()->Get_State(CTransform::STATE_POSITION).z;


	//if (m_Skill_Time_L > 0.5)
	//{
	//	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	//	Safe_AddRef(pGameInstance);

	//	auto Player_Pos = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));

	//	_float3 TargetPos = Player_Pos->Get_Transform()->Get_State(CTransform::STATE_POSITION);

	//	_float3 MyPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);


	//	_float3 Target = TargetPos - MyPos;


	//	// _float3 Target ;


	//	MyPos += *D3DXVec3Normalize(&Target, &Target) * fTimeDelta*1.5;

	//	m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
	//	m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyPos);

	//	if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Monster"), TEXT("Layer_Playe_Skill"), fTimeDelta, 1))
	//	{

	//	}


	//	Safe_Release(pGameInstance);

	//}

}

void CEffect::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CEffect::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;

	//_float4x4		ViewMatrix;
	//D3DXMatrixIdentity(&ViewMatrix);

	/*m_pGraphic_Device->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);*/

	if (FAILED(m_pTextureCom->Bind_OnGraphicDev(m_EffectFrame)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;



	return S_OK;
}

HRESULT CEffect::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Skill_Effect"), (CComponent**)&m_pTextureCom)))
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

HRESULT CEffect::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return S_OK;
}

HRESULT CEffect::Release_RenderState()
{
	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	return S_OK;
}

CEffect * CEffect::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CEffect*	pInstance = new CEffect(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CEffect::Clone(void* pArg)
{
	CEffect*	pInstance = new CEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CEffect::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}