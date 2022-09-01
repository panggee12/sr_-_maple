#include "stdafx.h"
#include "..\Public\YetiMonster.h"
#include "LupangSkill.h"

CYetiMonster::CYetiMonster(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CYetiMonster::CYetiMonster(const CYetiMonster & rhs)
	: CMonster(rhs)
{
}

HRESULT CYetiMonster::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CYetiMonster::Initialize(void * pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CYetiMonster::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	HitCheck(fTimeDelta);

}

void CYetiMonster::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CYetiMonster::Render()
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

HRESULT CYetiMonster::SetUp_Components()
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
	FrameTexture.EndFrame = 2;
	FrameTexture.FrameSpeed = 0.05f;

	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_YetiMonster"), (CComponent**)&m_pTextureCom, &FrameTexture)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Transform */
	CTransform::TRANSFORMDESC      TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(13.0f, 5.f, 13.0f));

	m_pTransformCom->Set_Scaled(_float3(-7.f, 7.f, 7.f));

	return S_OK;
}

HRESULT CYetiMonster::SetUp_RenderState()
{
	if (FAILED(__super::SetUp_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CYetiMonster::Release_RenderState()
{
	if (FAILED(__super::Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

void CYetiMonster::MonsterMove()
{
	if (m_bMotionCheck)
	{
		m_iTextureCount = 0.f;
		m_eState = STATE_ATTACK;

		_float fCurrentFrame = m_pTextureCom->m_FrameTexture.FirstFrame;

		if (fCurrentFrame >= 14 && fCurrentFrame < 14 + 0.05f)
		{
			CGameInstance* m_pGameInstance = CGameInstance::Get_Instance();
			Safe_AddRef(m_pGameInstance);

			_float3 vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

			if (FAILED(m_pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_YetiSkill"), LEVEL_GAMEPLAY, TEXT("Yeti_Skill"), &vPosition)))
				return;

			Safe_Release(m_pGameInstance);
		}

		if (m_pTextureCom->m_FrameTexture.FirstFrame >= 18)
			m_bMotionCheck = false;
	}

	if (!m_bMotionCheck)
	{
		_float3 vMyPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		_float3 vPlayerPosition = pPlayer->Get_Transform()->Get_State(CTransform::STATE_POSITION);

		_float fOriginYPos = vMyPosition.y;

		_float3 vLook = vPlayerPosition - vMyPosition;
		_float vLength = D3DXVec3Length(&vLook);


		if (vLength <= 5.f)
		{
			m_iTextureCount = 0.f;
			if (vMyPosition.x > vPlayerPosition.x)
			{
				if (m_pTransformCom->Get_ScaleX() < 0)
				{
					m_pTransformCom->Set_Scaled(_float3(-7.f, 7.f, 7.f));
				}
			}
			else if (vMyPosition.x < vPlayerPosition.x)
			{
				if (m_pTransformCom->Get_ScaleX() > 0)
				{
					m_pTransformCom->Set_Scaled(_float3(-7.f, 7.f, 7.f));
				}
			}

			m_pTextureCom->m_FrameTexture.FrameSpeed = 0.1f;
			m_pTextureCom->m_FrameTexture.FirstFrame = 10;
			m_pTextureCom->m_FrameTexture.OriginFrame = 10;
			m_pTextureCom->m_FrameTexture.EndFrame = 19;
			m_bMotionCheck = true;
		}

		else if (vLength <= 10.f)
		{
			m_iTextureCount = 0.f;
			if (vMyPosition.x > vPlayerPosition.x)
			{
				if (m_pTransformCom->Get_ScaleX() < 0)
				{
					m_pTransformCom->Set_Scaled(_float3(-7.f, 7.f, 7.f));
				}
			}
			else if (vMyPosition.x < vPlayerPosition.x)
			{
				if (m_pTransformCom->Get_ScaleX() > 0)
				{
					m_pTransformCom->Set_Scaled(_float3(-7.f, 7.f, 7.f));
				}
			}

			m_pTextureCom->m_FrameTexture.OriginFrame = 3;
			m_pTextureCom->m_FrameTexture.EndFrame = 6;
			m_pTextureCom->m_FrameTexture.FrameSpeed = 0.1f;

			D3DXVec3Normalize(&vLook, &vLook);

			vMyPosition = vMyPosition + vLook * 0.05f;

			m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(vMyPosition.x, fOriginYPos, vMyPosition.z));
		}
		else
		{
			m_iTextureCount += 0.1f;

			if (m_eState == STATE_ATTACK)
			{
				m_eState = STATE_IDLE;
				m_pTextureCom->m_FrameTexture.FirstFrame = 0;
				m_pTextureCom->m_FrameTexture.OriginFrame = 0;
				m_pTextureCom->m_FrameTexture.EndFrame = 2;
			}

			if (m_iTextureCount >= m_iTextureMaxCount)
			{
				m_iTextureCount = 0.f;
				m_iTextureMaxCount = rand() % 10 + 5;

				m_iUpDown++;

				if (m_iUpDown >= 3)
					m_iUpDown = 0;

				if (m_eState == STATE_LEFT)
				{
					m_pTextureCom->m_FrameTexture.FirstFrame = 0;
					m_pTextureCom->m_FrameTexture.OriginFrame = 0;
					m_pTextureCom->m_FrameTexture.EndFrame = 2;
					m_eState = STATE_IDLE;
				}

				else if (m_eState == STATE_IDLE)
				{
					m_pTextureCom->m_FrameTexture.FirstFrame = 3;
					m_pTextureCom->m_FrameTexture.OriginFrame = 3;
					m_pTextureCom->m_FrameTexture.EndFrame = 6;
					m_eState = STATE_LEFT;
					m_pTransformCom->Set_Scaled(_float3(-7.f, 7.f, 7.f));
				}
			}
		}
	}
}

void CYetiMonster::HitCheck(_float fTimeDelta)
{
	if (m_bHit)
	{
		m_bMotionCheck = false;
		if (m_iHp <= 0)
		{
			m_pTextureCom->m_FrameTexture.OriginFrame = 19;
			m_pTextureCom->m_FrameTexture.EndFrame = 25;
			m_pTextureCom->m_FrameTexture.FrameSpeed = 0.1f;

			if (m_pTextureCom->m_FrameTexture.FirstFrame >= 25.f)
			{
				CreateItem();
				m_bDead = true;
			}
		}
		else
		{
			if (m_eState != STATE_HIT)
				m_pTextureCom->m_FrameTexture.FirstFrame = 7;

			m_pTextureCom->m_FrameTexture.OriginFrame = 7;
			m_pTextureCom->m_FrameTexture.EndFrame = 9;
			m_pTextureCom->m_FrameTexture.FrameSpeed = 0.05f;
			m_eState = STATE_HIT;

			if (m_pTextureCom->m_FrameTexture.FirstFrame >= m_pTextureCom->m_FrameTexture.EndFrame)
				m_bHit = false;

			int a = 10;
		}
	}
	if (!m_bHit)
	{
		MonsterMove();

		if (!m_bMotionCheck)
		{
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
			else if (m_eState = STATE_IDLE)
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
}

void CYetiMonster::CreateItem()
{
	int iRand = rand() % 3 + 1;
<<<<<<< HEAD
=======

>>>>>>> aa192b3238a5dae7f5a2cf8c530fc184cccd860b
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

CYetiMonster * CYetiMonster::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CYetiMonster*	pInstance = new CYetiMonster(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CYetiMonster"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CYetiMonster::Clone(void * pArg)
{
	CYetiMonster*	pInstance = new CYetiMonster(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CYetiMonster"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CYetiMonster::Free()
{
	__super::Free();

}