#include"pch.h"
#include"DES.h"


DES::DES() 
{
	S = CreateS();
}


vector<bool> DES::StringToBool(string& data)
{
	map<int, int> bit;
	bit[0] = 1;
	bit[1] = 2;
	bit[2] = 4;
	bit[3] = 8;
	bit[4] = 16;
	bit[5] = 32;
	bit[6] = 64;
	bit[7] = 128;


	vector<bool>res;
	for (int i = 0; i < data.size(); i++)
	{
		for (int g = 0; g < 8; g++)
		{
			res.push_back((data[i] & bit[g]) >> g);
		}
	}
	return res;
}
string DES::BoolToString(vector<bool>& data)
{
	string res = "";


	int count = 0;
	unsigned char c = 0;
	for (int i = 0; i < data.size(); i++)
	{
		c |= data[i] << count;
		count++;

		if(count==8)
		{
			count = 0;
			res += c;
			c = 0;
		}
	}


	return res;
}

vector<bool> DES::IntToBool(int data)
{
	map<int, int> bit;
	bit[0] = 1;
	bit[1] = 2;
	bit[2] = 4;
	bit[3] = 8;
	bit[4] = 16;
	bit[5] = 32;
	bit[6] = 64;
	bit[7] = 128;

	vector<bool> res;
	for (int g = 0; g < 4; g++)
	{
		res.push_back((data & bit[g]) >> g);
	}
	return res;
}
int DES::BoolToInt(vector<bool>& data)
{
	int res = 0;
	for (int i = 0; i < data.size(); i++)
	{
		res |= data[i] << i;
	}
	return res;
}


vector<bool>DES::IP(vector<bool>& data)
{
	vector<bool>res;
	conj(res, getIPdata(data, 57));
	conj(res, getIPdata(data, 59));
	conj(res, getIPdata(data, 61));
	conj(res, getIPdata(data, 63));
	conj(res, getIPdata(data, 56));
	conj(res, getIPdata(data, 58));
	conj(res, getIPdata(data, 60));
	conj(res, getIPdata(data, 62));
	return res;
}
vector<bool>DES::_IP(vector<bool>& data)
{
	vector<bool>res = vector<bool>(64, 0);

	write_IPdata(res, get_IPdata(data, 39), 0);
	write_IPdata(res, get_IPdata(data, 7), 1);
	write_IPdata(res, get_IPdata(data, 47), 2);
	write_IPdata(res, get_IPdata(data, 15), 3);
	write_IPdata(res, get_IPdata(data, 55), 4);
	write_IPdata(res, get_IPdata(data, 23), 5);
	write_IPdata(res, get_IPdata(data, 63), 6);
	write_IPdata(res, get_IPdata(data, 31), 7);

	return res;
}
vector<bool>DES::getIPdata(vector<bool>& data, int id)
{
	vector<bool> res;
	while (id > -1)
	{
		res.push_back(data[id]);
		id -= 8;
	}
	return res;
}
vector<bool>DES::get_IPdata(vector<bool>& data, int id)
{
	vector<bool>res;
	for (int i = 0; i < 8; i++)
	{
		res.push_back(data[id - i]);
	}
	return res;
}
void DES::write_IPdata(vector<bool>& res, vector<bool>& data, int id)
{
	for (auto& item : data)
	{
		res[id] = item;
		id += 8;
	}
}


void DES::conj(vector<bool>& left, vector<bool>& right)
{
	for (auto& item : right)left.push_back(item);
}
vector<bool> DES::getSubVector(vector<bool>& data, int pos, int amount)
{
	if (data.size() < pos + amount)
	{
		MessageBoxW(mainWnd, L"data out of range", L"getSubVector", MB_OK);
		PostQuitMessage(0);
	}

	vector<bool> res;
	for (int i = pos; i < pos + amount; i++)
	{
		res.push_back(data[i]);
	}
	return res;
}
vector<bool> DES::SummBoolVectors(vector<bool>& left, vector<bool>& right)
{
	if(left.size()!=right.size())
	{
		MessageBoxW(mainWnd, L"разная длина векторов", L"SummBoolVectors", MB_OK);
		PostQuitMessage(0);
	}


	vector<bool> res;
	for (int i = 0; i < left.size(); i++)
	{
		if (left[i] == right[i])res.push_back(0);
		else res.push_back(1);
	}
	return res;
}


