#include "stdafx.h"
#include "IconUI.h"
#include "GameInstance.h"
#include "InventoryUI.h"

CIconUI::CIconUI(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CIconUI::CIconUI(const CIconUI & rhs)
	: CGameObject(rhs)
{
}

HRESULT CIconUI::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CIconUI::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0.f, 1.f);


	m_fSizeX = 57.f;
	m_fSizeY = 47.f;
	m_fX = 0.f;
	m_fY = 0.f;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	ZeroMemory(&m_fDifDis, sizeof(_float2));

	m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.f));

	return S_OK;
}

void CIconUI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	SetRect(&m_rcRect, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f, m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);

	POINT		ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	auto pInven = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_InvenUI"));

	if (PtInRect(&m_rcRect, ptMouse))
	{
		m_bRectInCheck = true;
		if (pGameInstance->Key_Pressing(VK_LBUTTON) && !m_bMoveUi)
		{
			m_bMoveUi = true;
			m_fMousePos.x = ptMouse.x;
			m_fMousePos.y = ptMouse.y;
		}
		else if (m_bMoveUi && !pGameInstance->Key_Pressing(VK_LBUTTON))
			m_bMoveUi = false;
	}
	if (m_bMoveUi)
	{
		m_fDifDis.x = m_fMousePos.x - ptMouse.x;
		m_fDifDis.y = m_fMousePos.y - ptMouse.y;
	}


	if (pGameInstance->Key_Pressing(VK_LBUTTON) && m_bRectInCheck)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(ptMouse.x - g_iWinSizeX * 0.5f, -ptMouse.y + g_iWinSizeY * 0.5f, 0.f));
	}

	if (pGameInstance->Key_Up(VK_LBUTTON)) 
	{
		for (auto& pInven : static_cast<CInventoryUI*>(pInven)->Get_InvenInfo())
		{
			if (PtInRect(&pInven.rcRect, ptMouse))
			{
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(pInven.RectX - g_iWinSizeX * 0.5f, -pInven.RectY + g_iWinSizeY * 0.5f, 0.f));
			}
		}
		m_bRectInCheck = false;
	}

	Safe_Release(pGameInstance);
}

void CIconUI::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	auto pInven = pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_InvenUI"));

	if (static_cast<CInventoryUI*>(pInven)->Get_OnCheck())
	{
		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
	}

	Safe_Release(pGameInstance);
}

HRESULT CIconUI::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;

	_float4x4		ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);

	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	if (FAILED(m_pTextureCom->Bind_OnGraphicDev()))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;



	return S_OK;
}

HRESULT CIconUI::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_IconUI"), (CComponent**)&m_pTextureCom)))
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

HRESULT CIconUI::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 10);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	return S_OK;
}

HRESULT CIconUI::Release_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}

CIconUI * CIconUI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CIconUI*	pInstance = new CIconUI(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CIconUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CIconUI::Clone(void* pArg)
{
	CIconUI*	pInstance = new CIconUI(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CIconUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CIconUI::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}
