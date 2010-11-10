// WGClient.h : main header file for the WGCLIENT application
//

#if !defined(AFX_WGCLIENT_H__42997F08_1D9C_4A10_B479_4D46B461B86F__INCLUDED_)
#define AFX_WGCLIENT_H__42997F08_1D9C_4A10_B479_4D46B461B86F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWGClientApp:
// See WGClient.cpp for the implementation of this class
//

class CWGClientApp : public CWinApp
{
public:
	CWGClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWGClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWGClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WGCLIENT_H__42997F08_1D9C_4A10_B479_4D46B461B86F__INCLUDED_)