vector<bool> DES::getL(vector<bool>& data)
{
	vector<bool> res;
	for (int i = 0; i < 32; i++)res.push_back(data[i]);
	return res;
}
vector<bool> DES::getR(vector<bool>& data)
{
	vector<bool> res;
	for (int i = 32; i < 64; i++)res.push_back(data[i]);
	return res;
}


vector<bool>DES::E(vector<bool>& data)
{
	vector<bool>res;
	vector<int> id = { 32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
					   16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };
	for (auto& item : id)res.push_back(data[item - 1]);
	return res;
}
vector<vector<vector<int>>> DES::CreateS()
{
	vector<vector<vector<int>>> res;
	vector<vector<int>> S;
	//[0][0]
	vector<int>temp = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 };
	S.push_back(temp);
	//[0][1]
	temp = { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 };
	S.push_back(temp);
	//[0][2]
	temp = { 4, 1, 4, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 };
	S.push_back(temp);
	//[0][3]
	temp = { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 };
	S.push_back(temp);
	res.push_back(S);
	S.clear();

	//[1][0]
	temp = { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 };
	S.push_back(temp);
	//[1][1]
	temp = { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 };
	S.push_back(temp);
	//[1][2]
	temp = { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 };
	S.push_back(temp);
	//[1][3]
	temp = { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 };
	S.push_back(temp);
	res.push_back(S);
	S.clear();

	//[2][0]
	temp = { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 };
	S.push_back(temp);
	//[2][1]
	temp = { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 };
	S.push_back(temp);
	//[2][2]
	temp = { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 };
	S.push_back(temp);
	//[2][3]
	temp = { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 };
	S.push_back(temp);
	res.push_back(S);
	S.clear();

	//[3][0]
	temp = { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 };
	S.push_back(temp);
	//[3][1]
	temp = { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 };
	S.push_back(temp);
	//[3][2]
	temp = { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 };
	S.push_back(temp);
	//[3][3]
	temp = { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 };
	S.push_back(temp);
	res.push_back(S);
	S.clear();

	//[4][0]
	temp = { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 };
	S.push_back(temp);
	//[4][1]
	temp = { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 };
	S.push_back(temp);
	//[4][2]
	temp = { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 };
	S.push_back(temp);
	//[4][3]
	temp = { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 };
	S.push_back(temp);
	res.push_back(S);
	S.clear();

	//[5][0]
	temp = { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 };
	S.push_back(temp);
	//[5][1]
	temp = { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 };
	S.push_back(temp);
	//[5][2]
	temp = { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 1, 6 };
	S.push_back(temp);
	//[5][3]
	temp = { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 };
	S.push_back(temp);
	res.push_back(S);
	S.clear();

	//[6][0]
	temp = { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 };
	S.push_back(temp);
	//[6][1]
	temp = { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 };
	S.push_back(temp);
	//[6][2]
	temp = { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 };
	S.push_back(temp);
	//[6][3]
	temp = { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 };
	S.push_back(temp);
	res.push_back(S);
	S.clear();

	//[7][0]
	temp = { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 };
	S.push_back(temp);
	//[7][1]
	temp = { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 };
	S.push_back(temp);
	//[7][2]
	temp = { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 };
	S.push_back(temp);
	//[7][3]
	temp = { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 };
	S.push_back(temp);
	res.push_back(S);
	S.clear();


	return res;
}
vector<bool> DES::TransformB(vector<bool>& data)
{
	vector<bool>res;
	//Bj переходит в Bj' при помощи Sj    111010
	//берем первый и последний разряд Bj
	//получаем, например, 10 - 3 в десятичной системе
	// берем оставшиеся разряды и получаем  1101 - 13 в десятичной
	// Sj[3][13] = чему-то и переписываем это в двоичный вид
	for (int i = 0; i < 8; i++)
	{
		vector<bool> vec = getSubVector(data, i * 6, 6);
		vector<bool>temp;
		temp.push_back(vec[5]);
		temp.push_back(vec[0]);
		int str = BoolToInt(temp);

		temp.clear();
		
		for (int g = 1; g < 5; g++)temp.push_back(vec[g]);
		int row = BoolToInt(temp);
		conj(res, IntToBool(S[i][str][row]));
	}


	return res;
}
vector<bool> DES::P(vector<bool>& data)
{
	vector<bool>res;
	vector<int> id = { 16, 7, 20, 21,29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25 };
	for (auto& item : id)res.push_back(data[item - 1]);
	return res;
}


