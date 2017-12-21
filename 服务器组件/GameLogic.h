#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgCustomRule.h"
//////////////////////////////////////////////////////////////////////////

//用于财神的转换，如果有牌可以代替财神本身牌使用，则设为该牌索引，否则设为MAX_INDEX. 注:如果替换牌是序数牌,将出错.
#define	INDEX_REPLACE_CARD					MAX_INDEX


#define INVAILD_CARD_INDEX          MAX_INDEX
#define INVAILD_CARD_DATA           0x00
//////////////////////////////////////////////////////////////////////////
//逻辑掩码

#define	MASK_COLOR					0xF0								//花色掩码
#define	MASK_VALUE					0x0F								//数值掩码

//////////////////////////////////////////////////////////////////////////
//动作定义

//动作类型
#define WIK_GANERAL					0x00								//普通操作
#define WIK_BU_GANG 				0x01								//明杠（碰后再杠）  - Means BuGang in Chaoyang
#define WIK_MING_GANG				0x02								//放杠				- Means MingGang in Chaoyang
#define WIK_AN_GANG					0x03								//暗杠

#define WIK_WND_GANG				0x04								//【东南西北】四张【风牌】在一起组成的杠
#define WIK_ARW_GANG				0x05								//【中发白】三张【箭牌】在一起组成的杠
#define WIK_CHASE_WND_GANG			0x06								//【东南西北】的杠追加风牌后的杠 长毛杠
#define WIK_CHASE_ARW_GANG			0x07								//【中发白】的杠追加【中发白】牌后的杠 长毛杠

//动作标志
#define WIK_NULL					0x0000								//没有类型
#define WIK_LEFT					0x0001								//左吃类型
#define WIK_CENTER					0x0002								//中吃类型
#define WIK_RIGHT					0x0004								//右吃类型
#define WIK_PENG					0x0008								//碰牌类型
#define WIK_GANG					0x0010								//杠牌类型
#define WIK_LISTEN					0x0020								//听牌类型
#define WIK_CHI_HU					0x0040								//吃胡类型
#define WIK_FANG_PAO				0x0080								//放炮

//朝阳麻将 Additional Flag
#define WIK_ARROW					0x0100							//【中发白】三张【箭牌】在一起组成的杠
#define WIK_WIND					0x0200							//【东南西北】四张【风牌】在一起组成的杠
#define WIK_CHASEARROW				0x0400							//【中发白】的杠追加【中发白】牌后的杠
#define WIK_CHASEWIND				0x0800							//【东南西北】的杠追加风牌后的杠
#define WIK_FEN_ZHANG				0x4000
#define WIK_UPDATE_BAO				0x8000							// UPDATED BAO PAI


// Hu Kind : CMD_S_GameConclude.dwChiHuKind[], CTableFrameSinkf.m_dwChiHuKind[]
#define WIK_NORMAL  				0x0000								//没有类型
#define WIK_KIND_HU					0x0040								//吃胡类型

//////////////////////////////////////////////////////////////////////////
//胡牌定义

//CTableFrameSinkf.m_ChiHuRight[]
#define HU_KIND_MASK				0x0000FFFF
#define CHR_PING_HU					0x00000001			//平胡
#define CHR_ZHUANG_JIA				0x00000002			// 庄家
#define CHR_ZI_MO					0x00000004			// 自摸
#define CHR_QING_YI_SE				0x00000008			// 清一色
#define CHR_PIAO_HU					0x00000010			// 飘胡     // =0
#define CHR_QIONG_HU				0x00000020			// 穷胡     // =0
#define CHR_SHI_SAN_YAO				0x00000040			// 十三幺
#define CHR_QI_DUI					0x00000080			// 七对		// =0
#define CHR_SHOU_BA_YI				0x00000100			//手把一	
#define CHR_JIA_HU					0x00000200			//	夹胡
#define CHR_JIN_BAO					0x00000800			// 进宝
#define CHR_FEN_ZHANG				0x00008000			//分张	// 海底捞月（haidilaoyue）

