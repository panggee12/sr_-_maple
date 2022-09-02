#include "stdafx.h"
#include "..\Public\Player.h"
#include "GameInstance.h"
#include "ItemInfoUI.h"
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

	m_uFrameNum += fTimeDelta + 0.2f;

<<<<<<< HEAD
	//m_fFrameTime += fTimeDelta;
=======
	m_fAttackTime += fTimeDelta + 0.2;

	//m_AttackTime=
>>>>>>> BaeH

	//m_pTransformCom->Down(fTimeDelta*1.0f);




	if (GetKeyState(VK_UP) < 0)
	{
		if (GetKeyState(VK_RIGHT) < 0)
		{
			m_ePlayer_State = CPlayer::PLAYER_MOVE;
			m_ePlayer_Dir = CPlayer::RU;

			m_pTransformCom->Go_RT(fTimeDelta);

			m_bPlayer_Move = true;
			m_bPlayer_Idle = false;
		}
		else if (GetKeyState(VK_LEFT) < 0)
		{
<<<<<<< HEAD
=======
			m_ePlayer_State = CPlayer::PLAYER_MOVE;
			m_ePlayer_Dir = CPlayer::LU;
			m_pTransformCom->Go_LT(fTimeDelta);
>>>>>>> BaeH


			m_ePlayer_State = CPlayer::PLAYER_MOVE;
			m_ePlayer_Dir = CPlayer::LU;

			m_pTransformCom->Go_LT(fTimeDelta);
			m_bPlayer_Move = true;
			m_bPlayer_Idle = false;
		}
		else
		{
<<<<<<< HEAD

=======
>>>>>>> BaeH
			m_ePlayer_State = CPlayer::PLAYER_MOVE;
			m_ePlayer_Dir = CPlayer::UP;
			m_pTransformCom->Go_Straight(fTimeDelta);

			m_bPlayer_Move = true;
			m_bPlayer_Idle = false;
		}
	}

	else if (GetKeyState(VK_DOWN) < 0)
	{
		if (GetKeyState(VK_RIGHT) < 0)
		{
<<<<<<< HEAD


=======
>>>>>>> BaeH
			m_ePlayer_State = CPlayer::PLAYER_MOVE;
			m_ePlayer_Dir = CPlayer::RD;
			m_pTransformCom->Go_Right(fTimeDelta);
			m_pTransformCom->Go_Backward(fTimeDelta);
			m_bPlayer_Move = true;
			m_bPlayer_Idle = false;
		}
		else if (GetKeyState(VK_LEFT) < 0)
		{
<<<<<<< HEAD

=======
			
>>>>>>> BaeH
			m_ePlayer_State = CPlayer::PLAYER_MOVE;
			m_ePlayer_Dir = LD;

			m_pTransformCom->Go_Left(fTimeDelta);
			m_pTransformCom->Go_Backward(fTimeDelta);

			m_bPlayer_Move = true;
			m_bPlayer_Idle = false;
		}
		else
		{
			m_ePlayer_State = CPlayer::PLAYER_MOVE;
			m_ePlayer_Dir = CPlayer::DOWN;
			m_pTransformCom->Go_Backward(fTimeDelta);
<<<<<<< HEAD
			m_bPlayer_Move = true;
			m_bPlayer_Idle = false;
=======
		
>>>>>>> BaeH
		}
	}

	else if (GetKeyState(VK_LEFT) < 0)
	{

		m_ePlayer_State = CPlayer::PLAYER_MOVE;
		m_ePlayer_Dir = CPlayer::LEFT;


		m_pTransformCom->Go_Left(fTimeDelta);
		m_bPlayer_Move = true;
		m_bPlayer_Idle = false;
	}

	else if (GetKeyState(VK_RIGHT) < 0)
	{

		m_ePlayer_State = CPlayer::PLAYER_MOVE;
		m_ePlayer_Dir = CPlayer::RIGHT;

		m_pTransformCom->Go_Right(fTimeDelta);

		m_bPlayer_Move = true;
		m_bPlayer_Idle = false;

	}
