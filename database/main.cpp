#include "dbtable.h"
#include "dbdate.h"

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

	return 0;

	

	/*DBtable tab2;
	tab.readTable(tab2,"out.txt");
	tab.printTable(tab2);*/

	
	//system("chcp 1251 > nul");
	//int justint = 0;

	//string d1,d2;	
	//cout<<"������� ����: ";
	//cin>>d1;
	//DBDate dat1(d1);
	//if(!dat1.CorrectDate()) return 0;
	////cout<<"������������ ���� "<<dat1.CorrectDate();

	//cout<<"���� 1: "<<dat1<<endl;

	//cout<<"������� �����: ";
	//cin>>justint;	
	//dat1+=justint;
	//cout<<"���������� ����1 += �����: "<<dat1<<endl;

	//cout<<"������� ����: ";
	//cin>>d1;
	//DBDate dat2(d1);
	//cout<<"���� 2: "<<dat2<<endl;
	//if(!dat2.CorrectDate()) return 0;
	//cout<<"��������� ��� ==: "<<(dat1==dat2)<<endl;
	//cout<<"��������� ��� "<<dat1<<">"<<dat2<<": "<<(dat2>dat1)<<endl;
	//cout<<"�������� ���: "<<dat1-dat2<<endl;
	//system("pause");
	//return 0;

}