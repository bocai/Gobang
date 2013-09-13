#if !defined(AFX_UDPMESSAGER_H__C50FC0A9_4D83_4C53_9AA2_35A54FE7AAD6__INCLUDED_)
#define AFX_UDPMESSAGER_H__C50FC0A9_4D83_4C53_9AA2_35A54FE7AAD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UdpMessager.h : header file
#include "GamePlayer.h"


/////////////////////////////////////////////////////////////////////////////
// CUdpMessager command target
// 联机对战时Udp传输消息 (使用单例模式)
class CUdpMessager : public CSocket
{
// Attributes
public:
	
// Operations
public:
	static	CUdpMessager *getMessagerInstance();
	// 处理消息
	static BOOL initParentWnd(CWnd *ParentWnd);
	
	virtual ~CUdpMessager();

// Overrides
public:
	static BOOL destoryInstance();
	static CString getHostIpstr();
	BOOL sendMsg(MsgStruct *msgStruct, CGamePlayer *pPlayer);
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUdpMessager)
	public:
	virtual void OnReceive(int nErrorCode);  // 收到消息交由游戏窗口类处理
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CUdpMessager)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	static	CUdpMessager *pInstance;
private:
	static CWnd *PparentWnd;
	CUdpMessager();

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPMESSAGER_H__C50FC0A9_4D83_4C53_9AA2_35A54FE7AAD6__INCLUDED_)
