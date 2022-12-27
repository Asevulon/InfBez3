#pragma once
#include"DES.h"
#include<fstream>
#include"Drawer.h"


class Rand
{
private:
	DES des;
	UINT64 ctr;

	Drawer drw;
protected:
	vector<bool>ToBool(UINT64 data);
	UINT64 ToUINT64(vector<bool>& data);
public:
	void SetCtr(UINT64 data = 0);
	void SetDrwHWND(HWND hWnd);
	void Redraw();


	string CreateKey();


	vector<int> Generate(int len);


	float Analise(vector<int>& data);
};