#include "dbtable.h"

int main()
{
	system("chcp 1251 > nul");
	string way = "", fname = " ", libname = "", fnameout="";
	DBtable tab;

	while(true)
	{
		switch(menu())
		{
		case 1:
			{
				cout<<"������� ��� �����: ";
				cin>>fname;
				way+=fname;
				tab.readTable(tab,way);
				cout<<"������� ������� �������"<<endl;
				break;
			}
		case 2:
			{
				cout<<"������� ���� � �����: ";
				cin>>fnameout;
				tab.record(tab,fnameout);
				break;
			}
		case 3:
			{
				tab.printTable(tab);
				cout<<endl;
				break;
			}
		case 4: 
			{
				cout<<"������� ��� ����������: ";
				cin>>libname;
				way = libname+"\\";
				break;
			}
		case 5:
			{
				way ="..\\";
				break;
			}
		case 6:
			{
				return 0;
			}
		default: 
			{
				cout<<"������� ����� �� 1 �� 6";
				break;
			}


		}
		system("pause");
		system("cls");
		

	}


	/*

	DBtable tab2;
	tab.readTable(tab2,"out.txt");
	tab.printTable(tab2);*/

	
	return 0;
	
	
}