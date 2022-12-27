#pragma once

#include <afxwin.h>
#include <vector>
#include<algorithm>
using namespace std;


class Drawer
{
	// ������������� ������� ���������.
	CRect frame;
	// ��������� �� ������ ����, ������� ���������.
	CWnd * wnd;
	// �������� ���������, ����������� � ������� ���������.
	CDC * dc;
	// �������� ���������, ����������� � ������.
	CDC memDC;
	// ������ ��� ��������� ��������� memDC.
	CBitmap bmp;
	// ���� ��� ������������ ��������� ������������� ������.
	bool init;

protected:
	double convert_range(double data, double outmax, double outmin, double inmax, double inmin);
	vector<double> convert_range(vector <double>& data, double outmax, double outmin, double inmax, double inmin);


public:
	// ������������������� ������ ������ �� ������ HWND.
	void Create(HWND hWnd);
	
	void DrawGraph(vector<double> data, double xmin, double xmax);


	void Clear();
	void Redraw();
};
