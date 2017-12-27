#include "StdAfx.h"
#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////////////

#define IDI_CHECK_TABLE				1					//检查桌子
#define IDI_START_GAME				2									//开始定时器
#define IDI_OUT_CARD				3									//出牌定时器
#define IDI_OPERATE_CARD			4									//操作定时器

#define IDI_FENZHANG_DELAY			5									//海底分张间隔定时器

//构造函数
CTableFrameSink::CTableFrameSink()
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	m_wPlayerCount = GAME_PLAYER;

	//组件变量
	m_pITableFrame = NULL;
	m_pGameServiceOption = NULL;
	m_pGameServiceAttrib = NULL;	

	//游戏变量
	m_wSiceCount = 0;
	m_wBankerUser = INVALID_CHAIR;
	m_wLianZhuang = 1;
	m_wCurrentUser = INVALID_CHAIR;
	m_cbMagicIndex = INVAILD_CARD_INDEX;
	m_cbBaoPaiIndex = INVAILD_CARD_INDEX;
	ZeroMemory(m_bTing, sizeof(m_bTing));
	ZeroMemory(m_bTrustee, sizeof(m_bTrustee));

	//堆立信息
	m_wHeapHead = INVALID_CHAIR;
	m_wHeapTail = INVALID_CHAIR;
	ZeroMemory(m_cbHeapCardInfo, sizeof(m_cbHeapCardInfo));

	//运行变量
	m_cbProvideCard = 0;
	m_wResumeUser = INVALID_CHAIR;
	m_wProvideUser = INVALID_CHAIR;

	//用户状态
	ZeroMemory(m_bResponse, sizeof(m_bResponse));
	ZeroMemory(m_wUserAction, sizeof(m_wUserAction));
	ZeroMemory(m_cbOperateCard, sizeof(m_cbOperateCard));
	ZeroMemory(m_wPerformAction, sizeof(m_wPerformAction));

	//组合扑克
	ZeroMemory(m_WeaveItemArray, sizeof(m_WeaveItemArray));
	ZeroMemory(m_cbWeaveItemCount, sizeof(m_cbWeaveItemCount));

	//结束信息
	m_cbChiHuCard = 0;
	ZeroMemory(m_dwChiHuKind, sizeof(m_dwChiHuKind));

	//状态变量
	m_bGangOutCard = false;
	m_enSendStatus = Not_Send;
	m_cbGangStatus = WIK_GANERAL;
	m_wProvideGangUser = INVALID_CHAIR;
	ZeroMemory(m_bEnjoinChiHu, sizeof(m_bEnjoinChiHu));
	ZeroMemory(m_bEnjoinChiPeng, sizeof(m_bEnjoinChiPeng));
	ZeroMemory(m_bEnjoinGang, sizeof(m_bEnjoinGang));
	ZeroMemory(m_cbChiPengCount, sizeof(m_cbChiPengCount));	
	ZeroMemory(m_cbGangCount, sizeof(m_cbGangCount));

	//出牌信息
	m_cbOutCardData = 0;
	m_cbOutCardCount = 0;
	m_wOutCardUser = INVALID_CHAIR;

	ZeroMemory(m_cbDiscardCard, sizeof(m_cbDiscardCard));
	ZeroMemory(m_cbDiscardCount, sizeof(m_cbDiscardCount));
	ZeroMemory(m_cbOutFromHandCount, sizeof(m_cbOutFromHandCount));

	//出牌信息
	m_cbMinusHeadCount = 0;
	m_cbMinusLastCount = 0;
	m_cbLeftCardCount = MAX_REPERTORY;
	m_cbEndLeftCount = 0;
	//m_cbSendCardCount = 0;

	//扑克信息
	ZeroMemory(m_cbCardIndex, sizeof(m_cbCardIndex));
	ZeroMemory(m_cbHandCardCount, sizeof(m_cbHandCardCount));

	ZeroMemory(m_lUserGangScore,sizeof(m_lUserGangScore));
	ZeroMemory(m_cbUserCatchCardCount,sizeof(m_cbUserCatchCardCount));
	ZeroMemory(m_bPlayStatus,sizeof(m_bPlayStatus));

	ZeroMemory(m_cbHuCardCount,sizeof(m_cbHuCardCount));
	ZeroMemory(m_cbHuCardData,sizeof(m_cbHuCardData));
	ZeroMemory(m_cbUserMaCount,sizeof(m_cbUserMaCount));
	ZeroMemory(&m_stRecord,sizeof(m_stRecord));

	//规则变量
	ZeroMemory(&m_tGameCustomRule,sizeof(m_tGameCustomRule));
	m_cbMaCount=0;
	m_cbPlayerCount=0;

	ZeroMemory(m_nChaseArrowCount, sizeof(m_nChaseArrowCount));
	ZeroMemory(m_cbChaseArrowArray, sizeof(m_cbChaseArrowArray));
	ZeroMemory(m_cbChaseRemainCard, sizeof(m_cbChaseRemainCard));

#ifdef  CARD_DISPATCHER_CONTROL
	m_cbControlGameCount = 0;
#endif

	return;
}

//析构函数
CTableFrameSink::~CTableFrameSink()
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
}

//接口查询
VOID * CTableFrameSink::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	QUERYINTERFACE(ITableFrameSink,Guid,dwQueryVer);
	QUERYINTERFACE(ITableUserAction,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITableFrameSink,Guid,dwQueryVer);
	return NULL;
}

//复位桌子
VOID CTableFrameSink::RepositionSink()
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//游戏变量
	m_wSiceCount = 0;
	m_wCurrentUser = INVALID_CHAIR;
	m_cbMagicIndex = INVAILD_CARD_INDEX;
	m_cbBaoPaiIndex = INVAILD_CARD_INDEX;
	m_cbMinusHeadCount = 0;
	m_cbMinusLastCount = 0;
	m_cbLeftCardCount = MAX_REPERTORY;
	m_cbEndLeftCount = 0;
	//m_cbSendCardCount = 0;

	ZeroMemory(m_bTing, sizeof(m_bTing));
	ZeroMemory(m_bTrustee, sizeof(m_bTrustee));

	//堆立信息
	m_wHeapHead = INVALID_CHAIR;
	m_wHeapTail = INVALID_CHAIR;
	ZeroMemory(m_cbHeapCardInfo, sizeof(m_cbHeapCardInfo));

	//运行变量
	m_cbProvideCard = 0;
	m_wResumeUser = INVALID_CHAIR;
	m_wProvideUser = INVALID_CHAIR;

	//状态变量
	m_bGangOutCard = false;
	m_enSendStatus = Not_Send;
	m_cbGangStatus = WIK_GANERAL;
	m_wProvideGangUser = INVALID_CHAIR;
	ZeroMemory(m_bEnjoinChiHu, sizeof(m_bEnjoinChiHu));
	ZeroMemory(m_bEnjoinChiPeng, sizeof(m_bEnjoinChiPeng));	
	ZeroMemory(m_bEnjoinGang, sizeof(m_bEnjoinGang));
	ZeroMemory(m_cbChiPengCount, sizeof(m_cbChiPengCount));
	ZeroMemory(m_cbGangCount, sizeof(m_cbGangCount));

	for(int i = 0; i < GAME_PLAYER; i++)
	{
		m_vecEnjoinChiHu[i].clear();
		m_vecEnjoinChiPeng[i].clear();	
	}

	//用户状态
	ZeroMemory(m_bResponse, sizeof(m_bResponse));
	ZeroMemory(m_wUserAction, sizeof(m_wUserAction));
	ZeroMemory(m_cbOperateCard, sizeof(m_cbOperateCard));
	ZeroMemory(m_wPerformAction, sizeof(m_wPerformAction));

	//组合扑克
	ZeroMemory(m_WeaveItemArray, sizeof(m_WeaveItemArray));
	ZeroMemory(m_cbWeaveItemCount, sizeof(m_cbWeaveItemCount));

	//结束信息
	m_cbChiHuCard=0;
	ZeroMemory(m_dwChiHuKind, sizeof(m_dwChiHuKind));
	
	//出牌信息
	m_cbOutCardData = 0;
	m_cbOutCardCount = 0;
	m_wOutCardUser = INVALID_CHAIR;

	ZeroMemory(m_cbDiscardCard, sizeof(m_cbDiscardCard));
	ZeroMemory(m_cbDiscardCount, sizeof(m_cbDiscardCount));
	ZeroMemory(m_cbOutFromHandCount, sizeof(m_cbOutFromHandCount));

	//扑克信息
	ZeroMemory(m_cbCardIndex, sizeof(m_cbCardIndex));
	ZeroMemory(m_cbHandCardCount, sizeof(m_cbHandCardCount));
	ZeroMemory(m_cbUserCatchCardCount,sizeof(m_cbUserCatchCardCount));
	ZeroMemory(m_bTrustee,sizeof(m_bTrustee));
	ZeroMemory(m_lUserGangScore,sizeof(m_lUserGangScore));
	ZeroMemory(m_bPlayStatus,sizeof(m_bPlayStatus));

	ZeroMemory(m_cbHuCardCount,sizeof(m_cbHuCardCount));
	ZeroMemory(m_cbHuCardData,sizeof(m_cbHuCardData));
	ZeroMemory(m_cbUserMaCount,sizeof(m_cbUserMaCount));

	ZeroMemory(m_nChaseArrowCount, sizeof(m_nChaseArrowCount));
	ZeroMemory(m_cbChaseArrowArray, sizeof(m_cbChaseArrowArray));
	ZeroMemory(m_cbChaseRemainCard, sizeof(m_cbChaseRemainCard));
	return;
}

//配置桌子
bool CTableFrameSink::Initialization(IUnknownEx * pIUnknownEx)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//查询接口
	m_pITableFrame=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITableFrame);

	//错误判断
	if (m_pITableFrame==NULL)
	{
		CTraceService::TraceString(TEXT("游戏桌子 CTableFrameSink 查询 ITableFrame 接口失败"),TraceLevel_Exception);
		return false;
	}

	//游戏配置
	m_pGameServiceAttrib=m_pITableFrame->GetGameServiceAttrib();
	m_pGameServiceOption=m_pITableFrame->GetGameServiceOption();

	//自定规则
	ASSERT(m_pITableFrame->GetCustomRule()!=NULL);
	tagCustomRule * pGameCustomRule=(tagCustomRule *)m_pITableFrame->GetCustomRule();
	m_tGameCustomRule = *pGameCustomRule;
	m_GameLogic.SetCustomRule(&m_tGameCustomRule);

	m_cbMaCount = m_tGameCustomRule.cbMaCount;
	m_cbPlayerCount = m_tGameCustomRule.cbPlayerCount;

	ZeroMemory(&m_stRecord,sizeof(m_stRecord));

	m_pITableFrame->SetStartMode(START_MODE_FULL_READY);

	return true;
}

//消费能力
SCORE CTableFrameSink::QueryConsumeQuota(IServerUserItem * pIServerUserItem)
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	return 0L;
}

//最少积分
SCORE CTableFrameSink::QueryLessEnterScore(WORD wChairID, IServerUserItem * pIServerUserItem)
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//金币游戏
	if (m_pGameServiceOption->wServerType&(GAME_GENRE_GOLD|SCORE_GENRE_POSITIVE))
	{		
		return 64 * m_pITableFrame->GetCellScore();
	}
	return 0;
}

//游戏开始
bool CTableFrameSink::OnEventGameStart()
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//设置状态
	m_pITableFrame->SetGameStatus(GAME_SCENE_PLAY);

	//随机扑克
	BYTE Sice1 = rand()%6 + 1;
	BYTE Sice2 = rand()%6 + 1;
	BYTE minSice = min(Sice1,Sice2);
	m_wSiceCount = MAKEWORD(Sice1,Sice2);
	m_cbLeftCardCount=MAX_REPERTORY;
	m_cbMinusHeadCount = 0;
	m_cbMinusLastCount = 0;
	//m_cbSendCardCount = 0;
	m_bUserActionDone=false;
	m_enSendStatus = Not_Send;
	m_cbGangStatus = WIK_GANERAL;
	m_wProvideGangUser = INVALID_CHAIR;

	m_GameLogic.RandCardList(m_cbRepertoryCard,CountArray(m_cbRepertoryCard));

#ifdef  CARD_DISPATCHER_CONTROL
	//非控制状态
	if(m_cbControlGameCount==0)
	{

		TCHAR szPath[MAX_PATH] = TEXT("");
		CString strSaveFileName;
		strSaveFileName.Format(TEXT("D:\\GameRule\\SparrowCHYData.dat"));
		CFile file;

		if (file.Open(strSaveFileName, CFile::modeRead))
		{
			file.Read(&m_wBankerUser,sizeof(m_wBankerUser));
			file.Read(m_cbRepertoryCard,sizeof(m_cbRepertoryCard));		
			file.Close();
		} 
		else 
		{
			GetCurrentDirectory(sizeof(szPath), szPath);
			strSaveFileName.Format(TEXT("%s\\GameRule\\SparrowCHYData.dat"), szPath);
			if (file.Open(strSaveFileName, CFile::modeRead))
			{
				file.Read(&m_wBankerUser,sizeof(m_wBankerUser));
				file.Read(m_cbRepertoryCard,sizeof(m_cbRepertoryCard));		
				file.Close();
			}
		}
	}
	else
	{
		m_wBankerUser = m_wControBankerUser;
		CopyMemory(m_cbRepertoryCard, m_cbControlRepertoryCard, sizeof(m_cbRepertoryCard));
		m_cbControlGameCount--;
	}

#endif

	//会牌可以当财神
	m_cbMagicIndex = m_tGameCustomRule.bEnabled_HuiPai ? m_GameLogic.GetRandHuiPaiCardIndex() : INVAILD_CARD_INDEX; //m_GameLogic.SwitchToCardIndex(0x35);

#ifdef  LSH_TEST
	m_cbMagicIndex = m_tGameCustomRule.bEnabled_HuiPai ? m_GameLogic.SwitchToCardIndex(0x11) : INVAILD_CARD_INDEX;  // for the TEST, Huipai set 7 wan always
