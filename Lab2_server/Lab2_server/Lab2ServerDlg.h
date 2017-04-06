
// Lab2ServerDlg.h : ���� ���������
//

#pragma once
#include "MySocket.h"
#include "resource.h"

// ���������� ���� CLab2ServerDlg
class CLab2ServerDlg : public CDialogEx
{
// ��������
public:
	CLab2ServerDlg(CWnd* pParent = NULL);	// ����������� �����������

	CMySocket m_pListenSocket;
	CMySocket m_pConnectSocket;
	CMySocket m_pConnectSocket2;

// ������ ����������� ����
	enum { IDD = IDD_LAB2_SERVER_DIALOG };

	void OnAccept(int ind);
	void OnReceive();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpenDrawClick();
	afx_msg void OnStartClicked();
	afx_msg void OnPointClicked();
	afx_msg void OnLineClicked();
	afx_msg void OnCircleClicked();
	afx_msg void OnRectangleClicked();
	CString m_sData;
	afx_msg void OnListenClicked();
};