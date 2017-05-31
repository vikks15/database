#pragma once
#include<iostream>
#include<string>
using namespace std;
static const int daysOfMonth[] = {0,31,28,31};
class DBDate{
private:
	int day,month,year;
public:
	bool CorrectDate(); //возвращает ошибку если дата неправильная
	bool IsLeapYear(); //високосный год
	DBDate(){};
	DBDate(int d, int m, int y){ //constructor from day month year
		day = d;
		month = m;
		year = y;
	};
	DBDate(string dat){ //constructor from string
		int  j = 0;
		char* num[3];
		char line[255];
		strcpy_s(line, dat.length()+1, dat.c_str());
		char* token = "", *nexttoken = line;
		while(token = strtok_s(nexttoken,".",&nexttoken))
		{
			num[j] = token;
			j++;
		}
		day = atoi(num[0]);
		month = atoi(num[1]);
		year = atoi (num[2]);
		if (!CorrectDate()) cout<<"Неправильно введена дата"<<endl;
	};  
	~DBDate(){}
	int DayInMonth(DBDate& dat);
	void DataCorrection();
	//-----------Перегрузки-------------------------------------
	const bool operator > (DBDate& dat1);
	DBDate& operator+ (DBDate& dat1);
	const int operator- (DBDate& dat1);
	DBDate& operator += (int d); 
	const bool operator == (DBDate& dat1);
	friend ostream& operator<<(ostream &s, DBDate &dat){
		return s<<dat.day<<"."<<dat.month<<"."<<dat.year;
	}
};
