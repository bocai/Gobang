// GobangDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Gobang.h"
#include "GobangDlg.h"
#include "bmpPicture.h"
#include "GameManager.h"
#include "GamePlayer.h"
#include "HumanPlayer.h"
#include "computerPlayer.h"
#include "NetwordSeting.h"
#include "GobangAboutDlg.h"
#include "StartUpAnimation.h"
#include "MusicPlayer.h"
#include "ConfigDlg.h"
#include "GameHallDlg.h"

#include <cstring>
#include <string>
#include <wchar.h>
using namespace std;

#define  T_COUNT_DOWN  1 // 定时器,倒计时
#define  T_WAIT_START  2  // 定时器，网络模式下等待对方回应开始游戏消息的时间
#define T_SUGGEST_TIMER 3  // 提示功能中画笔画的落子，闪烁一下
UINT  TIME_LIMIT  = 15;// 等待时间设为0代表不启用时间限制

class CcomputerPlayer;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "StartUpAnimation.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	virtual ~CAboutDlg();
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:

	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}
CAboutDlg::~CAboutDlg() 
{

}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_LBUTTONDOWN()
//	ON_BN_CLICKED(IDC_QUIT_ABOUT, OnQuitAbout)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////
// CGobangDlg dialog

CGobangDlg::CGobangDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGobangDlg::IDD, pParent)
{	
	//{{AFX_DATA_INIT(CGobangDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hCurNormal = m_hCurError = NULL;
	memset(&nid, 0, sizeof(nid)); // 系统托盘

	LinesNo = LINE_TOTAL; // 几根线
	n_pixel = LINE_DISTANCE;  // 两条线距离的像素
	borderWidth = 215;  // 棋盘(0,0）点与客户区原点的边界
	borderHeight = 68;
	


// 	m_bPenColor = RGB(167, 85, 48);
// 	m_wPenColor = RGB(192, 192, 192);
 	m_chessRadius = (n_pixel / 2 );
	maskColor = RGB(90, 90, 90);//RGB(255, 255, 255);  // 掩码色
	chessNumColor = RGB(30, 144, 255);
// 	ChessBlackPen.CreatePen(PS_SOLID, 2, RGB(210, 140, 180));
// 	ChessWhitePen.CreatePen(PS_SOLID, 2, RGB(255, 235, 205));;
	
	selectChess = BLACK; // 默认选择黑子



	pGameManager = NULL;
	pWhitePlayer = NULL;
	pBlackPlayer = NULL;
	pSelf        = NULL;
	pOpponent    = NULL;
	pCmpSelf = pCmpOpponent = NULL;
	pUdpMsger = NULL;
	
//	memset(ipBytes, 0, sizeof(ipBytes));

	timeCount = 0;
// 	currentChess.x = -1;
// 	currentChess.y = -1;

	m_font.CreatePointFont(270,__T("华文行楷"));
	m_numFont.CreatePointFont(130, __T("微软雅黑"));

	chessVoice.SetMusicFilePath(CString( _T("./resource/sound/chessvoice1.wav") ));
	soundPlayer.SetMusicFilePath(CString(_T("./resource/sound/mp3/kanong.mp3")));
	soundStart.SetMusicFilePath(__T(CString("./resource/sound/ringin.wav")) );
	
	bgroundChg = FALSE;
	m_handCur = LoadCursorFromFile(_T("./resource/ani/handCur.cur"));
	m_putChess = LoadCursorFromFile(_T("./resource/ani/putChess.cur"));
	hadSetCur = false;
}


void CGobangDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGobangDlg)
	DDX_Control(pDX, IDC_BTN_TEST, m_musicBtn);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnSendMsg);
	DDX_Control(pDX, IDC_MINSIZE_BTN, m_btnMinSize);
	DDX_Control(pDX, IDC_TAKEBACK_BTN, m_btnTakeBack);
	DDX_Control(pDX, IDC_BTN_TOTRAY, m_btnToTray);
	DDX_Control(pDX, IDC_START_BTN, m_btnStart);
	DDX_Control(pDX, IDC_HEQI_BTN, m_btnHeQi);
	DDX_Control(pDX, IDC_GIVEUP_BTN, m_btnGiveUp);
	DDX_Control(pDX, IDC_BACK_HOME_BTN, m_btnBackHome);
	DDX_Control(pDX, IDC_SETTING_BTN, m_btnSetting);
	DDX_Control(pDX, IDC_SKINCHG_BTN, m_btnSkin);

	DDX_Control(pDX, IDC_RIVAL_HEAD, m_rivalHeadBtn);
	DDX_Control(pDX, IDC_SELF_HEAD, m_selfHeadBtn);
	DDX_Control(pDX, IDC_ED_SEND_MSG, m_SendMsg);
	DDX_Control(pDX, IDC_ED_SHOWMSG, m_ShowMsg);
	DDX_Control(pDX, IDC_RIVAL_CHESS, m_rivalChess);
	DDX_Control(pDX, IDC_MY_CHESS, m_myChess);
	DDX_Control(pDX, IDC_COUNT_DOWN_BTN, m_countDownBtn);
	DDX_Control(pDX, IDC_BTN_RIVAL_IP, m_showRivalIp);
	DDX_Control(pDX, IDC_BTN_SELF_IP, m_showSelfIp);
	DDX_Control(pDX, IDC_SUGGEST_BTN, m_btnSuggest);
	//}}AFX_DATA_MAP
	
}

BEGIN_MESSAGE_MAP(CGobangDlg, CDialog)
//{{AFX_MSG_MAP(CGobangDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_LBUTTONUP()
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_BTN_TEST, OnBtnTest)
ON_BN_CLICKED(IDC_MINSIZE_BTN, OnMinsizeBtn)
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_TAKEBACK_BTN, OnTakebackBtn)
	ON_BN_CLICKED(IDC_BTN_TOTRAY, OnBtnTotray)
	ON_COMMAND(IDM_GAME_EXIT, OnGameExit)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_HEQI_BTN, OnHeqiBtn)
	ON_BN_CLICKED(IDC_GIVEUP_BTN, OnGiveupBtn)
	ON_BN_CLICKED(IDC_SETTING_BTN, OnSettingBtn)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_SKINCHG_BTN, OnSkinchgBtn)
	ON_BN_CLICKED(IDC_START_BTN, OnStartBtn)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SUGGEST_BTN, OnSuggestBtn)
	ON_COMMAND(IDM_MUSIC1, OnMusic1)
	ON_COMMAND(IDM_MUSIC2, OnMusic2)
	ON_COMMAND(IDM_MUSIC3, OnMusic3)
	ON_COMMAND(IDM_STOP_MUSIC, OnStopMusic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGobangDlg message handlers



BOOL CGobangDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	HideCaption(this->GetSafeHwnd()); // 去掉系统自带的标题栏
	
// 	int w = SCREEN_WIDTH;//(LinesNo + 5) * n_pixel;
// 	int h = SCREEN_HEIGHT;//(LinesNo + 1) * n_pixel;
	// 各个控件的摆放位置
	setUIwidgetPos();
	setUIwidgetPathFromFile("ini"); // 本来想从ini文件配置的。。。。

	// 	m_hCursor = AfxGetApp()->LoadCursor(IDI_CHESS_WHITE);
	m_hCurNormal = LoadCursorFromFile(m_curPathNormal); 
	m_hCurError = LoadCursorFromFile(m_curPathError);

	SetWindowEllispeFrame(this->GetSafeHwnd(), 20, 20); // 窗口边角圆弧
	bmpPicture.loadBmpFromFile(m_backgroundImgPath);

	// 加载贴图
	cpicBlackChess.loadBmpFromFile(blackChessBmpPath);
	cpicWhiteChess.loadBmpFromFile(whiteChessBmpPath);
	logoPic.loadBmpFromFile(m_logoPath);
	msgPic.loadBmpFromFile(m_chatBgPath);
	playerInfo1Bmp.loadBmpFromFile(playerInfo1BmpPath);
	playerInfo2Bmp.loadBmpFromFile(playerInfo2BmpPath);
	countDownBgBmp.loadBmpFromFile(countDownPath);
	tableBgBmp.loadBmpFromFile(tableBgPath);

	//Button init
	// 按钮贴图
	setBtnsImg();
	setHoverBtnSound();

	StartUpAnimation *psa = (StartUpAnimation *)GetParent();
	if(psa) {
		TIME_LIMIT = psa->configData.timeOut;
	}
	if (ONLINE_MODE == gameMode)
	{
		pUdpMsger = CUdpMessager::getMessagerInstance();
		pUdpMsger->Close();
		if (FALSE == pUdpMsger->Create(psa->myPort, SOCK_DGRAM, NULL))
		{
			MessageBox("网络初始化错误,请检查网络端口是否已被占用。");
		}
		else {
			pUdpMsger->initParentWnd(this);	
		}
		m_showSelfIp.SetWindowText(CUdpMessager::getHostIpstr());
	}
	
	
	//ModifyStyle(0,WS_CLIPCHILDREN); // 防止父窗口刷新时子窗口也跟着刷新，解决按钮闪烁问题
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGobangDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CGobangAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	// 	else if (SC_ICON == (nID & 0xfff0))
	// 	{
	// 		SendMessage( WM_SYSCOMMAND, SC_MINIMIZE, 0); 
	// 
	// 	//	MessageBox("kss");
	// 	}
	// 	else if (SC_RESTORE == (nID & 0xfff0))
	// 	{
	// 		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	// 		MessageBox("kswe");
	// 	}
// 	else if (nID==SC_RESTORE)
// 	{
// 		AfxGetMainWnd()->ShowWindow(WM_RESTORE);
// 	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGobangDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialog::OnPaint(); //不要调用
		CPaintDC dc(this);//对话框的dc//CPaintDC是从CDC派生出来的。在构造时自动调用CWnd::BeginPaint,析构时调用CWnd::EndPaint。通常CPaintDC用来响应WM_PAINT消息。一般应用在OnPaint函数
	//	DrawBackgroundImg(0, 0, IDB_BM_BACKGROUND1, dc);
		RECT rect;
		GetClientRect(&rect);
	//	rect.top += 1;	
		// 使用双缓冲避免屏幕刷新时闪烁
		CDC dcMem;
 		CBitmap bmpMem;
		dcMem.CreateCompatibleDC(NULL);
		bmpMem.CreateCompatibleBitmap(&dc, rect.right-rect.left, rect.bottom-rect.top);
		CBitmap *pOld = dcMem.SelectObject(&bmpMem);
		dcMem.FillSolidRect(0,0,rect.right-rect.left, rect.bottom-rect.top, RGB(255,255,255));	
		// 此处将绘制内容输出到dcMem上
	
		bmpPicture.PaintZoom(dcMem, rect);
		playerInfo1Bmp.PaintZoom(dcMem, playerInfoRect1);
		playerInfo2Bmp.PaintZoom(dcMem, playerInfoRect2);
		countDownBgBmp.PaintZoom(dcMem,countDownRect);
		tableBgBmp.PaintZoom(dcMem, tableBgRect);
		logoPic.PaintZoom(dcMem, logoRect);
		msgPic.PaintZoom(dcMem, chatBgRect);

		
		DrawTable(dcMem);
		DrawChesses(dcMem);
		showWinner(dcMem);
		// 从内存拷贝到设备dc
		dc.BitBlt(0, 0, rect.right - rect.left, rect.bottom - rect.top, &dcMem, 0, 0, SRCCOPY);
		dc.SelectObject(pOld);
		bmpMem.DeleteObject();
		dcMem.DeleteDC(); 
		
		if (bgroundChg)
		{
			bgroundChg = FALSE;
			ModifyStyle(0, WS_CLIPCHILDREN);
		}
	}	

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGobangDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGobangDlg::OnOK() 
{

	if (gameMode != ONLINE_MODE)
	{
		MessageBox("对不起，该功能仅对联机对战开放。");
		return;
	}
	if (pSelf == NULL || pOpponent == NULL)
	{	
		
		StartUpAnimation *pSa = (StartUpAnimation *)GetParent();  
		if (NULL != pSa && initGame(gameMode))
		{
			if (selectChess == BLACK)
			{
				pSelf = pBlackPlayer;
				pOpponent = pWhitePlayer;
			}else {
				pOpponent = pBlackPlayer;
				pSelf = pWhitePlayer;
			}
			pSelf->setPort(pSa->myPort);
			BYTE *ipBytes = pSa->ipBytes;
			CString str;
			str.Format("%d.%d.%d.%d", ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3]);
			//	MessageBox(str);
			pSelf->setIpString(str);
			pOpponent->setIpString(str);
			pOpponent->setPort(pSa->farPort);
		}
	}
	
	MsgStruct msgStruct;
	
	memset(&msgStruct, 0, sizeof(msgStruct));
	GetDlgItemText(IDC_ED_SEND_MSG, msgStruct.content.chatContent, sizeof(msgStruct.content.chatContent));
	m_SendMsg.SetFocus();
	if (strlen(msgStruct.content.chatContent) <= 0)
	{
		return;
	}
	
	msgStruct.requestResponse = REQUEST_MSG;
	msgStruct.msg_type = CHAT;
	// 	msgStruct.content.playChess.chess_x = 2;
	// 	msgStruct.content.playChess.chess_y = 3;
	//	SOCKADDR_IN romoteAddr;
	
	// 	memset(&romoteAddr, 0, sizeof(romoteAddr));
	// 	romoteAddr.sin_port = htons(5050);
	// 	romoteAddr.sin_family = AF_INET;
	// 	romoteAddr.sin_addr.S_un.S_addr = inet_addr(ipAddr);
	// 	int len = sizeof(romoteAddr);
	
	//	pUdpMsger->SendTo(msg, strlen(msg)+1, (SOCKADDR *)&romoteAddr, len);
	
	/* 或者下面这个重载函数 */
	if ( pUdpMsger )
	{
		if (pUdpMsger->SendTo(&msgStruct, sizeof(msgStruct), pOpponent->getPort(), pOpponent->getIpString()) <= 0) {
			MessageBox("发送失败");
			return;
		}
	}
	
	// 界面显示
	msgStr += __T("朕:\r\n");
	msgStr += CString(msgStruct.content.chatContent);
	msgStr += "\r\n";
	SetDlgItemText(IDC_ED_SHOWMSG, msgStr);
	
	m_SendMsg.SetWindowText("");


}


