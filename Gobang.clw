; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGobangDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gobang.h"
LastPage=0

ClassCount=13
Class1=CButtonST
Class2=CConfigDlg
Class3=CGameHallDlg
Class4=CGobangApp
Class5=CGobangAboutDlg
Class6=CAboutDlg
Class7=CGobangDlg
Class8=CNetwordSeting
Class9=CStartUp
Class10=StartUpAnimation
Class11=CtcpClientDlg
Class12=CTcpMessager
Class13=CUdpMessager

ResourceCount=11
Resource1=IDD_GAME_DLG
Resource2=IDD_CONFIG_DLG
Resource3=IDD_GAME_HALL_DLG
Resource4=IDD_DLG_CLIENT
Resource5=IDR_MENU_MUSIC
Resource6=IDD_GOBANG_DIALOG
Resource7=IDD_START_ANIMATION_DIALOG
Resource8=IDD_NETWORD_SETTING_DIALOG
Resource9=IDD_DLG_ABOUT
Resource10=IDR_GOBANG_MENU
Resource11=IDR_TOOLBAR

[CLS:CButtonST]
Type=0
BaseClass=CButton
HeaderFile=BtnST.h
ImplementationFile=BtnST.cpp

[CLS:CConfigDlg]
Type=0
BaseClass=CDialog
HeaderFile=ConfigDlg.h
ImplementationFile=ConfigDlg.cpp

[CLS:CGameHallDlg]
Type=0
BaseClass=CDialog
HeaderFile=GameHallDlg.h
ImplementationFile=GameHallDlg.cpp

[CLS:CGobangApp]
Type=0
BaseClass=CWinApp
HeaderFile=Gobang.h
ImplementationFile=Gobang.cpp

[CLS:CGobangAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=GobangAboutDlg.h
ImplementationFile=GobangAboutDlg.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=GobangDlg.cpp
ImplementationFile=GobangDlg.cpp
LastObject=IDM_MUSIC1

[CLS:CGobangDlg]
Type=0
BaseClass=CDialog
HeaderFile=GobangDlg.h
ImplementationFile=GobangDlg.cpp
LastObject=IDM_STOP_MUSIC
Filter=D
VirtualFilter=dWC

[CLS:CNetwordSeting]
Type=0
BaseClass=CDialog
HeaderFile=NetwordSeting.h
ImplementationFile=NetwordSeting.cpp

[CLS:CStartUp]
Type=0
BaseClass=CDialog
HeaderFile=StartUp.h
ImplementationFile=StartUp.cpp

[CLS:StartUpAnimation]
Type=0
BaseClass=CDialog
HeaderFile=StartUpAnimation.h
ImplementationFile=StartUpAnimation.cpp
LastObject=IDC_ABOUT

[CLS:CtcpClientDlg]
Type=0
BaseClass=CDialog
HeaderFile=tcpClientDlg.h
ImplementationFile=tcpClientDlg.cpp

[CLS:CTcpMessager]
Type=0
BaseClass=CSocket
HeaderFile=TcpMessager.h
ImplementationFile=TcpMessager.cpp

[CLS:CUdpMessager]
Type=0
BaseClass=CSocket
HeaderFile=UdpMessager.h
ImplementationFile=UdpMessager.cpp

[DLG:IDD_CONFIG_DLG]
Type=1
Class=CConfigDlg
ControlCount=19
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_HEAD_NEXT_BTN,button,1342242816
Control4=IDC_HEAD_PRE_BTN,button,1342242816
Control5=IDC_CORLOR_NEXT_BTN,button,1342242816
Control6=IDC_CORLOR_PRE_BTN,button,1342242816
Control7=IDC_TIME_NEXT_BTN,button,1342242816
Control8=IDC_TIME_PRE_BTN,button,1342242816
Control9=IDC_DIF_NEXT_BTN,button,1342242816
Control10=IDC_DIF_PRE_BTN,button,1342242816
Control11=IDC_IPADDR,SysIPAddress32,1342242816
Control12=IDC_ED_OP_PORT,edit,1350631552
Control13=IDC_ED_SEFT_PORT,edit,1350631552
Control14=IDC_DIF_SHOW,button,1342242816
Control15=IDC_COLOR_SHOW,button,1342242816
Control16=IDC_TIME_OUT_SHOW,button,1342242816
Control17=IDC_HEAD_SHOW,button,1342242816
Control18=IDC_ED_NAME,edit,1350631552
Control19=IDC_ST_NAME,static,1342308352

[DLG:IDD_GAME_HALL_DLG]
Type=1
Class=CGameHallDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TREE_ROOM,SysTreeView32,1350631431
Control4=IDC_TAB_ROOMS,SysTabControl32,1342177280

[DLG:IDD_DLG_ABOUT]
Type=1
Class=CGobangAboutDlg
ControlCount=1
Control1=IDC_QUIT_ABOUT,button,1342242816

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_GOBANG_DIALOG]
Type=1
Class=CGobangDlg
ControlCount=22
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_BTN_TEST,button,1342242816
Control4=IDC_MINSIZE_BTN,button,1342242816
Control5=IDC_TAKEBACK_BTN,button,1342242816
Control6=IDC_BTN_TOTRAY,button,1342242816
Control7=IDC_START_BTN,button,1342242816
Control8=IDC_HEQI_BTN,button,1342242816
Control9=IDC_GIVEUP_BTN,button,1342242816
Control10=IDC_SETTING_BTN,button,1342242816
Control11=IDC_SKINCHG_BTN,button,1342242816
Control12=IDC_BACK_HOME_BTN,button,1342242816
Control13=IDC_RIVAL_HEAD,button,1342242816
Control14=IDC_SELF_HEAD,button,1342242816
Control15=IDC_ED_SEND_MSG,edit,1350631552
Control16=IDC_ED_SHOWMSG,edit,1352730692
Control17=IDC_RIVAL_CHESS,button,1342242816
Control18=IDC_MY_CHESS,button,1342242816
Control19=IDC_COUNT_DOWN_BTN,button,1342242816
Control20=IDC_BTN_RIVAL_IP,button,1342242816
Control21=IDC_BTN_SELF_IP,button,1342242816
Control22=IDC_SUGGEST_BTN,button,1342242816