#endif
 	m_GameLogic.SetMagicIndex(m_cbMagicIndex);

	{ // BaoPai Generate
		m_cbBaoPaiIndex = CreateNewBaopaiIndex();
		m_GameLogic.SetBaopaiIndex(m_cbBaoPaiIndex);
		CString str; str.Format(_T("\n\t\t First Baopai index: %d(0x%02x)"), m_cbBaoPaiIndex, m_GameLogic.SwitchToCardData(m_cbBaoPaiIndex));
		OutputDebugString(str);
		CTraceService::TraceString((LPCTSTR)str,TraceLevel_Debug);
	}

	//分发扑克
	for (WORD i = 0; i < m_cbPlayerCount; i++)
	{
		if(m_pITableFrame->GetTableUserItem(i) == NULL)
			continue;

		m_bPlayStatus[i]=true;
		m_cbLeftCardCount -= (MAX_COUNT - 1);
		m_cbMinusHeadCount += (MAX_COUNT - 1);
		m_cbHandCardCount[i] = (MAX_COUNT - 1);

		BYTE cbCardIndex = MAX_REPERTORY - m_cbMinusHeadCount;
		m_GameLogic.SwitchToCardIndex(&m_cbRepertoryCard[cbCardIndex], MAX_COUNT - 1, m_cbCardIndex[i]);
	}

	if(m_wBankerUser == INVALID_CHAIR && (m_pGameServiceOption->wServerType&GAME_GENRE_PERSONAL)!=0 )//房卡模式下先把庄家给房主
	{
#ifdef LSH_TEST
		DWORD OwnerId =  m_pITableFrame->GetTableOwner();
		IServerUserItem *pOwnerItem = m_pITableFrame->SearchUserItem(OwnerId);
		if(pOwnerItem->GetChairID() != INVALID_CHAIR)
			m_wBankerUser = pOwnerItem->GetChairID();
#else
		m_wBankerUser = rand() % m_cbPlayerCount;
		while(m_pITableFrame->GetTableUserItem(m_wBankerUser)==NULL)
		{
			m_wBankerUser = (m_wBankerUser+1)%m_cbPlayerCount;
		}
#endif
	}
	//确定庄家
	if(m_wBankerUser == INVALID_CHAIR || m_bPlayStatus[m_wBankerUser]==false)
	{
		m_wBankerUser = rand() % m_cbPlayerCount;
		while(m_pITableFrame->GetTableUserItem(m_wBankerUser)==NULL)
		{
			m_wBankerUser = (m_wBankerUser+1)%m_cbPlayerCount;
		}
	}

	//发送扑克
	m_cbLeftCardCount--;
	BYTE cbCardIndex = MAX_REPERTORY - ++m_cbMinusHeadCount;
	m_cbSendCardData = m_cbRepertoryCard[cbCardIndex];
	m_cbCardIndex[m_wBankerUser][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]++;
	m_cbUserCatchCardCount[m_wBankerUser]++;
	//设置变量
	m_cbProvideCard = m_cbSendCardData;
	m_wProvideUser = m_wBankerUser;
	m_wCurrentUser = m_wBankerUser;

	//堆立信息
	WORD wSiceCount = LOBYTE(m_wSiceCount) + HIBYTE(m_wSiceCount);
	WORD wTakeChairID = (m_wBankerUser + wSiceCount - 1) % GAME_PLAYER;
	BYTE cbTakeCount = MAX_REPERTORY - m_cbLeftCardCount;
	for (WORD i = 0; i < GAME_PLAYER; i++)
	{
		//计算数目
		BYTE cbValidCount = HEAP_FULL_COUNT - m_cbHeapCardInfo[wTakeChairID][1] - ((i == 0) ? (minSice) * 2 : 0);
		BYTE cbRemoveCount = __min(cbValidCount, cbTakeCount);

		//提取扑克
		cbTakeCount -= cbRemoveCount;
		m_cbHeapCardInfo[wTakeChairID][(i == 0) ? 1 : 0] += cbRemoveCount;

		//完成判断
		if (cbTakeCount == 0)
		{
			m_wHeapHead = wTakeChairID;
			m_wHeapTail = (m_wBankerUser + wSiceCount - 1) % GAME_PLAYER;
			break;
		}
		//切换索引
		wTakeChairID = (wTakeChairID + GAME_PLAYER - 1) % GAME_PLAYER;
	}

	//操作分析
	ZeroMemory(m_wUserAction, sizeof(m_wUserAction));

	//杠牌判断
	tagGangCardResult GangCardResult;
	m_wUserAction[m_wCurrentUser] |= m_GameLogic.AnalyseGangCardEx(m_cbCardIndex[m_wCurrentUser],NULL,0,0,GangCardResult, m_cbOutFromHandCount[m_wCurrentUser]);

	//胡牌判断
	CChiHuRight chr;
	m_cbCardIndex[m_wCurrentUser][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]--;
	m_wUserAction[m_wCurrentUser] |= m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[m_wCurrentUser],NULL,0,m_cbSendCardData,chr);
	m_cbCardIndex[m_wCurrentUser][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]++;
	m_cbHandCardCount[m_wCurrentUser]++;

	//听牌判断
	BYTE cbCount = 0;
	BYTE cbOutCard[MAX_COUNT][28] = {0};
	CMD_S_Hu_Data HuData;
	ZeroMemory(&HuData,sizeof(HuData));
	if(m_bTing[m_wCurrentUser] == false)
	{
		cbCount =m_GameLogic.AnalyseTingCard(m_cbCardIndex[m_wCurrentUser],0,0,HuData.cbOutCardCount,HuData.cbOutCardData,HuData.cbHuCardCount,HuData.cbHuCardData);
		if(cbCount >0)
		{
			m_wUserAction[m_wCurrentUser] |= WIK_LISTEN;
			for(int i=0;i<MAX_COUNT;i++)
			{
				if(HuData.cbHuCardCount[i]>0)
				{
					for(int j=0;j<HuData.cbHuCardCount[i];j++)
					{
						HuData.cbHuCardRemainingCount[i][j] = GetRemainingCount(m_wCurrentUser,HuData.cbHuCardData[i][j]);
					}
				}
				else
					break;
			}
			m_pITableFrame->SendTableData(m_wCurrentUser,SUB_S_HU_CARD,&HuData,sizeof(HuData));
		}
	}
	
	//构造变量
	CMD_S_GameStart GameStart;
	ZeroMemory(&GameStart,sizeof(GameStart));
	GameStart.wBankerUser = m_wBankerUser;
	GameStart.wSiceCount = m_wSiceCount;
	GameStart.wHeapHead = m_wHeapHead;
	GameStart.wHeapTail = m_wHeapTail;
	GameStart.cbMagicIndex = m_cbMagicIndex;

	GameStart.cbInningsCount_cy = m_tGameCustomRule.cbInningsCount_cy;
	GameStart.bEnabled_DianPao = m_tGameCustomRule.bEnabled_DianPao;
	GameStart.bEnabled_FengGang= m_tGameCustomRule.bEnabled_FengGang;
	GameStart.bEnabled_HuiPai	= m_tGameCustomRule.bEnabled_HuiPai;
	GameStart.bEnabled_BaoPai	= m_tGameCustomRule.bEnabled_BaoPai;
	GameStart.bEnabled_ZhanLiHu= m_tGameCustomRule.bEnabled_ZhanLiHu;
	GameStart.bEnabled_JiaHu	= m_tGameCustomRule.bEnabled_JiaHu;
	GameStart.bEnabled_ChangMaoGang = m_tGameCustomRule.bEnabled_ChangMaoGang;

	CopyMemory(GameStart.cbHeapCardInfo, m_cbHeapCardInfo, sizeof(GameStart.cbHeapCardInfo));

	//发送数据
	for (WORD i=0;i<m_cbPlayerCount;i++)
	{
		if(m_pITableFrame->GetTableUserItem(i) == NULL)
			continue;
		GameStart.wUserAction = m_wUserAction[i];
		ZeroMemory(GameStart.cbCardData, sizeof(GameStart.cbCardData));
		m_GameLogic.SwitchToCardData(m_cbCardIndex[i], GameStart.cbCardData);

		//GameStart.cbOutCardCount=0;
		//ZeroMemory(GameStart.cbOutCardData, sizeof(GameStart.cbOutCardData));
		//if(i == m_wBankerUser && cbCount>0)
		//{
		//	GameStart.cbOutCardCount=cbCount;
		//	CopyMemory(GameStart.cbOutCardData,cbOutCard,sizeof(cbOutCard));
		//}
		m_pITableFrame->SendTableData(i, SUB_S_GAME_START, &GameStart, sizeof(GameStart));
		m_pITableFrame->SendLookonData(i, SUB_S_GAME_START, &GameStart, sizeof(GameStart));		
	}

	if((m_pGameServiceOption->wServerType&GAME_GENRE_MATCH) != 0)
	{
		m_pITableFrame->SetGameTimer(IDI_CHECK_TABLE, 30000, -1, NULL);
		m_cbWaitTime = 0;
	}

	return true;
}

//游戏结束
bool CTableFrameSink::OnEventGameConclude(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	CStringA str;str.Format("\n\t\t wChairID:%d, cbReason:%d   ", wChairID, cbReason);
	OutputDebugStringA(str);
	if((m_pGameServiceOption->wServerType & GAME_GENRE_MATCH) != 0)
		m_pITableFrame->KillGameTimer(IDI_CHECK_TABLE);
	switch (cbReason)
	{
	case GER_NORMAL:		//常规结束
		{
			//变量定义
			CMD_S_GameConclude GameConclude;
			ZeroMemory(&GameConclude, sizeof(GameConclude));
			GameConclude.cbSendCardData = m_cbSendCardData;

			WORD wWinner=INVALID_CHAIR;
			BYTE cbBiMenStatus = 0;
			for (WORD i = 0; i < m_cbPlayerCount; i++) {
				WORD k = wChairID==INVALID_CHAIR ? i: (i+wChairID)%m_cbPlayerCount;
				
				if(WIK_KIND_HU==m_dwChiHuKind[k]  && wWinner==INVALID_CHAIR)
					wWinner = k;

				else {
					if( WIK_KIND_HU==m_dwChiHuKind[k] ) m_dwChiHuKind[k] ^= WIK_KIND_HU;
					if( !m_GameLogic.isOpenedKaimen(m_WeaveItemArray[k], m_cbWeaveItemCount[k]))
						cbBiMenStatus |= (1<<k);
				}

				GameConclude.dwChiHuKind[k] = m_dwChiHuKind[k];
				GameConclude.cbCardCount[k] = m_GameLogic.SwitchToCardData(m_cbCardIndex[k], GameConclude.cbHandCardData[k]);
			}

			//结束信息
			if( wWinner != INVALID_CHAIR ){
				//权位过滤
				BYTE mask = (0xF^(1<<wWinner));
				if( (cbBiMenStatus & mask) == mask)
					m_ChiHuRight[wWinner] |= CHR_QI_YU;
				FiltrateRight(wWinner, m_ChiHuRight[wWinner]);
				m_ChiHuRight[wWinner].GetRightData(GameConclude.dwChiHuRight[wWinner], MAX_RIGHT_COUNT);
			}

			//计算胡牌输赢分
			SCORE lUserGameScore[GAME_PLAYER]={0};
			CalcHuPaiScore(wWinner, lUserGameScore, cbBiMenStatus);

			//积分变量
			tagScoreInfo ScoreInfoArray[GAME_PLAYER];
			ZeroMemory(&ScoreInfoArray, sizeof(ScoreInfoArray));

			if( wWinner != INVALID_CHAIR && wWinner != m_wProvideUser) {
				GameConclude.wProvideUser = m_wProvideUser;
			} else {
				GameConclude.wProvideUser = INVALID_CHAIR;
			}
			GameConclude.cbProvideCard = m_cbProvideCard;

			GameConclude.cbBaopaiCardData = m_GameLogic.SwitchToCardData(m_cbBaoPaiIndex);
			GameConclude.cbBiMenStatus = cbBiMenStatus;

			//CStringA strLogScore= "\n\tlUserGameScore = {", strLogGangScore="\n\tm_lUserGangScore = {";
			//统计积分
			for (WORD i = 0; i < m_cbPlayerCount; i++)
			{
				if(!m_bPlayStatus[i])
					continue;

				GameConclude.lGameScore[i] = lUserGameScore[i];
				//胡牌分算完后再加上杠的输赢分就是玩家本轮最终输赢分
				GameConclude.lGameScore[i] += m_lUserGangScore[i];
				GameConclude.lGangScore[i] = m_lUserGangScore[i];
				//strLogScore.Format("%s %I64d,", strLogScore, lUserGameScore[i] );
				//strLogGangScore.Format("%s %I64d,", strLogGangScore, m_lUserGangScore[i] );

				//收税
				if (GameConclude.lGameScore[i]>0 && (m_pGameServiceOption->wServerType&GAME_GENRE_GOLD)!=0)
				{
					GameConclude.lRevenue[i] = m_pITableFrame->CalculateRevenue(i,GameConclude.lGameScore[i]);
					GameConclude.lGameScore[i] -= GameConclude.lRevenue[i];
				}

				ScoreInfoArray[i].lRevenue = GameConclude.lRevenue[i];
				ScoreInfoArray[i].lScore = GameConclude.lGameScore[i];
				ScoreInfoArray[i].cbType = ScoreInfoArray[i].lScore > 0 ? SCORE_TYPE_WIN : SCORE_TYPE_LOSE;

				//历史积分
				m_HistoryScore.OnEventUserScore(i, GameConclude.lGameScore[i]);
				if(m_stRecord.nCount<32)
				{
					m_stRecord.lDetailScore[i][m_stRecord.nCount]=GameConclude.lGameScore[i];
					m_stRecord.lAllScore[i] += GameConclude.lGameScore[i];
				}
			}
			//strLogScore.Format("%s }", strLogScore);
			//strLogGangScore.Format("%s }", strLogGangScore);
			//OutputDebugStringA(strLogScore);
			//OutputDebugStringA(strLogGangScore);

			if( wWinner != INVALID_CHAIR){
				if(GameConclude.dwChiHuRight[wWinner][0]&CHR_ZI_MO){
					m_stRecord.cbZiMoCount[wWinner]++;
				} else{
					m_stRecord.cbDianPaoCount[wWinner]++;
				}
			}
			m_stRecord.cbZhuangJiaCount[m_wBankerUser]++;
			m_stRecord.nCount++;

			if( (m_pGameServiceOption->wServerType&GAME_GENRE_PERSONAL) !=0 )//房卡模式
			{
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_RECORD,&m_stRecord,sizeof(m_stRecord));
			}

			//发送数据
			m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_GAME_CONCLUDE, &GameConclude, sizeof(GameConclude));
			m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_GAME_CONCLUDE, &GameConclude, sizeof(GameConclude));

			
			//写入积分
			m_pITableFrame->WriteTableScore(ScoreInfoArray, m_cbPlayerCount);

			//结束游戏
			m_pITableFrame->ConcludeGame(GAME_SCENE_FREE);

			if( (m_pGameServiceOption->wServerType&GAME_GENRE_PERSONAL) !=0 )//房卡模式
			{
				if(m_pITableFrame->IsPersonalRoomDisumme() )//当前朋友局解散清理记录
				{
					ZeroMemory(&m_stRecord,sizeof(m_stRecord));
				}
			}
			
			return true;
		}
	case GER_NETWORK_ERROR:	//网络中断
		{
			return true;
		}
	case GER_USER_LEAVE:	//用户强退
		{
			if( (m_pGameServiceOption->wServerType&GAME_GENRE_PERSONAL) != 0 )//房卡模式
				return true;

			//自动托管
			OnUserTrustee(wChairID,true);

			return true;
		}
	case GER_DISMISS:		//游戏解散
		{
			//变量定义
			CMD_S_GameConclude GameConclude;
			ZeroMemory(&GameConclude, sizeof(GameConclude));

			m_wBankerUser = INVALID_CHAIR;

			GameConclude.cbSendCardData = m_cbSendCardData;

			//用户扑克
			BYTE cbCardIndex=0;
			for (WORD i = 0; i < GAME_PLAYER; i++)
			{
				GameConclude.cbCardCount[i] = m_GameLogic.SwitchToCardData(m_cbCardIndex[i], GameConclude.cbHandCardData[i]);
			}
			GameConclude.wProvideUser = INVALID_CHAIR;
			GameConclude.cbBaopaiCardData = m_GameLogic.SwitchToCardData(m_cbBaoPaiIndex);

			//发送信息
			m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_GAME_CONCLUDE, &GameConclude, sizeof(GameConclude));
			m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_GAME_CONCLUDE, &GameConclude, sizeof(GameConclude));

			//结束游戏
			m_pITableFrame->ConcludeGame(GAME_SCENE_FREE);

			if( (m_pGameServiceOption->wServerType&GAME_GENRE_PERSONAL) !=0 )//房卡模式
			{
				if(m_pITableFrame->IsPersonalRoomDisumme() )//当前朋友局解散清理记录
				{
					ZeroMemory(&m_stRecord,sizeof(m_stRecord));
				}
			}
			
			return true;
		}
	}

	//错误断言
	ASSERT(FALSE);

	return false;
}