void CGobangDlg::DrawTable(CDC &dc)
{
	
	CPen bi,*pbi;
	
	bi.CreatePen(PS_DASH,3,lineColor); //创建(RGB(90,90,90)画笔
	pbi=dc.SelectObject(&bi); //选择画笔（并保存原来的画笔）
	int i;
	
	int line = LinesNo - 1;
	
	for( i = 0;i < LinesNo; i++) //画水平线 
	{
		dc.MoveTo(borderWidth, borderHeight + i*n_pixel);// x不变 y+=n_pixel
		dc.LineTo( borderWidth + line*n_pixel,  borderHeight + i*n_pixel);
	}
	for(i = 0; i < LinesNo; i++)  //画垂直线  y不变
	{
		dc.MoveTo(borderWidth + i*n_pixel, borderHeight);
		dc.LineTo(borderWidth + i*n_pixel, borderHeight + line*n_pixel);
	}
	dc.SelectObject(pbi);//恢复原来的画笔
	 /*
						 画五子棋的子，可用以下的画圆的函数，
						 BOOL Ellipse( int x1, int y1, int x2, int y2 );
						 或
						 BOOL Ellipse( LPCRECT lpRect );
	*/
	
}

void CGobangDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int startX = borderWidth - n_pixel/2 , endX = borderWidth + n_pixel * LinesNo + n_pixel/2;
	
	int x = point.x;
	int y = point.y;
	// 检查点击位置，判断是否开始游戏了
	if (x < startX  || x > endX || NULL==pGameManager || !(pGameManager->isGameStart()))
	{
		return;
	}
	
	int startY = borderHeight - n_pixel/2, endY = borderHeight + n_pixel * LinesNo + n_pixel/2;
	if ( y < startY|| y > endY)
	{
		return;
	}
	
	x = ( (point.x  - borderWidth + n_pixel/2) / n_pixel)* n_pixel;//网格交叉线像素点范围内
	y = ( (point.y - borderHeight + n_pixel/2)/ n_pixel) * n_pixel;// 
	
// 	  CString cs;
// 	 	cs.Format("(%d,%d), x = %d, y=%d",point.x, point.y, x, y);
// 		MessageBox(cs);
	
	CPoint chessPoint;
	chessPoint.x = x / n_pixel;  //二维数组棋盘下标chess_x;
	chessPoint.y = y / n_pixel;  //         chess_y;
//	currentChess = chessPoint;

	// 进入相应的模式
	if ( COMPUTER_MODE == gameMode )
	{
		playWithComputer(nFlags, chessPoint);
		
	}
	else if (SINGLE_MODE == gameMode)
	{
		
		playInSingle(nFlags, chessPoint);

		//	MessageBox("人人 ");
	}
	else if (ONLINE_MODE == gameMode)
	{
		
		if (pGameManager->whoIsRuning() == pSelf->getMyChessType()) // 轮到自己
		{
			playInNetword(nFlags, chessPoint);
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CGobangDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(point.y < 50) //左键点击顶部的范围
	{
		if (m_handCur)
		{	
			hadSetCur = true;
			SetCursor(m_handCur);
		}
		else {
			hadSetCur = false;
		}
		//欺骗 Windows，发送拖动标题栏的消息，实现移动窗口
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y)); 
		
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}


void CGobangDlg::OnBtnTest() 
{


// 	CGameHallDlg gameHall;
// 	gameHall.DoModal();

// 	if (pOpponent)
// 	{
// 		CString str;
// 		str.Format("%s", pOpponent->getIpString());
// 		MessageBox(str);
// 	}
// 
// 	CConfigDlg conDlg;
// 	conDlg.DoModal();
	// TODO: Add your control notification handler code here
	// 	int cwidth = GetSystemMetrics(SM_CXSCREEN);
	// 	int chigh = GetSystemMetrics(SM_CYSCREEN);
	// 	CString msg;
	
	//	msg.Format("screen size: %d, %d", cwidth, chigh);
	
	//	MessageBox(msg);
	
	// 	CClientDC cDc(this);
	// 	RECT  Rect;
	// 	//	GetClientRect(&Rect);
	// 	Rect.left = n_pixel - n_pixel/2;
	// 	Rect.top = Rect.left;
	// 	Rect.bottom = n_pixel + n_pixel/2;
	// 	Rect.right = Rect.bottom;
	// 	CbmpPicture cpic;
	// 	if (!cpic.loadBmpFromFile("resource\\chesses\\棋子白.bmp"))
	// 	{
	// 		return;
	// 	}
	// 	cpic.TansParentBlt(cDc, Rect, RGB(255, 255, 255));
	// 
	// 	CustomBackground();	
	
	
// 	static isPlay = FALSE;
// 	if (!isPlay)
// 	{
// 		chessVoice.PlayMusicRepeat(TRUE);
// 		isPlay = TRUE;
// 	} else {
// 		chessVoice.PlayMusicRepeat(FALSE);
// 		isPlay = FALSE;
// 	}
	
// 	static BOOL bFirst = TRUE;
// 	if (bFirst && pUdpMsger)
// 	{
// 		bFirst = FALSE;
// 		
// 		if (pGameManager == NULL || !pGameManager->isGameStart())
// 		{	
// 			if (initGame(ONLINE_MODE) == FALSE)
// 			{
// 				return;
// 			}
// 
// 			if (selectChess == BLACK)
// 			{
// 				pSelf = pBlackPlayer;
// 				pOpponent = pWhitePlayer;
// 			}
// 			else {
// 				pSelf = pWhitePlayer;
// 				pOpponent = pBlackPlayer;
// 			}
// 			pGameManager->setWhoFirst(pSelf->getMyChessType()); // 先手
// 
// 			pGameManager->setGameMode(ONLINE_MODE);
// 			pGameManager->setGamePlayer(pBlackPlayer, pWhitePlayer);
// 
// 			MsgStruct msgstruct;
// 			memset(&msgstruct, 0, sizeof(msgstruct));
// 
// 			msgstruct.requestResponse = REQUEST_MSG;
// 			msgstruct.msg_type = START_GAME;
// 			strcpy(msgstruct.usrInfo.username , pSelf->getPlayerName());
// 			msgstruct.usrInfo.usrId = 1;
// 			msgstruct.content.startGame.chess_type = pSelf->getMyChessType();
// 			msgstruct.content.startGame.whoFirst = true; // 先手
// // 
// // 			CString ipAddr = "192.168.0.89";
// // 			pOpponent->setIpString(ipAddr);
// // 			pOpponent->setPort(5050);
// 		//	pUdpMsger = CUdpMessager::getMessagerInstance();
// 
// 			if (pUdpMsger && !pUdpMsger->sendMsg(&msgstruct, pOpponent) )
// 			{
// 				MessageBox("发送失败");
// 			}
// 			else {
// 				MessageBox("开始游戏请求已发送,请稍候...");
// 			}
// 			if (pUdpMsger != NULL && pUdpMsger->SendTo(&msgstruct, sizeof(msgstruct), 5050, ipAddr) <= 0)
// 			{
// 				MessageBox("发送失败");
// 			}
// 			else {
// 				MessageBox("发送成功");
// 			}
	//		pGameManager->startGame(WHITE);
			
// 
// 			Invalidate(FALSE);
// 		}
// 	}

	//	cpic.PaintZoom(cDc, Rect);

}


void CGobangDlg::DrawChesses(CDC &dc)
{
	
	if (NULL == pGameManager)
	{
		return;
	}
	chessType type = NOCHESS;
	vector <CPoint> *vecRecord = pGameManager->getVecRecord();

	for (int i = vecRecord->size()-1; i >= 0; i--)
	{
		int x = (*vecRecord)[i].x;
		int y = (*vecRecord)[i].y;
		if (pGameManager->getBoardPos(x, y, type))
		{
			DrawOneChess(dc, type, x * n_pixel, y * n_pixel);
			chessRect.top += 5;
			DrawNumber(dc, chessRect, chessNumColor, i+1);
		}
		
	}

}

void CGobangDlg::DrawOneChess(CDC &dc, chessType cType, int xPx, int yPx)
{
	
	if (xPx < 0 || yPx < 0)
	{
		return;
	}
//	CPen *poldPen = NULL;
	xPx += borderWidth;
	yPx += borderHeight;
	
	chessRect.left = xPx  - m_chessRadius;
	chessRect.right = xPx + m_chessRadius;
	chessRect.top = yPx  - m_chessRadius;
	chessRect.bottom = yPx + m_chessRadius;
	

	if (WHITE == cType)
	{
		// 		poldPen= dc.SelectObject(&ChessWhitePen);
		// 		CBrush brush(m_wPenColor);
		// 		dc.SelectObject(brush);
		// 	    // 画圆
		// 		dc.Ellipse((int)(x-m_chessRadius), (int) (y-m_chessRadius), 
		// 			(int)(x+m_chessRadius), (int)(y+m_chessRadius) );
		// 		dc.SelectObject(poldPen);
		
		
		cpicWhiteChess.TansParentBlt(dc, chessRect, RGB(255,255,255));
	} 
	else if (BLACK == cType)
	{
		// 		poldPen= dc.SelectObject(&ChessBlackPen);
		// 		CBrush brush(m_bPenColor);
		// 		dc.SelectObject(brush);
		// 		dc.Ellipse((int)(x-m_chessRadius), (int) (y-m_chessRadius), 
		// 			(int)(x+m_chessRadius), (int)(y+m_chessRadius) );
		// 		dc.SelectObject(poldPen);
		cpicBlackChess.TansParentBlt(dc, chessRect, RGB(255, 255, 255));		
	}
	//InvalidateRect(&chessRect, TRUE);
}

// 打开文件对话框让用户选择背景图
BOOL CGobangDlg::CustomBackground()
{
	char   szFilter[] = "BMP Files (*.bmp)|*.bmp|All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE,"BMP",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter );
	
    if(dlg.DoModal() == IDOK)
    {
		CString strPathName = dlg.GetPathName();    
		m_backgroundImgPath = strPathName;
		bmpPicture.unLoad();
		bmpPicture.loadBmpFromFile(m_backgroundImgPath);
		// 发现这方法行不通
		ModifyStyle(WS_CLIPCHILDREN, 0); 
		bgroundChg = TRUE;
		setBtnsImg();
		Invalidate(TRUE);

		return TRUE;
	}
	
	return FALSE;
}

