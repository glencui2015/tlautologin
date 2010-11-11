// ClassTupianDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClassTupian.h"
#include "ClassTupianDlg.h"
#include "DealPic.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CClassTupianDlg dialog

CClassTupianDlg::CClassTupianDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClassTupianDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClassTupianDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClassTupianDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClassTupianDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClassTupianDlg, CDialog)
	//{{AFX_MSG_MAP(CClassTupianDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassTupianDlg message handlers

BOOL CClassTupianDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClassTupianDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClassTupianDlg::OnPaint() 
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
HCURSOR CClassTupianDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
char *pDate =      "\x00\x3F\xFF\xFF\xFF\x44\xE3\xB0\x00\x40\x00\x00\x3F\xD8\x00\xE0"
					"\x00\x3F\xFF\xFF\xFF\xFF\xF4\xFA\x00\x20\x00\x18\xC7\xFC\x01\xF0"
					"\x02\xBA\xFF\xFF\xFF\xFF\xFD\xFF\x00\x08\x06\x0B\xE7\xFF\xF7\xF0"
					"\x07\xF0\x1F\xFF\xFF\xFF\xFF\xFF\x80\x00\x02\x07\xFF\xFF\xFF\xF0"
					"\x07\xE1\x63\xFF\xEF\xFF\xFF\xFF\xC1\x00\x02\x3F\xFF\xFD\xFF\xF0"
					"\x07\xE3\xF3\xFF\xFF\xFF\xFF\xFF\xE9\xB0\x4F\x3F\xFF\xFF\xFD\xF0"
					"\x07\xE6\xF9\xFF\xFF\xC3\xED\xFF\xDF\xF1\xBC\x7F\xFF\xFF\xFC\xFC"
					"\x07\xC7\x78\xFF\xFF\xC0\xEF\xFF\xDF\xFF\xBC\x7F\xFF\xFF\xFF\xF0"
					"\x07\xC7\xF8\xFF\xFF\x98\x1F\xFF\xFF\xFF\xF8\x7F\xFF\xFF\xFF\xF0"
					"\x07\xE3\xB9\xFF\xFF\x9F\x0F\xFF\x3F\xDF\xE0\x72\xFF\x3B\xFF\xF8"
					"\x07\xC1\x79\xFF\xEF\x3F\xC6\x7F\x7F\xFF\xC0\xF0\xBF\x7D\xC1\xFC"
					"\x05\xE6\xE1\xFD\xD7\x3F\xF7\xFF\xFF\xFF\xC8\xFF\xBF\xFF\xC0\x73"
					"\x00\xDE\xA3\xF8\xDE\x7F\xBF\xBF\xFF\xFF\x08\xFF\xFF\xFF\x8C\x00"
					"\x00\xFC\x07\xFC\x7E\x4F\xBF\xBF\xFF\xFE\x71\xFD\xFF\xFF\x9D\x8C"
					"\x01\xF0\x3F\xFC\x2A\x0F\xFF\xFF\xFF\xFC\x71\xFD\xFF\xFF\x9F\xF8"
					"\x03\xC4\x3F\xFE\x03\x53\xFB\x7F\xFF\xF8\xF1\xFF\xED\x7E\x3F\xF0"
					"\x03\x87\x1F\xFE\x05\x79\xFA\x1F\xFF\xF1\xF1\xFF\xC0\x27\x3F\xB0"
					"\x03\x07\x1F\xFE\x00\x98\x1C\x0F\xF7\xE5\xE3\xFF\x80\x03\x3F\x10"
					"\x07\x07\x9B\xFE\x00\x43\x08\x05\xFF\xC7\xE3\xFE\x00\x03\x26\x00"
					"\x07\x47\x8F\xFE\x10\x03\x00\x00\xFF\x03\xE3\xFC\x00\x01\xFF\x00"
					"\x03\x07\x1F\xFE\x38\x07\x80\x00\x7F\xC0\x03\xE8\x00\x03\x83\x00"
					"\x03\x03\x9F\xFC\x30\x07\x00\x10\x3E\xFC\x03\x40\x00\x81\x81\x80"
					"\x01\xC2\x9F\xFC\x70\x03\x00\x10\x14\x4F\x81\x80\x00\x01\x05\x80"
					"\x01\xC8\x3F\xF8\x66\x06\x00\x00\x00\x07\xC7\x00\x00\x00\x05\xC0"
					"\x20\x3F\x7F\xF0\x24\x06\x00\x00\x00\x00\x71\x00\x00\x0C\x01\xC0"
					"\x20\x0C\x7F\x60\x10\x1C\x80\x40\x00\x00\x71\x00\x00\x0C\x01\x80"
					"\x00\x00\x5F\x00\x18\x1C\x00\x40\x00\x00\x74\x00\x00\x18\x01\x80"
					"\x10\x00\x00\x00\x67\xF8\x00\x00\x00\x0F\xF6\x00\x00\x18\x01\x80"
					"\x08\x00\x00\x00\x01\xFC\x00\x30\x00\x07\xFA\x01\x00\x58\x07\x00"
					"\x00\x90\x00\x00\x00\x10\x00\x20\x00\x00\x7C\x74\x00\x18\x07\x80"
					"\xC0\x40\x00\x00\x00\x06\x00\x80\x18\x00\xC4\x10\x18\x04\x0F\x00"
					"\xC0\x00\x80\x00\x40\x06\x00\x80\x08\x00\x00\x00\x08\x07\x7E\x00"
					"\x02\x00\x00\x00\x00\x02\x60\x00\x00\x00\x08\x00\x00\x01\x98\x40"
					"\x00\x00\x00\x00\x00\x00\x10\x00\x00\x00\x00\x00\x00\x00\x18\x20"
					"\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x04\x00\x00"
					 "\x00\x13\x00\x00\x00\x00\x00\x00\x80\x00\x04\x00\x00\x06\x00\x00";