//发送场景
bool CTableFrameSink::OnEventSendGameScene(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret)
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	CStringA str;str.Format("\n\t\t wChairID:%d, cbGameStatus:%d   ", wChairID, cbGameStatus);
	OutputDebugStringA(str);
	switch (cbGameStatus)
	{
	case GAME_SCENE_FREE:	//空闲状态
		{
			//构造数据
			CMD_S_StatusFree StatusFree;
			ZeroMemory(&StatusFree, sizeof(StatusFree));

			//设置变量
			StatusFree.lCellScore = m_pITableFrame->GetCellScore();
			StatusFree.cbMaCount = m_cbMaCount;
			StatusFree.cbPlayerCount = m_cbPlayerCount;
			//自定规则
			StatusFree.cbTimeOutCard = m_tGameCustomRule.cbTimeOutCard;		
			StatusFree.cbTimeOperateCard = m_tGameCustomRule.cbTimeOperateCard;
			StatusFree.cbTimeStartGame = m_tGameCustomRule.cbTimeStartGame;

			//历史积分
			for (WORD i = 0; i < GAME_PLAYER; i++)
			{
				//变量定义
				tagHistoryScore * pHistoryScore = m_HistoryScore.GetHistoryScore(i);

				//设置变量
				StatusFree.lTurnScore[i] = pHistoryScore->lTurnScore;
				StatusFree.lCollectScore[i] = pHistoryScore->lCollectScore;
			}

			if( (m_pGameServiceOption->wServerType&GAME_GENRE_PERSONAL) !=0 )//房卡模式
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_RECORD,&m_stRecord,sizeof(m_stRecord));

			//发送场景
			return m_pITableFrame->SendGameScene(pIServerUserItem, &StatusFree, sizeof(StatusFree));
		}
	case GAME_SCENE_PLAY:	//游戏状态
		{
			//变量定义
			CMD_S_StatusPlay StatusPlay;
			ZeroMemory(&StatusPlay, sizeof(StatusPlay));

			//自定规则
			StatusPlay.cbTimeOutCard = m_tGameCustomRule.cbTimeOutCard;		
			StatusPlay.cbTimeOperateCard = m_tGameCustomRule.cbTimeOperateCard;
			StatusPlay.cbTimeStartGame = m_tGameCustomRule.cbTimeStartGame;
			
			if( (m_pGameServiceOption->wServerType&GAME_GENRE_PERSONAL) ==0)//普通房间
				OnUserTrustee(wChairID,false);//重入取消托管

			//规则
			StatusPlay.cbMaCount			= m_tGameCustomRule.cbMaCount;
			StatusPlay.cbPlayerCount		= m_tGameCustomRule.cbPlayerCount;
			StatusPlay.cbInningsCount_cy	= m_tGameCustomRule.cbInningsCount_cy;
			StatusPlay.bEnabled_DianPao 	= m_tGameCustomRule.bEnabled_DianPao;
			StatusPlay.bEnabled_FengGang	= m_tGameCustomRule.bEnabled_FengGang;
			StatusPlay.bEnabled_HuiPai		= m_tGameCustomRule.bEnabled_HuiPai;
			StatusPlay.bEnabled_BaoPai		= m_tGameCustomRule.bEnabled_BaoPai;
			StatusPlay.bEnabled_ZhanLiHu	= m_tGameCustomRule.bEnabled_ZhanLiHu;
			StatusPlay.bEnabled_JiaHu		= m_tGameCustomRule.bEnabled_JiaHu;
			StatusPlay.bEnabled_ChangMaoGang= m_tGameCustomRule.bEnabled_ChangMaoGang;

			//游戏变量
			StatusPlay.wBankerUser = m_wBankerUser;
			StatusPlay.wCurrentUser = m_wCurrentUser;
			StatusPlay.lCellScore = m_pGameServiceOption->lCellScore;
			StatusPlay.cbMagicIndex = m_cbMagicIndex;
			CopyMemory(StatusPlay.bTrustee, m_bTrustee, sizeof(m_bTrustee));

			//状态变量
			StatusPlay.cbActionCard = m_cbProvideCard;
			StatusPlay.cbLeftCardCount = m_cbLeftCardCount;
			StatusPlay.cbActionMask = !m_bResponse[wChairID] ? m_wUserAction[wChairID] : WIK_NULL;
			
			CopyMemory(StatusPlay.bTrustee, m_bTrustee, sizeof(StatusPlay.bTrustee));
			CopyMemory(StatusPlay.bTing, m_bTing, sizeof(StatusPlay.bTing));
			//当前能胡的牌
			StatusPlay.cbOutCardCount = m_GameLogic.AnalyseTingCard(m_cbCardIndex[wChairID],m_WeaveItemArray[wChairID],m_cbWeaveItemCount[wChairID],StatusPlay.cbOutCardCount,StatusPlay.cbOutCardDataEx,StatusPlay.cbHuCardCount,StatusPlay.cbHuCardData);
			//BYTE cbCount = 0;
			//if(m_bTing[wChairID] == false || m_wCurrentUser != wChairID) {

			//	m_GameLogic.AnalyseTingCard(m_cbCardIndex[wChairID],m_WeaveItemArray[wChairID],m_cbWeaveItemCount[wChairID],StatusPlay.cbOutCardCount,StatusPlay.cbOutCardDataEx,StatusPlay.cbHuCardCount,StatusPlay.cbHuCardData);

			//} else {
			//	m_GameLogic.AnalyseTingCard(m_cbCardIndex[wChairID],m_WeaveItemArray[wChairID],m_cbWeaveItemCount[wChairID],StatusPlay.cbOutCardCount,StatusPlay.cbOutCardDataEx,StatusPlay.cbHuCardCount,StatusPlay.cbHuCardData);
			//	m_cbCardIndex[wChairID][m_GameLogic.SwitchToCardIndex(m_cbProvideCard)]--;
			//	cbCount =m_GameLogic.AnalyseTingCard(m_cbCardIndex[wChairID],m_WeaveItemArray[wChairID],m_cbWeaveItemCount[wChairID],StatusPlay.cbOutCardCount,StatusPlay.cbOutCardDataEx,StatusPlay.cbHuCardCount,StatusPlay.cbHuCardData);
			//	m_cbCardIndex[wChairID][m_GameLogic.SwitchToCardIndex(m_cbProvideCard)]++;

			//	ASSERT(cbCount>0);
			//	if(cbCount > 0) {
			//		StatusPlay.cbOutCardDataEx[0] = m_cbProvideCard;
			//	}
			//}

			//历史记录
			StatusPlay.wOutCardUser = m_wOutCardUser;
			StatusPlay.cbOutCardData = m_cbOutCardData;
			CopyMemory(StatusPlay.cbDiscardCard, m_cbDiscardCard, sizeof(StatusPlay.cbDiscardCard));
			CopyMemory(StatusPlay.cbDiscardCount, m_cbDiscardCount, sizeof(StatusPlay.cbDiscardCount));

			CopyMemory(StatusPlay.cbChaseArrowArray,m_cbChaseArrowArray,sizeof(StatusPlay.cbChaseArrowArray));

			//组合扑克
			CopyMemory(StatusPlay.WeaveItemArray, m_WeaveItemArray, sizeof(StatusPlay.WeaveItemArray));
			CopyMemory(StatusPlay.cbWeaveItemCount, m_cbWeaveItemCount, sizeof(StatusPlay.cbWeaveItemCount));

			//堆立信息
			StatusPlay.wHeapHead = m_wHeapHead;
			StatusPlay.wHeapTail = m_wHeapTail;
			CopyMemory(StatusPlay.cbHeapCardInfo, m_cbHeapCardInfo, sizeof(m_cbHeapCardInfo));

			//扑克数据
			for(int i = 0; i < GAME_PLAYER; i++)
			{
				StatusPlay.cbCardCount[i] = m_GameLogic.GetCardCount(m_cbCardIndex[i]);
			}
			m_GameLogic.SwitchToCardData(m_cbCardIndex[wChairID], StatusPlay.cbCardData);
			StatusPlay.cbSendCardData = (m_wCurrentUser == wChairID) ? m_cbSendCardData : INVAILD_CARD_DATA;

			//历史积分
			for (WORD i = 0; i < GAME_PLAYER; i++)
			{
				//变量定义
				tagHistoryScore * pHistoryScore = m_HistoryScore.GetHistoryScore(i);

				//设置变量
				StatusPlay.lTurnScore[i] = pHistoryScore->lTurnScore;
				StatusPlay.lCollectScore[i] = pHistoryScore->lCollectScore;
			}

			if( (m_pGameServiceOption->wServerType&GAME_GENRE_PERSONAL) !=0 )//房卡模式
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_RECORD,&m_stRecord,sizeof(m_stRecord));
			//发送场景
			return m_pITableFrame->SendGameScene(pIServerUserItem, &StatusPlay, sizeof(StatusPlay));
		}
	}

	//错误断言
	ASSERT(FALSE);

	return false;
}

//时间事件
bool CTableFrameSink::OnTimerMessage(DWORD dwTimerID, WPARAM wBindParam)
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	if(dwTimerID == IDI_FENZHANG_DELAY)
	{
		m_pITableFrame->KillGameTimer(dwTimerID);

		//立刻发下一张
		m_wCurrentUser = NextUserID(m_wCurrentUser);
		if( m_cbLeftCardCount > FENZHANG_COUNT-m_cbPlayerCount){
			DispatchCardData(m_wCurrentUser, false);

		} else {
			OnEventGameConclude(INVALID_CHAIR, NULL, GER_NORMAL);
		}
		return true;
	}

	if((m_pGameServiceOption->wServerType&GAME_GENRE_MATCH)!=0)
	{
		if(dwTimerID==IDI_CHECK_TABLE)
		{
			m_cbWaitTime++;
			if(m_cbWaitTime>=3)
			{
				OnEventGameConclude(INVALID_CHAIR,NULL,GER_DISMISS);
			}
			else if(m_cbWaitTime>=2)
			{
				for(int i=0;i<GAME_PLAYER;i++)
				{
					IServerUserItem *pServerUserItem=m_pITableFrame->GetTableUserItem(i);
					if(pServerUserItem!=NULL && pServerUserItem->GetUserStatus()==US_OFFLINE)return true;				
				}
				OnEventGameConclude(INVALID_CHAIR,NULL,GER_DISMISS);
			}
			return true;
		}
	}

	if(dwTimerID == IDI_OUT_CARD)
	{
		m_pITableFrame->KillGameTimer(dwTimerID);

		BYTE cardindex=m_GameLogic.SwitchToCardIndex(m_cbSendCardData);
		if(cardindex != m_cbMagicIndex)
			cardindex = m_GameLogic.SwitchToCardIndex(m_cbSendCardData);
		else
		{
			for(int i=0;i<MAX_INDEX;i++)
			{
				if(m_cbCardIndex[m_wCurrentUser][i]>0 && i !=m_cbMagicIndex)
				{
					cardindex = i;
					break;
				}
			}
		}

		OnUserOutCard(m_wCurrentUser,m_GameLogic.SwitchToCardData(cardindex),true);

		UpdateBaoPaiIfNeed();
		return true;
	}
	else if(dwTimerID >= IDI_OPERATE_CARD && dwTimerID < IDI_OPERATE_CARD+GAME_PLAYER)
	{
		m_pITableFrame->KillGameTimer(dwTimerID);

		WORD wChair=(WORD)dwTimerID-IDI_OPERATE_CARD;
		BYTE cbOperateCard[3]={0};
		if(m_wUserAction[wChair] != WIK_LISTEN)
			OnUserOperateCard(wChair,WIK_NULL,cbOperateCard);
		else
		{
			OnUserListenCard(wChair,false);
		}

		UpdateBaoPaiIfNeed();
	}

	return false;
}

//数据事件
bool CTableFrameSink::OnDataBaseMessage(WORD wRequestID, VOID * pData, WORD wDataSize)
{
	return false;
}

//积分事件
bool CTableFrameSink::OnUserScroeNotify(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	return false;
}

//游戏消息
bool CTableFrameSink::OnGameMessage(WORD wSubCmdID, VOID * pData, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);

	m_cbWaitTime = 0;
	switch (wSubCmdID)
	{
	case SUB_C_OUT_CARD:
		{
			CStringA str;str.Format("\n\t\twSubCmdID:SUB_C_OUT_CARD(%d), wDataSize:%d   ", wSubCmdID, wDataSize);
			OutputDebugStringA(str);
			//效验消息
			ASSERT(wDataSize == sizeof(CMD_C_OutCard));
			if (wDataSize != sizeof(CMD_C_OutCard)) return false;

			//用户效验
			ASSERT(pIServerUserItem->GetUserStatus() == US_PLAYING);
			if (pIServerUserItem->GetUserStatus() != US_PLAYING) return true;

			//消息处理
			CMD_C_OutCard * pOutCard = (CMD_C_OutCard *)pData;
			bool bResult =  OnUserOutCard(pIServerUserItem->GetChairID(), pOutCard->cbCardData);

			UpdateBaoPaiIfNeed();
			return bResult;
		}
	case SUB_C_OPERATE_CARD:	//操作消息
		{
			CStringA str;str.Format("\n\t\twSubCmdID:SUB_C_OPERATE_CARD(%d), wDataSize:%d   ", wSubCmdID, wDataSize);
			OutputDebugStringA(str);
			//效验消息
			ASSERT(wDataSize == sizeof(CMD_C_OperateCard));
			if (wDataSize != sizeof(CMD_C_OperateCard)) return false;

			//用户效验
			if (pIServerUserItem->GetUserStatus() != US_PLAYING) return true;

			//消息处理
			CMD_C_OperateCard * pOperateCard = (CMD_C_OperateCard *)pData;
			bool bResult = OnUserOperateCard(pIServerUserItem->GetChairID(), pOperateCard->wOperateCode, pOperateCard->cbOperateCard);

			UpdateBaoPaiIfNeed();
			return bResult;
		}
	case SUB_C_LISTEN_CARD:
		{
			CStringA str;str.Format("\n\t\twSubCmdID:SUB_C_LISTEN_CARD(%d), wDataSize:%d   ", wSubCmdID, wDataSize);
			OutputDebugStringA(str);
			//效验消息
			ASSERT(wDataSize == sizeof(CMD_C_ListenCard));
			if (wDataSize != sizeof(CMD_C_ListenCard)) return false;

			//用户效验
			if (pIServerUserItem->GetUserStatus() != US_PLAYING) return true;

			//消息处理
			CMD_C_ListenCard * pOperateCard = (CMD_C_ListenCard *)pData;
			return OnUserListenCard(pIServerUserItem->GetChairID(), pOperateCard->bListenCard);
		}
	case SUB_C_TRUSTEE:
		{
			CStringA str;str.Format("\n\t\twSubCmdID:SUB_C_TRUSTEE(%d), wDataSize:%d   ", wSubCmdID, wDataSize);
			OutputDebugStringA(str);
			CMD_C_Trustee *pTrustee =(CMD_C_Trustee *)pData;
			if(wDataSize != sizeof(CMD_C_Trustee)) return false;

			return OnUserTrustee(pIServerUserItem->GetChairID(), pTrustee->bTrustee);
		}
	case SUB_C_REPLACE_CARD:	//用户补牌
		{
			CStringA str;str.Format("\n\t\twSubCmdID:SUB_C_REPLACE_CARD(%d), wDataSize:%d   ", wSubCmdID, wDataSize);
			OutputDebugStringA(str);
			//效验数据
			ASSERT(wDataSize == sizeof(CMD_C_ReplaceCard));
			if (wDataSize != sizeof(CMD_C_ReplaceCard)) return false;
			//用户效验
			if (pIServerUserItem->GetUserStatus() != US_PLAYING) return true;

			//变量定义
			CMD_C_ReplaceCard * pReplaceCard = (CMD_C_ReplaceCard *)pData;

			//消息处理
			bool bResult = OnUserReplaceCard(pIServerUserItem->GetChairID(), pReplaceCard->cbCardData);

			UpdateBaoPaiIfNeed();
			return bResult;
		}

#ifdef  CARD_DISPATCHER_CONTROL
	case SUB_C_SEND_CARD:
		{
			CStringA str;str.Format("\n\t\twSubCmdID:SUB_C_SEND_CARD(%d), wDataSize:%d   ", wSubCmdID, wDataSize);
			OutputDebugStringA(str);
			ASSERT(wDataSize==sizeof(CMD_C_SendCard));
			if(wDataSize!=sizeof(CMD_C_SendCard)) return false;

			CMD_C_SendCard * pSendCard = (CMD_C_SendCard *)pData;
			
			bool bResult = OnUserSendCard(pSendCard->cbCardCount, pSendCard->wBankerUser, pSendCard->cbCardData, pSendCard->cbControlGameCount);

			UpdateBaoPaiIfNeed();
			return bResult;
		}
#endif

	default:
		{
			CStringA str;str.Format("\n\t\twSubCmdID:NO_ACTION(%d), wDataSize:%d   ", wSubCmdID, wDataSize);
			OutputDebugStringA(str);
		}
		break;
	}

	return false;
}

