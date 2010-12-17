 // AutoLogin.cpp : Defines the entry point for the DLL application.
//
//取当前地址的 规则： db [[76317c]+3a38]+68
#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "CEGUI_Call.h"
#include "myHook.h"
//HWND在  mov dword ptr ds:[6B3650],esi
//"LogOn_LogonID_Active();"         鼠标点击账号输入栏

// "LogOn_PassWord_MouseEnter();"       鼠标点击密码输入栏

// "LogOn_CheckAccount();"         按"进入游戏"


//"SelectRole_Clicked(1);"          "SelectRole_TargetInfo_Button2" 选择角色


// "SelectRole_EnterGame();"         "SelectRole_Play"    确定进入游戏。
typedef IN;
typedef OUT;
typedef struct Task{
	char UserName[100];      //账号
	char PassWord[100];		//账号的密码
	char Login_Area[100];		//账号的所在的大区
	char Login_Server[100];		//对应大区的所在服务器
	int WebSite;				//用来存放用户名的注册网址 比如@changyou.cn 就是1
	int Level;					//人物等级
	int NoId;					//在所属的账号的第几个人物
	char Properties;			//人物的功能  是用来打图还是仓库号的（Att为打图 Ware：仓库）
	int Remaining;				//剩余的仓库格数
	int Number;					//拥有多少张宝图
	int Gold;					//拥有多少金币
	int iTask; // 用来记录任务的类型，1。升级 2。打图 3。创建账号
}Task,*pTask;
Task MyTask;
HWND gameHwnd=0;


