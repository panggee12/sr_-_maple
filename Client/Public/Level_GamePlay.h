#pragma once

#include "Client_Defines.h"
#include "Level.h"
#include "TestBox.h"
#include <string>
BEGIN(Client)

class CLevel_GamePlay final : public CLevel
{
private:
	typedef struct tagQuickInfo
	{
		RECT  rc;
		_uint iIndex;
	}QUICKINFO;
	enum TEXTUREPOS {Pos_Player,Pos_Monkey, Pos_Under_Bella, Pos_Under_Yeti, Pos_END};
private:
	CLevel_GamePlay(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_GamePlay() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float fTimeDelta);
	virtual void Late_Tick(_float fTimeDelta);

public:
	HRESULT Ready_Layer_Player(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Monster(const _tchar* pLayerTag);
	HRESULT Ready_Layer_TestBox(const _tchar* pLayerTag);
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
	HRESULT Ready_Layer_CubeTerrain(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Camera(const _tchar* pLayerTag);
	HRESULT Ready_Layer_InvenUI(const _tchar* pLayerTag);
	HRESULT Ready_Layer_IconUI(const _tchar* pLayerTag);
	HRESULT Ready_Layer_PlayerInfoUI(const _tchar* pLayerTag);
	HRESULT Ready_Layer_SkillInfoUI(const _tchar* pLayerTag);
	HRESULT Ready_Layer_ItemInfoUI(const _tchar* pLayerTag);
	HRESULT Ready_Layer_SkillBookUI(const _tchar* pLayerTag);
	HRESULT Ready_Layer_HpBarUI(const _tchar* pLayerTag);
	HRESULT Ready_Layer_ExpBarUI(const _tchar* pLayerTag);

	void LoadMapData(); // 맵 불러오기

private:
	void Check_Collision_Cube(const _tchar* pLayerTag, _float fTimeDelta, TEXTUREPOS ePos);
	
private://프레임
	_uint					m_iNumRender = 0;
	_tchar					m_szFPS[MAX_PATH] = TEXT("");
	_float					m_fTimeAcc = 0.f;
	//vector<RECT>			m_vecQuickrc;
	QUICKINFO				m_eQuickInfo[8];
private:
	list<CTestBox::CUBEDESC> m_CubeInfoList;
	_float					m_fLayerPos[200][20][200];
public:
	static CLevel_GamePlay* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END