//框架消息
bool CTableFrameSink::OnFrameMessage(WORD wSubCmdID, VOID * pData, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	return false;
}

//用户坐下
bool CTableFrameSink::OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//获取房卡规则
	BYTE* pSetInfo = m_pITableFrame->GetGameRule();
	if(pSetInfo[0] == 1)
	{
		m_tGameCustomRule.cbPlayerCount		= pSetInfo[1];
		m_tGameCustomRule.cbMaCount			= pSetInfo[2];
		m_tGameCustomRule.cbInningsCount_cy	= pSetInfo[3];
		m_tGameCustomRule.bEnabled_DianPao	= pSetInfo[4]!=0;
		m_tGameCustomRule.bEnabled_FengGang	= pSetInfo[5]!=0;
		m_tGameCustomRule.bEnabled_HuiPai	= pSetInfo[6]!=0;
		m_tGameCustomRule.bEnabled_BaoPai	= pSetInfo[7]!=0;
		m_tGameCustomRule.bEnabled_ZhanLiHu	= pSetInfo[8]!=0;
		m_tGameCustomRule.bEnabled_JiaHu		= pSetInfo[9]!=0;
		m_tGameCustomRule.bEnabled_ChangMaoGang = pSetInfo[10]!=0;

		m_GameLogic.SetCustomRule(&m_tGameCustomRule);

		m_cbPlayerCount = m_tGameCustomRule.cbPlayerCount;
		m_cbMaCount = m_tGameCustomRule.cbMaCount;
	}


	//历史积分
	if (bLookonUser==false)
	{
		ASSERT(wChairID!=INVALID_CHAIR);
		m_HistoryScore.OnEventUserEnter(wChairID);
		m_wBankerUser = INVALID_CHAIR;
		m_wLianZhuang = 1;
	}

	return true;
}

//用户起立
bool CTableFrameSink::OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//历史积分
	if (bLookonUser==false)
	{
		ASSERT(wChairID!=INVALID_CHAIR);
		m_HistoryScore.OnEventUserLeave(wChairID);
		m_wBankerUser = INVALID_CHAIR;
		m_wLianZhuang = 1;
	}

	if( (m_pGameServiceOption->wServerType&GAME_GENRE_PERSONAL) !=0 )//房卡模式
	{
		if(m_pITableFrame->IsPersonalRoomDisumme() )//当前朋友局解散清理记录
		{
			ZeroMemory(&m_stRecord,sizeof(m_stRecord));
		}
	}

	return true;
}

//用户出牌
bool CTableFrameSink::OnUserOutCard(WORD wChairID, BYTE cbCardData,bool bSysOut/*=false*/)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//效验状态
	ASSERT(m_pITableFrame->GetGameStatus() == GAME_SCENE_PLAY);
	if (m_pITableFrame->GetGameStatus() != GAME_SCENE_PLAY) return true;

	//错误断言
	ASSERT(wChairID == m_wCurrentUser);
	ASSERT(m_GameLogic.IsValidCard(cbCardData));

	//效验参数
	if (wChairID != m_wCurrentUser) return false;
	if (!m_GameLogic.IsValidCard(cbCardData)) return false;

	//删除扑克
 	if (!m_GameLogic.RemoveCard(m_cbCardIndex[wChairID], cbCardData))
 	{
 		ASSERT(FALSE);
 		return false;
 	}

	//清除禁止
	m_bEnjoinChiHu[wChairID] = false;
	m_bEnjoinChiPeng[wChairID] = false;
	m_vecEnjoinChiPeng[wChairID].clear();
	m_vecEnjoinChiHu[wChairID].clear();

	//设置变量
	m_enSendStatus = OutCard_Send;
	m_cbSendCardData = INVAILD_CARD_DATA;
	m_wUserAction[wChairID] = WIK_NULL;
	m_wPerformAction[wChairID] = WIK_NULL;
	m_bUserActionDone=false;
	//出牌记录
	m_wOutCardUser = wChairID;
	m_cbOutCardData = cbCardData;

	//构造数据
	CMD_S_OutCard OutCard;
	OutCard.wOutCardUser = wChairID;
	OutCard.cbOutCardData = cbCardData;
	OutCard.bSysOut=bSysOut;
	//发送消息
	m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_OUT_CARD, &OutCard, sizeof(OutCard));
	m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_OUT_CARD, &OutCard, sizeof(OutCard));

	m_wProvideUser = wChairID;
	m_cbProvideCard = cbCardData;

	//用户切换
	m_wCurrentUser = (wChairID + 1) % m_cbPlayerCount;
	for(int i=0;i<m_cbPlayerCount;i++)
	{
		if(m_bPlayStatus[m_wCurrentUser])
			break;
		m_wCurrentUser = (m_wCurrentUser+1)%m_cbPlayerCount;
	}

	m_cbOutFromHandCount[wChairID]++;

	//响应判断
 	bool bAroseAction = EstimateUserRespond(wChairID, cbCardData, EstimatKind_OutCard); 
	m_bGangOutCard = (m_cbGangStatus!=WIK_GANERAL);

 	//派发扑克
 	if (!bAroseAction) 
	{
		m_cbGangStatus = WIK_GANERAL;
		m_wProvideGangUser = INVALID_CHAIR;
		DispatchCardData(m_wCurrentUser);
	}

	return true;
}

