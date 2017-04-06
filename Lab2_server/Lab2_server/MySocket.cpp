#include "stdafx.h"
#include "MySocket.h"
#include "Lab2ServerDlg.h"

int ind = 0;

CMySocket::CMySocket()
{
}


CMySocket::~CMySocket()
{
}

void CMySocket::SetParentDlg(CLab2ServerDlg *pDlg)
{
	m_pDlg = pDlg;
}

void CMySocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	AfxMessageBox(L"Connecting..");
	m_pDlg->OnAccept(ind);
	ind++;
	CSocket::OnAccept(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	AfxMessageBox(L"Data accepted!");
	m_pDlg->OnReceive();
	CSocket::OnReceive(nErrorCode);
}