
// Lab2ServerDlg.h : ���� ���������
//

#pragma once

#include "MySocket.h"
#include "resource.h"
#include "afxwin.h"

// ���������� ���� CLab2ServerDlg
class CLab2ServerDlg : public CDialogEx
{
// ��������
public:
	CLab2ServerDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_LAB2_SERVER_DIALOG };
	void OnReceive();

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV
	
	CMySocket m_pConnectSocket;

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
	afx_msg void OnConnectClicked();
	afx_msg void OnSendClicked();
	int portIndex;
	afx_msg void OnBnClickedCancel();
	CComboBox portCombobox;
};