 // AutoLogin.cpp : Defines the entry point for the DLL application.
//
//ȡ��ǰ��ַ�� ���� db [[76317c]+3a38]+68
#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "CEGUI_Call.h"
#include "myHook.h"
//HWND��  mov dword ptr ds:[6B3650],esi
//"LogOn_LogonID_Active();"         ������˺�������

// "LogOn_PassWord_MouseEnter();"       ���������������

// "LogOn_CheckAccount();"         ��"������Ϸ"


//"SelectRole_Clicked(1);"          "SelectRole_TargetInfo_Button2" ѡ���ɫ


// "SelectRole_EnterGame();"         "SelectRole_Play"    ȷ��������Ϸ��
typedef IN;
typedef OUT;
typedef struct Task{
	char UserName[100];      //�˺�
	char PassWord[100];		//�˺ŵ�����
	char Login_Area[100];		//�˺ŵ����ڵĴ���
	char Login_Server[100];		//��Ӧ���������ڷ�����
	int WebSite;				//��������û�����ע����ַ ����@changyou.cn ����1
	int Level;					//����ȼ�
	int NoId;					//���������˺ŵĵڼ�������
	char Properties;			//����Ĺ���  ��������ͼ���ǲֿ�ŵģ�AttΪ��ͼ Ware���ֿ⣩
	int Remaining;				//ʣ��Ĳֿ����
	int Number;					//ӵ�ж����ű�ͼ
	int Gold;					//ӵ�ж��ٽ��
	int iTask; // ������¼��������ͣ�1������ 2����ͼ 3�������˺�
}Task,*pTask;
Task MyTask;
HWND gameHwnd=0;


