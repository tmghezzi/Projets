#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <string>
#include <VMProtectSDK.h>
using namespace std;

int secretfunction(int a)
{
	unsigned int b = 0xDEADBEEF;
	return a + b;
}

void cpuid(unsigned int CPUInfo[4], int InfoType)
{
	__asm
	{
		mov    esi, CPUInfo
			mov    eax, InfoType
			xor    ecx, ecx
			cpuid
			mov    dword ptr[esi + 0], eax
			mov    dword ptr[esi + 4], ebx
			mov    dword ptr[esi + 8], ecx
			mov    dword ptr[esi + 12], edx
	}
}

void test(unsigned int CPUInfo[4], int InfoType)
{
	__asm
	{
		mov    esi, CPUInfo
			mov    eax, InfoType
			xor    ecx, ecx
			cpuid
			mov    dword ptr[esi + 0], eax
			mov    dword ptr[esi + 4], ebx
			mov    dword ptr[esi + 8], ecx
			mov    dword ptr[esi + 12], edx
	}
}

int main()
{
	char* str = (char*)malloc(100);
	strcpy(str, "zepek");
	char* hwid = (char*)malloc(100);
	unsigned int CPUInfo[4];
	int InfoType = 0x1;
	cpuid(CPUInfo, InfoType);
	printf("do_cpuid cmd=0x3 %lx %lx %lx %lx\n", CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
	VMProtectGetCurrentHWID(hwid,100);

	DWORD a = 100;
	unsigned int r = 0;
	
	VMProtectBegin(str);
	GetComputerNameA(str, &a);
	__asm{
	xor eax, eax};
	GetComputerNameA(str, &a);
	GetComputerNameA(str, &a);
	//unsigned int r = secretfunction(a);
	VMProtectEnd();
	printf("res = %d %s \n", r, hwid);
	system("PAUSE");
	
	return 0;
}