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
				cout<<"������� ��� � �������: ";
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
				cout<<"������� �������� �����: ";
				break;
			}
		case 2:
			{
				cout<<"������ ����� ";
				break;
			}
		case 3:
			{
				cout<<"���������� ����� ";
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