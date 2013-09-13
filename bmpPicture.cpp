// bmpPicture.cpp: implementation of the CbmpPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gobang.h"
#include "bmpPicture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CbmpPicture::CbmpPicture()
{
	bmpHeight = bmpWidth = 0;
	hBmp = NULL;
}

CbmpPicture::~CbmpPicture()
{

}


void CbmpPicture::unLoad()
{
	bmp.DeleteObject();
	memset(&bmp, 0, sizeof(bmp));
}

int CbmpPicture::getHeight()
{
	return bmpHeight;
}

int CbmpPicture::getWidth()
{

	return bmpWidth;
}



bool CbmpPicture::loadBmpPicture(UINT resID)
{
	unLoad(); // 卸载已存在的位图资源

	if (! bmp.LoadBitmap(resID))
	{
		return false;
	}
	
	bmp.GetBitmap(&Bitmap);

	return true;
}


BOOL CbmpPicture::loadBmpFromFile(char *filePath)
{
	if (NULL == filePath)
	{
		return FALSE;
	}
	
	
	hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),filePath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	if (NULL == hBmp)
	{
		return FALSE;
	}
	
	if ( ! bmp.Attach(hBmp) )
	{
		return FALSE;
	}
	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);
	
	bmpWidth = bitmap.bmWidth;
	bmpHeight = bitmap.bmHeight;

	return TRUE;
}
// 不带缩放的作图
BOOL CbmpPicture::Paint(CDC &dc, const RECT &rcPos)
{
	if (!bmp.GetSafeHandle()) //没加载或加载失败
	{
		return FALSE;
	}
	
	CDC compDc;
	compDc.CreateCompatibleDC(&dc);
	CBitmap *oldBmp = compDc.SelectObject(&bmp);
	dc.SetStretchBltMode(HALFTONE);
	
	if (!dc.BitBlt(rcPos.left, rcPos.top, rcPos.right - rcPos.left, rcPos.bottom - rcPos.top,
		&compDc, 0, 0, SRCCOPY) )
	{
		return FALSE;
	}
	compDc.SelectObject(oldBmp);
	return TRUE;
}
/*
函数原型：BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int hHeightDest, 
	HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent)；
参数：
hdcDest：指向目标设备环境的句柄。
nXOriginDest：指定目标矩形左上角的X轴坐标，坐标以逻辑单位表示。
nYOriginDest：指定目标矩形左上角的Y轴坐标，坐标以逻辑单位表示。
nWidthDest：指定目标矩形的宽度。
nHeightDest：指定目标矩形的高度。
hdcsrc：指向源设备环境的句柄。
nXOriginSrc：指定源矩形（左上角）的X轴坐标，坐标以逻辑单位表示。
nYOriginsrc：指定源矩形（左上角）的Y轴坐标，坐标以逻辑单位表示。
nWidthSrc：指定源矩形的宽度。
nHeightSrc：指定源矩形的高度。
crTransparent：源位图中的RGB值当作透明颜色。(用RGB(0,0,0)也就是黑色不行)返回值：如果函数执行成功，那么返回值为TRUE；如果函数执行失败，那么返回值为FALSE。
*/
// 带缩放的作图
BOOL CbmpPicture::PaintZoom(CDC &dc, RECT &rectPos)
{
	if (!bmp.GetSafeHandle()) //没加载或加载失败
	{
		return FALSE;
	}
	
	CDC compDc;
	compDc.CreateCompatibleDC(&dc);
	CBitmap *oldBmp = compDc.SelectObject(&bmp);
	dc.SetStretchBltMode(HALFTONE);
	
	if (!dc.StretchBlt(rectPos.left, rectPos.top, rectPos.right - rectPos.left, rectPos.bottom - rectPos.top,
		&compDc, 0, 0, bmpWidth, bmpHeight, SRCCOPY) )
	{
		return FALSE;
	}
	compDc.SelectObject(oldBmp);
	return TRUE;
}

BOOL CbmpPicture::TansParentBlt(CDC &desDc, RECT rectPos, COLORREF color)
{
	if (!bmp.GetSafeHandle()) //没加载或加载失败
	{
		return FALSE;
	}
	
	CDC compDc;
	compDc.CreateCompatibleDC(&desDc);
	CBitmap *oldBmp = compDc.SelectObject(&bmp);
	compDc.SetStretchBltMode(HALFTONE);

	TransparentBlt(desDc.GetSafeHdc(), rectPos.left, rectPos.top, rectPos.right - rectPos.left, rectPos.bottom - rectPos.top,
				compDc.GetSafeHdc(), 0, 0, bmpWidth, bmpHeight, color);

	compDc.SelectObject(oldBmp);
	return TRUE;
}

BOOL CbmpPicture::loadBmpFromFile(CString &path)
{
	return loadBmpFromFile((LPSTR)(LPCTSTR)path);
}

HBITMAP CbmpPicture::getHBitmap()
{
	return hBmp;
}

CBitmap * CbmpPicture::getBitmap()
{
// 	return CBitmap::FromHandle(hBmp);
	return &bmp;
}