#define GANG_KIND_MASK				0xFFFF0000
#define CHR_GANG_SHANG_HUA          0x00010000          //杠上花
#define CHR_GANG_SHANG_PAO          0x00020000          //杠上炮
#define CHR_QIANG_GANG_HU           0x00040000          //抢杠胡
#define CHR_QI_YU					0x00080000			//其余三家闭门
#define CHR_CHI_HU					0x00100000			//放炮


//////////////////////////////////////////////////////////////////////////////////

//类型子项
struct tagKindItem
{
	WORD							wWeaveKind;						//组合类型
	BYTE							cbCenterCard;						//中心扑克
	BYTE							cbValidIndex[3];					//实际扑克索引
	BYTE							cbMagicCount;						//财神牌数
};

//杠牌结果
struct tagGangCardResult
{
	BYTE							cbCardCount;						//扑克数目
	BYTE							cbCardData[MAX_WEAVE];				//扑克数据
};


//分析子项
struct tagAnalyseItem
{
	BYTE							cbCardEye;							//牌眼扑克
	bool                            bMagicEye;                          //牌眼是否是王霸
	WORD							wWeaveKind[MAX_WEAVE];				//组合类型
	BYTE							cbCenterCard[MAX_WEAVE];			//中心扑克
	BYTE                            cbCardData[MAX_WEAVE][4];           //实际扑克
};


//////////////////////////////////////////////////////////////////////////


#define MASK_CHI_HU_RIGHT			0x0fffffff

/*
//	权位类。
//  注意，在操作仅位时最好只操作单个权位.例如
//  CChiHuRight chr;
//  chr |= (chr_zi_mo|chr_peng_peng)，这样结果是无定义的。
//  只能单个操作:
//  chr |= chr_zi_mo;
//  chr |= chr_peng_peng;
*/
class CChiHuRight
{	
	//静态变量
private:
	static bool						m_bInit;
	static DWORD					m_dwRightMask[MAX_RIGHT_COUNT];

	//权位变量
private:
	DWORD							m_dwRight[MAX_RIGHT_COUNT];

public:
	//构造函数
	CChiHuRight();

	//运算符重载
public:
	//赋值符
	CChiHuRight & operator = (DWORD dwRight);

	//与等于
	CChiHuRight & operator &= (DWORD dwRight);
	//或等于
	CChiHuRight & operator |= (DWORD dwRight);

	//与
	CChiHuRight operator & (DWORD dwRight);
	CChiHuRight operator & (DWORD dwRight) const;

	//或
	CChiHuRight operator | (DWORD dwRight);
	CChiHuRight operator | (DWORD dwRight) const;

	//相等
	bool operator == (DWORD dwRight) const;
	bool operator == (const CChiHuRight chr) const;

	//不相等
	bool operator != (DWORD dwRight) const;
	bool operator != (const CChiHuRight chr) const;

	//功能函数
public:
	//是否权位为空
	bool IsEmpty();

	//设置权位为空
	void SetEmpty();

	//获取权位数值
	BYTE GetRightData(DWORD dwRight[], BYTE cbMaxCount);

	//设置权位数值
	bool SetRightData(const DWORD dwRight[], BYTE cbRightCount);

private:
	//检查权位是否正确
	bool IsValidRight(DWORD dwRight);
};

//////////////////////////////////////////////////////////////////////////////////

//数组说明
typedef CWHArray<tagAnalyseItem,tagAnalyseItem &> CAnalyseItemArray;

//游戏逻辑类
class CGameLogic
{
	//变量定义
protected:
	static const BYTE				m_cbCardDataArray[MAX_REPERTORY];	//扑克数据
	BYTE							m_cbMagicIndex;						//钻牌索引
	BYTE							m_cbBaopaiIndex;					//宝牌索引
	tagCustomRule					m_CustomRule;						//定制规则

	//函数定义
public:
	//构造函数
	CGameLogic();
	//析构函数
	virtual ~CGameLogic();

