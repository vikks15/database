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

int menu();

int GetTypeCode(string colName);
void* getValue(string colName, string value);

class DBtable{
private:
	string TableName;

public:
	map<string,string> tableHeaders; //table header
	vector<Row> data; //table rows
	DBtable(){} //конструктор по умолчанию
	~DBtable(){} //деструктор по умолчанию
	void readTable(string filename);
	void printvalue(void *value, string type, int width);
	void printTable();
	void writeTableBin(DBtable tab1);
	void record(string fname);
	vector <Row> selfRows(string colName, void* obj);


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
				cout<<"Ошибка в откритии файла"<<endl;
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
				cout<<endl<<"Имя таблицы: "<<(it->first);
				(it->second).printTable();
			}
		}
		void addToSet (string DBName)
		{
			DBtable table;
			table.readTable(DBName);
			dbset.insert(make_pair(DBName,table));
			//set.db[DBName]=table;
	
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