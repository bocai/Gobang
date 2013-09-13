// StartUpAnimation.cpp : implementation file
//

#include "stdafx.h"
#include "gobang.h"
#include "StartUpAnimation.h"
#include "GobangAboutDlg.h"
#include "ConfigDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StartUpAnimation dialog


StartUpAnimation::StartUpAnimation(CWnd* pParent /*=NULL*/)
	: CDialog(StartUpAnimation::IDD, pParent)
{
	//{{AFX_DATA_INIT(StartUpAnimation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	pCgobangDlg = pPgobangDlg = pNgobangDlg = NULL;
	lastForeground = MAIN_WINDOW;
	
	ipBytes[0] = 127;
	ipBytes[1] = 0;
	ipBytes[2] = 0;
	ipBytes[3] = 1;
	myPort = 5050;
	farPort = 5051;
	
	configData.difficulty = 1;
	configData.chessColor = 0;
	configData.headPortrait = 1;
	configData.timeOut = 15;
	nikeName = "bocaihuang";


	
	singlePath = _T("./resource/buttons/theme_gray/p2p.bmp");
	computerPath = _T("./resource/buttons/theme_gray/vsComputer.bmp");
	networdPath = _T("./resource/buttons/theme_gray/vsNetword.bmp");
	settingPath = _T("./resource/buttons/theme_gray/gameConfig.bmp");
	exitPath = _T("./resource/buttons/theme_gray/exitGame.bmp");

	
}

StartUpAnimation::~StartUpAnimation()
{
	if (pCgobangDlg != NULL)
	{
		delete pCgobangDlg;
	}
	if (pNgobangDlg != NULL)
	{
		delete pNgobangDlg;
	}
	if (pPgobangDlg)
	{
		delete pPgobangDlg;
	}
}

void StartUpAnimation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StartUpAnimation)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDCANCEL, cancelBtn);
	DDX_Control(pDX, IDC_MINWIN_BTN, minSizeBtn);
	DDX_Control(pDX, IDC_TOTRAY_BTN, toTrayBtn);
	DDX_Control(pDX, IDC_SINGLE_BTN, m_singleBtn);
  	DDX_Control(pDX, IDC_VS_COMPUTER_BTN, m_computerBtn);
 	DDX_Control(pDX, IDC_VS_NETWORD_BTN, m_networdBtn);
	DDX_Control(pDX, IDC_SET_BTN, m_settingBtn);
	DDX_Control(pDX, IDC_EXIT_BTN, m_exitBtn);
	DDX_Control(pDX, IDC_ABOUT, m_aboutBtn);

}


BEGIN_MESSAGE_MAP(StartUpAnimation, CDialog)
	//{{AFX_MSG_MAP(StartUpAnimation)
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_NOTIFY_GOBANG_TRAY, OnTrayIcon)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SINGLE_BTN, OnSingleBtn)
	ON_BN_CLICKED(IDC_VS_COMPUTER_BTN, OnVsComputerBtn)
	ON_BN_CLICKED(IDC_VS_NETWORD_BTN, OnVsNetwordBtn)
	ON_BN_CLICKED(IDC_EXIT_BTN, OnExitBtn)
	ON_BN_CLICKED(IDC_MINSIZE_BTN, OnMinsizeBtn)
	ON_BN_CLICKED(IDC_TOTRAY_BTN, OnTotrayBtn)
	ON_COMMAND(IDM_GAME_EXIT, OnGameExit)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_WM_SETCURSOR()
	ON_COMMAND(IDM_RULE_HELP, OnRuleHelp)
	ON_BN_CLICKED(IDC_SET_BTN, OnSetBtn)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StartUpAnimation message handlers

