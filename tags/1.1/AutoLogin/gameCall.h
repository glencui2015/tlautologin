#include <windows.h>
/*
004C184B    C745 C8 BC96650>mov dword ptr ss:[ebp-38],Game.006596BC
004C1852    894D DA         mov dword ptr ss:[ebp-26],ecx
004C1855    8D55 C8         lea edx,dword ptr ss:[ebp-38]
004C1858    894D FC         mov dword ptr ss:[ebp-4],ecx
004C185B    8B0D DCE46B00   mov ecx,dword ptr ds:[6BE4DC]
004C1861    52              push edx
004C1862    C645 D4 01      mov byte ptr ss:[ebp-2C],1
004C1866    8975 D6         mov dword ptr ss:[ebp-2A],esi
004C1869    897D DA         mov dword ptr ss:[ebp-26],edi
004C186C    E8 FF410800     call Game.00545A70
*/
short answerData[0x40]={0};
void answerTheQuestion_Integer(char *num){
	answerData[0]=0x96bc;//0x06596BC;
	answerData[1]=0x0065;
	answerData[6]=1;
	answerData[7]=num[0];
	answerData[8]=num[1];
	answerData[9]=num[2];
	answerData[10]=num[3];
	__asm{
		lea eax,answerData
		push eax
		mov ecx,dword ptr ds:[0x6BE4DC]
		mov eax,0x0545A70
		call eax
	}
}


