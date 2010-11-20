// DealPic.h: interface for the DealPic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEALPIC_H__D4520936_3823_411E_B86F_CCDC9639B760__INCLUDED_)
#define AFX_DEALPIC_H__D4520936_3823_411E_B86F_CCDC9639B760__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef struct Gestures
{
	int iGestures;
	int x;
	int y;
	int Gesture;
	Gestures *pnext;
};
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
	BOOL IsLine(int n, int iclock, IN int x,IN int y,OUT int *osx,OUT int *osy,OUT int *odx,OUT int *ody);
	BOOL InReaturn(int n, Gestures *G,int Tilt,int sx,int sy,int dx,int dy);//No 表示第几个比划 Gesture 表示比划的方向 Tilt 表示当前斜率既 -1 表示左倾斜，0 表示正常 1 表示有倾斜
	BOOL InReaturnOver(int n,Gestures *G,int sx,int sy,int dx,int dy);
	BOOL ShowError(char *cs);
	BOOL ShowError(CString cs);
	BOOL ShowGesturePath(int n, Gestures *G);
	void ClearNum(int *osx,int *osy,int *odx,int *ody);
	void InMiddle(int min,int max,int *Num);
};

#endif // !defined(AFX_DEALPIC_H__D4520936_3823_411E_B86F_CCDC9639B760__INCLUDED_)
