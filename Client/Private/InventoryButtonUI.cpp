#include "stdafx.h"
#include "InventoryButtonUI.h"
#include "GameInstance.h"
#include "Loader.h"

CInventoryButtonUI::CInventoryButtonUI(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CInventoryButtonUI::CInventoryButtonUI(const CInventoryButtonUI & rhs)
	: CGameObject(rhs)
{
}

HRESULT CInventoryButtonUI::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CInventoryButtonUI::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0.f, 1.f);

	m_fSizeX = 66.f;
	m_fSizeY = 66.f;
	m_fX = 640.f;
	m_fY = 600.f;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.f));

	return S_OK;
}

void CInventoryButtonUI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);	
}

void CInventoryButtonUI::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
}

HRESULT CInventoryButtonUI::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	
	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;

	_float4x4		ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);
	
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	if (FAILED(m_pTextureCom->Bind_OnGraphicDev(0)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;



	return S_OK;
}

HRESULT CInventoryButtonUI::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_GamePlay_UI"), (CComponent**)&m_pTextureCom)))
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

HRESULT CInventoryButtonUI::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;	

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 250);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	return S_OK;
}

HRESULT CInventoryButtonUI::Release_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}

CInventoryButtonUI * CInventoryButtonUI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CInventoryButtonUI*	pInstance = new CInventoryButtonUI(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CInventoryButtonUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CInventoryButtonUI::Clone(void* pArg)
{
	CInventoryButtonUI*	pInstance = new CInventoryButtonUI(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CInventoryButtonUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CInventoryButtonUI::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}