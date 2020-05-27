#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#define DLL_NAME "YOUR.DLL"
#define JUNKS \
__asm _emit 0x00 \
__asm _emit 0x01 \
__asm _emit 0x03 \
__asm _emit 0x04 \
__asm _emit 0x5d \
__asm _emit 0x58 \
__asm _emit 0x7e \
__asm _emit 0xdf \
__asm _emit 0xf6 \
__asm _emit 0xb1 \
__asm _emit 0x13 \
__asm _emit 0x73 \
__asm _emit 0xb8 \
__asm _emit 0x96 \
__asm _emit 0xc3 \
__asm _emit 0x0f \
__asm _emit 0x18 \
__asm _emit 0x97 \
__asm _emit 0x24 \
__asm _emit 0xbb \
__asm _emit 0x3d \
__asm _emit 0xc6 \
__asm _emit 0x3f \
__asm _emit 0x3e \
__asm _emit 0x08 \
__asm _emit 0x77 \
__asm _emit 0x12 \
__asm _emit 0x27 \
__asm _emit 0xfb \
__asm _emit 0x34 \
__asm _emit 0x1c \
__asm _emit 0x0e \


#define _JUNK_BLOCK(s) __asm jmp s JUNKS __asm s:
DWORD Process(char* ProcessName)
{
	_JUNK_BLOCK(jmp_label1)
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	
	_JUNK_BLOCK(jmp_label2)
	PROCESSENTRY32 ProcEntry;
	
	_JUNK_BLOCK(jmp_label3)
	ProcEntry.dwSize = sizeof(ProcEntry);
	
	_JUNK_BLOCK(jmp_label4)
	do
	{
		_JUNK_BLOCK(jmp_label5)
		if (!strcmp(ProcEntry.szExeFile, ProcessName))
		{
			_JUNK_BLOCK(jmp_label6)
			DWORD dwPID = ProcEntry.th32ProcessID;
			
			_JUNK_BLOCK(jmp_label7)
			CloseHandle(hPID);
			
			_JUNK_BLOCK(jmp_label8)
			return dwPID;
		}
		
		_JUNK_BLOCK(jmp_label9)
	}
	while (Process32Next(hPID, &ProcEntry));
	
	_JUNK_BLOCK(jmp_label10)
}

int main()
{
	_JUNK_BLOCK(jmp_label11)
	DWORD dwProcess;
	
	_JUNK_BLOCK(jmp_label12)
	char myDLL[MAX_PATH];
	
	_JUNK_BLOCK(jmp_label13)
	GetFullPathName(DLL_NAME, MAX_PATH, myDLL, 0);
	
	_JUNK_BLOCK(jmp_label4)
	dwProcess = Process("csgo.exe");
	
	_JUNK_BLOCK(jmp_label15)
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, dwProcess);
	
	_JUNK_BLOCK(jmp_label16)
	LPVOID allocatedMem = VirtualAllocEx(hProcess, NULL, sizeof(myDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	
	_JUNK_BLOCK(jmp_label17)
	WriteProcessMemory(hProcess, allocatedMem, myDLL, sizeof(myDLL), NULL);
	
	_JUNK_BLOCK(jmp_label18)
	CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocatedMem, 0, 0);
	
	_JUNK_BLOCK(jmp_label19)
	CloseHandle(hProcess);
	
	_JUNK_BLOCK(jmp_label20)
	return 0;
	
	_JUNK_BLOCK(jmp_label21)
}
