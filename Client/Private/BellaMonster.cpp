#include "stdafx.h"
#include "..\Public\BellaMonster.h"

CBellaMonster::CBellaMonster(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CBellaMonster::CBellaMonster(const CBellaMonster & rhs)
	: CMonster(rhs)
{
}

HRESULT CBellaMonster::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBellaMonster::Initialize(void * pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CBellaMonster::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	HitCheck(fTimeDelta);
}

void CBellaMonster::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CBellaMonster::Render()
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

HRESULT CBellaMonster::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components()))
		return E_FAIL;


	CGameInstance* m_pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(m_pGameInstance);

	pPlayer = m_pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Player"));

	Safe_Release(m_pGameInstance);

	CTexture::FRAMETEXTURE		FrameTexture;
	ZeroMemory(&FrameTexture, sizeof(CTexture::FRAMETEXTURE));
	FrameTexture.FirstFrame = 0;
	FrameTexture.OriginFrame = 0;
	FrameTexture.EndFrame = 3;
	FrameTexture.FrameSpeed = 0.05f;

	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_BellaMonster"), (CComponent**)&m_pTextureCom, &FrameTexture)))
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

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(5.0f, 2.5f, 1.0f));

	m_pTransformCom->Set_Scaled(_float3(-2.f, 2.f, 2.f));

	return S_OK;
}

HRESULT CBellaMonster::SetUp_RenderState()
{
	if (FAILED(__super::SetUp_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBellaMonster::Release_RenderState()
{
	if (FAILED(__super::Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

void CBellaMonster::MonsterMove()
{
	m_iTextureCount += 0.1f;

	if (m_iTextureCount >= m_iTextureMaxCount)
	{
		m_iTextureCount = 0.f;
		m_iTextureMaxCount = rand() % 10 + 5;

		m_iUpDown++;

		if (m_iUpDown >= 3)
			m_iUpDown = 0;

		if (m_eState == STATE_LEFT || m_eState == STATE_HIT)
		{
			m_pTextureCom->m_FrameTexture.FirstFrame = 0;
			m_pTextureCom->m_FrameTexture.OriginFrame = 0;
			m_pTextureCom->m_FrameTexture.EndFrame = 3;
			m_eState = STATE_IDLE;
		}

		else if (m_eState == STATE_IDLE)
		{
			m_pTextureCom->m_FrameTexture.FirstFrame = 4;
			m_pTextureCom->m_FrameTexture.OriginFrame = 4;
			m_pTextureCom->m_FrameTexture.EndFrame = 7;
			m_eState = STATE_LEFT;
			m_pTransformCom->Set_Scaled(_float3(-2.f, 2.f, 2.f));
		}
	}

}

void CBellaMonster::HitCheck(_float fTimeDelta)
{

	if (m_bHit)
	{
		if (m_iHp <= 0)
		{
			m_pTextureCom->m_FrameTexture.OriginFrame = 8;
			m_pTextureCom->m_FrameTexture.EndFrame = 14;
			m_pTextureCom->m_FrameTexture.FrameSpeed = 0.1f;

			if (m_pTextureCom->m_FrameTexture.FirstFrame >= 14.f)
			{
				CreateItem();
				m_bDead = true;
			}
		}
		else
		{
			if (m_eState != STATE_HIT)
				m_pTextureCom->m_FrameTexture.FirstFrame = 8;

			m_pTextureCom->m_FrameTexture.OriginFrame = 8;
			m_pTextureCom->m_FrameTexture.EndFrame = 10;
			m_pTextureCom->m_FrameTexture.FrameSpeed = 0.05f;
			m_eState = STATE_HIT;

			if (m_pTextureCom->m_FrameTexture.FirstFrame >= m_pTextureCom->m_FrameTexture.EndFrame)
				m_bHit = false;
		}
	}
	if (!m_bHit)
	{
		MonsterMove();

		if (m_eState == STATE_LEFT)
		{
			if (m_iUpDown == 0)
			{
				m_pTransformCom->Go_Left(fTimeDelta);
			}
			else if (m_iUpDown == 1)
			{
				m_pTransformCom->Go_Left(fTimeDelta * 0.5f);
				m_pTransformCom->Go_Straight(fTimeDelta * 0.5f);
			}
			else if (m_iUpDown == 2)
			{
				m_pTransformCom->Go_Left(fTimeDelta * 0.5f);
				m_pTransformCom->Go_Backward(fTimeDelta * 0.5f);
			}
		}
	}
}

void CBellaMonster::CreateItem()
{
	
	int iRand = rand() % 3 + 1;

	if (iRand == 1)
	{
	
	CGameInstance* m_pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(m_pGameInstance);

	_float3 vScale = m_pTransformCom->Get_Scale();
	_float3 vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	vPosition.y -= vScale.y * 0.5f;

	if (FAILED(m_pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_ConsumItem"), LEVEL_GAMEPLAY, TEXT("ConsumItem"), &vPosition)))
		return;

	Safe_Release(m_pGameInstance);
	}
}

CBellaMonster * CBellaMonster::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBellaMonster*	pInstance = new CBellaMonster(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CBellaMonster"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBellaMonster::Clone(void * pArg)
{
	CBellaMonster*	pInstance = new CBellaMonster(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CBellaMonster"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBellaMonster::Free()
{
	__super::Free();
}