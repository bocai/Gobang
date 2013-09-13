// ComputerHarder.cpp: implementation of the CComputerHarder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gobang.h"
#include "computerPlayer.h"
#include "ComputerHarder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComputerHarder::CComputerHarder(chessType (*pChessBoard)[CHESS_BOARD_SIZE])
{
	m_chessBoard = pChessBoard;
}

CComputerHarder::~CComputerHarder()
{
	
}

//计算当前位置的得分
// int getScore(chessType m_chessBoard[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE], int x, int y, chessType Type);
// 





// 获得估分最大的点
CPoint CComputerHarder::getBestPos()
{
	iniValue();
	CPoint point;
	point.x = -1;
	point.y = -1;

	int maxComputer = 0, maxPlayer = 0, i, j;
	int x1, x2, y1, y2, pointx, pointy;

	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		for (j = 0; j < CHESS_BOARD_SIZE; j++)
		{
			if (m_chessBoard[i][j] == NOCHESS)//模拟落子
			{
				ComputerScore[i][j] = getScore(i, j, myChessType);//为PC打分
				PeopleScore[i][j] = getScore(i, j, opponentChessType);//为玩家打分

	
			}
		}
	}
	

    for (i = 0; i < CHESS_BOARD_SIZE; i++)
    {
		for (j = 0; j < CHESS_BOARD_SIZE; j++)
        {

			if (ComputerScore[i][j] > maxComputer)
			{
				maxComputer = ComputerScore[i][j];
				x1 = i;
                y1 = j;
			}
			
			//选出PeopleScore中最大值
			if (PeopleScore[i][j] > maxPlayer)
			{
				maxPlayer = PeopleScore[i][j];
				x2 = i;
				y2 = j;
			}		

			if (ComputerScore[i][j] == maxComputer)
			{
				if ((rand()%((10)-(0))+(0)%2) == 0)
				{ 
					maxComputer = ComputerScore[i][j];
					x1 = i;
                    y1 = j;
				}
            }
	
			if (PeopleScore[i][j] == maxPlayer)
			{
				if ((rand()%((10)-(0))+(0)%2) == 1)
				{
					maxPlayer = PeopleScore[i][j];
					x2 = i;
					y2 = j;
				}
			}
		}
	}


	if(maxComputer>=maxPlayer)
	{
		pointx=x1;
		pointy=y1;
	}
	else if(maxComputer<maxPlayer)
	{
		pointx=x2;
		pointy=y2;
	}

	point.x = pointx;
	point.y = pointy;

	return point;
}