<<<<<<< HEAD
	else if (Key_Down('Q') && m_bPlayer_Attack == true)
	{
		if (pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster")))
=======
	//else if(m_ePlayer_brfore)


	else if (Key_Pressing('Q')&& m_bPlayer_Attack==true)
	{
		Player_Attack(m_ePlayer_Dir, fTimeDelta);

		if (m_fAttackTime > 3.5f)
>>>>>>> BaeH
		{
			if (pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_Monster")))
			{
				m_ePlayer_State = PLAYER_ATTACK;

				if (FAILED(Ready_Layer_Player_Skill(TEXT("Layer_Playe_Skill"), fTimeDelta)));
				//return;
			}

		}
<<<<<<< HEAD
	}
	else if (Key_Down('X') && m_bPlayer_Attack == true)

=======
		
	}

	else if (Key_Pressing('X') && m_bPlayer_Attack == true)
>>>>>>> BaeH
	{
		if (pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_MonkeyMonster")))

<<<<<<< HEAD
			Player_Attack(m_ePlayer_Dir, fTimeDelta);
=======
		if (m_fAttackTime > 3.5f)
>>>>>>> BaeH
		{
			if (pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_Monster")))
			{

				if (FAILED(Ready_Layer_Player_Attack(TEXT("Layer_Playe_Attack"), fTimeDelta)));
				//return;
			}

<<<<<<< HEAD
			if (FAILED(Ready_Layer_Player_Attack(TEXT("Layer_Playe_Attack"), fTimeDelta)));

			//return;
		}

=======
		}
	
>>>>>>> BaeH
	}
	else if (Key_Pressing('W') && m_bPlayer_Attack == true)
	{

		Player_Attack(m_ePlayer_Dir, fTimeDelta);


		if (m_fAttackTime > 3.7f)
		{
<<<<<<< HEAD
			if (FAILED(Ready_Layer_Player_Meteor(TEXT("Layer_Playe_Skill_Meteor"), fTimeDelta)));
			//return;
=======
			if (pGameInstance->Check_Layer(LEVEL_GAMEPLAY, TEXT("Layer_Monster")))
			{

				if (FAILED(Ready_Layer_Player_Meteor(TEXT("Layer_Playe_Skill_Meteor"), fTimeDelta)));
				//return;
			}
>>>>>>> BaeH
		}
		


		/*	if (FAILED(Ready_Layer_Player_Attack(TEXT("Layer_Fire_Body_Effect"), fTimeDelta)));
		return;*/

	}

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

	{
		m_pTransformCom->Set_Jump(true);
		m_pTransformCom->Set_Fall(true);
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
	Use_Quick_Item(); 
	//퀵슬롯에 있는 아이템 사용 퀵슬롯은 벡터, 플레이어에 벡터 전달해줘서 인덱스에 맞는 칸 찾고 그 칸의 아이템 정보를 받아 아이템 사용여부, 효과 처리

	m_iHp;
	m_pTransformCom->Set_Fall(true);

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


void CPlayer::Player_Idle(PLAYER_DIR _ePlayer_Dir_State, _float fTimeDelta)
 {

	//기본
	if (_ePlayer_Dir_State == CPlayer::END_)
	{
		if (m_uFrameNum <= 0 || m_uFrameNum >= 7)
		{
			m_uFrameNum = 0;
		}

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


}

void CPlayer::Player_Move(PLAYER_DIR _ePlayer_Move_State, _float fTimeDelta)
{
<<<<<<< HEAD
=======
	
		 if ( _ePlayer_Move_State == CPlayer::RIGHT)
		{
			if (m_uFrameNum <= 16 || m_uFrameNum >= 23)
			{
				m_uFrameNum = 16;
			}
		}
		else if ( _ePlayer_Move_State == CPlayer::RU)
		{
			if (m_uFrameNum <= 56 || m_uFrameNum >= 63)
			{
				m_uFrameNum = 56;
			}
		}
		else if ( _ePlayer_Move_State == CPlayer::UP)
		{
			if (m_uFrameNum <= 8 || m_uFrameNum >= 15)
			{
				m_uFrameNum = 8;
			}
		}
		else if ( _ePlayer_Move_State == CPlayer::LU)
		{
			if (m_uFrameNum <= 64 || m_uFrameNum >= 71)
			{
				m_uFrameNum = 64;
			}
		}
		else if (_ePlayer_Move_State == CPlayer::LEFT)
		{
			if (m_uFrameNum <= 24 || m_uFrameNum >= 32)
			{
				m_uFrameNum = 24;
			}
		}
		else if (_ePlayer_Move_State == CPlayer::LD)
		{
			if (m_uFrameNum <= 72 || m_uFrameNum >= 79)
			{
				m_uFrameNum = 72;
			}
		}
		else if (_ePlayer_Move_State == CPlayer::DOWN)
		{
			if (m_uFrameNum <= 32 || m_uFrameNum >= 40)
			{
				m_uFrameNum = 32;
			}
		}
		else if ( _ePlayer_Move_State == CPlayer::RD)
		{
			if (m_uFrameNum <= 80 || m_uFrameNum >= 87)
			{
				m_uFrameNum = 80;
			}
		}
		else
		{
			m_ePlayer_State = PLAYER_MOVE;
			m_ePlayer_brfore = PLAYER_MOVE;
				
						m_bPlayer_Attack = false;
>>>>>>> BaeH

	if (_ePlayer_Move_State == CPlayer::RIGHT)
	{
		if (m_uFrameNum <= 16 || m_uFrameNum >= 23)
		{
			m_uFrameNum = 16;
		}
	}
	else if (_ePlayer_Move_State == CPlayer::RU)
	{
		if (m_uFrameNum <= 56 || m_uFrameNum >= 63)
		{
			m_uFrameNum = 56;
		}
	}
	else if (_ePlayer_Move_State == CPlayer::UP)
	{
		if (m_uFrameNum <= 8 || m_uFrameNum >= 15)
		{
			m_uFrameNum = 8;
		}
	}
	else if (_ePlayer_Move_State == CPlayer::LU)
	{
		if (m_uFrameNum <= 64 || m_uFrameNum >= 71)
		{
			m_uFrameNum = 64;
		}
	}
	else if (_ePlayer_Move_State == CPlayer::LEFT)
	{
		if (m_uFrameNum <= 24 || m_uFrameNum >= 32)
		{
			m_uFrameNum = 24;
		}
	}
	else if (_ePlayer_Move_State == CPlayer::LD)
	{
		if (m_uFrameNum <= 72 || m_uFrameNum >= 79)
		{
			m_uFrameNum = 72;
		}
	}
	else if (_ePlayer_Move_State == CPlayer::DOWN)
	{
		if (m_uFrameNum <= 32 || m_uFrameNum >= 40)
		{
			m_uFrameNum = 32;
		}
	}
	else if (_ePlayer_Move_State == CPlayer::RD)
	{
		if (m_uFrameNum <= 80 || m_uFrameNum >= 87)
		{
			m_uFrameNum = 80;
		}
	}
	else
	{
		m_ePlayer_State = PLAYER_MOVE;
		m_ePlayer_brfore = PLAYER_MOVE;

		m_bPlayer_Attack = false;

	}
}

void CPlayer::Player_Attack(PLAYER_DIR _PlayerAttack, float fTimeDelta)
{
	if (_PlayerAttack == CPlayer::RIGHT)
	{
		if (m_uFrameNum <= 40 || m_uFrameNum >= 47)
		{
			m_uFrameNum = 40;
		}
	}
	else if (_PlayerAttack == CPlayer::RU)
	{
		if (m_uFrameNum <= 192 || m_uFrameNum >= 199)
		{
			m_uFrameNum = 192;
		}
	}
	else if (_PlayerAttack == CPlayer::UP)
	{
		if (m_uFrameNum <= 48 || m_uFrameNum >= 55)
		{
			m_uFrameNum = 48;
		}
	}
	else if (_PlayerAttack == CPlayer::LU)
	{
		if (m_uFrameNum <= 160 || m_uFrameNum >= 167)
		{
			m_uFrameNum = 160;
		}
	}
	else if (_PlayerAttack == CPlayer::LEFT)
	{
		if (m_uFrameNum <= 168 || m_uFrameNum >= 175)
		{
			m_uFrameNum = 168;
		}
	}
	else if (_PlayerAttack == CPlayer::LD)
	{
		if (m_uFrameNum <= 176 || m_uFrameNum >= 183)
		{
			m_uFrameNum = 176;
		}
	}
	else if (_PlayerAttack == CPlayer::DOWN)
	{
		if (m_uFrameNum <= 184 || m_uFrameNum >= 191)
		{
			m_uFrameNum = 184;
		}
	}
	else if (_PlayerAttack == CPlayer::RD)
	{
		if (m_uFrameNum <= 192 || m_uFrameNum >= 199)
		{
			m_uFrameNum = 192;
		}
	}
	else
	{
		m_fAttackTime += 0.1;
<<<<<<< HEAD

=======
		
>>>>>>> BaeH
		if (m_fAttackTime > 1.f)
		{
			m_bPlayer_Attack = false;
		}
		m_bPlayer_Attack = false;


		m_ePlayer_State == PLAYER_ATTACK;
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

HRESULT CPlayer::Ready_Layer_Player_Meteor(const _tchar * pLayerTag, _float fTimeDelta)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	//pGameInstance->AddRef();

	_float3 vPosition_ = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_Meteo_Skill"), LEVEL_GAMEPLAY, pLayerTag, vPosition_)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

void CPlayer::Use_Quick_Item()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	if (pGameInstance->Key_Down('1'))
	{
		auto iter = m_vecQuickItem->at(0);
		iter->Use_Item();
	}
	else if (pGameInstance->Key_Down('2'))
	{
		auto iter = m_vecQuickItem->at(1);
		iter->Use_Item();
	}
	else if (pGameInstance->Key_Down('3'))
	{
		auto iter = m_vecQuickItem->at(2);
		iter->Use_Item();
	}
	else if (pGameInstance->Key_Down('4'))
	{
		auto iter = m_vecQuickItem->at(3);
		iter->Use_Item();
	}
	else if (pGameInstance->Key_Down('5'))
	{
		auto iter = m_vecQuickItem->at(4);
		iter->Use_Item();
	}
	else if (pGameInstance->Key_Down('6'))
	{
		auto iter = m_vecQuickItem->at(5);
		iter->Use_Item();
	}
	else if (pGameInstance->Key_Down('7'))
	{
		auto iter = m_vecQuickItem->at(6);
		iter->Use_Item();
	}
	else if (pGameInstance->Key_Down('8'))
	{
		auto iter = m_vecQuickItem->at(7);
		iter->Use_Item();
	}
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
