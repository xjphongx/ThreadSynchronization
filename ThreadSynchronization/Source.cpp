#include <iostream>
#include<Windows.h>
#include <fstream>
#include <thread>
#include <mutex>


using namespace std; 
mutex mtx;

void printNum() {
	mtx.lock();
	ofstream outFile;
	outFile.open("synch.txt", std::ios_base::app); // this will continue to update synch.txt file
	//outer loop for amount of lines
	for (int a = 0; a < 20; a++) 
	{
		//inner loop for how many numbers per line
		for (int b = 1; b <= 26; b++)
		{
			outFile << b << " ";
			cout << b << " ";
		}
		outFile << endl;
		cout << endl;
	}
	cout << "number printing complete" << endl;
	outFile.close();
	mtx.unlock();
}
void printAlpha() {
	mtx.lock();
	ofstream outFile;
	outFile.open("synch.txt", std::ios_base::app);
	for (int a = 0; a < 20; a++)
	{
		for (int b = 65; b <= 90; b++)
		{
			cout << (char)b << " ";
			outFile << (char)b << " ";
		}
		cout << endl;
		outFile << endl;
	}
	cout << "alphabet printing complete" << endl;
	outFile.close();
	mtx.unlock();
}
int main()
{
	ofstream outFile;
	cout << "Thread Synchronizaton" << endl;
	thread numThread(printNum);
	thread alphaThread(printAlpha);

	numThread.join();
	alphaThread.join();
	
	

	
	return 0;
}
