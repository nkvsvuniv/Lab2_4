
// Lab2ServerDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Lab2_server.h"
#include "Lab2ServerDlg.h"
#include "afxdialogex.h"
#include "glutMFC.h"
#include <afxdb.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

glutMFC gl;

void display()
{
	gl.display();
}

void resize(int w, int h)
{
	gl.resize(w, h);
}

void render()
{
	gl.render();
}

void mouse(int bt, int st, int x, int y)
{
	gl.mouse(bt, st, x, y);
}

void mouseMove(int x, int y)
{
	gl.mouseMove(x, y);
}

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CLab2ServerDlg



CLab2ServerDlg::CLab2ServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLab2ServerDlg::IDD, pParent)
	, m_sData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLab2ServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATA, m_sData);
}

BEGIN_MESSAGE_MAP(CLab2ServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLab2ServerDlg::OnOpenDrawClick)
	ON_BN_CLICKED(IDC_BUTTON1, &CLab2ServerDlg::OnStartClicked)
	ON_BN_CLICKED(IDC_BUTTON4, &CLab2ServerDlg::OnPointClicked)
	ON_BN_CLICKED(IDC_BUTTON3, &CLab2ServerDlg::OnLineClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CLab2ServerDlg::OnCircleClicked)
	ON_BN_CLICKED(IDC_BUTTON5, &CLab2ServerDlg::OnRectangleClicked)
	ON_BN_CLICKED(IDC_LISTEN, &CLab2ServerDlg::OnListenClicked)
END_MESSAGE_MAP()


// обработчики сообщений CLab2ServerDlg

BOOL CLab2ServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	m_pListenSocket.SetParentDlg(this);
	m_pConnectSocket.SetParentDlg(this);
	m_pConnectSocket2.SetParentDlg(this);
	m_pListenSocket.Create(2000);			//Создаем сокет на 2000 порту

	CDatabase db1;
	db1.Open(L"Lab2src");
	db1.ExecuteSQL(L"DELETE * FROM primitives");
	//db1.CommitTrans();
	db1.Close();

	CString type, p1, p2, p3, p4;
	CDatabase db;
	db.Open(L"Lab2src");
	CRecordset recset(&db);
	recset.Open(CRecordset::forwardOnly, L"SELECT * FROM primitives", CRecordset::readOnly);

	while (!recset.IsEOF())
	{
		// Copy each column into a variable
		recset.GetFieldValue(L"type", type);
		recset.GetFieldValue(L"p1", p1);
		recset.GetFieldValue(L"p2", p2);
		recset.GetFieldValue(L"p3", p3);
		recset.GetFieldValue(L"p4", p4);

		if (type == "L")
		{
			gl.primitives.push_back(new Line());
		}
		else if (type == "C")
		{
			gl.primitives.push_back(new Circle());
		}
		else if (type == "R")
		{
			gl.primitives.push_back(new Rect());
		}

		int x = gl.primitives.size() - 1;
		gl.primitives[x]->parameters.push_back(_wtof(p1));
		gl.primitives[x]->parameters.push_back(_wtof(p2));
		gl.primitives[x]->parameters.push_back(_wtof(p3));
		gl.primitives[x]->parameters.push_back(_wtof(p4));

		// goto next record
		recset.MoveNext();
	}

	db.Close();

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CLab2ServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CLab2ServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CLab2ServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLab2ServerDlg::OnOpenDrawClick()
{
	
}


void CLab2ServerDlg::OnStartClicked()
{
	m_pListenSocket.Listen();

	char *str = "Lab1";
	int argc = 1;
	char **argv = new char*[argc];
	*argv = str;

	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Lab2 server");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutIdleFunc(render);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);

	glutMainLoop();
}


void CLab2ServerDlg::OnPointClicked()
{
	gl.currDrawing = 0;
}


void CLab2ServerDlg::OnLineClicked()
{
	gl.currDrawing = DRAW_LINE;
}


void CLab2ServerDlg::OnCircleClicked()
{
	gl.currDrawing = DRAW_CIRCLE;
}


void CLab2ServerDlg::OnRectangleClicked()
{
	gl.currDrawing = DRAW_RECT;
}

void CLab2ServerDlg::OnAccept(int ind)
{
	if (!ind)
	{
		m_pListenSocket.Accept(m_pConnectSocket);
		gl.SetSocket(&m_pConnectSocket, ind);
		gl.Sync(ind);
	}
	else
	{
		m_pListenSocket.Accept(m_pConnectSocket2);
		gl.SetSocket(&m_pConnectSocket2, ind);
		gl.Sync(ind);
	}
}

void CLab2ServerDlg::OnReceive()
{
	char *pBuf = new char[1025];
	//Записываем полученные данные в pBuf
	//Записываем в n количество полученных байтов
	int n = m_pConnectSocket.Receive(pBuf, 1024);
	//Отсекаем лишние символы
	pBuf[n] = NULL;
	//Записываем данные в переменную, связанную с edit'ом
	m_sData = pBuf;
	UpdateData(FALSE);
}

void CLab2ServerDlg::OnListenClicked()
{
	
}