BOOL CGobangDlg::playWithComputer(UINT nFlags, CPoint point)
{
	chessType cType;

	int chess_x = point.x;
	int chess_y = point.y;
	chessType turn = NOCHESS;

	CString str;
	CClientDC dc(this);
	if (pGameManager->getBoardPos(chess_x, chess_y, cType))
	{

		if (NOCHESS  != cType)
		{
			SetCursor(m_hCurError);
			return FALSE;
		}
		turn = pGameManager->whoIsRuning();
	
		
		if (pSelf->getMyChessType() == turn  && timeCount >= 0) // 轮到白棋(人类玩家）
		{
// 			str.Format("你点击了：%d,%d", chess_x, chess_y);
// 			MessageBox(str);
			
			pSelf->getGameManager()->setBoardPos( chess_x, chess_y, pSelf->getMyChessType());
			chessVoice.PlayMusicNoRepeat(TRUE);
// 			DrawOneChess(dc, turn,chess_x*n_pixel, chess_y*n_pixel);
// 			chessRect.top += 5;
// 			DrawNumber(dc, chessRect, chessNumColor, pGameManager->getVecRecord()->size());
//			((CcomputerPlayer *) pBlackPlayer)->rest_win2(chess_x, chess_y);
			
			if (pGameManager->judgeVictory(chess_x, chess_y, pSelf->getMyChessType()))
			{
				pGameManager->stopGame();
				if (TIME_LIMIT > 0)
				{
					KillTimer(T_COUNT_DOWN);
				}
			} 
			else {
				timeCount = TIME_LIMIT;
				pGameManager->setWhoIsRun(pSelf->getOppenentChess()); // 通知对方
				//switchShowChess(pGameManager->whoIsRuning());
			}
			Invalidate(FALSE);
			
			//((CcomputerPlayer *) pBlackPlayer)->rest_win2(chess_x, chess_y);
		}
	}
		
	turn = pGameManager->whoIsRuning();
	chessType opsType = pOpponent->getMyChessType();
	if(pGameManager->isGameStart() && opsType == turn ) // 电脑
	{

		CPoint p;
		p.x = -1;
		p.y = -1;
		if (TRUE == pOpponent->thinkPlayChess(p))
		{
		
			chessVoice.PlayMusicNoRepeat(FALSE);
			if (pGameManager->getBoardPos(p.x, p.y, cType) && timeCount >= 0)
			{
				if (cType != NOCHESS)  // 已经有棋子
				{
// 					CString cs;
// 					cs.Format("computer: %d, %d", p.x, p.y);
// 					MessageBox(cs);
					pGameManager->setWhoIsRun(pOpponent->getOppenentChess()); // 通知人类玩家
					return FALSE;
				}
				else {
		
					pOpponent->getGameManager()->setBoardPos(p.x, p.y, opsType);
					chessVoice.PlayMusicNoRepeat(TRUE);
// 					DrawOneChess(dc, opsType, p.x * n_pixel, p.y * n_pixel);
// 					chessRect.top += 5;
// 					DrawNumber(dc, chessRect, chessNumColor, pGameManager->getVecRecord()->size());
					
					if (pGameManager->judgeVictory(p.x, p.y, opsType))
					{
						pGameManager->stopGame();
						if (TIME_LIMIT > 0)
						{
							KillTimer(T_COUNT_DOWN);
						}
					} 	
					
				}
			}
		}
		else
		{
			//MessageBox("电脑没有找到合适位置");
			return FALSE;
		}
		timeCount = TIME_LIMIT;
		Invalidate(FALSE);
		pGameManager->setWhoIsRun(pOpponent->getOppenentChess());
		//switchShowChess(pGameManager->whoIsRuning());
	}
	
	return TRUE;
}

BOOL CGobangDlg::playInSingle(UINT nFlags, CPoint point)
{
	if (NULL == pGameManager || pSelf == pOpponent || pOpponent == NULL)
	{
		return FALSE;
	}

	chessType cType;
//	CClientDC dc(this);
	int chess_x = point.x;
	int chess_y = point.y;
	
	if (pGameManager->getGobangChess()->getBoardPos(chess_x, chess_y, cType))
	{
		CString msg;
		if (NOCHESS  == cType)
		{
			chessType turn = pGameManager->whoIsRuning();


			if (pSelf->getMyChessType() == turn && timeCount >= 0) // 轮到自己
			{
				if (pSelf->forbid(chess_x, chess_y) == FORBIDDEN)
				{
						MessageBox("这是禁手位置，请选择其他位置下棋");
						return FALSE;
				}
					
				pGameManager->setBoardPos( chess_x, chess_y, turn);
				
				chessVoice.PlayMusicNoRepeat(TRUE);
// 				DrawOneChess(dc, turn,chess_x*n_pixel, chess_y*n_pixel);
// 				chessRect.top += 5;
// 				DrawNumber(dc, chessRect, chessNumColor, pGameManager->getVecRecord()->size());
	
				if (pGameManager->judgeVictory(chess_x, chess_y, turn))
				{
					pGameManager->stopGame();
					if (TIME_LIMIT > 0)
					{
						KillTimer(T_COUNT_DOWN);
					}
				} 	
				else {
					
					timeCount = TIME_LIMIT;
					
					pGameManager->setWhoIsRun(pSelf->getOppenentChess());
					switchShowChess(pGameManager->whoIsRuning());
				}
				Invalidate(FALSE);
				
			} 
			else if (pOpponent->getMyChessType() == turn && timeCount >= 0)
			{
				if (pOpponent->forbid(chess_x, chess_y) == FORBIDDEN)
				{
					MessageBox("这是禁手位置，请选择其他位置下棋");
					return FALSE;
				}
				pGameManager->setBoardPos(chess_x, chess_y, turn);
				
				chessVoice.PlayMusicNoRepeat(TRUE);
// 				DrawOneChess(dc, turn, chess_x * n_pixel, chess_y * n_pixel);
// 				chessRect.top += 5;
// 				DrawNumber(dc, chessRect, chessNumColor, pGameManager->getVecRecord()->size());
			
				if (pGameManager->judgeVictory(chess_x, chess_y, turn))
				{
					pGameManager->stopGame(); 
					if (TIME_LIMIT > 0)
					{
						KillTimer(T_COUNT_DOWN);
					}
				} 	
				else
				{
					timeCount = TIME_LIMIT;
					pGameManager->setWhoIsRun(pOpponent->getOppenentChess());
					switchShowChess(pGameManager->whoIsRuning());
				}
				Invalidate(FALSE);
			}
			
		}
		else {
			SetCursor(m_hCurError);// 该位置已有棋子
			return FALSE;
		}
	}
	
	return TRUE;
}

BOOL CGobangDlg::initGame(GameMode mode)
{
	srand((unsigned)time(NULL));// 倒计时为0随机选择一个空位下
	if (pGameManager == NULL)
	{
		pGameManager = new CGameManager();
		pGameManager->stopGame();
		srand(time(NULL));
		
	}
	pGameManager->getGobangChess()->reset();
	pGameManager->cleanRecord();
	chessType (*pBoard)[CHESS_BOARD_SIZE] = pGameManager->getChessBoard(NULL);
	
// 	if (pWhitePlayer != NULL)
// 	{
// 		delete pWhitePlayer;
// 		pWhitePlayer = NULL;
// 	}
// 
// 	if (pBlackPlayer != NULL)
// 	{
// 		delete pBlackPlayer;
// 		pBlackPlayer = NULL;
// 	}

	if (NULL == pBlackPlayer)
	{
		if (COMPUTER_MODE == mode)
		{
			
			pBlackPlayer = new CComputerHarder(pBoard); // 先默认为电脑，之后看用户选择再调换相应的指针
		}
		else //if (SINGLE_MODE == mode || ONLINE_MODE == mode)
		{
			pBlackPlayer = new CHumanPlayer(pBoard);
		}
	}

	if (NULL == pWhitePlayer)
	{
		if (COMPUTER_MODE == mode)
		{
			
			pWhitePlayer = new CComputerHarder(pBoard); // 先默认为电脑
			
		}
		else //if (SINGLE_MODE == mode || ONLINE_MODE == mode)
		{
			pWhitePlayer = new CHumanPlayer(pBoard);
		}
	}

	if (NULL == pBlackPlayer || NULL == pWhitePlayer )
	{
		MessageBox("游戏初始化，创建玩家失败");
		return FALSE;
	}

	pBlackPlayer->suggestAdd(-1);// -1 表示把提示次数就计数重置为n (7)
	pWhitePlayer->suggestAdd(-1);

	pBlackPlayer->setPlayer("黑棋", BLACK);
	pBlackPlayer->setOpponentChessType(WHITE);

	pWhitePlayer->setPlayer("白棋", WHITE);
	pWhitePlayer->setOpponentChessType(BLACK);
	
	pWhitePlayer->setGameManager(pGameManager);
	pBlackPlayer->setGameManager(pGameManager);
	
	pGameManager->setGamePlayer(pBlackPlayer, pWhitePlayer);
	pGameManager->setGameMode(mode);
	

	return TRUE;
}

void CGobangDlg::OnCancel() 
{
	
	if (pGameManager && pGameManager->isGameStart())
	{
		if (IDYES == MessageBox("您正在游戏中，是否确定退出?", NULL, MB_YESNO))
		{
			if (ONLINE_MODE == gameMode) // 要通知对方
			{
				MsgStruct msgstruct;
				msgstruct.requestResponse = REQUEST_MSG;
				msgstruct.msg_type = EXIT;
				
				pUdpMsger->sendMsg(&msgstruct, pOpponent);
				
			}

		
			// 释放申请的内存
			if (pUdpMsger != NULL)
			{
				//pUdpMsger->destoryInstance();
				delete pUdpMsger;
				pUdpMsger = NULL;
			}
			if (pGameManager != NULL)
			{
				delete pGameManager;
				pGameManager = NULL;
			}
			if (pBlackPlayer != NULL)
			{
				delete pBlackPlayer;
				pBlackPlayer = NULL;
			}
			if (pWhitePlayer != NULL)
			{
				delete pWhitePlayer;
				pWhitePlayer = NULL;
			}

		} else {
			return;
		}	
	}
	soundPlayer.PlayMusicRepeat(FALSE);// 关闭背景音乐
	StartUpAnimation *p = (StartUpAnimation *)GetParent();
	if (p != NULL)
	{
		p->ShowWindow(SW_SHOWNORMAL | SW_NORMAL);// 显示父窗口
		
		// 销毁非模态对话框，把父窗口指向它的指针至空
		if (p->pPgobangDlg == this) {
			p->pPgobangDlg = NULL;
		}
		else if(p->pCgobangDlg == this) {
			p->pCgobangDlg = NULL;
		}
		else if(p->pNgobangDlg == this) {
			p->pNgobangDlg = NULL;
		}
	}
	

	CDialog::OnCancel();
	DestroyWindow();//WM_DESTROY 销毁非模态对话框
}
// 在屏幕只输出文字(不要底色)
void CGobangDlg::strTextOut(CDC &dc, int cx, int cy, CFont &font, CString &str)
{
	CFont *oldFont = dc.SelectObject(&font);
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(cx, cy, str);
	dc.SelectObject(oldFont);
}

// 最小化
void CGobangDlg::OnMinsizeBtn() 
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


BOOL CGobangDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default

// 	CPoint pointPos;
// 	::GetCursorPos(&pointPos); 

	if (hadSetCur == false && m_hCurNormal)
	{
		SetCursor(m_hCurNormal);
		return TRUE;
	}
	else {
		//hadSetCur = false;
	
		return TRUE;
	}

// 	if (pGameManager && pGameManager->isGameStart())
// 	{
// 		return TRUE;
// 	}
// 	if (m_handCur)
// 	{
// 		SetCursor(m_handCur);
// 		return TRUE;
// 	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CGobangDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// 在棋盘范围内，鼠标指针显示下棋的手
	if (pGameManager && pGameManager->isGameStart() && point.x > boardTabRect.left && point.x < boardTabRect.right
		&& point.y > boardTabRect.top && point.y < boardTabRect.bottom)
	{
		SetCursor(m_putChess);
		hadSetCur = true;
	}
	else {
		hadSetCur = false;
	}

	CDialog::OnMouseMove(nFlags, point);
}
// 最小化到托盘（参数是让父窗口记录最小化的是哪个窗口)
void CGobangDlg::ToTray()
{
	
	StartUpAnimation *pSa = (StartUpAnimation *)GetParent();  
	if (NULL == pSa)
	{
		return;
	}
	StartUpAnimation::ForegroundWindow fw;

	if (SINGLE_MODE == gameMode)
	{
		fw = StartUpAnimation::LOCAL_SINGLE;
	} else if (COMPUTER_MODE == gameMode)
	{
		fw = StartUpAnimation::VS_COMPUTER;
	}
	else if (ONLINE_MODE == gameMode)
	{
		fw = StartUpAnimation::VS_ONLINE;
	}
	
	
	pSa->ToTray(fw);

	ShowWindow(SW_HIDE);
	
}