BOOL StartUpAnimation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_hCursor = LoadCursorFromFile(_T("./resource/ani/normal.cur")); 

	if (NULL == m_hCursor)
	{
		MessageBox("资源文件无法打开，请检查程序所在的路径是否正确？");
		exit(-1);
	}
	m_selectBtnCur = LoadCursorFromFile(_T("./resource/ani/onSelectBtn.ani"));
	SetWindowPos(this, 0,0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOZORDER);
	CenterWindow(this);
	SetWindowEllispeFrame(this->GetSafeHwnd(), 20, 20); // 窗口边角圆弧	

//	minSizeBtn.SetWindowPos(NULL, 4, 0, 32, 32, SWP_SHOWWINDOW);

	cancelBtn.SetWindowPos(NULL, SCREEN_WIDTH-42, 0, 32, 32, SWP_SHOWWINDOW);
	
	m_aboutBtn.SetWindowPos(NULL, SCREEN_WIDTH - 74, 0, 32, 32, SWP_SHOWWINDOW);
	toTrayBtn.SetWindowPos(NULL, SCREEN_WIDTH - 108, 0, 32, 32, SWP_SHOWWINDOW);

	int width = 250;
	int hight = 70;
	int py = 180;
	m_computerBtn.SetWindowPos(NULL, 380, py, width, hight, SWP_SHOWWINDOW);
	py += 70;
	m_singleBtn.SetWindowPos(NULL, 380, py, width, hight, SWP_SHOWWINDOW);
 	py += 70;
	m_networdBtn.SetWindowPos(NULL, 380, py, width, hight, SWP_SHOWWINDOW);
 	py += 70;
 	m_settingBtn.SetWindowPos(NULL, 380, py, width, hight, SWP_SHOWWINDOW);
	py += 70;
 	m_exitBtn.SetWindowPos(NULL, 380, py, width, hight, SWP_SHOWWINDOW);

	m_aboutBtn.SetIcon(IDI_ICO_ABOUT, (int)BTNST_AUTO_GRAY);
	m_aboutBtn.DrawTransparent(FALSE);
	m_aboutBtn.SetWindowText("");
	m_aboutBtn.SetTooltipText("关于");

// 	minSizeBtn.SetIcon(IDI_MIN_SIZE);
// 	minSizeBtn.DrawTransparent(FALSE);
// 	minSizeBtn.SetTooltipText("最小化");
// 	minSizeBtn.SetWindowText("");
	minSizeBtn.ShowWindow(SW_HIDE);

	toTrayBtn.SetIcon(IDI_TOTRAY, IDI_ICON_XU);
//	toTrayBtn.DrawBorder(FALSE);
	toTrayBtn.DrawTransparent(FALSE);
	toTrayBtn.SetWindowText("");
	toTrayBtn.SetTooltipText("最小化到托盘");
	
	cancelBtn.SetIcon(IDI_ICON_EXIT, (int)BTNST_AUTO_GRAY);
