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
	enum PLAYER_STATE {PLAYER_IDLE,UP_STATE,DOWN_STATE,LEFT_STATE,RIGHT_STATE,RT_STATE, LT_STATE, LD_STATE, RD_STATE, PLAYER_ATTACK,PLAYER_SKILL,PLAYER_END};
	enum PLAYER_ATTACK_ {UP_ATTACK,DOWN_ATTACK,LEFT_ATTACK,RIGHT_ATTACK,ATTACK_END};

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
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_RenderState();
	HRESULT Release_RenderState();
	void Player_Idel(PLAYER_STATE _PlayerState,_float fTimeDelta);
	void Player_Move(PLAYER_STATE _PlayerState ,_float fTimeDelta);
	void Player_Attack(PLAYER_STATE _PlayerState,PLAYER_ATTACK_ _PlayerAttack, float fTimeDelta);
	HRESULT Ready_Layer_Player_Skill(const _tchar * pLayerTag, _float fTimeDelta);
	HRESULT Ready_Layer_Player_Attack(const _tchar * pLayerTag, _float fTimeDelta);
<<<<<<< HEAD
public:
	_bool Key_Up(int _Key);
	_bool Key_Down(int _Key);
	_bool Key_Pressing(int _Key);
public:
	HRESULT Fire_Body_On(const _tchar* pEffet_LayerTag, _float fTimeDelta);
=======
>>>>>>> bf356d80309bcd323a4df46af9d27d0e7845c1fb


public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:

	_float m_fFallSpeed = 0.f;
	_float m_fMaxFallSpeed = 3.f;
	_float m_fJumpPower = 0.f; //����, ������ �������� �ൿ ���� 

	_float m_uFrameNum = 0;

	_float m_fSkillTime = 0.f;

	_float m_fFrameTime = 0.f;

	PLAYER_STATE   m_ePlayer_State= PLAYER_IDLE;
	PLAYER_ATTACK_  m_ePlayer_Attack = ATTACK_END;

	_bool	m_bPlayer_Move=false;
	_bool	m_bPlayer_Idle = true;
	_bool	m_bPlayer_Attack = false;
	_bool   m_bSkill = false;
	_bool	m_KeyInput = false;


};

END