// 给按钮加图片等美化
BOOL CGobangDlg::setBtnsImg()
{
//	short	shBtnColor = 30;
	HBITMAP hBitmapIn = NULL, hBitmapOut = NULL;

	hBitmapOut = getBmpImg(CString("./resource/buttons/theme_gray/toTray.bmp"));
	
	if (hBitmapOut) {
		m_btnToTray.SetBitmaps(hBitmapOut, maskColor);
	//m_btnToTray.SetIcon(IDI_ICON_XU);// (int)BTNST_AUTO_GRAY);
		m_btnToTray.SetWindowText("");
		m_btnToTray.DrawTransparent(FALSE);
	}
	
	m_btnToTray.SetTooltipText(_T("最小化到托盘"));

	hBitmapIn = getBmpImg(minSizeBmpPathIn);
	hBitmapOut = getBmpImg(minSizeBmpPathOut);
	if (hBitmapIn && hBitmapOut)
	{
		m_btnMinSize.SetBitmaps(hBitmapIn, maskColor, hBitmapOut, maskColor);
		m_btnMinSize.SetWindowText("");
		m_btnMinSize.DrawTransparent(FALSE);
	}
	
	m_btnMinSize.SetTooltipText(_T("最小化"));

	
//	m_btnStart.ModifyStyle(0, BS_BITMAP | BS_OWNERDRAW);//
// 	m_btnStart.SetButtonStyle(BS_BITMAP | BS_OWNERDRAW);
	
	//	m_btnCancel.SubclassDlgItem(IDI_ICON_EXIT, this);
// 	m_btnCancel.SetIcon(IDI_ICO_EXIT);//, );
	hBitmapIn = getBmpImg(cancelBmpPathIn);
	hBitmapOut = getBmpImg(cancelBmpPathOut);
	if (hBitmapIn && hBitmapOut)
	{
		m_btnCancel.SetBitmaps(hBitmapIn, maskColor, hBitmapOut, maskColor);
		m_btnCancel.SetWindowText("");
		m_btnCancel.DrawTransparent(FALSE);
		//	m_btnCancel.DrawBorder(FALSE);
	}
	m_btnCancel.SetTooltipText(_T("退出游戏"));

	hBitmapIn = getBmpImg(skinBmpPath);
	if (hBitmapIn)
	{
		m_btnSkin.SetBitmaps(hBitmapIn, maskColor);
		m_btnSkin.SetWindowText("");
		m_btnSkin.DrawTransparent(FALSE);
	}
	m_btnSkin.SetTooltipText("切换皮肤");

	hBitmapIn = getBmpImg(startBtnBmpPathIn);
	hBitmapOut = getBmpImg(startBtnBmpPathOut);
	if (hBitmapIn && hBitmapOut )
	{
		m_btnStart.SetBitmaps(hBitmapIn, maskColor, hBitmapOut, maskColor);
		m_btnStart.SetWindowText("");
		m_btnStart.DrawTransparent(TRUE);
		m_btnStart.DrawBorder(FALSE);
	}

	m_btnStart.SetTooltipText("开始游戏");
	m_btnStart.SetCursor(m_handCur);
//  m_btnStart.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(51,161,201));//鼠标进
// 	m_btnStart.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(0,255,255));
//	m_btnStart.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
// 	m_btnStart.SetAlign(CButtonST::ST_ALIGN_VERT);

	hBitmapIn = getBmpImg(takeBackBmpPathIn);
	hBitmapOut = getBmpImg(takeBackBmpPathOut);
	if (hBitmapIn && hBitmapOut)
	{
		m_btnTakeBack.SetBitmaps(hBitmapIn, maskColor, hBitmapOut, maskColor);
		
		m_btnTakeBack.SetWindowText("");
		m_btnTakeBack.DrawTransparent(FALSE);
		m_btnTakeBack.DrawBorder(FALSE);
	}
	m_btnTakeBack.SetTooltipText("请求悔棋");
	m_btnTakeBack.SetCursor(m_handCur);

	hBitmapIn = getBmpImg(sendMsgBmpPath);
//	hBitmapOut = getBmpImg();
	if (hBitmapIn && hBitmapOut)
	{
		m_btnSendMsg.SetBitmaps(hBitmapIn, maskColor);
		m_btnSendMsg.DrawTransparent(FALSE);
		m_btnSendMsg.SetWindowText("");
	}
//	m_btnSendMsg.DrawBorder(FALSE);
	m_btnSendMsg.SetTooltipText("发送消息");

	hBitmapIn = getBmpImg(heqiBmpPathIn);
	hBitmapOut = getBmpImg(heqiBmpPathOut);
	if (hBitmapIn && hBitmapOut)
	{
		m_btnHeQi.SetBitmaps(hBitmapIn, maskColor, hBitmapOut, maskColor);
		m_btnHeQi.SetWindowText("");	
		m_btnHeQi.DrawTransparent(FALSE);
		
		m_btnHeQi.DrawBorder(FALSE);
	}
	m_btnHeQi.SetTooltipText(_T("请求和棋"));

	hBitmapIn = getBmpImg(giveUpBmpPathIn);
	hBitmapOut = getBmpImg(giveUpBmpPathOut);
	if (hBitmapIn && hBitmapOut)
	{
		m_btnGiveUp.SetBitmaps(hBitmapIn, maskColor, hBitmapOut, maskColor);
		m_btnGiveUp.SetWindowText("");
		m_btnGiveUp.DrawTransparent(FALSE);
		m_btnGiveUp.DrawBorder(FALSE);
	}
	
	m_btnGiveUp.SetTooltipText(_T("请求认输"));

	hBitmapIn = getBmpImg(suggestBmpPathIn);
	hBitmapOut = getBmpImg(suggestBmpPathOut);
	if (hBitmapIn && hBitmapOut) {
		m_btnSuggest.SetBitmaps(hBitmapIn, maskColor, hBitmapOut, maskColor);
		m_btnSuggest.SetWindowText("");
		m_btnSuggest.DrawTransparent(FALSE);
		m_btnSuggest.DrawBorder(FALSE);
	}
	m_btnSuggest.SetTooltipText("提示下一步");

	hBitmapIn = getBmpImg(settingBmpPathIn);
	hBitmapOut = getBmpImg(settingBmpPathOut);
	if (hBitmapIn && hBitmapOut)
	{
		m_btnSetting.SetBitmaps(hBitmapIn, maskColor, hBitmapOut, maskColor);
		m_btnSetting.SetWindowText("");
		m_btnSetting.DrawTransparent(FALSE);
	}
	m_btnSetting.SetTooltipText(_T("设置"));

	m_btnBackHome.ShowWindow(SW_HIDE);

// 	hBitmapIn = getBmpImg(backHomeBmpPathIn);
// 	hBitmapOut = getBmpImg(backHomeBmpPathOut);
// 	
// 	if (hBitmapIn && hBitmapOut)
// 	{
// 		m_btnBackHome.SetBitmaps(hBitmapIn, maskColor, hBitmapOut, maskColor);
// 		m_btnBackHome.DrawTransparent(FALSE);
// 		m_btnBackHome.SetWindowText("");
// 	}
// 	//m_btnBackHome.DrawBorder(FALSE);
// 	m_btnBackHome.SetTooltipText(_T("返回主界面"));

	// 对方的头像
	hBitmapIn = getBmpImg(rivalHeadPath);
	if (hBitmapIn)
	{
		m_rivalHeadBtn.SetBitmaps(hBitmapIn, maskColor);
		m_rivalHeadBtn.DrawTransparent(FALSE);
		
	}	
	m_rivalHeadBtn.SetWindowText("");

	hBitmapIn = getBmpImg(selfHeadPath);
	if (hBitmapIn)
	{
 		m_selfHeadBtn.SetBitmaps(hBitmapIn,maskColor);
		m_selfHeadBtn.DrawTransparent(FALSE);
		m_selfHeadBtn.SetWindowText("");
	}
	
	m_showRivalIp.SetFont(&m_numFont);
	m_showSelfIp.SetFont(&m_numFont);
	m_showRivalIp.DrawTransparent(FALSE);
	m_showSelfIp.DrawTransparent(FALSE);
	m_showRivalIp.DrawBorder(FALSE);
	m_showSelfIp.DrawBorder(FALSE);

	m_rivalChess.DrawTransparent(FALSE);
	m_rivalChess.SetWindowText("");	
	m_myChess.DrawTransparent(FALSE);
	m_myChess.SetWindowText("");
	
	m_countDownBtn.SetFont(&m_font);
	m_countDownBtn.SetWindowText("0");
	m_countDownBtn.DrawBorder(FALSE);
	m_countDownBtn.DrawTransparent(FALSE);
//	m_testBtn.SetBitmaps(hBitmapOut, maskColor);
//	m_testBtn.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255, 0, 0));
 
	m_musicBtn.SetWindowText("");
	m_musicBtn.DrawTransparent(FALSE);
	m_musicBtn.SetIcon(IDI_MUSIC);//, (int)BTNST_AUTO_GRAY);
	m_musicBtn.SetTooltipText("背景音乐");
#ifdef	BTNST_USE_BCMENU
	m_musicBtn.SetMenu(IDR_MENU_MUSIC, m_hWnd, TRUE, IDR_TOOLBAR);
#else
	m_musicBtn.SetMenu(IDR_MENU_MUSIC, m_hWnd);
#endif
	
 	m_musicBtn.SetFlat(TRUE);
//	m_musicBtn.SetRounded(TRUE);

	return TRUE;
}
// 各个控件的摆放位置
BOOL CGobangDlg::setUIwidgetPos()
{
	// 主窗口大小,位置居中
	SetWindowPos(this, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOZORDER);//
	CenterWindow(this);

	m_btnCancel.SetWindowPos(NULL,SCREEN_WIDTH-46, 2, 32, 32, SWP_SHOWWINDOW);
	m_btnMinSize.SetWindowPos(NULL, SCREEN_WIDTH-82, 2, 34, 32, SWP_SHOWWINDOW);
	m_btnToTray.SetWindowPos(NULL,SCREEN_WIDTH-119, 2, 32, 32, SWP_SHOWWINDOW);
	
	m_btnSkin.SetWindowPos(NULL, 810, 640, 45, 43, SWP_SHOWWINDOW);
	m_musicBtn.SetWindowPos(NULL,870, 640, 45, 45, SWP_SHOWWINDOW);
	m_btnSendMsg.SetWindowPos(NULL, 908, 570, 47, 30, SWP_SHOWWINDOW);
	m_btnSetting.SetWindowPos(NULL, 930, 640, 45, 45, SWP_SHOWWINDOW);

	int py = 634;
	int px = 180;
	m_btnStart.SetWindowPos(NULL, px, py, 100, 36, SWP_SHOWWINDOW);
	
	px += 120;
	m_btnTakeBack.SetWindowPos(NULL, px, py, 100,36, SWP_SHOWWINDOW);
	px += 120;
	m_btnHeQi.SetWindowPos(NULL, px, py, 100, 36, SWP_SHOWWINDOW);
	px += 120;
	m_btnGiveUp.SetWindowPos(NULL, px, py, 100, 36, SWP_SHOWWINDOW);
	px += 120;
	m_btnSuggest.SetWindowPos(NULL, px, py, 100, 36, SWP_SHOWWINDOW);
	m_btnBackHome.SetWindowPos(NULL, 850, 630, 45, 37, SWP_SHOWWINDOW);


	m_rivalHeadBtn.SetWindowPos(NULL, 42, 52, 117, 115, SWP_SHOWWINDOW);
	m_selfHeadBtn.SetWindowPos(NULL, 42, 495, 117, 115, SWP_SHOWWINDOW);
	
	m_showRivalIp.SetWindowText("");
	m_showSelfIp.SetWindowText("");
	m_showRivalIp.SetWindowPos(NULL, 40, 14, 110, 35, SWP_SHOWWINDOW);
	m_showSelfIp.SetWindowPos(NULL, 40, 627, 110, 35, SWP_SHOWWINDOW);
	
	m_rivalChess.SetWindowPos(NULL, 35, 293, 36, 34, SWP_SHOWWINDOW);
	m_myChess.SetWindowPos(NULL, 35, 327, 36, 34, SWP_SHOWWINDOW);

	m_countDownBtn.SetWindowPos(NULL, 80, 303, 60, 60, SWP_SHOWWINDOW);

	m_ShowMsg.SetWindowPos(NULL, 780, 284, 180, 282, SWP_SHOWWINDOW);
	m_SendMsg.SetWindowPos(NULL, 780, 574, 124, 27, SWP_SHOWWINDOW);
	m_ShowMsg.SetLimitText(UINT_MAX);


	// 贴图矩形位置
	// 头像及胜负情况
	playerInfoRect1.left = 28;
	playerInfoRect1.right = playerInfoRect1.left + 142;
	playerInfoRect1.top = 37;
	playerInfoRect1.bottom = playerInfoRect1.top + 245;
	
	playerInfoRect2.left = 28;
	playerInfoRect2.right = playerInfoRect2.left + 142;
	playerInfoRect2.top  = 375;
	playerInfoRect2.bottom = playerInfoRect2.top + 245;
	
	// 倒计时显示区域
	countDownRect.left = 27;
	countDownRect.right = countDownRect.left + 142;
	countDownRect.top = 282;
	countDownRect.bottom = countDownRect.top + 97;
	
	// logo显示
	logoRect.left = 773;
	logoRect.right = logoRect.left + 192;
	logoRect.top = 40;
	logoRect.bottom = logoRect.top + 230;
	// 聊天信息显示
	chatBgRect.left = logoRect.left - 2;
	chatBgRect.right = chatBgRect.left + 195;
	chatBgRect.top =  logoRect.bottom + 2;
	chatBgRect.bottom = chatBgRect.top + 340;
	// 棋盘格子背景区域
	tableBgRect.left = 185;
	tableBgRect.right = tableBgRect.left + 577;
	tableBgRect.top = 42;
	tableBgRect.bottom = tableBgRect.top + 572;
	// 棋盘格子（下棋开始后用于判断显示鼠标形状）
	boardTabRect.left = borderWidth - m_chessRadius;
	boardTabRect.right = borderWidth + (LinesNo - 1) * n_pixel + m_chessRadius;
	boardTabRect.top = borderHeight - m_chessRadius;
	boardTabRect.bottom = borderHeight + (LinesNo - 1) * n_pixel + m_chessRadius;

	return TRUE;
}


