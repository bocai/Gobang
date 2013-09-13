#if !defined(AFX_TCPMESSAGER_H__590D1514_7E0F_4CF6_AECB_23AE14A12E75__INCLUDED_)
#define AFX_TCPMESSAGER_H__590D1514_7E0F_4CF6_AECB_23AE14A12E75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TcpMessager.h : header file
//

//#include "tcpClientDlg.h"
class CtcpClientDlg;
/////////////////////////////////////////////////////////////////////////////
// CTcpMessager command target
// 游戏大厅版本Tcp传输
class CTcpMessager : public CSocket
{
// Attributes
public:

// Operations
public:
	CTcpMessager();

	virtual ~CTcpMessager();
	CTcpMessager(CtcpClientDlg *pdlg);
// Overrides
public:
	UINT getConnectPort();
	CString & getConnectIp();
	BOOL connectServer();
	BOOL initSock(CString ipStr, UINT port);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTcpMessager)
	public:
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CTcpMessager)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	UINT connectPort;
	CString connectIp;
	BOOL isConnect;
	CtcpClientDlg *pDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCPMESSAGER_H__590D1514_7E0F_4CF6_AECB_23AE14A12E75__INCLUDED_)
