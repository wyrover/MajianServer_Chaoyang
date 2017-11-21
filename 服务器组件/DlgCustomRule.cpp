#include "Stdafx.h"
#include "Resource.h"
#include "DlgCustomRule.h"

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgCustomRule, CDialog)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

#define DEFAULT_INNINGS_COUNT       16
#define INNINGS_COUNT_2             24

//���캯��
CDlgCustomRule::CDlgCustomRule() : CDialog(IDD_CUSTOM_RULE)
{
	//���ñ���
	ZeroMemory(&m_CustomRule,sizeof(m_CustomRule));

	return;
}

//��������
CDlgCustomRule::~CDlgCustomRule()
{
}

//���ú���
BOOL CDlgCustomRule::OnInitDialog()
{
	__super::OnInitDialog();

	//���ÿؼ�
	((CEdit *)GetDlgItem(IDC_TIME_OUT_CARD))->LimitText(2);
	((CEdit *)GetDlgItem(IDC_TIME_START_GAME))->LimitText(2);
	((CEdit *)GetDlgItem(IDC_TIME_OPERATE_CARD))->LimitText(2);
	((CEdit *)GetDlgItem(IDC_MA_COUNT))->LimitText(1);
	((CEdit *)GetDlgItem(IDC_PLAYER_COUNT))->LimitText(1);
	//���²���
	FillDataToControl();

	return FALSE;
}

//ȷ������
VOID CDlgCustomRule::OnOK() 
{ 
	//Ͷ����Ϣ
	GetParent()->PostMessage(WM_COMMAND,MAKELONG(IDOK,0),0);

	return;
}

//ȡ����Ϣ
VOID CDlgCustomRule::OnCancel() 
{ 
	//Ͷ����Ϣ
	GetParent()->PostMessage(WM_COMMAND,MAKELONG(IDCANCEL,0),0);

	return;
}

//���¿ؼ�
bool CDlgCustomRule::FillDataToControl()
{
	//��������
	SetDlgItemInt(IDC_TIME_OUT_CARD,m_CustomRule.cbTimeOutCard);
	SetDlgItemInt(IDC_TIME_START_GAME,m_CustomRule.cbTimeStartGame);
	SetDlgItemInt(IDC_TIME_OPERATE_CARD,m_CustomRule.cbTimeOperateCard);

	//��Ϸ����
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

//��������
bool CDlgCustomRule::FillControlToData()
{
	//��������
	m_CustomRule.cbTimeOutCard=(BYTE)GetDlgItemInt(IDC_TIME_OUT_CARD);
	m_CustomRule.cbTimeStartGame=(BYTE)GetDlgItemInt(IDC_TIME_START_GAME);
	m_CustomRule.cbTimeOperateCard=(BYTE)GetDlgItemInt(IDC_TIME_OPERATE_CARD);

	//��Ϸ����
	m_CustomRule.cbMaCount=(BYTE)GetDlgItemInt(IDC_MA_COUNT);
	m_CustomRule.cbPlayerCount=(BYTE)GetDlgItemInt(IDC_PLAYER_COUNT);
	//��ʼʱ��
	if ((m_CustomRule.cbTimeStartGame<5)||(m_CustomRule.cbTimeStartGame>60))
	{
		AfxMessageBox(TEXT("��ʼʱ�����÷�Χ�������������ã�"),MB_ICONSTOP);
		return false;
	}

	//����ʱ��
	if ((m_CustomRule.cbTimeOperateCard<5)||(m_CustomRule.cbTimeOperateCard>60))
	{
		AfxMessageBox(TEXT("����ʱ�����÷�Χ�������������ã�"),MB_ICONSTOP);
		return false;
	}

	//����ʱ��
	if ((m_CustomRule.cbTimeOutCard<5)||(m_CustomRule.cbTimeOutCard>60))
	{
		AfxMessageBox(TEXT("����ʱ�����÷�Χ�������������ã�"),MB_ICONSTOP);
		return false;
	}

	//����
	if ((m_CustomRule.cbMaCount<1)||(m_CustomRule.cbMaCount>6))
	{
		AfxMessageBox(TEXT("�������÷�Χ�������������ã�"),MB_ICONSTOP);
		return false;
	}

	//����
	if ((m_CustomRule.cbPlayerCount<2)||(m_CustomRule.cbPlayerCount>4))
	{
		AfxMessageBox(TEXT("��Ϸ������Χ�������������ã�"),MB_ICONSTOP);
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

//��ȡ����
bool CDlgCustomRule::GetCustomRule(tagCustomRule & CustomRule)
{
	//��ȡ����
	if (FillControlToData()==true)
	{
		CustomRule=m_CustomRule;
		return true;
	}

	return false;
}

//��������
bool CDlgCustomRule::SetCustomRule(tagCustomRule & CustomRule)
{
	//���ñ���
	m_CustomRule=CustomRule;

	//���²���
	if (m_hWnd!=NULL) FillDataToControl();

	return true;
}

//////////////////////////////////////////////////////////////////////////////////