void selectServer(char *Login_Area,char *Login_Server,int Account_MailIndex){//选择大区，服务器，邮箱名。(以修改配置文件的方法)
	string str;
	char aaa[0x30]={0};
	char bbb[0x30]={0};
	DWORD dwWrite;
	HANDLE  hFile=CreateFile("D:\\TLBB\\Accounts\\System.cfg",GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
	str.append("[Variable]");
	str.append("\r\n");
	
	str.append("Login_Area=");//选区
	str.append(Login_Area);
	str.append("\r\n");
	
	str.append("Login_Server=");//选服务器
	str.append(Login_Server);
	str.append("\r\n");
	
	str.append("Account_MailIndex=");//选账号名后的邮箱名。
	str.append(itoa(Account_MailIndex,aaa,10));
	str.append("\r\n");
	
	str.append("View_MaxWindow=");//选账号名后的邮箱名。
	str.append("0");
	str.append("\r\n");
	
	WriteFile(hFile,str.c_str(),str.length(),&dwWrite,NULL);
	
	CloseHandle(hFile);
}


void inputID(HWND hwnd,char *ID,char *passWord){//输入账号密码
	int i=0;

	for(i=0;i<strlen(ID);i++){//输入账号
		SendMessage(hwnd, WM_IME_CHAR,(WPARAM)ID[i],1);
	}
	
	SendMessage(hwnd, WM_KEYDOWN,VK_RETURN,0);//按确定换行

	for(i=0;i<strlen(passWord);i++){//输入密码
		SendMessage(hwnd, WM_IME_CHAR,(WPARAM)passWord[i],1);
	}
}

void UpDateControl(void)//这个函数用来向控制端 报告任务的完成 和更新人物信息
{

}
void GetTAsk(void)
{
// 	char ts[100];
// 	::GetCurrentDirectory(MAX_PATH,ts);
	memcpy(MyTask.UserName,"ecvg_cwej_bbtn",15);
	MyTask.WebSite = 2;
	memcpy(MyTask.PassWord,"132456789",9);
	memcpy(MyTask.Login_Area,"网通-华北网通一区",sizeof("网通-华北网通一区"));
	memcpy(MyTask.Login_Server,"香露茶",sizeof("香露茶"));
	MyTask.Level = 28;
	MyTask.NoId = 2;
	MyTask.Number = 0;
	MyTask.Gold = 0;
	MyTask.iTask = 1;
}
void InitHuodong()
{
	while(1){
		Sleep(3000);
		//先看看有没加载UI_CEGUI.dll
		int UI_CEGUI_Base=(int)GetModuleHandle("UI_CEGUI.dll");
		if(UI_CEGUI_Base==0){
			continue;
		}
		int CEGUIBase_Base=(int)GetModuleHandle("CEGUIBase.dll");
		if(CEGUIBase_Base==0){
			continue;
		}
		
		if(0==SearchAllCEGUI_Window()){
			continue;//获取所有可视的CEGUI窗口。
		}
		//	win_next_botton();//下一步。
		Sleep(100);		
		if (UseButton("HuoDongRiCheng_next_click();","HuoDongRiCheng_next") == 0)
		{
			continue;
		}
		else
		{
			gameHwnd=FindWindow(NULL,"《天龙八部2》 2.20.1105");
			SetWindowText(gameHwnd,"登陆界面初始化");
			break;
		}
		
		
		break;
}
}
void InitLogin(void)
{
	char RoleNumber[100] = {0};
	while (1)
	{
		Sleep(1000);
		if(0==SearchAllCEGUI_Window()){
			continue;//获取所有可视的CEGUI窗口。
		}
		if(UseButton("SelectServer_SelectOk();","SelectServer_Accept")){
			Sleep(1000);
			inputID(gameHwnd,MyTask.UserName,MyTask.PassWord);//输入账号密码
			Sleep(1000);
			
			SearchAllCEGUI_Window();
			UseButton("LogOn_CheckAccount();","LogOn_LogOnGame");
			Sleep(5000);
			SearchAllCEGUI_Window();
			if(UseButton("FangChenMi_Accept_Clicked();","FangChenMi_Accept")==0){//密码保护的那个按钮
				MessageBox(0,"没调用成功","",0);
			}
			Sleep(5000);
			SearchAllCEGUI_Window();
			sprintf(RoleNumber,"SelectRole_Clicked(%d);",MyTask.NoId);
			UseButton(RoleNumber, "SelectRole_TargetInfo_Button2" );//选择第二个人物。
			
			Sleep(2000);
			SearchAllCEGUI_Window();
			UseButton("SelectRole_EnterGame();" , "SelectRole_Play");
			//一下还有输入验证码 和进入游戏 还没有写完 这个函数



			SetWindowText(gameHwnd,"登陆成功");
			break;
		}
	}
}
void ShowAllCEGUI_Window()
{
	if(BottonCallAddress==0){
		int UI_CEGUI_Base=(int)GetModuleHandle("UI_CEGUI.dll");
		BottonCallAddress=UI_CEGUI_Base+0x2E0F0;//这个偏移值游戏每次更新也要跟着要更新
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

		MessageBox(0,getWindowString(*itr),"",0);
	}
	CEGUI_WIN.clear();
}
BOOL CreateRole(int RoleNumber)
{
	MessageBox(0,"创建任务","",0);
	while (1)
	{
		Sleep(1000);
		if(0==SearchAllCEGUI_Window()){
			continue;//获取所有可视的CEGUI窗口。
		}
		if(UseButton("SelectServer_SelectOk();","SelectServer_Accept")){
			Sleep(1000);
				MessageBox(0,"输入账号","",0);
			inputID(gameHwnd,MyTask.UserName,MyTask.PassWord);//输入账号密码
			Sleep(1000);
			
			SearchAllCEGUI_Window();
			UseButton("LogOn_CheckAccount();","LogOn_LogOnGame");
			Sleep(5000);
			SearchAllCEGUI_Window();
			if(UseButton("FangChenMi_Accept_Clicked();","FangChenMi_Accept")==0){//密码保护的那个按钮
				MessageBox(0,"没调用成功","",0);
			}
			Sleep(5000);
			SearchAllCEGUI_Window();
			UseButton("SelectRole_Clicked(1);", "SelectRole_TargetInfo_Button2" );//选择第二个人物。

			ShowAllCEGUI_Window();
 			Sleep(2000);
			SearchAllCEGUI_Window();
 			UseButton("SelectRole_CreateRole();" , "SelectRole_Create");
			//ShowAllCEGUI_Window();
			break;
		}
	}
	return true;
}
void EntCreateRole(void)
{
	int RoleNumber = 1;
	while (RoleNumber < 4)
	{
		switch (RoleNumber)
		{
		case 1:
			if (CreateRole(1))
			{
				UpDateControl();
			}
			break;
		case 2:
			if(CreateRole(2))
			{
				UpDateControl();
			}
			break;
		case 3:
			if(CreateRole(3))
			{
				UpDateControl();
			}
			
			break;
		}
	}
	return ;
}

// BOOL RoleUp()
// {
// 
// }
DWORD WINAPI initWindow(
  LPVOID lpParameter   // thread data
  ){

	InitHuodong(); //跳过今日活动的界面
	while (1)  //这一层循环是 任务循环 没执行一次任务 就循环一次
	{
		GetTAsk();
		//selectServer(MyTask.Login_Area,MyTask.Login_Server,MyTask.WebSite);
		//由于进入游戏以后 在修改配置文件进行选区就无效了，占时的方法是 一个游戏客户端 做的每次都是在一个区下完成的
		switch (MyTask.iTask) //判断任务的类型，1。升级 2。打图 3。创建账号
		{	
		case 1:		//升级
			InitLogin();
			//RoleUp();
			break;
		case 2:		//打图
			break;
		case 3:		//创建账号
			EntCreateRole();
			break;
		}
	}
	return 0;
}


BOOL APIENTRY
DllMain (HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    { 
  //把互斥体打上补丁。这就可以多开了。/////////////////////////////////////////
//	  int mutexAddress=(int)GetProcAddress (GetModuleHandle ("Kernel32"), "CreateMutexA");//获取互斥体函数的地址
int MBWAddress=(int)GetProcAddress (GetModuleHandle ("USER32"), "MessageBoxW");
//	  char mypatch[]={0xB8 ,0x10 ,0x00 ,0x00 ,0x00 ,0xC2 ,0x0C ,0x00};//补丁数组
char mypatch[]={0xB8 ,0x82 ,0x2E ,0x40 ,0x00 ,0xC7 ,0x00 ,0x90 ,0x90 ,0x90 ,0x90 ,0x66 ,0xC7 ,0x40 ,0x04 ,0x90 ,0x90 ,0xC2 ,0x10 ,0x00};
		DWORD oldProtect=0;
		VirtualProtect(
		  (void*)MBWAddress,       // region of committed pages
		  sizeof(mypatch),          // size of the region
		  PAGE_EXECUTE_READWRITE,     // desired access protection
		  &oldProtect   // old protection
		);//修改页属性，让我可以修改其中的代码，这样才可以打补丁
		memcpy((void*)MBWAddress,mypatch,sizeof(mypatch));//打补丁

		VirtualProtect(
		  (void*)MBWAddress,       // region of committed pages
		  sizeof(mypatch),          // size of the region
		  oldProtect,     // desired access protection
		  &oldProtect   // old protection
		);//恢复页属性
		char asas[100];

	//	hookRecv(); // 采用打补丁的方式 并非hook 这样 就能实现客户端对自己的精确控制了


		HANDLE hThread1;
		hThread1=CreateThread(NULL,0,initWindow,NULL,0,NULL);
		CloseHandle(hThread1);
    }
  return true;
}
