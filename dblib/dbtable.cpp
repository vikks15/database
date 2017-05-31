#include "dbtable.h"
#include "dbdate.h"
int GetTypeCode(string colType)
{
	string types[4] = {"Int", "Double","String","Date"};
	if (colType==types[0]) return 1;
	else if (colType==types[1]) return 2;
	else if (colType==types[2]) return 3;
	else if (colType==types[3]) return 4;
}
void* getValue(string colType, string value)
{
	void* val = NULL;
	switch(GetTypeCode(colType))
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
			DBDate *dat;
			if(value=="-") dat = NULL;
			else dat = new DBDate(value);
			val=dat;
			break;
		}
	default: break;
	}
	return val;
}
void DBtable::readTable(string filename)
{
	ifstream fin(filename); 
	if(fin.is_open()==0)
	{
		cout<<"������ � �������� �����"<<endl;
		system("pause");
	}

	char buff[200];
	char* token = " ", *nexttoken = buff;
	vector<string>tab1Head;
	fin.getline(buff, 200);
	while(token=strtok_s(nexttoken,"|",&nexttoken)) tab1Head.push_back(token);//���������� �����
	for(int i = 0; i<tab1Head.size(); i+=2) (*this).tableHeaders[tab1Head[i]]=tab1Head[i+1];//������ ����� � ��������� dbtable
	
	while(fin.getline(buff,200)) //������ �����
	{
		nexttoken = buff;
		map<string,void*> curRow;
		int i = 0;
		while(token=strtok_s(nexttoken,"|", &nexttoken))
		{
			curRow[tab1Head[i]]=getValue(tab1Head[i+1],token);
			i+=2;
		}
		(*this).data.push_back(curRow);
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
	else if (type == "Date")
	{ 
		if(value==NULL) cout<<setw(10)<<"-";
		else cout<<setw(7)<<*(DBDate*)value; 
	}
}
void DBtable::printTable()
{
	int width = 0;
	int size = (*this).data.size();
	cout<<(*this).TableName<<endl;

	it_header it1 = (*this).tableHeaders.begin(); //�������� ����� ���� ��� | � �����
	for(int i = 0; i<(*this).tableHeaders.size()-1;i++) it1++;

	for(it_header i = (*this).tableHeaders.begin(); i != (*this).tableHeaders.end(); i++)//������ ����� 
	{
		cout<<i->first<<" "<<i->second; 
		if((i->second=="String" && i!=it1)) cout<<setw(7)<<"|";
		else if(i!=it1)cout<<"|";
	}
	cout<<endl;
	for(int i = 0; i < size; i++)
	{
		for(auto j = (*this).tableHeaders.begin(); j!= (*this).tableHeaders.end(); j++) 
		{
			width = (j->first).length() + (j->second).length(); //������ ��������
			printvalue((*this).data[i][j->first],j->second, width);
			if(j!=it1)cout<<"|";
		}
		cout<<endl;
	}
}
void DBtable::record(string fname)
{
	string type = " ", value = " ";
	int size = (*this).data.size(), width = 0;
	ofstream fout(fname);

	it_header it1 = (*this).tableHeaders.begin(); //�������� ����� ���� ��� | � �����
	for(int i = 0; i<(*this).tableHeaders.size()-1;i++) it1++;

	for(it_header i = (*this).tableHeaders.begin(); i != (*this).tableHeaders.end(); i++)
	{
		fout<<i->first<<"|"<<i->second; //������ �����
		if(i!=it1)fout<<"|";
	}
	fout<<endl;
	for(int i = 0; i < size; i++)
	{
		for(auto j = (*this).tableHeaders.begin(); j!= (*this).tableHeaders.end(); j++) 
		{
			type = j->second;
			width = (j->first).length() + (j->second).length(); //������ ��������
			int otv = 0;
			void* v = NULL;
			if(type == "Int") fout<<*(int*)(*this).data[i][j->first];
			else if (type == "Double") fout<<*(double*)(*this).data[i][j->first];
			else if (type == "String") fout<<(char*)(*this).data[i][j->first]; 
			if(j!=it1)fout<<"|";
		}
		fout<<endl;
	}
	fout.close();
};
vector <Row> DBtable::selfRows(string colName, void* obj) //���������� ������ �� �����, � �. ���� obj
{
	void* value = NULL;
	vector <Row> res;
	string type = "";
	for(it_header i = (*this).tableHeaders.begin(); i != (*this).tableHeaders.end(); i++)
	{
		if(i -> first==colName) type = i->second;
	}
	for(int i = 0; i!=(*this).data.size(); i++)
	{
		value = (*this).data[i][colName];
		if(type == "Int" && *(int*)value==*(int*)obj) res.push_back((*this).data[i]);
		else if (type == "String")
		{
			string a = (char*)value;
			string b = (char*)obj;
			if(a==b) res.push_back((*this).data[i]);
		} 
	}
	return res;
}