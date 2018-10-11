#define WINPROC_API extern "C" __declspec(dllexport)
#include <stdio.h>
#include <Windows.h>
#include <Tlhelp32.h>

void AdjustPrivilege() {
	HANDLE hToken;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken)) {
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid)) {
			AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
		}
		CloseHandle(hToken);
	}
}

WINPROC_API int findProc(const wchar_t* procName) {
	if (procName == nullptr || *procName == '\0') {
		MessageBox(NULL, L"empty", L"warn", MB_OK);
		return -1;
	}
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return -1;
	}
	PROCESSENTRY32 pi;
	pi.dwSize = sizeof(PROCESSENTRY32);
	BOOL bRet = Process32First(hSnapshot, &pi);
	while (bRet) {
		if (wcscmp(procName, pi.szExeFile) == 0) {
			return (int)pi.th32ProcessID;
		}
		bRet = Process32Next(hSnapshot, &pi);
	}
	return -1;
}

WINPROC_API void terminate(const int pid) {
	AdjustPrivilege();
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if (hProcess) {
		TerminateProcess(hProcess, 4);
		CloseHandle(hProcess);
	}
}