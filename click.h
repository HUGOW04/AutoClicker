#pragma once
#include <iostream>
#include <Windows.h>



class Autoclicker
{
public:
	void menu()
	{
		std::cout << "Press 'X' to enable and 'Z' to disable autoclicker\n";
	}

	void clicker()
	{
		bool click = false;
		int countClicks = 0;
		while (true)
		{
			if (GetAsyncKeyState('X'))
			{
				click = true;
			}
			else if (GetAsyncKeyState('Z'))
			{
				click = false;
			}
			if (click)
			{
				system("cls");
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				countClicks++;
				std::cout << "Total clicks: " << countClicks;
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				Sleep(1);
			}
		}
	}
};
