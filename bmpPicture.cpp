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
	unLoad(); // ж���Ѵ��ڵ�λͼ��Դ

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
// �������ŵ���ͼ
BOOL CbmpPicture::Paint(CDC &dc, const RECT &rcPos)
{
	if (!bmp.GetSafeHandle()) //û���ػ����ʧ��
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
����ԭ�ͣ�BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int hHeightDest, 
	HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent)��
������
hdcDest��ָ��Ŀ���豸�����ľ����
nXOriginDest��ָ��Ŀ��������Ͻǵ�X�����꣬�������߼���λ��ʾ��
nYOriginDest��ָ��Ŀ��������Ͻǵ�Y�����꣬�������߼���λ��ʾ��
nWidthDest��ָ��Ŀ����εĿ�ȡ�
nHeightDest��ָ��Ŀ����εĸ߶ȡ�
hdcsrc��ָ��Դ�豸�����ľ����
nXOriginSrc��ָ��Դ���Σ����Ͻǣ���X�����꣬�������߼���λ��ʾ��
nYOriginsrc��ָ��Դ���Σ����Ͻǣ���Y�����꣬�������߼���λ��ʾ��
nWidthSrc��ָ��Դ���εĿ�ȡ�
nHeightSrc��ָ��Դ���εĸ߶ȡ�
crTransparent��Դλͼ�е�RGBֵ����͸����ɫ��(��RGB(0,0,0)Ҳ���Ǻ�ɫ����)����ֵ���������ִ�гɹ�����ô����ֵΪTRUE���������ִ��ʧ�ܣ���ô����ֵΪFALSE��
*/
// �����ŵ���ͼ
BOOL CbmpPicture::PaintZoom(CDC &dc, RECT &rectPos)
{
	if (!bmp.GetSafeHandle()) //û���ػ����ʧ��
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
	if (!bmp.GetSafeHandle()) //û���ػ����ʧ��
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