//横向
int CComputerHarder::HorizontalsimpleScore(int x, int y, chessType Type, BoardType type)
{
    int count = 1;
    int t1 = y + 1, t2 = y - 1;
    //右
	for (int j = y + 1 ; j < y + 5; j++)
    {
		if (j >= CHESS_BOARD_SIZE)
        {
			type = DEAD;
            break;
        }
        if (m_chessBoard[x][j] == Type)
        {
			count++;
            if (count >= 5) 
				return count;
        }
        else
        {
            if(m_chessBoard[x][j] == NOCHESS) 
				type=ALIVE;
			else 
				type=DEAD;
            t1 = j;//记录遇到空格时的位置
            break;
        }
    }
	//左
    for (j = y - 1; j > y - 5; j--)
    {
        if (j < 0)
        {
			if (type == DEAD && count < 5)
				return 0;
			type = DEAD;
			break;
        }
        if (m_chessBoard[x][j] == Type)
        {
            count++;
            if (count >= 5) 
				return count;
        }
        else
        {
            if (type == DEAD)
            {
                if (count < 5 && m_chessBoard[x][j] != NOCHESS) 
					return 0;
            }
            else
            {
                 if(m_chessBoard[x][j] == NOCHESS)
					type=ALIVE;
				 else
					type=DEAD;
                 t2 = j;//记录遇到空格时的位置
                 //两头都是alive时，判断能否延伸
                 if (type == ALIVE)
                 {
                     int count1 = count, count2 = count;
                     bool isalive1 = false, isalive2 = false;
                     for (int t = t1 + 1; t < t1 + 5; t++)
                     {
						if (t >= CHESS_BOARD_SIZE) 
							break;
                        if (m_chessBoard[x][t] == Type) 
							count1++;
                        else
						{
                            if(m_chessBoard[x][t] == NOCHESS) 
								isalive1 = true;
							else
								isalive1 = false;
                            break;
                        }
                     }
                     for (t = t2 - 1; t > t2 - 5; t--)
                     {
                        if (t < 0) 
							break;
                        if (m_chessBoard[x][t] == Type) 
							count2++;
						else
                        {
							if(m_chessBoard[x][t] == NOCHESS)
								isalive2 = true; 
							else 
								isalive2 = false;
                            break;
                        }
                     }
                     //两头都是空，直接跳出
                     if (count1 == count && count2 == count)
						break;
                     if (count1 == count2)
                     {
						count = count1;
						if(isalive1 == true && isalive2 == true)
							type = HALF_ALIVE;
						else
							type = DEAD;
                     }
                     else
                     {
						if(count1 > count2)
							count = count1;
						else
							count = count2;
                        if (count >= 5) 
							return 0;
                        if (count1 > count2)
						{
							if(isalive1=true)
								type = HALF_ALIVE;
							else 
								type = DEAD;
						}	
                        else
						{
							if(isalive2=true)
								type = HALF_ALIVE;
							else 
								type = DEAD;
                        
						}
					 }
				}
			}
		break;
		}
    }
	return count;
}
//竖
int CComputerHarder::VerticalsimpleScore(int x, int y, chessType Type, BoardType type)
{
    int count = 1;
    int t1 = x + 1, t2 = x - 1;
    //上
	for (int i = x + 1; i < x+ 5; i++)
    {
		if (i >= CHESS_BOARD_SIZE)
        {
			type = DEAD;
            break;
        }
        if (m_chessBoard[i][y] == Type)
        {
			count++;
            if (count >= 5) return count;
        }
        else
        {
            if(m_chessBoard[i][y] == NOCHESS) 
				type=ALIVE;
			else 
				type=DEAD;
            t1 = i;//记录遇到空格时的位置
            break;
        }
    }
	//下
    for (i = x - 1; i > x - 5; i--)
    {
        if (i < 0)
        {
			if (type == DEAD && count < 5)
				return 0;
            type = DEAD;
            break;
        }
        if (m_chessBoard[i][y] == Type)
        {
            count++;
            if (count >= 5) 
				return count;
        }
        else
        {
            if (type == DEAD)
            {
                if (count < 5 && m_chessBoard[i][y] != NOCHESS) 
					return 0;
            }
            else
            {
                 if(m_chessBoard[i][y] == NOCHESS)
					type=ALIVE;
				 else
					type=DEAD;
                 t2 = i;//记录遇到空格时的位置
                 //两头都是alive时，判断能否延伸
                 if (type == ALIVE)
                 {
                     int count1 = count, count2 = count;
                     bool isalive1 = false, isalive2 = false;
                     for (int t = t1 + 1; t < t1 + 5; t++)
                     {
						if (t >= CHESS_BOARD_SIZE) 
							break;
                        if (m_chessBoard[t][y] == Type) 
							count1++;
                        else
						{
                            if(m_chessBoard[t][y] == 0) 
								isalive1 = true;
							else
								isalive1 = false;
                            break;
                        }
                     }
                     for (t = t2 - 1; t > t2 - 5; t--)
                     {
                        if (t < 0) 
							break;
                        if (m_chessBoard[t][y] == Type) 
							count2++;
						else
                        {
							if(m_chessBoard[t][y] == NOCHESS)
								isalive2 = true; 
							else 
								isalive2 = false;
                            break;
                        }
                     }
                     //两头都是空，直接跳出
                     if (count1 == count && count2 == count)
						break;
                     if (count1 == count2)
                     {
						count = count1;
						if(isalive1 == true && isalive2 == true)
							type = HALF_ALIVE;
						else
							type = DEAD;
                     }
                     else
                     {
						if(count1 > count2)
							count = count1;
						else
							count = count2;
                        if (count >= 5) 
							return 0;
                        if (count1 > count2)
						{
							if(isalive1=true)
								type = HALF_ALIVE;
							else 
								type = DEAD;
						}	
                        else
						{
							if(isalive2=true)
								type = HALF_ALIVE;
							else 
								type = DEAD;
                        
						}
					 }
				}
			}
		break;
		}
    }
	return count;
}

