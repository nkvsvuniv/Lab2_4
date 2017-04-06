#pragma once
#include "afxsock.h"

class CLab2ServerDlg;

class CMySocket : public CSocket
{
public:
	CLab2ServerDlg* m_pDlg;

	void SetParentDlg(CLab2ServerDlg *pDlg);
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	CMySocket();
	~CMySocket();
};