//	cancelBtn.DrawBorder(FALSE);
	cancelBtn.DrawTransparent(FALSE);
	cancelBtn.SetTooltipText("退出");
	cancelBtn.SetWindowText("");


	cpicBg.loadBmpFromFile(_T("./resource/bg/theme_gray/select_mode_bg.bmp"));
	
	// 加载游戏模式选择界面上的按钮bmp
	HBITMAP hBmp, hBmpIn = NULL;
	COLORREF maskColor = RGB(90, 90, 90);
	hBmpIn = getBmpImg(CString("./resource/buttons/theme_gray/vsComputerLight.bmp"));
	hBmp = getBmpImg(computerPath);
	if (hBmp && hBmpIn)
	{
		m_computerBtn.SetBitmaps(hBmpIn, maskColor, hBmp, maskColor);
		m_computerBtn.SetWindowText("");
		//	m_computerBtn.DrawBorder(FALSE);
		m_computerBtn.DrawTransparent(FALSE);
	}

	hBmp = getBmpImg(singlePath);
	hBmpIn = getBmpImg(CString("./resource/buttons/theme_gray/p2pLight.bmp"));
	if (hBmp && hBmpIn)
	{
		m_singleBtn.SetBitmaps(hBmpIn, maskColor, hBmp, maskColor);
		m_singleBtn.SetWindowText("");
		//	m_singleBtn.DrawBorder(FALSE);
		m_singleBtn.DrawTransparent(FALSE);
	}
	hBmp = getBmpImg(networdPath);
	hBmpIn = getBmpImg(CString("./resource/buttons/theme_gray/vsNetwordLight.bmp"));
	if (hBmp && hBmpIn)
	{
		m_networdBtn.SetBitmaps(hBmpIn, maskColor, hBmp, maskColor);
		m_networdBtn.SetWindowText("");
		//	m_networdBtn.DrawBorder(FALSE);
		m_networdBtn.DrawTransparent(FALSE);
	}
	
	hBmp = getBmpImg(settingPath);
	hBmpIn = getBmpImg(CString("./resource/buttons/theme_gray/gameConfigLight.bmp"));
	if (hBmp)
	{
		m_settingBtn.SetBitmaps(hBmpIn, maskColor, hBmp, maskColor);
		m_settingBtn.SetWindowText("");
	//	m_settingBtn.DrawBorder(FALSE);
		m_settingBtn.DrawTransparent(FALSE);
	
	}

	hBmp = getBmpImg(exitPath); 
	hBmpIn = getBmpImg(CString("./resource/buttons/theme_gray/exitGameLight.bmp"));
	if (hBmp)
	{
		m_exitBtn.SetBitmaps(hBmpIn, maskColor, hBmp, maskColor);
		m_exitBtn.SetWindowText("");
		
	//	m_exitBtn.DrawBorder(FALSE);
		m_exitBtn.DrawTransparent(FALSE);
	}
	
	m_singleBtn.SetPlaySound(true, "IDR_HVER");
	m_computerBtn.SetPlaySound(true, "IDR_HVER");
	m_networdBtn.SetPlaySound(true, "IDR_HVER");
	m_settingBtn.SetPlaySound(true, "IDR_HVER");
	m_exitBtn.SetPlaySound(true, "IDR_HVER");


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void StartUpAnimation::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CGobangAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
void StartUpAnimation::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

		//欺骗 Windows，发送拖动标题栏的消息
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y)); 

	CDialog::OnLButtonDown(nFlags, point);
}



void StartUpAnimation::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages

	CRect rect;
	GetClientRect(&rect);
	cpicBg.Paint(dc, rect);

}

void StartUpAnimation::OnCancel() 
{
	// TODO: Add extra cleanup here
	if (NULL != pCgobangDlg)
	{
		delete pCgobangDlg;
		pCgobangDlg = NULL;
		// 		CString msg;
		// 		msg.Format("ok");
		// 		MessageBox(msg);
	}
	if (nid.hWnd == this->m_hWnd)
	{
		DeleteTray();
	}

	CDialog::OnCancel();
}

void StartUpAnimation::OnSingleBtn() 
{
	// TODO: Add your control notification handler code here
	
	if (NULL == pPgobangDlg )
	{
		pPgobangDlg = new CGobangDlg(this);
		
		pPgobangDlg->Create(IDD_GOBANG_DIALOG);
	}
	if (NULL != pPgobangDlg)
	{	
		this->ShowWindow(SW_HIDE);
		pPgobangDlg->setGameMode(SINGLE_MODE);
		pPgobangDlg->ShowWindow(SW_SHOWNORMAL | SW_NORMAL);
	}
	
}

void StartUpAnimation::OnVsComputerBtn() 
{
	// TODO: Add your control notification handler code here
	

	int nResponse = 0;
//	CGobangDlg gobangDlg;
	if (NULL == pCgobangDlg )
	{
		pCgobangDlg = new CGobangDlg(this);
		pCgobangDlg->setGameMode(COMPUTER_MODE);
		pCgobangDlg->Create(IDD_GOBANG_DIALOG);
	}

	if (NULL != pCgobangDlg)
	{
		this->ShowWindow(SW_HIDE);
		pCgobangDlg->setGameMode(COMPUTER_MODE);
		pCgobangDlg->ShowWindow(SW_SHOWNORMAL | SW_NORMAL);
	}
}

