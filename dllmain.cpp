// Includes
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include "pch.h"

// Defines
#define _CRT_SECURE_NO_DEPRICATE
#define _CRT_SECURE_NO_WARNINGS
#define abc(abc) (abc - 0x400000 + (DWORD)GetModuleHandleA(0)) // silly address thingy idk if this works but we'll see

// Usings (yes, I declared std early)
using namespace std;

// Console Code & Function
void Console(const char* title) {
	DWORD tesla;
	VirtualProtect((PVOID)&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &tesla);
	*(BYTE*)(&FreeConsole) = (0xC3);
	AllocConsole();
	SetConsoleTitleA(title);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	HWND ConsoleHandle = GetConsoleWindow();
	::SetWindowPos(ConsoleHandle, HWND_TOP, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	::ShowWindow(ConsoleHandle, SW_NORMAL);
}

// Addy stuff that makes it work and I don't know the addy so yeah
typedef int(__cdecl* Printing)(int a1, const char* a2);
Printing rbx_Print = (Printing)abc(0x51EB70);

// Main Code once injected
void main() {
	Console("Printer");
	cout << "Test!";
	cout << "printing";
	while (true) {
		string print = "";
		getline(cin, print);
		rbx_Print(0, print.c_str());
		cout << "Printed. \n";
	}
}
