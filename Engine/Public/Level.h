#pragma once

/* Ŭ���̾�Ʈ���� ������ �������� �θ� �Ǵ� Ŭ������. */
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CLevel abstract : public CBase
{
protected:
	CLevel(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float fTimeDelta);
	virtual void Late_Tick(_float fTimeDelta);

protected:
	LPDIRECT3DDEVICE9		m_pGraphic_Device = nullptr;

public:
	virtual void Free() override;
};

END