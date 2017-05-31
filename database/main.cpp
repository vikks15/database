#include "dbtable.h"
#include "dbdate.h"
#include "header.h"

int main()
{
	system("chcp 1251 > nul");
	bool m1 = true;
	int studId;
	DBTableSet set;
	set.readSet("DBtables.txt");

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
				DBDate* d=NULL;
				void* val=NULL;

				cout<<"Введите название книги: ";
				getline(cin,bookName);
				vector <Row> b = set["Books.txt"].selfRows("2.Title",getValue("String",bookName));

				if(b.size()!=0)	//quantity check
				{
					curBookNum=*(int*)b[0]["1.BookID"];
					col = *(int*)b[0]["5.Number"];
					if(col<=0)
					{
						cout<<"Данной книги временно нет."<<endl;
						break;
					}
					//--------------------Abonement check-----------------
					val = new int (studId); //no getvalue
					vector <Row> ab = set["Abonements.txt"].selfRows("1.StudentID",val);
					
					for(int i = 0; i<ab.size(); i++)
					{
						myBookNum = *(int*)ab[i]["2.BookID"];
						d = (DBDate*)ab[i]["4.InDate"];
						if (myBookNum==curBookNum && d==NULL) 
						{
							check=0;
							cout<<"У вас уже есть эта книга."<<endl;
							break;
						}
					}
					if (check==0) break;
					//--------------------------------------------------

					//change number of remaining books
					col--;
					*(int*)set["Books.txt"].data[curBookNum-1]["5.Number"] = col;//record in set
					set["Books.txt"].record("Books.txt");//record in file

					//------making abonement------------------------
					ofstream fout("Abonements.txt", ios_base::app);
					fout<<endl<<studId<<"|"<<curBookNum<<"|"<<"1.06.2017|-";
					fout.close();
					set.dbset.erase("Abonements.txt");
					set.addToSet("Abonements.txt");
					//----------------------------------------------------------

					cout<<"Книга выдана"<<endl;
				}
				else cout<<"Данной книги нет в библиотеке"<<endl;
				delete d;
				delete val;
				break;
			}
		case 2:
			{
				set["Books.txt"].printTable();	
				break;
			}
		case 3:
			{
				return 0;
			}
		}
		system("pause");
		system("cls");
	}
}