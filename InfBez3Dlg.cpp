
// InfBez3Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "InfBez3.h"
#include "InfBez3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CInfBez3Dlg



CInfBez3Dlg::CInfBez3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFBEZ3_DIALOG, pParent)
	, X(_T(""))
	, k(_T(""))
	, len(100)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInfBez3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, X);
	DDX_Text(pDX, IDC_EDIT2, k);
	DDX_Text(pDX, IDC_EDIT1, len);
}

BEGIN_MESSAGE_MAP(CInfBez3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CInfBez3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CInfBez3Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CInfBez3Dlg

BOOL CInfBez3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	rand.SetDrwHWND(GetDlgItem(IDC_PICTURE)->GetSafeHwnd());
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CInfBez3Dlg::OnPaint()
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
		rand.Redraw();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CInfBez3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CInfBez3Dlg::OnBnClickedButton1()
{
	TerminateThread(th, 0);
	k = rand.CreateKey().c_str();
	UpdateData(FALSE);
}


void CInfBez3Dlg::OnBnClickedOk()
{
	TerminateThread(th, 0);


	UpdateData();

	rand.SetCtr();
	/*auto r = rand.Generate(len);
	float x = rand.Analise(r);

	X.Format(L"%.3f", x);
	UpdateData(FALSE);*/

	th = CreateThread(NULL, 0, thStart, this, 0, NULL);

}


DWORD WINAPI thStart(LPVOID lp)
{
	CInfBez3Dlg* p = (CInfBez3Dlg*)lp;
	auto r = p->rand.Generate(p->len);
	float x = p->rand.Analise(r);

	p->X.Format(L"%.3f", x);
	//p->UpdateData(FALSE);
	return 0;
}