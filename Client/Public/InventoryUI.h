#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CInventoryUI final : public CGameObject
{
private:
	typedef struct tagInventory
	{
		RECT	rcRect;
		_float  RectX;
		_float  RectY;
	}INVEN;

private:
	CInventoryUI(LPDIRECT3DDEVICE9 pGraphic_Device);
	CInventoryUI(const CInventoryUI& rhs);
	virtual ~CInventoryUI() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta)override;
	virtual void Late_Tick(_float fTimeDelta)override;
	virtual HRESULT Render() override;
	void Show_Inven();

	vector<INVEN> Get_InvenInfo() { return m_vecInven; }
	_bool Get_OnCheck() { return m_bOnCheck; }

private: /* For.Components */
	CTexture*				m_pTextureCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;


private:
	_float4x4				m_ProjMatrix;
	_float					m_fX, m_fY, m_fSizeX, m_fSizeY;
	_bool					m_bOnCheck = false;
	_bool					m_bMoveUi = false;
	_float2					m_fMousePos;
	_float2					m_fDifDis;
	RECT					m_rcRect;
	vector<INVEN>			m_vecInven;
	INVEN					m_Inven;
	_float					m_fRectX = 0.f;
	_float					m_fRectY = 0.f;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_RenderState();
	HRESULT Release_RenderState();

public:
	static CInventoryUI* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;
};

END