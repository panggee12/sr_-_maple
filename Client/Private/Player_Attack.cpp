#include "stdafx.h"
#include "..\Public\Player_Attack.h"
#include "GameInstance.h"
<<<<<<< HEAD
#include "Player.h"
=======
>>>>>>> e8a7accc92a0666938010f64fe805e1f1445c9cf

CPlayer_Attack::CPlayer_Attack(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CPlayer_Attack::CPlayer_Attack(const CPlayer_Attack & rhs)
	: CGameObject(rhs)
{
<<<<<<< HEAD
} 
=======
}
>>>>>>> e8a7accc92a0666938010f64fe805e1f1445c9cf

HRESULT CPlayer_Attack::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer_Attack::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

<<<<<<< HEAD
	//memcpy(&m_vSkillPosition, pArg, sizeof(_float3));

	//D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0.f, 1.f);
	
	m_fSizeX = 1.1f;
	m_fSizeY = 1.1f;
	m_fX = 1.f;
	m_fY = -4.f;
=======
	memcpy(&m_vPosition, pArg, sizeof(_float3));
>>>>>>> e8a7accc92a0666938010f64fe805e1f1445c9cf

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

	if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Playe_Attack"), TEXT("Layer_Monster"), fTimeDelta, 1, _float3(0.15f, 0.3f, 0.15f), _float3(0.3f, 0.3f, 0.3f)))
	{

		Fire_Efect_On(TEXT("Layer_Attack"), fTimeDelta);
		m_bDead = true;
<<<<<<< HEAD
		Safe_Release(pGameInstance);
		return;
	}

	m_SkillTime += m_SkillTime+fTimeDelta+0.2f;


	m_fAttack_Frame = m_fAttack_Frame + 0.2f;

	if (m_fAttack_Frame <= 0 || m_fAttack_Frame >= 8)
	{
		m_fAttack_Frame = 0;
	}

	if (m_SkillTime > 0.3f)
	{
		auto Player_Pos = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));

		_float3 TargetPos = Player_Pos->Get_Transform()->Get_State(CTransform::STATE_POSITION);

		_float3 MyPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

		_float3 Target = TargetPos - MyPos;

		MyPos += *D3DXVec3Normalize(&Target, &Target) * fTimeDelta*10.5;

		m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyPos);

		if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Playe_Attack"), TEXT("Layer_Monster"), fTimeDelta, 1 ,_float3(0.15f, 0.3f, 0.15f), _float3(0.3f, 0.3f, 0.3f)))
		{
			Fire_Efect_On(TEXT("Layer_Attack"), fTimeDelta);
			m_bDead = true;
			Safe_Release(pGameInstance);
			return;
		}
		
	}

 if (m_SkillTime >= 2.5f)
	{
		m_SkillTime = 0.f;

	}

	m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
=======

	}

>>>>>>> e8a7accc92a0666938010f64fe805e1f1445c9cf
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

	pPlayer = m_pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));

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
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 0);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
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
