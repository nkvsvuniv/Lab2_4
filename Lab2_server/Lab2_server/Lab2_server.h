
// Lab2_server.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CLab2S:
// � ���������� ������� ������ ��. Lab2_server.cpp
//

class CLab2S : public CWinApp
{
public:
	CLab2S();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CLab2S theApp;