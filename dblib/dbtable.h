#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
using namespace std;
typedef pair<string,string> myPair;
typedef map<string, void*> Row;//������ �������
typedef map<string,string>::iterator it_header; //��� ��������� �� ���������
int GetTypeCode(string colName);
void* getValue(string colName, string value);

class DBtable{
private:
	string TableName;
public:
	map<string,string> tableHeaders; //����� �������
	vector<Row> data; //������ �� ����� �������
	DBtable(){} //����������� �� ���������
	~DBtable(){} //���������� �� ���������
	void readTable(string filename);
	void printvalue(void *value, string type, int width);
	void printTable();
	void record(string fname);
	vector <Row> selfRows(string colName, void* obj);
};

class DBTableSet{
private: string DBName;
public: map<string, DBtable> dbset;
		map<string,DBtable>::iterator it;
		DBTableSet (){};
		~DBTableSet (){};
		void readSet(const string& filename)
		{
			ifstream fin(filename);
			string tableName;
			if(fin.is_open()==0)
			{
				cout<<"������ � �������� �����"<<endl;
				system("pause");
			}
			while(getline(fin,tableName)){
				DBtable t;
				t.readTable(tableName);
				dbset.insert(make_pair(tableName, t));	
			}
		}
		void printSet()
		{
			for(it = dbset.begin(); it!=dbset.end(); it++)
			{
				cout<<endl<<"��� �������: "<<(it->first);
				(it->second).printTable();
			}
		}
		void addToSet (string DBName)//�������� ������� � Set
		{
			DBtable table;
			table.readTable(DBName);
			dbset.insert(make_pair(DBName,table));
		}
		void DBWrite(string DBName){};
		DBtable& operator[](string tabName){ return dbset[tabName]; } //���������� ���������[]
};