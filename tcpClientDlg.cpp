// tcpClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gobang.h"
#include "tcpClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CtcpClientDlg dialog


CtcpClientDlg::CtcpClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtcpClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CtcpClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CtcpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CtcpClientDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT_IP, m_cedIp);
	DDX_Control(pDX, IDC_EDIT_PORT, m_cedPort);
	DDX_Control(pDX, IDC_ED_MSG, m_ShowMsg);
}


BEGIN_MESSAGE_MAP(CtcpClientDlg, CDialog)
	//{{AFX_MSG_MAP(CtcpClientDlg)
	ON_BN_CLICKED(IDC_CON_SVR, OnConSvr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CtcpClientDlg message handlers

void CtcpClientDlg::OnConSvr() 
{
	CString ipStr;
	char ip[18] = {'\0'};

	GetDlgItemText(IDC_EDIT_IP,ip, 18);
	UINT port =	GetDlgItemInt(IDC_EDIT_PORT);

	CString msg;
// 	msg.Format("%s:%d", ip, port);
// 	MessageBox(msg);

	tcpMsger.initSock(ip, port);
	if(tcpMsger.connectServer() == FALSE) {
		MessageBox("连接失败");
	}
	else {
		appenStrToEdit(CString("连接成功"));
	}

// 	if (tcpMsger.Create())
// 	{
// 		int ret = tcpMsger.Connect(tcpMsger.getConnectIp(), 5050 );
// 		if (ret < 0)
// 		{
// 			MessageBox("连接失败");
// 		}
// 	}
	

}

BOOL CtcpClientDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cedIp.SetFocus();
	CEdit *pEd = (CEdit *)GetDlgItem(IDC_EDIT_IP) ;
	pEd->SetFocus();
	pEd->SetWindowText(tcpMsger.getConnectIp());
	SetDlgItemInt(IDC_EDIT_PORT, tcpMsger.getConnectPort());
	
	return FALSE;
	//return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CtcpClientDlg::appenStrToEdit(CString str)
{
	msgStr += str;
	msgStr += "\r\n";

	m_ShowMsg.SetWindowText(msgStr);
	return TRUE;
}

void CtcpClientDlg::OnOK() 
{
	// TODO: Add extra validation here
	char str[50];
	memset(str, 0, sizeof(str));

	GetDlgItemText(IDC_ED_SEND, str, sizeof(str));
	
	if (tcpMsger.Send(str, sizeof(str)) > 0)
	{
		appenStrToEdit(str);
		CEdit *pEd = (CEdit *) GetDlgItem(IDC_ED_SEND);
		pEd->SetWindowText("");
		pEd->SetFocus();
	}
	
	
//	CDialog::OnOK();
}
