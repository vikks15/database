#include "dbtable.h"
#include "dbdate.h"
#include "header.h"

int main()
{
	system("chcp 1251 > nul");

	DBTableSet set;
	set.readSet();
	//set.addToSet("third");
	//set.printSet();

	bool m1 = true;

	while(m1)
	{
		switch(menu1())
		{
		case 1:
			{
				string name;
				cout<<"Введите имя и фамилию: ";
				cin>>name;
				//name check
				m1=false;
				break;
			}
		case 2:
			{
				return 0;
			}

		}
		system("cls");
	}


	while(true)
	{
		switch(menu2())
		{
		case 1:
			{
				cout<<"Введите название книги: ";
				break;
			}
		case 2:
			{
				cout<<"Отдать книгу ";
				break;
			}
		case 3:
			{
				cout<<"Посмотреть книгу ";
				break;
			}
		case 4:
			{
				return 0;
			}

		}
		system("pause");
		system("cls");
	}

	


}