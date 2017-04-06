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
	m_pDlg = pDlg; //«адаем указатель на диалоговое окно
}

void CMySocket::OnReceive(int nErrorCode)
{
	m_pDlg->OnReceive();
	CSocket::OnReceive(nErrorCode);
}