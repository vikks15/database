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
				cout<<"Введите имя файла: ";
				cin>>fname;
				way+=fname;
				tab.readTable(tab,way);
				cout<<"Таблица успешно считана"<<endl;
				break;
			}
		case 2:
			{
				cout<<"Укажите путь к файлу: ";
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
				cout<<"Введите имя библиотеки: ";
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
				cout<<"Введите цифру от 1 до 6";
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
	//cout<<"Введите дату: ";
	//cin>>d1;
	//DBDate dat1(d1);
	//if(!dat1.CorrectDate()) return 0;
	////cout<<"Правильность даты "<<dat1.CorrectDate();

	//cout<<"Дата 1: "<<dat1<<endl;

	//cout<<"Введите число: ";
	//cin>>justint;	
	//dat1+=justint;
	//cout<<"Правильная дата1 += число: "<<dat1<<endl;

	//cout<<"Введите дату: ";
	//cin>>d1;
	//DBDate dat2(d1);
	//cout<<"Дата 2: "<<dat2<<endl;
	//if(!dat2.CorrectDate()) return 0;
	//cout<<"Сравнение дат ==: "<<(dat1==dat2)<<endl;
	//cout<<"Сравнение дат "<<dat1<<">"<<dat2<<": "<<(dat2>dat1)<<endl;
	//cout<<"Разность дат: "<<dat1-dat2<<endl;
	//system("pause");
	//return 0;

}