//用户操作
bool CTableFrameSink::OnUserOperateCard(WORD wChairID, WORD wOperateCode, BYTE cbOperateCard[3])
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//效验状态
	ASSERT(m_pITableFrame->GetGameStatus() == GAME_SCENE_PLAY);
	if (m_pITableFrame->GetGameStatus() != GAME_SCENE_PLAY) return true;

	//效验用户 注意：机器人有可能发生此断言
	ASSERT((wChairID == m_wCurrentUser) || (m_wCurrentUser == INVALID_CHAIR));
	if ((wChairID != m_wCurrentUser) && (m_wCurrentUser != INVALID_CHAIR))  return true;

 	//被动动作
 	if (m_wCurrentUser == INVALID_CHAIR)
 	{
 		//效验状态
 		ASSERT(!m_bResponse[wChairID]);
 		ASSERT(m_wUserAction[wChairID] != WIK_NULL);
 		ASSERT((wOperateCode == WIK_NULL) || ((m_wUserAction[wChairID]&wOperateCode) != 0));
 
 		//效验状态
 		if (m_bResponse[wChairID]) return true;
 		if(m_wUserAction[wChairID] == WIK_NULL) return true;
 		if ((wOperateCode!=WIK_NULL) && ((m_wUserAction[wChairID]&wOperateCode) == 0)) return true;
 
 		//设置变量
		m_bEnjoinGang[wChairID] = false;
 		m_bResponse[wChairID] = true;
 		m_wPerformAction[wChairID] = wOperateCode;
 		if(cbOperateCard[0] == INVAILD_CARD_DATA)
		{
			m_cbOperateCard[wChairID][0] = m_cbProvideCard;
		}
 		else 
		{
			CopyMemory(m_cbOperateCard[wChairID], cbOperateCard, sizeof(m_cbOperateCard[wChairID]));
		}

		//变量定义
		WORD wTargetUser = GetBestActionPerformedUser(m_wProvideUser);
		WORD wTargetAction = m_wPerformAction[wTargetUser];

		if( SendOperateNotifyWithRank(m_wProvideUser, wTargetAction) != INVALID_CHAIR ) {
			return true;
		}

		if (wTargetAction == WIK_NULL){
			//用户状态
			ZeroMemory(m_bResponse, sizeof(m_bResponse));
			ZeroMemory(m_wUserAction, sizeof(m_wUserAction));
			ZeroMemory(m_cbOperateCard, sizeof(m_cbOperateCard));
			ZeroMemory(m_wPerformAction, sizeof(m_wPerformAction));

			DispatchCardData(m_wResumeUser,m_cbGangStatus != WIK_GANERAL);
			return true;
		}
 
 		//变量定义
 		BYTE cbTargetCard = m_cbOperateCard[wTargetUser][0];
 
 		//出牌变量
 		m_enSendStatus = Gang_Send;
		m_cbSendCardData = INVAILD_CARD_DATA;
 		m_wOutCardUser = INVALID_CHAIR;
		m_cbOutCardData = INVAILD_CARD_DATA;
 
 		//胡牌操作
 		if (wTargetAction == WIK_CHI_HU)
 		{
 			//结束信息
 			m_cbChiHuCard = cbTargetCard;
 
			WORD wChiHuUser = wTargetUser;
			for(int i = 0; i < m_cbPlayerCount; i++)
 			{
 				wChiHuUser = (wTargetUser + i) % m_cbPlayerCount;
				//过虑判断
 				if ((m_wPerformAction[wChiHuUser]&WIK_CHI_HU) == 0)
 					continue;
 
 				//胡牌判断
 				BYTE cbWeaveItemCount = m_cbWeaveItemCount[wChiHuUser];
 				tagWeaveItem * pWeaveItem = m_WeaveItemArray[wChiHuUser];
 				m_dwChiHuKind[wChiHuUser] = m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[wChiHuUser], pWeaveItem, cbWeaveItemCount, m_cbChiHuCard, m_ChiHuRight[wChiHuUser]);

 				//插入扑克
 				if (m_dwChiHuKind[wChiHuUser] != WIK_NORMAL) 
 				{
 					wTargetUser = wChiHuUser;
					break;
 				}
 			}
			
			BYTE cbArrQiangGang[] = {WIK_BU_GANG,WIK_CHASE_WND_GANG,WIK_CHASE_ARW_GANG};
			if( m_bGangOutCard
				&& ExistInArray(m_cbGangStatus ,cbArrQiangGang, CountArray(cbArrQiangGang)) 
				&& wChairID!=m_wProvideUser){
				ASSERT(m_wProvideUser!=INVALID_CHAIR);
				processQiangGangHu(m_cbGangStatus, wChairID, m_wProvideUser);
			}
 
 			//结束游戏
 			ASSERT(m_dwChiHuKind[wTargetUser] != WIK_NORMAL);
 			OnEventGameConclude(wTargetUser, NULL, GER_NORMAL);
 
 			return true;
 		}
 
 		//组合扑克
 		ASSERT(m_cbWeaveItemCount[wTargetUser] < MAX_WEAVE);
 		WORD wIndex = m_cbWeaveItemCount[wTargetUser]++;
 		m_WeaveItemArray[wTargetUser][wIndex].cbParam = WIK_GANERAL;
 		m_WeaveItemArray[wTargetUser][wIndex].cbCenterCard = cbTargetCard;
 		m_WeaveItemArray[wTargetUser][wIndex].wWeaveKind = wTargetAction;
 		m_WeaveItemArray[wTargetUser][wIndex].wProvideUser = (m_wProvideUser == INVALID_CHAIR) ? wTargetUser : m_wProvideUser;
 		m_WeaveItemArray[wTargetUser][wIndex].cbCardData[0] = cbTargetCard;
 		if(wTargetAction&(WIK_LEFT | WIK_CENTER | WIK_RIGHT))
 		{
 			m_WeaveItemArray[wTargetUser][wIndex].cbCardData[1] = m_cbOperateCard[wTargetUser][1];
 			m_WeaveItemArray[wTargetUser][wIndex].cbCardData[2] = m_cbOperateCard[wTargetUser][2];
 		}
 		else
 		{
 			m_WeaveItemArray[wTargetUser][wIndex].cbCardData[1] = cbTargetCard;
 			m_WeaveItemArray[wTargetUser][wIndex].cbCardData[2] = cbTargetCard;
 			if(wTargetAction & WIK_GANG)
			{
				m_WeaveItemArray[wTargetUser][wIndex].cbParam = WIK_MING_GANG;
				m_WeaveItemArray[wTargetUser][wIndex].cbCardData[3] = cbTargetCard;
			}
 		}
 
 		//删除扑克
 		switch (wTargetAction)
 		{
 		case WIK_LEFT:		//上牌操作
 			{
 				//删除扑克
 				if(!m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser], &m_cbOperateCard[wTargetUser][1], 2))
 				{
 					ASSERT(FALSE);
 					return false;
 				}
				m_cbChiPengCount[wTargetUser]++;
 
 				break;
 			}
 		case WIK_RIGHT:		//上牌操作
 			{
 				//删除扑克
 				if(!m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser], &m_cbOperateCard[wTargetUser][1], 2))
 				{
 					ASSERT(FALSE);
 					return false;
 				}
				m_cbChiPengCount[wTargetUser]++;
 
 				break;
 			}
 		case WIK_CENTER:	//上牌操作
 			{
 				//删除扑克
 				if(!m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser], &m_cbOperateCard[wTargetUser][1], 2))
 				{
 					ASSERT(FALSE);
 					return false;
 				}
				m_cbChiPengCount[wTargetUser]++;
 
 				break;
 			}
 		case WIK_PENG:		//碰牌操作
 			{
 				//删除扑克
 				BYTE cbRemoveCard[] = {cbTargetCard,cbTargetCard};
 				if(!m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser], cbRemoveCard, 2))
 				{
 					ASSERT(FALSE);
 					return false;
 				}
				m_cbChiPengCount[wTargetUser]++;

 				break;
 			}
 		case WIK_GANG:		//杠牌操作
 			{
 				//删除扑克,被动动作只存在放杠
 				BYTE cbRemoveCard[] = {cbTargetCard, cbTargetCard, cbTargetCard};
 				if(!m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser], cbRemoveCard, CountArray(cbRemoveCard)))
 				{
 					ASSERT(FALSE);
 					return false;
 				}
 
 				break;
 			}
 		default:
 			ASSERT(FALSE);
 			return false;
 		}
 
 		//构造结果
 		CMD_S_OperateResult OperateResult;
 		ZeroMemory(&OperateResult, sizeof(OperateResult));
 		OperateResult.wOperateUser = wTargetUser;
 		OperateResult.wOperateCode = wTargetAction;
 		OperateResult.wProvideUser = (m_wProvideUser == INVALID_CHAIR) ? wTargetUser : m_wProvideUser;
 		OperateResult.cbOperateCard[0] = cbTargetCard;
 		if(wTargetAction & (WIK_LEFT | WIK_CENTER | WIK_RIGHT))
		{
			CopyMemory(&OperateResult.cbOperateCard[1], &m_cbOperateCard[wTargetUser][1], 2 * sizeof(BYTE));
		}
 		else if(wTargetAction&WIK_PENG)
 		{
 			OperateResult.cbOperateCard[1] = cbTargetCard;
 			OperateResult.cbOperateCard[2] = cbTargetCard;
 		}
 
 		//用户状态
 		ZeroMemory(m_bResponse, sizeof(m_bResponse));
 		ZeroMemory(m_wUserAction, sizeof(m_wUserAction));
 		ZeroMemory(m_cbOperateCard, sizeof(m_cbOperateCard));
 		ZeroMemory(m_wPerformAction, sizeof(m_wPerformAction));
 
 		//如果非杠牌
 		if(wTargetAction != WIK_GANG)
 		{
			BYTE cbLastCard = m_cbProvideCard;
			WORD wLastProvider = m_wProvideUser;
			m_wProvideUser = INVALID_CHAIR;
			m_cbProvideCard = INVAILD_CARD_DATA;

			if(m_bTing[wTargetUser] == false)
			{
				BYTE cbCount = 0;
				CMD_S_Hu_Data HuData;
				ZeroMemory(&HuData,sizeof(HuData));
				cbCount =m_GameLogic.AnalyseTingCard(m_cbCardIndex[wTargetUser],m_WeaveItemArray[wTargetUser],m_cbWeaveItemCount[wTargetUser],HuData.cbOutCardCount,HuData.cbOutCardData,HuData.cbHuCardCount,HuData.cbHuCardData);
				if(cbCount >0)
				{
					//m_wUserAction[wTargetUser] |= WIK_LISTEN; 

					for(int i=0;i<MAX_COUNT;i++)
					{
						if(HuData.cbHuCardCount[i]>0)
						{
							for(int j=0;j<HuData.cbHuCardCount[i];j++)
							{
								HuData.cbHuCardRemainingCount[i][j] = GetRemainingCount(wTargetUser,HuData.cbHuCardData[i][j]);
							}
						}
						else
							break;
					}
					m_pITableFrame->SendTableData(wTargetUser,SUB_S_HU_CARD,&HuData,sizeof(HuData));
				}

				// This is for Checking Hu status after peng/chi operation
				/*if(wTargetAction&(WIK_LEFT|WIK_CENTER|WIK_RIGHT|WIK_PENG)){
					ASSERT(cbLastCard!=INVAILD_CARD_DATA);
					if( cbLastCard != INVAILD_CARD_DATA) {
						CChiHuRight chr;
						BYTE huResult = m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[wTargetUser],m_WeaveItemArray[wTargetUser],m_cbWeaveItemCount[wTargetUser], INVAILD_CARD_DATA,chr);
						if( WIK_CHI_HU == huResult ){
							m_wUserAction[wTargetUser] |= huResult;

							m_wProvideUser = wLastProvider;
							m_cbProvideCard = cbLastCard;
							m_cbChiHuCard = cbLastCard;
							m_cbSendCardData = cbLastCard;
						}
					}
				}*/
			}
 			OperateResult.wActionMask |= m_wUserAction[wTargetUser];
 		}

		PrepareOperateResult(OperateResult);
 		//发送消息
 		m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_OPERATE_RESULT, &OperateResult, sizeof(OperateResult));
 		m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_OPERATE_RESULT, &OperateResult, sizeof(OperateResult));
 
 		//设置用户
 		m_wCurrentUser = wTargetUser;
		m_cbGangStatus = WIK_GANERAL;
 
 		//杠牌处理
 		if (wTargetAction == WIK_GANG)
 		{
 			m_cbGangStatus = WIK_MING_GANG;
			m_wProvideGangUser = (m_wProvideUser == INVALID_CHAIR) ? wTargetUser : m_wProvideUser;
			m_cbGangCount[wTargetUser]++;
 			DispatchCardData(wTargetUser, true);
		}

 		return true;
 	}
 
 	//主动动作
 	if (m_wCurrentUser == wChairID)
 	{
 		//效验操作
 		//ASSERT((cbOperateCode != WIK_NULL) && ((m_cbUserAction[wChairID]&cbOperateCode) != 0));
 		//if ((cbOperateCode == WIK_NULL) || ((m_cbUserAction[wChairID]&cbOperateCode) == 0)) return false;
 
 		//扑克效验
 		ASSERT((wOperateCode == WIK_NULL) || (wOperateCode == WIK_CHI_HU) || (m_GameLogic.IsValidCard(cbOperateCard[0])));
 		if ((wOperateCode != WIK_NULL) && (wOperateCode != WIK_CHI_HU) && (!m_GameLogic.IsValidCard(cbOperateCard[0]))) return false;
 
 		//设置变量
 		m_wUserAction[m_wCurrentUser] = WIK_NULL;
 		m_wPerformAction[m_wCurrentUser] = WIK_NULL;
 
 		//执行动作
 		switch (wOperateCode)
 		{
 		case WIK_GANG:			//杠牌操作
 			{
				m_enSendStatus = Gang_Send;

 				//变量定义
 				BYTE cbWeaveIndex = INVAILD_CARD_INDEX;
 				BYTE cbCardIndex = m_GameLogic.SwitchToCardIndex(cbOperateCard[0]);
				WORD wProvideUser = wChairID;
				BYTE cbGangKind = WIK_BU_GANG;
 				//杠牌处理
 				if (m_cbCardIndex[wChairID][cbCardIndex] == 1)
 				{
 					//寻找组合
 					for (BYTE i = 0; i < m_cbWeaveItemCount[wChairID]; i++)
 					{
 						WORD wWeaveKind = m_WeaveItemArray[wChairID][i].wWeaveKind;
 						BYTE cbCenterCard = m_WeaveItemArray[wChairID][i].cbCenterCard;
 						if ((cbCenterCard == cbOperateCard[0]) && (wWeaveKind == WIK_PENG))
 						{
 							cbWeaveIndex = i;
 							break;
 						}
 					}
 
 					//效验动作
 					ASSERT(cbWeaveIndex != INVAILD_CARD_INDEX);
 					if (cbWeaveIndex == INVAILD_CARD_INDEX) return false;
 
					cbGangKind = WIK_BU_GANG;

 					//组合扑克
 					m_WeaveItemArray[wChairID][cbWeaveIndex].cbParam = WIK_BU_GANG;
 					m_WeaveItemArray[wChairID][cbWeaveIndex].wWeaveKind = wOperateCode;
 					m_WeaveItemArray[wChairID][cbWeaveIndex].cbCenterCard = cbOperateCard[0];
 					m_WeaveItemArray[wChairID][cbWeaveIndex].cbCardData[3] = cbOperateCard[0];
 
 					//杠牌得分
 					wProvideUser = m_WeaveItemArray[wChairID][cbWeaveIndex].wProvideUser;
 				}
 				else
 				{
 					//扑克效验
 					ASSERT(m_cbCardIndex[wChairID][cbCardIndex] == 4);
 					if (m_cbCardIndex[wChairID][cbCardIndex] != 4) 
 						return false;
 
 					//设置变量
 					cbGangKind = WIK_AN_GANG;
 					cbWeaveIndex = m_cbWeaveItemCount[wChairID]++;
 					m_WeaveItemArray[wChairID][cbWeaveIndex].cbParam = WIK_AN_GANG;
 					m_WeaveItemArray[wChairID][cbWeaveIndex].wProvideUser = wChairID;
 					m_WeaveItemArray[wChairID][cbWeaveIndex].wWeaveKind = wOperateCode;
 					m_WeaveItemArray[wChairID][cbWeaveIndex].cbCenterCard = cbOperateCard[0];
 					for(BYTE j = 0; j < 4; j++) 
					{
						m_WeaveItemArray[wChairID][cbWeaveIndex].cbCardData[j] = cbOperateCard[0];
					}
 				}
 
 				//删除扑克
 				m_cbCardIndex[wChairID][cbCardIndex] = 0;
				m_cbGangStatus = cbGangKind;
				m_wProvideGangUser = wProvideUser;
				m_cbGangCount[wChairID]++;
 
 				//构造结果
 				CMD_S_OperateResult OperateResult;
 				ZeroMemory(&OperateResult, sizeof(OperateResult));
 				OperateResult.wOperateUser = wChairID;
 				OperateResult.wProvideUser = wProvideUser;
 				OperateResult.wOperateCode = wOperateCode;
 				OperateResult.cbOperateCard[0] = cbOperateCard[0];
 
				PrepareOperateResult(OperateResult);
 				//发送消息
 				m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_OPERATE_RESULT, &OperateResult, sizeof(OperateResult));
 				m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_OPERATE_RESULT, &OperateResult, sizeof(OperateResult));

 				//效验动作
 				bool bAroseAction = false;
 				if (m_cbGangStatus == WIK_BU_GANG ) 
				{
					bAroseAction=EstimateUserRespond(wChairID, cbOperateCard[0], EstimatKind_GangCard);
				}
 
 				//发送扑克
 				if (!bAroseAction)
 				{
 					DispatchCardData(wChairID, true);
 				}
 
 				return true;
 			}

		case WIK_WIND:			//东南西北
			{
				m_enSendStatus = Gang_Send;

				//变量定义
				BYTE cbWeaveIndex;

				//扑克效验
				ASSERT(m_GameLogic.IsSpGangOK(m_cbCardIndex[wChairID], WIK_WIND));
				if (!m_GameLogic.IsSpGangOK(m_cbCardIndex[wChairID], WIK_WIND)) 
					return false;

				//设置变量
				cbWeaveIndex = m_cbWeaveItemCount[wChairID]++;
				m_WeaveItemArray[wChairID][cbWeaveIndex].cbParam = WIK_WND_GANG;
				m_WeaveItemArray[wChairID][cbWeaveIndex].wProvideUser = wChairID;
				m_WeaveItemArray[wChairID][cbWeaveIndex].wWeaveKind = wOperateCode;
				m_WeaveItemArray[wChairID][cbWeaveIndex].cbCenterCard = 0x31;
				m_WeaveItemArray[wChairID][cbWeaveIndex].cbCardData[0] = 0x31;
				m_WeaveItemArray[wChairID][cbWeaveIndex].cbCardData[1] = 0x32;
				m_WeaveItemArray[wChairID][cbWeaveIndex].cbCardData[2] = 0x33;
				m_WeaveItemArray[wChairID][cbWeaveIndex].cbCardData[3] = 0x34;

				//删除扑克
				m_GameLogic.TakeOutSpGang(m_cbCardIndex[wChairID], WIK_WIND);
				m_cbGangStatus = WIK_WND_GANG;
				m_wProvideGangUser = wChairID;
				m_cbGangCount[wChairID]++;

				//构造结果
				CMD_S_OperateResult OperateResult;
				ZeroMemory(&OperateResult, sizeof(OperateResult));
				OperateResult.wOperateUser = wChairID;
				OperateResult.wProvideUser = wChairID;
				OperateResult.wOperateCode = wOperateCode;
				OperateResult.cbOperateCard[0] = cbOperateCard[0];

				//发送消息
				PrepareOperateResult(OperateResult);

				m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_OPERATE_RESULT, &OperateResult, sizeof(OperateResult));
				m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_OPERATE_RESULT, &OperateResult, sizeof(OperateResult));

				//发送扑克
				DispatchCardData(wChairID, true);

				return true;
			}

		case WIK_ARROW:			//中发白
			{
				m_enSendStatus = Gang_Send;

				//变量定义
				BYTE cbWeaveIndex;

				//扑克效验
				ASSERT(m_GameLogic.IsSpGangOK(m_cbCardIndex[wChairID], WIK_ARROW));
				if (!m_GameLogic.IsSpGangOK(m_cbCardIndex[wChairID], WIK_ARROW)) 
					return false;

				//设置变量
				cbWeaveIndex = m_cbWeaveItemCount[wChairID]++;
				m_WeaveItemArray[wChairID][cbWeaveIndex].cbParam = WIK_ARW_GANG;
				m_WeaveItemArray[wChairID][cbWeaveIndex].wProvideUser = wChairID;
				m_WeaveItemArray[wChairID][cbWeaveIndex].wWeaveKind = wOperateCode;
				m_WeaveItemArray[wChairID][cbWeaveIndex].cbCenterCard = 0x35;
				m_WeaveItemArray[wChairID][cbWeaveIndex].cbCardData[0] = 0x35;
				m_WeaveItemArray[wChairID][cbWeaveIndex].cbCardData[1] = 0x36;
				m_WeaveItemArray[wChairID][cbWeaveIndex].cbCardData[2] = 0x37;

				//删除扑克
				m_GameLogic.TakeOutSpGang(m_cbCardIndex[wChairID], WIK_ARROW);
				m_cbGangStatus = WIK_ARW_GANG;
				m_cbGangCount[wChairID]++;

				tagGangCardResult gcr;
				m_wUserAction[wChairID] |= m_GameLogic.AnalyseGangCardEx(m_cbCardIndex[wChairID], m_WeaveItemArray[wChairID], m_cbWeaveItemCount[wChairID],0, gcr, m_cbOutFromHandCount[wChairID]);

				//构造结果
				CMD_S_OperateResult OperateResult;
				ZeroMemory(&OperateResult, sizeof(OperateResult));
				OperateResult.wOperateUser = wChairID;
				OperateResult.wProvideUser = wChairID;
				OperateResult.wOperateCode = wOperateCode;
				OperateResult.cbOperateCard[0] = cbOperateCard[0];
				OperateResult.wActionMask |= m_wUserAction[wChairID];

				//发送消息
				PrepareOperateResult(OperateResult);

				m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_OPERATE_RESULT, &OperateResult, sizeof(OperateResult));
				m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_OPERATE_RESULT, &OperateResult, sizeof(OperateResult));

				DispatchCardData(wChairID, true);

				return true;
			}

		case WIK_CHASEWIND:		//东南西北 长毛杠（风）
			{
				m_enSendStatus = Gang_Send;
				//变量定义
				BYTE cbCardIndex = m_GameLogic.SwitchToCardIndex(cbOperateCard[0]);
				//扑克效验
				if (!m_GameLogic.IsChaseArrow(cbCardIndex, m_WeaveItemArray[wChairID],MAX_WEAVE,WIK_CHASEWIND)) {
					ASSERT(FALSE);
					return false;
				}
				ASSERT(0x31<=cbOperateCard[0] && cbOperateCard[0]<=0x34);
				if (cbOperateCard[0]<0x31 || cbOperateCard[0]>0x34) 
				{
					return false;
				}
				//设置变量
				m_cbChaseArrowArray[wChairID][m_nChaseArrowCount[wChairID]++] = cbOperateCard[0];
				m_cbChaseRemainCard[wChairID][cbOperateCard[0]-0x31]++;

				//删除扑克
				m_GameLogic.TakeOutCHMGang(m_cbCardIndex[wChairID],cbOperateCard[0]);
				m_cbGangStatus = WIK_CHASE_WND_GANG;
				m_wProvideGangUser = wChairID;

				//构造结果
				CMD_S_OperateResult OperateResult;
				ZeroMemory(&OperateResult, sizeof(OperateResult));
				OperateResult.wOperateUser = wChairID;
				OperateResult.wProvideUser = wChairID;
				OperateResult.wOperateCode = wOperateCode;
				OperateResult.cbOperateCard[0] = cbOperateCard[0];

				//发送消息
				PrepareOperateResult(OperateResult);

				m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_OPERATE_RESULT, &OperateResult, sizeof(OperateResult));
				m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_OPERATE_RESULT, &OperateResult, sizeof(OperateResult));

				//效验动作
				bool bAroseAction = false;
				bAroseAction=EstimateUserRespond(wChairID, cbOperateCard[0], EstimatKind_GangCard);

				//发送扑克
				if (!bAroseAction)
				{
					DispatchCardData(wChairID, true);
				}

				return true;
			}

		case WIK_CHASEARROW:			//中发白【长毛杠】
			{
				m_enSendStatus = Gang_Send;
				//变量定义
				BYTE cbCardIndex = m_GameLogic.SwitchToCardIndex(cbOperateCard[0]);
				
				//扑克效验
				if (!m_GameLogic.IsChaseArrow(cbCardIndex, m_WeaveItemArray[wChairID],MAX_WEAVE,WIK_CHASEARROW)) {
					ASSERT(FALSE);
					return false;
				}

				ASSERT(0x35<=cbOperateCard[0] && cbOperateCard[0]<=0x37);
				if (cbOperateCard[0]<0x35 || cbOperateCard[0]>0x37) {
					return false;
				}
				//设置变量
				m_cbChaseArrowArray[wChairID][m_nChaseArrowCount[wChairID]++] = cbOperateCard[0];
				m_cbChaseRemainCard[wChairID][cbOperateCard[0]-0x31]++;

				//删除扑克
				m_GameLogic.TakeOutCHMGang(m_cbCardIndex[wChairID],cbOperateCard[0]);
				m_cbGangStatus = WIK_CHASE_ARW_GANG;
				m_wProvideGangUser = wChairID;


				//构造结果
				CMD_S_OperateResult OperateResult;
				ZeroMemory(&OperateResult, sizeof(OperateResult));
				OperateResult.wOperateUser = wChairID;
				OperateResult.wProvideUser = wChairID;
				OperateResult.wOperateCode = wOperateCode;
				OperateResult.cbOperateCard[0] = cbOperateCard[0];

				//发送消息
				PrepareOperateResult(OperateResult);

				m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_OPERATE_RESULT, &OperateResult, sizeof(OperateResult));
				m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_OPERATE_RESULT, &OperateResult, sizeof(OperateResult));

				//效验动作
				bool bAroseAction = false;
				bAroseAction=EstimateUserRespond(wChairID, cbOperateCard[0], EstimatKind_GangCard);

				//发送扑克
				if (!bAroseAction)
				{
					DispatchCardData(wChairID, true);
				}

				return true;
			}

 		case WIK_CHI_HU:		//自摸
 			{
 				//普通胡牌
 				BYTE cbWeaveItemCount = m_cbWeaveItemCount[wChairID];
 				tagWeaveItem * pWeaveItem = m_WeaveItemArray[wChairID];

				m_cbCardIndex[wChairID][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]--;
				m_dwChiHuKind[wChairID] = m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[wChairID], pWeaveItem, cbWeaveItemCount, m_cbSendCardData, m_ChiHuRight[wChairID]);
				m_cbCardIndex[wChairID][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]++;
 
 				//结束信息
				m_cbChiHuCard = m_cbSendCardData;
				m_cbProvideCard = m_cbSendCardData;
				
 				//结束游戏
 				OnEventGameConclude(wChairID, NULL, GER_NORMAL);
 
 				return true;
 			}
 		}
 
 		return true;
 	}

	return false;
}


