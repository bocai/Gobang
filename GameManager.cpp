//GameManager.cpp: implementation of the CGameManager class.

////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gobang.h"
#include "GameManager.h"
#include  "ComputerHarder.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////
//Construction/Destruction
////////////////////////////////////////////////////////////////////

CGameManager::CGameManager()
{
	isStart = FALSE;
	pBlackPlayer = NULL;
	pWhitePlayer = NULL;
	pWinnerPlayer = NULL;
	winnerChessCount = 0;
	pSuggest = new CComputerHarder(gobangChess.getChessBoard());
}

CGameManager::~CGameManager()
{
	whoFirst = NOCHESS;
	if (pSuggest)
	{
		delete pSuggest;
	}
	
}

BOOL CGameManager::stopGame()
{
	isStart = FALSE;
	return TRUE;
}

BOOL CGameManager::isGameStart()
{
	return isStart;
}

BOOL CGameManager::setWhoIsRun(chessType turn) 
{
	if (NOCHESS == turn || BLACK == turn || WHITE == turn)
	{
		m_turn = turn;
		return TRUE;
	}
	
	return FALSE;
}

chessType CGameManager::whoIsRuning() const
{
	return m_turn;
}

BOOL CGameManager::setGamePlayer(CGamePlayer *blackPlayer, CGamePlayer *whitePlayer)
{
	if (NULL ==blackPlayer || NULL == whitePlayer || blackPlayer == whitePlayer )
	{
		return FALSE;
	}
	chessType bType = blackPlayer->getMyChessType();
	chessType wType = whitePlayer->getMyChessType();

	if (bType == wType)
	{
		return FALSE;
	}
	pBlackPlayer = blackPlayer;
	pWhitePlayer = whitePlayer;
	pWhitePlayer->setOpponentChessType(bType);
	pBlackPlayer->setOpponentChessType(wType);

	return TRUE;
}

BOOL CGameManager::startGame(chessType StartTurn)
{
	if (isGameStart() || NULL == pBlackPlayer || NULL == pWhitePlayer || pWhitePlayer == pBlackPlayer)
	{
		AfxMessageBox("�Բ���,��Ϸ��ʼ�����󣡣�");
		return FALSE;
	}

	if ( !(NOCHESS == StartTurn || BLACK == StartTurn || WHITE == StartTurn) )
	{
		return FALSE;
	}

	gobangChess.cleanBoard(NOCHESS);
	VecChessRecord.clear();
	pBlackPlayer->cleanRecordStack();
	pWhitePlayer->cleanRecordStack();
	isStart = TRUE;
	m_turn = StartTurn;

	return TRUE;
}

GobangChess * CGameManager::getGobangChess()
{
	return  &gobangChess;
}

BOOL CGameManager::judgeVictory(int chess_x, int chess_y, chessType cType)
{
	int countH, countV, countR, countL;
	int maxCount = 0;
	if ( ( countH = gobangChess.getHorizontalChessCount(chess_x, chess_y, cType, win2point) ) >= 5 ) {
			maxCount = countH;
	}
	else if (( countV = gobangChess.getVerticalChessCount(chess_x, chess_y, cType, win2point) ) >= 5)
	{
			maxCount = countV;
	}
	else if (( countR = gobangChess.getRightInclineChessCount(chess_x, chess_y, cType, win2point) ) >= 5 ) {
		maxCount = countR;
		
	} 
	else if (( countL= gobangChess.getLeftInclineChessCount(chess_x, chess_y, cType, win2point) ) >= 5 )
	{
		maxCount = countL;
		
	}else {
		return FALSE;
	}
	
	winnerChessCount = maxCount;
	
	if (pBlackPlayer->getMyChessType() == cType)
	{
		pWinnerPlayer = pBlackPlayer;
	} 
	else if (pWhitePlayer->getMyChessType() == cType)
	{
		pWinnerPlayer = pWhitePlayer;
	}
	
	return TRUE;
}

GameMode CGameManager::getGameMode()
{
	return gameMode;
}

BOOL CGameManager::setGameMode(GameMode mode)
{
	gameMode = mode;
	return TRUE;
}


BOOL CGameManager::setBoardPos(const CPoint &point, const chessType type)
{
	return setBoardPos(point.x, point.y, type);
}

BOOL CGameManager::getBoardPos(const CPoint &point, chessType &cType)
{
	return getBoardPos(point.x, point.y, cType);
}

BOOL CGameManager::setBoardPos(const int x, const int y, const chessType &cType)
{
	if (NOCHESS == cType)
	{
		return FALSE;
	}

	CPoint point(x,y);

	VecChessRecord.push_back(point);


	if (cType == BLACK)
	{
		pBlackPlayer->pushRecord(point);
	} else if (WHITE == cType)
	{
		pWhitePlayer->pushRecord(point);
	}
	return gobangChess.setBoardPos(x, y, cType);
}

