#include "dbtable.h"
#include "dbdate.h"
#include "header.h"

int main()
{
	system("chcp 1251 > nul");

	bool m1 = true;
	int studId;
	DBTableSet set;
	set.readSet();

	//set["Students.txt"].printTable(set["Students.txt"]);
	//set.addToSet("third");
	//set.printSet();

	while(m1)
	{
		switch(menu1())
		{
		case 1:
			{
				string name;
				cout<<"Введите имя и фамилию: ";
				getline(cin, name);
				vector <Row> r = set["Students.txt"].selfRows("2.Name",getValue("String",name));
				if(r.size()!=0)
				{
					m1=false;
					studId=*(int*)r[0]["1.StudentID"];
					cout<<"Вход успешно выполнен. ID студента: "<<studId<<endl;
					system ("pause");
				}
				else 
				{ 
					cout<<"Такого студента нет в базе."<<endl;
					system ("pause");
				}
				break;
			}
		case 2: return 0;

		}
		system("cls");
	}


	while(true)
	{
		switch(menu2())
		{
		case 1:
			{
				string bookName;
				int col,curBookNum; //curBookNum-1 = current Row in Books.txt
				int myBookNum, check=1;
				int* pcol;
				cout<<"Введите название книги: ";
				getline(cin,bookName);
				vector <Row> b = set["Books.txt"].selfRows("2.Title",getValue("String",bookName));

				if(b.size()!=0)
				{
					curBookNum=*(int*)b[0]["1.BookID"];
					col = *(int*)b[0]["5.Number"];
					if(col<=0)
					{
						cout<<"Данной книги временно нет."<<endl;
						break;
					}

					int *buff = new int (studId); //no getvalue
					void *val = buff;

					vector <Row> ab = set["Abonements.txt"].selfRows("1.StudentID",val);

					for(int i = 0; i<ab.size(); i++)
					{
						myBookNum = *(int*)ab[i]["2.BookID"];
						if (myBookNum==curBookNum) 
						{
							check=0;
							cout<<"У вас уже есть эта книга."<<endl;
							break;
							
						}
						if (check=0) break;
					}

					col--;
					pcol=&col;
					set["Books.txt"].data[curBookNum-1]["5.Number"] = pcol;
					set["Books.txt"].record(set["Books.txt"],"Books.txt"); //bug

					//write abonement///
				}
				else cout<<"Данной книги нет в библиотеке"<<endl;


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