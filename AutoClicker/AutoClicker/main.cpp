#include <Windows.h>
#include <tchar.h>
#include <string>

#define CLICKS 1

// Function prototypes
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);
void click();

// Global variables
HWND hWnd;
const char szClassName[] = "AutoClicker";
HHOOK g_hook = NULL;
bool g_clicking = false;
int clickcount = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Register window class
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONERROR | MB_OK);
		return 0;
	}

	// Create window 
	hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, szClassName, "AutoClicker", WS_CAPTION |  WS_OVERLAPPEDWINDOW &~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX), CW_USEDEFAULT, CW_USEDEFAULT, 300, 100, NULL, NULL, hInstance, NULL);
	if (hWnd == NULL)
	{
		MessageBox(NULL,"Window Creation Failed!","Error", MB_ICONERROR | MB_OK);
		return 0;
	}

	// Show window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Install a global keyboard hook
	g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookProc, NULL, 0);
	if (!g_hook)
	{
		MessageBox(NULL, "Failed to install keyboard hook!", "Error", MB_ICONERROR | MB_OK);
		return 1;
	}
	// Main message loop
	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Uninstall the hook before exiting
	UnhookWindowsHookEx(g_hook);
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR clickPaint[] = "Clicks: ";
	TCHAR info[] = "Press 'Q' to start and 'W' to stop";
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// Here your application is laid out.
		// For this introduction, we just print out "CheatEngine!"
		// in the bottom left corner.
		TextOut(hdc, 10, 20, clickPaint, _tcslen(clickPaint));
		TextOut(hdc, 10, 40, info, _tcslen(info));
		// End application-specific layout section.
		EndPaint(hWnd, &ps);
		break;
	case WM_CREATE:
		CreateWindow("Static", "0",
			WS_VISIBLE | WS_CHILD,
			60, 20, 200, 20,
			hWnd, (HMENU)CLICKS, NULL, NULL);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

// Keyboard hook procedure
LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		if (wParam == WM_KEYDOWN)
		{
			int keyCode = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;
			if (keyCode == 'Q')
			{
				g_clicking = true;
				while (g_clicking)
				{
					click();
					clickcount++;
					std::string num = std::to_string(clickcount);
					SetWindowText(GetDlgItem(hWnd, CLICKS), num.c_str());
					MSG msg;
					while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
			}
			if (keyCode == 'W')
			{
				g_clicking = false;
			}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void click()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(rand() % 10);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
