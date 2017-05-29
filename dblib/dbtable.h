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

class DBTableSet{
private: string DBName;
public: map<string, DBtable> dbset;
		map<string,DBtable>::iterator it;

		void readSet()
		{
			ifstream fin("DBTables.txt");
			string tableName;

			if(fin.is_open()==0)
			{
				cout<<"������ � �������� �����"<<endl;
				system("pause");
			}

			while(getline(fin,tableName)){
				DBtable t;
				t.readTable(t,tableName);
				dbset.insert(make_pair(tableName, t));	
			}


		}
		void printSet()
		{
			for(it = dbset.begin(); it!=dbset.end(); it++)
			{
				cout<<endl<<"��� �������: "<<(it->first);
				(it->second).printTable(it->second);
			}
		}
		void addToSet (string DBName)
		{
			DBtable table;
			string filename;
			cout<<"������� ��� �����: ";
			cin>>filename;
			table.readTable(table,filename);
			cout<<"������� �������"<<endl;
			dbset.insert(make_pair(DBName,table));
			//set.db[DBName]=table;
			cout<<"������� �������� � ����"<<endl;
		}

		void DBWrite(string DBName){};
		DBTableSet (){};
		//DBTableSet (string DBNum):DBName(DBNum){};
		DBtable& operator[](string tabName){return dbset[tabName];}

};

//DBTableSet bd(bdName)

//vector <Row> selfRows(string colName,void* val) //search in colname column string equals val
//{
//	vector<Row>row;
//	...
//	return row;
//}