#pragma once

#include "Component.h"

/* V : Vertex, I : Index, Buffer : Memory */
/* �θ�Ŭ���� : Rect, Cube, Terrain etc*/

BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Render();

protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVB = nullptr;
	_uint						m_iNumVertices = 0;
	_uint						m_iStride = 0; /* ������ ũ��(byte) */
	_ulong						m_dwFVF = 0;
	D3DPRIMITIVETYPE			m_ePrimitiveType;
	_uint						m_iNumPrimitive = 0;

protected:
	LPDIRECT3DINDEXBUFFER9		m_pIB = nullptr;
	_uint						m_iIndicesByte = 0;
	D3DFORMAT					m_eIndexFormat;

protected:
	HRESULT Ready_Vertex_Buffer();
	HRESULT Ready_Index_Buffer();



public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END