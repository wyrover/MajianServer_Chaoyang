#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgCustomRule.h"
//////////////////////////////////////////////////////////////////////////

//���ڲ����ת����������ƿ��Դ����������ʹ�ã�����Ϊ����������������ΪMAX_INDEX. ע:����滻����������,������.
#define	INDEX_REPLACE_CARD					MAX_INDEX


#define INVAILD_CARD_INDEX          MAX_INDEX
#define INVAILD_CARD_DATA           0x00
//////////////////////////////////////////////////////////////////////////
//�߼�����

#define	MASK_COLOR					0xF0								//��ɫ����
#define	MASK_VALUE					0x0F								//��ֵ����

//////////////////////////////////////////////////////////////////////////
//��������

//��������
#define WIK_GANERAL					0x00								//��ͨ����
#define WIK_BU_GANG 				0x01								//���ܣ������ٸܣ�  - Means BuGang in Chaoyang
#define WIK_MING_GANG				0x02								//�Ÿ�				- Means MingGang in Chaoyang
#define WIK_AN_GANG					0x03								//����

#define WIK_WND_GANG				0x04								//���������������š����ơ���һ����ɵĸ�
#define WIK_ARW_GANG				0x05								//���з��ס����š����ơ���һ����ɵĸ�
#define WIK_CHASE_WND_GANG			0x06								//�������������ĸ�׷�ӷ��ƺ�ĸ� ��ë��
#define WIK_CHASE_ARW_GANG			0x07								//���з��ס��ĸ�׷�ӡ��з��ס��ƺ�ĸ� ��ë��

//������־
#define WIK_NULL					0x0000								//û������
#define WIK_LEFT					0x0001								//�������
#define WIK_CENTER					0x0002								//�г�����
#define WIK_RIGHT					0x0004								//�ҳ�����
#define WIK_PENG					0x0008								//��������
#define WIK_GANG					0x0010								//��������
#define WIK_LISTEN					0x0020								//��������
#define WIK_CHI_HU					0x0040								//�Ժ�����
#define WIK_FANG_PAO				0x0080								//����

//�����齫 Additional Flag
#define WIK_ARROW					0x0100							//���з��ס����š����ơ���һ����ɵĸ�
#define WIK_WIND					0x0200							//���������������š����ơ���һ����ɵĸ�
#define WIK_CHASEARROW				0x0400							//���з��ס��ĸ�׷�ӡ��з��ס��ƺ�ĸ�
#define WIK_CHASEWIND				0x0800							//�������������ĸ�׷�ӷ��ƺ�ĸ�
#define WIK_FEN_ZHANG				0x4000
#define WIK_UPDATE_BAO				0x8000							// UPDATED BAO PAI


// Hu Kind : CMD_S_GameConclude.dwChiHuKind[], CTableFrameSinkf.m_dwChiHuKind[]
#define WIK_NORMAL  				0x0000								//û������
#define WIK_KIND_HU					0x0040								//�Ժ�����

//////////////////////////////////////////////////////////////////////////
//���ƶ���

//CTableFrameSinkf.m_ChiHuRight[]
#define HU_KIND_MASK				0x0000FFFF
#define CHR_PING_HU					0x00000001			//ƽ��
#define CHR_ZHUANG_JIA				0x00000002			// ׯ��
#define CHR_ZI_MO					0x00000004			// ����
#define CHR_QING_YI_SE				0x00000008			// ��һɫ
#define CHR_PIAO_HU					0x00000010			// Ʈ��     // =0
#define CHR_QIONG_HU				0x00000020			// ���     // =0
#define CHR_SHI_SAN_YAO				0x00000040			// ʮ����
#define CHR_QI_DUI					0x00000080			// �߶�		// =0
#define CHR_SHOU_BA_YI				0x00000100			//�ְ�һ	
#define CHR_JIA_HU					0x00000200			//	�к�
#define CHR_JIN_BAO					0x00000800			// ����
#define CHR_FEN_ZHANG				0x00008000			//����	// �������£�haidilaoyue��

#define GANG_KIND_MASK				0xFFFF0000
#define CHR_GANG_SHANG_HUA          0x00010000          //���ϻ�
#define CHR_GANG_SHANG_PAO          0x00020000          //������
#define CHR_QIANG_GANG_HU           0x00040000          //���ܺ�
#define CHR_QI_YU					0x00080000			//�������ұ���
#define CHR_CHI_HU					0x00100000			//����


//////////////////////////////////////////////////////////////////////////////////

//��������
struct tagKindItem
{
	WORD							wWeaveKind;						//�������
	BYTE							cbCenterCard;						//�����˿�
	BYTE							cbValidIndex[3];					//ʵ���˿�����
	BYTE							cbMagicCount;						//��������
};

//���ƽ��
struct tagGangCardResult
{
	BYTE							cbCardCount;						//�˿���Ŀ
	BYTE							cbCardData[MAX_WEAVE];				//�˿�����
};


//��������
struct tagAnalyseItem
{
	BYTE							cbCardEye;							//�����˿�
	bool                            bMagicEye;                          //�����Ƿ�������
	WORD							wWeaveKind[MAX_WEAVE];				//�������
	BYTE							cbCenterCard[MAX_WEAVE];			//�����˿�
	BYTE                            cbCardData[MAX_WEAVE][4];           //ʵ���˿�
};


//////////////////////////////////////////////////////////////////////////


#define MASK_CHI_HU_RIGHT			0x0fffffff

/*
//	Ȩλ�ࡣ
//  ע�⣬�ڲ�����λʱ���ֻ��������Ȩλ.����
//  CChiHuRight chr;
//  chr |= (chr_zi_mo|chr_peng_peng)������������޶���ġ�
//  ֻ�ܵ�������:
//  chr |= chr_zi_mo;
//  chr |= chr_peng_peng;
*/
class CChiHuRight
{	
	//��̬����
private:
	static bool						m_bInit;
	static DWORD					m_dwRightMask[MAX_RIGHT_COUNT];

	//Ȩλ����
private:
	DWORD							m_dwRight[MAX_RIGHT_COUNT];

public:
	//���캯��
	CChiHuRight();

	//���������
public:
	//��ֵ��
	CChiHuRight & operator = (DWORD dwRight);

	//�����
	CChiHuRight & operator &= (DWORD dwRight);
	//�����
	CChiHuRight & operator |= (DWORD dwRight);

	//��
	CChiHuRight operator & (DWORD dwRight);
	CChiHuRight operator & (DWORD dwRight) const;

	//��
	CChiHuRight operator | (DWORD dwRight);
	CChiHuRight operator | (DWORD dwRight) const;

	//���
	bool operator == (DWORD dwRight) const;
	bool operator == (const CChiHuRight chr) const;

	//�����
	bool operator != (DWORD dwRight) const;
	bool operator != (const CChiHuRight chr) const;

	//���ܺ���
public:
	//�Ƿ�ȨλΪ��
	bool IsEmpty();

	//����ȨλΪ��
	void SetEmpty();

	//��ȡȨλ��ֵ
	BYTE GetRightData(DWORD dwRight[], BYTE cbMaxCount);

	//����Ȩλ��ֵ
	bool SetRightData(const DWORD dwRight[], BYTE cbRightCount);

private:
	//���Ȩλ�Ƿ���ȷ
	bool IsValidRight(DWORD dwRight);
};

//////////////////////////////////////////////////////////////////////////////////

//����˵��
typedef CWHArray<tagAnalyseItem,tagAnalyseItem &> CAnalyseItemArray;

//��Ϸ�߼���
class CGameLogic
{
	//��������
protected:
	static const BYTE				m_cbCardDataArray[MAX_REPERTORY];	//�˿�����
	BYTE							m_cbMagicIndex;						//��������
	BYTE							m_cbBaopaiIndex;					//��������
	tagCustomRule					m_CustomRule;						//���ƹ���

	//��������
public:
	//���캯��
	CGameLogic();
	//��������
	virtual ~CGameLogic();