	//类型函数
public:
	//获取数值
	BYTE GetCardValue(BYTE cbCardData) { return cbCardData&MASK_VALUE; }
	//获取花色
	BYTE GetCardColor(BYTE cbCardData) { return cbCardData&MASK_COLOR; }

	//控制函数
public:
	//混乱扑克
	VOID RandCardList(BYTE cbCardBuffer[], BYTE cbBufferCount);
	//混乱扑克
	VOID RandCardList(BYTE cbCardData[], BYTE cbCardBuffer[], BYTE cbBufferCount);
	//删除扑克
	bool RemoveCard(BYTE cbCardIndex[MAX_INDEX], const BYTE cbRemoveCard[], BYTE cbRemoveCount);
	//删除扑克
	bool RemoveCard(BYTE cbCardIndex[MAX_INDEX], BYTE cbRemoveCard);
	//删除扑克
	bool RemoveCard(BYTE cbCardData[], BYTE cbCardCount, const BYTE cbRemoveCard[], BYTE cbRemoveCount);
	//排序,根据牌值排序
	bool SortCardList(BYTE cbCardData[MAX_COUNT], BYTE cbCardCount);
	//设置财神
	void SetMagicIndex(BYTE cbMagicIndex) { m_cbMagicIndex = cbMagicIndex; }
	//财神判断
	bool IsMagicCard(BYTE cbCardData);
	//设置财神
	void SetBaopaiIndex(BYTE cbBaoPaiIndex) { m_cbBaopaiIndex = cbBaoPaiIndex; }
	//财神判断
	bool IsBaoPaiCard(BYTE cbCardData);
	//花牌判断
	bool IsHuaCard(BYTE cbCardData);
	//花牌判断
	BYTE IsHuaCard(BYTE cbCardIndex[MAX_INDEX]);

	//逻辑函数
public:

	//等级函数
public:
	//动作等级
	BYTE GetUserActionRank(WORD wUserAction);
	//胡牌等级
	WORD GetChiHuActionRank(const CChiHuRight & ChiHuRight);
	//胡牌倍数
	WORD GetChiHuTime(const CChiHuRight & ChiHuRight);
	//自动出牌
	BYTE AutomatismOutCard(const BYTE cbCardIndex[MAX_INDEX], const BYTE cbEnjoinOutCard[MAX_COUNT], BYTE cbEnjoinOutCardCount);

	//动作判断
public:
	//吃牌判断
	BYTE EstimateEatCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard);
	//碰牌判断
	BYTE EstimatePengCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard);
	//杠牌判断
	BYTE EstimateGangCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard);

	//动作判断
public:
	//杠牌分析
	WORD AnalyseGangCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, tagGangCardResult & GangCardResult);
	//杠牌分析
	WORD AnalyseGangCardEx(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount,BYTE cbProvideCard, tagGangCardResult & GangCardResult, BYTE cbDiscardCount);
	//吃胡分析
	BYTE AnalyseChiHuCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE cbCurrentCard, CChiHuRight &ChiHuRight/*,bool bTingStatus=false*/);
	//听牌分析
	BYTE AnalyseTingCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount);
	//听牌分析，获取打那些牌能听，以及能胡哪些牌
	//BYTE AnalyseTingCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE cbOutCard[][28]);
	BYTE AnalyseTingCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE& cbOutCardCount,BYTE cbOutCardData[],BYTE cbHuCardCount[],BYTE cbHuCardData[][28]);
	// Check Ting conditions
	bool isPossibleTing(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount);	
	//Check if Kaimen was opened or not
	bool isOpenedKaimen(const tagWeaveItem WeaveItem[], BYTE cbWeaveCount);
	//获取胡牌数据，听牌后调用
	BYTE GetHuCard( const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount,BYTE cbHuCardData[]);
	BYTE GetRandHuiPaiCardIndex( );

	//转换函数
