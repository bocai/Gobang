// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gobang.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_MyPort = 0;
	m_hisPort = 0;
	m_nikeName = _T("");
	//}}AFX_DATA_INIT
	pParentDlg = (StartUpAnimation *) pParent;
	m_font.CreatePointFont(180,__T("华文楷体"));

	
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_IPADDR, m_ipAddrCtrl);
	DDX_Text(pDX, IDC_ED_SEFT_PORT, m_MyPort);
	DDV_MinMaxUInt(pDX, m_MyPort, 1024, 65535);
	DDX_Text(pDX, IDC_ED_OP_PORT, m_hisPort);
	DDV_MinMaxUInt(pDX, m_hisPort, 1024, 65535);
	DDX_Text(pDX, IDC_ED_NAME, m_nikeName);
	DDV_MaxChars(pDX, m_nikeName, 40);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDCANCEL, m_cancelBtn);
	DDX_Control(pDX, IDOK, m_OkBtn);

	DDX_Control(pDX, IDC_DIF_PRE_BTN, preDif);
	DDX_Control(pDX, IDC_DIF_NEXT_BTN, nextDif);
	DDX_Control(pDX, IDC_CORLOR_PRE_BTN, preChessCor);
	DDX_Control(pDX, IDC_CORLOR_NEXT_BTN, nextChessCor);
	DDX_Control(pDX, IDC_TIME_PRE_BTN, preTimeOut);
	DDX_Control(pDX, IDC_TIME_NEXT_BTN, nextTimeOut);
	DDX_Control(pDX, IDC_HEAD_PRE_BTN, preHead);
	DDX_Control(pDX, IDC_HEAD_NEXT_BTN, nextHead);

	DDX_Control(pDX, IDC_DIF_SHOW, difBtn);
	DDX_Control(pDX, IDC_HEAD_SHOW, headBtn);
	DDX_Control(pDX, IDC_TIME_OUT_SHOW, timeOutBtn);
	DDX_Control(pDX, IDC_COLOR_SHOW, chessColorBtn);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_DIF_PRE_BTN, OnDifPreBtn)
	ON_BN_CLICKED(IDC_DIF_NEXT_BTN, OnDifNextBtn)
	ON_BN_CLICKED(IDC_CORLOR_PRE_BTN, OnCorlorPreBtn)
	ON_BN_CLICKED(IDC_CORLOR_NEXT_BTN, OnCorlorNextBtn)
	ON_BN_CLICKED(IDC_TIME_PRE_BTN, OnTimePreBtn)
	ON_BN_CLICKED(IDC_TIME_NEXT_BTN, OnTimeNextBtn)
	ON_BN_CLICKED(IDC_HEAD_PRE_BTN, OnHeadPreBtn)
	ON_BN_CLICKED(IDC_HEAD_NEXT_BTN, OnHeadNextBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

void CConfigDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	RECT rect;
	GetClientRect(&rect);
	rect.top += 1;
	bmpPic.PaintZoom(dc, rect);
	// Do not call CDialog::OnPaint() for painting messages
	
}

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowPos(this, 0, 0, 385, 550, SWP_NOZORDER|SWP_SHOWWINDOW);
	CenterWindow(GetDesktopWindow());
	HideCaption(this->GetSafeHwnd());
	
	SetWindowEllispeFrame(this->GetSafeHwnd(), 30, 30);

	m_cancelBtn.SetWindowPos(NULL, 330, 18, 30, 30, SWP_SHOWWINDOW);
	m_OkBtn.SetWindowPos(NULL, 253, 478, 60, 30, SWP_SHOWWINDOW);
	m_OkBtn.SetRounded(TRUE);
	m_OkBtn.SetColor(CWinXPButtonST::BTNST_COLOR_BK_OUT, RGB(67,105, 225));
	m_OkBtn.SetColor(CWinXPButtonST::BTNST_COLOR_BK_IN, RGB(106,90, 215));

	m_cancelBtn.SetWindowText("");
	m_cancelBtn.SetTooltipText("关闭");
	m_cancelBtn.SetIcon(IDI_ICON_EXIT);
