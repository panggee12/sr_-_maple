//#pragma once
//
//#include "Component.h"
//
//BEGIN(Engine)
//
//class CKeyMgr abstract :public CComponent
//{
//	DECLARE_SINGLETON(CKeyMgr)
//
//
//private:
//	CKeyMgr();
//	virtual ~CKeyMgr()=default;
//
//public:
//	bool		Key_Pressing(int _Key);
//	bool		Key_Up(int _Key);		// ������ �ִٰ� ���� ��
//	bool		Key_Down(int _Key);		// ������ ��
//
//public:
//	CKeyMgr*		Get_Instance(void)
//	{
//		if (nullptr == m_pInstance)
//			m_pInstance = new CKeyMgr;
//
//		return m_pInstance;
//	}
//
//	//void			Destroy_Instance(void);
//
//private:
//	CKeyMgr*		m_pInstance;
//	bool						m_bKeyState[VK_MAX];
//
//};
//
//END