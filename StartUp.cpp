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
			SendMessage(WM_CLOSE); //�رնԻ��� 
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
	SetWindowEllispeFrame(this->GetSafeHwnd(), 20, 20); // ���ڱ߽�Բ��	
	HideCaption(this->GetSafeHwnd()); // ȥ��ϵͳ�Դ��ı�����

	HWND m_VideoWnd; //��Ƶ���ھ��
	long m_VideoLength; //��Ƶ��ӳ�ܳ���
	
	SetTimer(T_MOVIE, 300, NULL);
/************************************************************************/
/*	����1�������ھ��      
	����2��Ӧ�ó����ʵ�����
	����3����ʾ���
	����4����ý���ļ���
	
	  ���ص�HWND���Ա����������Թ��Ժ�ʹ�ã�Ҳ�ɲ����档
	�����ú��������丸�����ϴ���һ���Ӵ��ڣ������ڴ���һ���ؼ��簴Ť���б��ȡ�
 �������Ӵ��ڻ�ռ�ݸ�����һ���ռ䣬�ɴ��в��Ű�ť�����������˵���ť�ȡ�
*/
/************************************************************************/

	m_VideoWnd = MCIWndCreate(this->GetSafeHwnd(),
							  AfxGetInstanceHandle(),//��ȡ�ñ�Ӧ�ó����ʵ�����
							  WS_CHILD|WS_VISIBLE//ע����CHILD����,����,��ʹ���Ŵ��������ڶԻ�����
							  |MCIWNDF_NOPLAYBAR
							  |MCIWNDF_NOMENU,
							  "./resource/bg/theme_gray/��繤����1.0.mpg");

	CRect rcDlgs;
	this->GetWindowRect(&rcDlgs);
	ScreenToClient(&rcDlgs);

//	MCIWndSetZoom(m_VideoWnd, 1000);//������Ļ��С
 	MCIWndSetSpeed(m_VideoWnd, 1000);
//	MoveWindow(&rcDlgs);
	::MoveWindow(m_VideoWnd, rcDlgs.left-30, rcDlgs.top - 6 ,
				 rcDlgs.Width()+58, rcDlgs.Height()+60, TRUE); //�ƶ�MCI���ڵ������ڵĺ���λ

	m_VideoLength = MCIWndGetLength(m_VideoWnd);//�����Ƶ��ӳ�ܳ���

	MCIWndPlay(m_VideoWnd);//������Ƶ�ļ�


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
