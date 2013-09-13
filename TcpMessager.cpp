// TcpMessager.cpp : implementation file
//

#include "stdafx.h"
#include "gobang.h"
#include "TcpMessager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTcpMessager

CTcpMessager::CTcpMessager()
{
	isConnect = FALSE;
	connectIp = "192.168.0.159";
	connectPort = 5050;
}

CTcpMessager::CTcpMessager(CtcpClientDlg *pdlg)
{

	pDlg = pdlg;
}
CTcpMessager::~CTcpMessager()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CTcpMessager, CSocket)
	//{{AFX_MSG_MAP(CTcpMessager)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CTcpMessager member functions

int CTcpMessager::Receive(void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CSocket::Receive(lpBuf, nBufLen, nFlags);
}

BOOL CTcpMessager::initSock(CString ipStr, UINT port)
{
	if (ipStr.GetLength() < 7)
	{
		return FALSE;
	}
	connectIp = ipStr;
	connectPort = port;

	return TRUE;
}

BOOL CTcpMessager::connectServer()
{
	if (isConnect)
	{
		return FALSE;
	}
	if (Create())
	{	
		if (Connect(connectIp, connectPort) <= 0)
		{
			AfxMessageBox("连接服务器失败");
			isConnect = FALSE;
			return FALSE;
		}
	}
	


	isConnect = TRUE;
	return TRUE;
}

CString & CTcpMessager::getConnectIp()
{
	return connectIp;
}

UINT CTcpMessager::getConnectPort()
{
	return connectPort;
}
