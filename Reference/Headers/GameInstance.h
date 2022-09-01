#pragma once

#include "Graphic_Device.h"
#include "Input_Device.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Timer_Manager.h"
#include "Component_Manager.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "Layer.h"

BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance)
private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public: /* For.Engine */
	HRESULT Initialize_Engine(HINSTANCE hInst, _uint iNumLevels, const GRAPHIC_DESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut);
	void Tick_Engine(_float fTimeDelta);

	void Clear(_uint iLevelIndex);


public: /* For.Graphic_Device */
	void		Render_Begin(void);
	void		Render_End(HWND hWnd = 0);

public: /* For.Input_Device */
	_char Get_DIKState(_uchar eKeyID);
	_char Get_DIMKeyState(DIMK eMouseKeyID);
	_long Get_DIMMoveState(DIMM eMouseMoveID);

public: /* For.Timer_Manager */
	HRESULT Add_Timer(const _tchar* pTimerTag);
	_float Get_TimeDelta(const _tchar* pTimerTag);
	void Update(const _tchar* pTimerTag);

public: /* For.Level_Manager */
	HRESULT Open_Level(unsigned int iLevelIndex, class CLevel* pNewLevel);

public: /* For.Object_Manager */
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObject(const _tchar* pPrototypeTag, _uint iLevelIndex, const _tchar* pLayerTag, void* pArg = nullptr);
	class CGameObject* Find_Target(_uint iLevelIndex, const _tchar* pLayerTag);
	class CGameObject* Get_BackObject(_uint iLevelIndex, const _tchar* pLayerTag);
	bool  Collision(_uint iLevelIndex, const _tchar* col1, const _tchar* col2, _float fTimeDelta, _float3 f1Scale, _float3 f2Scale);
	int   Collision_Rect_Cube(_uint iLevelIndex, const _tchar * col1, _float3 fPos, _float fTimeDelta, _float3 fScale);
	bool  Collision_Attacked(_uint iLevelIndex, const _tchar* col1, const _tchar* col2, _float fTimeDelta, int ioption, _float3 f1Scale, _float3 f2Scale);
	bool  Check_Layer(_uint iLevelIndex, const _tchar* pLayerTag);
	class CLayer* Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag);
public: /* For.Component_Manager */
	HRESULT Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, class CComponent* pPrototype);
	class CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg = nullptr);
public: 
	bool		Key_Pressing(int _Key);
	bool		Key_Up(int _Key);
	bool		Key_Down(int _Key);

public:
	static void Release_Engine();

private:
	CGraphic_Device*				m_pGraphic_Device = nullptr;
	CInput_Device*					m_pInput_Device = nullptr;
	CLevel_Manager*					m_pLevel_Manager = nullptr;
	CObject_Manager*				m_pObject_Manager = nullptr;
	CTimer_Manager*					m_pTimer_Manager = nullptr;
	CComponent_Manager*				m_pComponent_Manager = nullptr;
	CCollisionMgr*					m_pCollision_Manager = nullptr;
	CKeyMgr*						m_pKey_Manager = nullptr;
public:
	virtual void Free() override;
};

END