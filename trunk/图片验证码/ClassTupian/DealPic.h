// DealPic.h: interface for the DealPic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEALPIC_H__D4520936_3823_411E_B86F_CCDC9639B760__INCLUDED_)
#define AFX_DEALPIC_H__D4520936_3823_411E_B86F_CCDC9639B760__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DealPic  
{
public:
	BOOL B1[36][32];
	BOOL B2[36][32];
	BOOL B3[36][32];
	BOOL B4[36][32];
	BOOL TMP[36][32];

	DealPic();
	virtual ~DealPic();

};

#endif // !defined(AFX_DEALPIC_H__D4520936_3823_411E_B86F_CCDC9639B760__INCLUDED_)