[DLG:IDD_NETWORD_SETTING_DIALOG]
Type=1
Class=CNetwordSeting
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_IP_ADDRESS,SysIPAddress32,1342242816
Control4=IDC_IP_STATIC,static,1342308352
Control5=IDC_EDIT_PORT,edit,1350631552
Control6=IDC_PORT_STATIC,static,1342308352

[DLG:IDD_GAME_DLG]
Type=1
Class=CStartUp
ControlCount=0

[DLG:IDD_START_ANIMATION_DIALOG]
Type=1
Class=StartUpAnimation
ControlCount=9
Control1=IDCANCEL,button,1342242816
Control2=IDC_SINGLE_BTN,button,1342242816
Control3=IDC_VS_COMPUTER_BTN,button,1342242816
Control4=IDC_VS_NETWORD_BTN,button,1342242816
Control5=IDC_EXIT_BTN,button,1342242816
Control6=IDC_MINWIN_BTN,button,1342242816
Control7=IDC_TOTRAY_BTN,button,1342242816
Control8=IDC_SET_BTN,button,1342242816
Control9=IDC_ABOUT,button,1342242816

[DLG:IDD_DLG_CLIENT]
Type=1
Class=CtcpClientDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CON_SVR,button,1342242816
Control4=IDC_EDIT_IP,edit,1350631552
Control5=IDC_EDIT_PORT,edit,1350639744
Control6=IDC_ED_MSG,edit,1353777348
Control7=IDC_ED_SEND,edit,1350631552

[MNU:IDR_GOBANG_MENU]
Type=1
Class=StartUpAnimation
Command1=IDM_GAME_EXIT
Command2=IDM_ABOUT
Command3=IDM_RULE_HELP
CommandCount=3

[MNU:IDR_MENU_MUSIC]
Type=1
Class=CGobangDlg
Command1=IDM_MUSIC1
Command2=IDM_MUSIC2
Command3=IDM_MUSIC3
Command4=IDM_STOP_MUSIC
CommandCount=4

[TB:IDR_TOOLBAR]
Type=1
Class=?
CommandCount=0

