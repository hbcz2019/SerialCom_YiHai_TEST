
// SerialCommunicationTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSerialCommunicationTestApp: 
// �йش����ʵ�֣������ SerialCommunicationTest.cpp
//

class CSerialCommunicationTestApp : public CWinApp
{
public:
	CSerialCommunicationTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSerialCommunicationTestApp theApp;