// ComputerSimple.cpp: implementation of the CComputerSimple class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gobang.h"
#include "ComputerSimple.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComputerSimple::CComputerSimple()
{

}

CComputerSimple::~CComputerSimple()
{

}
CPoint CComputerSimple::getBestPos()
{
// 	CPoint point;
// 	return 	Computer_play(myChessType, point);



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
				
				if (ComputerScore[i][j] > maxComputer)
				{
					maxComputer = ComputerScore[i][j];
				}
				
				//选出PeopleScore中最大值
				if (PeopleScore[i][j] > maxPlayer)
				{
					maxPlayer = PeopleScore[i][j];
					
				}		
			}
		}
	}
	
	
    for (i = 0; i < CHESS_BOARD_SIZE; i++)
    {
		for (j = 0; j < CHESS_BOARD_SIZE; j++)
        {
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



BOOL CComputerSimple::simpleComputerPlay(CPoint *point)
{
//	CcomputerPlayer::BzeroComputerScoreTb();
	
	return TRUE;
}

BOOL CComputerSimple::simpleComputerPlay(CPoint &point)
{
	
	return TRUE;
}

BOOL CComputerSimple::thinkPlayChess(CPoint &point)
{

	if ( NULL == m_chessBoard)
	{
		return FALSE;
	}

// 	
// 	point.x = p.x;
// 	point.y = p.y;

	return TRUE;
	
}

/* 计算共有多少种获胜情况 */
void CComputerSimple::install_game()
{
    int i, k=0;
    for (i = 1; i <= (CHESS_BOARD_SIZE - 4 ); i++)
    {
		k=k+i;
    } 
	for(i = (CHESS_BOARD_SIZE - 4) - 1; i>0; i--)
	{	
		k=k+i;
	}
	WIN_COUNT = (CHESS_BOARD_SIZE - 4) * CHESS_BOARD_SIZE *2+k*2;
}

void CComputerSimple::install_list()
{
    int i, j, k, m;	
    /* 初始化获胜情况表 */
    for (k = 0;k < WIN_COUNT; k++)
    {	
		WinListP[k].last = 1;
		WinListC[k].last = 1;
		for(m = 0;m < 5; m++)
		{
			WinListP[k].z[m] = 0;
			WinListC[k].z[m] = 0;
		}
	}
	//横向获胜情况	
	k=0;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		for (j = 0; j < (CHESS_BOARD_SIZE - 4); j++)
		{	
			for(m = 0; m < 5; m++)
			{
				WinListP[k].x[m] = j;
				WinListP[k].y[m] = i + m;
				WinListC[k].x[m] = j;
				WinListC[k].y[m] = i + m;
			}
			k++;
		}
	}
	//竖向获胜情况
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		for (j = 0; j < (CHESS_BOARD_SIZE - 4); j++)
		{	
			for(m = 0; m < 5; m++)
			{
				WinListP[k].x[m] = i + m;
				WinListP[k].y[m] = j ;	
				WinListC[k].x[m] = i + m;
				WinListC[k].y[m] = j ;
			}
			k++;
		}
	}
	//左斜获胜情况
	for (i = 0; i < (CHESS_BOARD_SIZE - 4); i++)
	{
		for	(j = 0; j < (CHESS_BOARD_SIZE- 4); j++)
		{
			for (m = 0; m < 5; m++)
			{
				WinListP[k].x[m] = i + m;
				WinListP[k].y[m] = j + m;
				WinListC[k].x[m] = i + m;
				WinListC[k].y[m] = j + m;
			}
			k++;
		}
	}
	//右斜获胜情况
	for (i = 0; i < (CHESS_BOARD_SIZE - 4); i++)
	{
		for (j = (CHESS_BOARD_SIZE - 1); j > 3; j--)
		{
			for (m = 0; m < 5; m++)
			{
				WinListP[k].x[m] = i + m;
				WinListP[k].y[m] = j - m;
				WinListC[k].x[m] = i + m;
				WinListC[k].y[m] = j - m;
			}
			k++;
		}
	}
}