	//���ͺ���
public:
	//��ȡ��ֵ
	BYTE GetCardValue(BYTE cbCardData) { return cbCardData&MASK_VALUE; }
	//��ȡ��ɫ
	BYTE GetCardColor(BYTE cbCardData) { return cbCardData&MASK_COLOR; }

	//���ƺ���
public:
	//�����˿�
	VOID RandCardList(BYTE cbCardBuffer[], BYTE cbBufferCount);
	//�����˿�
	VOID RandCardList(BYTE cbCardData[], BYTE cbCardBuffer[], BYTE cbBufferCount);
	//ɾ���˿�
	bool RemoveCard(BYTE cbCardIndex[MAX_INDEX], const BYTE cbRemoveCard[], BYTE cbRemoveCount);
	//ɾ���˿�
	bool RemoveCard(BYTE cbCardIndex[MAX_INDEX], BYTE cbRemoveCard);
	//ɾ���˿�
	bool RemoveCard(BYTE cbCardData[], BYTE cbCardCount, const BYTE cbRemoveCard[], BYTE cbRemoveCount);
	//����,������ֵ����
	bool SortCardList(BYTE cbCardData[MAX_COUNT], BYTE cbCardCount);
	//���ò���
	void SetMagicIndex(BYTE cbMagicIndex) { m_cbMagicIndex = cbMagicIndex; }
	//�����ж�
	bool IsMagicCard(BYTE cbCardData);
	//���ò���
	void SetBaopaiIndex(BYTE cbBaoPaiIndex) { m_cbBaopaiIndex = cbBaoPaiIndex; }
	//�����ж�
	bool IsBaoPaiCard(BYTE cbCardData);
	//�����ж�
	bool IsHuaCard(BYTE cbCardData);
	//�����ж�
	BYTE IsHuaCard(BYTE cbCardIndex[MAX_INDEX]);

	//�߼�����
public:

	//�ȼ�����
public:
	//�����ȼ�
	BYTE GetUserActionRank(WORD wUserAction);
	//���Ƶȼ�
	WORD GetChiHuActionRank(const CChiHuRight & ChiHuRight);
	//���Ʊ���
	WORD GetChiHuTime(const CChiHuRight & ChiHuRight);
	//�Զ�����
	BYTE AutomatismOutCard(const BYTE cbCardIndex[MAX_INDEX], const BYTE cbEnjoinOutCard[MAX_COUNT], BYTE cbEnjoinOutCardCount);

	//�����ж�
public:
	//�����ж�
	BYTE EstimateEatCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard);
	//�����ж�
	BYTE EstimatePengCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard);
	//�����ж�
	BYTE EstimateGangCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard);

	//�����ж�
public:
	//���Ʒ���
	WORD AnalyseGangCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, tagGangCardResult & GangCardResult);
	//���Ʒ���
	WORD AnalyseGangCardEx(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount,BYTE cbProvideCard, tagGangCardResult & GangCardResult, BYTE cbDiscardCount);
	//�Ժ�����
	BYTE AnalyseChiHuCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE cbCurrentCard, CChiHuRight &ChiHuRight/*,bool bTingStatus=false*/);
	//���Ʒ���
	BYTE AnalyseTingCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount);
	//���Ʒ�������ȡ����Щ���������Լ��ܺ���Щ��
	//BYTE AnalyseTingCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE cbOutCard[][28]);
	BYTE AnalyseTingCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE& cbOutCardCount,BYTE cbOutCardData[],BYTE cbHuCardCount[],BYTE cbHuCardData[][28]);
	// Check Ting conditions
	bool isPossibleTing(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount);	
	//Check if Kaimen was opened or not
	bool isOpenedKaimen(const tagWeaveItem WeaveItem[], BYTE cbWeaveCount);
	//��ȡ�������ݣ����ƺ����
	BYTE GetHuCard( const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount,BYTE cbHuCardData[]);
	BYTE GetRandHuiPaiCardIndex( );

	//ת������
