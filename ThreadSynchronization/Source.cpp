#include <iostream>
#include<Windows.h>


using namespace std;
HANDLE mutex;

DWORD WINAPI printNum(LPVOID lpParam) {
	//outer loop for amount of lines
	for (int a = 0; a < 20; a++) 
	{
		WaitForSingleObject(mutex, INFINITE);
		//inner loop for how many numbers per line
		for (int b = 1; b <= 26; b++)
		{
			cout << b << " ";
		}
		cout << endl;
	}
	ReleaseMutex(mutex);
	cout << "number printing complete" << endl;
	return 0;
}
DWORD WINAPI printAlpha(LPVOID lpParam) {

	for (int a = 0; a < 20; a++)
	{
		WaitForSingleObject(mutex, INFINITE);
		for (int b = 65; b <= 90; b++)
		{
			cout << (char)b << " ";
		}
		cout << endl;
	}
	ReleaseMutex(mutex);
	cout << "alphabet printing complete" << endl;
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

	numThread = CreateThread(
		NULL,
		0,
		printNum,
		NULL,
		0,
		NULL);

	alphaThread = CreateThread(
		NULL,
		0,
		printAlpha,
		NULL,
		0,
		NULL);

	WaitForSingleObject(numThread, INFINITE);
	WaitForSingleObject(alphaThread, INFINITE);

	CloseHandle(numThread);
	CloseHandle(alphaThread);

	
	return 0;
}
