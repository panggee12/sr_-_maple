#include "stdafx.h"
#include "ItemInfoUI.h"
#include "GameInstance.h"
#include "Loader.h"
#include "Player.h"

CItemInfoUI::CItemInfoUI(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CItemInfoUI::CItemInfoUI(const CItemInfoUI & rhs)
	: CGameObject(rhs)
{
}

HRESULT CItemInfoUI::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CItemInfoUI::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	_float3 vPos = {};

	memcpy(&vPos, pArg, sizeof(_float3));

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0.f, 1.f);

	m_fSizeX = 66.f;
	m_fSizeY = 66.f;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(vPos.x + 770.f - g_iWinSizeX * 0.5f , -vPos.y + g_iWinSizeY * 0.5f, 0.f));

	return S_OK;
}

void CItemInfoUI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);	

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	if (m_iCheck == 3)
		m_iCheck = 0;

	m_eQuick_Item=QUICK_ITEM(m_iCheck);

	Safe_Release(pGameInstance);
}

void CItemInfoUI::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
}

HRESULT CItemInfoUI::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	
	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;

	_float4x4		ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);
	
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	if (FAILED(m_pTextureCom->Bind_OnGraphicDev(m_eQuick_Item)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;



	return S_OK;
}

void CItemInfoUI::Use_Item()//플레이어 퀵슬롯 버튼 클린한것 판단 후 들어오는 함수 실질적 아이템 사용 함수
{		//여기서 물약먹으면 인벤토리 물약 감소, 인벤토리 물약 갯수와 연동되어야하고 플레이어 hp나 mp등 플레이어 능력치와도 연동이 되어야함
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	auto Player = dynamic_cast<CPlayer*>(pGameInstance->Find_Target(LEVEL_GAMEPLAY, TEXT("Layer_Player")));

	switch (m_eQuick_Item)
	{
	case Client::Quick_Normal:
		break;
	case Client::Quick_HP:
		Player->Set_Hp(-1);
		break;
	case Client::Quick_MP:
		//Player->S
		break;
	default:
		break;
	}
}

HRESULT CItemInfoUI::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_ItemInfoUI"), (CComponent**)&m_pTextureCom)))
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

HRESULT CItemInfoUI::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;	

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 60);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	return S_OK;
}

HRESULT CItemInfoUI::Release_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}

CItemInfoUI * CItemInfoUI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CItemInfoUI*	pInstance = new CItemInfoUI(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CItemInfoUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CItemInfoUI::Clone(void* pArg)
{
	CItemInfoUI*	pInstance = new CItemInfoUI(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CItemInfoUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItemInfoUI::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}