void StartUpAnimation::OnVsNetwordBtn() 
{
	
	if (NULL == pNgobangDlg )
	{
		pNgobangDlg = new CGobangDlg(this);
		pNgobangDlg->setGameMode(ONLINE_MODE);
		pNgobangDlg->Create(IDD_GOBANG_DIALOG);
	}
	if (NULL != pNgobangDlg)
	{
		this->ShowWindow(SW_HIDE);
		pNgobangDlg->setGameMode(ONLINE_MODE);
		pNgobangDlg->ShowWindow(SW_SHOWNORMAL | SW_NORMAL);
	}
	
}


CGobangDlg * StartUpAnimation::getGobangDlg()
{
	return NULL;
	return pCgobangDlg;
}

void StartUpAnimation::OnExitBtn() 
{
	// TODO: Add your control notification handler code here
	
	this->OnCancel();
//	MessageBox("exit");
}

void StartUpAnimation::ToTray(ForegroundWindow fw)
{
// 	if (LOCAL_SINGLE == fw)
// 	{
// 		lastForeground = fw;
// 	}
// 	else if (VS_COMPUTER == fw)
// 	{
// 		lastForeground = fw;
// 	}
// 	else if (VS_ONLINE == fw)
// 	{
// 		lastForeground = fw;
// 	}
	
	lastForeground = fw;

	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);   
	nid.hWnd=this->m_hWnd;   
	nid.uID=IDR_MAINFRAME;   
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP   ;   
	nid.uCallbackMessage= WM_NOTIFY_GOBANG_TRAY;//自定义的消息名称   
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));   
	strcpy(nid.szTip,"五子棋游戏");//信息提示条为“计划任务提醒”  
	// 	strcpy(nid.szInfo,_T("五子棋"));  // 标题
	// 	strcpy(nid.szInfoTitle,_T("隐藏到托盘"));  // 显示内容
	// 	nid.dwInfoFlags=NIIF_INFO;  
	//     nid.uTimeout=4000;        

	Shell_NotifyIcon(NIM_ADD,&nid);//在托盘区添加图标   
    ShowWindow(SW_HIDE);//隐藏主窗口   
}

void StartUpAnimation::DeleteTray()
{
	Shell_NotifyIcon(NIM_DELETE, &nid);
}


