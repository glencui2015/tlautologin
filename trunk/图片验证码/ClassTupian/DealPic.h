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
	BOOL BO[4][36][32];
	BOOL TMP[4][36][32];
	char NUMBER[4];

	DealPic();
	virtual ~DealPic();
	
	BOOL IsZero(int n);
	BOOL IsOne(int n);
	BOOL IsTwo(int n);
	BOOL IsThree(int n);
	BOOL IsFour(int n);
	BOOL IsFive(int n);
	BOOL IsSix(int n);
	BOOL IsSeven(int n);
	BOOL IsEight(int n);
	BOOL IsNine(int n);
	
	BOOL LoadBin(char *pDate);
	BOOL ShowNum(int n, HWND hWnd);
	BOOL DealNum(); // 对图片阵列进行处理 将结果放到NUMBER里面
	BOOL DealFirst();
	int  DealOne(int n);   //对一个进行初步处理的数字阵列进行 判断 将结果返回
	BOOL IsLine(int n, int bias, IN int x,IN int y);

};

#endif // !defined(AFX_DEALPIC_H__D4520936_3823_411E_B86F_CCDC9639B760__INCLUDED_)