/*********************************************************************
配置文件中经常用到ini文件，在VC中其函数分别为：

写入.ini文件：bool WritePrivateProfileString(LPCTSTR lpAppName,LPCTSTR lpKeyName,LPCTSTR lpString,LPCTSTR lpFileName);

读取.ini文件：DWORD GetPrivateProfileString(LPCTSTR lpAppName,LPCTSTR lpKeyName,LPCTSTR lpDefaut,LPSTR lpReturnedString,DWORD nSize,LPCTSTR lpFileName);

读取整形值：UINT GetPrivateProfileInt(LPCTSTR lpAppName,LPCTSTR lpKeyName,INT nDefault,LPCTSTR lpFileName);

其中个参数的意思：

LPCTSTR lpAppName ------- INI文件中的一个字段名

LPCTSTR lpKeyName -------- lpAppName 下的一个键名，也就是里面具体的变量名

LPCTSTR lpString ---------是键值，也就是变量的值，必须为LPCTSTR或CString类型

LPCTSTR lpFileName --------完整的INI文件路径名

LPCTSTR lpDefaut ----------如果没有其前两个参数值，则将此值赋给变量

LPSTR lpReturnedString --------接收INI文件中的值的CString对象，即接收缓冲区

DWORD nSize ------接收缓冲区的大小
**********************************************************************************/
// 从ini文件读取路径
BOOL CGobangDlg::setUIwidgetPathFromFile(CString filepath)
{
// 	if (filepath.GetLength() < 1) {
// 		return FALSE;
// 	}

	m_curPathNormal	= __T("resource/ani/gobang_game.ani");
	m_curPathError  = __T("./resource/ani/nosymbol.cur");
	
	m_backgroundImgPath = "./resource/bg/theme_gray/background0.bmp";
	sendMsgBmpPath  = "./resource/buttons/theme_gray/sendMsg.bmp";
	// 鼠标在按钮上时显示
	cancelBmpPathIn = "./resource/buttons/theme_gray/close_light.bmp";
	minSizeBmpPathIn = "./resource/buttons/theme_gray/minSize_light.bmp";
	startBtnBmpPathIn = "./resource/buttons/theme_gray/start_light.bmp";
	takeBackBmpPathIn = "./resource/buttons/theme_gray/updo_light.bmp";
	heqiBmpPathIn  = "./resource/buttons/theme_gray/heqi_light.bmp";
	giveUpBmpPathIn = "./resource/buttons/theme_gray/giveUp_light.bmp";
	backHomeBmpPathIn = "./resource/buttons/theme_gray/home_light.bmp";
	settingBmpPathIn = "./resource/buttons/theme_gray/setting_light.bmp";
	suggestBmpPathIn = "./resource/buttons/theme_gray/suggest_light.bmp" ;
	// 鼠标不在按钮上
	cancelBmpPathOut = "./resource/buttons/theme_gray/close.bmp";
	minSizeBmpPathOut = "./resource/buttons/theme_gray/minSize.bmp";
	startBtnBmpPathOut = "./resource/buttons/theme_gray/start.bmp";
	takeBackBmpPathOut = "./resource/buttons/theme_gray/updo.bmp";
	heqiBmpPathOut  = "./resource/buttons/theme_gray/heqi.bmp";
	giveUpBmpPathOut = "./resource/buttons/theme_gray/giveUp.bmp";
	backHomeBmpPathOut = "./resource/buttons/theme_gray/home.bmp";
	settingBmpPathOut = "./resource/buttons/theme_gray/setting.bmp";
	suggestBmpPathOut = "./resource/buttons/theme_gray/suggest.bmp" ;
	
	blackChessBmpPath = "./resource/chesses/Black_White/chessBlack.bmp";
	whiteChessBmpPath = "./resource/chesses/Black_White/chessWhite.bmp";
	showBlackPath = __T("./resource/buttons/theme_gray/show_black.bmp");
	showWhitePath = __T("./resource/buttons/theme_gray/show_white.bmp");

	skinBmpPath = "./resource/buttons/theme_gray/skin.bmp";   //皮肤
	
	StartUpAnimation *psa = (StartUpAnimation *) GetParent();
	if (psa) {
		selfHeadPath.Format("./resource/headPortrait/theme_gray/head%d.bmp", 
			psa->configData.headPortrait);
	} else {
		selfHeadPath  = __T("./resource/headPortrait/theme_gray/head1.bmp");
	}
	
	if(gameMode == COMPUTER_MODE)
	{
		rivalHeadPath = __T("./resource/headPortrait/theme_gray/computer.bmp");
	}
	else {
		rivalHeadPath = __T("./resource/headPortrait/theme_gray/head0.bmp");
	}

	m_logoPath = __T("./resource/msg_show/theme_gray/logo.bmp");
	m_chatBgPath = __T("./resource/msg_show/theme_gray/msg.bmp");
	
	playerInfo1BmpPath = __T("./resource/msg_show/theme_gray/playerInfoRival.bmp");
	playerInfo2BmpPath = __T("./resource/msg_show/theme_gray/playerInfoSelf.bmp");
	countDownPath = __T("./resource/msg_show/theme_gray/countDownBg.bmp");
	tableBgPath = __T("./resource/msg_show/theme_gray/tableBg.bmp");

	return TRUE;
}
// 悔棋
void CGobangDlg::OnTakebackBtn() 
{

	if (pGameManager == NULL || ! pGameManager->isGameStart() || pGameManager->getVecRecord()->size() <= 0)
	{
		return;
	}
	bool isOk = false;
	int step = 1;
	CGamePlayer *pToTackBack = NULL, *acceptTakeBack = NULL;
	// 对于在不同游戏模式下的悔棋进行处理
	if (pGameManager->getGameMode() == SINGLE_MODE)
	{
		if (pGameManager->whoIsRuning() == pOpponent->getMyChessType())
		{
			pToTackBack= pSelf;
			acceptTakeBack = pOpponent;
		}
		else {
			pToTackBack= pOpponent;
			acceptTakeBack = pSelf;
		}
		isOk = true;

	} 
	else if (pGameManager->getGameMode() == COMPUTER_MODE)
	{
		if (pGameManager->whoIsRuning() == pOpponent->getMyChessType())
		{
			pToTackBack= pOpponent;
			acceptTakeBack = pSelf;
			isOk = true;
		 // 因为这事电脑已经下了
		}
		else if (pGameManager->whoIsRuning() == pSelf->getMyChessType())
		{
			pToTackBack= pSelf;
			acceptTakeBack = pOpponent;
			isOk = true;
			//step = 1; // 因为这事电脑已经下了
		}
	}
	else if (pGameManager->getGameMode() == ONLINE_MODE)
	{
		isOk = false; // 发消息,然后等待对方回应才能悔棋
		MsgStruct msgStruct;
		memset(&msgStruct, 0, sizeof(msgStruct));

		msgStruct.requestResponse = REQUEST_MSG;
		msgStruct.msg_type = UNDO_CHESS;
		msgStruct.content.undoChess.undo_nStep = 1;
		
		// 向对方发请求
		pUdpMsger->sendMsg(&msgStruct, pOpponent);
	}
	
	if (isOk)
	{
		if ( TRUE == pGameManager->takeBack(pToTackBack, acceptTakeBack, step))
		{
			Invalidate(FALSE);
			//	MessageBox("悔棋成功");
		}
		else {
			MessageBox("对不起，悔棋失败, 您的悔棋次数（7次)已够。");
		}
	}
	
}
// 最小化到托盘按钮
void CGobangDlg::OnBtnTotray() 
{

	ToTray();
	
//	ShowWindow(SW_HIDE);
}

void CGobangDlg::OnGameExit() 
{
	// 退出
	OnCancel();
}


void CGobangDlg::OnAbout() 
{
	// 关于对话框
	CGobangAboutDlg abDlg;
	abDlg.DoModal();
}


// 处理网络(UDP)过来的消息
BOOL CGobangDlg::handleNetMsg(MsgStruct *pMsgStruct, int bufLen, CString &ipStr, UINT port)
{
	if (pMsgStruct == NULL || bufLen <= 0 || port < 0  )
	{
		return FALSE;
	}

	MsgType  msgType = pMsgStruct->msg_type;
	
	//对家（对象）还没创建时，只接受请求开始游戏消息
	if (NULL == pOpponent && msgType != START_GAME)
	{
		return FALSE;
	}
// 不是跟自己玩的人过来的消息
	if (pOpponent && pOpponent->getIpString() != ipStr && pGameManager->isGameStart()) 
	{
		pMsgStruct->requestResponse = RESPONSE_MSG;
		pMsgStruct->msg_type = PLAYING; // 正在游戏中，请勿打扰
		pUdpMsger->SendTo(pMsgStruct, sizeof(*pMsgStruct), port, ipStr);
		return FALSE;
	}
	
	BOOL ret = FALSE;
	bool req_resp = pMsgStruct->requestResponse;
	
	// 处理请求消息
	if(req_resp == REQUEST_MSG) 
	{
		switch (msgType) 
		{
		case PUT_CHESS: // 下棋
			{
			
				ret = dealwithPutChessMsg(pMsgStruct);
				
			}
			break;

		case CHAT:
			{
			//	MessageBox("收到聊天消息");
				msgStr += pOpponent->getPlayerName();
				msgStr += __T(":\r\n");
				
				msgStr += CString(pMsgStruct->content.chatContent);
				msgStr += "\r\n";
				SetDlgItemText(IDC_ED_SHOWMSG, msgStr);
				UpdateData();
			}
			break;	
		case TIME_OUT:
			{
				// 时差1秒左右
				if ( pGameManager == NULL || pSelf == NULL || timeCount > 2) 
				{
					return FALSE;
				}
				chessType turn = pGameManager->whoIsRuning();
			// 状态还是轮到自己，说明还没给对方发消息,说明自己真的超时了，切换到对方
				if(turn != pSelf->getMyChessType()) {
					return FALSE;
				}
				// 先把状态设为对方，防止用户鼠标点击
				pGameManager->setWhoIsRun(pSelf->getOppenentChess());
				switchShowChess(pGameManager->whoIsRuning());
		//		CPoint point = randPutChess(turn);
			
				memset(pMsgStruct, 0, sizeof(MsgStruct));

				pMsgStruct->requestResponse = RESPONSE_MSG;
				pMsgStruct->msg_type  =  TIME_OUT;
				
				if (pUdpMsger->sendMsg(pMsgStruct, pOpponent))
				{
					pGameManager->setWhoIsRun(pOpponent->getMyChessType());
					switchShowChess(pGameManager->whoIsRuning());
				//	MessageBox("收到了超时请求消息， 已给对方回应");
				}	

				if (TIME_LIMIT > 0)
				{
					KillTimer(T_COUNT_DOWN);
					timeCount = TIME_LIMIT; // 给对方重新计时
				
					SetTimer(T_COUNT_DOWN, 1000, NULL);
				}				
			}
			break;
		case SYN_UPDATE:
			break;
		case UNDO_CHESS: // 收到悔棋请求
			{
				pMsgStruct->requestResponse = RESPONSE_MSG; // 回应对方
				pMsgStruct->msg_type = UNDO_CHESS;
				CString str;
				str.Format("%s 要申请悔棋，是否同意?", pOpponent->getPlayerName());
				if (IDNO == MessageBox(str, NULL, MB_YESNO))
				{		
					// 不同意回应step 为0
					pMsgStruct->content.undoChess.undo_nStep = 0;
				} 

				pUdpMsger->sendMsg(pMsgStruct, pOpponent);
				if (pGameManager->takeBack(pOpponent, pSelf,pMsgStruct->content.undoChess.undo_nStep))
				{
					timeCount = TIME_LIMIT;
					Invalidate(FALSE);
				}
				
			}
	
			break;
		case USR_INFO:
			break;
		case START_GAME:
			{	
				chessType c_type = pMsgStruct->content.startGame.chess_type; //对方使用的棋子
				CString Info;
				Info.Format(_T("玩家：%s (ip:%s)请求开始游戏，"),pMsgStruct->usrInfo.username, ipStr);
				
				if (BLACK == c_type)
				{
					Info += "执黑棋，是否同意？";
				}
				else if (WHITE == c_type)
				{
					Info += "执白棋，是否同意？";
				}

				if (IDYES == MessageBox(Info, NULL, MB_YESNO))
				{
					handleStartGameMsg(pMsgStruct, bufLen, ipStr, port);
					pMsgStruct->content.startGame.isAgree = true;
				}
				else {
					pMsgStruct->content.startGame.isAgree = FALSE;
				}
				
				//给对方回应
				pMsgStruct->requestResponse = RESPONSE_MSG;
				pMsgStruct->msg_type  = START_GAME;
				
				if (!pUdpMsger->sendMsg(pMsgStruct, pOpponent))
				{
					MessageBox("发送失败");
					ret = FALSE;
				}
			}
			break;
		case STOP_GAME:
			{
				if (pGameManager)
				{
					pGameManager->stopGame();
					if (TIME_LIMIT > 0)
					{
						KillTimer(T_COUNT_DOWN);
					}
					
					MessageBox("对方已经离开游戏");
				}
			}
			break;
		case ONLINE:
			{

			}
			break;
		case OFFLINE:
			{

			}
			break;
		case GIVE_UP:
			{
				if (pGameManager)
				{
					pGameManager->stopGame();
					KillTimer(T_COUNT_DOWN);
					pGameManager->setWinner(pSelf);
				//	pMsgStruct->requestResponse = RESPONSE_MSG;
				//	pUdpMsger->sendMsg(pMsgStruct, pOpponent);
					Invalidate(FALSE);
					//MessageBox("对方认输了。。");
				}
				

			}
			break;
		case WIN_WIN:
			{
				if (pGameManager && pGameManager->isGameStart())
				{
					CString str;
					str.Format("%s 向你求和啦，同意否？");
					if (IDYES == MessageBox(str, NULL, MB_YESNO))
					{
				
						pGameManager->stopGame();
						if (TIME_LIMIT > 0)
						{
							KillTimer(T_COUNT_DOWN);
						}
						
						CClientDC dc(this);
						strTextOut(dc, 300, 45, m_font, CString(__T("~ 哈哈,本局和棋啦~")) );
						pMsgStruct->content.isWinWin = true;
					}
					else {
						pMsgStruct->content.isWinWin = false;
					}
					pMsgStruct->requestResponse = RESPONSE_MSG; // 回应对方

					pUdpMsger->sendMsg(pMsgStruct, pOpponent);
				}
				
			}

			break;
		case EXIT:
			{
				
				pGameManager->stopGame();
				if (TIME_LIMIT > 0)
				{
					KillTimer(T_COUNT_DOWN);
				}
				MessageBox("对方已经退出游戏。。。");
				CClientDC dc(this);
				strTextOut(dc, 300, 45, m_font, CString(__T("~ 哈哈,对方已退出游戏啦~")) );
			}

			break;
											
		}
	}
// 应答(回应)的消息
	else if (RESPONSE_MSG == req_resp)
	{
		switch (msgType) 
		{
		case PUT_CHESS:
			//MessageBox("回应下棋成功");
			break;
		case TIME_OUT:
			{		
				// 之前发的请求有回应了,
			//	ret = dealwithPutChessMsg(pMsgStruct);
				// 对方回应他超时了,切换状态
				pGameManager->setWhoIsRun(pSelf->getMyChessType());
				switchShowChess(pGameManager->whoIsRuning());
				timeCount = TIME_LIMIT;
				SetTimer(T_COUNT_DOWN, 1000, NULL);
				
			}
			break;
		case SYN_UPDATE:
			break;

		case CHAT:
			break;
		case UNDO_CHESS:
			{
	//	MessageBox("收到应答悔棋消息");
				int nStep = pMsgStruct->content.undoChess.undo_nStep;
				chessType turn = pGameManager->whoIsRuning();
				if ( nStep > 0) // 对方回复nStep == 0不同意，> 0对方同意悔棋
				{
					CGamePlayer *pToTackBack, *acceptTakeBack;
					// 现在轮到对方了,对方还没下，这时请求悔棋，悔棋2步

					pToTackBack = pSelf;
					acceptTakeBack = pOpponent;
				
// 					if ( turn == pOpponent->getMyChessType())
// 					{
// 						pToTackBack = pOpponent;
// 						acceptTakeBack = pSelf;
// 						
// 						//nStep = 1; 
// 					}
// 					else //if (turn == pSelf->getMyChessType())
// 					{
// 						pToTackBack= pSelf;
// 						acceptTakeBack = pOpponent;
// 					
// 						//nStep = 2; // 因为这已经下了
// 					}

					if ( TRUE == pGameManager->takeBack(pToTackBack, acceptTakeBack, nStep))
					{
						Invalidate(FALSE);
						timeCount = TIME_LIMIT;
					//	MessageBox("悔棋成功");
					}
// 					else {
// 						ret = FALSE;
// 						MessageBox("悔棋失败, 可能您的悔棋次数（5次)已够。");
// 
// 					}
				}
				else {
					MessageBox("对不起，对方不同意悔棋。");
				}
			}
		
			break;
		case USR_INFO:
			break;
		case START_GAME:
			if (pGameManager && !pGameManager->isGameStart())
			{
				if (false == pMsgStruct->content.startGame.isAgree)
				{
					MessageBox("对不起，对方暂时不想跟你游戏。。");
					return FALSE;
				}
				if (TIME_LIMIT > 0)
				{
					timeCount = TIME_LIMIT;
					SetTimer(T_COUNT_DOWN, 1000, NULL);
					KillTimer(T_WAIT_START);
				}
			
				pGameManager->startGame(pGameManager->getWhoFirst());

				rivalHeadPath.Format("./resource/headPortrait/theme_gray/head%d.bmp", 
					pMsgStruct->content.startGame.headPortrait);

				HBITMAP hBitmap = getBmpImg(rivalHeadPath);
				if(hBitmap) {
					m_rivalHeadBtn.SetBitmaps(hBitmap, maskColor);

				}
				pOpponent->setPlayerName(CString(pMsgStruct->content.startGame.nikeName));
				Invalidate(FALSE);

				//MessageBox("开始游戏消息的回应, 准备开始啦。。");
			}
			
			break;
		case ONLINE:
			{

			}
			break;
		case OFFLINE:
			{

			}
			break;
		case STOP_GAME:
			{

			}
			break;
		case GIVE_UP:
			{

			}
			break;
		case WIN_WIN: //求和
			{
				if (pMsgStruct->content.isWinWin == true) {
				//	Invalidate(FALSE);
					pGameManager->stopGame();
					if (TIME_LIMIT > 0)
					{
						KillTimer(T_COUNT_DOWN);
					}
				
					CClientDC dc(this);
					strTextOut(dc, 300, 45, m_font, CString(__T("~ 哈哈,本局和棋啦~")) );
				}
				else {
					MessageBox("对不起，对方不同意和棋");
				}
			}
			
			break;
		case EXIT:
			{

			}
			break;
		case PLAYING:
			{
				MessageBox("对不起，对方正在游戏");
			}
			break;
		}
	}
	

	return ret;
}

// 联机对战时下棋处理
BOOL CGobangDlg::playInNetword(UINT nFlag, CPoint point)
{

	chessType cType;
	int chess_x = point.x;
	int chess_y = point.y;
	
	if (pGameManager->getBoardPos(chess_x, chess_y, cType))
	{
		if (NOCHESS  == cType)
		{	
			MsgStruct msgStruct;
			CClientDC dc(this);
			chessType turn = pGameManager->whoIsRuning();
			chessType myChess = pSelf->getMyChessType();
			
			if ( myChess == turn) 
			{
				// 先把状态转为对方
				pGameManager->setWhoIsRun(pSelf->getOppenentChess());
				memset(&msgStruct, 0, sizeof(msgStruct));
				
				CString romoteIpstr = pOpponent->getIpString();
				UINT romotePort = pOpponent->getPort();
				msgStruct.requestResponse = REQUEST_MSG;
				msgStruct.msg_type = PUT_CHESS;
				pGameManager->setBoardPos( chess_x, chess_y, myChess);
 				
				chessVoice.PlayMusicNoRepeat(TRUE);
//  	 			DrawOneChess(dc, myChess,chess_x*n_pixel, chess_y*n_pixel);
// 				chessRect.top += 5;
// 				DrawNumber(dc, chessRect, chessNumColor, pGameManager->getVecRecord()->size());

		//		Invalidate(FALSE);
				msgStruct.content.playChess.chess_x = chess_x;
				msgStruct.content.playChess.chess_y = chess_y;
				strcpy(msgStruct.usrInfo.username, pSelf->getPlayerName());
				// 给对方发消息
				pUdpMsger->sendMsg(&msgStruct, pOpponent);
				
				if (pGameManager->judgeVictory(chess_x, chess_y, myChess))
				{
					pGameManager->stopGame();
					if (TIME_LIMIT > 0)
					{
						KillTimer(T_COUNT_DOWN);
					}					
				}
				else {	
					timeCount = TIME_LIMIT;
					switchShowChess(pGameManager->whoIsRuning());
				//	MessageBox("下棋，并发了消息给对方");
					//SetTimer(T_COUNT_DOWN, 1000, NULL);		
				}
				Invalidate(FALSE);	
			} 
			
		}
	}

	return TRUE;
}

BOOL CGobangDlg::saveUiPathToFile(CString &path_ini)
{
	return TRUE;
}

void CGobangDlg::OnHeqiBtn() 
{
	if (NULL == pGameManager || ! pGameManager->isGameStart())
	{
		return;
	}
	if (ONLINE_MODE == gameMode)
	{
		MsgStruct msgstruct;
		msgstruct.requestResponse = REQUEST_MSG;
		msgstruct.msg_type = WIN_WIN;
		
		pUdpMsger->sendMsg(&msgstruct, pOpponent);
		
	}
	else {
		pGameManager->stopGame();
		KillTimer(T_COUNT_DOWN);
		CClientDC dc(this);
		strTextOut(dc, 300, 40, m_font, CString(__T("~ 哈哈,本局和棋啦~")) );
	}
}
// 认输处理
void CGobangDlg::OnGiveupBtn() 
{
	if (NULL == pGameManager || !pGameManager->isGameStart())
	{
		return;
	}

	if (gameMode == ONLINE_MODE)
	{
		MsgStruct msgstruct;
		msgstruct.requestResponse = REQUEST_MSG;
		msgstruct.msg_type = GIVE_UP;

		pUdpMsger->sendMsg(&msgstruct, pOpponent);

	}

	if (pGameManager->whoIsRuning() == pSelf->getMyChessType())
	{
		pGameManager->setWinner(pOpponent);
	}
	else {
		pGameManager->setWinner(pSelf);
	}
	pGameManager->stopGame();
	if (TIME_LIMIT > 0)
	{
		KillTimer(T_COUNT_DOWN);
	}
	
	Invalidate(FALSE);

	// TODO: Add your control notification handler code here
//	selectChess = BLACK;
// 	CClientDC dc(this);
// 	CFont myFont;
// 	myFont.CreatePointFont(200, "华文细黑");
// 	CFont* oldFont = dc.SelectObject ( &myFont);
// 	dc.SetTextColor (RGB (255,0,0));
// 	
// 	dc.SetBkMode(TRANSPARENT); //背景模式为透明
// 	
// 	dc.TextOut(200,200,"屏幕上显示文字");
//	Invalidate(FALSE);
//	dc.SelectObject ( oldFont);
// 	static int i = 0;
// 	CString count;
// 	count.Format("计数:%d", i++);
// //	m_countDown.SetWindowText(count);
// 	CStatic *pStatic=(CStatic*)GetDlgItem(IDC_COUNT_DOWN);
// 	m_countDown.ShowWindow(SW_HIDE);
// 	pStatic->SetWindowText(count);
// 	m_countDown.ShowWindow(SW_SHOW);
// 	if (timeCount == 0)
// 	{
// 		SetTimer(T_COUNT_DOWN, 1000, NULL);
// 		timeCount = 20;
// 	}
	
}

