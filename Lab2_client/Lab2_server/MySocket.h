#pragma once
#include "afxsock.h"

class CLab2ServerDlg;		// client

class CMySocket : public CSocket
{
public:
	CLab2ServerDlg* m_pDlg;			// client!

	void SetParentDlg(CLab2ServerDlg *pDlg);
	virtual void OnReceive(int nErrorCode);
	CMySocket();
	~CMySocket();
};

