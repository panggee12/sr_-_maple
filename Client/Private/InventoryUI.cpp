#include "stdafx.h"
#include "..\Public\InventoryUI.h"
#include "GameInstance.h"

CInventoryUI::CInventoryUI(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
	ZeroMemory(&m_vecCheckRect, sizeof(RECT));
}

CInventoryUI::CInventoryUI(const CInventoryUI & rhs)
	: CGameObject(rhs)
{
}

HRESULT CInventoryUI::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CInventoryUI::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0.f, 1.f);

	m_fSizeX = 468.f;
	m_fSizeY = 702.f;
	m_fX = 500.f;
	m_fY = 400.f;
	

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	
	m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
	ZeroMemory(&m_fDifDis, sizeof(_float2));
	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.f));


	return S_OK;
}

void CInventoryUI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);	 
	
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);
	
	if(!m_bMoveUi)
		SetRect(&m_rcRect, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f, m_fX + m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.4f);

	POINT		ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	_char         MouseMove = 0;
	bool         bDown = false;
	if (PtInRect(&m_rcRect, ptMouse)) //눌렀을때 마우스 위치를 기록해놔야함
	{
		if ((MouseMove = pGameInstance->Get_DIMKeyState(DIMK_LBUTTON)) && !m_bMoveUi)
		{
			m_bMoveUi = true;
			m_fMousePos.x = ptMouse.x;
			m_fMousePos.y = ptMouse.y;
			m_iCheck++;
		}
		else if(m_bMoveUi&& !(MouseMove = pGameInstance->Get_DIMKeyState(DIMK_LBUTTON)))
			m_bMoveUi = false;
	}
	if (m_bMoveUi)
	{
		m_fDifDis.x = m_fMousePos.x - ptMouse.x;
		m_fDifDis.y = m_fMousePos.y - ptMouse.y;
	}
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - m_fDifDis.x - m_fSizeX*1.25f, m_fY + m_fDifDis.y - m_fSizeY*0.7f, 0.f));
	SetRect(&m_rcRect, m_fX - m_fDifDis.x - m_fSizeX * 0.5f, m_fY + m_fDifDis.y - m_fSizeY * 0.5f, m_fX - m_fDifDis.x + m_fSizeX * 0.5f, m_fY + m_fDifDis.y - m_fSizeY * 0.4f);

	if (m_iCheck > 1)
		int a = 10;
	Safe_Release(pGameInstance);

}

void CInventoryUI::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	POINT		ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	_float fLeft = m_fX - m_fDifDis.x - m_fSizeX * 0.5f;
	_float fTop = m_fY - m_fDifDis.y - m_fSizeY * 0.5f;
	_float fRight = m_fX + m_fDifDis.x + m_fSizeX * 0.5f;
	_float fBottom = m_fY + m_fDifDis.y + m_fSizeY * 0.5f;

	if (GetKeyState('I') & 0x0001)
	{
		if (m_bOnCheck == true)
		{
			if (nullptr != m_pRendererCom)
				m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);		

			for (_uint i = 1; i <= 8; ++i) //y
			{
				for (_uint j = 1; j <= 6; ++j) //x
				{
					RECT rcRect;

					SetRect(&rcRect,
						fLeft + 48.f + j * 37.5f,
						fTop + 130.f + i * 36.f,
						fLeft + 48.f + j * 75.f,
						fTop + 130.f + i * 72.f);

					m_vecCheckRect.push_back(rcRect);
				}
			}
		}
		else
		{
			m_bOnCheck = true;
		}

		
	}



	Safe_Release(pGameInstance);
	
}

HRESULT CInventoryUI::Render()
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

HRESULT CInventoryUI::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_InventoryUI"), (CComponent**)&m_pTextureCom)))
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

HRESULT CInventoryUI::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;	

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 250);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	return S_OK;
}

HRESULT CInventoryUI::Release_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}

CInventoryUI * CInventoryUI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CInventoryUI*	pInstance = new CInventoryUI(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CInventoryUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CInventoryUI::Clone(void* pArg)
{
	CInventoryUI*	pInstance = new CInventoryUI(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CInventoryUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CInventoryUI::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}