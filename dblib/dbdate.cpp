#include "dbdate.h"
bool DBDate::CorrectDate()
{
	if(month==0 || month>12) return 0; //неправильно введен месяц
	if(month!=2 && day>30)
	{
		if(day>31) return 0;//неправильно введен день
		else if((month<8 && (month%2==0)) || month==9 || month==11) return 0;
	}
	else if(month==2 && !IsLeapYear() && day>28) return 0;//високосный год
	else if(month==2 && IsLeapYear() && day>29) return 0;
	else return 1;
}
int day,month,year;
bool DBDate :: IsLeapYear() //проверка високосного года
{
	return !(year%400) || (!(year%4) && (year%100));
}
int DBDate :: DayInMonth(DBDate& dat)
{
	int res = 0;
	if ((dat.month%2!=0 && dat.month<8) || (dat.month==8) || dat.month==10 || dat.month ==12 ) res=31;
	else if (dat.month%2==0 && dat.month<8 && dat.month!=2 || dat.month==9 || dat.month ==11) res=30;
	else if (dat.month==2 && dat.IsLeapYear()) res = 29;
	else if (dat.month==2 && !IsLeapYear()) res = 28;
	return res;
}
void DBDate :: DataCorrection()
{
	while(CorrectDate()==0)
	{
		if(month>12)
		{
			month-=12;
			year++;
		}

		if(day>DayInMonth(*this))
		{
			day-=DayInMonth(*this);
			month++;
		}
	}
}
//------------------Перегрузки-----------------------------
const bool DBDate :: operator > (DBDate& dat1)
{
	if(dat1.year>year) return true;
	else if(dat1.year==year)
	{
		if(dat1.month==month)
		{
			if(dat1.day>day) return true;
			else return false;
		} 
		else if(dat1.month>month) return true;
		else return false;
	}
	else return false;
}
DBDate&  DBDate :: operator+ (DBDate& dat1) { //overload of +
	cout<<"this day "<<this ->day;
	int d = 0, m = 0, y = 0;
	d = dat1.day+(this->day);
	m = dat1.month+(this->month);
	y = dat1.year+(this->year);
	DBDate temp (d,m,y);
	if(!CorrectDate())
	{
		cout<<"Неправильная дата+: "<<temp.day<<"."<<temp.month<<"."<<temp.year<<endl;
		temp.DataCorrection();
	}
	return temp;
};
const int DBDate :: operator- (DBDate& dat1)
{
	int a=1, b = dat1.month, c=1;
	DBDate temp(a,b,c);
	int tmpM = 0, res = 0;
	//cout<<dat1.day<<" "<<day; 12 14
	if(dat1>*(this))
	{
		if(dat1.year==year && dat1.month==month) return (day-dat1.day);
		else if(year==dat1.year)
		{
			int tmpM = DayInMonth(dat1);
			res=tmpM-dat1.day;
			cout<<"day in m"<<tmpM<<" dat1.day"<<dat1.day<<endl;

			for(int i = dat1.month+1; i<month; i++)
			{
				res+=DayInMonth(temp);
				temp.month++;
			}
			res+=day;
			return res;
		}
		else {
			temp.day = dat1.day; // меньшая дата
			temp.year = dat1.year;
			temp.month = dat1.month;

			for(int i = dat1.year; i<year; i++)
			{
				if(temp.IsLeapYear())
					res+=366;
				else res+=365;
				temp.year+=1;
			}

			if(temp>(*this))
			{
				cout<<endl<<"temp "<<temp<<endl;

				int tmpM = DayInMonth(temp);
				res+=tmpM-temp.day;
				temp.month++;
				for(int i = temp.month; i<month; i++)
				{
					res+=DayInMonth(temp);
					temp.month++;
				}
				res+=day;
				cout<<endl<<"temp "<<temp<<endl;
				return res;
			}
			else
			{
				res-=temp.day;
				for(int i = temp.month; i>month; i--)
				{
					temp.month--;
					res-=DayInMonth(temp);

				}
				res+=day;
				return res;
			}
		}

	}
	else cout<<"Нельзя вычитать из меньшей даты большую. ";
}
DBDate& DBDate :: operator += (int d) //overload of +=
{
	day = day + d;
	if(!CorrectDate())
	{
		cout<<"Неправильная дата +=: "<<day<<"."<<month<<"."<<year<<endl;
		DataCorrection();
	}
	return *this;
};
const bool DBDate :: operator == (DBDate& dat1)
{
	if(dat1.day == day && dat1.month == month && dat1.year == year) return true;
	else return false;
}
