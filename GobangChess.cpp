// GobangChess.cpp: implementation of the GobangChess class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Gobang.h"
#include "GobangChess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GobangChess::GobangChess()
{
	cleanBoard(NOCHESS);
}

GobangChess::~GobangChess()
{

}


BOOL GobangChess::cleanBoard(const chessType type)
{
	return memset(m_chessBoard, NOCHESS, sizeof(m_chessBoard)) != NULL;
}

BOOL GobangChess::setBoardPos(const CPoint &point, const chessType cType)
{
	
	return setBoardPos(point.x, point.y, cType);
}

BOOL GobangChess::getBoardPos(const CPoint &point, chessType &cType)
{
	return getBoardPos(point.x, point.y, cType);
}

BOOL GobangChess::setBoardPos(const int x, const int y, const chessType &type)
{
	
	if (x < 0 || y < 0 || x >= CHESS_BOARD_SIZE 
		|| y >= CHESS_BOARD_SIZE)
	{
		return FALSE;
	}
	
	if (type == NOCHESS || type == WHITE || type == BLACK)
	{
		m_chessBoard[x][y] = type;
		return TRUE;
	}
	
	return FALSE;
}

BOOL GobangChess::getBoardPos(const int x, const int y, chessType &cType)
{
	if (x < 0 || y < 0 || x >= CHESS_BOARD_SIZE || y >= CHESS_BOARD_SIZE)
	{
		return FALSE;
	}
	cType = m_chessBoard[x][y];
	
	return TRUE;
}


// 注意：屏幕坐标刚好逆时针旋转90度即为二维数组的坐标
// 落子点(x, y)水平方向上(横)的连续棋子(type类型的)数 ,y轴(行)不变(和二维数组的行列相反）
int GobangChess::getHorizontalChessCount(int x, int y, chessType type, CPoint *point2)
{
	int count = 0;

	if (m_chessBoard[x][y] == type)
	{
		count++;
		point2[0].x = x;
		point2[0].y = y;
	}
	point2[0].x = x;
	point2[1].x = x;
	point2[1].y = y;

	int col = y;
	while( ++col < CHESS_BOARD_SIZE ) // 右半边
	{
		if(m_chessBoard[x][col] == type ) {
			count++;
			point2[0].y = col;
		}
		else {
	
			break;
		}
	}	

	col = y;
	while( --col >= 0 )  // 左半边
	{
		if(m_chessBoard[x][col] == type ) {
			count++;
			point2[1].y = col;
		}else {

			break;
		}
	
	}

	return count;
}

// 落子点(x, y)垂直方向上的连续棋子(type类型的)数 , x轴(列)不变
int GobangChess::getVerticalChessCount(int x, int y, chessType type, CPoint *point2) 
{
	int count = 0;
	
	if (m_chessBoard[x][y] == type)
	{
		count++;
		point2[0].x = x;
		point2[0].y = y;
	}
	point2[0].y = y;
	point2[1].x = x;
	point2[1].y = y;

	int row = x;
	while( ++row < CHESS_BOARD_SIZE ) // 下半部分
	{
		if(m_chessBoard[row][y] == type ) 
		{
			count++;
			point2[0].x = row;
		}
		else 
		{
			break;
		}
	}

	
	row = x;
	
	while( --row >= 0)  //上半部分
	{
		if(m_chessBoard[row][y] == type) 
		{
			count++;
			point2[1].x = row;
		}
		else
		{
			break;
		}
	}

	return count;
}

// 落子点(x, y)向左倾斜方向上\的连续棋子(type类型的)数
int GobangChess::getLeftInclineChessCount(int x, int y, chessType type, CPoint *point2) 
{
	int count = 0;
	int i, j;
	
	if (m_chessBoard[x][y] == type)
	{
		count++;
		point2[0].x = x;
		point2[0].y = y;
	}
	// 左上部
	for ( i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)
	{
		
		if (m_chessBoard[i][j] == type)
		{
			count++;
			point2[0].x = i;
			point2[0].y = j;
		}
		else {
			break;
		}
	}
	 
	for ( i = x + 1, j = y + 1; i < CHESS_BOARD_SIZE && j < CHESS_BOARD_SIZE; i++, j++)
	{
		
		if (m_chessBoard[i][j] == type)
		{
			count++;
			point2[1].x = i;
			point2[1].y = j;
		}
		else {
			break;
		}
	}

	return count;
}

// 落子点(x, y)向左倾斜方向上/的连续棋子(type类型的)数
int GobangChess::getRightInclineChessCount(int x, int y, chessType type, CPoint *point2)  
{
	int count = 0;
	int i, j;
	
	if (m_chessBoard[x][y] == type)
	{
		count++;
		point2[0].x = x;
		point2[0].y = y;
	}

	for ( i = x - 1, j = y + 1; i >= 0 && j < CHESS_BOARD_SIZE; i--, j++)
	{
		if (m_chessBoard[i][j] == type)
		{
			count++;
			point2[0].x = i;
			point2[0].y = j;
		}
		else {
			break;
		}
	}

	for ( i = x + 1, j = y - 1; i < CHESS_BOARD_SIZE && j >= 0; i++, j--)
	{
		
		if (m_chessBoard[i][j] == type)
		{
			count++;
			point2[1].x = i;
			point2[1].y = j;
		}
		else {
			break;
		}
	}

	return count;
}

void GobangChess::reset()
{
	cleanBoard(NOCHESS);
}

chessType (* GobangChess::getChessBoard()) [CHESS_BOARD_SIZE]
{
	return m_chessBoard;
}
