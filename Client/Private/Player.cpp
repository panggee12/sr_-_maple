#include "stdafx.h"
#include "..\Public\Player.h"
#include "GameInstance.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CPlayer::CPlayer(const CPlayer & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPlayer::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CPlayer::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

void CPlayer::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	m_pTransformCom->Save_Collision_Pos(fTimeDelta);

	m_uFrameNum = m_uFrameNum + 0.2f;

	//m_fFrameTime += fTimeDelta;

	//m_pTransformCom->Down(fTimeDelta*1.0f);


	if (GetKeyState(VK_UP) < 0)
	{
		if (GetKeyState(VK_RIGHT) < 0)
		{
<<<<<<< HEAD
			m_ePlayer_State = CPlayer::PLAYER_MOVE_STATE;
			m_ePlayer_Dir = CPlayer::RU;
=======
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
			m_pTransformCom->Go_RT(fTimeDelta);
			m_ePlayer_State = CPlayer::RT_STATE;
			m_ePlayer_Attack = CPlayer::UP_ATTACK;
			m_bPlayer_Move = true;
			m_bPlayer_Idle = false;
		}
		else if (GetKeyState(VK_LEFT) < 0)
		{
<<<<<<< HEAD
			m_ePlayer_State = CPlayer::PLAYER_MOVE_STATE;
			m_ePlayer_Dir = CPlayer::LU;
=======
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
			m_pTransformCom->Go_LT(fTimeDelta);
			m_ePlayer_State = CPlayer::LT_STATE;
			m_ePlayer_Attack = CPlayer::UP_ATTACK;
			m_bPlayer_Move = true;
			m_bPlayer_Idle = false;
		}
		else
		{
<<<<<<< HEAD
			m_ePlayer_State = CPlayer::PLAYER_MOVE_STATE;
			m_ePlayer_Dir = CPlayer::UP;
=======
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
			m_pTransformCom->Go_Straight(fTimeDelta);
			m_ePlayer_State = CPlayer::UP_STATE;
			m_ePlayer_Attack = CPlayer::UP_ATTACK;
			m_bPlayer_Move = true;
			m_bPlayer_Idle = false;
		}
	}

	else if (GetKeyState(VK_DOWN) < 0 )
	{
		if (GetKeyState(VK_RIGHT) < 0)
		{
<<<<<<< HEAD
			m_ePlayer_State = CPlayer::PLAYER_MOVE_STATE;
			m_ePlayer_Dir = CPlayer::RD;
=======
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
			m_pTransformCom->Go_Right(fTimeDelta);
			m_pTransformCom->Go_Backward(fTimeDelta);
			m_ePlayer_State = CPlayer::RD_STATE;
			m_ePlayer_Attack = CPlayer::UP_ATTACK;
			m_bPlayer_Move = true;
			m_bPlayer_Idle = false;
		}
		else if (GetKeyState(VK_LEFT) < 0)
		{
<<<<<<< HEAD
			
			m_ePlayer_State = CPlayer::PLAYER_MOVE_STATE;
			m_ePlayer_Dir = LD;
=======
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
			m_pTransformCom->Go_Left(fTimeDelta);
			m_pTransformCom->Go_Backward(fTimeDelta);
			m_ePlayer_State = CPlayer::LD_STATE;
			m_ePlayer_Attack = CPlayer::UP_ATTACK;
			m_bPlayer_Move = true;
			m_bPlayer_Idle = false;
		}
		else
		{
<<<<<<< HEAD
			m_ePlayer_State = CPlayer::PLAYER_MOVE_STATE;
			m_ePlayer_Dir = CPlayer::DOWN;
=======
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
			m_pTransformCom->Go_Backward(fTimeDelta);
			m_ePlayer_State = CPlayer::DOWN_STATE;
			m_ePlayer_Attack = CPlayer::DOWN_ATTACK;
			m_bPlayer_Move = true;
			m_bPlayer_Idle = false;
		}
	}

	else if (GetKeyState(VK_LEFT) < 0 )
	{
<<<<<<< HEAD

		m_ePlayer_State = CPlayer::PLAYER_MOVE_STATE;
		m_ePlayer_Dir = CPlayer::LEFT;
=======
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
		m_pTransformCom->Go_Left(fTimeDelta);
		m_ePlayer_State = CPlayer::LEFT_STATE;
		m_ePlayer_Attack = CPlayer::LEFT_ATTACK;
		m_bPlayer_Move = true;
		//m_bPlayer_Attack = true;
		m_bPlayer_Idle = false;


	}

	else if (GetKeyState(VK_RIGHT) < 0 )
	{
<<<<<<< HEAD

		m_ePlayer_State = CPlayer::PLAYER_MOVE_STATE;
		m_ePlayer_Dir = CPlayer::RIGHT;
=======
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
		m_pTransformCom->Go_Right(fTimeDelta);
		m_ePlayer_State = CPlayer::RIGHT_STATE;
		m_ePlayer_Attack = CPlayer::RIGHT_ATTACK;
		m_bPlayer_Move = true;
		//m_bPlayer_Attack = true;
		m_bPlayer_Idle = false;

	}
