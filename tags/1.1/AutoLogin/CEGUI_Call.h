#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

vector<int> CEGUI_WIN;
int BottonCallAddress=0;

string str_win;

int GetCEGUI(){
	return	(int)GetModuleHandle("CEGUIBase.dll");//��ȡģ���ַ
}

int CEGUIBase_Handle=0;

int myTestValue(int address){
	int a=0;
	if(IsBadReadPtr((void*)(address),4)==0){
		a=1;
	}else{
		a=0;
	}
	return a;
}

int getwin(int sheet){//�ݹ��������"����"����
	//�ȿ����е�ǰ�Ĵ�����ӵ�е��Ӵ���,
	int local_sheet=sheet;
	int child=*(int*)(local_sheet+0x2c);    //����Ŀ�ʼ��ַ
	int end=*(int*)(local_sheet+0x30);		//����Ľ�����ַ
	if(child==end){
		return 0;
	}
//��ȡ�����еĴ��ڶ���
	for(int i=child;i!=end;i+=4){
		int winobj=*(int*)i;
		if(winobj==0){
			continue;
		}
		char isVisible=*(char*)(winobj+0x129);
		if(isVisible==0){//���������Ƿ�ɼ������ɼ���continue
			continue;
		}else{//�ݹ鿴������û�Ӵ���
			CEGUI_WIN.push_back(winobj);
			int win2=getwin(winobj);//���Ӵ��ھͷ��ء�
	//		if(win2){	
	//			return win2;
	//		}
		}

	}
	return 0;
}


int SearchAllCEGUI_Window(){//��ȡ����CEGUI���Ӵ���

	if(CEGUIBase_Handle==0){
		CEGUIBase_Handle=GetCEGUI();//����CEGUIBase.dll�����˽��ڴ�û��
	}

	if(CEGUIBase_Handle==0){//����CEGUIBase.dll�����˽��ڴ�û��
		return 0;
	}

	typedef int (*ADDPROC)();
	ADDPROC getSingleton = (ADDPROC)(0x492e0+CEGUIBase_Handle);//���ÿ�θ��¶�Ҫ����
//mov eax,dword ptr ds:[CEGUI::Singleton<CEGUI::System>::m>
	int WinBase=getSingleton();//��ȡ���ڻ��ࡣ
	if(WinBase==0){
		return 0;
	}

	char aaa[30]={0};
//��ȡ���Ի�Ĵ���
	int d_activeSheet=*(int*)(WinBase+0x2c);
/////������Ҫ�ݹ��������"����"�����ˡ�
	if(myTestValue(d_activeSheet)==0){
		return 0;
	}
	getwin(d_activeSheet);//�ݹ�������ڣ�������CEGUI_WIN���vector��
/*	for(vector<int>::iterator itr = CEGUI_WIN.begin();itr!=CEGUI_WIN.end();++itr){
		memset(aaa,0,sizeof(aaa));
	}*/
	return 1;
}
/*
///////////
//ʹ�ô��ڰ�ť��
char *str_fun_next="HuoDongRiCheng_next_click();";
char *str_fun="SelectServer_SelectOk();";

//char *str_fun="Pet_Feed_Clicked();";


void win_next_botton(){

	if(BottonCallAddress==0){
		int UI_CEGUI_Base=(int)GetModuleHandle("UI_CEGUI.dll");
		BottonCallAddress=UI_CEGUI_Base+0x27210;
	}
//	MessageBox(0,"","",0);
	for(vector<int>::iterator itr = CEGUI_WIN.begin();itr!=CEGUI_WIN.end();++itr){
		if(*itr==0){
			continue;
		}
		int a=*(int*)(*itr+0xf0);
		if(a==0){
			continue;
		}
		int xml_str=*(int*)(a+0x28);
		if(myTestValue(xml_str)==0){
			continue;
		}
		if(strcmp((char*)xml_str,"Huodongricheng/Huodongricheng.layout.xml")==0){
			__asm{
				mov eax,itr
				mov eax,[eax]
				push eax
				mov eax,str_fun_next
				push eax
				mov esi,a
				mov ecx,esi
				
				call BottonCallAddress
			}
			CEGUI_WIN.clear();
			return ;
		}
	}
	CEGUI_WIN.clear();
}


int win_enter_botton(){
//	MessageBox(0,"","",0);
	__asm{
		mov eax,eax
	}
	if(BottonCallAddress==0){

		int UI_CEGUI_Base=(int)GetModuleHandle("UI_CEGUI.dll");
		BottonCallAddress=UI_CEGUI_Base+0x27790;
	}

	for(vector<int>::iterator itr = CEGUI_WIN.begin();itr!=CEGUI_WIN.end();++itr){
		if(*itr==0){
			continue;
		}
		int a=*(int*)(*itr+0xf0);
		if(a==0){
			continue;
		}
		int xml_str=*(int*)(a+0x28);
		if(myTestValue(xml_str)==0){
			continue;
		}//0BDF7B08  0BDF77F0  ASCII "SelectServer/SelectServer.layout.xml"


		if(strcmp((char*)xml_str,"SelectServer/SelectServer.layout.xml")==0){
			int btn_win=*itr;
			__asm{
				
				mov eax,btn_win
				push eax
				mov eax,str_fun
				push eax
				mov esi,a
				mov ecx,esi
				
				call BottonCallAddress
			}
			CEGUI_WIN.clear();
			return 1;
		}
	}
	CEGUI_WIN.clear();
	return 0;
}
*/

char *getWindowString(int winObj){//��ȡ���ڶ��������һ���ַ���.
	char *str=0;
	__asm{
		mov edi,winObj
		lea ecx,dword ptr ds:[edi+0x20C]
		cmp dword ptr ds:[ecx+0x18],0x10
		jb short hi
		mov eax,dword ptr ds:[ecx+0x4]
		jmp hi2
hi:		lea eax,dword ptr ds:[ecx+0x4]
hi2:	mov str,eax
	}
	return str;
}

int UseButton(char *functionString,char *functionString_2){//ʹ�ð�ť�����۳ɹ���񶼻���ջ�ȡ���Ĵ���
	if(BottonCallAddress==0){
		int UI_CEGUI_Base=(int)GetModuleHandle("UI_CEGUI.dll");
		BottonCallAddress=UI_CEGUI_Base+0x36d10;//���ƫ��ֵ��Ϸÿ�θ���ҲҪ����Ҫ����
	}

	for(vector<int>::iterator itr = CEGUI_WIN.begin();itr!=CEGUI_WIN.end();++itr){//����֮ǰ��ȡ�����д��ڡ�
		if(*itr==0){
			continue;
		}
		int a=*(int*)(*itr+0xf0);
		if(a==0){
			continue;
		}
		int xml_str=*(int*)(a+0x28);
		if(myTestValue(xml_str)==0){
			continue;
		}
		if(strcmp(getWindowString(*itr),functionString_2)==0){//�Լ�������ַ����ͻ�ȡ���Ĵ��ڵ��ַ����Ƚ��Ƿ���ȣ���Ⱦ͵��ð�ťcall
			int btn_win=*itr;
			__asm{
				mov eax,btn_win
				push eax
				mov eax,functionString
				push eax
				mov esi,a
				mov ecx,esi
				call BottonCallAddress
			}
			CEGUI_WIN.clear();
			return 1;
		}
	}
	CEGUI_WIN.clear();
	return 0;
}