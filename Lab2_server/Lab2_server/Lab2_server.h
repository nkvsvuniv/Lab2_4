
// Lab2_server.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CLab2S:
// О реализации данного класса см. Lab2_server.cpp
//

class CLab2S : public CWinApp
{
public:
	CLab2S();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CLab2S theApp;