#pragma once

#include "Base.h"


BEGIN(Engine)


class CGraphic_Device final : public CBase
{
	DECLARE_SINGLETON(CGraphic_Device)

private:
	CGraphic_Device();
	virtual ~CGraphic_Device() = default;
	// com ��ü : ������ ��� �Ծ��� ���� �ϵ��� �����Ͽ� ���� ����� �����ϴ� ��ü

public:
	LPDIRECT3DDEVICE9			Get_Device(void) { return m_pDevice; }
	LPD3DXSPRITE				Get_Sprite(void) { return m_pSprite; }
	LPD3DXFONT					Get_Font(void) { return m_pFont; }

public:
	HRESULT		InitDevice(const GRAPHIC_DESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut);
	void		SetParameters(D3DPRESENT_PARAMETERS& d3dpp);
	void		Render_Begin(void);
	void		Render_End(HWND hWnd = NULL);

private:
	LPDIRECT3D9				m_p3D;
	LPDIRECT3DDEVICE9		m_pDevice;
	GRAPHIC_DESC			m_GraphicDesc;

	// dx �󿡼� 2d �̹����� ������ִ� com��ü
	LPD3DXSPRITE			m_pSprite;
	LPD3DXFONT				m_pFont;

public:
	virtual void Free() override;
};

END