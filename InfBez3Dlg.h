
// InfBez3Dlg.h: файл заголовка
//

#pragma once
#include"Rand.h"

// Диалоговое окно CInfBez3Dlg
class CInfBez3Dlg : public CDialogEx
{
// Создание
public:
	CInfBez3Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFBEZ3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString X;
	CString k;
	int len;

	Rand rand;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	HANDLE th;
};


DWORD WINAPI thStart(LPVOID lp);