public:
	//�˿�ת��
	BYTE SwitchToCardData(BYTE cbCardIndex);
	//�˿�ת��
	BYTE SwitchToCardIndex(BYTE cbCardData);
	//�˿�ת��
	BYTE SwitchToCardData(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCardData[MAX_COUNT]);
	//�˿�ת��
	BYTE SwitchToCardIndex(const BYTE cbCardData[], BYTE cbCardCount, BYTE cbCardIndex[MAX_INDEX]);
	

	//��������
public:
	//��Ч�ж�
	bool IsValidCard(BYTE cbCardData);
	//�˿���Ŀ
	BYTE GetCardCount(const BYTE cbCardIndex[MAX_INDEX]);	
	//����˿�
	BYTE GetWeaveCard(WORD wWeaveKind, BYTE cbCenterCard, BYTE cbCardBuffer[4]);

	//�ڲ�����
private:
	bool AddKindItem(tagKindItem &TempKindItem, tagKindItem KindItem[], BYTE &cbKindItemCount, bool &bMagicThree);
	//�����˿�
	bool AnalyseCard(BYTE cbCurrentCard, const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveICount, CAnalyseItemArray & AnalyseItemArray);

	// If this Analyse Item is able to do Hu(��) return ture. if not, return false
	bool isPossibleHu(BYTE cbHuCard, const tagAnalyseItem *pAnalyseItem, BYTE cbWeaveCount);
	
	bool CheckHuFormatStyle(const tagAnalyseItem *pAnalyseItem);
	bool CheckJiaHuStyle(BYTE cbHuCard, const tagAnalyseItem *pAnalyseItem, BYTE cbWeaveCount);
	bool CheckYaoJiuFormat(const tagAnalyseItem *pAnalyseItem);
	bool isYaoJiuCard(BYTE card);
	bool isYaoJiuSubstitute(BYTE card);

	//��������
protected:

	//������
	bool IsPengPeng(const tagAnalyseItem *pAnalyseItem);
	//����ϵ��
	bool IsMaQi(const BYTE cbCardIndex[MAX_INDEX],BYTE cbWeaveCount);
	//ʮ����ϵ��
	bool IsShiSanYao(const BYTE cbCardIndex[MAX_INDEX],BYTE cbWeaveCount);

	bool IsShouBaYi(const tagAnalyseItem *pAnalyseItem, BYTE nWeaveCount);

	bool IsJiaHuFormat(BYTE cbHuPai, const tagAnalyseItem *pAnalyseItem, BYTE nWeaveCount);
	//ƽ��
	bool IsPingHu(const tagAnalyseItem *pAnalyseItem);
	//����
	bool IsJiHu(const tagAnalyseItem *pAnalyseItem);
	//��һɫ
	bool IsQingYiSe(const tagAnalyseItem * pAnalyseItem);	
	//��һɫ
	bool IsHunYiSe(const tagAnalyseItem * pAnalyseItem);	


public:
	//��֤ĳ����Ƿ����������ܲ���
	bool IsSpGangOK(const BYTE cbCardIndex[MAX_INDEX], DWORD dwOpCode);
	//�����п۵�����ܵ�����
	bool TakeOutSpGang(BYTE cbCardIndex[MAX_INDEX], DWORD dwOpCode);
	//�����п۵���ë�ܵ�����
	bool TakeOutCHMGang(BYTE cbCardIndex[MAX_INDEX],BYTE cbCernterCard);

public:
	//��Ĭ��ֵ��ʼ�����ƹ���
	void InitCustomRule();
	//���ö��ƹ���
	void SetCustomRule(tagCustomRule *pRule);

	bool IsChaseArrow(BYTE cbProvidedCardIndex,const tagWeaveItem WeaveItem[], BYTE cbWeaveICount,DWORD dwOpCode);

	bool IsPossibleChaseArrow(const BYTE cbHandCards[MAX_INDEX],const tagWeaveItem WeaveItem[], BYTE cbWeaveICount,DWORD dwOpCode);

#ifdef CARD_DISPATCHER_CONTROL
	void printLogAnalyseItems(BYTE cbHuCard, CAnalyseItemArray* arr);
#endif
};

//////////////////////////////////////////////////////////////////////////////////

#endif