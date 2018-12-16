
// SerialCommunicationTestDlg.h : ͷ�ļ�
//
#include "SerialPort.h"
#pragma once


// CSerialCommunicationTestDlg �Ի���
class CSerialCommunicationTestDlg : public CDialogEx
{
// ����
public:
	CSerialCommunicationTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALCOMMUNICATIONTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LONG OnComm(WPARAM ch, LPARAM port);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	CSerialPort m_SerialPort;
	BOOL  m_bSerialPortOpened; //��־�����Ƿ��
	BOOL  m_bPublihTask; //��־�����Ƿ񷢲�
	CButton m_CommOpenClose;
	CString m_EditCW;
	CComboBox m_CommPort;
	unsigned int m_PortNo;
	CComboBox m_CommBaud;

	CString m_CarNum;//IDC_EDIT_CarNum-���ƺ�
	CString m_FinshNum;//IDC_EDIT_FinshNum-��ǰ��ˮ���������
	CString m_ResidualNum;//IDC_EDIT_ResidualNum-��ǰ��ˮ��ʣ���ᵥ����
	CString m_Amount;//IDC_EDIT_Amount-��ǰ��ˮ����Ҫ�ᵥ��������
	CString m_TimeRemain;// IDC_EDIT_TimeRemain-��ǰ��ˮ�߻���೤ʱ������ᵥ
	CString m_ALL_StatusDiplay;//IDC_EDIT_ALL_StatusDiplay- ������ˮ������״̬
	CComboBox m_material;//IDC_COMBO_MATERIAL-��������
	CComboBox m_AssemblyLine;//�����������ˮ�ߺ�
	CButton m_Task;
	CComboBox m_AssemblyCheck;//��ѯ��ˮ������
	CString PushTask_List;//����������嵥��Ϣ���ݻ���

	unsigned int m_BaudNo;
	afx_msg void OnBnClickedButtonSendtest();
	afx_msg void OnBnClickedCheckHex();
	int FlagHex;   //16������ʾ��ASCII��ʾ��־λ��1--16������ʾ  0--ASCII��ʾ
	afx_msg void OnBnClickedButtonEmptycw();
	afx_msg void OnCbnSelchanageComboCommport();
	// ���յ������ݷŵ����ַ�����������ʾ
	CString edit_recv;
	int FlagHex_Send;  //16���Ʒ�����ASCII���ͱ�־λ��1--16���Ʒ���  0--ASCII����
	afx_msg void OnBnClickedCheckHexSend();
	int String2Hex(CString str, CByteArray &senddata);
	char ConvertHexChar(char ch);
	// �������б�־λ��1--���ͻس�  0--�����ͻس�
	BOOL flag_sendnewline;
	afx_msg void OnBnClickedCheckNewLine();
	afx_msg void OnBnClickedButtonOpenFile();
	// �򿪵��ļ�
	CString filepath;
	char rxbuf[20000];
	int last_num,cur_num,rx_num;
	afx_msg void OnBnClickedButtonClrSend();
	afx_msg void OnEnChangeEditOpenFile();
	afx_msg void OnBnClickedButtonSendFile();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCbnSelchangeComboBaud();
	afx_msg void OnBnClickedButtonTask();
	afx_msg void OnCbnSelchangeComboAssembly();
//	afx_msg void OnCbnSelchangeComboCheck();
	afx_msg void OnCbnSelchangeComboCheck();
};
