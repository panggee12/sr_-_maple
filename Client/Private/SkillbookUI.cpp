#include "stdafx.h"
#include "SkillbookUI.h"
#include "GameInstance.h"
#include "Loader.h"

CSkillbookUI::CSkillbookUI(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CSkillbookUI::CSkillbookUI(const CSkillbookUI & rhs)
	: CGameObject(rhs)
{
}

HRESULT CSkillbookUI::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSkillbookUI::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0.f, 1.f);

	m_fSizeX = 200.f;
	m_fSizeY = 300.f;
	m_fX = 700.f;
	m_fY = 400.f;
	m_fDifDis.x = 0.f;
	m_fDifDis.y = 0.f;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.f));
	SetRect(&m_rcRect, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f, m_fX + m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.4f);
	return S_OK;
}

// 레프트 탑 라이트 바텀

void CSkillbookUI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	//불변수 하나로 눌렀을때 안눌렀을때 판별
	//눌렀을때 

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	//if (!m_bMoveUi)
	//	SetRect(&m_rcRect, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f, m_fX + m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.4f);

	//300 //100 700 160
	POINT		ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (m_bMoveUi)
	{									//100						99
		m_fDifDis.x = m_fMousePos.x - ptMouse.x;
		m_fDifDis.y = m_fMousePos.y - ptMouse.y;
	}

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - g_iWinSizeX * 0.5f - m_fDifDis.x, -m_fY + g_iWinSizeY * 0.5f + m_fDifDis.y, 0.f));
	SetRect(&m_rcRect, m_fX - m_fSizeX * 0.5f-m_fDifDis.x, m_fY - m_fSizeY * 0.5f+ m_fDifDis.y, m_fX + m_fSizeX * 0.5f- m_fDifDis.x, m_fY - m_fSizeY * 0.4f+ m_fDifDis.y);


	_float fMx, fMy;

	_char         MouseMove = 0;
	bool         bDown = false;
	if (pGameInstance->Key_Pressing(VK_LBUTTON) && !m_bMoveUi)
	{
		if (PtInRect(&m_rcRect, ptMouse))
		{
			m_bMoveUi = true;
			m_fMousePos.x = ptMouse.x;
			m_fMousePos.y = ptMouse.y;
			m_iCheck++;
		}
	}

	else if (pGameInstance->Key_Up(VK_LBUTTON) && m_bMoveUi)
		m_bMoveUi = false;
<<<<<<< HEAD
=======


	if (m_bMoveUi)
	{									//100						99
		m_fDifDis.x = m_fMousePos.x - ptMouse.x;
		m_fDifDis.y = m_fMousePos.y - ptMouse.y;
	}

>>>>>>> 763671df696a78e2247104d8f8547f8d45e72ab2


	if (m_iCheck > 1)
		int a = 10;
	Safe_Release(pGameInstance);
}

void CSkillbookUI::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	if (pGameInstance->Key_Down('K'))
	{
		m_bOnCheck = true;

	}
	if (m_bOnCheck == true)
	{
		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
		//RECT		rcRect;
		//SetRect(&rcRect, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f, m_fX + m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.4f);

		/*	POINT		ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);*/

		/*if (PtInRect(&rcRect, ptMouse))
		{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(ptMouse.x, ptMouse.y * -1.f, 0.f));
		}

		}*/
	}
	/*else
	{
	m_bOnCheck = true;
	}*/
	Safe_Release(pGameInstance);
}

HRESULT CSkillbookUI::Render()
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

HRESULT CSkillbookUI::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_SkillbookUI"), (CComponent**)&m_pTextureCom)))
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

HRESULT CSkillbookUI::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 250);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	return S_OK;
}

HRESULT CSkillbookUI::Release_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}

CSkillbookUI * CSkillbookUI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSkillbookUI*	pInstance = new CSkillbookUI(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CSkillbookUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSkillbookUI::Clone(void* pArg)
{
	CSkillbookUI*	pInstance = new CSkillbookUI(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CSkillbookUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSkillbookUI::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}