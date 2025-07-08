#include "stdafx.h"

#include <iostream>
#include <vector>
#include <Windows.h>

#include "proc.h"
#include "mem.h"
#include "ascii.h"

bool bHP = false, bMP = false, bHearts = false;

void Menu() {
	std::cout << "HOTKEY ||   FUNCTIONS   || STATUS\n";
	std::cout << "=============================\n";
	std::cout << " NUM1  ||  Infinite HP  ||  " << (bHP ? "ON" : "OFF") << "\n";
	std::cout << " NUM2  ||  Infinite MP  ||  " << (bMP ? "ON" : "OFF") << "\n";
	std::cout << " NUM3  ||  Inf. Hearts  ||  " << (bHearts ? "ON" : "OFF") << "\n\n";
	std::cout << "Press INSERT to exit the trainer.\n";
}

int main() {
	HANDLE hProcess = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 9);

	uintptr_t moduleBase = 0;
	uintptr_t draBase = 0;

	DWORD procId = GetProcId(L"game.exe");

	if (procId) {
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
		moduleBase = GetModuleBaseAddress(procId, L"game.exe");
		draBase = GetModuleBaseAddress(procId, L"dra03.dll");

		AsciiArt();
		getchar();
		ClearScreen();
		Menu();
	} else {
		std::cout << "game.exe process not found! Press enter to exit.\n";
		getchar();
		return 0;
	}

	DWORD dwExit = 0;

	while (GetExitCodeProcess(hProcess, &dwExit) && dwExit == STILL_ACTIVE) {
		if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
			bHP = !bHP;

			if (bHP) {
				mem::NopEx((BYTE*)(draBase + 0x178B51), 7, hProcess);
				ClearScreen();
				Menu();
			} else {
			mem::PatchEx((BYTE*)(draBase + 0x178B51), (BYTE*)"\x66\x89\x05\xC4\x63\x75\x00", 7, hProcess);
				ClearScreen();
				Menu();
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
			bMP = !bMP;

			if (bMP) {
				mem::NopEx((BYTE*)(draBase + 0x20FCE9), 8, hProcess);
				ClearScreen();
				Menu();
			} else {
				mem::PatchEx((BYTE*)(draBase + 0x20FCE9), (BYTE*)"\x66\x44\x29\x0D\x2F\xF2\x6B\x00", 8, hProcess);
				ClearScreen();
				Menu();
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
			bHearts = !bHearts;

			if (bHearts) {
				mem::NopEx((BYTE*)(draBase + 0x20FCBD), 8, hProcess);
				ClearScreen();
				Menu();
			} else {
				mem::PatchEx((BYTE*)(draBase + 0x20FCBD), (BYTE*)"\x66\x44\x29\x0D\x5F\xF2\x6B\x00", 8, hProcess);
				ClearScreen();
				Menu();
			}
		}

		if (GetAsyncKeyState(VK_INSERT) & 1) {
			return 0;
		}

		Sleep(100);
	}

	ClearScreen();
	std::cout << "game.exe process has exited. Press enter to exit the trainer.\n";
	getchar();
	return 0;
}