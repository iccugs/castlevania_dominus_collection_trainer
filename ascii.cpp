#include "stdafx.h"
#include "ascii.h"

void AsciiArt() {
	const char* art = R"(
	  _____         __  __                   _     
	 / ___/__ ____ / /_/ /__ _  _____ ____  (_)__ _
	/ /__/ _ `(_-</ __/ / -_) |/ / _ `/ _ \/ / _ `/
	\___/\_,_/___/\__/_/\__/|___/\_,_/_//_/_/\_,_/ 
	  / _ \___  __ _  (_)__  __ _____              
	 / // / _ \/  ' \/ / _ \/ // (_-<              
	/____/\___/_/_/_/_/_//_/\_,_/___/              
	 / ___/__  / / /__ ____/ /_(_)__  ___          
	/ /__/ _ \/ / / -_) __/ __/ / _ \/ _ \         
	\___/\___/_/_/\__/\__/\__/_/\___/_//_/         
	/_  __/______ _(_)__  ___ ____                 
	 / / / __/ _ `/ / _ \/ -_) __/                 
	/_/ /_/  \_,_/_/_//_/\__/_/                    

		By Paradox.Actual
	)";
	std::cout << art << std::endl;
}

void ClearScreen() {
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count, cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	SetConsoleCursorPosition(hStdOut, homeCoords);
}
