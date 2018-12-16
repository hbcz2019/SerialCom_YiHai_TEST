
// SerialCommunicationTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SerialCommunicationTest.h"
#include "SerialCommunicationTestDlg.h"
#include "afxdialogex.h"
#include "SerialPort.h"
#include <AFXPRIV.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSerialCommunicationTestDlg �Ի���



CSerialCommunicationTestDlg::CSerialCommunicationTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERIALCOMMUNICATIONTEST_DIALOG, pParent)
	, m_EditCW(_T(""))
	, FlagHex(0)
	, m_PortNo(1)
	, m_BaudNo(115200)
	, edit_recv(_T(""))
	, FlagHex_Send(0)
	, flag_sendnewline(FALSE)
	, filepath(_T(""))
	, cur_num(0)
	, last_num(0)
	, m_bSerialPortOpened(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialCommunicationTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CW, m_EditCW);
	DDX_Control(pDX, IDC_BUTTON_Open, m_CommOpenClose);
	DDX_Control(pDX, IDC_COMBO_CommPort, m_CommPort);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_CommBaud);
	DDX_Text(pDX, IDC_EDIT_RECV, edit_recv);
	DDX_Check(pDX, IDC_CHECK_NEW_LINE, flag_sendnewline);
	DDX_Text(pDX, IDC_EDIT_OPEN_FILE, filepath);

	DDX_Control(pDX, IDC_COMBO_ASSEMBLY, m_AssemblyLine);
	DDX_Control(pDX, IDC_COMBO_MATERIAL, m_material);
	DDX_Control(pDX, IDC_COMBO_Check, m_AssemblyCheck);

	DDX_Text(pDX, IDC_EDIT_CarNum, m_CarNum);
	DDX_Text(pDX, IDC_EDIT_FinshNum, m_FinshNum);
	DDX_Text(pDX, IDC_EDIT_ResidualNum, m_ResidualNum);
	DDX_Text(pDX, IDC_EDIT_Amount, m_Amount);
	DDX_Text(pDX, IDC_EDIT_TimeRemain, m_TimeRemain);
	DDX_Text(pDX, IDC_EDIT_ALL_StatusDiplay, m_ALL_StatusDiplay);
	DDX_Control(pDX, IDC_BUTTON_TASK, m_Task);
	
}

BEGIN_MESSAGE_MAP(CSerialCommunicationTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Open, &CSerialCommunicationTestDlg::OnBnClickedButtonOpen)
	ON_MESSAGE(WM_COMM_RXCHAR, OnComm)
	ON_BN_CLICKED(IDC_BUTTON_SendTest, &CSerialCommunicationTestDlg::OnBnClickedButtonSendtest)
	ON_BN_CLICKED(IDC_CHECK_Hex, &CSerialCommunicationTestDlg::OnBnClickedCheckHex)
	ON_BN_CLICKED(IDC_BUTTON_EmptyCW, &CSerialCommunicationTestDlg::OnBnClickedButtonEmptycw)
	ON_CBN_SELCHANGE(IDC_COMBO_CommPort, &CSerialCommunicationTestDlg::OnCbnSelchanageComboCommport)
	ON_BN_CLICKED(IDC_CHECK_HEX_SEND, &CSerialCommunicationTestDlg::OnBnClickedCheckHexSend)
	ON_BN_CLICKED(IDC_CHECK_NEW_LINE, &CSerialCommunicationTestDlg::OnBnClickedCheckNewLine)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CSerialCommunicationTestDlg::OnBnClickedButtonOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_CLR_SEND, &CSerialCommunicationTestDlg::OnBnClickedButtonClrSend)
	ON_EN_CHANGE(IDC_EDIT_OPEN_FILE, &CSerialCommunicationTestDlg::OnEnChangeEditOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_SEND_FILE, &CSerialCommunicationTestDlg::OnBnClickedButtonSendFile)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_BAUD, &CSerialCommunicationTestDlg::OnCbnSelchangeComboBaud)
	ON_BN_CLICKED(IDC_BUTTON_TASK, &CSerialCommunicationTestDlg::OnBnClickedButtonTask)
	ON_CBN_SELCHANGE(IDC_COMBO_ASSEMBLY, &CSerialCommunicationTestDlg::OnCbnSelchangeComboAssembly)