BOOL CGameManager::getBoardPos(const int x, const int y, chessType &cType)
{
// 	int row = y;
// 	int col = x;
	return gobangChess.getBoardPos(x, y, cType);
}

chessType (* CGameManager::getChessBoard(CGamePlayer *pGameplayer)) [CHESS_BOARD_SIZE]
{
	return	gobangChess.getChessBoard();
}

// ��һ������ָ��Ҫ�������ң��ڶ�������ָ��Ҫ������ҵĶ��֣� ����������ָ������
BOOL CGameManager::takeBack(CGamePlayer *pToTackBack, CGamePlayer *pAccept, int nStep=1)
{
	if ( //(gameMode != COMPUTER_MODE && whoIsRuning() != pAccept->getMyChessType() )||
		nStep <=0 || pToTackBack->getTakeBackCount() >= TAKE_BACK_TOTAL_COUNT
		|| VecChessRecord.size() <= 0 || VecChessRecord.empty())
	{
		return FALSE;
	
	}
	vector <CPoint> vecCpoint;
	CPoint point;
	// ��ǰ�ֵ��������������,˵��Ҫ������������(�ɶ�)
	if (m_turn == pToTackBack->getMyChessType())
	{
		for(int i = nStep; i > 0 && !VecChessRecord.empty(); i--)
		{
			point = *(VecChessRecord.end()-1);
			gobangChess.setBoardPos(point, NOCHESS);
			VecChessRecord.pop_back(); // ɾ��Manager�еļ�¼
			if (!VecChessRecord.empty())
			{	
				point = *(VecChessRecord.end()-1);
				gobangChess.setBoardPos(point, NOCHESS);
				VecChessRecord.pop_back();
			}
		

			pToTackBack->takeBack(nStep, &vecCpoint);// ��ջ
			pAccept->takeBack(nStep, &vecCpoint);
		}
		
	}
	else { // �Ѿ��ֵ��Է���˵������һ���ӣ����Ϊ�ಽ�����Լ��ȶԷ��೷��һ��)
		if (pToTackBack->takeBack(nStep, &vecCpoint))
		{
			if (vecCpoint.size() <= 0)
			{
				return FALSE;
			}
			vector <CPoint>::iterator itr;
			
			int i = vecCpoint.size() - 1;
			if (i >= 0) // �೷��һ��
			{
				point = vecCpoint[i];
				gobangChess.setBoardPos(point, NOCHESS);
				VecChessRecord.pop_back(); // ɾ��Manager�еļ�¼
			}
			i--;
			for (; i >= 0 ; i--)
			{
				point = vecCpoint[i];
				gobangChess.setBoardPos(point, NOCHESS);
				VecChessRecord.pop_back();
				
				itr = VecChessRecord.end() - 1;
				gobangChess.setBoardPos(*itr, NOCHESS);
				VecChessRecord.pop_back();
			}
		}
	}
//	setWhoIsRun(NOCHESS);

	vecCpoint.clear();	
	setWhoIsRun(pToTackBack->getMyChessType());
	return TRUE;
}

vector  <CPoint> *CGameManager::getVecRecord()
{
	return &VecChessRecord;
}

chessType CGameManager::getWhoFirst()
{
	return whoFirst;
}

BOOL CGameManager::setWhoFirst(chessType cType)
{
	whoFirst = cType;
	m_turn = cType;
	return TRUE;
}

BOOL CGameManager::cleanRecord()
{
	if (pWhitePlayer)
	{
		pWhitePlayer->cleanRecordStack();
	}
	if (pBlackPlayer)
	{
		pBlackPlayer->cleanRecordStack();
	}
//	VecChessRecord.empty();
	VecChessRecord.clear();
	
	pWinnerPlayer = NULL;
	return TRUE;
}

CGamePlayer * CGameManager::getWinner()
{
	return pWinnerPlayer;
}

CPoint CGameManager::getOneEmptyPosByRand()
{
	chessType cType;
	CPoint point(-1, -1);
	for (;;)
	{
		int x = rand() % CHESS_BOARD_SIZE;
		int y = rand() % CHESS_BOARD_SIZE;
		if (gobangChess.getBoardPos(x, y, cType))
		{
			if (NOCHESS == cType)
			{
				point.x = x;
				point.y = y;
				break;
			}
		}
	}

	return point;
}

BOOL CGameManager::setWinner(CGamePlayer *player)
{
	if (NULL == player)
	{
		winnerChessCount = 0;
	}
	pWinnerPlayer = player;
	return TRUE;
}

CPoint * CGameManager::getWin2points()
{
	if (!isStart)
	{
		return win2point;
	}

	return NULL;
}

CPoint CGameManager::getSuggestPoint(chessType selfChess, chessType rivalChess)
{
	CPoint point;
	pSuggest->setMyChessType(selfChess);
	pSuggest->setOpponentChessType(rivalChess);
	pSuggest->thinkPlayChess(point);

	return point;
}

int CGameManager::getWinnerChessCount()
{
	return winnerChessCount;
}
