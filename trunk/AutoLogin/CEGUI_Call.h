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
	return	(int)GetModuleHandle("CEGUIBase.dll");//获取模块基址
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

int getwin(int sheet){//递归遍历所有"可视"窗口
	//先看看有当前的窗口所拥有的子窗口,
	int local_sheet=sheet;
	int child=*(int*)(local_sheet+0x2c);    //数组的开始地址
	int end=*(int*)(local_sheet+0x30);		//数组的结束地址
	if(child==end){
		return 0;
	}
//获取数组中的窗口对象，
	for(int i=child;i!=end;i+=4){
		int winobj=*(int*)i;
		if(winobj==0){
			continue;
		}
		char isVisible=*(char*)(winobj+0x129);
		if(isVisible==0){//看看窗口是否可见，不可见就continue
			continue;
		}else{//递归看看还有没子窗口
			CEGUI_WIN.push_back(winobj);
			int win2=getwin(winobj);//有子窗口就返回。
	//		if(win2){	
	//			return win2;
	//		}
		}

	}
	return 0;
}


int SearchAllCEGUI_Window(){//获取所有CEGUI可视窗口

	if(CEGUIBase_Handle==0){
		CEGUIBase_Handle=GetCEGUI();//看看CEGUIBase.dll加载了进内存没。
	}

	if(CEGUIBase_Handle==0){//看看CEGUIBase.dll加载了进内存没。
		return 0;
	}

	typedef int (*ADDPROC)();
	ADDPROC getSingleton = (ADDPROC)(0x492e0+CEGUIBase_Handle);//这个每次更新都要更新
//mov eax,dword ptr ds:[CEGUI::Singleton<CEGUI::System>::m>
	int WinBase=getSingleton();//获取窗口基类。
	if(WinBase==0){
		return 0;
	}

	char aaa[30]={0};
//获取可以活动的窗口
	int d_activeSheet=*(int*)(WinBase+0x2c);
/////接下来要递归遍历所有"可视"窗口了。
	if(myTestValue(d_activeSheet)==0){
		return 0;
	}
	getwin(d_activeSheet);//递归遍历窗口，保存在CEGUI_WIN这个vector中
/*	for(vector<int>::iterator itr = CEGUI_WIN.begin();itr!=CEGUI_WIN.end();++itr){
		memset(aaa,0,sizeof(aaa));
	}*/
	return 1;
}
/*
///////////
//使用窗口按钮。
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

char *getWindowString(int winObj){//获取窗口对象的另外一个字符串.
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

int UseButton(char *functionString,char *functionString_2){//使用按钮。无论成功与否都会清空获取到的窗口
	if(BottonCallAddress==0){
		int UI_CEGUI_Base=(int)GetModuleHandle("UI_CEGUI.dll");
		BottonCallAddress=UI_CEGUI_Base+0x36d10;//这个偏移值游戏每次更新也要跟着要更新
	}

	for(vector<int>::iterator itr = CEGUI_WIN.begin();itr!=CEGUI_WIN.end();++itr){//遍历之前获取的所有窗口。
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
		if(strcmp(getWindowString(*itr),functionString_2)==0){//自己输入的字符串和获取到的窗口的字符串比较是否相等，相等就调用按钮call
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