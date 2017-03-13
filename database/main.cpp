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
	map<string,string> tableHeaders; // шапка таблицы
	vector<Row> data; //строки таблицы
	DBtable(){} //конструктор по умолчанию
	~DBtable(){} //деструктор по умолчанию
	int GetTypeCode(string colName)
	{
		string types[3] = {"Int", "Double","String"};

		if (colName==types[0]) return 1;
		else if (colName==types[1]) return 2;
		else if (colName==types[2]) return 3;
	}

	void* getValue(string colName, string value)
	{
		void* val = NULL;
		switch(GetTypeCode(colName))
		{
		case 1:
			{
				int *buff = new int (atoi(value.c_str()));
				val = buff;
				break;
			}
		case 2: 
			{
				double *buff = new double (atof(value.c_str())); 
				val = buff;
				break;
			}
		case 3:
			{
				char *buff = new char();
				strcpy(buff,value.c_str());
				val = buff;

				break;
			}
		default: break;
		}
		return val;
	}

	void readTable(DBtable &tab1, string filename)
	{
		ifstream fin(filename); 

		if(fin.is_open()==0)
		{
			cout<<"Проблема с открытием файла";
			system("pause");
		}

		char buff[200];
		char* token = " ", *nexttoken = buff;
		vector<string>tab1Head;

		fin.getline(buff, 200);
		while(token=strtok_s(nexttoken,"|",&nexttoken))
		{

			tab1Head.push_back(token);// считывание шапки

		}

		for(int i = 0; i<tab1Head.size(); i+=2) tab1.tableHeaders[tab1Head[i]]=tab1Head[i+1];//запись шапки в структуру dbtable

		while(fin.getline(buff,200)) //запись строк
		{
			nexttoken = buff;
			map<string,void*> curRow;
			int i = 0;
			while(token=strtok_s(nexttoken,"|", &nexttoken))
			{
				curRow[tab1Head[i]]=getValue(tab1Head[i+1],token);
				i+=2;
			}

			tab1.data.push_back(curRow);
			//int *c = (int*)tab1.data[0][tab1Head[0]];
			//cout<<"ghf "<<*c; working
		}

		fin.close();

	}

	void printvalue(void *value, string type, int width)
	{
		int otv = 0;
		void* v = NULL;
		if(type == "Int") cout<<setw(width+1)<<*(int*)value<<"|";
		else if (type == "Double") cout<<setw(width+1)<<*(double*)value<<"|";
		else if (type == "String") cout<<setw(width+1)<<(char*)value<<"|"; 
	}


	void printTable(DBtable tab1)
	{
		int width = 0;
		int size = tab1.data.size();
		cout<<tab1.TableName<<endl;

		for(it_header i = tab1.tableHeaders.begin(); i != tab1.tableHeaders.end(); i++)
		{
			cout<<i->first<<" "<<i->second<<"|"; //печать шапки 
		}

		cout<<endl;

		for(int i = 0; i < size; i++)
		{
			for(auto j = tab1.tableHeaders.begin(); j!= tab1.tableHeaders.end(); j++) 
			{

				width = (j->first).length() + (j->second).length(); //ширина столбцов
				printvalue(tab1.data[i][j->first],j->second, width);
			}
			cout<<endl;
		}
	}

	void writeTableBin(DBtable tab1)
	{
		//char *fname = " ";
		int hdrsize = 0;
		ofstream fout("out.bin", ios::binary);

		for(it_header i = tab1.tableHeaders.begin(); i != tab1.tableHeaders.end(); i++)
		{
			hdrsize = (i->first).length();
			//fout.write((char*)&hdrsize,sizeof(string));
			fout.write((i->first).c_str(),sizeof(string));
			hdrsize = (i->second).length();
			//fout.write((char*)&hdrsize,sizeof(string));
			fout.write((i->second).c_str(),sizeof(string));

		}
		fout.close();

	}


	void recordvalue(void *value, string type, int width)
	{
		ofstream fout("out.txt");
		int otv = 0;
		void* v = NULL;
		if(type == "Int") fout<<setw(width+1)<<*(int*)value<<"|";
		else if (type == "Double") fout<<setw(width+1)<<*(double*)value<<"|";
		else if (type == "String") fout<<setw(width+1)<<(char*)value<<"|"; 
	}

	void record(DBtable tab1)
	{
		string type = " ", value = " ";
		int size = tab1.data.size(), width = 0;
		ofstream fout("out.txt");

		for(it_header i = tab1.tableHeaders.begin(); i != tab1.tableHeaders.end(); i++)
		{
			fout<<i->first<<"|"<<i->second<<"|"; //печать шапки 
		}

		fout<<endl;
		for(int i = 0; i < size; i++)
		{
			for(auto j = tab1.tableHeaders.begin(); j!= tab1.tableHeaders.end(); j++) 
			{

				type = j->second;
				width = (j->first).length() + (j->second).length(); //ширина столбцов
				
				int otv = 0;
				void* v = NULL;
				if(type == "Int") fout<<*(int*)tab1.data[i][j->first]<<"|";
				else if (type == "Double") fout<<*(double*)tab1.data[i][j->first]<<"|";
				else if (type == "String") fout<<(char*)tab1.data[i][j->first]<<"|"; 
			}
			fout<<endl;
		}

		fout.close();
	}

};

int main()
{
	system("chcp 1251 > nul");
	DBtable tab;
	tab.readTable(tab,"table.txt");

	tab.printTable(tab);
	tab.record(tab);

	DBtable tab2;
	tab.readTable(tab2,"out.txt");
	tab.printTable(tab2);

	system("pause");
	return 0;
}