//用户听牌
bool CTableFrameSink::OnUserListenCard(WORD wChairID, bool bListenCard)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	if(bListenCard)
	{
		ASSERT(!m_bTing[wChairID]);
		if(WIK_LISTEN == m_GameLogic.AnalyseTingCard(m_cbCardIndex[wChairID], m_WeaveItemArray[wChairID], m_cbWeaveItemCount[wChairID]))
		{
			bool bTing = m_GameLogic.isPossibleTing(m_cbCardIndex[wChairID], m_WeaveItemArray[wChairID], m_cbWeaveItemCount[wChairID]);
			ASSERT(bTing);
			if( !bTing ) return false;

			m_bTing[wChairID] = true;
			CMD_S_ListenCard ListenCard;
			ZeroMemory(&ListenCard,sizeof(ListenCard));

			ListenCard.wListenUser = wChairID;
			ListenCard.bListen = true;
			//发给消息
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_LISTEN_CARD,&ListenCard,sizeof(ListenCard));
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_LISTEN_CARD,&ListenCard,sizeof(ListenCard));

			//for(int i=0;i<m_cbPlayerCount;i++)
			//{
			//	if( i != wChairID)
			//		m_pITableFrame->SendTableData(i,SUB_S_LISTEN_CARD,&ListenCard,sizeof(ListenCard));
			//}

			//计算胡几张字
			//m_cbHuCardCount[wChairID] = m_GameLogic.GetHuCard(m_cbCardIndex[wChairID],m_WeaveItemArray[wChairID],m_cbWeaveItemCount[wChairID],m_cbHuCardData[wChairID]);
			//ASSERT(m_cbHuCardCount[wChairID]>0);
			//ListenCard.cbHuCardCount = m_cbHuCardCount[wChairID];
			//CopyMemory(ListenCard.cbHuCardData,m_cbHuCardData[wChairID],sizeof(ListenCard.cbHuCardData));

			//m_pITableFrame->SendTableData(wChairID,SUB_S_LISTEN_CARD,&ListenCard,sizeof(ListenCard));

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{

		ASSERT(m_bTing[wChairID]);
		m_bTing[wChairID] = false;

		CMD_S_ListenCard ListenCard;
		ListenCard.wListenUser = wChairID;
		ListenCard.bListen = false;

		//发送消息
		m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_LISTEN_CARD, &ListenCard, sizeof(ListenCard));
		m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_LISTEN_CARD, &ListenCard, sizeof(ListenCard));
		return true;
	}
}

//用户托管
bool CTableFrameSink::OnUserTrustee(WORD wChairID, bool bTrustee)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//效验状态
	ASSERT((wChairID < m_cbPlayerCount));
	if ((wChairID>=m_cbPlayerCount)) return false;

	m_bTrustee[wChairID]=bTrustee;

	CMD_S_Trustee Trustee;
	Trustee.bTrustee=bTrustee;
	Trustee.wChairID = wChairID;
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_TRUSTEE,&Trustee,sizeof(Trustee));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_TRUSTEE,&Trustee,sizeof(Trustee));

	if(bTrustee)
	{
		if(wChairID == m_wCurrentUser && m_bUserActionDone==false)
		{
			BYTE cardindex=MAX_INDEX;
			if(m_cbSendCardData != INVAILD_CARD_DATA && m_GameLogic.SwitchToCardIndex(m_cbSendCardData) != m_cbMagicIndex)
				cardindex = m_GameLogic.SwitchToCardIndex(m_cbSendCardData);
			else
			{
				for(int i=0;i<MAX_INDEX;i++)
				{
					if(m_cbCardIndex[wChairID][i]>0 && i !=m_cbMagicIndex)
					{
						cardindex = i;
						break;
					}
				}
			}

			ASSERT(cardindex != INVAILD_CARD_INDEX);
			OnUserOutCard(wChairID,m_GameLogic.SwitchToCardData(cardindex),true);
		}
		else if(m_wCurrentUser == INVALID_CHAIR && m_bUserActionDone==false)
		{
			BYTE operatecard[3]={0};
			OnUserOperateCard(wChairID,WIK_NULL,operatecard);
		}
	}

	return true;
}

//用户补牌
bool CTableFrameSink::OnUserReplaceCard(WORD wChairID, BYTE cbCardData)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//错误断言
	ASSERT(m_GameLogic.IsValidCard(cbCardData));
	//效验参数
	if(!m_GameLogic.IsValidCard(cbCardData))  return false;

	//删除扑克
	if (m_GameLogic.RemoveCard(m_cbCardIndex[wChairID], cbCardData)==false)
	{
		ASSERT(FALSE);
		return false;
	}

	//状态变量
	m_enSendStatus = BuHua_Send;
	m_cbGangStatus = WIK_GANERAL;
	m_wProvideGangUser = INVALID_CHAIR;

	//构造数据
	CMD_S_ReplaceCard ReplaceCard;
	ReplaceCard.wReplaceUser = wChairID;
	ReplaceCard.cbReplaceCard = cbCardData;

	//发送消息
	m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_REPLACE_CARD, &ReplaceCard, sizeof(ReplaceCard));
	m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_REPLACE_CARD, &ReplaceCard, sizeof(ReplaceCard));

	//派发扑克
	DispatchCardData(wChairID, true);

	return true;
}

//发送扑克
bool CTableFrameSink::OnUserSendCard(BYTE cbCardCount, WORD wBankerUser, BYTE cbCardData[], BYTE cbControlGameCount)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
#ifdef  CARD_DISPATCHER_CONTROL
	ASSERT(cbCardCount == MAX_REPERTORY && wBankerUser < GAME_PLAYER);
	if(cbCardCount != MAX_REPERTORY || wBankerUser >= GAME_PLAYER) return false;

	//设置控制局数
	m_cbControlGameCount = cbControlGameCount;

	m_wControBankerUser = wBankerUser;

	//拷贝控制扑克
	CopyMemory(m_cbControlRepertoryCard, cbCardData, sizeof(m_cbControlRepertoryCard));
#endif
	return true;
}

//发送操作结果
void CTableFrameSink::PrepareOperateResult(CMD_S_OperateResult &OperateResult)
{
	if (OperateResult.wOperateUser<GAME_PLAYER)
	{
		//OperateResult.cbResultWeaveCount = m_cbWeaveItemCount[OperateResult.wOperateUser];
		CopyMemory(OperateResult.cbChaseArrowArray, m_cbChaseArrowArray[OperateResult.wOperateUser], sizeof(OperateResult.cbChaseArrowArray));
	}
}

//发送操作
bool CTableFrameSink::SendOperateNotify()
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//发送提示
	for (WORD i=0;i<m_cbPlayerCount;i++)
	{
		WORD userIndex = (i+m_wProvideUser+1)%GAME_PLAYER;
		if( m_wUserAction[userIndex] != WIK_NULL)
		{
			//构造数据
			CMD_S_OperateNotify OperateNotify;
			OperateNotify.cbActionCard=m_cbProvideCard;
			OperateNotify.wActionMask=m_wUserAction[userIndex];

			//发送数据
			m_pITableFrame->SendTableData(userIndex,SUB_S_OPERATE_NOTIFY,&OperateNotify,sizeof(OperateNotify));
			m_pITableFrame->SendLookonData(userIndex,SUB_S_OPERATE_NOTIFY,&OperateNotify,sizeof(OperateNotify));
			
// 			if(m_bTrustee[i])
// 			{
// 				m_pITableFrame->SetGameTimer(IDI_OPERATE_CARD+i,1000,1,0);
// 			}
		}
	}

	return true;
}


WORD CTableFrameSink::GetBestActionPerformedUser(WORD cbProvider)
{
	WORD wBestUser = INVALID_CHAIR;
	WORD wBestAction = WIK_NULL;
	//执行判断
	for (WORD i = 0; i < m_cbPlayerCount; i++)
	{
		WORD k = (i+cbProvider+1)%GAME_PLAYER;
		if( k == cbProvider ) continue;

		if( m_bResponse[k] ){
			//获取动作
			WORD wUserAction = m_wPerformAction[k];

			//优先级别
			BYTE cbUserActionRank = m_GameLogic.GetUserActionRank(wUserAction);
			BYTE cbTargetActionRank = m_GameLogic.GetUserActionRank(wBestAction);

			//动作判断
			if (cbUserActionRank > cbTargetActionRank) {
				wBestUser = k;
				wBestAction = wUserAction;
			}
		}
	}
	return wBestUser;
}

//Send the Operate Notificatoin for Best rank users
WORD CTableFrameSink::SendOperateNotifyWithRank(WORD cbProvider, WORD cbTargetAction)
{
	int bestRank = m_GameLogic.GetUserActionRank(cbTargetAction);
	WORD wBestUser = INVALID_CHAIR;
	//发送提示
	for (WORD i=0;i<m_cbPlayerCount;i++)
	{
		WORD userIndex = (i+cbProvider+1)%GAME_PLAYER;
		if( userIndex == cbProvider ) continue;

		BYTE cbAction = m_bResponse[userIndex] ? m_wPerformAction[userIndex] : m_wUserAction[userIndex];
		int rank = m_GameLogic.GetUserActionRank(cbAction);
		if( rank > bestRank ){
			bestRank = rank;
			wBestUser = userIndex;
		} else if( rank == bestRank && wBestUser == INVALID_CHAIR){
			wBestUser = userIndex;
		}
	}

	ASSERT(wBestUser!=INVALID_CHAIR);
	if( wBestUser == INVALID_CHAIR) return INVALID_CHAIR;

	if( !m_bResponse[wBestUser] ){
		//构造数据
		CMD_S_OperateNotify OperateNotify;
		OperateNotify.cbActionCard=m_cbProvideCard;
		OperateNotify.wActionMask=m_wUserAction[wBestUser];

		//发送数据
		m_pITableFrame->SendTableData(wBestUser,SUB_S_OPERATE_NOTIFY,&OperateNotify,sizeof(OperateNotify));
		m_pITableFrame->SendLookonData(wBestUser,SUB_S_OPERATE_NOTIFY,&OperateNotify,sizeof(OperateNotify));

		return wBestUser;
	}

	return INVALID_CHAIR;
}


//
bool CTableFrameSink::SendUpdateBaopaiNotify()
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);

	for (WORD i=0;i<m_cbPlayerCount;i++)
	{
		CMD_S_OperateNotify OperateNotify;
		OperateNotify.cbActionCard=0;
		OperateNotify.wActionMask=WIK_UPDATE_BAO;

		m_pITableFrame->SendTableData(i,SUB_S_OPERATE_NOTIFY,&OperateNotify,sizeof(OperateNotify));
		m_pITableFrame->SendLookonData(i,SUB_S_OPERATE_NOTIFY,&OperateNotify,sizeof(OperateNotify));
	}

	return true;
}

BYTE CTableFrameSink::CreateNewBaopaiIndex()
{
	if( m_tGameCustomRule.bEnabled_BaoPai ){
		BYTE magicCard = m_cbMagicIndex<MAX_INDEX ? m_GameLogic.SwitchToCardData(m_cbMagicIndex) : INVAILD_CARD_DATA;
		for(int i=m_cbMinusLastCount; i<CountArray(m_cbRepertoryCard); i++){
			if( magicCard != m_cbRepertoryCard[i] ) break;            
		}
		if( i != m_cbMinusLastCount){
			magicCard = m_cbRepertoryCard[i];
			m_cbRepertoryCard[i] = m_cbRepertoryCard[m_cbMinusLastCount];
			m_cbRepertoryCard[m_cbMinusLastCount] = magicCard;
		}

		BYTE cardData;
		if( m_wHeapHead != INVALID_CHAIR && m_wHeapTail != INVALID_CHAIR){
			cardData = GetSendCard(true);
		} else {

			m_cbLeftCardCount--;
			cardData = m_cbRepertoryCard[m_cbMinusLastCount++];
		}
		return m_GameLogic.SwitchToCardIndex(cardData);

	} else {
		return INVAILD_CARD_INDEX;
	}
}

bool CTableFrameSink::UpdateBaoPaiIfNeed(){
	if( m_tGameCustomRule.bEnabled_BaoPai && !CheckBaopaiExist() ){

		m_cbBaoPaiIndex = CreateNewBaopaiIndex();
		m_GameLogic.SetBaopaiIndex(m_cbBaoPaiIndex);
		CString str; str.Format(_T("\n\t\t Updated Baopai index: %d(0x%02x)"), m_cbBaoPaiIndex, m_GameLogic.SwitchToCardData(m_cbBaoPaiIndex));
		OutputDebugString(str);
		CTraceService::TraceString((LPCTSTR)str,TraceLevel_Debug);
		SendUpdateBaopaiNotify();
		return true;
	}

	return false;
}