<<<<<<< HEAD


	else if (Key_Down('Q')&& m_bPlayer_Attack==true)
	{
<<<<<<< HEAD
		if (pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster")))
=======
		Player_Attack(m_ePlayer_Dir, fTimeDelta);

		if (pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_Monster")))
>>>>>>> e8a7accc92a0666938010f64fe805e1f1445c9cf
=======
	
	if (GetKeyState('A') & 0x8000)
	{
		if (pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster")))
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
		{
			m_ePlayer_State = PLAYER_ATTACK;

			if (FAILED(Ready_Layer_Player_Skill(TEXT("Layer_Playe_Skill"), fTimeDelta)));
			return;
		}
	}

<<<<<<< HEAD
	else if (Key_Down('X') && m_bPlayer_Attack == true)
	{
<<<<<<< HEAD
		if (pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster")))
=======
		
		Player_Attack(m_ePlayer_Dir, fTimeDelta);


		if (pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_Monster")))
>>>>>>> e8a7accc92a0666938010f64fe805e1f1445c9cf
=======
	else if (pGameInstance->Key_Down('X'))
	{
		if (pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster")))
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
		{
			Player_Attack(m_ePlayer_State, m_ePlayer_Attack, fTimeDelta);

			


			if (FAILED(Ready_Layer_Player_Attack(TEXT("Layer_Playe_Attack"), fTimeDelta)));
			return;
		}

		if (FAILED(Ready_Layer_Player_Attack(TEXT("Layer_Fire_Body_Effect"), fTimeDelta)));
		return;
	}
	

<<<<<<< HEAD

	else if (Key_Down('C') && !m_pTransformCom->Get_Fall())
=======
	_uint			Keyboard;
	bool			bDown = false;
	if (Keyboard = pGameInstance->Get_DIKState(DIK_Z))
	{
		m_ePlayer_State = PLAYER_ATTACK;
	}
	
	if (Keyboard = pGameInstance->Get_DIKState(DIK_U))
	{
		m_pTransformCom->Down(fTimeDelta);
	}
	if (Keyboard = pGameInstance->Get_DIKState(DIK_Y))
	{
		m_pTransformCom->Up(fTimeDelta);
	}
	//m_pTransformCom->Fall(fTimeDelta);
	
	if (Keyboard = pGameInstance->Get_DIKState(DIK_C)&& !m_pTransformCom->Get_Fall())
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
	{
		m_pTransformCom->Set_Jump(true);
		m_pTransformCom->Set_Fall(true);
	}

	if (m_ePlayer_State == UP_STATE&&m_bPlayer_Move==true)
	{
<<<<<<< HEAD
		m_ePlayer_State = CPlayer::PLAYER_IDLE;
		Player_Idle(m_ePlayer_Dir, fTimeDelta);
		m_bPlayer_Attack = true;
=======
		Player_Move(UP_STATE, fTimeDelta);
	}
	else if (m_ePlayer_State == RIGHT_STATE&&m_bPlayer_Move == true )
	{
		Player_Move(RIGHT_STATE, fTimeDelta);
	}
	else if (m_ePlayer_State == LEFT_STATE&&m_bPlayer_Move == true )
	{
		Player_Move(LEFT_STATE, fTimeDelta);
	}
	else if (m_ePlayer_State == DOWN_STATE&&m_bPlayer_Move == true)
	{
		Player_Move(DOWN_STATE, fTimeDelta);
	}
	else if (m_ePlayer_State == RT_STATE&&m_bPlayer_Move == true)
	{
		Player_Move(RT_STATE, fTimeDelta);
	}
	else if (m_ePlayer_State == LT_STATE&&m_bPlayer_Move == true)
	{
		Player_Move(LT_STATE, fTimeDelta);
	}
	else if (m_ePlayer_State == LD_STATE&&m_bPlayer_Move == true)
	{
		Player_Move(LD_STATE, fTimeDelta);
	}
	else if (m_ePlayer_State == RD_STATE&&m_bPlayer_Move == true)
	{
		Player_Move(RD_STATE, fTimeDelta);
	}
	else if (m_ePlayer_State == PLAYER_ATTACK&&m_bPlayer_Move == false)
	{
		Player_Attack(m_ePlayer_State, m_ePlayer_Attack,fTimeDelta);
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
	}

	if (m_pTransformCom->Get_Jump())			
		m_fJumpPower = 1.2f;	
	else	
		m_fJumpPower = 0.f;
		
	if (m_pTransformCom->Get_Fall())
	{
		m_fFallSpeed += 0.04f;
		if (m_fFallSpeed >= m_fMaxFallSpeed)
			m_fFallSpeed = m_fMaxFallSpeed;
	}
	else
		m_fFallSpeed = 0.f;

	m_pTransformCom->Jump(fTimeDelta, m_fJumpPower, m_fFallSpeed);

	//m_pTransformCom->Set_Fall(true);

	/*if (m_pTransformCom->Check_SecSavePos())
	{
		m_pTransformCom->Set_SecSavePosOn(false);
		m_pTransformCom->Save_Collision_Pos(fTimeDelta);
	}*/

	Safe_Release(pGameInstance);
}

void CPlayer::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CPlayer::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	
	if (FAILED(m_pTransformCom->Bind_OnGraphicDev()))
		return E_FAIL;

	if (FAILED(m_pTextureCom->Bind_OnGraphicDev(m_uFrameNum)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

<<<<<<< HEAD
_bool CPlayer::Key_Up(int _Key)
{

	if (m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8000))
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (!m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8000))
			m_bKeyState[_Key] = !m_bKeyState[_Key];
	}

	return false;
}

_bool CPlayer::Key_Down(int _Key)
{
	if (!m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8000))
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8000))
			m_bKeyState[_Key] = !m_bKeyState[_Key];
	}

	return false;
}

_bool CPlayer::Key_Pressing(int _Key)
{
	if (GetAsyncKeyState(_Key) & 0x8000)
		return true;

	return false;
}

HRESULT CPlayer::Fire_Body_On(const _tchar * pEffet_LayerTag, _float fTimeDelta)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	//pGameInstance->AddRef();

	_float3 vPosition_B = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_FireBody_Effect"), LEVEL_GAMEPLAY, pEffet_LayerTag, vPosition_B)))
		return E_FAIL;

	//m_fSkillTime = m_fSkillTime + 0.5f;

	Safe_Release(pGameInstance);
	return S_OK;
}

=======
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
HRESULT CPlayer::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Components(TEXT("Com_Texture"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player"), (CComponent**)&m_pTextureCom)))
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

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(1.0f, 4.0f, 1.0f));
	m_pTransformCom->Set_Scaled(_float3(2.f, 2.f, 2.f));

	return S_OK;
}

HRESULT CPlayer::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;	

	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 250);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	return S_OK;
}

