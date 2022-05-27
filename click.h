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
			if (!click)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				Sleep(1);
			}
		}
	}
};
