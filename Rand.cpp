#include"pch.h"
#include"Rand.h"


void Rand::SetCtr(UINT64 data)
{
	ctr = data;
}
void Rand::SetDrwHWND(HWND hWnd)
{
	drw.Create(hWnd);
}
void Rand::Redraw()
{
	drw.Redraw();
}

string Rand::CreateKey()
{
	return des.CreateAndGetKey();
}


vector<bool>Rand::ToBool(UINT64 data)
{
	UINT64 temp = 1;
	vector<bool>res;
	for (int i = 0; i < 64; i++)
	{
		res.push_back((data & temp) >> i);
		temp = temp << 1;
	}
	return res;
}
UINT64 Rand::ToUINT64(vector<bool>& data)
{
	UINT res = 0;
	for (int i = 0; i < data.size(); i++)
	{
		res |= data[i] << i;
	}
	return res;
}


vector<int> Rand::Generate(int len)
{
	vector<int> res;


	string temp = des.Code(ToBool(ctr), des.getKey());
	res.push_back(UINT8(temp[7]));
	temp[7] = temp[7] + 1;


	for (int i = 1; i < len; i++)
	{
		temp = des.Code(temp, des.getKey());
		res.push_back(UINT8(temp[7]));
		temp[7] = temp[7] + 1;
	}

	ofstream of("result.txt");
	for (auto& item : res)of << item << endl;
	of.close();


	return res;
}


float Rand::Analise(vector<int>& data)
{
	int n = 1 + log2(data.size());

	sort(data.begin(), data.end());


	vector<double> val;
	vector<float>Pi;

	int total = 0;
	for (int i = 0; i < n; i++)
	{
		float left = 255 * i / float(n);
		float right = 255 * (i + 1) / float(n);
		
		int indeed = 0;
		while (data[total + indeed] < right)
		{
			indeed++;
			if (total + indeed == data.size())break;
		}
		val.push_back(indeed);
		total+=indeed;


		float temp = (right + 1) / 255;
		temp+=-(left + 1) / 255;
		Pi.push_back(temp);
	}


	float res = 0;
	for (int i = 0; i < Pi.size(); i++)
	{
		float temp = data.size() * Pi[i];
		res += (val[i] - temp) * (val[i] - temp) / temp;
	}


	drw.DrawGraph(val, 0, 255);


	return res;
}
