#include <iostream>
#include<Windows.h>
#include <fstream>


using namespace std;
HANDLE mutex;

DWORD WINAPI printNum(LPVOID lpParam) {
	ofstream outFile;
	outFile.open("synch.txt", std::ios_base::app); // this will continue to update synch.txt file
	//outer loop for amount of lines
	for (int a = 0; a < 20; a++) 
	{
		WaitForSingleObject(mutex, INFINITE);
		//inner loop for how many numbers per line
		for (int b = 1; b <= 26; b++)
		{
			outFile << b << " ";
			cout << b << " ";
		}
		outFile << endl;
		cout << endl;
	}
	ReleaseMutex(mutex);
	cout << "number printing complete" << endl;
	outFile.close();
	return 0;
}
DWORD WINAPI printAlpha(LPVOID lpParam) {
	ofstream outFile;
	outFile.open("synch.txt", std::ios_base::app);
	for (int a = 0; a < 20; a++)
	{
		WaitForSingleObject(mutex, INFINITE);
		for (int b = 65; b <= 90; b++)
		{
			cout << (char)b << " ";
			outFile << (char)b << " ";
		}
		cout << endl;
		outFile << endl;
	}
	ReleaseMutex(mutex);
	cout << "alphabet printing complete" << endl;
	outFile.close();
	return 0;
}
int main()
{
	cout << "Thread Synchronizaton" << endl;
	HANDLE numThread, alphaThread;

	mutex = CreateMutex(
		NULL,
		FALSE,
		NULL);

	alphaThread = CreateThread(
		NULL,
		0,
		printAlpha,
		NULL,
		0,
		NULL);

	numThread = CreateThread(
		NULL,
		0,
		printNum,
		NULL,
		0,
		NULL);

	
	
	WaitForSingleObject(alphaThread, INFINITE);
	WaitForSingleObject(numThread, INFINITE);
	

	CloseHandle(numThread);
	CloseHandle(alphaThread);

	
	return 0;
}
