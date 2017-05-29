#include "dbtable.h"
#include "dbdate.h"

int DBtable::GetTypeCode(string colName)
{
	string types[4] = {"Int", "Double","String","Date"};

	if (colName==types[0]) return 1;
	else if (colName==types[1]) return 2;
	else if (colName==types[2]) return 3;
	else if (colName==types[3]) return 4;
}

void* DBtable::getValue(string colName, string value)
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
			char *buff = new char[value.length()];
			strcpy_s(buff,value.length()+1,value.c_str());
			val = buff;
			break;
		}
	case 4:
		{
			DBDate *dat = new DBDate(value);
			val=dat;
			break;
		}
	default: break;
	}
	return val;
}

void DBtable::readTable(DBtable &tab1, string filename)
{
	ifstream fin(filename); 

	if(fin.is_open()==0)
	{
		cout<<"Ошибка в откритии файла"<<endl;
		system("pause");
	}

	char buff[200];
	char* token = " ", *nexttoken = buff;
	vector<string>tab1Head;

	fin.getline(buff, 200);
	while(token=strtok_s(nexttoken,"|",&nexttoken))
	{

		tab1Head.push_back(token);//считывание шапки

	}

	for(int i = 0; i<tab1Head.size(); i+=2) tab1.tableHeaders[tab1Head[i]]=tab1Head[i+1];//запись шапки в структуры dbtable
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

void DBtable::printvalue(void *value, string type, int width)
{
	int otv = 0;
	void* v = NULL;
	if(type == "Int") cout<<setw(width+1)<<*(int*)value;
	else if (type == "Double") cout<<setw(width+1)<<*(double*)value;
	else if (type == "String") cout<<setw(width+7)<<(char*)value; 
	else if (type == "Date") cout<<setw(8)<<*(DBDate*)value; 
}

void DBtable::printTable(DBtable tab1)
{
	int width = 0;
	int size = tab1.data.size();
	cout<<tab1.TableName<<endl;

	it_header it1 = tab1.tableHeaders.begin(); //итератор чтобы было без | в конце
	for(int i = 0; i<tab1.tableHeaders.size()-1;i++) it1++;

	for(it_header i = tab1.tableHeaders.begin(); i != tab1.tableHeaders.end(); i++)//печать шапки 
	{
		 cout<<i->first<<" "<<i->second; 

		 if((i->second=="String" && i!=it1)) cout<<setw(7)<<"|";
		 else if(i!=it1)cout<<"|";
	}
	cout<<endl;

	for(int i = 0; i < size; i++)
	{
		for(auto j = tab1.tableHeaders.begin(); j!= tab1.tableHeaders.end(); j++) 
		{

			width = (j->first).length() + (j->second).length(); //ширина столбцов
			printvalue(tab1.data[i][j->first],j->second, width);
			if(j!=it1)cout<<"|";
		}
		cout<<endl;
	}
}

void DBtable::record(DBtable tab1, string fname)
{
	string type = " ", value = " ";
	int size = tab1.data.size(), width = 0;
	ofstream fout(fname);

	it_header it1 = tab1.tableHeaders.begin(); //итератор чтобы было без | в конце
	for(int i = 0; i<tab1.tableHeaders.size()-1;i++) it1++;

	for(it_header i = tab1.tableHeaders.begin(); i != tab1.tableHeaders.end(); i++)
	{
		fout<<i->first<<"|"<<i->second; //запись шапки
		if(i!=it1)fout<<"|";
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
			if(type == "Int") fout<<*(int*)tab1.data[i][j->first];
			else if (type == "Double") fout<<*(double*)tab1.data[i][j->first];
			else if (type == "String") fout<<(char*)tab1.data[i][j->first]; 

			if(j!=it1)fout<<"|";
		}
		fout<<endl;
	}

	fout.close();

};