//	m_cancelBtn.DrawBorder(FALSE);
	m_cancelBtn.DrawTransparent(FALSE);
	
	bmpPic.loadBmpFromFile(_T("./resource/bg/theme_gray/config_1.1.bmp"));

	int bWidth = 198;
	int bHight = 248;
	preDif.SetWindowPos(NULL, bWidth, bHight, 32, 32, SWP_SHOWWINDOW);
	bHight += 60;
	preChessCor.SetWindowPos(NULL, bWidth, bHight, 32, 32, SWP_SHOWWINDOW);
	bHight += 60;
	preTimeOut.SetWindowPos(NULL, bWidth, bHight, 32, 32, SWP_SHOWWINDOW);
	bHight += 57;
	preHead.SetWindowPos(NULL, bWidth, bHight, 32, 32, SWP_SHOWWINDOW);

	bWidth = 294;
	bHight = 248;

	nextDif.SetWindowPos(NULL, bWidth, bHight, 32, 32, SWP_SHOWWINDOW);
	bHight += 60;
	nextChessCor.SetWindowPos(NULL, bWidth, bHight, 32, 32, SWP_SHOWWINDOW);
	bHight += 60;
	nextTimeOut.SetWindowPos(NULL, bWidth, bHight, 32, 32, SWP_SHOWWINDOW);
	bHight += 57;
	nextHead.SetWindowPos(NULL, bWidth, bHight, 32, 32, SWP_SHOWWINDOW);
	

	preDif.DrawTransparent(FALSE);
	preChessCor.DrawTransparent(FALSE);
	preTimeOut.DrawTransparent(FALSE);
	preHead.DrawTransparent(FALSE);
	
	nextDif.DrawTransparent(FALSE);
	nextChessCor.DrawTransparent(FALSE);
	nextTimeOut.DrawTransparent(FALSE);
	nextHead.DrawTransparent(FALSE);

	preDif.SetIcon(IDI_ICO_PRE);
	preChessCor.SetIcon(IDI_ICO_PRE);
	preTimeOut.SetIcon(IDI_ICO_PRE);
	preHead.SetIcon(IDI_ICO_PRE);
	nextDif.SetIcon(IDI_ICO_NEXT);
	nextChessCor.SetIcon(IDI_ICO_NEXT);
	nextTimeOut.SetIcon(IDI_ICO_NEXT);
	nextHead.SetIcon(IDI_ICO_NEXT);
	
	
	bHight = 244;
	bWidth = 237;

	difBtn.SetWindowPos(NULL, bWidth, bHight, 50, 40, SWP_SHOWWINDOW);
	difBtn.SetRounded(TRUE);
	difBtn.DrawTransparent(FALSE);
	difBtn.DrawBorder(FALSE);
	difBtn.SetFont(&m_font);
	
	bHight += 60;
	chessColorBtn.SetWindowPos(NULL, bWidth, bHight, 50, 40, SWP_SHOWWINDOW);
	chessColorBtn.SetRounded(TRUE);
	chessColorBtn.DrawTransparent(FALSE);
	chessColorBtn.DrawBorder(FALSE);
	chessColorBtn.SetFont(&m_font);

	bHight += 60;
	timeOutBtn.SetWindowPos(NULL, bWidth, bHight, 50, 40, SWP_SHOWWINDOW);
	timeOutBtn.SetRounded(TRUE);
	timeOutBtn.DrawTransparent(FALSE);
	timeOutBtn.DrawBorder(FALSE);
	timeOutBtn.SetFont(&m_font);

	bHight += 60;
	headBtn.SetWindowPos(NULL, bWidth, bHight, 50, 40, SWP_SHOWWINDOW);
	headBtn.SetRounded(TRUE);
	headBtn.DrawTransparent(FALSE);
	headBtn.DrawBorder(FALSE);
	headBtn.SetFont(&m_font);


	if (pParentDlg != NULL)
	{
		m_hisPort = pParentDlg->farPort;
		m_MyPort = pParentDlg->myPort;

		BYTE *ipBytes = pParentDlg->ipBytes;
		m_ipAddrCtrl.SetAddress(ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3]);

		SetDlgItemInt(IDC_DIF_SHOW, pParentDlg->configData.difficulty);
		SetDlgItemInt(IDC_TIME_OUT_SHOW, pParentDlg->configData.timeOut);
		SetDlgItemInt(IDC_HEAD_SHOW, pParentDlg->configData.headPortrait);
		m_nikeName = pParentDlg->nikeName;
		if (pParentDlg->configData.chessColor == 0)
		{
			SetDlgItemText(IDC_COLOR_SHOW, "黑");
		}
		else {
			SetDlgItemText(IDC_COLOR_SHOW, "白");
		}
		
	}
	SetDlgItemInt(IDC_ED_SEFT_PORT, m_MyPort);
	SetDlgItemInt(IDC_ED_OP_PORT, m_hisPort);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y)); 

	CDialog::OnLButtonDown(nFlags, point);
}

