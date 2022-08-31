#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Cube;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CPlayer final : public CGameObject
{
	//enum PLAYER_STATE {PLAYER_IDLE,UP_STATE,DOWN_STATE,LEFT_STATE,RIGHT_STATE,RT_STATE, LT_STATE, LD_STATE, RD_STATE, PLAYER_ATTACK,PLAYER_SKILL,PLAYER_END};
	//PlayerState
	enum PLAYER_STATE {PLAYER_IDLE,PLAYER_MOVE_STATE,PLAYER_ATTACK, PLAYER_SKILL, PLAYER_END };
	//MoveState
	enum PLAYER_MOVE { UP_MOVE, DOWN_MOVE, LEFT_MOVE, RIGHT_MOVE, RU_MOVE, LU_MOVE, RD_MOVE, LD_MOVE, STOP_MOVE,MOVE_END };
	//AttackState
	enum PLAYER_ATTACK_ {UP_ATTACK,DOWN_ATTACK,LEFT_ATTACK,RIGHT_ATTACK, RD_ATTACK,RU_ATTACK,LU_ATTACK,LD_ATTACK, ATTACK_END};
	//아이들 상태 ;
	enum PLATY_IDLE_STATE {IDLE_ON,UP_IDLE, DOWN_IDLE,LEFT_IDLE, RIGHT_IDLE,RU_IDLE,LU_IDLE,RD_IDLE,LD_IDLE,IDLE_END	};
	//JumpState
	enum PLAYER_JUMP { UP_ON,UP_JUMP, DOWN_JUMP, LEFT_JUMP, RIGHT_JUMP, RU_JUMP, LU_JUMP, RD_JUMP, LD_JUMP, JUMP_END };

private:
	CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device);
	CPlayer(const CPlayer& rhs);
	virtual ~CPlayer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta)override;
	virtual void Late_Tick(_float fTimeDelta)override;
	virtual HRESULT Render() override;
public:
	CTransform* Get_TransformCom() { return m_pTransformCom; }
	//void		Set_OnBlock(bool bOn) { m_bOnBlock = bOn; }
private: /* For.Components */
	CTexture*				m_pTextureCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_RenderState();
	HRESULT Release_RenderState();
	void Player_Idle(PLAYER_STATE _PlayerState, PLATY_IDLE_STATE _ePlayer_Idle_State, _float fTimeDelta);
	void Player_Move(PLAYER_STATE _PlayerState, PLAYER_MOVE _ePlayer_Move_State, _float fTimeDelta);
	void Player_Attack(PLAYER_STATE _PlayerState,PLAYER_ATTACK_ _PlayerAttack, float fTimeDelta);
	HRESULT Ready_Layer_Player_Skill(const _tchar * pLayerTag, _float fTimeDelta);
	HRESULT Ready_Layer_Player_Attack(const _tchar * pLayerTag, _float fTimeDelta);

	_bool Key_Up(int _Key);
	_bool Key_Down(int _Key);
	_bool Key_Pressing(int _Key);

public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:

	_float m_fFallSpeed = 0.f;
	_float m_fMaxFallSpeed = 3.f;
	_float m_fJumpPower = 0.f; //점프, 블럭에서 떨어지는 행동 관련 

	_float m_uFrameNum = 0;

	_float m_fSkillTime = 0.f;

	_float m_fFrameTime = 0.f;

	_float		m_PlyerTime=0.f;

	//Player_State
	PLAYER_STATE   m_ePlayer_State= PLAYER_IDLE;
	//Attack
	PLAYER_ATTACK_  m_ePlayer_Attack_State = ATTACK_END;
	//Move
	PLAYER_MOVE    m_ePlayer_Move_State = MOVE_END;
	//IDle
	PLATY_IDLE_STATE		m_ePlayer_Idle_State = IDLE_END;
	//Jump
	PLAYER_JUMP		m_ePlayer_Jump_State = JUMP_END;


	_bool	m_bPlayer_Move=false;
	_bool	m_bPlayer_Idle = true;
	_bool	m_bNoIdle = false;
	_bool	m_bPlayer_Attack = false;
	_bool   m_bSkill = false;
	_bool	m_KeyInput = false;
	_bool	m_bKeyState[VK_MAX];

};

END