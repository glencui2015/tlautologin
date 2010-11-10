// WGClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WGClient.h"
#include "WGClientDlg.h"

#include <stdio.h>
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef __CONFIG_H__
#define __CONFIG_H__

#define INI_NAME "gsb-zh_cn.ini"
#define DLL_NAME "AutoLogin.dll"
#endif


int ClientNumber = 1;   //在外挂目录下 config.ini指定 在这里设置无效
int ClientNUmbered = 0;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWGClientDlg dialog

CWGClientDlg::CWGClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWGClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWGClientDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWGClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWGClientDlg)
	DDX_Control(pDX, IDC_EDIT3, m_MEMP);
	DDX_Control(pDX, IDC_EDIT1, m_CPUP);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWGClientDlg, CDialog)
	//{{AFX_MSG_MAP(CWGClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

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
static void CALLBACK  QiDongClient(          HWND hwnd,
						UINT uMsg,
						UINT_PTR idEvent,
						DWORD dwTime
						)
{

	if (ClientNUmbered < ClientNumber)
	{
		Sleep(1000);
		selectServer("网通-华北网通一区","香露茶",1);//一开始就修改配置文件。
		__asm{
			mov eax,eax
		}
		// TODO: Add your control notification handler code here
		STARTUPINFO sif;
		PROCESS_INFORMATION pi;
		ZeroMemory (&sif, sizeof (STARTUPINFO));
		ZeroMemory (&pi, sizeof (PROCESS_INFORMATION));
		sif.cb = sizeof (STARTUPINFO);
		
		char exeName[MAX_PATH];
		char pathName[MAX_PATH];
		char pathNameAndDllName[MAX_PATH];
		// GetModuleFileName (NULL, pathNameAndDllName, MAX_PATH);//获得当前进程的路径+名字
		
		
		// *(strrchr (pathNameAndDllName, '\\') + 1) = '\0';//把刚刚获取到的字符串截断，变成当前路径
		
		
		if (!CreateProcess (NULL,     // If No module name (then use command line).
			"D:\\TLBB\\Bin\\Game.exe -fl",  // Command line.
			NULL,     // Process handle not inheritable.
			NULL,     // Thread handle not inheritable.
			FALSE,    // Set handle inheritance to FALSE.
			CREATE_SUSPENDED | CREATE_DEFAULT_ERROR_MODE,     //CREATE_DEFAULT_ERROR_MODE,//DEBUG_ONLY_THIS_PROCESS,    // creation flags.
			0,     // Use parent's environment block.
			"D:\\TLBB\\Bin\\",     // Use parent's starting directory.
			&sif,     // Pointer to STARTUPINFO structure.
			&pi))     // Pointer to PROCESS_INFORMATION structure.
		{
			::MessageBox (0, "Unexpected load error", "Create Process Failed", MB_OK + MB_ICONERROR);
			return ;
		}
		
		char dllstr[]="E:\\天龙外挂\\AutoLogin\\Release\\AutoLogin.dll";//注入游戏的dll名
		// char *dllName = DLL_NAME;
		int dllNameSize = strlen (dllstr) + 1;
		
		
		lstrcat (pathNameAndDllName, DLL_NAME);//把AutoLogin.dll加在当前路径
		
		char *dllNameP = (char *) VirtualAllocEx (pi.hProcess, NULL, dllNameSize, MEM_COMMIT,
			PAGE_READWRITE);//在游戏中申请一块内存
		WriteProcessMemory (pi.hProcess, dllNameP, (void *) dllstr, dllNameSize, NULL);//把dll名字写进去
		
		PTHREAD_START_ROUTINE LoadLibAddress = (PTHREAD_START_ROUTINE)
			GetProcAddress (GetModuleHandle ("Kernel32"), "LoadLibraryA");//获取LoadLibrary的地址
		
		HANDLE thread = CreateRemoteThread (pi.hProcess, NULL, 0, LoadLibAddress, dllNameP, 0, NULL);//注入远程线程
		
		WaitForSingleObject (thread, INFINITE);
		
		VirtualFreeEx (pi.hProcess, dllNameP, dllNameSize, MEM_DECOMMIT);
		
		ResumeThread (pi.hThread);//恢复线程

		ClientNUmbered++;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWGClientDlg message handlers
BOOL CWGClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CHAR FilePath[255]; 
    GetModuleFileName(NULL,FilePath,255); 
    (strrchr(FilePath,'\\'))[1] = 0; 
    strcat(FilePath,"config.ini");
	char content[20] = {0};
	GetPrivateProfileString("ClientNumber", "NUM",NULL,content,20,FilePath); //读取指定的启动客户端的数量
	ClientNumber = atoi(content);
	SetTimer(123,1000/*300000*/,(TIMERPROC)QiDongClient);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWGClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWGClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWGClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
