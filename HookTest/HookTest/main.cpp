#include <iostream>
#include <Windows.h>

using namespace std;

HDC hdc = GetWindowDC(GetDesktopWindow());

void draw() {
	POINT point;
	GetCursorPos(&point);
	cout << "x: " << point.x << ", y: " << point.y << endl;
}

LRESULT CALLBACK mykeyboard(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= HC_ACTION && wParam == WM_KEYDOWN) {
		LPKBDLLHOOKSTRUCT pkb = (LPKBDLLHOOKSTRUCT)lParam;
		cout << pkb->vkCode;
		switch (wParam) {
		case WM_KEYDOWN:
			cout << " down";
			break;
		case WM_KEYUP:
			cout << " up";
			break;
		case WM_SYSKEYDOWN:
			cout << " sys key down";
			break;
		case WM_SYSKEYUP:
			cout << " sys key up";
			break;
		}
		cout << endl;
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK mymouse(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0){
		switch (wParam){
		case WM_LBUTTONDOWN:
			//cout << "Left Button Down" << endl;
			draw();
			break;

		case WM_LBUTTONUP:
			cout << "Left Button Up" << endl;
			break;
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main()
{
	HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mymouse, 0, 0);
	HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, mykeyboard, 0, 0);
	MSG msg;
	while (GetMessage(&msg, NULL, NULL, NULL))                
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(mouseHook);
	UnhookWindowsHookEx(keyboardHook);
	return 0;
}