//	ON_CBN_SELCHANGE(IDC_COMBO_Check, &CSerialCommunicationTestDlg::OnCbnSelchangeComboCheck)
ON_CBN_SELCHANGE(IDC_COMBO_Check, &CSerialCommunicationTestDlg::OnCbnSelchangeComboCheck)
END_MESSAGE_MAP()


// CSerialCommunicationTestDlg ��Ϣ�������

BOOL CSerialCommunicationTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	HKEY RegKey;
	CString strtemp;
	int nCount = 0;
	CString subKey = _T("HARDWARE\\DEVICEMAP\\SERIALCOMM");

	if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey, NULL, KEY_QUERY_VALUE, &RegKey) == ERROR_SUCCESS)
	{
		edit_recv += "ע���򿪳ɹ�\r\n";
		SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		while (true)
		{
			wchar_t ValueName[_MAX_PATH];
			unsigned char ValueData[_MAX_PATH];
			DWORD nValueSize = _MAX_PATH;
			DWORD nDataSize = _MAX_PATH;
			DWORD nType;

			if (::RegEnumValue(HKEY(RegKey), nCount, ValueName, &nValueSize, NULL, &nType, ValueData, &nDataSize) == ERROR_NO_MORE_ITEMS)
			{
				break;
			}
			edit_recv += ValueName;
			edit_recv += " = ";
			strtemp.Format(_T("%s"), ValueData);
			edit_recv += strtemp;
			edit_recv += "\r\n";
			nCount++;
			m_CommPort.AddString(strtemp);
		}
		m_CommPort.SetCurSel(0);
	}
	edit_recv += "nCount = ";
	strtemp.Format(_T("%d"), nCount);
	edit_recv += strtemp;
	edit_recv += "\r\n";
	SetDlgItemText(IDC_EDIT_RECV, edit_recv);
	::RegCloseKey(RegKey);

	m_CommBaud.AddString(_T("1200"));
	m_CommBaud.AddString(_T("2400"));
	m_CommBaud.AddString(_T("4800"));
	m_CommBaud.AddString(_T("9600"));
	m_CommBaud.AddString(_T("14400"));
	m_CommBaud.AddString(_T("19200"));
	m_CommBaud.AddString(_T("38400"));
	m_CommBaud.AddString(_T("43000"));
	m_CommBaud.AddString(_T("57600"));
	m_CommBaud.AddString(_T("76800"));
	m_CommBaud.AddString(_T("115200"));
	m_CommBaud.AddString(_T("128000"));
	m_CommBaud.AddString(_T("230400"));
	m_CommBaud.AddString(_T("256000"));
	m_CommBaud.AddString(_T("460800"));
	m_CommBaud.AddString(_T("921600"));
	m_CommBaud.AddString(_T("1382400"));

	m_CommBaud.SetCurSel(10);

	m_AssemblyLine.AddString(_T("һ����"));
	m_AssemblyLine.AddString(_T("������"));
	m_AssemblyLine.AddString(_T("������"));
	m_AssemblyLine.AddString(_T("�ĺ���"));
	m_AssemblyLine.AddString(_T("�����"));
	m_AssemblyLine.SetCurSel(0);

	m_AssemblyCheck.AddString(_T("һ����"));
	m_AssemblyCheck.AddString(_T("������"));
	m_AssemblyCheck.AddString(_T("������"));
	m_AssemblyCheck.AddString(_T("�ĺ���"));
	m_AssemblyCheck.AddString(_T("�����"));

	m_material.AddString(_T("һ������65KG"));
	m_material.AddString(_T("��������50KG"));
	m_material.AddString(_T("��������100KG"));
	m_material.AddString(_T("�ļ�����30KG"));
	m_material.AddString(_T("�弶����40KG"));
	m_material.SetCurSel(0);

	SetDlgItemText(IDC_EDIT_CarNum, L"�뷢������");
	SetDlgItemText(IDC_EDIT_FinshNum, L"�뷢������");
	SetDlgItemText(IDC_EDIT_ResidualNum, L"�뷢������");
	SetDlgItemText(IDC_EDIT_Amount, L"�뷢������");
	SetDlgItemText(IDC_EDIT_TimeRemain, L"�ѽ���");
	SetDlgItemText(IDC_EDIT_ALL_StatusDiplay, L"�����ڹ�������ˮ��");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSerialCommunicationTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSerialCommunicationTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSerialCommunicationTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSerialCommunicationTestDlg::OnBnClickedButtonOpen()
{
	CString strtemp;
	BOOL Isclosed = FALSE;
	if (m_bSerialPortOpened == 0)
	{
		if (m_PortNo)
		{
			m_bSerialPortOpened = m_SerialPort.InitPort(this,
				m_PortNo,
				m_BaudNo,
				'N',
				8,
				1,
				EV_RXCHAR | EV_CTS,
				65536,
				1000,
				1000,
				1000,
				1000,
				1000);
			m_bSerialPortOpened = m_bSerialPortOpened && m_SerialPort.StartMonitoring();
			if (m_bSerialPortOpened)
			{
				edit_recv += "COM";
				strtemp.Format(_T("%u"), m_PortNo);
				edit_recv += strtemp;
				edit_recv += "�Ѵ򿪣�������115200\r\n";
				SetDlgItemText(IDC_EDIT_RECV, edit_recv);
				cur_num = 0;
				last_num = 0;
				memset(rxbuf, 0, 20000);
				rx_num = 0;
				m_CommOpenClose.SetWindowText(_T("�رմ���"));
			}
			else
			{
				edit_recv += "���ڲ����ڻ�ռ�ã��򿪴���ʧ�ܣ�\r\n";
				SetDlgItemText(IDC_EDIT_RECV, edit_recv);
			}
		}
		else
		{
			edit_recv += "����ѡ�񴮿�\r\n";
			SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		}
	}
	else
	{
		Isclosed = m_SerialPort.StopMonitoring();
		if (Isclosed)
		{
			m_SerialPort.ClosePort();
			edit_recv += "�����ѹر�\r\n";
			SetDlgItemText(IDC_EDIT_RECV, edit_recv);
			m_bSerialPortOpened = FALSE;
			m_CommOpenClose.SetWindowText(_T("�򿪴���"));
		}
		else
		{
			edit_recv += "����δ�ɹ��ر�\r\n";
			SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		}
	}

}



