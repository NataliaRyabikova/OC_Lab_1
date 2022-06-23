#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;

struct Employee {
	int num;
	char name[10];
	double hours;
};

int main(int argc, char* argv[])
{
	char* filename = argv[1];
	ofstream out(filename, ios::binary);
	int amount = atoi(argv[2]);
	cin >> amount;
	for (int i = 0; i < amount; i++)
	{
		Employee employee;
		cout << "Enter employee number: ";
		cin >> employee.num;
		cout << "Enter employee name: ";
		cin >> employee.name;
		cout << "Enter hours: ";
		cin >> employee.hours;
		out.write((char*)&employee, sizeof(struct Employee));
	}
	out.close();
	system("pause");
	return 1;
}
