
// Lab2ServerDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Lab2_server.h"
#include "Lab2ServerDlg.h"
#include "afxdialogex.h"
#include "glutMFC.h"

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
	, portIndex(0)
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
	ON_BN_CLICKED(IDC_CONNECT, &CLab2ServerDlg::OnConnectClicked)
	ON_BN_CLICKED(IDC_SEND, &CLab2ServerDlg::OnSendClicked)
	ON_BN_CLICKED(IDCANCEL, &CLab2ServerDlg::OnBnClickedCancel)
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
	m_pConnectSocket.SetParentDlg(this);
	m_pConnectSocket.Create();

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
	char *str = "Lab1";
	int argc = 1;
	char **argv = new char*[argc];
	*argv = str;

	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Lab2 Client");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutIdleFunc(render);

	glutMainLoop();
}


void CLab2ServerDlg::OnPointClicked()
{
	gl.currDrawing = DRAW_POINT;
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


void CLab2ServerDlg::OnConnectClicked()
{
	m_pConnectSocket.Connect(L"127.0.0.1", 2000);
}


void CLab2ServerDlg::OnSendClicked()
{
	UpdateData(TRUE);
	m_pConnectSocket.Send(m_sData, m_sData.GetLength());
}

void CLab2ServerDlg::OnReceive()
{
	char *pBuf = new char[1025];
	//Записываем полученные данные в pBuf
	//Записываем в n количество полученных байтов
	int n = m_pConnectSocket.Receive(pBuf, 1024);
	//Отсекаем лишние символы
	pBuf[n] = NULL;
	
	string data(pBuf);
	string p1, p2, p3, p4, s1, s2;
	int sep1, sep2, sep3;
	switch (data[0])
	{
	case 'P':
		data = data.substr(2, data.size() - 2);
		sep1 = data.find('~');
		p1 = data.substr(0, sep1);
		p2 = data.substr(sep1 + 1, data.size() - sep1 - 1);
		gl.primitives.push_back(new Point());
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p1));
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p2));
		break;
	case 'L':
		data = data.substr(2, data.size() - 2);
		sep1 = data.find('~');
		p1 = data.substr(0, sep1);
		s1 = data.substr(sep1 + 1, data.size() - sep1 - 1);
		sep2 = s1.find('~');
		p2 = s1.substr(0, sep2);
		s2 = s1.substr(sep2 + 1, s1.size() - sep2 - 1);
		sep3 = s2.find('~');
		p3 = s2.substr(0, sep3);
		p4 = s2.substr(sep3 + 1, s2.size() - sep3 - 1);
		gl.primitives.push_back(new Line());
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p1));
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p2));
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p3));
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p4));
		break;
	case 'C':
		data = data.substr(2, data.size() - 2);
		sep1 = data.find('~');
		p1 = data.substr(0, sep1);
		s1 = data.substr(sep1 + 1, data.size() - sep1 - 1);
		sep2 = s1.find('~');
		p2 = s1.substr(0, sep2);
		p3 = s1.substr(sep2 + 1, s1.size() - sep2 - 1);
		gl.primitives.push_back(new Circle());
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p1));
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p2));
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p3));
		break;
	case 'R':
		data = data.substr(2, data.size() - 2);
		sep1 = data.find('~');
		p1 = data.substr(0, sep1);
		s1 = data.substr(sep1 + 1, data.size() - sep1 - 1);
		sep2 = s1.find('~');
		p2 = s1.substr(0, sep2);
		s2 = s1.substr(sep2 + 1, s1.size() - sep2 - 1);
		sep3 = s2.find('~');
		p3 = s2.substr(0, sep3);
		p4 = s2.substr(sep3 + 1, s2.size() - sep3 - 1);
		gl.primitives.push_back(new Rect());
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p1));
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p2));
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p3));
		gl.primitives[gl.primitives.size() - 1]->parameters.push_back(stoi(p4));
		break;
	}

	m_sData = pBuf;
	UpdateData(FALSE);
}

void CLab2ServerDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}
