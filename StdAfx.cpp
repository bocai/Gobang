// stdafx.cpp : source file that includes just the standard includes
//	Gobang.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

void SetWindowEllispeFrame(HWND hwnd, int nWidthEllipse, int nHeightEllipse)
{
    HRGN hRgn;
    RECT rect;
	
    GetWindowRect(hwnd, &rect);
	
    hRgn = CreateRoundRectRgn(0, 0, rect.right - rect.left, rect.bottom - rect.top, nWidthEllipse, nHeightEllipse);
    SetWindowRgn(hwnd, hRgn, TRUE);
	
	// 	CString msg;
	// 	msg.Format("%d %d", rect.left, rect.right);
	// 	AfxMessageBox(msg);
}

void ShowCaption(HWND hWnd)
{
	LONG style = GetWindowLong(hWnd,GWL_STYLE);
    style     |= WS_CAPTION;
    SetWindowLong(hWnd,GWL_STYLE,style);
    RECT     r;   
    GetWindowRect(hWnd, &r);   
    r.bottom++;   
 //   MoveWindow(hWnd, r.left, r.bottom, r.right-r.left, r.bottom-r.top, TRUE);
	
}

void HideCaption(HWND hWnd)
{
	long style = GetWindowLong(hWnd,GWL_STYLE);   
    style     &= ~(WS_CAPTION);   
    SetWindowLong(hWnd,GWL_STYLE,style);
    RECT     r;   
    GetWindowRect(hWnd, &r);   
    r.bottom++;   
  //  MoveWindow(hWnd, r.left, r.bottom, r.right-r.left, r.bottom-r.top, TRUE);
}

HBITMAP getBmpImg(CString &bmpPath)
{
	return (HBITMAP)::LoadImage(NULL, bmpPath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
}