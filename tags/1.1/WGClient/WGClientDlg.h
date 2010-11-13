// WGClientDlg.h : header file
//

#if !defined(AFX_WGCLIENTDLG_H__A256BB87_0815_4B4B_8CF1_AEA0818F3373__INCLUDED_)
#define AFX_WGCLIENTDLG_H__A256BB87_0815_4B4B_8CF1_AEA0818F3373__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWGClientDlg dialog

class CWGClientDlg : public CDialog
{
// Construction
public:
	CWGClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWGClientDlg)
	enum { IDD = IDD_WGCLIENT_DIALOG };
	CEdit	m_MEMP;
	CEdit	m_CPUP;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWGClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWGClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WGCLIENTDLG_H__A256BB87_0815_4B4B_8CF1_AEA0818F3373__INCLUDED_)