bool CTableFrameSink::CheckBaopaiExist(){
	int nBaoCount = 0;

	if( m_cbBaoPaiIndex >= MAX_INDEX)
		return false;

	BYTE baoPaiCard;
	baoPaiCard = m_GameLogic.SwitchToCardData(m_cbBaoPaiIndex);

	// find Baopai in Discard List
	for( int i=0; i<m_cbPlayerCount; i++){
		for( int j=0; j<m_cbDiscardCount[i]; j++){
			if( m_cbDiscardCard[i][j] == baoPaiCard)
				nBaoCount++;
		}
	}

	ASSERT(nBaoCount<4);

	//find Baopai in Viewed card list ( peng, gang, chi )
	for( int i=0; i<m_cbPlayerCount; i++){
		for( int j=0; j<m_cbWeaveItemCount[i]; j++){
			if( m_WeaveItemArray[i][j].wWeaveKind == WIK_GANG && m_WeaveItemArray[i][j].cbParam == WIK_AN_GANG) continue; //Except 暗杠
			for( int k=0; k<4; k++){
				if( m_WeaveItemArray[i][j].cbCardData[k] == baoPaiCard)
					nBaoCount++;
			}
		}
	}

	ASSERT(nBaoCount<4);

	//find Baopai in ChangMao Gang list
	for( int i=0; i<m_cbPlayerCount; i++){
		for( int j=0; j<m_nChaseArrowCount[i]; j++){
			if( m_cbChaseArrowArray[i][j] == baoPaiCard)
				nBaoCount++;
		}
	}

	ASSERT(nBaoCount<4);
	if(nBaoCount >= 3) return false;

	return true;
}

//取得扑克
BYTE CTableFrameSink::GetSendCard(bool bTail)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//发送扑克
	m_cbLeftCardCount--;

	BYTE cbSendCardData = 0;
	
	BYTE cbIndexCard;
	if(bTail)
	{	
		cbSendCardData = m_cbRepertoryCard[m_cbMinusLastCount++];
	}
	else
	{
		cbIndexCard = MAX_REPERTORY - ++m_cbMinusHeadCount;
		cbSendCardData=m_cbRepertoryCard[cbIndexCard];
	}	

	//堆立信息
	ASSERT(m_wHeapHead != INVALID_CHAIR && m_wHeapTail != INVALID_CHAIR);
	if(!bTail)
	{
		//切换索引
		BYTE cbHeapCount = m_cbHeapCardInfo[m_wHeapHead][0] + m_cbHeapCardInfo[m_wHeapHead][1];
		if (cbHeapCount == HEAP_FULL_COUNT) 
		{
			m_wHeapHead = (m_wHeapHead + GAME_PLAYER - 1) % CountArray(m_cbHeapCardInfo);
		}
		m_cbHeapCardInfo[m_wHeapHead][0]++;
	}
	else
	{
		//切换索引
		BYTE cbHeapCount = m_cbHeapCardInfo[m_wHeapTail][0] + m_cbHeapCardInfo[m_wHeapTail][1];
		if (cbHeapCount == HEAP_FULL_COUNT) 
		{
			m_wHeapTail = (m_wHeapTail + 1) % CountArray(m_cbHeapCardInfo);
		}
		m_cbHeapCardInfo[m_wHeapTail][1]++;
	}

	return cbSendCardData;
}

//派发扑克
bool CTableFrameSink::DispatchCardData(WORD wSendCardUser, bool bTail)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//状态效验
	ASSERT(wSendCardUser != INVALID_CHAIR);
	if (wSendCardUser == INVALID_CHAIR) return false;

	ASSERT(m_enSendStatus != Not_Send);
	if(m_enSendStatus == Not_Send) return false;

	WORD wCurrentUser = wSendCardUser;

	//丢弃扑克
	if ((m_wOutCardUser != INVALID_CHAIR) && (m_cbOutCardData != 0))
	{
		m_cbOutCardCount++;
		m_cbDiscardCard[m_wOutCardUser][m_cbDiscardCount[m_wOutCardUser]] = m_cbOutCardData;
		m_cbDiscardCount[m_wOutCardUser]++;
	}

	//发送扑克
	if( m_cbGangStatus == WIK_ARW_GANG) {
		//m_cbProvideCard = m_cbProvideCard;	// keep ProvideCard
		m_cbSendCardData = INVAILD_CARD_DATA;
	} else {
		m_cbSendCardData = GetSendCard(bTail);
		m_cbProvideCard = m_cbSendCardData;

		//加牌
		m_cbCardIndex[wCurrentUser][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]++;
		m_cbUserCatchCardCount[wCurrentUser]++;
	}

	//清除禁止胡牌的牌
	m_bEnjoinChiHu[wCurrentUser] = false;
	m_vecEnjoinChiHu[wCurrentUser].clear();
	m_bEnjoinChiPeng[wCurrentUser] = false;		
	m_vecEnjoinChiPeng[wCurrentUser].clear();
	m_bEnjoinGang[wCurrentUser] = false;
	
	//设置变量	
	m_wOutCardUser = INVALID_CHAIR;
	m_cbOutCardData = 0;	
	m_wCurrentUser = wCurrentUser;
	m_wProvideUser = wCurrentUser;		
	m_bGangOutCard = false;
	
	if(bTail)//从尾部取牌，说明玩家杠牌了,计算分数
	{
		CalcGangScore(m_cbGangStatus);
	}


	if(!m_bTrustee[wCurrentUser])
	{
		//胡牌判断
		if(!m_bEnjoinChiHu[wCurrentUser])
		{
			CChiHuRight chr;
			m_cbCardIndex[wCurrentUser][m_GameLogic.SwitchToCardIndex(m_cbProvideCard)]--;
			m_wUserAction[wCurrentUser] |= m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[wCurrentUser], m_WeaveItemArray[wCurrentUser],
				m_cbWeaveItemCount[wCurrentUser], m_cbProvideCard, chr);
			m_cbCardIndex[wCurrentUser][m_GameLogic.SwitchToCardIndex(m_cbProvideCard)]++;

			if( m_GameLogic.IsBaoPaiCard(m_cbProvideCard) && m_bTing[wCurrentUser] ){
				chr |= CHR_JIN_BAO;
				if( m_cbLeftCardCount < FENZHANG_COUNT ) chr |= CHR_FEN_ZHANG;

				m_ChiHuRight[wCurrentUser] = chr;
				m_dwChiHuKind[wCurrentUser] = WIK_KIND_HU;
				if(!m_GameLogic.RemoveCard(m_cbCardIndex[wCurrentUser], &m_cbProvideCard, 1))
				{
					ASSERT(FALSE);
					return false;
				}

				//结束信息
				m_cbChiHuCard = m_cbProvideCard;
				m_cbSendCardData = m_cbProvideCard;

				//结束游戏
				OnEventGameConclude(wCurrentUser, NULL, GER_NORMAL);
				return true;
			}
		}

		//杠牌判断
		if ((!m_bEnjoinGang[wCurrentUser]) && (m_cbLeftCardCount > m_cbEndLeftCount) && !m_bTing[wCurrentUser])
		{
			BYTE cbWeaveCount = m_cbWeaveItemCount[wCurrentUser];

			if( m_GameLogic.isPossibleGang(m_WeaveItemArray[wCurrentUser], cbWeaveCount) ){
				tagGangCardResult GangCardResult;
				m_wUserAction[wCurrentUser] |= m_GameLogic.AnalyseGangCardEx(m_cbCardIndex[wCurrentUser],
					m_WeaveItemArray[wCurrentUser], m_cbWeaveItemCount[wCurrentUser],m_cbSendCardData ,GangCardResult, m_cbOutFromHandCount[wCurrentUser]);
			}
		}
	}

		//构造数据
	CMD_S_SendCard SendCard;
	ZeroMemory(&SendCard,sizeof(SendCard));

	//听牌判断
	CMD_S_Hu_Data HuData;
	ZeroMemory(&HuData,sizeof(HuData));

	BYTE cbCount = 0;
	cbCount =m_GameLogic.AnalyseTingCard(m_cbCardIndex[wCurrentUser],m_WeaveItemArray[wCurrentUser],m_cbWeaveItemCount[wCurrentUser],HuData.cbOutCardCount,HuData.cbOutCardData,HuData.cbHuCardCount,HuData.cbHuCardData);

	if(cbCount > 0) {
		m_wUserAction[wCurrentUser] |= WIK_LISTEN; 

		for(int i=0;i<MAX_COUNT;i++)
		{
			if(HuData.cbHuCardCount[i]>0)
			{
				for(int j=0;j<HuData.cbHuCardCount[i];j++)
					HuData.cbHuCardRemainingCount[i][j] = GetRemainingCount(wCurrentUser,HuData.cbHuCardData[i][j]);
			}
			else break;
		}
		m_pITableFrame->SendTableData(wCurrentUser,SUB_S_HU_CARD,&HuData,sizeof(HuData));
	}

	SendCard.wSendCardUser = wSendCardUser;
	SendCard.wCurrentUser = wCurrentUser;
	SendCard.bTail = bTail;
	SendCard.wActionMask = m_wUserAction[wCurrentUser];
	if( m_bTing[wCurrentUser] && (SendCard.wActionMask&WIK_LISTEN)!=0 ){
		SendCard.wActionMask ^= WIK_LISTEN;
	}
	SendCard.cbCardData = m_cbSendCardData;

	//荒庄结束
	if (m_cbLeftCardCount < FENZHANG_COUNT )//
	{
		m_cbChiHuCard = INVAILD_CARD_DATA;
		SendCard.wActionMask |= WIK_FEN_ZHANG;
		SendCard.wActionMask &= (WIK_CHI_HU | WIK_FEN_ZHANG);

		if ( (SendCard.wActionMask&WIK_CHI_HU) != 0 ) {

			m_ChiHuRight[wCurrentUser] |= CHR_FEN_ZHANG;
			m_cbChiHuCard = m_cbSendCardData;
			m_cbProvideCard = m_cbSendCardData;

			m_wProvideUser = INVALID_CHAIR;
			OnEventGameConclude(wCurrentUser, NULL, GER_NORMAL);
			return true;
		}
	}

	//发送数据
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_SEND_CARD, &SendCard, sizeof(SendCard));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_SEND_CARD, &SendCard, sizeof(SendCard));

	if( m_cbLeftCardCount < FENZHANG_COUNT ){
		m_pITableFrame->SetGameTimer(IDI_FENZHANG_DELAY, 3000, 1, NULL);
	} else {
		if(m_bTrustee[wCurrentUser])
		{
			m_bUserActionDone=true;
			m_pITableFrame->SetGameTimer(IDI_OUT_CARD,1000,1,0);
		}
	}

	return true;
}

//响应判断
bool CTableFrameSink::EstimateUserRespond(WORD wCenterUser, BYTE cbCenterCard, enEstimatKind EstimatKind)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//变量定义
	bool bAroseAction = false;

	//用户状态
	ZeroMemory(m_bResponse, sizeof(m_bResponse));
	ZeroMemory(m_wUserAction, sizeof(m_wUserAction));
	ZeroMemory(m_wPerformAction, sizeof(m_wPerformAction));

	//动作判断
	for (WORD k = 0; k < m_cbPlayerCount; k++)
	{
		WORD i = (wCenterUser+k+1)%m_cbPlayerCount;
		//用户过滤
		if (wCenterUser == i || !m_bPlayStatus[i] || m_bTrustee[i]) continue;

		//出牌类型
		if (EstimatKind == EstimatKind_OutCard )
		{
			CChiHuRight chr;
			BYTE cbWeaveCount = m_cbWeaveItemCount[i];
			BYTE cbAction = m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[i], m_WeaveItemArray[i], cbWeaveCount, cbCenterCard, chr);
			m_wUserAction[i] = cbAction;
			if( !m_bTing[i] ) {
				//吃碰判断
				if(!m_bEnjoinChiPeng[i])
				{
					bool bPeng = true;
					for(UINT j = 0; j < m_vecEnjoinChiPeng[i].size(); j++)
					{
						if(m_vecEnjoinChiPeng[i][j] == cbCenterCard)
						{
							bPeng = false;
						}
					}
					if(bPeng)
					{
						if( m_GameLogic.isPossiblePeng(m_WeaveItemArray[i], cbWeaveCount) ){
							//碰牌判断
							m_wUserAction[i] |= m_GameLogic.EstimatePengCard(m_cbCardIndex[i], cbCenterCard);
						}
					}

					//吃牌判断
					WORD wEatUser=(wCenterUser+1)%m_wPlayerCount;
					if (wEatUser==i){
						if( m_GameLogic.isPossibleChi(m_WeaveItemArray[i], cbWeaveCount) ){
							m_wUserAction[i] |= m_GameLogic.EstimateEatCard(m_cbCardIndex[i],cbCenterCard);
						}
					}

					//杠牌判断
					if(m_cbLeftCardCount > m_cbEndLeftCount && !m_bEnjoinGang[i]) 
					{
						if( m_GameLogic.isPossibleGang(m_WeaveItemArray[i], cbWeaveCount) ){
							m_wUserAction[i] |= m_GameLogic.EstimateGangCard(m_cbCardIndex[i], cbCenterCard);
						}
					}

					//if( m_wUserAction[i]&(WIK_LEFT|WIK_CENTER|WIK_RIGHT|WIK_PENG) ){
					//	CChiHuRight chr;
					//	BYTE cbWeaveCount = m_cbWeaveItemCount[i];
					//	BYTE cbAction = m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[i], m_WeaveItemArray[i], cbWeaveCount, cbCenterCard, chr);
					//	m_wUserAction[i] |= cbAction;
					//}
				}
			}
		}

		//检查抢杠胡
   		if (EstimatKind == EstimatKind_GangCard)
   		{
			//只有庄家和闲家之间才能放炮
			if(m_cbMagicIndex == INVAILD_CARD_INDEX || (m_cbMagicIndex != INVAILD_CARD_INDEX && cbCenterCard != m_GameLogic.SwitchToCardData(m_cbMagicIndex)))
			{
				bool bChiHu = true;
				for(UINT j = 0; j < m_vecEnjoinChiHu[i].size(); j++)
				{
					if(m_vecEnjoinChiHu[i][j] == cbCenterCard)
					{
						bChiHu = false;
						break;
					}
				}
				if(bChiHu && m_bTing[i])
				{
					//吃胡判断
					CChiHuRight chr;
					BYTE cbWeaveCount = m_cbWeaveItemCount[i];
					BYTE cbAction = m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[i], m_WeaveItemArray[i], cbWeaveCount, cbCenterCard, chr);
					m_wUserAction[i] |= cbAction;
				}
			}
   		}

		//结果判断
		if (m_wUserAction[i] != WIK_NULL) 
			bAroseAction = true;
	}

	//结果处理
	if (bAroseAction) 
	{
		//设置变量
		m_wProvideUser = wCenterUser;
		m_cbProvideCard = cbCenterCard;
		m_wResumeUser = m_wCurrentUser;
		m_wCurrentUser = INVALID_CHAIR;

		//发送提示
		SendOperateNotifyWithRank(m_wProvideUser, WIK_NULL);

		return true;
	}

	return false;
}