HRESULT CPlayer::Release_RenderState()
{
	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}

void CPlayer::Player_Idel(PLAYER_STATE _PlayerState,_float fTimeDelta)
{
	if (m_ePlayer_State==PLAYER_IDLE&&m_bPlayer_Move == false)
	{
		if (m_uFrameNum <= 0 || m_uFrameNum >= 7)
		{
			m_uFrameNum = 0;
		}
<<<<<<< HEAD
	
	}

	//RIGHT
	 if (_ePlayer_Dir_State == CPlayer::RIGHT)
	{
		if (m_uFrameNum <= 88 || m_uFrameNum >= 95)
		{
			m_uFrameNum = 88;
		}
		

	}
	//RU
	else if (_ePlayer_Dir_State == CPlayer::RU)
	{
		if (m_uFrameNum <= 96 || m_uFrameNum >= 103)
		{
			m_uFrameNum = 96;
		}
		
	}
	//UP
	else if (_ePlayer_Dir_State == CPlayer::UP)
	{
		if (m_uFrameNum <= 104 || m_uFrameNum >= 111)
		{
			m_uFrameNum = 104;
		}
		
	}
	//LU
	else if (_ePlayer_Dir_State == CPlayer::LU)
	{
		if (m_uFrameNum <= 112 || m_uFrameNum >= 119)
		{
			m_uFrameNum = 112;
		}
		
	}
	//LEFT
	else if (_ePlayer_Dir_State == CPlayer::LEFT)
	{
		if (m_uFrameNum <= 120 || m_uFrameNum >= 127)
		{
			m_uFrameNum = 120;
		}
		
	}

	//LD
	else if (_ePlayer_Dir_State == CPlayer::LD)
	{
		if (m_uFrameNum <= 128 || m_uFrameNum >= 136)
		{
			m_uFrameNum = 128;
		}
		
	}
	//DOWN
	else if (_ePlayer_Dir_State == CPlayer::DOWN)
	{
		if (m_uFrameNum <= 137 || m_uFrameNum >= 144)
		{
			m_uFrameNum = 137;
		}
		
	}
	//RD
	else if (_ePlayer_Dir_State == CPlayer::RD)
	{
		if (m_uFrameNum <= 145 || m_uFrameNum >= 152)
		{
			m_uFrameNum = 145;
		}
		
	}
	else
	{
		m_ePlayer_State = PLAYER_IDLE;
		m_ePlayer_brfore = PLAYER_IDLE;
		m_bPlayer_Attack = true;

	}

	
=======
	}				
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb
}
void CPlayer::Player_Move(PLAYER_STATE _PlayerState, _float fTimeDelta)
{
	if (m_ePlayer_State == UP_STATE)
	{
		if (m_uFrameNum <= 8 || m_uFrameNum >= 15)
		{
			m_uFrameNum = 8;
		}
	}
	else if (m_ePlayer_State == RIGHT_STATE)
	{
		if (m_uFrameNum <= 16 || m_uFrameNum >= 23)
		{
			m_uFrameNum = 16;
		}
	}

	else if (m_ePlayer_State == LEFT_STATE )
	{
		if (m_uFrameNum <= 24 || m_uFrameNum >= 32)
		{
			m_uFrameNum = 24;
		}
	}
	else if (m_ePlayer_State == DOWN_STATE )
	{
		if (m_uFrameNum <= 32 || m_uFrameNum >= 40)
		{
			m_uFrameNum = 32;
		}
	}
	else if (m_ePlayer_State == RT_STATE)
	{
		if (m_uFrameNum <= 56 || m_uFrameNum >= 63)
		{
			m_uFrameNum = 56;
		}
	}
	else if (m_ePlayer_State == LT_STATE)
	{
		if (m_uFrameNum <= 64 || m_uFrameNum >= 71)
		{
			m_uFrameNum = 64;
		}
	}

	else if (m_ePlayer_State == LD_STATE)
	{
		if (m_uFrameNum <= 72 || m_uFrameNum >= 79)
		{
			m_uFrameNum = 72;
		}
	}
	else if (m_ePlayer_State == RD_STATE)
	{
		if (m_uFrameNum <= 80 || m_uFrameNum >= 87)
		{
			m_uFrameNum = 80;
		}
	}
	else
		m_ePlayer_State == PLAYER_IDLE;
}

