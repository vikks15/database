#include "dbtable.h"

int menu()
{
	int number = 0;

	cout<<"1 - чтение из файла"<<endl;
	cout<<"2 - запись в файл"<<endl;
	cout<<"3 - вывод на экран"<<endl;
	cout<<"4 - выбрать библиотеку"<<endl;
	cout<<"5 - выйти из текущей библиотеки"<<endl;
	cout<<"6 - выход"<<endl;
	cin>>number;

	cin.clear();
	cin.ignore(256,'\n');
	return number;
}

int DBtable::GetTypeCode(string colName)
{
	string types[3] = {"Int", "Double","String"};

	if (colName==types[0]) return 1;
	else if (colName==types[1]) return 2;
	else if (colName==types[2]) return 3;
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
			strcpy(buff,value.c_str());
			val = buff;

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
	else if (type == "String") cout<<setw(width+1)<<(char*)value; 
}

void DBtable::printTable(DBtable tab1)
{
	int width = 0;
	int size = tab1.data.size();
	cout<<tab1.TableName<<endl;

	it_header it1 = tab1.tableHeaders.begin(); //итератор чтобы было без | в конце
	for(int i = 0; i<tab1.tableHeaders.size()-1;i++) it1++;

	for(it_header i = tab1.tableHeaders.begin(); i != tab1.tableHeaders.end(); i++)
	{
		cout<<i->first<<" "<<i->second; //печать шапки 
		if(i!=it1)cout<<"|";
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