
// Lab2ServerDlg.h : файл заголовка
//

#pragma once

#include "MySocket.h"
#include "resource.h"
#include "afxwin.h"

// диалоговое окно CLab2ServerDlg
class CLab2ServerDlg : public CDialogEx
{
// Создание
public:
	CLab2ServerDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_LAB2_SERVER_DIALOG };
	void OnReceive();

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV
	
	CMySocket m_pConnectSocket;

// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
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