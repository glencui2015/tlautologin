// ShowTL.h : main header file for the SHOWTL application
//

#if !defined(AFX_SHOWTL_H__E2A4ED57_715E_4BA0_91F1_CD4874F0A4A3__INCLUDED_)
#define AFX_SHOWTL_H__E2A4ED57_715E_4BA0_91F1_CD4874F0A4A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShowTLApp:
// See ShowTL.cpp for the implementation of this class
//

class CShowTLApp : public CWinApp
{
public:
	CShowTLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowTLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShowTLApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWTL_H__E2A4ED57_715E_4BA0_91F1_CD4874F0A4A3__INCLUDED_)
