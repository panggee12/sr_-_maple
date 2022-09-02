#include "stdafx.h"
#include "..\Public\Player_Skill.h"
#include "GameInstance.h"

CPlayer_Skill::CPlayer_Skill(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CPlayer_Skill::CPlayer_Skill(const CPlayer_Skill & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPlayer_Skill::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer_Skill::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;


	m_fSizeX = 15.0f;
	m_fSizeY = 15.0f;
	m_fX = 10.f;
	m_fY = 10.f;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	//D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0.f, 1.f);

	memcpy(&m_vSkillPosition_2, pArg, sizeof(_float3));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vSkillPosition_2);

	//m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));

	return S_OK;
}

void CPlayer_Skill::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

<<<<<<< HEAD
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (!pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_Monster")))
	{
		m_bDead = true;
		Safe_Release(pGameInstance);
		return;
=======
	m_Skill_Daed += fTimeDelta + 0.2f;

	_float3 vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	vPos = vPos + m_vMyLook * 0.1f;

	m_fDistance += 0.1f;

	if (m_fDistance >= 8.f)
		m_bDead = true;

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Playe_Skill"), TEXT("Layer_Monster"), fTimeDelta, 1, _float3(0.15f, 0.3f, 0.15f), _float3(0.3f, 0.3f, 0.3f)))
	{

		Lite_Ning_Effect_On(TEXT("Layer_Skill_Effect"), fTimeDelta);

		if (m_Skill_Daed > 20.f)
		{
			m_bDead = true;

		}

		//Fire_Efect_On(TEXT("Layer_Attack"), fTimeDelta);
>>>>>>> BaeH
	}

	m_Skill_Time_L += fTimeDelta;

	m_fSkill_Frame += m_fSkill_Frame + 0.2f;

	if (m_fSkill_Frame <= 0 || m_fSkill_Frame >= 8)
	{
		m_fSkill_Frame = 0;

	}
	//_float MonsterPosx = Monster->CMonster::Get_Transform()->Get_State(CTransform::STATE_POSITION).x;
	//_float MonsterPosy = Monster->CMonster::Get_Transform()->Get_State(CTransform::STATE_POSITION).y;
	//_float MonsterPosz = Monster->CMonster::Get_Transform()->Get_State(CTransform::STATE_POSITION).z;


	if (m_Skill_Time_L > 0.5)
	{
		

		auto Player_Pos = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));

		_float3 TargetPos = Player_Pos->Get_Transform()->Get_State(CTransform::STATE_POSITION);

		_float3 MyPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

		_float3 Target = TargetPos - MyPos;

		MyPos += *D3DXVec3Normalize(&Target, &Target) * fTimeDelta*1.5;

		m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyPos);	
	}	

	if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Playe_Skill"), TEXT("Layer_Monster"), fTimeDelta, 1, _float3(0.1f, 0.1f, 0.1f), _float3(0.45f, 0.45f, 0.45f)))
	{
		m_bDead = true;
		Safe_Release(pGameInstance);
		return;
	}


	if (m_Skill_Time_L > 0.5)
	{
		CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		auto Player_Pos = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));

		_float3 TargetPos = Player_Pos->Get_Transform()->Get_State(CTransform::STATE_POSITION);

		_float3 MyPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);


		_float3 Target = TargetPos - MyPos;


		// _float3 Target ;


		MyPos += *D3DXVec3Normalize(&Target, &Target) * fTimeDelta*1.5;

		m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyPos);

		if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Monster"), TEXT("Layer_Playe_Skill"), fTimeDelta, 1, _float3(0.15f, 0.3f, 0.15f), _float3(0.3f, 0.3f, 0.3f)))
		{
		//	/*CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
		//	Safe_AddRef(pGameInstance);

		//	auto Player_Pos = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));




		//	Safe_Release(pGameInstance);*/

			Safe_Release(pGameInstance);
			//CPlayer_Skill::Free();

		}


		Safe_Release(pGameInstance);

	}
	
}

void CPlayer_Skill::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CPlayer_Skill::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;

	//_float4x4		ViewMatrix;
	//D3DXMatrixIdentity(&ViewMatrix);

	/*m_pGraphic_Device->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);*/

	if (FAILED(m_pTextureCom->Bind_OnGraphicDev(m_fSkill_Frame)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;



	return S_OK;
}

HRESULT CPlayer_Skill::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Skill_Litening"), (CComponent**)&m_pTextureCom)))
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

HRESULT CPlayer_Skill::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return S_OK;
}
<<<<<<< HEAD

HRESULT CPlayer_Skill::Release_RenderState()
{
	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	return S_OK;
}

HRESULT CPlayer_Skill::Efect_On(const _tchar * pLayerTag)
=======
HRESULT CPlayer_Litening::Lite_Ning_Effect_On(const _tchar * pLayerTag, _float fTimeDelta)
>>>>>>> BaeH
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	//pGameInstance->AddRef();

	_float3 vPosition_S = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

<<<<<<< HEAD
	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_Effect"), LEVEL_GAMEPLAY, pLayerTag, vPosition_S)))
=======
	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_Litenig_Effect"), LEVEL_GAMEPLAY, pLayerTag, vPos_Efect)))
>>>>>>> BaeH
		return E_FAIL;

	//m_fSkillTime = m_fSkillTime + 0.5f;

	auto Monster = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));



	Safe_Release(pGameInstance);
<<<<<<< HEAD
=======

	
>>>>>>> BaeH
	return S_OK;
}


CPlayer_Skill * CPlayer_Skill::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPlayer_Skill*	pInstance = new CPlayer_Skill(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CPlayer_Skill"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPlayer_Skill::Clone(void* pArg)
{
	CPlayer_Skill*	pInstance = new CPlayer_Skill(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CPlayer_Skill"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayer_Skill::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}