int CSerialCommunicationTestDlg::String2Hex(CString str, CByteArray &senddata)
{
	int hexdata, lowhexdata;
	int hexdatalen = 0;
	int len = str.GetLength();
	senddata.SetSize(len / 2);
	for (int i = 0; i < len;)
	{
		char lstr, hstr = str[i];
		if (hstr == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		lstr = str[i];
		hexdata = ConvertHexChar(hstr);
		lowhexdata = ConvertHexChar(lstr);
		if ((hexdata == 16) || (lowhexdata == 16))
			break;
		else
			hexdata = hexdata * 16 + lowhexdata;
		i++;
		senddata[hexdatalen] = (char)hexdata;
		hexdatalen++;
	}
	senddata.SetSize(hexdatalen);
	return hexdatalen;
}
//����һ�����ַ�ת��Ϊ��Ӧ��ʮ������ֵ�ĺ���
//�ö�C�������϶������ҵ�
//���ܣ�������0-F֮����ַ�����ת��Ϊ��Ӧ��ʮ�������ַ������򷵻�-1
char CSerialCommunicationTestDlg::ConvertHexChar(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else return (-1);
}

void CSerialCommunicationTestDlg::OnBnClickedButtonSendtest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CByteArray hexdata;
	CString strtemp;
	if (m_bSerialPortOpened)
	{
		if (FlagHex_Send)    //16���Ʒ���
		{
			GetDlgItemText(IDC_EDIT_CW, m_EditCW);
			int len = String2Hex(m_EditCW, hexdata); //�˴����ص�len�������ڼ��㷢���˶��ٸ�ʮ��������
			if (flag_sendnewline)
			{
				hexdata.Add(0x0d);      //��ӻس�����
				hexdata.Add(0x0a);
			}
			m_SerialPort.WriteToPort((char*)&hexdata[0]);
		}
		else     //ascii����
		{
			GetDlgItemText(IDC_EDIT_CW, m_EditCW);
			if (flag_sendnewline)
			{
				strtemp = "\r\n";     //��ӻس�����
				m_EditCW += strtemp;
			}

			m_SerialPort.WriteToPort(m_EditCW);
		}
	}
}

