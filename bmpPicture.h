// bmpPicture.h: interface for the CbmpPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPPICTURE_H__19F0C118_9229_4DFF_BF92_5A0791573222__INCLUDED_)
#define AFX_BMPPICTURE_H__19F0C118_9229_4DFF_BF92_5A0791573222__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#pragma comment(lib, "msimg32.lib")


// º”‘ÿbmpÕº∆¨
class CbmpPicture  
{
public:
	CBitmap * getBitmap();
	HBITMAP getHBitmap();
	BOOL loadBmpFromFile(CString &path);
	BOOL TansParentBlt(CDC &desDc, RECT rectPos, COLORREF color);
	BOOL PaintZoom(CDC &dc, RECT &rectPos);
	BOOL Paint(CDC &dc, const RECT &rcPos);
	BOOL loadBmpFromFile(char *path);
	bool loadBmpPicture(UINT resID);
	int getWidth();
	int getHeight();

	void unLoad();

	CbmpPicture();
	virtual ~CbmpPicture();
private:
	BITMAP Bitmap;
	CBitmap bmp;
	HBITMAP hBmp;
	int bmpWidth, bmpHeight;
};

#endif // !defined(AFX_BMPPICTURE_H__19F0C118_9229_4DFF_BF92_5A0791573222__INCLUDED_)
