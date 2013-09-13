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


// ע�⣺��Ļ����պ���ʱ����ת90�ȼ�Ϊ��ά���������
// ���ӵ�(x, y)ˮƽ������(��)����������(type���͵�)�� ,y��(��)����(�Ͷ�ά����������෴��
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
	while( ++col < CHESS_BOARD_SIZE ) // �Ұ��
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
	while( --col >= 0 )  // ����
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

// ���ӵ�(x, y)��ֱ�����ϵ���������(type���͵�)�� , x��(��)����
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
	while( ++row < CHESS_BOARD_SIZE ) // �°벿��
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
	
	while( --row >= 0)  //�ϰ벿��
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

// ���ӵ�(x, y)������б������\����������(type���͵�)��
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
	// ���ϲ�
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

// ���ӵ�(x, y)������б������/����������(type���͵�)��
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
