#include "stdafx.h"
#include "..\Public\Player_Attack.h"
#include "GameInstance.h"

CPlayer_Attack::CPlayer_Attack(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CPlayer_Attack::CPlayer_Attack(const CPlayer_Attack & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPlayer_Attack::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer_Attack
::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	memcpy(&m_vPosition, pArg, sizeof(_float3));

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

void CPlayer_Attack::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	_float3 vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	vPos = vPos + m_vMyLook * 0.1f;

	m_fDistance += 0.1f;

	if (m_fDistance >= 8.f)
		m_bDead = true;

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	/*if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Playe_Attack"), TEXT("Layer_Monster"), fTimeDelta, 1, _float3(0.15f, 0.3f, 0.15f), _float3(0.3f, 0.3f, 0.3f)))
	{

		Fire_Efect_On(TEXT("Layer_Attack"), fTimeDelta);
		m_bDead = true;

	}
*/
	if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Playe_Attack"), TEXT("Layer_MonkeyMonster"), fTimeDelta, 1, _float3(0.15f, 0.3f, 0.15f), _float3(0.3f, 0.3f, 0.3f)))
	{

		Fire_Efect_On(TEXT("Layer_Skill_Effect"), fTimeDelta);
		m_bDead = true;
		//if (m_Skill_Daed > 20.f)
		//{
		//	m_bDead = true;

		//}

		//Fire_Efect_On(TEXT("Layer_Attack"), fTimeDelta);
	}
	if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Playe_Attack"), TEXT("Layer_YetiMonster"), fTimeDelta, 1, _float3(0.15f, 0.3f, 0.15f), _float3(0.3f, 0.3f, 0.3f)))
	{

		Fire_Efect_On(TEXT("Layer_Skill_Effect"), fTimeDelta);
		m_bDead = true;
		//if (m_Skill_Daed > 20.f)
		//{
		//	m_bDead = true;

		//}

		//Fire_Efect_On(TEXT("Layer_Attack"), fTimeDelta);
	}

	if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Playe_Attack"), TEXT("Layer_BellaMonster"), fTimeDelta, 1, _float3(0.15f, 0.3f, 0.15f), _float3(0.3f, 0.3f, 0.3f)))
	{

		Fire_Efect_On(TEXT("Layer_Skill_Effect"), fTimeDelta);
		m_bDead = true;
	/*	if (m_Skill_Daed > 20.f)
		{
			m_bDead = true;

		}
*/
		//Fire_Efect_On(TEXT("Layer_Attack"), fTimeDelta);
	}

	Safe_Release(pGameInstance);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
}

void CPlayer_Attack::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CPlayer_Attack::Render()
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

HRESULT CPlayer_Attack::SetUp_Components()
{

	m_pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(m_pGameInstance);

	pPlayer = m_pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster"));

	Safe_Release(m_pGameInstance);

	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	CTexture::FRAMETEXTURE		FrameTexture;
	ZeroMemory(&FrameTexture, sizeof(CTexture::FRAMETEXTURE));
	FrameTexture.FirstFrame = 0;
	FrameTexture.OriginFrame = 0;
	FrameTexture.EndFrame = 15;
	FrameTexture.FrameSpeed = 0.1f;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack"), (CComponent**)&m_pTextureCom, &FrameTexture)))
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

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vMyPosition);

	m_pTransformCom->Set_Scaled(_float3(2.f, 2.f, 2.f));

	return S_OK;
}

HRESULT CPlayer_Attack::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 0);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	return S_OK;
}
HRESULT CPlayer_Attack::Fire_Efect_On(const _tchar * pLayerTag, _float fTimeDelta)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	_float3 vPos_Efect = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_Fire_Effect"), LEVEL_GAMEPLAY, pLayerTag, vPos_Efect)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	if (fTimeDelta > 0.2f)
	{
		__super::Free();
	}
	return S_OK;
}


HRESULT CPlayer_Attack::Release_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}

CPlayer_Attack * CPlayer_Attack::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPlayer_Attack*   pInstance = new CPlayer_Attack(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CPlayer_Attack"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPlayer_Attack::Clone(void* pArg)
{
	CPlayer_Attack*   pInstance = new CPlayer_Attack(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CPlayer_Attack"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayer_Attack::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}