LONG CSerialCommunicationTestDlg::OnComm(WPARAM ch, LPARAM port)
{
	//m_EditCW += "�����յ�����\r\n";
	CString strtemp;
	if (FlagHex)
	{
		strtemp.Format(_T("%.2x "), (BYTE)ch);
		edit_recv += strtemp;
		SetDlgItemText(IDC_EDIT_RECV, edit_recv);
	}
	else
	{
		last_num = cur_num;
		rxbuf[rx_num++] += (char)ch;
		if(rx_num ==1)
			SetTimer(1, 2, NULL);  //2ms���붨ʱ���ص�����
		

		/*buf [i++]+= (char)ch;
		if (buf[i - 2] == 0x0d && buf[i-1] == 0x0a)
		{
			buf[i - 2] = 0;
			buf[i-1] = 0;
			edit_recv += buf;
			i = 0;
			memset(buf,0,20000);
			SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		}	*/
	}
	
	return 0;
}




void CSerialCommunicationTestDlg::OnBnClickedCheckHex()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString edit_data;
	CString strtemp;
	LPCSTR b;
	int i;
	if (IsDlgButtonChecked(IDC_CHECK_Hex) == BST_CHECKED)
	{
		
		GetDlgItemText(IDC_EDIT_RECV, edit_data);
		edit_recv.Empty();
		USES_CONVERSION;
		b = T2A(edit_data.GetBuffer(edit_data.GetLength()));
		for (i = 0; i < edit_data.GetLength(); i++)
		{
			strtemp.Format(_T("%.2x "), (BYTE)b[i]);
			edit_recv += strtemp;
		}
		
		SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		
		FlagHex = 1;
	}
	else
	{
		edit_recv.Empty();
		SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		FlagHex = 0;
	}		
}


void CSerialCommunicationTestDlg::OnBnClickedButtonEmptycw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	edit_recv.Empty();
	SetDlgItemText(IDC_EDIT_RECV, edit_recv);
}


void CSerialCommunicationTestDlg::OnCbnSelchanageComboCommport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int Index;
	CString strCBText;
	Index = m_CommPort.GetCurSel();
	m_CommPort.GetLBText(Index, strCBText);
	edit_recv += strCBText;
	strCBText.Delete(0, 3);
	/*edit_recv += strCBText;*/
	m_PortNo = atoi((LPSTR)(LPCTSTR)strCBText);
	SetDlgItemText(IDC_EDIT_RECV, edit_recv);
}


void CSerialCommunicationTestDlg::OnBnClickedCheckHexSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString edit_data;
	CString strtemp;
	LPCSTR b;
	int i;
	if (IsDlgButtonChecked(IDC_CHECK_HEX_SEND) == BST_CHECKED)
	{
		FlagHex_Send = 1;
		GetDlgItemText(IDC_EDIT_CW, edit_data);
		m_EditCW.Empty();
		USES_CONVERSION;
		b = T2A(edit_data.GetBuffer(edit_data.GetLength()));
		for (i = 0; i < edit_data.GetLength(); i++)
		{
			strtemp.Format(_T("%.2x "), (BYTE)b[i]);
			m_EditCW += strtemp;
		}
		SetDlgItemText(IDC_EDIT_CW, m_EditCW);

	}
	else
	{
		FlagHex_Send = 0;
	}
}


void CSerialCommunicationTestDlg::OnBnClickedCheckNewLine()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (IsDlgButtonChecked(IDC_CHECK_NEW_LINE) == BST_CHECKED)
	{
		flag_sendnewline = 1;
	}
	else
	{
		flag_sendnewline = 0;
	}
}


void CSerialCommunicationTestDlg::OnBnClickedButtonOpenFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL isOpen = TRUE;     //�Ƿ��(����Ϊ����)  
	CString defaultDir = L"�ĵ�";   //Ĭ�ϴ򿪵��ļ�·��  
	CString fileName = L"";         //Ĭ�ϴ򿪵��ļ���  
	CString filter = L"Text Files (*.TXT)|*.txt|HEX (*.hex)|*.hex|BIN (*.bin)|*.bin|C (*.c;*.c++)|*.c;*.c++|ASM (*.s)|*.s|header (*.h)|*.h|All Files (*.*)|*.*|";  //�ļ����ǵ�����  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	if (result ==IDOK) {
		filepath = openFileDlg.GetPathName();
	}
	CWnd::SetDlgItemTextW(IDC_EDIT_OPEN_FILE, filepath);
}


