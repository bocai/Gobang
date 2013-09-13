// UdpMessager.cpp : implementation file
//

#include "stdafx.h"
#include "gobang.h"
#include "UdpMessager.h"
#include "GobangDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUdpMessager


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CUdpMessager, CSocket)
	//{{AFX_MSG_MAP(CUdpMessager)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CUdpMessager member functions

CUdpMessager * CUdpMessager::pInstance = NULL;
CWnd * CUdpMessager::PparentWnd = NULL;

CUdpMessager::CUdpMessager()
{
}

CUdpMessager::~CUdpMessager()
{

}


CUdpMessager * CUdpMessager::getMessagerInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new CUdpMessager();
	}

	return pInstance;
}

void CUdpMessager::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	MsgStruct msgStruct;

	memset(&msgStruct, 0, sizeof(msgStruct));

/* (1) */
// 	SOCKADDR_IN romoteAddr;
// 	
// 	memset(&romoteAddr, 0, sizeof(romoteAddr));
// 	romoteAddr.sin_port = htons(5050);
// 	romoteAddr.sin_family = AF_INET;
// 	romoteAddr.sin_addr.S_un.S_addr = inet_addr(ipStr);
// 
// 	int len = sizeof(romoteAddr);
 
// 	if (ReceiveFrom(buf, sizeof(buf), (SOCKADDR *)&romoteAddr, &len) <= 0)
// 	{
// 		AfxMessageBox("接收数据出错！");
// 		
// 	}
// 	else {
// 		buf[len] = '\0';
// 		AfxMessageBox(buf);
// 	}

	/* (2) */
	CString ipString;
	UINT port = 0;
	ReceiveFrom(&msgStruct, sizeof(msgStruct), ipString, port);

	if (NULL != PparentWnd)
	{
		((CGobangDlg *)PparentWnd)->handleNetMsg(&msgStruct, sizeof(msgStruct), ipString, port);
	}
// 		CString msg;
// 		msg.Format("接收:%s:%d %s", ipStr,port, buf);
// 		AfxMessageBox(msg);
	

	CSocket::OnReceive(nErrorCode);
}


BOOL CUdpMessager::initParentWnd(CWnd *parentWnd)
{
	if (!parentWnd)
	{
		return FALSE;
	}

	PparentWnd = parentWnd;

	return TRUE;
}

BOOL CUdpMessager::sendMsg(MsgStruct *msgStruct, CGamePlayer *pPlayer)
{
	if (NULL == msgStruct)
	{
		return FALSE;
	}
	UINT port = pPlayer->getPort();
	CString &ipstr = pPlayer->getIpString();
	int ret = SendTo(msgStruct, sizeof(*msgStruct), port, ipstr);
	if (ret <= 0)
	{
		return FALSE;
	}

	return TRUE;
}

CString CUdpMessager::getHostIpstr()
{
	//本机名称获取
	CString strName = _T("");
	gethostname(strName.GetBuffer(1024), 1024);
	strName.ReleaseBuffer();

	CString ipStrs = _T("");
	//本机信息获取
	struct hostent* pHostEnt = gethostbyname(strName);
	if (pHostEnt == NULL)
	{
		return ipStrs;
	}
	
	//本机IP地址获取
	

	ipStrs += _T("本机IP地址是:\n");
	int n = 0;

	while (pHostEnt->h_addr_list[n] != NULL)
	{
		CString strTemp = _T("");
		strTemp.Format(_T("%d.%d.%d.%d\n"),
			(pHostEnt->h_addr_list[n][0] & 0x00FF),
			(pHostEnt->h_addr_list[n][1] & 0x00FF),
			(pHostEnt->h_addr_list[n][2] & 0x00FF),
			(pHostEnt->h_addr_list[n][3] & 0x00FF));
	//	ipStrs += strTemp;
		ipStrs = strTemp; break;
		n++;
	}

//	AfxMessageBox(ipStrs);

	return ipStrs;
}

BOOL CUdpMessager::destoryInstance()
{
	if (pInstance != NULL)
	{
		
		delete pInstance;
		pInstance = NULL;
	}

	return TRUE;
}