void CPlayer::Player_Attack(PLAYER_STATE _PlayerState, PLAYER_ATTACK_ _PlayerAttack, float fTimeDelta)
{

	if (m_ePlayer_State == RIGHT_STATE ||m_ePlayer_Attack == RIGHT_ATTACK&&m_uFrameNum <= 40 || m_uFrameNum >= 47)
	{
		m_uFrameNum = 40;
	}

	 else if (m_ePlayer_State == UP_STATE||m_ePlayer_Attack == UP_ATTACK&&m_uFrameNum <= 47 || m_uFrameNum >= 55)	
	{
		m_uFrameNum = 48;
	}
}


HRESULT CPlayer::Ready_Layer_Player_Skill(const _tchar * pLayerTag, _float fTimeDelta)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	//pGameInstance->AddRef();

	_float3 vPosition_S = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_Player_Skill"), LEVEL_GAMEPLAY, pLayerTag, vPosition_S)))
		return E_FAIL;

	//m_fSkillTime = m_fSkillTime + 0.5f;

	Safe_Release(pGameInstance);
	return S_OK;
}


HRESULT CPlayer::Ready_Layer_Player_Attack(const _tchar * pLayerTag, _float fTimeDelta)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	//pGameInstance->AddRef();

	_float3 vPosition_ = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_Player_Attack"), LEVEL_GAMEPLAY, pLayerTag, vPosition_)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	//_float3		vPosition = Get_State(CTransform::STATE_POSITION);

	//_float3		vLook = vPoint - vPosition;

	//_float3		vRight = *D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &vLook);

	//_float3		vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);

	//_float3		vScale = Get_Scale();

	//Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * vScale.x);
	//Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * vScale.y);
	//Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * vScale.z);
	//}
	return S_OK;
}

CPlayer * CPlayer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPlayer*	pInstance = new CPlayer(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CPlayer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPlayer::Clone(void* pArg)
{
	CPlayer*	pInstance = new CPlayer(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CPlayer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayer::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
}