DealPic Dp;
void CClassTupianDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
	int dLen = 0x240;
	char c;
	int a = 128;
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	int k = 0;
	int ret = 0;
	while (i < dLen)
	{
		a = 128;
		c = pDate[i];
		for (k = 0;k < 8;k++)
		{
			if (!(a&c))
			{
				ret = x / 32;
				
				switch (ret)
				{
				case 0:
						Dp.B1[y][x%32] = !(a&c);
						 break;
				case 1:
						 Dp.B2[y][x%32] = !(a&c);
						 break;
				case 2:
						 Dp.B3[y][x%32] = !(a&c);
						 break;
				case 3:
						 Dp.B4[y][x%32] = !(a&c);
						 break;
				Default:
						 break;
				}
					
			}
			if (x == 127)
			{
				x = 0;
				y++;
			}
			else
			{
				x++;
			}
			a = a >> 1;
		}
		i++;
	}
}

void CClassTupianDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	int x,y;
	x = y = 0;
	int up = 3;
	while (y < 36)
	{
		while (x < 32)
		{
			if (Dp.B2[y][x])
			{
				SetPixel(::GetDC(this->m_hWnd),x*up,y*up,RGB(0,0,0));
			}
			x++;
		}
		x = 0;
		y++;
	}
	
}

void CClassTupianDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	int x , y ;
	x = y = 0;
	BOOL before;

	while (y < 36)
	{
		while (x < 32)
		{
			before = Dp.B2[y][x];
			if (before == Dp.B2[y-1][x-1] && before == Dp.B2[y-1][x] && before == Dp.B2[y-1][x+1] && before == Dp.B2[y][x-1] && 
		before == Dp.B2[y][x+1] && before == Dp.B2[y+1][x-1] && before == Dp.B2[y+1][x] && before == Dp.B2[y+1][x+1])
			{
				Dp.TMP[y][x] = FALSE;
			}
			else
			{
				Dp.TMP[y][x] = TRUE;
			}
			x++;
		}
		x = 0;
		y++;
	}
	x = y = 0;
	while (y < 36)
	{
		while (x < 32)
		{
			Dp.B2[y][x] = Dp.TMP[y][x];
			x++;
		}
		x = 0;
		y++;
	}
	//下面是去掉数字内部的干扰点
	x = y = 0;
	while (y < 36)
	{
		while (x < 32)
		{
			if (Dp.B2[y-1][x-1] && Dp.B2[y-1][x] && Dp.B2[y-1][x+1] &&
				Dp.B2[y][x-1]   &&!Dp.B2[y][x]   && Dp.B2[y][x+1]   && 
				Dp.B2[y+1][x-1] && Dp.B2[y+1][x] && Dp.B2[y+1][x+1])
			{
				Dp.B2[y][x]  = true;
			}
			if (Dp.B2[y-1][x-1] && Dp.B2[y-1][x] && Dp.B2[y-1][x+1] && Dp.B2[y-1][x+2] &&
				Dp.B2[y][x-1]   &&!Dp.B2[y][x]   &&!Dp.B2[y][x+1]   && Dp.B2[y][x+2]   &&
				Dp.B2[y+1][x-1] && Dp.B2[y+1][x] && Dp.B2[y+1][x+1] && Dp.B2[y+1][x+2])
			{
				Dp.B2[y][x] = true;
				Dp.B2[y][x+1] = true;
			}
			if (Dp.B2[y-1][x-1] && Dp.B2[y-1][x] && Dp.B2[y-1][x+1] &&
				Dp.B2[y][x-1]   &&!Dp.B2[y][x]   && Dp.B2[y][x+1]   &&
				Dp.B2[y+1][x-1] &&!Dp.B2[y+1][x] && Dp.B2[y+1][x+1] &&
				Dp.B2[y+2][x-1] && Dp.B2[y+2][x] && Dp.B2[y+2][x+1])
			{
				Dp.B2[y][x] = true;
				Dp.B2[y+1][x] = true;
			}
			if (Dp.B2[y-1][x-1] && Dp.B2[y-1][x] && Dp.B2[y-1][x+1] && Dp.B2[y-1][x+2] &&
				Dp.B2[y][x-1]   &&!Dp.B2[y][x]   &&!Dp.B2[y][x+1]   && Dp.B2[y][x+2]   &&
				Dp.B2[y+1][x-1] &&!Dp.B2[y+1][x] &&!Dp.B2[y+1][x+1] && Dp.B2[y+1][x+2] &&
				Dp.B2[y+2][x-1] && Dp.B2[y+2][x] && Dp.B2[y+2][x+1] && Dp.B2[y+2][x+2])
			{
				Dp.B2[y][x] = true;
				Dp.B2[y][x+1] = true;
				Dp.B2[y+1][x] = true;
				Dp.B2[y+1][x+1] = true;
			}
			x++;
		}
		x = 0;
		y++;
	}
	//一下进行线条缩小
	x = y = 0;
	while (y < 36)      //首先要对TMP数组进行清空
	{
		while (x < 32)
		{
			Dp.TMP[y][x] = false;
			x++;
		}
		x = 0;
		y++;
	}

	//以上是进行 二值话 把数值的线条弄粗 下面进行 数字比对
// 	x = y = 0;
// 	while (y < 36)
// 	{
// 		while (x < 32)
// 		{
// 			before = Dp.B2[y][x];
// 			
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
}
