#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#pragma warning(disable : 4996)
using namespace std;
struct Employee {
	int num;
	char name[10];
	double hours;
};

string GetExeFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL,(LPWSTR)buffer, MAX_PATH);
	return std::string(buffer);
}

string GetExePath()
{
	std::string f = GetExeFileName();
	return f.substr(0, f.find_last_of("\\/"));
}

char* prepareDataForCreatorProcess(char*& fileEmployeeName, int number){
	char data[200] = "Creator ";
	char* a = strcat(fileEmployeeName, " ");
	char* b = strcat(data, a);
	char* creator = new char[100];
	strcpy(creator, strcat(b, to_string(number).c_str()));
	return creator;
}

void runCreatorProcess(char* dataForCreator){
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	ZeroMemory(&pi, sizeof(pi));
	char path[200];
	strcpy(path, GetExePath().c_str());
	strcat(path, ":\\Creator.exe");
	if (!CreateProcess((LPCWSTR)L"Creator.exe", (LPWSTR)dataForCreator, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)){
		cout << GetLastError();
		cout << "The creator process is not created. " << endl;
		return;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

void readBinaryFile(char* fileName){
	ifstream in(fileName, ios::binary);
	cout << "Employees: " << endl;
	while (in.peek() != EOF){
		Employee employee;
		in.read((char*)&employee, sizeof(Employee));
		cout << "Employee number: " << employee.num << endl;
		cout << "Employee name: " << employee.name << endl;
		cout << "Employee hours: " << employee.hours << endl;
	}
	in.close();
}

char* prepareDataForReporterProcess(char* fileEmployeeName, char* fileReportName, int salary){
	char data[200] = "Reporter ";
	char* a = strcat(data, fileEmployeeName);
	char* b = strcat(a, " ");
	char* c = strcat(b, fileReportName);
	char* d = strcat(c, " ");
	char* reporter = new char[200];
	strcpy(reporter, strcat(d, to_string(salary).c_str()));
	return reporter;
}

void runReporterProcess(char* data){
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	char path[200];
	strcpy(path, GetExePath().c_str());
	strcat(path, "\\Reporter.exe");
	if (!CreateProcess((LPCWSTR)path, (LPWSTR)data, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)){
		cout << "The reporter process is not created." << endl;
		return;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

void readFile(char* fileName){
	ifstream fin(fileName);
	char line[200];
	while (!fin.eof())
	{
		fin.getline(line, 200);
		cout << line << endl;
	}
	fin.close();
}

int main()
{
	char* fileName = new char[30];
	cout << "Enter name of file: ";
	cin >> fileName;
	cout << endl;
	int amountOfRecords;
	cout << "Enter amount of file's records: ";
	cin >> amountOfRecords;
	cout << endl;
	char* dataForCreator = prepareDataForCreatorProcess(fileName, amountOfRecords);
	cout << dataForCreator << endl;
	runCreatorProcess(dataForCreator);
	readBinaryFile(fileName);
	char* fileReportName = new char[30];
	cout << "Enter file report name: ";
	cin >> fileReportName;
	cout << endl;
	int salary;
	cout << "Enter salary for hour: ";
	cin >> salary;
	cout << endl;
	char* dataForReporter = prepareDataForReporterProcess(fileName, fileReportName, salary);
	cout << dataForReporter << endl;
	runReporterProcess(dataForReporter);
	readFile(fileReportName);
	return 0;
}
