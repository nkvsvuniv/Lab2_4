#include "stdafx.h"
#include "MySocket.h"
#include "Lab2ServerDlg.h"

CMySocket::CMySocket()
{
}


CMySocket::~CMySocket()
{
}


void CMySocket::SetParentDlg(CLab2ServerDlg *pDlg)
{
	m_pDlg = pDlg; //������ ��������� �� ���������� ����
}

void CMySocket::OnReceive(int nErrorCode)
{
	m_pDlg->OnReceive();
	CSocket::OnReceive(nErrorCode);
}