// NetwordSeting.cpp : implementation file
//

#include "stdafx.h"
#include "gobang.h"
#include "NetwordSeting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetwordSeting dialog


CNetwordSeting::CNetwordSeting(CWnd* pParent /*=NULL*/)
	: CDialog(CNetwordSeting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetwordSeting)
	m_port = 0;


	//}}AFX_DATA_INIT
	ipBytes[0] = 127;
	ipBytes[1] = 0;
	ipBytes[2] = 0;
	ipBytes[3] = 1;

//	m_ipAddrCtrl.SetAddress(ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3]);
}


void CNetwordSeting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetwordSeting)
	DDX_Control(pDX, IDC_IP_ADDRESS, m_ipAddrCtrl);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDV_MinMaxUInt(pDX, m_port, 1025, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetwordSeting, CDialog)
	//{{AFX_MSG_MAP(CNetwordSeting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetwordSeting message handlers

void CNetwordSeting::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	
	int count = m_ipAddrCtrl.GetAddress(ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3]);
// 	if (count == 4)
// 	{
// 		CString ipStr;
// 		ipStr.Format("%d.%d.%d.%d £º%d", ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3], m_port );
// 		MessageBox(ipStr);
// 
// 	}
	

	CDialog::OnOK();
}

BOOL CNetwordSeting::getIpAddr(BYTE &by0, BYTE &by1, BYTE &by2, BYTE &by3)
{
	by0 = ipBytes[0];
	by1 = ipBytes[1];
	by2 = ipBytes[2];
	by3 = ipBytes[3];
	
	return TRUE;
}

UINT CNetwordSeting::getPort()
{
	return m_port;
}

BOOL CNetwordSeting::setPort(UINT port)
{
	m_port = port;

	return TRUE;
}

BOOL CNetwordSeting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CEdit *pEdPort = (CEdit *)GetDlgItem(IDC_EDIT_PORT);
	CString strPort;
	strPort.Format("%d", m_port);
	pEdPort->SetWindowText(strPort);
	
	m_ipAddrCtrl.SetAddress(ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3]);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CNetwordSeting::setIpByte(BYTE by0, BYTE by1, BYTE by2, BYTE by3)
{
	ipBytes[0] = by0;
	ipBytes[1] = by1;
	ipBytes[2] = by2;
	ipBytes[3] = by3;

	return TRUE;
}
