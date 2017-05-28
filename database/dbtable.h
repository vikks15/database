#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
using namespace std;

typedef pair<string,string> myPair;
typedef map<string, void*>  Row;
typedef map<string,string>::iterator it_header; // ��� ��������� �� ���������

int menu();

class DBtable{
private:
	string TableName;

public:
	map<string,string> tableHeaders; //����� �������
	vector<Row> data; //������ �������
	DBtable(){} //����������� �� ���������
	~DBtable(){} //���������� �� ���������
	int GetTypeCode(string colName);
	void* getValue(string colName, string value);
	void readTable(DBtable &tab1, string filename);
	void printvalue(void *value, string type, int width);
	void printTable(DBtable tab1);
	void writeTableBin(DBtable tab1);
	void record(DBtable tab1,string fname);

};

//DBTableSet bd(bdName)

//vector <Row> selfRows(string colName,void* val) //search in colname column string equals val
//{
//	vector<Row>row;
//	...
//	return row;
//}