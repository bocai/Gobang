// HumanPlayer.cpp: implementation of the CHumanPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gobang.h"
#include "HumanPlayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHumanPlayer::CHumanPlayer()
{
	m_chessBoard = NULL;
}

CHumanPlayer::CHumanPlayer(chessType (*pChessBoard)[CHESS_BOARD_SIZE])
{
	m_chessBoard = pChessBoard;
}

CHumanPlayer::~CHumanPlayer()
{

}
// 
// BOOL CHumanPlayer::takeBack(int nStep)
// {
// 	return TRUE;
// }

BOOL CHumanPlayer::thinkPlayChess(CPoint &point)
{
	
	return TRUE;
}