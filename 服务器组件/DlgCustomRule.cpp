#include "Stdafx.h"
#include "Resource.h"
#include "DlgCustomRule.h"

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgCustomRule, CDialog)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

#define DEFAULT_INNINGS_COUNT       16
#define INNINGS_COUNT_2             24

//构造函数
CDlgCustomRule::CDlgCustomRule() : CDialog(IDD_CUSTOM_RULE)
{
	//设置变量
	ZeroMemory(&m_CustomRule,sizeof(m_CustomRule));

	return;
}

//析构函数
CDlgCustomRule::~CDlgCustomRule()
{
}

//配置函数
BOOL CDlgCustomRule::OnInitDialog()
{
	__super::OnInitDialog();

	//设置控件
	((CEdit *)GetDlgItem(IDC_TIME_OUT_CARD))->LimitText(2);
	((CEdit *)GetDlgItem(IDC_TIME_START_GAME))->LimitText(2);
	((CEdit *)GetDlgItem(IDC_TIME_OPERATE_CARD))->LimitText(2);
	((CEdit *)GetDlgItem(IDC_MA_COUNT))->LimitText(1);
	((CEdit *)GetDlgItem(IDC_PLAYER_COUNT))->LimitText(1);
	//更新参数
	FillDataToControl();

	return FALSE;
}

//确定函数
VOID CDlgCustomRule::OnOK() 
{ 
	//投递消息
	GetParent()->PostMessage(WM_COMMAND,MAKELONG(IDOK,0),0);

	return;
}

//取消消息
VOID CDlgCustomRule::OnCancel() 
{ 
	//投递消息
	GetParent()->PostMessage(WM_COMMAND,MAKELONG(IDCANCEL,0),0);

	return;
}

//更新控件
bool CDlgCustomRule::FillDataToControl()
{
	//设置数据
	SetDlgItemInt(IDC_TIME_OUT_CARD,m_CustomRule.cbTimeOutCard);
	SetDlgItemInt(IDC_TIME_START_GAME,m_CustomRule.cbTimeStartGame);
	SetDlgItemInt(IDC_TIME_OPERATE_CARD,m_CustomRule.cbTimeOperateCard);

	//游戏控制
	SetDlgItemInt(IDC_MA_COUNT,m_CustomRule.cbMaCount);
	SetDlgItemInt(IDC_PLAYER_COUNT,m_CustomRule.cbPlayerCount);

	((CButton*)GetDlgItem( IDC_RADIO_16 ))->SetCheck(m_CustomRule.cbInningsCount_cy==DEFAULT_INNINGS_COUNT);
	((CButton*)GetDlgItem( IDC_RADIO_24 ))->SetCheck(m_CustomRule.cbInningsCount_cy!=DEFAULT_INNINGS_COUNT);
	((CButton*)GetDlgItem( IDC_CHK_DIANPAO ))->SetCheck(m_CustomRule.bEnabled_DianPao);
	((CButton*)GetDlgItem( IDC_CHK_FENGGANG ))->SetCheck(m_CustomRule.bEnabled_FengGang);
	((CButton*)GetDlgItem( IDC_CHK_HUIPAI ))->SetCheck(m_CustomRule.bEnabled_HuiPai);
	((CButton*)GetDlgItem( IDC_CHK_BAOPAI ))->SetCheck(m_CustomRule.bEnabled_BaoPai);
	((CButton*)GetDlgItem( IDC_CHK_ZHUANGLIHU ))->SetCheck(m_CustomRule.bEnabled_ZhanLiHu);
	((CButton*)GetDlgItem( IDC_CHK_JIAHU ))->SetCheck(m_CustomRule.bEnabled_JiaHu);
	((CButton*)GetDlgItem( IDC_CHK_CHANGMAO ))->SetCheck(m_CustomRule.bEnabled_ChangMaoGang);
	return true;
}

