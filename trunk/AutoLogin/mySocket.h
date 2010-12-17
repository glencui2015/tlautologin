  #include "gameCall.h"
#include <windows.h>
#include <winsock2.h>
//#include <iostream.h>
#pragma comment(lib, "wsock32.lib")


#define CLIENT_EXIT_OK				0	//�ͻ��������˳�
#define CLIENT_DLL_REEOR			1	//����Windows socket dllʧ��
#define CLIENT_API_ERROR			2	//����Windows socket apiʧ��
#define MAX_NUM_BUF					0x1000	//����������󳤶�
#define	SERVERPORT					5555//������TCP�˿�


//����
char	bufRecv[MAX_NUM_BUF];			//��������
char	bufSend[MAX_NUM_BUF];			//д������
SOCKET	sHost;							//socket
BOOL	bConning;						//���ӷ�����״̬

//����
void	InitMember(void);				//��ʼ������
int		ExitClient(int nExit);			//�˳�

void	ShowErrorMsg(void);				//��ʾ������Ϣ






DWORD WINAPI MyRecvThread(
  LPVOID lpParameter   // thread data
  ){

	while(1){
		Sleep(500);
		memset(bufRecv,0,sizeof(bufRecv));
		int e=recv(sHost,bufRecv,sizeof(bufRecv),0);
		int a=WSAGetLastError();
		if(e==0||e==0xffffffff){
			closesocket(sHost);
			return 0;
		}
		if(a==WSAENETDOWN){
			closesocket(sHost);
			return 0;
		}
		if(a==WSAETIMEDOUT){
			closesocket(sHost);
			return 0;
		}
		if(WSAENOTCONN == a)
		{
			closesocket(sHost);
		//	ShowSocketMsg("The socket is not connected!");
			return 0;
		}
		if(WSAECONNRESET == a)
		{
			closesocket(sHost);
		//	ShowSocketMsg("The socket WSAECONNRESET");
			return 0;
		}
		if(0x100==*(int*)bufRecv){
			//˵���ҽӵ��İ������ִ����
			MessageBox(NULL, "��ʼ����", "", MB_OK);
			answerTheQuestion_Integer(bufRecv+4);
				
		}
	}

	return 0;
}

//������
int myInitSocket()
{

	//��ʼ������
	InitMember();

	WORD	wVersionRequested;		//Ӧ�ó�����ҪWindows sockets DLL�İ汾
	WSADATA	wsaData;				//Windows sockets DLL�汾��Ϣ
	int		retVal;					//����Windows sockets API����ֵ

	//��ʼ��Windows Sockets DLL
	wVersionRequested = MAKEWORD(1,1);	
	retVal = WSAStartup(wVersionRequested,(LPWSADATA)&wsaData);
	if ( 0 != retVal ) 
	{
		MessageBox(NULL, "Can not find a usable Windows Sockets dll!", "ERROR", MB_OK);
		return CLIENT_DLL_REEOR;
	}


	//����Windows socket
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == sHost)
	{
		ShowErrorMsg();			//��ʾ������Ϣ
		WSACleanup();			//�ͷ���Դ
		return CLIENT_API_ERROR;//�˳�
	}

	//׼�����ӷ�����
//	cout << "Client succeeded!" << endl;
//	cout<<"Be ready to connect to server..."<<endl;

	
	
	//��ȡ��������Ϣ
	LPHOSTENT hostEntry;
	char hostname[MAX_NUM_BUF];
	gethostname(hostname,MAX_NUM_BUF);			//��ȡ��������
	hostEntry = gethostbyname(hostname);		//��ȡ������Ϣ
	if(!hostEntry)
	{
		ShowErrorMsg();							//��ʾ������Ϣ
		return ExitClient(CLIENT_API_ERROR);	//�˳�
	}
	//����sockaddr_in
	SOCKADDR_IN addrServ;
	addrServ.sin_family = AF_INET;
	addrServ.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	addrServ.sin_port = htons(SERVERPORT);
	//���ӷ�����
	retVal=connect(sHost,(LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
	if(SOCKET_ERROR == retVal)
	{
		ShowErrorMsg();							//��ʾ������Ϣ
		return ExitClient(CLIENT_API_ERROR);	//�˳�
	}else{
		bConning = TRUE;						//���ӷ������ɹ�
	}     
	//���ӷ������ɹ�
//	cout<<"Connect successfully!"<<endl;

	HANDLE hThread1;
	hThread1=CreateThread(NULL,0,MyRecvThread,NULL,0,NULL);
	WaitForSingleObject(  hThread1, NULL  );
	CloseHandle(hThread1);

/*

	//���������������
	strcpy(bufSend, "Hello, Server!\n");
	retVal = send(sHost, bufSend, strlen(bufSend), 0);
	if (SOCKET_ERROR == retVal)
	{
		ShowErrorMsg();							//��ʾ������Ϣ
		return ExitClient(CLIENT_API_ERROR);	//�˳�
	}

	//�ӷ�������������
	if (!RecvLine(sHost, bufRecv))
	{
		ShowErrorMsg();							//��ʾ������Ϣ
		return ExitClient(CLIENT_API_ERROR);	//�˳�
	}
	//��ʾ��������Ӧ��
//	cout<<bufRecv<<endl;*/

	//�˳�
	return 1;//ExitClient(CLIENT_EXIT_OK);
}


/*
 *	��ʾ������Ϣ
 */
void	ShowErrorMsg(void)
{
	int nErrCode = WSAGetLastError();//��ȡ�������

	HLOCAL hlocal = NULL;  
	
	//��ȡ������ı��ַ���
	BOOL fOk = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL, nErrCode, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
		(PTSTR)&hlocal, 0, NULL);
	
	//��ʾ������Ϣ
	if (hlocal != NULL)
	{
		MessageBox(NULL, (char*)LocalLock(hlocal), "CLIENT ERROR", MB_OK);	
		LocalFree(hlocal);
	}
}


/*
 *	��ʼ����Ա����
 */
void	InitMember(void)
{
	//��ʼ������д������
	memset(bufRecv, 0, MAX_NUM_BUF);
	memset(bufSend, 0, MAX_NUM_BUF);
	//��ʼ��
	sHost = INVALID_SOCKET;
	//û������״̬
	bConning = FALSE;
}

/*
 *	�˳�
 */
int		ExitClient(int nExit)
{
	closesocket(sHost);		//�ر��׽���
	WSACleanup();			//ж��Windows sockets DLL �����ڴ�

		//��ʾ�˳���Ϣ
//	cout << "Client exiting..." << endl;
	Sleep(20000);
	return nExit;	//�˳�
}