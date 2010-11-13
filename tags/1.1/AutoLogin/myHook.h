#include "mySocket.h"
#include <windows.h>
#include <Winsock2.h>
#pragma comment(lib,"ws2_32")

int gameRecvAddress=0x64C740;
char *pRecvAddress = NULL;
PROC oldRecv;
typedef int (WINAPI *PFNRECV)(SOCKET s,              
  const char FAR *buf,  
  int len,               
  int flags   
  );
int GetImgInt(char *pImg)
{
	int iret = 0;
	
	return iret;
}

int WINAPI MyRecv(){

	_asm{
// 		sub esp,0x0c
// 		pop pRecvAddress
// 		add esp,0x10
		pop ebp
		pop eax
		push ebp 
		mov ebp,esp
		push eax
		ret
	}

	return 1;
}

void hookRecv()
{
__asm{
			mov edx,edx
			mov ecx,ecx
	  }
	PROC pfnOrig=GetProcAddress(GetModuleHandle("ws2_32"),"recv");//先获取send的地址
oldRecv=pfnOrig;
	HMODULE hmodCaller=GetModuleHandle("game.exe");
//	ReplaceIATEntryInOneMod("ws2_32.dll",pfnOrig,(PROC)MySend,hmodCaller);
	DWORD   dwOldProcess;   
	int *myRecvAddress=(int*)MyRecv;
	
	DWORD pInt = NULL;
	pInt = (DWORD)myRecvAddress - (DWORD)pfnOrig -5;    //计算call后面的跳转到MyRecv 的地址

	VirtualProtect((LPVOID)pfnOrig,5,PAGE_READWRITE,&dwOldProcess);   

	char kiss[10] = {0};
	kiss[0] = 0xe8;
	*(DWORD *)(kiss+1) = pInt;


	if(!WriteProcessMemory(GetCurrentProcess(), (LPVOID)pfnOrig,kiss,5, NULL))
	{
		MessageBox(0,"修改E8失败","",0);
		ExitProcess(1);
	}
	
	VirtualProtect((LPVOID)pfnOrig,5,dwOldProcess,0);
	
	// TODO: 在此添加控件通知处理程序代码
}