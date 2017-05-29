#pragma once
#include "dbtable.h"
#include "dbdate.h"

int menu1()
{
	int number = 0;

	cout<<"1 - Войти в личный кабинет"<<endl;
	cout<<"2 - Выйти из программы"<<endl;
	cin>>number;

	cin.clear();
	cin.ignore(256,'\n');
	return number;
}

int menu2()
{
	int number = 0;

	cout<<"1 - Взять книгу"<<endl;
	cout<<"2 - Сдать книгу"<<endl;
	cout<<"3 - Посмотреть какие книги на руках"<<endl;
	cout<<"4 - Выйти из личного кабинета"<<endl;
	cin>>number;

	cin.clear();
	cin.ignore(256,'\n');
	return number;
}