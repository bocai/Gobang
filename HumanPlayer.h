// HumanPlayer.h: interface for the CHumanPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HUMANPLAYER_H__E2DC1CB7_7503_4CD1_B7E7_2A08D6DD146E__INCLUDED_)
#define AFX_HUMANPLAYER_H__E2DC1CB7_7503_4CD1_B7E7_2A08D6DD146E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GamePlayer.h"

class CHumanPlayer  : public CGamePlayer
{
public:
	CHumanPlayer();
	CHumanPlayer(chessType (*pChessBoard)[CHESS_BOARD_SIZE]);
	virtual ~CHumanPlayer();
//	virtual BOOL takeBack(int nStep=1);
	virtual BOOL thinkPlayChess(CPoint &);// ¿ÕµÄÊµÏÖ
protected:

};

#endif // !defined(AFX_HUMANPLAYER_H__E2DC1CB7_7503_4CD1_B7E7_2A08D6DD146E__INCLUDED_)