//左斜
int CComputerHarder::getLeftInclinesimpleScore(int x, int y, chessType Type, BoardType type)
{
    int count = 1;
    int t1x = x + 1, t1y = y + 1, t2x = x - 1, t2y = y - 1;
    //右下
	for (int i = x + 1,j = y + 1; i < x+ 5; i++, j++)
    {
		if (i >= CHESS_BOARD_SIZE||j >= CHESS_BOARD_SIZE)
        {
			type = DEAD;
            break;
        }
        if (m_chessBoard[i][j] == Type)
        {
			count++;
            if (count >= 5) return count;
        }
        else
        {
            if(m_chessBoard[i][j] == NOCHESS) 
				type=ALIVE;
			else 
				type=DEAD;
            t1x = i;
			t1y = j;//记录遇到空格时的位置
            break;
        }
    }
	//左上
    for (i = x - 1,j = y - 1; i > x - 5; i--, j--)
    {
        if (i < 0 || j < 0)
        {
			if (type == DEAD && count < 5)
				return 0;
            type = DEAD;
            break;
        }
        if (m_chessBoard[i][j] == Type)
        {
            count++;
            if (count >= 5) 
				return count;
        }
        else
        {
            if (type == DEAD)
            {
                if (count < 5 && m_chessBoard[i][j] != NOCHESS) 
					return 0;
            }
            else
            {
                 if(m_chessBoard[i][j] == NOCHESS)
					type=ALIVE;
				 else
					type=DEAD;
                 t2x = i;
				 t2y = j;//记录遇到空格时的位置
                 //两头都是alive时，判断能否延伸
                 if (type == ALIVE)
                 {
                     int count1 = count, count2 = count;
                     bool isalive1 = false, isalive2 = false;
                     for (int t = t1x + 1, d =t1y+1; t < t1x + 5; t++, d++)
                     {
						if (t >= CHESS_BOARD_SIZE || d >= CHESS_BOARD_SIZE) 
							break;
                        if (m_chessBoard[t][d] == Type) 
							count1++;
                        else
						{
                            if(m_chessBoard[t][d] == NOCHESS) 
								isalive1 = true;
							else
								isalive1 = false;
                            break;
                        }
                     }
                     for (t = t2x - 1, d = t2y - 1; t > t2x - 5; t--, d--)
                     {
                        if (t < 0 || d < 0) 
							break;
                        if (m_chessBoard[t][d] == Type) 
							count2++;
						else
                        {
							if(m_chessBoard[t][d] == NOCHESS)
								isalive2 = true; 
							else 
								isalive2 = false;
                            break;
                        }
                     }
                     //两头都是空，直接跳出
                     if (count1 == count && count2 == count)
						break;
                     if (count1 == count2)
                     {
						count = count1;
						if(isalive1 == true && isalive2 == true)
							type = HALF_ALIVE;
						else
							type = DEAD;
                     }
                     else
                     {
						if(count1 > count2)
							count = count1;
						else
							count = count2;
                        if (count >= 5) 
							return 0;
                        if (count1 > count2)
						{
							if(isalive1=true)
								type = HALF_ALIVE;
							else 
								type = DEAD;
						}	
                        else
						{
							if(isalive2=true)
								type = HALF_ALIVE;
							else 
								type = DEAD;
                        
						}
					}
				 }
			}
			break;
		}
    }
	return count;
}
//右斜
int CComputerHarder::getRightInclinesimpleScore(int x, int y, chessType Type, BoardType type)
{
    int count = 1;
    int t1x = x + 1, t1y = y - 1, t2x = x - 1, t2y = y + 1;
    //左下
	for (int i = x + 1,j = y - 1; i < x+ 5; i++, j--)
    {
		if (i >= CHESS_BOARD_SIZE||j < 0)
        {
			type = DEAD;
            break;
        }
        if (m_chessBoard[i][j] == Type)
        {
			count++;
            if (count >= 5) return count;
        }
        else
        {
            if(m_chessBoard[i][j] == NOCHESS) 
				type=ALIVE;
			else 
				type=DEAD;
            t1x = i;
			t1y = j;//记录遇到空格时的位置
            break;
        }
    }
	//右上
    for (i = x - 1,j = y + 1; i > x - 5; i--, j++)
    {
        if (i < 0 || j >= CHESS_BOARD_SIZE)
        {
			if (type == DEAD && count < 5)
				return 0;
            type = DEAD;
            break;
        }
        if (m_chessBoard[i][j] == Type)
        {
            count++;
            if (count >= 5) 
				return count;
        }
        else
        {
            if (type == DEAD)
            {
                if (count < 5 && m_chessBoard[i][j] != NOCHESS) 
					return 0;
            }
            else
            {
                 if(m_chessBoard[i][j] == NOCHESS)
					type=ALIVE;
				 else
					type=DEAD;
                 t2x = i;
				 t2y = j;//记录遇到空格时的位置
                 //两头都是alive时，判断能否延伸
                 if (type == ALIVE)
                 {
                     int count1 = count, count2 = count;
                     bool isalive1 = false, isalive2 = false;
                     for (int t = t1x + 1, d =t1y - 1; t < t1x + 5; t++, d--)
                     {
						if (t >= CHESS_BOARD_SIZE || d < 0) 
							break;
                        if (m_chessBoard[t][d] == Type) 
							count1++;
                        else
						{
                            if(m_chessBoard[t][d] == NOCHESS) 
								isalive1 = true;
							else
								isalive1 = false;
                            break;
                        }
                     }
                     for (t = t2x - 1, d = t2y + 1; t > t2x - 5; t--, d++)
                     {
                        if (t < 0 || d >= CHESS_BOARD_SIZE) 
							break;
                        if (m_chessBoard[t][d] == Type) 
							count2++;
						else
                        {
							if(m_chessBoard[t][d] == 0)
								isalive2 = true; 
							else 
								isalive2 = false;
                            break;
                        }
                     }
                     //两头都是空，直接跳出
                     if (count1 == count && count2 == count)
						break;
                     if (count1 == count2)
                     {
						count = count1;
						if(isalive1 == true && isalive2 == true)
							type = HALF_ALIVE;
						else
							type = DEAD;
                     }
                     else
                     {
						if(count1 > count2)
							count = count1;
						else
							count = count2;
                        if (count >= 5) 
							return 0;
                        if (count1 > count2)
						{
							if(isalive1=true)
								type = HALF_ALIVE;
							else 
								type = DEAD;
						}	
                        else
						{
							if(isalive2=true)
								type = HALF_ALIVE;
							else 
								type = DEAD;
                        
						}
					}
				 }
			}
			break;
		}
    }
	return count;
}

BOOL CComputerHarder::thinkPlayChess(CPoint &point)
{
	CPoint p =	getBestPos();
	
	if (p.x < 0 || p.x >= CHESS_BOARD_SIZE || p.y < 0 || p.y >= CHESS_BOARD_SIZE)
	{
		return FALSE;
	}
	point.x = p.x;
	point.y = p.y;
	
	return TRUE;
}