//重置获胜情况,电脑获胜表发现人落子处即标为失效,人获胜表记录落子处
void CComputerSimple::rest_win1(int x,int y)
{
	int i, j;
	for (i = 0;i < WIN_COUNT; i++)
	{
		for(j = 0;j < 5; j++)
		{
			if(WinListC[i].x[j] == x&&WinListC[i].y[j] == y)
			{
				WinListC[i].last = 0;
				WinListP[i].z[j] = 1;
				break;
			}
		}
    }
}
//电脑下棋后更新获胜表,记录落子处,人获胜表标为失效
void CComputerSimple::rest_win2(int x,int y)
{
	int i, j;
	for (i = 0;i < WIN_COUNT; i++)
	{
		for(j = 0;j < 5; j++)
		{
			if(WinListP[i].x[j] == x&&WinListP[i].y[j] == y)
			{
				WinListP[i].last = 0;
				WinListC[i].z[j] = 1;
				break;
			}
		}
    }
}

//根据获胜表给得分表评分
void CComputerSimple::do_score()
{
	int i, j, k, m;
	//初始化
	for (i = 0; i < CHESS_BOARD_SIZE ; i++)
	{
		for (j = 0; j < CHESS_BOARD_SIZE; j++)
		{
			PeopleScore[i][j] = 0;                /* 初始化人，机器评分表    */
			ComputerScore[i][j] = 0;
			
			if (m_chessBoard[i][j] == NOCHESS)        /* 为空格                */
			{
				for (k = 0; k < WIN_COUNT; k++)
				{
					if (WinListC[k].last == 1)    /* 机器方各空格评分    */
					{
						for (m = 0; m < 5; m++)
						{
							if (WinListC[k].x[m] == i && WinListC[k].y[m] == j)
							{
								ComputerScore[i][j]++;
							}
						}
					}   
					if (WinListP[k].last == 1)    /* 人方各空格评分    */
					{
						for (m = 0; m < 5; m++)
						{
							if (WinListP[k].x[m] == i && WinListP[k].y[m] == j)
							{
								PeopleScore[i][j]++;
							}
						}
					}
				}
			}
		}
	}
}

