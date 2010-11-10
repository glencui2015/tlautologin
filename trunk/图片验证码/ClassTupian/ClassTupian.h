// ClassTupian.h : main header file for the CLASSTUPIAN application
//

#if !defined(AFX_CLASSTUPIAN_H__E86BE0AF_E32E_4420_992D_96FD5922801B__INCLUDED_)
#define AFX_CLASSTUPIAN_H__E86BE0AF_E32E_4420_992D_96FD5922801B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClassTupianApp:
// See ClassTupian.cpp for the implementation of this class
//

class CClassTupianApp : public CWinApp
{
public:
	CClassTupianApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClassTupianApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClassTupianApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSTUPIAN_H__E86BE0AF_E32E_4420_992D_96FD5922801B__INCLUDED_)
