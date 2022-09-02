#include "stdafx.h"
#include "..\Public\Skill_Meteo.h"
#include"Meteo_Effect.h"

CMeteo_Skill::CMeteo_Skill(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CSkill(pGraphic_Device)
{
}

CMeteo_Skill::CMeteo_Skill(const CMeteo_Skill & rhs)
	: CSkill(rhs)
{
}

HRESULT CMeteo_Skill::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMeteo_Skill::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	memcpy(&m_vPosition, pArg, sizeof(_float3));

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

void CMeteo_Skill::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_Skil_DaedTime += fTimeDelta + 0.1f;
	_float3 vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	vPos = vPos + m_vMyLook * 0.1f;

	//m_fDistance += 0.1f;

	//if (m_fDistance >= 8.f)
	//	m_bDead = true;

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Playe_Skill_Meteor"), TEXT("Layer_Monster"), fTimeDelta, 1, _float3(0.15f, 0.3f, 0.15f), _float3(0.3f, 0.3f, 0.3f)))
	{
		m_bDead = true;
		
		Fire_Efect_On(TEXT("Layer_Attack"), fTimeDelta);
		
		Meteor_Fire_Efect_On(TEXT("Layer_Playe_Skill_Meteor_Effect"), fTimeDelta);
		Meteor_Fire_Efect_On(TEXT("Layer_Playe_Skill_Meteor"), fTimeDelta);

	}
	if (m_Skil_DaedTime > 15.f)
	{
		m_bDead = true;

	}
	
	Safe_Release(pGameInstance);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
}

void CMeteo_Skill::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CMeteo_Skill::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;

	m_pTextureCom->Bind_FrameMove();

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMeteo_Skill::SetUp_Components()
{

	m_pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(m_pGameInstance);

	pPlayer = m_pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));

	Safe_Release(m_pGameInstance);

	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	CTexture::FRAMETEXTURE		FrameTexture;
	ZeroMemory(&FrameTexture, sizeof(CTexture::FRAMETEXTURE));
	FrameTexture.FirstFrame = 0;
	FrameTexture.OriginFrame = 0;
	FrameTexture.EndFrame = 5;
	FrameTexture.FrameSpeed = 0.1f;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Skill_Meteo"), (CComponent**)&m_pTextureCom, &FrameTexture)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Transform */
	CTransform::TRANSFORMDESC      TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 3.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_vPosition.x, m_vPosition.y, m_vPosition.z));

	_float3 vMyPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_float3 vPlayerPosition = pPlayer->Get_Transform()->Get_State(CTransform::STATE_POSITION);


	m_vMyLook = vPlayerPosition - vMyPosition;

	D3DXVec3Normalize(&m_vMyLook, &m_vMyLook);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_vPosition.x, m_vPosition.y+3.f, m_vPosition.z));

	m_pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(m_pGameInstance);
	pPlayer= m_pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Player"));

	if (vPlayerPosition.x >=m_vMyLook.x)
	{

		m_pTransformCom->Set_Scaled(_float3(5.f* -1, 3.5f, 0.f));

	}
	if (vPlayerPosition.y >= m_vMyLook.y&&vPlayerPosition.x <= m_vMyLook.x
		|| vPlayerPosition.y >= m_vMyLook.y&&vPlayerPosition.x >= m_vMyLook.x)
	{
		m_vMyLook.y -= 0.2f;
		//m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_vMyLook.x, m_vMyLook.y, m_vMyLook.z));
	}


	m_pTransformCom->Set_Scaled(_float3(5.f, 3.5f, 0.f));



	return S_OK;
}

HRESULT CMeteo_Skill::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 100);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	//m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	return S_OK;
}

HRESULT CMeteo_Skill::Fire_Efect_On(const _tchar * pLayerTag, _float fTimeDelta)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	_float3 vPos_Efect = m_pTransformCom->Get_State(CTransform::STATE_POSITION);


	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_Fire_Effect"), LEVEL_GAMEPLAY, pLayerTag, _float3(vPos_Efect.x, vPos_Efect.y, vPos_Efect.z))))
		return E_FAIL;

	Safe_Release(pGameInstance);

	/*if (fTimeDelta > 0.2f)
	{
	__super::Free();
	}*/
	return S_OK;
}

HRESULT CMeteo_Skill::Meteor_Fire_Efect_On(const _tchar * pLayerTag, _float fTimeDelta)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	_float3 vPos_Efect = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	
	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_Meteor_Effect"), LEVEL_GAMEPLAY, pLayerTag, _float3(vPos_Efect.x, vPos_Efect.y-2.f, vPos_Efect.z)
	)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	/*if (fTimeDelta > 0.2f)
	{
	__super::Free();
	}*/
	return S_OK;
}


HRESULT CMeteo_Skill::Release_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}

CMeteo_Skill * CMeteo_Skill::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CMeteo_Skill*   pInstance = new CMeteo_Skill(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CMeteo_Skill"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMeteo_Skill::Clone(void* pArg)
{
	CMeteo_Skill*   pInstance = new CMeteo_Skill(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CMeteo_Skill"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMeteo_Skill::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}

