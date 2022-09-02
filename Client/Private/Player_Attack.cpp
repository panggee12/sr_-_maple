#include "stdafx.h"
#include "..\Public\Player_Attack.h"
#include "GameInstance.h"
#include "Player.h"
#include "Monster.h"

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


	//memcpy(&m_vSkillPosition, pArg, sizeof(_float3));

	//D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0.f, 1.f);



	
	m_fSizeX = 1.1f;
	m_fSizeY = 1.1f;
	m_fX = 1.f;
	m_fY = -4.f;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_vSkillPosition, pArg, sizeof(_float3));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vSkillPosition);

	return S_OK;
}

void CPlayer_Attack::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (!pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster")))
	{
		m_bDead = true;
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
		auto Player_Pos = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster"));


		_float3 TargetPos = Player_Pos->Get_Transform()->Get_State(CTransform::STATE_POSITION);

		_float3 MyPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);


		_float3 Target = TargetPos - MyPos;

		MyPos += *D3DXVec3Normalize(&Target, &Target) * fTimeDelta*10.5;

		m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyPos);

		if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Playe_Attack"), TEXT("Layer_MonkeyMonster"), fTimeDelta, 2 ,_float3(0.15f, 0.3f, 0.15f), _float3(0.3f, 0.3f, 0.3f)))
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
	Safe_Release(pGameInstance);
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

	if (FAILED(m_pTextureCom->Bind_OnGraphicDev(m_fAttack_Frame)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;



	return S_OK;
}

HRESULT CPlayer_Attack::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack"), (CComponent**)&m_pTextureCom)))
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

HRESULT CPlayer_Attack::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
<<<<<<< HEAD
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 250);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

=======
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 0);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
>>>>>>> BaeH
	return S_OK;
}

HRESULT CPlayer_Attack::Release_RenderState()
{
	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

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



CPlayer_Attack * CPlayer_Attack::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPlayer_Attack*	pInstance = new CPlayer_Attack(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CPlayer_Attack"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPlayer_Attack::Clone(void* pArg)
{
	CPlayer_Attack*	pInstance = new CPlayer_Attack(*this);

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

	//Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}
