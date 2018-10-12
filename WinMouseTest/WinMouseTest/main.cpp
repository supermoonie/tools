#include <windows.h>
#include <iostream>
#include "tchar.h"

using namespace std;

#define MAX_TEXT_LEN 512

BOOL CALLBACK EnumChildProc(HWND child, LPARAM lParam);
void FindHandleByClassName(HWND hwnd, TCHAR* className);

HWND targetHwnd = NULL;

int main(int argc, char *argv[])
{
	//    SetCursorPos(0, 0);
	//    mouse_event(MOUSEEVENTF_MOVE, 200, 200, 0, 0);
	//    for(int i = 0; i < 300; i ++) {
	//        mouse_event(MOUSEEVENTF_MOVE, 1, 0, 0, 0);
	//        cout << i << endl;
	//        Sleep(500);
	//    }

	HWND root = GetDesktopWindow();
	TCHAR* className = _T("Client Caption");
	EnumChildWindows(root, EnumChildProc, (LPARAM)className);
	if (targetHwnd) {
		SetForegroundWindow(targetHwnd);
		TCHAR cName[MAX_TEXT_LEN];
		GetClassName(targetHwnd, cName, MAX_TEXT_LEN);
		_tprintf(_T("hwnd=%p, className=%s\n"), targetHwnd, cName);
		RECT rect;
		GetWindowRect(targetHwnd, &rect);
		cout << rect.left << endl;
		cout << rect.top << endl;
		/*
		SetCursorPos(rect.left + 100, rect.top + 100);
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		*/
	}
	return 0;
}

BOOL CALLBACK EnumChildProc(HWND child, LPARAM lParam) {
	if (child == NULL) {
		return FALSE;
	}
	TCHAR* toFind = (TCHAR*)lParam;
	TCHAR winName[MAX_TEXT_LEN];
	GetClassName(child, winName, sizeof(winName) / sizeof(TCHAR));
	wcout << winName << endl;
	if (_tcscmp(winName, toFind) == 0) {
		MessageBox(NULL, winName, TEXT("info"), MB_OK);
		targetHwnd = child;
		return FALSE;
	}
	return TRUE;
}

void FindHandleByClassName(HWND hwnd, TCHAR *className) {
	//    HWND root = GetDesktopWindow();
	//    EnumChildWindows(root, EnumChildProc, NULL);
}