//更新数据
bool CDlgCustomRule::FillControlToData()
{
	//设置数据
	m_CustomRule.cbTimeOutCard=(BYTE)GetDlgItemInt(IDC_TIME_OUT_CARD);
	m_CustomRule.cbTimeStartGame=(BYTE)GetDlgItemInt(IDC_TIME_START_GAME);
	m_CustomRule.cbTimeOperateCard=(BYTE)GetDlgItemInt(IDC_TIME_OPERATE_CARD);

	//游戏控制
	m_CustomRule.cbMaCount=(BYTE)GetDlgItemInt(IDC_MA_COUNT);
	m_CustomRule.cbPlayerCount=(BYTE)GetDlgItemInt(IDC_PLAYER_COUNT);
	//开始时间
	if ((m_CustomRule.cbTimeStartGame<5)||(m_CustomRule.cbTimeStartGame>60))
	{
		AfxMessageBox(TEXT("开始时间设置范围错误，请重新设置！"),MB_ICONSTOP);
		return false;
	}

	//操作时间
	if ((m_CustomRule.cbTimeOperateCard<5)||(m_CustomRule.cbTimeOperateCard>60))
	{
		AfxMessageBox(TEXT("操作时间设置范围错误，请重新设置！"),MB_ICONSTOP);
		return false;
	}

	//出牌时间
	if ((m_CustomRule.cbTimeOutCard<5)||(m_CustomRule.cbTimeOutCard>60))
	{
		AfxMessageBox(TEXT("出牌时间设置范围错误，请重新设置！"),MB_ICONSTOP);
		return false;
	}

	//码数
	if ((m_CustomRule.cbMaCount<1)||(m_CustomRule.cbMaCount>6))
	{
		AfxMessageBox(TEXT("码数设置范围错误，请重新设置！"),MB_ICONSTOP);
		return false;
	}

	//人数
	if ((m_CustomRule.cbPlayerCount<2)||(m_CustomRule.cbPlayerCount>4))
	{
		AfxMessageBox(TEXT("游戏人数范围错误，请重新设置！"),MB_ICONSTOP);
		return false;
	}

	m_CustomRule.cbInningsCount_cy	= ((CButton*)GetDlgItem( IDC_RADIO_16 ))->GetCheck() ? DEFAULT_INNINGS_COUNT : INNINGS_COUNT_2;
	m_CustomRule.bEnabled_DianPao	= ((CButton*)GetDlgItem( IDC_CHK_DIANPAO ))->GetCheck()==BST_CHECKED;
	m_CustomRule.bEnabled_FengGang= ((CButton*)GetDlgItem( IDC_CHK_FENGGANG ))->GetCheck()==BST_CHECKED;
	m_CustomRule.bEnabled_HuiPai	= ((CButton*)GetDlgItem( IDC_CHK_HUIPAI ))->GetCheck()==BST_CHECKED;
	m_CustomRule.bEnabled_BaoPai	= ((CButton*)GetDlgItem( IDC_CHK_BAOPAI ))->GetCheck()==BST_CHECKED;
	m_CustomRule.bEnabled_ZhanLiHu= ((CButton*)GetDlgItem( IDC_CHK_ZHUANGLIHU ))->GetCheck()==BST_CHECKED;
	m_CustomRule.bEnabled_JiaHu	= ((CButton*)GetDlgItem( IDC_CHK_JIAHU ))->GetCheck()==BST_CHECKED;
	m_CustomRule.bEnabled_ChangMaoGang = ((CButton*)GetDlgItem( IDC_CHK_CHANGMAO ))->GetCheck()==BST_CHECKED;
	return true;
}

//读取配置
bool CDlgCustomRule::GetCustomRule(tagCustomRule & CustomRule)
{
	//读取参数
	if (FillControlToData()==true)
	{
		CustomRule=m_CustomRule;
		return true;
	}

	return false;
}

//设置配置
bool CDlgCustomRule::SetCustomRule(tagCustomRule & CustomRule)
{
	//设置变量
	m_CustomRule=CustomRule;

	//更新参数
	if (m_hWnd!=NULL) FillDataToControl();

	return true;
}

//////////////////////////////////////////////////////////////////////////////////
