// Gobang.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Gobang.h"
#include "GobangDlg.h"
#include "StartUpAnimation.h"
#include "GameHallDlg.h"
#include "tcpClientDlg.h"
#include "StartUp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CGobangApp

BEGIN_MESSAGE_MAP(CGobangApp, CWinApp)
	//{{AFX_MSG_MAP(CGobangApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGobangApp construction

CGobangApp::CGobangApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGobangApp object

CGobangApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGobangApp initialization

BOOL CGobangApp::InitInstance()
{
	AfxEnableControlContainer();

	if (!AfxSocketInit())
	{
		AfxMessageBox("网络初始化失败!");
		return FALSE;
	}
	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	// 开始前的动画
	CStartUp startUp;
	startUp.DoModal();
	
	int nResponse = 0;
	// 游戏模式选择界面
	StartUpAnimation startUpDlg;
	m_pMainWnd = &startUpDlg;
 	nResponse = startUpDlg.DoModal();

// 	CGameDlg gameDlg;
// 	m_pMainWnd = &gameDlg;
// 	nResponse = gameDlg.DoModal();
// 	CGobangDlg gobangDlg;
// 	nResponse = gobangDlg.DoModal();

// 
// 	CGameHallDlg gameHall;
// 	m_pMainWnd = &gameHall;
// 	nResponse = gameHall.DoModal();

// 	CtcpClientDlg cDlg;
// 	m_pMainWnd = &cDlg;
// 	nResponse = cDlg.DoModal();

	if (nResponse == IDOK)
	{
		//AfxMessageBox("end movie!");
	}



	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
