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
typedef map<string,string>::iterator it_header; // тип итератора по заголовку

class DBtable{
private:
	string TableName;

public:
	map<string,string> tableHeaders; //шапка таблицы
	vector<Row> data; //строки таблицы
	DBtable(){} //конструктор по умолчанию
	~DBtable(){} //деструктор по умолчанию
	int GetTypeCode(string colName);
	void* getValue(string colName, string value);
	void readTable(DBtable &tab1, string filename);
	void printvalue(void *value, string type, int width);
	void printTable(DBtable tab1);
	void writeTableBin(DBtable tab1);
	void record(DBtable tab1);
	void menu();

};