void CConfigDlg::OnOK() 
{
	
	if (pParentDlg != NULL) //模式选择窗口为父窗口
	{
		UpdateData(TRUE);
		pParentDlg->myPort = m_MyPort;
		pParentDlg->farPort = m_hisPort;

		BYTE *ipBytes = pParentDlg->ipBytes;
		m_ipAddrCtrl.GetAddress(ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3]);
		if (m_nikeName.GetAllocLength() > 0)
		{
			pParentDlg->nikeName = m_nikeName;
		}
		
// 		CString str;
// 		str.Format("自己%d, 对方%d", m_MyPort, m_hisPort);
// 		MessageBox(str);
	}

	CDialog::OnOK();
}

void CConfigDlg::OnDifPreBtn() 
{
	if (pParentDlg != NULL)
	{
		if (pParentDlg->configData.difficulty > 0)
		{
			pParentDlg->configData.difficulty--;
			SetDlgItemInt(IDC_DIF_SHOW, pParentDlg->configData.difficulty);
		}	
	}
	
}

void CConfigDlg::OnDifNextBtn() 
{
	if (pParentDlg != NULL)
	{
		
		if (pParentDlg->configData.difficulty < 2)
		{

			pParentDlg->configData.difficulty++;
		}
		SetDlgItemInt(IDC_DIF_SHOW, pParentDlg->configData.difficulty);
		
	}
}

void CConfigDlg::OnCorlorPreBtn() 
{
	if (pParentDlg != NULL)
	{
		
		if (pParentDlg->configData.chessColor > 0)
		{
			
			pParentDlg->configData.chessColor--;
			
		}
	
		if (pParentDlg->configData.chessColor == 0)
		{
			SetDlgItemText(IDC_COLOR_SHOW, "黑");
		}
		else if ( 1 == pParentDlg->configData.chessColor){
			SetDlgItemText(IDC_COLOR_SHOW, "白");
		}
		
	}
}

void CConfigDlg::OnCorlorNextBtn() 
{

	if (pParentDlg != NULL)
	{
		
		if (pParentDlg->configData.chessColor < 1)
		{
			
			pParentDlg->configData.chessColor++;	
			SetDlgItemInt(IDC_COLOR_SHOW, pParentDlg->configData.chessColor);
		}
	
		if (pParentDlg->configData.chessColor == 0)
		{
			SetDlgItemText(IDC_COLOR_SHOW, "黑");
		}
		else if ( 1 == pParentDlg->configData.chessColor){
			SetDlgItemText(IDC_COLOR_SHOW, "白");
		}
// 		else if (2 == pParentDlg->configData.chessColor)
// 		{
// 			SetDlgItemText(IDC_COLOR_SHOW, "红");
// 		}
	}
}

void CConfigDlg::OnTimePreBtn() 
{
	if (pParentDlg != NULL)
	{
		
		if (pParentDlg->configData.timeOut > 0)
		{
			
			pParentDlg->configData.timeOut--;
			SetDlgItemInt(IDC_TIME_OUT_SHOW, pParentDlg->configData.timeOut);
		}
		
	}
}

void CConfigDlg::OnTimeNextBtn() 
{
	
	if (pParentDlg != NULL)
	{
		
		if (pParentDlg->configData.timeOut < 25)
		{
			
			pParentDlg->configData.timeOut++;
			SetDlgItemInt(IDC_TIME_OUT_SHOW, pParentDlg->configData.timeOut);
		}
		
		
	}
}

void CConfigDlg::OnHeadPreBtn() 
{
	if (pParentDlg != NULL)
	{
		
		if (pParentDlg->configData.headPortrait > 0)
		{
			
			pParentDlg->configData.headPortrait--;
		
			SetDlgItemInt(IDC_HEAD_SHOW, pParentDlg->configData.headPortrait);
		
		}
	
		
	}
	
}

void CConfigDlg::OnHeadNextBtn() 
{
	if (pParentDlg != NULL)
	{
		
		if (pParentDlg->configData.headPortrait < 10)
		{
			
			pParentDlg->configData.headPortrait++;
		
			SetDlgItemInt(IDC_HEAD_SHOW, pParentDlg->configData.headPortrait);
		
		}
		
		
	}
}