void selectServer(char *Login_Area,char *Login_Server,int Account_MailIndex){//ѡ�����������������������(���޸������ļ��ķ���)
	string str;
	char aaa[0x30]={0};
	char bbb[0x30]={0};
	DWORD dwWrite;
	HANDLE  hFile=CreateFile("D:\\TLBB\\Accounts\\System.cfg",GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
	str.append("[Variable]");
	str.append("\r\n");
	
	str.append("Login_Area=");//ѡ��
	str.append(Login_Area);
	str.append("\r\n");
	
	str.append("Login_Server=");//ѡ������
	str.append(Login_Server);
	str.append("\r\n");
	
	str.append("Account_MailIndex=");//ѡ�˺��������������
	str.append(itoa(Account_MailIndex,aaa,10));
	str.append("\r\n");
	
	str.append("View_MaxWindow=");//ѡ�˺��������������
	str.append("0");
	str.append("\r\n");
	
	WriteFile(hFile,str.c_str(),str.length(),&dwWrite,NULL);
	
	CloseHandle(hFile);
}


void inputID(HWND hwnd,char *ID,char *passWord){//�����˺�����
	int i=0;

	for(i=0;i<strlen(ID);i++){//�����˺�
		SendMessage(hwnd, WM_IME_CHAR,(WPARAM)ID[i],1);
	}
	
	SendMessage(hwnd, WM_KEYDOWN,VK_RETURN,0);//��ȷ������

	for(i=0;i<strlen(passWord);i++){//��������
		SendMessage(hwnd, WM_IME_CHAR,(WPARAM)passWord[i],1);
	}
}

void UpDateControl(void)//���������������ƶ� ������������ �͸���������Ϣ
{

}
void GetTAsk(void)
{
// 	char ts[100];
// 	::GetCurrentDirectory(MAX_PATH,ts);
	memcpy(MyTask.UserName,"ecvg_cwej_bbtn",15);
	MyTask.WebSite = 2;
	memcpy(MyTask.PassWord,"132456789",9);
	memcpy(MyTask.Login_Area,"��ͨ-������ͨһ��",sizeof("��ͨ-������ͨһ��"));
	memcpy(MyTask.Login_Server,"��¶��",sizeof("��¶��"));
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
		//�ȿ�����û����UI_CEGUI.dll
		int UI_CEGUI_Base=(int)GetModuleHandle("UI_CEGUI.dll");
		if(UI_CEGUI_Base==0){
			continue;
		}
		int CEGUIBase_Base=(int)GetModuleHandle("CEGUIBase.dll");
		if(CEGUIBase_Base==0){
			continue;
		}
		
		if(0==SearchAllCEGUI_Window()){
			continue;//��ȡ���п��ӵ�CEGUI���ڡ�
		}
		//	win_next_botton();//��һ����
		Sleep(100);		
		if (UseButton("HuoDongRiCheng_next_click();","HuoDongRiCheng_next") == 0)
		{
			continue;
		}
		else
		{
			gameHwnd=FindWindow(NULL,"�������˲�2�� 2.20.1105");
			SetWindowText(gameHwnd,"��½�����ʼ��");
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
			continue;//��ȡ���п��ӵ�CEGUI���ڡ�
		}
		if(UseButton("SelectServer_SelectOk();","SelectServer_Accept")){
			Sleep(1000);
			inputID(gameHwnd,MyTask.UserName,MyTask.PassWord);//�����˺�����
			Sleep(1000);
			
			SearchAllCEGUI_Window();
			UseButton("LogOn_CheckAccount();","LogOn_LogOnGame");
			Sleep(5000);
			SearchAllCEGUI_Window();
			if(UseButton("FangChenMi_Accept_Clicked();","FangChenMi_Accept")==0){//���뱣�����Ǹ���ť
				MessageBox(0,"û���óɹ�","",0);
			}
			Sleep(5000);
			SearchAllCEGUI_Window();
			sprintf(RoleNumber,"SelectRole_Clicked(%d);",MyTask.NoId);
			UseButton(RoleNumber, "SelectRole_TargetInfo_Button2" );//ѡ��ڶ������
			
			Sleep(2000);
			SearchAllCEGUI_Window();
			UseButton("SelectRole_EnterGame();" , "SelectRole_Play");
			//һ�»���������֤�� �ͽ�����Ϸ ��û��д�� �������



			SetWindowText(gameHwnd,"��½�ɹ�");
			break;
		}
	}
}
void ShowAllCEGUI_Window()
{
	if(BottonCallAddress==0){
		int UI_CEGUI_Base=(int)GetModuleHandle("UI_CEGUI.dll");
		BottonCallAddress=UI_CEGUI_Base+0x2E0F0;//���ƫ��ֵ��Ϸÿ�θ���ҲҪ����Ҫ����
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

		MessageBox(0,getWindowString(*itr),"",0);
	}
	CEGUI_WIN.clear();
}
BOOL CreateRole(int RoleNumber)
{
	MessageBox(0,"��������","",0);
	while (1)
	{
		Sleep(1000);
		if(0==SearchAllCEGUI_Window()){
			continue;//��ȡ���п��ӵ�CEGUI���ڡ�
		}
		if(UseButton("SelectServer_SelectOk();","SelectServer_Accept")){
			Sleep(1000);
				MessageBox(0,"�����˺�","",0);
			inputID(gameHwnd,MyTask.UserName,MyTask.PassWord);//�����˺�����
			Sleep(1000);
			
			SearchAllCEGUI_Window();
			UseButton("LogOn_CheckAccount();","LogOn_LogOnGame");
			Sleep(5000);
			SearchAllCEGUI_Window();
			if(UseButton("FangChenMi_Accept_Clicked();","FangChenMi_Accept")==0){//���뱣�����Ǹ���ť
				MessageBox(0,"û���óɹ�","",0);
			}
			Sleep(5000);
			SearchAllCEGUI_Window();
			UseButton("SelectRole_Clicked(1);", "SelectRole_TargetInfo_Button2" );//ѡ��ڶ������

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

	InitHuodong(); //�������ջ�Ľ���
	while (1)  //��һ��ѭ���� ����ѭ�� ûִ��һ������ ��ѭ��һ��
	{
		GetTAsk();
		//selectServer(MyTask.Login_Area,MyTask.Login_Server,MyTask.WebSite);
		//���ڽ�����Ϸ�Ժ� ���޸������ļ�����ѡ������Ч�ˣ�ռʱ�ķ����� һ����Ϸ�ͻ��� ����ÿ�ζ�����һ��������ɵ�
		switch (MyTask.iTask) //�ж���������ͣ�1������ 2����ͼ 3�������˺�
		{	
		case 1:		//����
			InitLogin();
			//RoleUp();
			break;
		case 2:		//��ͼ
			break;
		case 3:		//�����˺�
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
  //�ѻ�������ϲ�������Ϳ��Զ࿪�ˡ�/////////////////////////////////////////
//	  int mutexAddress=(int)GetProcAddress (GetModuleHandle ("Kernel32"), "CreateMutexA");//��ȡ�����庯���ĵ�ַ
int MBWAddress=(int)GetProcAddress (GetModuleHandle ("USER32"), "MessageBoxW");
//	  char mypatch[]={0xB8 ,0x10 ,0x00 ,0x00 ,0x00 ,0xC2 ,0x0C ,0x00};//��������
char mypatch[]={0xB8 ,0x82 ,0x2E ,0x40 ,0x00 ,0xC7 ,0x00 ,0x90 ,0x90 ,0x90 ,0x90 ,0x66 ,0xC7 ,0x40 ,0x04 ,0x90 ,0x90 ,0xC2 ,0x10 ,0x00};
		DWORD oldProtect=0;
		VirtualProtect(
		  (void*)MBWAddress,       // region of committed pages
		  sizeof(mypatch),          // size of the region
		  PAGE_EXECUTE_READWRITE,     // desired access protection
		  &oldProtect   // old protection
		);//�޸�ҳ���ԣ����ҿ����޸����еĴ��룬�����ſ��Դ򲹶�
		memcpy((void*)MBWAddress,mypatch,sizeof(mypatch));//�򲹶�

		VirtualProtect(
		  (void*)MBWAddress,       // region of committed pages
		  sizeof(mypatch),          // size of the region
		  oldProtect,     // desired access protection
		  &oldProtect   // old protection
		);//�ָ�ҳ����
		char asas[100];

	//	hookRecv(); // ���ô򲹶��ķ�ʽ ����hook ���� ����ʵ�ֿͻ��˶��Լ��ľ�ȷ������


		HANDLE hThread1;
		hThread1=CreateThread(NULL,0,initWindow,NULL,0,NULL);
		CloseHandle(hThread1);
    }
  return true;
}
