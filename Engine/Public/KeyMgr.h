#pragma once

#include "Base.h"

BEGIN(Engine)

class CKeyMgr final :public CBase
{
	DECLARE_SINGLETON(CKeyMgr)
private:
	CKeyMgr();
	virtual ~CKeyMgr() = default;

public:
	bool		Key_Pressing(int _Key);
	bool		Key_Up(int _Key);		// ������ �ִٰ� ���� ��
	bool		Key_Down(int _Key);		// ������ ��

private:
	bool			m_bKeyState[VK_MAX];

private:
	virtual void Free() override;
};

END