// 联机模式下，处理远端过来的请求开始游戏消息
BOOL CGobangDlg::handleStartGameMsg(MsgStruct *pMsgStruct, int bufLen, CString &ipStr, UINT port)
{
	//MessageBox("请求开始游戏");
	//对方使用的棋子
	chessType c_type = pMsgStruct->content.startGame.chess_type; 

	// 对方选择的棋子
	if (BLACK == c_type)
	{
		selectChess = WHITE;
	} else if (WHITE == c_type)
	{
		selectChess = BLACK;
	}

	initGame(ONLINE_MODE);
	if (WHITE == selectChess) //自己选到的棋子颜色
	{
		pSelf     = pWhitePlayer;
		pOpponent = pBlackPlayer;
		
	
	} else if (selectChess == BLACK)
	{
		pSelf     = pBlackPlayer;
		pOpponent = pWhitePlayer;
		
		
	}else {
		selectChess = BLACK;
		c_type = WHITE;
		pOpponent = pWhitePlayer;
		pSelf  = pBlackPlayer;//MessageBox("对方么有指定选什么类型的棋子");
	}
	initChessSwitchBmp(selectChess);
	
	rivalHeadPath.Format("./resource/headPortrait/theme_gray/head%d.bmp", 
		pMsgStruct->content.startGame.headPortrait);

	HBITMAP hBitmap = getBmpImg(rivalHeadPath);
	if(hBitmap) {
		m_rivalHeadBtn.SetBitmaps(hBitmap, maskColor);
	}
	// 对方昵称
	pOpponent->setPlayer(CString(pMsgStruct->content.startGame.nikeName), c_type);

	// 记下对方ip
	DWORD dwIp;
	dwIp = inet_addr(ipStr);
//	unsigned char *pIp = (unsigned char *)&dwIp;
	StartUpAnimation *pSa = (StartUpAnimation *)GetParent();  
	
	if (NULL != pSa)
	{
		memcpy(pSa->ipBytes, &dwIp, sizeof(dwIp));
		//BYTE *ipb = pSa->ipBytes;
		// 设置对方的头像
		pMsgStruct->content.startGame.headPortrait = pSa->configData.headPortrait;
		pSa->configData.timeOut = TIME_LIMIT = pMsgStruct->content.startGame.countDownTime;
	}
	pOpponent->setIpString(ipStr);
	pOpponent->setPort(port);

// 		CString str;
// 		str.Format("%d.%d.%d.%d", ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3]);
// 		MessageBox(str);
	strcpy(pMsgStruct->content.startGame.nikeName, pSelf->getPlayerName());
	pMsgStruct->content.startGame.chess_type = pSelf->getMyChessType();
	

	if (pMsgStruct->content.startGame.whoFirst) //判断谁先手
	{
		pGameManager->setWhoFirst(pOpponent->getMyChessType());
		pGameManager->setWhoIsRun(pOpponent->getMyChessType());
		
	}
	else {
		pGameManager->setWhoFirst(pSelf->getMyChessType());
		pGameManager->setWhoIsRun(pSelf->getMyChessType());
		
	}
	timeCount = TIME_LIMIT;
	if (TIME_LIMIT > 0)
	{	
		
		SetTimer(T_COUNT_DOWN, 1000, NULL);
	}

	Invalidate(FALSE);
	pGameManager->startGame(pGameManager->getWhoFirst());

	return TRUE;
}


// 设置按钮
void CGobangDlg::OnSettingBtn() 
{
	if (pGameManager && pGameManager->isGameStart())
	{
		MessageBox("正在游戏中，不能修改配置。");
		return;
	}
	
	StartUpAnimation *psa = (StartUpAnimation *) GetParent();
	if (psa) {
		CConfigDlg configDlg(psa);

	//	configDlg.UpdateData(FALSE);
		if(IDOK == configDlg.DoModal()) 
		{
			if(gameMode == ONLINE_MODE) {
				CString ipStr;
				BYTE *pb = psa->ipBytes;
				ipStr.Format("%d.%d.%d.%d",pb[0], pb[1], pb[2], pb[3]); 
				m_showRivalIp.SetWindowText(ipStr);
			}
			selfHeadPath.Format("./resource/headPortrait/theme_gray/head%d.bmp", 
				psa->configData.headPortrait);
			HBITMAP hBitmap = getBmpImg(selfHeadPath);
			if(hBitmap) {
				m_selfHeadBtn.SetBitmaps(hBitmap, maskColor);
			}
			if (pSelf)
			{
				pSelf->setPlayerName(CString(psa->nikeName));
			}
			
			TIME_LIMIT = psa->configData.timeOut;
		}
	}
	
// 	CNetwordSeting netSet;
// 	
// 	netSet.setPort(m_sendPort);
// 	netSet.setIpByte(ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3]);
// 	netSet.DoModal();
// 	netSet.getIpAddr(ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3]);
// 	CString ipStr;
// 	ipStr.Format("%d.%d.%d.%d", ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3]);
// 
// 	m_sendPort = netSet.getPort();
// 	if (pOpponent != NULL)
// 	{
// 		pOpponent->setIpString(ipStr);
// 		pOpponent->setPort(m_sendPort);
// 	}
	
}

HBRUSH CGobangDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	
// 	if (CTLCOLOR_STATIC == nCtlColor)
// 	{
// 		pDC->SetTextColor(RGB(0, 0, 250));
// 		pDC->SetBkMode(TRANSPARENT);
// 		hbr = (HBRUSH)GetStockObject( HOLLOW_BRUSH );
// 	}
	return hbr;
}

void CGobangDlg::OnTimer(UINT nIDEvent) 
{
	
	if (T_COUNT_DOWN == nIDEvent && TIME_LIMIT > 0)
	{
		doCountDown();
	}
	else if (T_WAIT_START == nIDEvent)
	{
		static	int waitSeconds = 10; // n秒后没收到开始游戏回应消息
		waitSeconds--;
		if(waitSeconds <= 0) {
			KillTimer(nIDEvent);
			if (pGameManager && !pGameManager->isGameStart())
			{
				MessageBox("对方可能不在，请稍候再发请求");
			}
			
			waitSeconds = 10;
		}
	}
	else if (T_SUGGEST_TIMER == nIDEvent) {
		/*staitc int  twinkleCount = 3; // 提示下棋，闪烁次数*/
			Invalidate(FALSE);
	
			KillTimer(nIDEvent);
	
	}
	CDialog::OnTimer(nIDEvent);
}





void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y)); 
	CDialog::OnLButtonDown(nFlags, point);
}



BOOL CGobangDlg::setGameMode(GameMode mode)
{
	gameMode = mode;

	return TRUE;
}
// 给棋子加序号
BOOL CGobangDlg::DrawNumber(CDC &dc, RECT &rect, COLORREF textColor, int num)
{
	CString numStr;
	
	numStr.Format("%d", num);
	CFont *pOldFont = dc.SelectObject(&m_numFont);
	COLORREF oldColor =	dc.SetTextColor(textColor);
	dc.SetBkMode(TRANSPARENT); //背景模式为透明
	
	DrawText(dc, numStr, numStr.GetLength(), &rect, DT_CENTER);
	dc.SelectObject(pOldFont);
	dc.SetTextColor(oldColor);

	dc.SetBkMode(OPAQUE); 
	return TRUE;
}

BOOL CGobangDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
// 	CRect rect; 
// 	GetDlgItem(IDC_START_BTN)->GetWindowRect(&rect); 
// 	ScreenToClient(&rect); 
// 	pDC->ExcludeClipRect (&rect);//该函数可以使这部分区域不被画

	return TRUE; // 屏蔽背景刷新（避免闪烁)
//	return CDialog::OnEraseBkgnd(pDC);
}

// 处理联机模式时，远端发来的下棋消息
BOOL CGobangDlg::dealwithPutChessMsg(MsgStruct *pMsg)
{
		if (pGameManager == NULL || !pGameManager->isGameStart() || 
			pGameManager->whoIsRuning() != pOpponent->getMyChessType())
		{
			return FALSE;
		}
		
		int cx = pMsg->content.playChess.chess_x;
		int cy = pMsg->content.playChess.chess_y;
		// 				CString msg;
		// 				msg.Format("x=%d y=%d", cx, cy);
		// 				msg += "下棋消息";
		// 				MessageBox(msg);
		if (! pGameManager->setBoardPos(cx, cy, pOpponent->getMyChessType()) )
		{
			MessageBox("下棋位置有误");
		}
		else {
		//	CClientDC dc(this);
			chessVoice.PlayMusicNoRepeat(TRUE);
			
// 			DrawOneChess(dc, pOpponent->getMyChessType(), cx*n_pixel, cy*n_pixel);
// 			chessRect.top += 5;
// 			DrawNumber(dc, chessRect, chessNumColor, pGameManager->getVecRecord()->size());
			
			if (pGameManager->judgeVictory(cx, cy, pOpponent->getMyChessType()))
			{
				pGameManager->stopGame();
			
		
			}
			else {// 切换对家
				pGameManager->setWhoIsRun(pSelf->getMyChessType());
				switchShowChess(pGameManager->whoIsRuning());
				timeCount = TIME_LIMIT;
			}
			Invalidate(FALSE);	
		}

		return TRUE;
}

//随机找一个空位下棋
CPoint CGobangDlg::randPutChess(chessType turn)
{
	int szCount = 0;
	CPoint point(-1, -1);
	CClientDC dc(this);
	
	point = pGameManager->getOneEmptyPosByRand();
	
	if (pGameManager->setBoardPos(point, turn))
	{
//		szCount = pGameManager->getVecRecord()->size();
// 		DrawOneChess(dc, turn, point.x * n_pixel, point.y * n_pixel);
// 		chessRect.top += 5;
		chessVoice.PlayMusicNoRepeat(TRUE);
		
//		DrawNumber(dc, chessRect, chessNumColor, szCount);
	}
	// 落子后检查胜负
	if (pGameManager->judgeVictory(point.x, point.y, turn))
	{
		pGameManager->stopGame();
		
		KillTimer(T_COUNT_DOWN);
		return point;
	}
	
	// 轮到自己
	if ( turn == pSelf->getMyChessType())
	{
		// 改变状态，到对方
		pGameManager->setWhoIsRun(pSelf->getOppenentChess());
		switchShowChess(pSelf->getOppenentChess());
		
	}
	else if (turn == pOpponent->getMyChessType() /*&& pGameManager->getGameMode() != ONLINE_MODE*/)  // 到对方
	{
		// 到对方
		pGameManager->setWhoIsRun(pOpponent->getOppenentChess());
		switchShowChess(pOpponent->getOppenentChess());
		
	}
	Invalidate(FALSE);

	return point;
}
// 切换显示当前该谁下棋了
BOOL CGobangDlg::switchShowChess(chessType turn)
{
	if (pSelf == NULL)
	{
		return FALSE;
	}
	if (pSelf->getMyChessType() == turn)
	{
		m_myChess.ShowWindow(SW_SHOW);
		m_rivalChess.ShowWindow(SW_HIDE);
	}
	else {
		m_rivalChess.ShowWindow(SW_SHOW);
		m_myChess.ShowWindow(SW_HIDE);
	}

	return TRUE;
}
//倒计时处理
BOOL CGobangDlg::doCountDown()
{
	if (NULL == pGameManager|| pSelf == NULL || NULL == pOpponent || !pGameManager->isGameStart())
	{
		return FALSE;
	}
	
	CString str;
	str.Format("%d",timeCount);
	m_countDownBtn.SetWindowText(str);
	
// 	m_countDown.ShowWindow(SW_HIDE);
//  countDownDc.SetBkMode(TRANSPARENT); //背景模式为透明
// 	
// 	m_countDown.SetWindowText(str);
// 	m_countDown.ShowWindow(SW_SHOW);
	
	// 时间到,若ONLINE_MODE下超时给对方发通知
	if (pGameManager->getGameMode() != ONLINE_MODE && timeCount <= 0)
	{
	
		timeCount = TIME_LIMIT;
		chessType turn = pGameManager->whoIsRuning();
		randPutChess(turn);
		
	}
	// 网络模式下自己超时则停止计数，不做任何动作，而如果对方超时，给对方发消息请他下棋
	else if (pGameManager->getGameMode() == ONLINE_MODE && timeCount <= 1)
	{
		if (TIME_LIMIT > 0)
		{
			KillTimer(T_COUNT_DOWN);
		}
	
		
		chessType turn = pGameManager->whoIsRuning();
		// 对方超时
		if (pSelf->getOppenentChess() == turn)
		{
			MsgStruct msgStruct;
			memset(&msgStruct, 0, sizeof(msgStruct));
			msgStruct.requestResponse = REQUEST_MSG;
			msgStruct.msg_type = TIME_OUT;
			
			if (pUdpMsger->sendMsg(&msgStruct, pOpponent))
			{
				//MessageBox("已发送消息请对方下棋");
			}
			else {
				return FALSE;
			}
			
		}
	}

	timeCount--;
	return TRUE;
}