void CSerialCommunicationTestDlg::OnBnClickedButtonClrSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_EditCW.Empty();
	SetDlgItemText(IDC_EDIT_CW, m_EditCW);
}


void CSerialCommunicationTestDlg::OnEnChangeEditOpenFile()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CSerialCommunicationTestDlg::OnBnClickedButtonSendFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStdioFile file;
	//���ļ�

	if (!file.Open(filepath, CFile::modeRead))

	{

		::AfxMessageBox(_T("�ļ���ʧ�ܡ�"));

		return;

	}

	//���ļ�
	DWORD len;
	len = file.GetLength();
	/*CEdit* pBoxOne;*/
	char *pReadData = new char[len + 5]; // �����ڴ�
	
	file.Read(pReadData, len);                                       //  ���ﱣ��Ķ�ȡ�ļ�������
	pReadData[len] = 0;
	pReadData[len + 1] = 0;
	pReadData[len + 2] = 0;
	pReadData[len + 3] = 0;
	pReadData[len+4] = 0;
	/*pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT_RECV);
	::SetWindowTextA(pBoxOne->m_hWnd, pReadData); */ //ǿ����ΪASCII�����

	/*CString strText = _T("");

	while (file.ReadString(strText))
		edit_recv += strText;
	SetDlgItemText(IDC_EDIT_RECV, edit_recv);  *///��UNICODE�����
	
	//�ر��ļ�

	file.Close();

	CByteArray hexdata;
	char *strtemp;
	if (m_bSerialPortOpened)
	{
		if (FlagHex_Send)    //16���Ʒ���
		{
			int len = String2Hex((CString)pReadData, hexdata); //�˴����ص�len�������ڼ��㷢���˶��ٸ�ʮ��������
			if (flag_sendnewline)
			{
				hexdata.Add(0x0d);      //��ӻس�����
				hexdata.Add(0x0a);
			}
			m_SerialPort.WriteToPort((char*)&hexdata[0]);
		}
		else     //ascii����
		{
			if (flag_sendnewline)
			{
				strtemp = "\r\n";     //��ӻس�����
				(CString)pReadData += strtemp;
			}
			m_SerialPort.WriteToPort(pReadData);
		}
	}

}

void CSerialCommunicationTestDlg::OnTimer(UINT nIDEvent)
{
	cur_num++;
	if(cur_num>(last_num+3))
	{
		rxbuf[rx_num] = 0;
		edit_recv += rxbuf;
		rx_num = 0;
		memset(rxbuf, 0, 20000);
		SetDlgItemText(IDC_EDIT_RECV, edit_recv);
		cur_num = 0;
		last_num = 0;
		KillTimer(1);
	}
	
}



void CSerialCommunicationTestDlg::OnCbnSelchangeComboBaud()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int Index;
	CString strCBText;
	Index = m_CommBaud.GetCurSel();
	m_CommBaud.GetLBText(Index, strCBText);
	edit_recv += strCBText;
	m_BaudNo = atoi((LPSTR)(LPCTSTR)strCBText);
	SetDlgItemText(IDC_EDIT_RECV, edit_recv);
}


void CSerialCommunicationTestDlg::OnBnClickedButtonTask()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (m_bPublihTask == 0)
	{		
		int Index;
		CString AssemblyLine;
		Index = m_AssemblyLine.GetCurSel();

		switch (Index)
		{
			case 0://0����ˮ��

				break;
			case 1:
				break;
			case 2:
				break;
			default:
				break;
		}
		//if ()
		//{
		//	GetDlgItemText(IDC_EDIT_CW, m_CarNum);
		//	
		//}

			if (m_bPublihTask==0)//������յ���ȷ�Ĵӻ��ϱ���Ӧ���������ʾ���񷢲��ɹ�
			{
				m_bPublihTask = 1;//���񷢲��ɹ�
				m_Task.SetWindowText(_T("��������"));
				
			}
			else
			{
				m_Task.SetWindowText(_T("��������"));
				m_bPublihTask = 0;//���񷢲�ʧ��
			
			}
	}
	else if(m_bPublihTask==1)
	{
		m_Task.SetWindowText(_T("��������"));
		m_bPublihTask = 0;
	}
}


void CSerialCommunicationTestDlg::OnCbnSelchangeComboAssembly()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


}

void CSerialCommunicationTestDlg::OnCbnSelchangeComboCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


}
