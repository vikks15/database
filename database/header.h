#pragma once
#include "dbtable.h"
#include "dbdate.h"
int menu1()
{
	int number = 0;
	cout<<"1 - ����� � ������ �������"<<endl;
	cout<<"2 - ����� �� ���������"<<endl;
	cin>>number;
	cin.clear();
	cin.ignore(256,'\n');
	return number;
}
int menu2()
{
	int number = 0;
	cout<<"1 - ����� �����"<<endl;
	cout<<"2 - ���������� � ������"<<endl;
	cout<<"3 - ����� �� ������� ��������"<<endl;
	cin>>number;
	cin.clear();
	cin.ignore(256,'\n');
	return number;
}