// 更换皮肤
void CGobangDlg::OnSkinchgBtn() 
{
	//CustomBackground();
	static int i = 0;
	i = (++i) % 7;
	m_backgroundImgPath = "";
	m_backgroundImgPath.Format("./resource/bg/theme_gray/background%d.bmp", i); 
	bmpPicture.unLoad();
	bmpPicture.loadBmpFromFile(m_backgroundImgPath);
	
//	if (pGameManager && pGameManager->isGameStart())
	{// 先移除不让子窗口（按钮等)跟着父窗口一同刷新属性，到OnPaint（）再中加上
		ModifyStyle(WS_CLIPCHILDREN, 0); 
		bgroundChg = TRUE;
	}
	
	setBtnsImg();
	
	Invalidate(FALSE);
	
/*	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN);*/

}
// 点击开始游戏按钮
void CGobangDlg::OnStartBtn() 
{
	if (pGameManager != NULL && pGameManager->isGameStart())
	{
		return;
	}

	initGame(gameMode);	
	StartUpAnimation *psa = (StartUpAnimation *)GetParent();
	if(psa)
	{	
		if (gameMode == ONLINE_MODE)// && !bIsCreated)
		{	
			pUdpMsger = CUdpMessager::getMessagerInstance();
			pUdpMsger->Close();
			if (FALSE == pUdpMsger->Create(psa->myPort, SOCK_DGRAM, NULL))
			{
				MessageBox("网络初始化错误,请检查网络端口是否已被占用。");
				return;
			}
			else {
				pUdpMsger->initParentWnd(this);	
			}
		}


		if (0 == psa->configData.chessColor) {
			selectChess = BLACK;
		}
		else {
			selectChess = WHITE;
		}

		TIME_LIMIT = psa->configData.timeOut;
	}
	if (pGameManager != NULL && pBlackPlayer && pWhitePlayer 
		&& !pGameManager->isGameStart() && NULL != psa)
	{
		if (BLACK == selectChess)
		{
			pSelf = pBlackPlayer;
			pOpponent = pWhitePlayer;
		}
		else {
			pSelf = pWhitePlayer;
			pOpponent = pBlackPlayer;

		}
	
		initChessSwitchBmp(selectChess);
		pSelf->setPlayer(psa->nikeName, selectChess);
		pGameManager->setGamePlayer(pSelf, pOpponent);
		pGameManager->setWhoFirst(pSelf->getMyChessType()); // 先手
		switchShowChess(pSelf->getMyChessType());
		if (ONLINE_MODE == gameMode)
		{			
			
			pSelf->setPort(psa->myPort);
			BYTE *ipBytes = psa->ipBytes;
			CString str;
			str.Format("%d.%d.%d.%d", ipBytes[0], ipBytes[1], ipBytes[2], ipBytes[3]);
			pSelf->setIpString(str);
			pOpponent->setIpString(str);
			pOpponent->setPort(psa->farPort);
			
			MsgStruct msgstruct;
			memset(&msgstruct, 0, sizeof(msgstruct));
			
			msgstruct.requestResponse = REQUEST_MSG;
			msgstruct.msg_type = START_GAME;
			strcpy(msgstruct.usrInfo.username , pSelf->getPlayerName());
			msgstruct.usrInfo.usrId = rand() % 1000;
			msgstruct.content.startGame.chess_type = pSelf->getMyChessType();
			msgstruct.content.startGame.whoFirst = true; // 先手
			msgstruct.content.startGame.countDownTime = psa->configData.timeOut;
			msgstruct.content.startGame.headPortrait = psa->configData.headPortrait;
			strcpy(msgstruct.content.startGame.nikeName, psa->nikeName);

			if (pUdpMsger && !pUdpMsger->sendMsg(&msgstruct, pOpponent) )
			{
				MessageBox("发送失败");
			}
			else {
				MessageBox("开始游戏请求已发送,请稍候...");
				SetTimer(T_WAIT_START, 1000, NULL);
			}
			
		}
		else {
			timeCount = TIME_LIMIT;
			if (TIME_LIMIT > 0)
			{
				SetTimer(T_COUNT_DOWN, 1000, NULL);
			}
			
			pGameManager->startGame(pSelf->getMyChessType());
			
			soundStart.PlayMusicNoRepeat(TRUE);
		}
		ModifyStyle(0, WS_CLIPCHILDREN);// 防止父窗口刷新时子窗口也跟着刷新，解决按钮闪烁问题
		Invalidate(TRUE);		
	}
}

// 根据所选择的棋子类型，加载对应的bmp棋子，用于提示当前轮到谁下
void CGobangDlg::initChessSwitchBmp(chessType selectType)
{
	
	if (BLACK == selectType) {
		HBITMAP hBitmapIn = getBmpImg(showBlackPath);
		if (hBitmapIn)
		{
			m_myChess.SetBitmaps(hBitmapIn, RGB(190,190,190));
		}
		else {
			m_myChess.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0, 0, 0));
		}
		
		hBitmapIn = getBmpImg(showWhitePath);
		if (hBitmapIn)
		{
			m_rivalChess.SetBitmaps(hBitmapIn, RGB(90,90,90));
		}
		else {
			m_rivalChess.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0, 0, 0));
		}
	}
	else if (WHITE == selectType) {
		HBITMAP hBitmapIn = getBmpImg(showWhitePath);
		if (hBitmapIn)
		{
			m_myChess.SetBitmaps(hBitmapIn, RGB(190,190,190));
		}
		else {
			m_myChess.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0, 0, 0));
		}
		
		hBitmapIn = getBmpImg( showBlackPath);
		if (hBitmapIn)
		{
			m_rivalChess.SetBitmaps(hBitmapIn, RGB(90,90,90));
		}
		else {
			m_rivalChess.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0, 0, 0));
		}
	}
}

// 销毁非模态对话框
void CGobangDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete this;
}

// 电脑帮忙提示下一步
void CGobangDlg::OnSuggestBtn() 
{
	if (pGameManager && pGameManager->isGameStart()) {
		CPoint point;
		CGamePlayer *player = NULL;
		if (pGameManager->whoIsRuning() == pSelf->getMyChessType()) {
				player = pSelf;
		} 
		else {
			player = pOpponent;
		}
		if (player->getSuggestCount() > 7)
		{
			MessageBox("提示总共7次，您的提示次数已用完！");
			return;
		}
		point =	pGameManager->getSuggestPoint(player->getMyChessType(), 
				player->getOppenentChess());
		
		player->suggestAdd(1);
		CClientDC dc(this);
		
/*
		CPen *pOldPen, cpen;
		cpen.CreatePen(PS_SOLID, 2, RGB(210, 140, 180));
		int	x = borderWidth + point.x * n_pixel;
		int y = borderHeight + point.y * n_pixel;
		
		pOldPen= dc.SelectObject(&cpen);
		
		dc.Ellipse((int)(x-m_chessRadius), (int) (y-m_chessRadius), 
			(int)(x+m_chessRadius), (int)(y+m_chessRadius) );
		dc.SelectObject(pOldPen);

  */
		DrawOneChess(dc, player->getMyChessType(),point.x*n_pixel, point.y*n_pixel);
		SetTimer(T_SUGGEST_TIMER, 500, NULL);
	}
	
}

// 当某一方获胜时，屏幕显示相应信息
BOOL CGobangDlg::showWinner(CDC &dc)
{
	if (pGameManager != NULL)
	{
		CGamePlayer *pPlayer = pGameManager->getWinner();
		if (NULL == pPlayer)
		{
			return FALSE;
		}
		
		CString str;
		CMusicPlayer mup;
		mup.SetMusicFilePath(CString("./resource/sound/mp3/stopGame.mp3"));
		mup.PlayMusicNoRepeat(TRUE);

		if (pGameManager->getWinnerChessCount() >= 5) { 
			// 把赢者的5（n）个棋子用线连起来
			CPoint *points = pGameManager->getWin2points();
			if (points != NULL) {
				CPen bi,*pbi;
				
				bi.CreatePen(PS_DASH,3,RGB(0, 255, 0)); //创建(RGB(90,90,90)画笔
				pbi=dc.SelectObject(&bi); //选择画笔（并保存原来的画笔）
				
				dc.MoveTo(borderWidth + points[0].x * n_pixel, borderHeight + points[0].y * n_pixel);
				dc.LineTo(borderWidth + points[1].x * n_pixel, borderHeight + points[1].y * n_pixel);
				
				dc.SelectObject(&pbi);	
			}
			
			if (gameMode == ONLINE_MODE)
			{
				if (pPlayer == pSelf)
				{
					str.Format(_T("恭喜 %s 你赢啦。再接再厉哦。。"));
				}
				else {
					str.Format(_T("Sorry, 你输啦啦，要努力哦。。"));
				}
			
			} // 说明有一方认输
			else {
				str.Format("恭喜 %s 你赢啦。。", pPlayer->getPlayerName());
			}
			
		}
		else {
			str.Format("恭喜%s你赢啦。。", pPlayer->getPlayerName());
		}
		
		strTextOut(dc, 300, 40, m_font, str);
		pGameManager->setWinner(NULL);
		return TRUE;
	}

	return FALSE;
}

// 背景音乐1
void CGobangDlg::OnMusic1() 
{
	soundPlayer.PlayMusicRepeat(FALSE);
	soundPlayer.SetMusicFilePath(CString(_T("./resource/sound/mp3/kanong.mp3")));
	soundPlayer.PlayMusicRepeat(TRUE);
	
}

// 背景音乐2
void CGobangDlg::OnMusic2() 
{
	soundPlayer.PlayMusicRepeat(FALSE);
	soundPlayer.SetMusicFilePath(CString(_T("./resource/sound/mp3/千与千寻.mp3")));
	soundPlayer.PlayMusicRepeat(TRUE);
	
}

// 背景音乐3
void CGobangDlg::OnMusic3() 
{
	soundPlayer.PlayMusicRepeat(FALSE);
	soundPlayer.SetMusicFilePath(CString(_T("./resource/sound/mp3/LuvLetter.mp3")));
	soundPlayer.PlayMusicRepeat(TRUE);
	
}

void CGobangDlg::OnStopMusic() 
{
	soundPlayer.PlayMusicRepeat(FALSE);
	
}
// 鼠标滑过按钮时发出“呲”声
BOOL CGobangDlg::setHoverBtnSound()
{
//#ifdef	BTNST_USE_SOUND
	m_btnStart.SetPlaySound(true, "IDR_HVER");
	m_btnTakeBack.SetPlaySound(true, "IDR_HVER");
	m_btnHeQi.SetPlaySound(true, "IDR_HVER");
	m_btnGiveUp.SetPlaySound(true, "IDR_HVER");
	m_btnSuggest.SetPlaySound(true, "IDR_HVER");
	m_musicBtn.SetPlaySound(true, "IDR_HVER");
	m_btnSetting.SetPlaySound(true, "IDR_HVER");
	m_btnSendMsg.SetPlaySound(true, "IDR_HVER");
	m_btnSkin.SetPlaySound(true, "IDR_HVER");
	m_btnMinSize.SetPlaySound(true, "IDR_HVER");
	m_btnToTray.SetPlaySound(true, "IDR_HVER");
	m_btnCancel.SetPlaySound(true, "IDR_HVER");
//#endif

	return TRUE;
}

BOOL CGobangDlg::transparentTextOut(CDC &dc, RECT &rect, COLORREF color, CString &str)
{
	COLORREF oldColor =	dc.SetTextColor(color);
	dc.SetBkMode(TRANSPARENT); //背景模式为透明
	
	DrawText(dc, str, str.GetLength(), &rect, DT_CENTER);
	dc.SetTextColor(oldColor);
	
	dc.SetBkMode(OPAQUE); 
	return TRUE;
}