//电脑下棋
BOOL CComputerSimple::Computer_play(chessType type, CPoint &point)
{
	 //人,电脑
	int i, j;
	int score_c=0,score_p=0;
    int people_x, people_y, computer_x, computer_y,computer_x1, computer_y1;
	people_x = people_y = computer_x = computer_y = computer_x1 = computer_y1 = -1;
	/* 常规算法 */
    for (i = 0; i < WIN_COUNT; i++)
    {
		if (WinListC[i].last == 1 )			//电脑
		{
			for (j = 0; j < 5; j++)
			{
				if (WinListC[i].z[j] == 0)
				{
					ComputerScore[WinListC[i].x[j]][WinListC[i].y[j]] += 1;
					PeopleScore[WinListC[i].x[j]][WinListC[i].y[j]] -= 1;
				}
			}
		}
		if (WinListP[i].last == 1 )			//人
		{
			for (j = 0; j < 5; j++)
			{
				if (WinListP[i].z[j] == 0)
				{
					PeopleScore[WinListP[i].x[j]][WinListP[i].y[j]] += 1; 
					ComputerScore[WinListC[i].x[j]][WinListC[i].y[j]] -= 1;
				}
			}
		}
	}
	/* 加强算法，防止3，4连子时电脑不能识别 */
    for (i = 0; i < WIN_COUNT; i++)
    {
		int computer_count=0;
		if (WinListC[i].last == 1)		//电脑的连子
		{	
			for(j = 0; j < 5; j++)
			{
				if(WinListC[i].z[j] == 1)
					computer_count++;
			}
			switch(computer_count)
			{
			case 3:                 //3连子得分表空位加20分
				for(j = 0;j < 5; j++)
				{
					if(WinListC[i].z[j] == 0)
						ComputerScore[WinListC[i].x[j]][WinListC[i].y[j]] += 20;			
				}
				break;
			case 4:                //4连子得分表空位加30分
				for(j = 0;j < 5; j++)
				{
					if(WinListC[i].z[j] == 0)
						ComputerScore[WinListC[i].x[j]][WinListC[i].y[j]] += 30;	
				}
				break;
			}
		}
		int people_count=0;
		if (WinListC[i].last == 0)		//人的连子,加分多,使电脑重防御
		{
			for(j = 0; j < 5; j++)
			{
				if(WinListP[i].z[j] == 1)
					people_count++;
			}
			switch(people_count)
			{
			case 3:                 //3连子得分表空位加25分
				for(j = 0;j < 5; j++)
				{
					if(WinListP[i].z[j] == 0)
					PeopleScore[WinListP[i].x[j]][WinListP[i].y[j]] += 25;		
				}
				break;
			case 4:                //4连子得分表空位加35分
				for(j = 0;j < 5; j++)
				{
					if(WinListP[i].z[j] == 0)
						PeopleScore[WinListP[i].x[j]][WinListP[i].y[j]] += 35;	
				}
				break;
			}
		}
	}
	
	//比较得分
	for(i = 0;i < CHESS_BOARD_SIZE; i++)     
	{
		for(j = 0;j < CHESS_BOARD_SIZE; j++)
		{
			if((ComputerScore[i][j]+PeopleScore[i][j]) > score_c&&m_chessBoard[i][j] == NOCHESS)     //电脑
			{
				score_c=ComputerScore[i][j]+PeopleScore[i][j];
				computer_x=i;
				computer_y=j;
			}
		}
	}

// 	if(score_c > score_p)     //比较得分表,落子
// 	{
// 		computer_x=computer_x1;
// 		computer_y=computer_y1;
// 		m_chessBoard[computer_x][computer_y] = type;
// 	}
// 	else
// 	{
// 		computer_x=people_x;
// 		computer_y=people_y;
// 		m_chessBoard[computer_x][computer_y] = type;
// 	}
	if (computer_x < 0 || computer_y < 0)
	{
		return FALSE;
	}

	point.x = computer_x;
	point.y = computer_y;
	return TRUE;
}
	
	//玩家下子
	// void CComputerSimple::People_play()
	// {
	// 
	// }

	//开始游戏
// 	void CComputerSimple::play_game(chessType type)
// 	{
// 		int play_x,play_y;
// 		chessType typePeople ,typeComputer;   //人,电脑
// 	
// 		if(First == 0)       //电脑先,设点在棋盘中央
// 		{
// 			play_x=play_y=7;
// 			m_chessBoard[play_x][play_y]=typeComputer;
// 			rest_win2(play_x,play_y);     //重置
// 			//显示棋子
// 			First=1;
// 		}
// 		if (First == 1)      //人
// 		{
// 			//输入棋子坐标
// 			m_chessBoard[play_x][play_y]=typePeople;
// 			rest_win1(play_x,play_y);     //重置
// 			//显示棋子
// 			First=0;
// 		}
// 		while(1)
// 		{
// 			if(First == 0)
// 			{
// 				Computer_play(type);
// 				//显示棋子
// 				First=1;
// 			}
// 			if(First == 1)
// 			{
// 				People_play();
// 				//显示棋子
// 				First=0;
// 			}
// 		}
// 		
// 	}

// 悔棋
// BOOL CComputerSimple::takeBack(int step)
// {
// 
// 	return FALSE; // 电脑不能悔棋
// }






// 落子点水平方向(横)上的评分
int CComputerSimple::HorizontalsimpleScore(int x, int y, chessType type) const
{
	int score = 0;

	return score;

}

// 落子点垂直方向上(竖)的评分
int CComputerSimple::VerticalsimpleScore(int x, int y, chessType type) const
{
	int score = 0;
	
	return score;

}

// 向左倾斜方向(捺)上的评分
int CComputerSimple::getLeftInclinesimpleScore(int x, int y, chessType type) const
{
	int score = 0;
	
	return score;

}

// 向右倾斜方向（撇)上的评分
int CComputerSimple::getRightInclinesimpleScore(int x, int y, chessType type) const
{
	int score = 0;
	
	return score;

}