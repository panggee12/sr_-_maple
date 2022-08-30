#include "..\Public\Texture.h"

CTexture::CTexture(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
	ZeroMemory(&m_FrameTexture, sizeof(FRAMETEXTURE));
}

CTexture::CTexture(const CTexture & rhs)
	: CComponent(rhs)
	, m_Textures(rhs.m_Textures)
	, m_iNumTextures(rhs.m_iNumTextures)
{
	for (auto& pTexture : m_Textures)
		Safe_AddRef(pTexture);
}

//Texture.png
//Texture%d.png

void CTexture::Test()
{
	int a = 10;
}

HRESULT CTexture::Initialize_Prototype(TYPE eType, const _tchar * pTextureFilePath, _uint iNumTexture)
{
	m_iNumTextures = iNumTexture;

	_tchar			szFullPath[MAX_PATH] = TEXT("");

	for (_uint i = 0; i < m_iNumTextures; ++i)
	{
		IDirect3DBaseTexture9*			pTexture = nullptr;

		wsprintf(szFullPath, pTextureFilePath, i);
		
		HRESULT hr = eType == TYPE_DEFAULT ? D3DXCreateTextureFromFile(m_pGraphic_Device, szFullPath, (LPDIRECT3DTEXTURE9*)&pTexture) : D3DXCreateCubeTextureFromFile(m_pGraphic_Device, szFullPath, (LPDIRECT3DCUBETEXTURE9*)&pTexture);

		if (FAILED(hr))
			return E_FAIL;

		m_Textures.push_back(pTexture);
	}

	return S_OK;
}

HRESULT CTexture::Initialize(void * pArg)
{
	if (nullptr != pArg)
		memcpy(&m_FrameTexture, pArg, sizeof(FRAMETEXTURE));

	return S_OK;
}

HRESULT CTexture::Bind_OnGraphicDev(_uint iIndex)
{
	if (iIndex >= m_iNumTextures)
		return E_FAIL;

	return m_pGraphic_Device->SetTexture(0, m_Textures[iIndex]);	
}
//������ ������ �Լ�
HRESULT CTexture::Bind_FrameMove()
{
	if (m_FrameTexture.FirstFrame < m_FrameTexture.OriginFrame)
		m_FrameTexture.FirstFrame = m_FrameTexture.OriginFrame;
	else if(m_FrameTexture.FirstFrame > m_FrameTexture.EndFrame)
		m_FrameTexture.FirstFrame = m_FrameTexture.OriginFrame;

	m_FrameTexture.FirstFrame += m_FrameTexture.FrameSpeed;

	if (m_FrameTexture.FirstFrame > m_FrameTexture.EndFrame)
	{
		m_FrameTexture.FirstFrame = m_FrameTexture.OriginFrame;
	}

	m_pGraphic_Device->SetTexture(0, m_Textures[m_FrameTexture.FirstFrame]);

	return S_OK;
}

CTexture * CTexture::Create(LPDIRECT3DDEVICE9 pGraphic_Device, TYPE eType, const _tchar * pTextureFilePath, _uint iNumTexture)
{
	CTexture*	pInstance = new CTexture(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype(eType, pTextureFilePath, iNumTexture)))
	{
		ERR_MSG(TEXT("Failed to Created : CTexture"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CTexture::Clone(void* pArg)
{
	CTexture*	pInstance = new CTexture(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CTexture"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTexture::Free()
{
	__super::Free();

	for (auto& pTexture : m_Textures)
		Safe_Release(pTexture);

	m_Textures.clear();
}