LRESULT StartUpAnimation::OnTrayIcon(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
	{
		return 1;
	}
	
	switch(lParam)
	{
	case WM_RBUTTONUP://右键起来时弹出快捷菜单
		{
			
			//声明一个弹出式菜单
			//增加菜单项“关闭”，点击则发送消息WM_CLOSE给主窗口（已  
			//隐藏），将程序结束。
			// 			CMenu menu;
			// 			menu.CreatePopupMenu();
			// 			CbmpPicture cpic;
			// 			cpic.loadBmpFromFile("resource")
			// 			menu.AppendMenu(MF_STRING, ID_APP_EXIT, _T("关闭"));
			// 			menu.AppendMenu(MF_STRING, ID_APP_ABOUT, _T("关于"));
			// 			
			// 			//得到鼠标位置
			// 			LPPOINT lpoint= new tagPOINT;
			// 			::GetCursorPos(lpoint);
			// 			
			// 			//确定弹出式菜单的位置  
			// 			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y,this);
			// 			
			// 			//资源回收
			// 			HMENU   hmenu=menu.Detach();
			// 			menu.DestroyMenu();
			// 			
			// 			delete lpoint;
			// 			lpoint = NULL;
			
			CPoint pt;
			CMenu menu;   //定义右键菜单对象
			GetCursorPos(&pt);   //获取当前鼠标位置
			menu.LoadMenu(IDR_GOBANG_MENU);   //载入右键快捷菜单
			SetForegroundWindow();//放置在前面
			CMenu* pmenu;    //定义右键菜单指针
			pmenu=menu.GetSubMenu(0);      //该函数取得被指定菜单激活的下拉式菜单或子菜单的句柄
			ASSERT(pmenu!=NULL);      
			
			// 	CBitmap *pBitmap = NULL;
			// 	CbmpPicture cpic;
			// 	cpic.loadBmpFromFile("./resource/buttons/theme_gray/退出.bmp");
			// 			
			// 	pBitmap = cpic.getBitmap();
			// 	ASSERT(pBitmap != NULL);
			// 	pmenu->SetMenuItemBitmaps(0, MF_BYPOSITION, pBitmap, pBitmap);
			pmenu-> TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,pt.x,pt.y,this);   //在指定位置显示右键快捷菜单
			HMENU hmenu=pmenu -> Detach();  
            pmenu ->DestroyMenu();  
			
			
			break;
		}
	case WM_LBUTTONDBLCLK:
		{
			//双击左键的处理
			//显示界面
			switch(lastForeground)
			{
			case LOCAL_SINGLE:
				{if (pPgobangDlg)
				{
					pPgobangDlg->ShowWindow(SW_SHOW | SW_NORMAL);
				}
					
				}
				break;
			case VS_COMPUTER:
				{
					if (pCgobangDlg)
					{
						pCgobangDlg->ShowWindow(SW_SHOW | SW_NORMAL);
					}
				
				}
				break;
			case VS_ONLINE:
				{
					if (pNgobangDlg)
					{
						pNgobangDlg->ShowWindow(SW_SHOW | SW_NORMAL);
					}
					
				}
				break;
			case MAIN_WINDOW:
				{
					ShowWindow(SW_SHOW | SW_NORMAL);
					SetForegroundWindow();
				}
				break;
			}
	
			//界面置顶
			//SetForegroundWindow();
			
			break;	       
		}	  
	}
	
	return 0;
}

void StartUpAnimation::OnMinsizeBtn() 
{
	// TODO: Add your control notification handler code here
	if (!IsIconic())
	{
		// 		WINDOWPLACEMENT   lwndpl; 
		// 		
		// 		GetWindowPlacement(&lwndpl); 
		// 		lwndpl.showCmd=SW_SHOWMINIMIZED; 
		// 		SetWindowPlacement(&lwndpl);
		//	MessageBox("kkkkl");
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); 
	}
}

void StartUpAnimation::OnTotrayBtn() 
{
	// TODO: Add your control notification handler code here
//	bIsToTray = TRUE;
//	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); 
	ToTray(MAIN_WINDOW);
//	lastForeground = MAIN_WINDOW;
}

void StartUpAnimation::OnGameExit() 
{
	// TODO: Add your command handler code here
	OnCancel();
}

void StartUpAnimation::OnAbout() 
{
	// TODO: Add your command handler code here
	CGobangAboutDlg dlg;
	dlg.DoModal();
}
BOOL StartUpAnimation::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default

	 switch (pWnd->GetDlgCtrlID())  
	 {
	 case IDC_VS_COMPUTER_BTN:
	 case IDC_SINGLE_BTN:
	 case IDC_VS_NETWORD_BTN:
	 case IDC_SET_BTN:
	 case IDC_EXIT_BTN:
		 if (m_selectBtnCur)
		 { 
			 SetCursor(m_selectBtnCur);
			return TRUE;
		 }
		
	 }

	if (m_hCursor != NULL)
	{
		SetCursor(m_hCursor);
		return TRUE;
	}
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}



void StartUpAnimation::OnSetBtn() 
{
	// TODO: Add your control notification handler code here
	CConfigDlg configDlg(this);
	
	configDlg.DoModal();

}

void StartUpAnimation::OnRuleHelp() 
{
	// TODO: Add your command handler code here
	CGobangAboutDlg aDlg;
	aDlg.setBkImg(CGobangAboutDlg::HELP_IMG);
	aDlg.DoModal();
	
}

void StartUpAnimation::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnTimer(nIDEvent);
}
