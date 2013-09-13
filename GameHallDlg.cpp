// GameHallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gobang.h"
#include "GameHallDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameHallDlg dialog


CGameHallDlg::CGameHallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameHallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGameHallDlg)
	//}}AFX_DATA_INIT
}


void CGameHallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameHallDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_TAB_ROOMS, m_tabRooms);
}


BEGIN_MESSAGE_MAP(CGameHallDlg, CDialog)
	//{{AFX_MSG_MAP(CGameHallDlg)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameHallDlg message handlers

void CGameHallDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CGameHallDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	
	HideCaption(this->GetSafeHwnd());
	SetWindowEllispeFrame(this->GetSafeHwnd(), 30, 30);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGameHallDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y)); 
	CDialog::OnLButtonDown(nFlags, point);
}
