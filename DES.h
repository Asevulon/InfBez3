#pragma once
#include<vector>
#include<string>
#include<map>
#include<time.h>
#include<random>
using namespace std;


static HWND mainWnd;


class DES
{
private:
	vector<vector<vector<int>>> S;
	vector<bool> created_key;

protected:
	
	vector<bool> IntToBool(int data);
	int BoolToInt(vector<bool>& data);

	vector<bool> StringToBool(string& data);
	string BoolToString(vector<bool>& data);

	vector<bool>IP(vector<bool>& data);
	vector<bool>_IP(vector<bool>& data);
	vector<bool>getIPdata(vector<bool>& data, int id);
	vector<bool>get_IPdata(vector<bool>& data, int id);
	void write_IPdata(vector<bool>& res, vector<bool>& data, int id);


	void conj(vector<bool>& left, vector<bool>&right);
	vector<bool> getSubVector(vector<bool>& data, int pos, int amount);
	vector<bool> SummBoolVectors(vector<bool>& left, vector<bool>& right);


	vector<bool> getL(vector<bool>& data);
	vector<bool> getR(vector<bool>& data);

	vector<bool>E(vector<bool>& data);
	vector<vector<vector<int>>> CreateS();
	vector<bool>TransformB(vector<bool>& data);
	vector<bool>P(vector<bool>& data);


	vector<bool> CreateKey();
	vector<bool> CD(vector<bool>& data);
	vector<bool> shiftCD(vector<bool>& data, int iteration);
	vector<bool> Ki(vector<bool>& data);
	vector<vector<bool>> CreateKi(vector<bool> data);


public:
	DES();


	string DES::Code(vector<bool> bdata, string key);
	string DES::Code(string data, string key);

	string Decode(string data, string key);


	string getKey();
	string CreateAndGetKey();
	void test();
};