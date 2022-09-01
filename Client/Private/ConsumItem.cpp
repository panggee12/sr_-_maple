
#include "stdafx.h"
#include "..\Public\ConsumItem.h"

CConsumItem::CConsumItem(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CItem(pGraphic_Device)
{
}

CConsumItem::CConsumItem(const CConsumItem & rhs)
	: CItem(rhs)
{
}

HRESULT CConsumItem::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CConsumItem::Initialize(void * pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	memcpy(&m_vPosition, pArg, sizeof(_float3));

	m_iTextureNum = rand() % 6;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

void CConsumItem::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	_float3 vMyPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_float3 vPlayerPosition = pPlayer->Get_Transform()->Get_State(CTransform::STATE_POSITION);

	_float3 vLook = vPlayerPosition - vMyPosition;
	_float vLength = D3DXVec3Length(&vLook);

	if (vLength < 3.f)
	{
		m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta*2.f);

		D3DXVec3Normalize(&vLook, &vLook);
		vMyPosition = vMyPosition + vLook * 0.1f;

		if (m_iHeight == 20.f)
			m_bHeightCheck = 1;

		else if (m_iHeight == 0.f)
			m_bHeightCheck = 2;

		if (m_bHeightCheck == 0)
		{
			m_iHeight += 0.1f;
			vMyPosition.y += 0.1f;
		}
		else if(m_bHeightCheck == 1)
		{
			m_iHeight -= 0.1f;
			vMyPosition.y += 0.1f;
		}
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, vMyPosition);
	}

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	if (pGameInstance->Collision_Attacked(LEVEL_GAMEPLAY, TEXT("Layer_Player"), TEXT("ConsumItem"), fTimeDelta, 1, _float3(0.15f, 0.3f, 0.15f), _float3(0.3f, 0.3f, 0.3f)))
	{

	}

	Safe_Release(pGameInstance);
}

void CConsumItem::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CConsumItem::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;


	if (FAILED(m_pTextureCom->Bind_OnGraphicDev(m_iTextureNum)))
		return E_FAIL;
	
	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CConsumItem::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components()))
		return E_FAIL;


	CGameInstance* m_pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(m_pGameInstance);

	pPlayer = m_pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Player"));

	Safe_Release(m_pGameInstance);

	CTexture::FRAMETEXTURE		FrameTexture;
	ZeroMemory(&FrameTexture, sizeof(CTexture::FRAMETEXTURE));

	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_ConsumItem"), (CComponent**)&m_pTextureCom)))
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

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPosition);

	m_pTransformCom->Set_Scaled(_float3(1.f, 1.f, 1.f));

	return S_OK;
}

HRESULT CConsumItem::SetUp_RenderState()
{
	if (FAILED(__super::SetUp_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CConsumItem::Release_RenderState()
{
	if (FAILED(__super::Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

CConsumItem * CConsumItem::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CConsumItem*	pInstance = new CConsumItem(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CConsumItem"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CConsumItem::Clone(void * pArg)
{
	CConsumItem*	pInstance = new CConsumItem(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CConsumItem"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CConsumItem::Free()
{
	__super::Free();
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}