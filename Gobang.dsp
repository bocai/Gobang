# Microsoft Developer Studio Project File - Name="Gobang" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Gobang - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Gobang.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gobang.mak" CFG="Gobang - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Gobang - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Gobang - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Gobang - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Gobang - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Gobang - Win32 Release"
# Name "Gobang - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\bmpPicture.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\CeXDib.cpp
# End Source File
# Begin Source File

SOURCE=.\ComputerHarder.cpp
# End Source File
# Begin Source File

SOURCE=.\computerPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\ComputerSimple.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GameHallDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GameManager.cpp
# End Source File
# Begin Source File

SOURCE=.\GamePlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Gobang.cpp
# End Source File
# Begin Source File

SOURCE=.\Gobang.rc
# End Source File
# Begin Source File

SOURCE=.\GobangAboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GobangChess.cpp
# End Source File
# Begin Source File

SOURCE=.\GobangDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HumanPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\NetwordSeting.cpp
# End Source File
# Begin Source File

SOURCE=.\ShadeButtonST.cpp
# End Source File
# Begin Source File

SOURCE=.\StartUp.cpp
# End Source File
# Begin Source File

SOURCE=.\StartUpAnimation.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\tcpClientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TcpMessager.cpp
# End Source File
# Begin Source File

SOURCE=.\UdpMessager.cpp
# End Source File
# Begin Source File

SOURCE=.\WinXPButtonST.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\bmpPicture.h
# End Source File
# Begin Source File

SOURCE=.\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\CeXDib.h
# End Source File
# Begin Source File

SOURCE=.\ComputerHarder.h
# End Source File
# Begin Source File

SOURCE=.\computerPlayer.h
# End Source File
# Begin Source File

SOURCE=.\ComputerSimple.h
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\GameHallDlg.h
# End Source File
# Begin Source File

SOURCE=.\GameManager.h
# End Source File
# Begin Source File

SOURCE=.\GamePlayer.h
# End Source File
# Begin Source File

SOURCE=.\Gobang.h
# End Source File
# Begin Source File

SOURCE=.\GobangAboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\GobangChess.h
# End Source File
# Begin Source File

SOURCE=.\GobangDlg.h
# End Source File
# Begin Source File

SOURCE=.\HumanPlayer.h
# End Source File
# Begin Source File

SOURCE=.\MusicPlayer.h
# End Source File
# Begin Source File

SOURCE=.\NetwordSeting.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShadeButtonST.h
# End Source File
# Begin Source File

SOURCE=.\StartUp.h
# End Source File
# Begin Source File

SOURCE=.\StartUpAnimation.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\tcpClientDlg.h
# End Source File
# Begin Source File

SOURCE=.\TcpMessager.h
# End Source File
# Begin Source File

SOURCE=.\UdpMessager.h
# End Source File
# Begin Source File

SOURCE=.\WinXPButtonST.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\resource\icon\About.ico
# End Source File
# Begin Source File

SOURCE=.\resource\icon\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\resource\icon\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\Gobang.ico
# End Source File
# Begin Source File

SOURCE=.\res\Gobang.rc2
# End Source File
# Begin Source File

SOURCE=.\resource\icon\Left6_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\resource\icon\no30x30.ico
# End Source File
# Begin Source File

SOURCE=.\resource\icon\No3_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\resource\icon\Right6_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\resource\icon\Run.ico
# End Source File
# Begin Source File

SOURCE=.\resource\buttons\theme_gray\sendBtn.ico
# End Source File
# Begin Source File

SOURCE=.\resource\sound\Sound.ico
# End Source File
# Begin Source File

SOURCE=.\resource\icon\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\resource\icon\toTray.ico
# End Source File
# Begin Source File

SOURCE=.\resource\icon\xu.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\resource\sound\Hover.wav
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\resource\icon\ringin.wav
# End Source File
# Begin Source File

SOURCE=.\resource\sound\ringin.wav
# End Source File
# End Target
# End Project
