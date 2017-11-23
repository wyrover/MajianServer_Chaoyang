#ifndef GAME_DLG_CUSTOM_RULE_HEAD_FILE
#define GAME_DLG_CUSTOM_RULE_HEAD_FILE

#pragma once

#include "Stdafx.h"


#define DEFAULT_INNINGS_COUNT       16
#define INNINGS_COUNT_2             24

//////////////////////////////////////////////////////////////////////////////////

//���ýṹ
struct tagCustomRule
{
	//��������
	BYTE							cbMaCount;							//������1��һ��ȫ�У�2-6����Ӧ���� // no need in Chaoyang
	BYTE							cbPlayerCount;						//���� 2-4						   //Always 4 in Chaoyang

	//ʱ�䶨��
	BYTE							cbTimeOutCard;						//����ʱ��
	BYTE							cbTimeOperateCard;					//����ʱ��
	BYTE							cbTimeStartGame;					//��ʼʱ��	
	
	// Added custome game settings for Chaoyang
	BYTE							cbInningsCount_cy;
	bool							bEnabled_DianPao;
	bool							bEnabled_FengGang;
	bool							bEnabled_HuiPai;
	bool							bEnabled_BaoPai;
	bool							bEnabled_ZhanLiHu;
	bool							bEnabled_JiaHu;
	bool							bEnabled_ChangMaoGang;
};

//////////////////////////////////////////////////////////////////////////////////

//���ô���
class CDlgCustomRule : public CDialog
{
	//���ñ���
protected:
	tagCustomRule					m_CustomRule;						//���ýṹ

	//��������
public:
	//���캯��
	CDlgCustomRule();
	//��������
	virtual ~CDlgCustomRule();

	//���غ���
protected:
	//���ú���
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();
	//ȡ����Ϣ
	virtual VOID OnCancel();

private:
	VOID CDlgCustomRule::OnClickChechBox(UINT nIDbutton);

	//���ܺ���
public:
	//���¿ؼ�
	bool FillDataToControl();
	//��������
	bool FillControlToData();

	//���ú���
public:
	//��ȡ����
	bool GetCustomRule(tagCustomRule & CustomRule);
	//��������
	bool SetCustomRule(tagCustomRule & CustomRule);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif