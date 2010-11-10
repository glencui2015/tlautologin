// ClassTupianDlg.h : header file
//

#if !defined(AFX_CLASSTUPIANDLG_H__BA9B1024_F803_4BB6_BF29_179D08A37D4D__INCLUDED_)
#define AFX_CLASSTUPIANDLG_H__BA9B1024_F803_4BB6_BF29_179D08A37D4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClassTupianDlg dialog

class CClassTupianDlg : public CDialog
{
// Construction
public:
	CClassTupianDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClassTupianDlg)
	enum { IDD = IDD_CLASSTUPIAN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClassTupianDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClassTupianDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSTUPIANDLG_H__BA9B1024_F803_4BB6_BF29_179D08A37D4D__INCLUDED_)
