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

	enum PLAYER_STATE { PLAYER_IDLE, PLAYER_MOVE_STATE, PLAYER_ATTACK, PLAYER_SKILL, PLAYER_END };
	enum PLAYER_DIR { UP, DOWN, LEFT, RIGHT, RU, LU, RD, LD, STOP, END_ };



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

private: /* For.Components */
	CTexture*				m_pTextureCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_RenderState();
	HRESULT Release_RenderState();
	void Player_Idle(PLAYER_DIR _ePlayer_Idle_State, _float fTimeDelta);
	void Player_Move(PLAYER_DIR _ePlayer_Move_State, _float fTimeDelta);
	void Player_Attack(PLAYER_DIR _PlayerAttack, float fTimeDelta);
	HRESULT Ready_Layer_Player_Skill(const _tchar * pLayerTag, _float fTimeDelta);
	HRESULT Ready_Layer_Player_Attack(const _tchar * pLayerTag, _float fTimeDelta);
	HRESULT Ready_Layer_Player_Meteor(const _tchar * pLayerTag, _float fTimeDelta);
public:
	PLAYER_DIR Get_DirState() { return m_ePlayer_Dir; }

public:
	_bool Key_Up(int _Key);
	_bool Key_Down(int _Key);
	_bool Key_Pressing(int _Key);
public:
	HRESULT Fire_Body_On(const _tchar* pEffet_LayerTag, _float fTimeDelta);


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
	_float m_PlyerTime = 0.f;

	_float m_AttackTime = 0.f;

	//Player_State
	PLAYER_STATE   m_ePlayer_State = PLAYER_IDLE;
	//이전
	PLAYER_STATE  m_ePlayer_brfore = PLAYER_END;

	// 방향 
	PLAYER_DIR		m_ePlayer_Dir = END_;


	_bool	m_bPlayer_Move = false;
	_bool	m_bPlayer_Idle = true;
	_bool	m_bNoIdle = false;
	_bool	m_bPlayer_Attack = false;
	_bool   m_bSkill = false;
	_bool	m_bKeyInput = false;
	_bool	m_bKeyState[VK_MAX];

};

END