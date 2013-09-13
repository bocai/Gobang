// GobangAboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gobang.h"
#include "GobangAboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGobangAboutDlg dialog


CGobangAboutDlg::CGobangAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGobangAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGobangAboutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	bkImg = ABOUT_IMG;
}
CGobangAboutDlg::~CGobangAboutDlg()
{
	
	bmpPic.unLoad();
}

void CGobangAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGobangAboutDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
//	DDX_Control(pDX, IDOK, m_okBtn);
	DDX_Control(pDX, IDC_QUIT_ABOUT, m_quitBtn);
}

BEGIN_MESSAGE_MAP(CGobangAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CGobangAboutDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_QUIT_ABOUT, OnQuitAbout)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGobangAboutDlg message handlers

BOOL CGobangAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowPos(this, 0, 0, 384, 548, SWP_NOZORDER|SWP_SHOWWINDOW);
	CenterWindow(GetDesktopWindow());
	HideCaption(this->GetSafeHwnd());
	SetWindowEllispeFrame(this->GetSafeHwnd(), 30, 30);

	m_quitBtn.SetWindowPos(NULL, 330, 18, 30, 30, SWP_SHOWWINDOW);
//	m_okBtn.SetWindowPos(NULL, 270, 470, 50, 40, SWP_SHOWWINDOW);

	m_quitBtn.SetWindowText("");
	m_quitBtn.SetTooltipText("¹Ø±Õ");
	m_quitBtn.SubclassDlgItem(IDI_ICON_EXIT, this);
	m_quitBtn.SetIcon(IDI_ICON_EXIT);
	m_quitBtn.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(90,90,90));
	m_quitBtn.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255,0,0));
 	m_quitBtn.DrawBorder(FALSE);
 //	m_quitBtn.DrawTransparent(FALSE);

//	m_okBtn.DrawBorder(FALSE);
	if (ABOUT_IMG == bkImg)
	{
		bmpPic.loadBmpFromFile(_T("./resource/bg/theme_gray/game_about_1.0.bmp"));
	}
	else if (HELP_IMG == bkImg)
	{
		bmpPic.loadBmpFromFile(_T("./resource/bg/theme_gray/game_rule.bmp"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGobangAboutDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	RECT rect;
	GetClientRect(&rect);
	rect.top += 1;
	bmpPic.PaintZoom(dc, rect);
	if (bkImg == ABOUT_IMG)
	{
		dc.SetBkMode(TRANSPARENT);
		TextOut(dc, 270, 400, "»Æ²©Ø”", 6);
	}

	// Do not call CDialog::OnPaint() for painting messages
}

void CGobangAboutDlg::OnQuitAbout() 
{
	// TODO: Add your control notification handler code here
		CDialog::OnCancel();
}

void CGobangAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y)); 
	CDialog::OnLButtonDown(nFlags, point);
}

BOOL CGobangAboutDlg::setBkImg(ShowImg img)
{
	bkImg = img;

	return TRUE;
}