vector<bool> DES::CreateKey()
{
	vector<bool>res;
	srand(time(NULL));


	for (int i = 0; i < 64; i++)
	{
		float k = float(rand()) / RAND_MAX;
		if (k < 0.5)res.push_back(0);
		else res.push_back(1);
	}


	created_key = res;
	return res;
}
vector<bool> DES::CD(vector<bool>& data)
{
	vector<bool>res;
	vector<int> id = { 57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15,
					   7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4 };
	for (auto& item : id)res.push_back(data[item - 1]);
	return res;
}
vector<bool> DES::shiftCD(vector<bool>& data, int iteration)
{
	vector<int>shift = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
	vector<bool>res;
	for (int i = 0; i < shift[iteration]; i++)res.push_back(data[28 - shift[iteration] + i]);
	for (int i = 0; i < 28 - shift[iteration]; i++)res.push_back(data[i]);
	for (int i = 0; i < shift[iteration]; i++)res.push_back(data[56 - shift[iteration] + i]);
	for (int i = 28; i < 56 - shift[iteration]; i++)res.push_back(data[i]);

	return res;
}
vector<bool> DES::Ki(vector<bool>& data)
{
	vector<bool>res;
	vector<int>id = { 14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
					  44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32 };
	for (auto& item : id)res.push_back(data[item - 1]);
	return res;
}
vector<vector<bool>> DES::CreateKi(vector<bool> data)
{
	vector<vector<bool>>res;

	
	for (int i = 0; i < 16; i++)
	{
		data = shiftCD(data, i);
		res.push_back(Ki(data));
	}
	return res;
}

string DES::Code(vector<bool> bdata, string key)
{
	bdata = IP(bdata);
	vector<bool> l = getL(bdata);
	vector<bool> r = getR(bdata);

	vector<bool>bkey;
	if (key.size() != 0)bkey = StringToBool(key);
	else bkey = CreateKey();
	vector<bool>cd = CD(bkey);

	for (int i = 0; i < 16; i++)
	{
		cd = shiftCD(cd, i);
		bkey = Ki(cd);

		vector<bool> temp = E(r);
		temp = SummBoolVectors(temp, bkey);
		temp = TransformB(temp);
		temp = P(temp);//fi
		temp = SummBoolVectors(l, temp);//r1
		l = r;//l1
		r = temp;
	}

	vector<bool>res;
	conj(res, l);
	conj(res, r);
	res = _IP(res);

	return BoolToString(res);
}
string DES::Code(string data, string key)
{
	vector<bool> bdata = StringToBool(data);
	bdata = IP(bdata);
	vector<bool> l = getL(bdata);
	vector<bool> r = getR(bdata);

	vector<bool>bkey;
	if (key.size() != 0)bkey = StringToBool(key);
	else bkey = CreateKey();
	vector<bool>cd = CD(bkey);

	for (int i = 0; i < 16; i++)
	{
		cd = shiftCD(cd, i);
		bkey = Ki(cd);
		
		vector<bool> temp = E(r);
		temp = SummBoolVectors(temp, bkey);
		temp = TransformB(temp);
		temp = P(temp);//fi
		temp = SummBoolVectors(l, temp);//r1
		l = r;//l1
		r = temp;
	}

	vector<bool>res;
	conj(res, l);
	conj(res, r);
	res = _IP(res);

	return BoolToString(res);
}
string DES::Decode(string data, string key)
{
	vector<bool> bdata = StringToBool(data);
	bdata = IP(bdata);
	vector<bool> l = getL(bdata);
	vector<bool> r = getR(bdata);


	vector<bool>bkey = StringToBool(key);
	vector<bool>cd = CD(bkey);
	vector<vector<bool>>bkeys = CreateKi(cd);


	for (int i = 15; i > -1; i--)
	{
		vector<bool> temp = E(l);
		temp = SummBoolVectors(temp, bkeys[i]);
		temp = TransformB(temp);
		temp = P(temp);//fi
		temp = SummBoolVectors(r, temp);//l-1
		r = l;//r-1
		l = temp;
	}


	vector<bool>res;
	conj(res, l);
	conj(res, r);
	res = _IP(res);

	return BoolToString(res);
}


string DES::getKey()
{
	return BoolToString(created_key);
}


void DES::test()
{
	string str = "12345678";
	auto a = Code(str,str);
	auto b = Decode(a, str);
	while (1);
}


string DES::CreateAndGetKey()
{
	return BoolToString(CreateKey());
}