public:
	//扑克转换
	BYTE SwitchToCardData(BYTE cbCardIndex);
	//扑克转换
	BYTE SwitchToCardIndex(BYTE cbCardData);
	//扑克转换
	BYTE SwitchToCardData(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCardData[MAX_COUNT]);
	//扑克转换
	BYTE SwitchToCardIndex(const BYTE cbCardData[], BYTE cbCardCount, BYTE cbCardIndex[MAX_INDEX]);
	

	//辅助函数
public:
	//有效判断
	bool IsValidCard(BYTE cbCardData);
	//扑克数目
	BYTE GetCardCount(const BYTE cbCardIndex[MAX_INDEX]);	
	//组合扑克
	BYTE GetWeaveCard(WORD wWeaveKind, BYTE cbCenterCard, BYTE cbCardBuffer[4]);

	//内部函数
private:
	bool AddKindItem(tagKindItem &TempKindItem, tagKindItem KindItem[], BYTE &cbKindItemCount, bool &bMagicThree);
	//分析扑克
	bool AnalyseCard(BYTE cbCurrentCard, const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveICount, CAnalyseItemArray & AnalyseItemArray);

	// If this Analyse Item is able to do Hu(胡) return ture. if not, return false
	bool isPossibleHu(BYTE cbHuCard, const tagAnalyseItem *pAnalyseItem, BYTE cbWeaveCount);
	
	bool CheckHuFormatStyle(const tagAnalyseItem *pAnalyseItem);
	bool CheckJiaHuStyle(BYTE cbHuCard, const tagAnalyseItem *pAnalyseItem, BYTE cbWeaveCount);
	bool CheckYaoJiuFormat(const tagAnalyseItem *pAnalyseItem);
	bool isYaoJiuCard(BYTE card);
	bool isYaoJiuSubstitute(BYTE card);

	//胡法分析
protected:

	//碰碰和
	bool IsPengPeng(const tagAnalyseItem *pAnalyseItem);
	//麻七系列
	bool IsMaQi(const BYTE cbCardIndex[MAX_INDEX],BYTE cbWeaveCount);
	//十三烂系列
	bool IsShiSanYao(const BYTE cbCardIndex[MAX_INDEX],BYTE cbWeaveCount);

	bool IsShouBaYi(const tagAnalyseItem *pAnalyseItem, BYTE nWeaveCount);

	bool IsJiaHuFormat(BYTE cbHuPai, const tagAnalyseItem *pAnalyseItem, BYTE nWeaveCount);
	//平胡
	bool IsPingHu(const tagAnalyseItem *pAnalyseItem);
	//鸡胡
	bool IsJiHu(const tagAnalyseItem *pAnalyseItem);
	//清一色
	bool IsQingYiSe(const tagAnalyseItem * pAnalyseItem);	
	//混一色
	bool IsHunYiSe(const tagAnalyseItem * pAnalyseItem);	


public:
	//验证某玩家是否可以做特殊杠操作
	bool IsSpGangOK(const BYTE cbCardIndex[MAX_INDEX], DWORD dwOpCode);
	//从手中扣掉特殊杠的牌组
	bool TakeOutSpGang(BYTE cbCardIndex[MAX_INDEX], DWORD dwOpCode);
	//从手中扣掉长毛杠的牌组
	bool TakeOutCHMGang(BYTE cbCardIndex[MAX_INDEX],BYTE cbCernterCard);

public:
	//按默认值初始化定制规则
	void InitCustomRule();
	//设置定制规则
	void SetCustomRule(tagCustomRule *pRule);

	bool IsChaseArrow(BYTE cbProvidedCardIndex,const tagWeaveItem WeaveItem[], BYTE cbWeaveICount,DWORD dwOpCode);

	bool IsPossibleChaseArrow(const BYTE cbHandCards[MAX_INDEX],const tagWeaveItem WeaveItem[], BYTE cbWeaveICount,DWORD dwOpCode);

#ifdef CARD_DISPATCHER_CONTROL
	void printLogAnalyseItems(BYTE cbHuCard, CAnalyseItemArray* arr);
#endif
};

//////////////////////////////////////////////////////////////////////////////////

#endif