//算分
void CTableFrameSink::CalcHuPaiScore(WORD wWinnder, LONGLONG lEndScore[GAME_PLAYER], BYTE cbBiMenStatus)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//初始化
	ZeroMemory(lEndScore,sizeof(LONGLONG)*GAME_PLAYER);
	ZeroMemory(m_cbUserMaCount,sizeof(m_cbUserMaCount));

	bool bNoNegative = (m_pGameServiceOption->wServerType & GAME_GENRE_GOLD) != 0 || (m_pGameServiceOption->wServerType & SCORE_GENRE_POSITIVE) != 0;

	SCORE lCellScore = m_pITableFrame->GetCellScore();

	SCORE lUserScore[GAME_PLAYER] = {0};//玩家手上分
	SCORE lTempScore = 0;
	SCORE lTempAllScore = 0;
	for(int i = 0; i < GAME_PLAYER; i++)
	{
		if(!m_bPlayStatus[i])
			continue;
		IServerUserItem * pIServerUserItem = m_pITableFrame->GetTableUserItem(i);
		ASSERT(pIServerUserItem);
		if(pIServerUserItem)
		{
			lUserScore[i] = pIServerUserItem->GetUserScore();
		}		
	}

	if( wWinnder!=INVALID_CHAIR ){
		m_stRecord.cbHuCount[wWinnder]++;


		DWORD dwHuRight[MAX_RIGHT_COUNT];
		m_ChiHuRight[wWinnder].GetRightData(dwHuRight, MAX_RIGHT_COUNT);

		for(int i=0;i<GAME_PLAYER;i++)
		{
			if(!m_bPlayStatus[i])
				continue;
			if( i != wWinnder)
			{
				DWORD cbTimes = GetTimesOfUser(i, wWinnder, (cbBiMenStatus&(1<<i))!=0);
				SCORE lScoreItem = cbTimes*lCellScore;
				if( i == m_wBankerUser)		// already i != wWinnder, so
					lScoreItem *= 2;

				if(m_tGameCustomRule.bEnabled_DianPao && !(dwHuRight[0]&CHR_ZI_MO) ){
					ASSERT((m_wProvideUser!=INVALID_CHAIR) && (m_wProvideUser!=wWinnder) );
					lEndScore[m_wProvideUser] -= lScoreItem;
				} else {
					lEndScore[i] -= lScoreItem;
				}
				lEndScore[wWinnder] += lScoreItem;
			}
		}

		if(m_wBankerUser != wWinnder){
			m_wBankerUser = (m_wBankerUser+1)%m_cbPlayerCount;
		}
	}
}

void CTableFrameSink::CalcGangScore(BYTE cbStatus)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	SCORE lcell = m_pITableFrame->GetCellScore();
	switch(cbStatus){

		case WIK_MING_GANG:  //明杠每家出1倍
			{
				for(int i=0;i<GAME_PLAYER;i++)
				{
					if(!m_bPlayStatus[i])
						continue;
					if(i != m_wCurrentUser)
					{
						m_lUserGangScore[i] -= lcell;
						m_lUserGangScore[m_wCurrentUser] += lcell;
					}
				}
				//记录明杠次数
				m_stRecord.cbMingGang[m_wCurrentUser]++;
			}
			break;
		case WIK_BU_GANG:  //放杠一家扣分
			{
				for(int i=0;i<GAME_PLAYER;i++)
				{
					if(!m_bPlayStatus[i])
						continue;
					if(i != m_wCurrentUser)
					{
						m_lUserGangScore[i] -= lcell;
						m_lUserGangScore[m_wCurrentUser] += lcell;
					}
				}
				//记录明杠次数
				m_stRecord.cbMingGang[m_wCurrentUser]++;
			}
			break;
		case WIK_AN_GANG:  //暗杠每家出2倍
			{
				for(int i=0;i<GAME_PLAYER;i++)
				{
					if(!m_bPlayStatus[i])
						continue;
					if(i != m_wCurrentUser)
					{
						m_lUserGangScore[i] -= 2*lcell;
						m_lUserGangScore[m_wCurrentUser] += 2*lcell;
					}
				}
				//记录暗杠次数
				m_stRecord.cbAnGang[m_wCurrentUser]++;
			}
			break;
		case WIK_WND_GANG:
			{
				ASSERT(m_wCurrentUser!=INVALID_CHAIR);
				if(m_wCurrentUser != INVALID_CHAIR){
					for(int i=0;i<GAME_PLAYER;i++)
					{
						if(!m_bPlayStatus[i])
							continue;
						if(i != m_wCurrentUser)
						{
							m_lUserGangScore[i] -= 2*lcell;
							m_lUserGangScore[m_wCurrentUser] += 2*lcell;
						}
					}
					//记录暗杠次数
					m_stRecord.cbAnGang[m_wCurrentUser]++;
				}
			}
			break;
		case WIK_ARW_GANG:
			{
				ASSERT(m_wCurrentUser!=INVALID_CHAIR);
				if(m_wCurrentUser != INVALID_CHAIR){
					for(int i=0;i<GAME_PLAYER;i++)
					{
						if(!m_bPlayStatus[i])
							continue;
						if(i != m_wCurrentUser)
						{
							m_lUserGangScore[i] -= lcell;
							m_lUserGangScore[m_wCurrentUser] += lcell;
						}
					}
					//记录暗杠次数
					m_stRecord.cbMingGang[m_wCurrentUser]++;
				}
			}
			break;
		case WIK_CHASE_WND_GANG:
			{
				ASSERT(m_wCurrentUser!=INVALID_CHAIR);
				if(m_wCurrentUser != INVALID_CHAIR){
					if( m_cbChaseRemainCard[m_wCurrentUser][0]>0
						&& m_cbChaseRemainCard[m_wCurrentUser][1]>0
						&& m_cbChaseRemainCard[m_wCurrentUser][2]>0
						&& m_cbChaseRemainCard[m_wCurrentUser][3]>0 )
					{
						m_cbChaseRemainCard[m_wCurrentUser][0]--;
						m_cbChaseRemainCard[m_wCurrentUser][1]--;
						m_cbChaseRemainCard[m_wCurrentUser][2]--;
						m_cbChaseRemainCard[m_wCurrentUser][3]--;

						for(int i=0;i<GAME_PLAYER;i++)
						{
							if(!m_bPlayStatus[i])
								continue;
							if(i != m_wCurrentUser)
							{
								m_lUserGangScore[i] -= 2*lcell;
								m_lUserGangScore[m_wCurrentUser] += 2*lcell;
							}
						}
						//记录暗杠次数
						m_stRecord.cbAnGang[m_wCurrentUser]++;
					}
				}
			}
			break;
		case WIK_CHASE_ARW_GANG:
			{
				ASSERT(m_wCurrentUser!=INVALID_CHAIR);
				if(m_wCurrentUser != INVALID_CHAIR){
					if( m_cbChaseRemainCard[m_wCurrentUser][4]>0
						&& m_cbChaseRemainCard[m_wCurrentUser][5]>0
						&& m_cbChaseRemainCard[m_wCurrentUser][6]>0 )
					{
						m_cbChaseRemainCard[m_wCurrentUser][4]--;
						m_cbChaseRemainCard[m_wCurrentUser][5]--;
						m_cbChaseRemainCard[m_wCurrentUser][6]--;

						for(int i=0;i<GAME_PLAYER;i++)
						{
							if(!m_bPlayStatus[i])
								continue;
							if(i != m_wCurrentUser)
							{
								m_lUserGangScore[i] -= lcell;
								m_lUserGangScore[m_wCurrentUser] += lcell;
							}
						}
						//记录暗杠次数
						m_stRecord.cbMingGang[m_wCurrentUser]++;
					}
				}
			}
			break;
		default:
			CStringA str; str.Format("unknown Gang Status: %d", cbStatus);
			OutputDebugStringA(str);
			break;
	}
}
//权位过滤
void CTableFrameSink::FiltrateRight(WORD wWinner, CChiHuRight &chr)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//自摸
	if((wWinner == m_wProvideUser) || (m_wProvideUser==INVALID_CHAIR))
	{
		chr |= CHR_ZI_MO;

		BYTE cbArrGangShangHua[] = {WIK_BU_GANG,WIK_AN_GANG,WIK_MING_GANG,WIK_CHASE_WND_GANG,WIK_CHASE_ARW_GANG,WIK_WND_GANG};
		
		if( ExistInArray(m_cbGangStatus,cbArrGangShangHua, CountArray(cbArrGangShangHua)) )
			chr |= CHR_GANG_SHANG_HUA;
	}
	else {

		BYTE cbArrGangShangPao[] = {WIK_BU_GANG,WIK_AN_GANG,WIK_MING_GANG,WIK_CHASE_WND_GANG,WIK_CHASE_ARW_GANG,WIK_WND_GANG};

		if( ExistInArray(m_cbGangStatus,cbArrGangShangPao, CountArray(cbArrGangShangPao)) )
			chr |= CHR_GANG_SHANG_PAO;

	}
	/*else
	{
		ASSERT(false);
	}*/

	if (wWinner == m_wBankerUser)
	{
		//庄胡
		chr |= CHR_ZHUANG_JIA;
	}


}

//设置基数
void CTableFrameSink::SetGameBaseScore(LONG lBaseScore)
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	//发送数据
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_SET_BASESCORE,&lBaseScore,sizeof(lBaseScore));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_SET_BASESCORE,&lBaseScore,sizeof(lBaseScore));
}

DWORD CTableFrameSink::GetTimes(WORD wChairId)
{
	DWORD wFanShu = 1;
	DWORD wSpHuPaiKind[] = {CHR_ZHUANG_JIA, CHR_QING_YI_SE, CHR_QI_YU, CHR_GANG_SHANG_PAO, 
		CHR_GANG_SHANG_HUA, CHR_FEN_ZHANG, CHR_SHOU_BA_YI, CHR_JIA_HU, CHR_JIN_BAO};

	if( wChairId == INVALID_CHAIR) return wFanShu;

	DWORD dwRight[MAX_RIGHT_COUNT];
	m_ChiHuRight[wChairId].GetRightData(dwRight, MAX_RIGHT_COUNT);

	BYTE nTime = 0;
	for(int i=0; i<CountArray(wSpHuPaiKind); i++){
		if( wSpHuPaiKind[i] & dwRight[0] )
			wFanShu *= 2;
	}
	return wFanShu;//2^n( 番数 )
}

DWORD CTableFrameSink::GetTimesOfUser(WORD wUserId, WORD wWinnerId, bool isBiMen)
{
	DWORD wFanShu = 1;
	DWORD wSpHuPaiKind[] = {CHR_ZHUANG_JIA, CHR_QING_YI_SE, CHR_QI_YU, CHR_GANG_SHANG_PAO,
		CHR_GANG_SHANG_HUA, CHR_FEN_ZHANG, CHR_SHOU_BA_YI, CHR_JIA_HU, CHR_JIN_BAO};

	if( wWinnerId == INVALID_CHAIR) return wFanShu;

	DWORD dwRight[MAX_RIGHT_COUNT];
	m_ChiHuRight[wWinnerId].GetRightData(dwRight, MAX_RIGHT_COUNT);

	BYTE nTime = 0;
	for(int i=0; i<CountArray(wSpHuPaiKind); i++){
		if( wSpHuPaiKind[i] & dwRight[0] )
			wFanShu *= 2;
	}
	if(isBiMen)
		wFanShu *= 2;
	return wFanShu;//2^n( 番数 )
}

BYTE CTableFrameSink::GetRemainingCount(WORD wChairID,BYTE cbCardData)
{
	//OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	BYTE cbIndex = m_GameLogic.SwitchToCardIndex(cbCardData);
	BYTE nCount=0;
	for(int i=m_cbMinusLastCount;i<MAX_REPERTORY-m_cbMinusHeadCount;i++)
	{
		if(m_cbRepertoryCard[i] == cbCardData)
			nCount++;
	}
	for(WORD i=0;i<GAME_PLAYER;i++)
	{
		if( i == wChairID)
			continue;

		nCount += m_cbCardIndex[i][cbIndex];
	}
	return nCount;
}

bool CTableFrameSink::OnActionUserOffLine(WORD wChairID, IServerUserItem * pIServerUserItem)
{
	OutputDebugStringA("\n");OutputDebugStringA(__FUNCTION__);
	if( (m_pGameServiceOption->wServerType&GAME_GENRE_PERSONAL) != 0)//房卡模式
		return true;
	//自动托管
	OnUserTrustee(wChairID,true);

	return true;
}

//bool CTableFrameSink::OnEventFenZhang()
//{
//	OutputDebugStringA("\n\t\t");OutputDebugStringA(__FUNCTION__);
//	WORD chiHuUserId = INVALID_CHAIR;
//	for( int i=0; i<GAME_PLAYER; i++){
//		WORD playerIndex = (m_wCurrentUser + i) % GAME_PLAYER;
//
//		BYTE cardData = GetSendCard();
//		m_dwChiHuKind[playerIndex] = m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[playerIndex], m_WeaveItemArray[playerIndex],
//			m_cbWeaveItemCount[playerIndex], cardData, m_ChiHuRight[playerIndex]);
//
//		if( m_GameLogic.IsBaoPaiCard(cardData) && m_bTing[playerIndex] ){
//			m_dwChiHuKind[playerIndex] |= WIK_KIND_HU;			
//			m_ChiHuRight[playerIndex] |= CHR_JIN_BAO;
//		}
//
//		if( (m_dwChiHuKind[playerIndex]&WIK_KIND_HU) == WIK_KIND_HU){
//
//			chiHuUserId = playerIndex;
//			m_ChiHuRight[playerIndex] |= CHR_FEN_ZHANG;
//			m_cbCardIndex[playerIndex][m_GameLogic.SwitchToCardIndex(cardData)]++;
//			m_cbHandCardCount[playerIndex]++;
//
//			m_cbChiHuCard = cardData;
//			m_cbSendCardData = cardData;
//
//			m_cbProvideCard = cardData;
//			break;
//		}
//	}
//	m_wProvideUser = INVALID_CHAIR;
//	OnEventGameConclude(chiHuUserId, NULL, GER_NORMAL);
//	return true;
//}

bool CTableFrameSink::processQiangGangHu(BYTE cbGangStatus, WORD wUser, WORD wProvider){

	m_cbGangStatus = WIK_GANERAL;
	m_wProvideGangUser = INVALID_CHAIR;

	switch(cbGangStatus){
		case WIK_BU_GANG:
			{
				ASSERT(m_cbGangCount[wProvider]>0);
				m_cbGangCount[wProvider]--;

				BYTE cbWeaveIndex=0xFF;
				for (BYTE i = 0; i < m_cbWeaveItemCount[wProvider]; i++)
				{
					WORD cbParam = m_WeaveItemArray[wProvider][i].cbParam;
					BYTE cbCenterCard = m_WeaveItemArray[wProvider][i].cbCenterCard;
					if ((cbCenterCard == m_cbChiHuCard) && (cbParam == WIK_BU_GANG))
					{
						cbWeaveIndex = i;
						break;
					}
				}
				ASSERT(cbWeaveIndex<MAX_WEAVE);
				if(cbWeaveIndex<MAX_WEAVE){
					//组合扑克
					m_WeaveItemArray[wProvider][cbWeaveIndex].cbParam = WIK_GANERAL;
					m_WeaveItemArray[wProvider][cbWeaveIndex].wWeaveKind = WIK_PENG;
					m_WeaveItemArray[wProvider][cbWeaveIndex].cbCardData[3] = INVAILD_CARD_DATA;
				}

				m_dwChiHuKind[wUser] |= CHR_QIANG_GANG_HU;
				break;
			}
		case WIK_CHASE_WND_GANG:
		case WIK_CHASE_ARW_GANG:
			{
				ASSERT(m_nChaseArrowCount[wProvider]>0);
				m_cbChaseArrowArray[wProvider][--m_nChaseArrowCount[wProvider]] = INVAILD_CARD_DATA;
                
				m_dwChiHuKind[wUser] |= CHR_QIANG_GANG_HU;
				break;
			}

		default:
			ASSERT(false);
			break;
	}
	return true;
}

bool CTableFrameSink::ExistInArray(BYTE cbStatus, BYTE cbArray[], WORD nCount){
	for( int i=0; i<nCount; i++){
		if( cbStatus == cbArray[i]){
			return true;
		}
	}
	return false;
}

WORD CTableFrameSink::NextUserID(WORD wCurrentID){
	WORD nextId = (wCurrentID + 1) % m_cbPlayerCount;
	for(int i=0;i<m_cbPlayerCount;i++)
	{
		if(m_bPlayStatus[nextId])
			break;
		nextId = (nextId+1)%m_cbPlayerCount;
	}
	return nextId;
}

//////////////////////////////////////////////////////////////////////////////////
