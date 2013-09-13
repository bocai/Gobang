// StartUp.cpp : implementation file
//

#include "stdafx.h"
#include "gobang.h"
#include "StartUp.h"

#define  T_MOVIE 3
#include <vfw.h>

#pragma comment(lib,"vfw32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartUp dialog


CStartUp::CStartUp(CWnd* pParent /*=NULL*/)
	: CDialog(CStartUp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartUp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	mvWait = 14;
}


void CStartUp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartUp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartUp, CDialog)
	//{{AFX_MSG_MAP(CStartUp)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartUp message handlers

void CStartUp::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (T_MOVIE == nIDEvent)
	{	
		if (mvWait-- <= 0)
		{	KillTimer(nIDEvent);
			SendMessage(WM_CLOSE); //关闭对话框 
		}
		if (mvWait == 1)
		{
			ShowWindow(SW_HIDE);
		}
		
		
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CStartUp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowPos(this, 0,0, 600, 460, SWP_NOZORDER);
	CenterWindow(this);
	SetWindowEllispeFrame(this->GetSafeHwnd(), 20, 20); // 窗口边角圆弧	
	HideCaption(this->GetSafeHwnd()); // 去掉系统自带的标题栏

	HWND m_VideoWnd; //视频窗口句柄
	long m_VideoLength; //视频放映总长度
	
	SetTimer(T_MOVIE, 300, NULL);
/************************************************************************/
/*	参数1、父窗口句柄      
	参数2、应用程序的实例句柄
	参数3、显示风格
	参数4、多媒体文件名
	
	  返回的HWND可以保存下来，以供以后使用，也可不保存。
	　　该函数会在其父窗口上创建一个子窗口，类似于创建一个控间如按扭或列表框等。
 　　该子窗口会占据父窗口一定空间，可带有播放按钮、进度条、菜单按钮等。
*/
/************************************************************************/

	m_VideoWnd = MCIWndCreate(this->GetSafeHwnd(),
							  AfxGetInstanceHandle(),//可取得本应用程序的实例句柄
							  WS_CHILD|WS_VISIBLE//注意用CHILD属性,这样,会使播放窗口依附于对话框上
							  |MCIWNDF_NOPLAYBAR
							  |MCIWNDF_NOMENU,
							  "./resource/bg/theme_gray/清风工作室1.0.mpg");

	CRect rcDlgs;
	this->GetWindowRect(&rcDlgs);
	ScreenToClient(&rcDlgs);

//	MCIWndSetZoom(m_VideoWnd, 1000);//设置屏幕大小
 	MCIWndSetSpeed(m_VideoWnd, 1000);
//	MoveWindow(&rcDlgs);
	::MoveWindow(m_VideoWnd, rcDlgs.left-30, rcDlgs.top - 6 ,
				 rcDlgs.Width()+58, rcDlgs.Height()+60, TRUE); //移动MCI窗口调整窗口的合适位

	m_VideoLength = MCIWndGetLength(m_VideoWnd);//获得视频放映总长度

	MCIWndPlay(m_VideoWnd);//播放视频文件


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
