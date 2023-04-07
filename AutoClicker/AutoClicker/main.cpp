#include <Windows.h>

// Function prototypes
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);
void click();

// Global variables
const char szClassName[] = "AutoClicker";
HHOOK g_hook = NULL;
bool g_clicking = false;

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
	HWND hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, szClassName, "AutoClicker", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, NULL, NULL, hInstance, NULL);
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
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
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