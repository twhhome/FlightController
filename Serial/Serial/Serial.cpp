#include "stdafx.h"
#include "SerialPort.h"
#include <iostream>
#include <windows.h>  

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

using namespace std;
const char button[8] = { 'W','A','S','D','I','J','K','L' };
bool state[8] = { 0 };
int COM;
bool controlState = false;
CSerialPort mySerialPort;

void color(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

void check(int a) {
	unsigned char *c = new unsigned char(button[a]);
	if (!KEY_DOWN(*c)) {
		if (state[a]) {
			state[a] = false;
			*c += 32;
			mySerialPort.WriteData(c, 1);
			*c -= 32;
		}
		color(7);
	}
	else {
		if (!state[a]) {
			state[a] = true;
			mySerialPort.WriteData(c, 1);
		}
		color(112);
	}
	printf("  %c  ", *c);
	color(7);
}

int main()
{
	cout << "COM:";
	cin >> COM;

	if (!mySerialPort.InitPort(COM)) {
		cout << "initPort fail !\nProgram will exit in 5 seconds.";
		Sleep(5000);
		return 0;
	}
	else cout << "initPort success !\n";
	
	if (!mySerialPort.OpenListenThread()) cout << "OpenListenThread fail !\n";
	else cout << "OpenListenThread success !\n";

	Sleep(1000);
	cout << "Please turn on the remote control !\n";

	while (1) {
		if (KEY_DOWN('P')) {
			while (KEY_DOWN('P'));//Wait until button released
			controlState = true;
			while (controlState) {
				cout << "In Controlling... Press P to quit.\n";
				printf("      "); check(0); printf("          "); check(4);
				printf("\n\n ");
				check(1); check(2); check(3); check(5); check(6); check(7);
				Sleep(20);//循环时间间隔，防止太占内存   
				system("cls");//清屏   
				if (KEY_DOWN('P')) {
					while (KEY_DOWN('P'));//Wait until button released
					controlState = false;
				}

			}
		}
	}

	return 0;
}