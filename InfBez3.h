
// InfBez3.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CInfBez3App:
// Сведения о реализации этого класса: InfBez3.cpp
//

class CInfBez3App : public CWinApp
{
public:
	CInfBez3App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CInfBez3App theApp;
