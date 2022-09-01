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
	bool		Key_Up(int _Key);		// 누르고 있다가 뗐을 때
	bool		Key_Down(int _Key);		// 눌렀을 때

private:
	bool			m_bKeyState[VK_MAX];

private:
	virtual void Free() override;
};

END