#include "dbtable.h"

int main()
{
	system("chcp 1251 > nul");
	DBtable tab;
	tab.readTable(tab,"table.txt");

	tab.printTable(tab);
	tab.record(tab);

	DBtable tab2;
	tab.readTable(tab2,"out.txt");
	tab.printTable(tab2);

	system("pause");
	return 0;

}