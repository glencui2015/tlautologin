// DealPic.cpp: implementation of the DealPic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClassTupian.h"
#include "DealPic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define  IN
#define  OUT

#define  CLOCK0 0
#define  CLOCK1 1
#define  CLOCK2 2
#define  CLOCK3 3
#define  CLOCK4 4
#define  CLOCK5 5
#define  CLOCK6 6
#define  CLOCK7 7
#define  CLOCK8 8
#define  CLOCK9 9
#define  CLOCK10 10
#define  CLOCK11 11
#define  CLOCK12 12
#define  CLOCK13 13
#define  CLOCK14 14
#define  CLOCK15 15

//#define  DEBUG


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DealPic::DealPic()
{
}

DealPic::~DealPic()
{

}

//////////////////////////////////////////////////////////////////////////
//加载数字到类中的变量
//////////////////////////////////////////////////////////////////////////
BOOL DealPic::LoadBin(char *pDate)
{
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
					this->BO[0][y][x%32] = !(a&c);
					break;
				case 1:
					this->BO[1][y][x%32] = !(a&c);
					break;
				case 2:
					this->BO[2][y][x%32] = !(a&c);
					break;
				case 3:
					this->BO[3][y][x%32] = !(a&c);
					break;
				default:
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
	return true;
}
////////////////////////////////////////////////////////////////////////////
//功能：在hwnd制定的界面上显示第n个数字
//////////////////////////////////////////////////////////////////////////
BOOL DealPic::ShowNum(int n, HWND hWnd)
{
	int x,y;
	x = y = 0;
	int up = 3;
	while (y < 36)
	{
		while (x < 32)
		{
			SetPixel(::GetDC(hWnd),x*up,y*up,RGB(255,255,255));
			if (this->BO[n][y][x])
			{
				SetPixel(::GetDC(hWnd),x*up,y*up,RGB(0,0,0));
			}
			x++;
		}
		x = 0;
		y++;
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//功能：用来处理图片 将结果放到NUMBER中
//////////////////////////////////////////////////////////////////////////
BOOL DealPic::DealNum()
{
	this->DealFirst();
	this->DealOne(1);
	return true;
}
//////////////////////////////////////////////////////////////////////////
//功能： 将位图图片进行一次性处理 所有的处理工作都在这里进行 其他的函数在进行分析。 
//////////////////////////////////////////////////////////////////////////
BOOL DealPic::DealFirst()     
{
	int x , y , n;
	x = y = n = 0;
	BOOL before;
	while (n < 4)
	{

		while (y < 36)
		{
			while (x < 32)
			{
				before = this->BO[n][y][x];
				if (before == this->BO[n][y-1][x-1] && before == this->BO[n][y-1][x] && before == this->BO[n][y-1][x+1] && before == this->BO[n][y][x-1] && 
			before == this->BO[n][y][x+1] && before == this->BO[n][y+1][x-1] && before == this->BO[n][y+1][x] && before == this->BO[n][y+1][x+1])
				{
					
					this->TMP[n][y][x] = FALSE;
				}
				else
				{
					this->TMP[n][y][x] = TRUE;
				}
				x++;
			}
			x = 0;
			y++;
		}
		x = y = 0;
		n++;
	}

	x = y = n = 0;
	while (n < 4)
	{
		while (y < 36)
		{
			while (x < 32)
			{
				this->BO[n][y][x] = this->TMP[n][y][x];
				x++;
			}
			x = 0;
			y++;
		}
		x = y = 0;
		n++;
	}	
	//下面是去掉数字内部的干扰点  把一些指定的点 进行去除
		x = y = n = 0;

	while (n < 4)
	{
		while (y < 36)
		{
			while (x < 32)
			{
				if (this->BO[n][y-1][x-1] && this->BO[n][y-1][x] && this->BO[n][y-1][x+1] &&
					this->BO[n][y][x-1]   &&!this->BO[n][y][x]   && this->BO[n][y][x+1]   && 
					this->BO[n][y+1][x-1] && this->BO[n][y+1][x] && this->BO[n][y+1][x+1])
				{
					this->BO[n][y][x]   = TRUE;
				}
				if (this->BO[n][y-1][x-1] && this->BO[n][y-1][x] && this->BO[n][y-1][x+1] && this->BO[n][y-1][x+2] &&
					this->BO[n][y][x-1]   &&!this->BO[n][y][x]   &&!this->BO[n][y][x+1]   && this->BO[n][y][x+2]   &&
					this->BO[n][y+1][x-1] && this->BO[n][y+1][x] && this->BO[n][y+1][x+1] && this->BO[n][y+1][x+2])
				{
					this->BO[n][y][x]   = TRUE;
					this->BO[n][y][x+1] = TRUE;
				}
				if (this->BO[n][y-1][x-1] && this->BO[n][y-1][x] && this->BO[n][y-1][x+1] &&
					this->BO[n][y][x-1]   &&!this->BO[n][y][x]   && this->BO[n][y][x+1]   &&
					this->BO[n][y+1][x-1] &&!this->BO[n][y+1][x] && this->BO[n][y+1][x+1] &&
					this->BO[n][y+2][x-1] && this->BO[n][y+2][x] && this->BO[n][y+2][x+1])
				{
					this->BO[n][y][x]   = TRUE;
					this->BO[n][y+1][x] = TRUE;
				}
				if (this->BO[n][y-1][x-1] && this->BO[n][y-1][x] && this->BO[n][y-1][x+1] && this->BO[n][y-1][x+2] &&
					this->BO[n][y][x-1]   &&!this->BO[n][y][x]   &&!this->BO[n][y][x+1]   && this->BO[n][y][x+2]   &&
					this->BO[n][y+1][x-1] &&!this->BO[n][y+1][x] &&!this->BO[n][y+1][x+1] && this->BO[n][y+1][x+2] &&
					this->BO[n][y+2][x-1] && this->BO[n][y+2][x] && this->BO[n][y+2][x+1] && this->BO[n][y+2][x+2])
				{
					this->BO[n][y][x] = TRUE;
					this->BO[n][y][x+1] = TRUE;
					this->BO[n][y+1][x] = TRUE;
					this->BO[n][y+1][x+1] = TRUE;
				}
				if (this->BO[n][y-1][x-1] && this->BO[n][y-1][x] && this->BO[n][y-1][x+1] && this->BO[n][y-1][x+2] && this->BO[n][y-1][x+3] &&
					this->BO[n][y][x-1]   &&!this->BO[n][y][x]   &&!this->BO[n][y][x+1]   &&!this->BO[n][y][x+2]   && this->BO[n][y][x+3]   &&
					this->BO[n][y+1][x-1] && this->BO[n][y+1][x] && this->BO[n][y+1][x+1] && this->BO[n][y+1][x+2] && this->BO[n][y+1][x+3])
				{
					this->BO[n][y][x]   = TRUE;
					this->BO[n][y][x+1] = TRUE;
					this->BO[n][y][x+2] = TRUE;
				}
				if (this->BO[n][y-1][x-1] && this->BO[n][y-1][x] && this->BO[n][y-1][x+1] &&
					this->BO[n][y][x-1]   &&!this->BO[n][y][x]   && this->BO[n][y][x+1]   &&
					this->BO[n][y+1][x-1] &&!this->BO[n][y+1][x] && this->BO[n][y+1][x+1] &&
					this->BO[n][y+2][x-1] &&!this->BO[n][y+2][x] && this->BO[n][y+2][x+1] &&
					this->BO[n][y+3][x-1] && this->BO[n][y+3][x] && this->BO[n][y+3][x+1])
				{
					this->BO[n][y][x]  = TRUE;
					this->BO[n][y+1][x] = TRUE;
					this->BO[n][y+2][x] = TRUE;
				}
				if (this->BO[n][y-1][x-1] && this->BO[n][y-1][x] && this->BO[n][y-1][x+1] && this->BO[n][y-1][x+2] && this->BO[n][y-1][x+3] && this->BO[n][y-1][x+4] &&
					this->BO[n][y][x-1]   &&!this->BO[n][y][x]   &&!this->BO[n][y][x+1]   &&!this->BO[n][y][x+2]   &&!this->BO[n][y][x+3]   && this->BO[n][y][x+4]   &&
					this->BO[n][y+1][x-1] && this->BO[n][y+1][x] && this->BO[n][y+1][x+1] && this->BO[n][y+1][x+2] && this->BO[n][y+1][x+3] && this->BO[n][y+1][x+4])
				{
					this->BO[n][y][x]   = TRUE;
					this->BO[n][y][x+1] = TRUE;
					this->BO[n][y][x+2] = TRUE;
					this->BO[n][y][x+3] = TRUE;
				}
				if (this->BO[n][y-1][x-1] && this->BO[n][y-1][x] && this->BO[n][y-1][x+1] &&
					this->BO[n][y][x-1]   &&!this->BO[n][y][x]   && this->BO[n][y][x+1]   &&
					this->BO[n][y+1][x-1] &&!this->BO[n][y+1][x] && this->BO[n][y+1][x+1] &&
					this->BO[n][y+2][x-1] &&!this->BO[n][y+2][x] && this->BO[n][y+2][x+1] &&
					this->BO[n][y+3][x-1] &&!this->BO[n][y+3][x] && this->BO[n][y+3][x+1] &&
					this->BO[n][y+4][x-1] && this->BO[n][y+4][x] && this->BO[n][y+4][x+1])
				{
					this->BO[n][y][x]  = TRUE;
					this->BO[n][y+1][x] = TRUE;
					this->BO[n][y+2][x] = TRUE;
					this->BO[n][y+3][x] = TRUE;
				}
				
				x++;
			}
			x = 0;
			y++;
		}
		x = y = 0;
		n++;
	}



return true;
}
//////////////////////////////////////////////////////////////////////////
//功能 用来判断一个数字阵列到底是几
//////////////////////////////////////////////////////////////////////////
int  DealPic::DealOne(int n)
{
	BOOL Ret[10] = {false};
	int iRet = 0;
	int i = 0;
	while (i < 10) // 先进行一次遍历 看看和那几个数字 相似度最高
	{
		switch(i)
		{
		case 0:
			if (this->IsZero(n))
			{
				Ret[n] = true;
			}
			break;
		case 1:
			if (this->IsOne(n))
			{
				Ret[n] = true;
			}
			break;
		case 2:
			if (this->IsTwo(n))
			{
				Ret[n] = true;
			}
			break;
		case 3:
			if (this->IsThree(n))
			{
				Ret[n] = true;
			}
			break;
		case 4:
			if (this->IsFour(n))
			{
				Ret[n] = true;
			}
			break;
		case 5:
			if (this->IsFive(n))
			{
				Ret[n] = true;
			}
			break;
		case 6:
			if (this->IsSix(n))
			{
				Ret[n] = true;
			}
			break;
		case 7:
			if (this->IsSeven(n))
			{
				Ret[n] = true;
			}
			break;
		case 8:
			if (this->IsEight(n))
			{
				Ret[n] = true;
			}
			break;
		case 9:
			if (this->IsNine(n))
			{
				Ret[n] = true;
			}
			break;
		default:
					break;
		}
		i++;
	}
	//下面进行优化 如果存在多个相识度高的数字 进行优化排序 这个需要根据以往多次对比的经验总结 需要后续开发的内容

	return iRet;
}
//////////////////////////////////////////////////////////////////////////
//功能：对递归函数InReaturn 进行一次包装 ， 初始化一些变量。
//////////////////////////////////////////////////////////////////////////
BOOL DealPic::InReaturnOver(int n,Gestures *G,int sx,int sy, int dx, int dy)
{
	int osx = 0;
	int osy = 0;
	int odx = 0;
	int ody = 0;

	if (G == NULL){return false;}
	if (sx > 32 || sx < 0 || dx < 0 || dy > 36)
	{
		return FALSE;
	}
	int x = sx;
	int y = sy;

CString cs;
	while (y <= dy )
	{
		while (x <= dx)
		{

			if (IsLine(n, ((*G).iGestures-1+16)%16, x , y , &osx, &osy, &odx, &ody))
			{
				if ((*G).pnext == NULL)
				{
					(*G).x = x;
					(*G).y = y;
					(*G).Gesture = ((*G).iGestures-1+16)%16;
					return TRUE;
				}

				else if (InReaturn(n, (*G).pnext, -1, osx, osy, odx, ody))
				{
					(*G).x = x;
					(*G).y = y;
					(*G).Gesture = ((*G).iGestures-1+16)%16;
					return TRUE;
				}
			}
			if (IsLine(n, ((*G).iGestures+0+16)%16, x, y, &osx, &osy, &odx, &ody))
			{
				if ((*G).pnext == NULL)
				{
					(*G).x = x;
					(*G).y = y;
					(*G).Gesture =  ((*G).iGestures+0+16)%16;
					return TRUE;
				}
				else if (InReaturn(n, (*G).pnext, 0, osx, osy, odx, ody))
				{
					(*G).x = x;
					(*G).y = y;
					(*G).Gesture =  ((*G).iGestures+0+16)%16;
					return TRUE;
				}
			}
			if (IsLine(n, ((*G).iGestures+1+16)%16,x ,y , &osx, &osy, &odx, &ody))
			{
				if ((*G).pnext == NULL)
				{
					(*G).x = x;
					(*G).y = y;
					(*G).Gesture =  ((*G).iGestures+1+16)%16;
					return TRUE;
				}
				else if (InReaturn(n, (*G).pnext, 1, osx, osy, odx, ody))
				{
					(*G).x = x;
					(*G).y = y;
					(*G).Gesture =  ((*G).iGestures+1+16)%16;
					return TRUE;
				}		
			}
			x++;
		}
		x=0;
		y++;
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////
//No 表示第几个比划 Gesture 表示比划的方向 Tilt 表示当前斜率既 -1 表示左倾斜，0 表示正常 1 表示有倾斜
//功能 用递归来实现比划规律的判断 根据事先定义好的比划顺序 模糊查找 数字
//////////////////////////////////////////////////////////////////////////
BOOL DealPic::InReaturn(int n, Gestures *G,int Tilt,int sx,int sy,int dx,int dy)
{
	int osx = 0;
	int osy = 0;
	int odx = 0;
	int ody = 0;
	
	if (G == NULL){return false;}
	if (sx > 32 || sx < 0 || dx < 0 || dy > 36)
	{
		return FALSE;
	}
	int x = sx;
	int y = sy;
	
	
	while (y <= dy )
	{
		while (x <= dx)
		{
			if (IsLine(n, ((*G).iGestures + Tilt -1+16)%16, x , y , &osx, &osy, &odx, &ody))
			{
				
				if ((*G).pnext == NULL)
				{
					(*G).x = x;
					(*G).y = y;
					(*G).Gesture = ((*G).iGestures + Tilt -1+16)%16;
					return TRUE;
				}
				
				else if (InReaturn(n, (*G).pnext, -1, osx, osy, odx, ody))
				{
					(*G).x = x;
					(*G).y = y;
					(*G).Gesture = ((*G).iGestures + Tilt -1+16)%16;
					return TRUE;
				}
			}
			if (IsLine(n, ((*G).iGestures + Tilt + 0 +16)%16, x, y, &osx, &osy, &odx, &ody))
			{
				
				if ((*G).pnext == NULL)
				{
					(*G).x = x;
					(*G).y = y;
					(*G).Gesture = ((*G).iGestures + Tilt + 0 +16)%16;
					return TRUE;
				}
				else if (InReaturn(n, (*G).pnext, 0, osx, osy, odx, ody))
				{
					(*G).x = x;
					(*G).y = y;
					(*G).Gesture = ((*G).iGestures + Tilt + 0 +16)%16;
					return TRUE;
				}
			}
			if (IsLine(n, ((*G).iGestures+Tilt + 1 +16)%16, x, y, &osx, &osy, &odx, &ody))
			{
				if ((*G).pnext == NULL)
				{
					(*G).x = x;
					(*G).y = y;
					(*G).Gesture = ((*G).iGestures+Tilt + 1 +16)%16;
					return TRUE;
				}
				else if (InReaturn(n, (*G).pnext, 1, osx, osy, odx, ody))
				{
					(*G).x = x;
					(*G).y = y;
					(*G).Gesture = ((*G).iGestures+Tilt + 1 +16)%16;
					return TRUE; 
				}		
			}
			x++;
		}
		x=0;
		y++;
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////
//参数n表示 要比较的第几个数是不是0
//功能：判断制定的图片是不是0
//////////////////////////////////////////////////////////////////////////
BOOL DealPic::IsZero(int n)
{
	int osx = 8;
	int osy = 0;
	int odx = 23;
	int ody = 17;
	
	Gestures G[10] = {0};
	G[0].iGestures = 4;
	G[0].pnext = &G[1];
	G[1].iGestures = 6;
	G[1].pnext = &G[2];
	G[2].iGestures = 8;
	G[2].pnext = &G[3];
	G[3].iGestures = 10;
	G[3].pnext = &G[4];
	G[4].iGestures = 12;
	G[4].pnext = &G[5];
	G[5].iGestures = 14;
	G[5].pnext = &G[6];
	G[6].iGestures = 0;
	G[6].pnext = &G[7];
	G[7].iGestures = 2;
	G[7].pnext = NULL;


	if (this->InReaturnOver(n,G,osx,osy,odx,ody))
	{
		this->ShowGesturePath(0, &G[0]);
		return TRUE;
	}
	return FALSE;
}

BOOL DealPic::IsOne(int n)
{
	int osx = 8;
	int osy = 3;
	int odx = 23;
	int ody = 14;

	Gestures G[10] = {0};
	G[0].iGestures = 8;
	G[0].pnext = &G[1];
	G[1].iGestures = 8;
	G[1].pnext = NULL;

	if (this->InReaturnOver(n,G,osx,osy,odx,ody))
	{
		this->ShowGesturePath(1,&G[0]);
		return TRUE;
	}

	return FALSE;
}

BOOL DealPic::IsTwo(int n)
{
	return true;
}

BOOL DealPic::IsThree(int n)
{
	return true;
}

BOOL DealPic::IsFour(int n)
{
	return true;
}

BOOL DealPic::IsFive(int n)
{
	return true;
}

BOOL DealPic::IsSix(int n)
{
	int osx = 8;
	int osy = 3;
	int odx = 23;
	int ody = 14;

	Gestures G[10] = {0};
	G[0].iGestures = 12;
	G[0].pnext = &G[1];
	G[1].iGestures = 12;
	G[1].pnext = &G[2];
	G[2].iGestures = 8;
	G[2].pnext = &G[3];
	G[3].iGestures = 8;
	G[3].pnext = &G[4];
	G[4].iGestures = 4;
	G[4].pnext = &G[5];
	G[5].iGestures = 0;
	G[5].pnext = &G[6];
	G[6].iGestures = 12;
	G[6].pnext = NULL;
	if (this->InReaturnOver(n,G,osx,osy,odx,ody))
	{
		this->ShowGesturePath(6,&G[0]);
		return TRUE;
	}
	return FALSE;
}

BOOL DealPic::IsSeven(int n)
{
	return true;
}

BOOL DealPic::IsEight(int n)
{
	return true;
}

BOOL DealPic::IsNine(int n)
{
	return true;
}
//////////////////////////////////////////////////////////////////////////
//功能：判断 制定坐标的周围有没有iclock制定的倾斜的直线 宽度现在默认是3 并判断终点坐标是否越界 
//参数：
//		int *ox   如果有直线 返回直线另一端的x坐标
//		int *oy   如果有直线 返回直线另一端的y坐标
//		int x     指定坐标的x坐标
//		int y	  指定坐标的y坐标
//		int iclock  指定倾斜的方向 这里用整点数来做区别 用宏clock0-clock11来表示0点到11点的方向
//		int n	  用来表示判断第几个数
//////////////////////////////////////////////////////////////////////////

BOOL DealPic::IsLine(int n, int iclock, IN int x,IN int y,OUT int *osx,OUT int *osy,OUT int *odx,OUT int *ody)
{
	CString cs;
	cs.Format("是%d点的方向 x:%d y:%d",iclock,x,y);
	switch(iclock)
	{
	case CLOCK0:
		if (this->BO[n][y-8][x+0] && this->BO[n][y-8][x+1] && this->BO[n][y-8][x+2] && this->BO[n][y-7][x+0] && this->BO[n][y-7][x+1] && this->BO[n][y-7][x+2] && this->BO[n][y-6][x+0] && this->BO[n][y-6][x+1] && this->BO[n][y-6][x+2] && this->BO[n][y-5][x+0] && this->BO[n][y-5][x+1] && this->BO[n][y-5][x+2] && this->BO[n][y-4][x+0] && this->BO[n][y-4][x+1] && this->BO[n][y-4][x+2] && this->BO[n][y-3][x+0] && this->BO[n][y-3][x+1] && this->BO[n][y-3][x+2] && this->BO[n][y-2][x+0] && this->BO[n][y-2][x+1] && this->BO[n][y-2][x+2] && this->BO[n][y-1][x+0] && this->BO[n][y-1][x+1] && this->BO[n][y-1][x+2] && this->BO[n][y+0][x+0] && this->BO[n][y+0][x+1] && this->BO[n][y+0][x+2])
		{
			this->ShowError(cs);
			*osx = x+2-3;
			*osy = y-8-3;
			*odx = x+2+3;
			*ody = y-8+3;
			if (-2 < x && x < 30 && 8 < y && y  < 44)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK1:
		if (this->BO[n][y-12][x+5] && this->BO[n][y-11][x+5] && this->BO[n][y-10][x+4] && this->BO[n][y-10][x+5] && this->BO[n][y-9][x+4] && this->BO[n][y-8][x+3] && this->BO[n][y-8][x+4] && this->BO[n][y-7][x+3] && this->BO[n][y-6][x+2] && this->BO[n][y-6][x+3] && this->BO[n][y-5][x+2] && this->BO[n][y-4][x+1] && this->BO[n][y-4][x+2] && this->BO[n][y-3][x+1] && this->BO[n][y-2][x+0] && this->BO[n][y-2][x+1] && this->BO[n][y-1][x+0] && this->BO[n][y+0][x+0])
		{
			this->ShowError(cs);
			*osx = x+5-3;
			*osy = y-12-3;
			*odx = x+5+3;
			*ody = y-12+3;
			if (-5 < x && x < 27 && 12 < y && y < 48)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK2:
		if (this->BO[n][y-8][x+7] && this->BO[n][y-8][x+8] && this->BO[n][y-7][x+6] && this->BO[n][y-7][x+7] && this->BO[n][y-7][x+8] && this->BO[n][y-6][x+5] && this->BO[n][y-6][x+6] && this->BO[n][y-6][x+7] && this->BO[n][y-5][x+4] && this->BO[n][y-5][x+5] && this->BO[n][y-5][x+6] && this->BO[n][y-4][x+3] && this->BO[n][y-4][x+4] && this->BO[n][y-4][x+5] && this->BO[n][y-3][x+2] && this->BO[n][y-3][x+3] && this->BO[n][y-3][x+4] && this->BO[n][y-2][x+1] && this->BO[n][y-2][x+2] && this->BO[n][y-2][x+3] && this->BO[n][y-1][x+0] && this->BO[n][y-1][x+1] && this->BO[n][y-1][x+2] && this->BO[n][y+0][x+0] && this->BO[n][y+0][x+1])
		{
			this->ShowError(cs);
			*osx = x+8-3;
			*osy = x-8-3;
			*odx = x+8+3;
			*ody = y-8+3;
			if (-8 < x && x < 24 && 8 < y && y < 44)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK3:
		if (this->BO[n][y-5][x+10] && this->BO[n][y-5][x+11] && this->BO[n][y-5][x+12] && this->BO[n][y-4][x+8] && this->BO[n][y-4][x+9] && this->BO[n][y-4][x+10] && this->BO[n][y-3][x+6] && this->BO[n][y-3][x+7] && this->BO[n][y-3][x+8] && this->BO[n][y-2][x+4] && this->BO[n][y-2][x+5] && this->BO[n][y-2][x+6] && this->BO[n][y-1][x+2] && this->BO[n][y-1][x+3] && this->BO[n][y-1][x+4] && this->BO[n][y+0][x+0] && this->BO[n][y+0][x+1] && this->BO[n][y+0][x+2])
		{
			this->ShowError(cs);
			*osx = x+12-3;
			*osy = y-5-3;
			*odx = x+12+3;
			*ody = y-5+3;
			if (-12 < x && x < 20 && 5 < y && y < 41)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK4:
		if (this->BO[n][y-2][x+0] && this->BO[n][y-2][x+1] && this->BO[n][y-2][x+2] && this->BO[n][y-2][x+3] && this->BO[n][y-2][x+4] && this->BO[n][y-2][x+5] && this->BO[n][y-2][x+6] && this->BO[n][y-2][x+7] && this->BO[n][y-1][x+0] && this->BO[n][y-1][x+1] && this->BO[n][y-1][x+2] && this->BO[n][y-1][x+3] && this->BO[n][y-1][x+4] && this->BO[n][y-1][x+5] && this->BO[n][y-1][x+6] && this->BO[n][y-1][x+7] && this->BO[n][y+0][x+0] && this->BO[n][y+0][x+1] && this->BO[n][y+0][x+2] && this->BO[n][y+0][x+3] && this->BO[n][y+0][x+4] && this->BO[n][y+0][x+5] && this->BO[n][y+0][x+6] && this->BO[n][y+0][x+7])
		{
			this->ShowError(cs);
			*osx = x+7-3;
			*osy = y-2-3;
			*odx = x+7+3;
			*ody = y-2+3;
			if (-7 < x && x < 25 && 2 < y && y < 38)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK5:
		if (this->BO[n][y+0][x+0] && this->BO[n][y+0][x+1] && this->BO[n][y+0][x+2] && this->BO[n][y+1][x+2] && this->BO[n][y+1][x+3] && this->BO[n][y+1][x+4] && this->BO[n][y+2][x+4] && this->BO[n][y+2][x+5] && this->BO[n][y+2][x+6] && this->BO[n][y+3][x+6] && this->BO[n][y+3][x+7] && this->BO[n][y+3][x+8] && this->BO[n][y+4][x+8] && this->BO[n][y+4][x+9] && this->BO[n][y+4][x+10] && this->BO[n][y+5][x+10] && this->BO[n][y+5][x+11] && this->BO[n][y+5][x+12])
		{
			this->ShowError(cs);
			*osx = x+12-3;
			*osy = y+5-3;
			*odx = x+12+3;
			*ody = y+5+3;
			if (-12 < x && x < 20 && -5 < y && y < 31)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK6:
		if (this->BO[n][y+0][x+0] && this->BO[n][y+0][x+1] && this->BO[n][y+1][x+0] && this->BO[n][y+1][x+1] && this->BO[n][y+1][x+2] && this->BO[n][y+2][x+1] && this->BO[n][y+2][x+2] && this->BO[n][y+2][x+3] && this->BO[n][y+3][x+2] && this->BO[n][y+3][x+3] && this->BO[n][y+3][x+4] && this->BO[n][y+4][x+3] && this->BO[n][y+4][x+4] && this->BO[n][y+4][x+5] && this->BO[n][y+5][x+4] && this->BO[n][y+5][x+5] && this->BO[n][y+5][x+6] && this->BO[n][y+6][x+5] && this->BO[n][y+6][x+6] && this->BO[n][y+6][x+7] && this->BO[n][y+7][x+6] && this->BO[n][y+7][x+7])
		{
			this->ShowError(cs);
			*osx = x+8-3;
			*osy = y+8-3;
			*odx = x+8+3;
			*ody = y+8+3;
			if (-8 < x && x < 24 && -8 < y && y < 28)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK7:
		if (this->BO[n][y+0][x+0] && this->BO[n][y+1][x+0] && this->BO[n][y+2][x+0] && this->BO[n][y+2][x+1] && this->BO[n][y+3][x+1] && this->BO[n][y+4][x+1] && this->BO[n][y+4][x+2] && this->BO[n][y+5][x+2] && this->BO[n][y+6][x+2] && this->BO[n][y+6][x+3] && this->BO[n][y+7][x+3] && this->BO[n][y+8][x+3] && this->BO[n][y+8][x+4] && this->BO[n][y+9][x+4] && this->BO[n][y+10][x+4] && this->BO[n][y+10][x+5] && this->BO[n][y+11][x+5] && this->BO[n][y+12][x+5])
		{
			this->ShowError(cs);
			*osx = x+5-3;
			*osy = y+12-3;
			*odx = x+5+3;
			*ody = y+12+3;
			if (-5 < x && x < 27 && -12 < y && x < 24)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK8:
		if (this->BO[n][y+0][x+0] && this->BO[n][y+0][x+1] && this->BO[n][y+0][x+2] && this->BO[n][y+1][x+0] && this->BO[n][y+1][x+1] && this->BO[n][y+1][x+2] && this->BO[n][y+2][x+0] && this->BO[n][y+2][x+1] && this->BO[n][y+2][x+2] && this->BO[n][y+3][x+0] && this->BO[n][y+3][x+1] && this->BO[n][y+3][x+2] && this->BO[n][y+4][x+0] && this->BO[n][y+4][x+1] && this->BO[n][y+4][x+2] && this->BO[n][y+5][x+0] && this->BO[n][y+5][x+1] && this->BO[n][y+5][x+2] && this->BO[n][y+6][x+0] && this->BO[n][y+6][x+1] && this->BO[n][y+6][x+2] && this->BO[n][y+7][x+0] && this->BO[n][y+7][x+1] && this->BO[n][y+7][x+2] && this->BO[n][y+8][x+0] && this->BO[n][y+8][x+1] && this->BO[n][y+8][x+2])
		{
			this->ShowError(cs);
			*osx = x+2-3;
			*osy = y+8-3;
			*odx = x+2+3;
			*ody = y+8+3;
			if (-2 < x && x < 30 && -8 < y && y < 28)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK9:
		if (this->BO[n][y+0][x+0] && this->BO[n][y+1][x+0] && this->BO[n][y+2][x-1] && this->BO[n][y+2][x+0] && this->BO[n][y+3][x-1] && this->BO[n][y+4][x-2] && this->BO[n][y+4][x-1] && this->BO[n][y+5][x-2] && this->BO[n][y+6][x-3] && this->BO[n][y+6][x-2] && this->BO[n][y+7][x-3] && this->BO[n][y+8][x-4] && this->BO[n][y+8][x-3] && this->BO[n][y+9][x-4] && this->BO[n][y+10][x-5] && this->BO[n][y+10][x-4] && this->BO[n][y+11][x-5] && this->BO[n][y+12][x-5])
		{
			this->ShowError(cs);
			*osx = x-5-3;
			*osy = y+12-3;
			*odx = x-5+3;
			*ody = y+12+3;
			if (5 < x && x < 37 && -12 < x && x < 24)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK10:
		if (this->BO[n][y+0][x-1] && this->BO[n][y+0][x+0] && this->BO[n][y+1][x-2] && this->BO[n][y+1][x-1] && this->BO[n][y+1][x+0] && this->BO[n][y+2][x-3] && this->BO[n][y+2][x-2] && this->BO[n][y+2][x-1] && this->BO[n][y+3][x-4] && this->BO[n][y+3][x-3] && this->BO[n][y+3][x-2] && this->BO[n][y+4][x-5] && this->BO[n][y+4][x-4] && this->BO[n][y+4][x-3] && this->BO[n][y+5][x-6] && this->BO[n][y+5][x-5] && this->BO[n][y+5][x-4] && this->BO[n][y+6][x-7] && this->BO[n][y+6][x-6] && this->BO[n][y+6][x-5] && this->BO[n][y+7][x-7] && this->BO[n][y+7][x-6])
		{
			this->ShowError(cs);
			*osx = x-8-3;
			*osy = y+8-3;
			*odx = x-8+3;
			*ody = y+8+3;
			if (8 < x && x < 40 && -8 < y && y < 28)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK11:
		if (this->BO[n][y+0][x-2] && this->BO[n][y+0][x-1] && this->BO[n][y+0][x+0] && this->BO[n][y+1][x-4] && this->BO[n][y+1][x-3] && this->BO[n][y+1][x-2] && this->BO[n][y+2][x-6] && this->BO[n][y+2][x-5] && this->BO[n][y+2][x-4] && this->BO[n][y+3][x-8] && this->BO[n][y+3][x-7] && this->BO[n][y+3][x-6] && this->BO[n][y+4][x-10] && this->BO[n][y+4][x-9] && this->BO[n][y+4][x-8] && this->BO[n][y+5][x-12] && this->BO[n][y+5][x-11] && this->BO[n][y+5][x-10])
		{
			this->ShowError(cs);
			*osx = x-12-3;
			*osy = y+5-3;
			*odx = x-12+3;
			*ody = y+5+3;
			if (12 < x && x < 44 && -5 < y && y < 31)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK12:
		if (this->BO[n][y+0][x-8] && this->BO[n][y+0][x-7] && this->BO[n][y+0][x-6] && this->BO[n][y+0][x-5] && this->BO[n][y+0][x-4] && this->BO[n][y+0][x-3] && this->BO[n][y+0][x-2] && this->BO[n][y+0][x-1] && this->BO[n][y+0][x+0] && this->BO[n][y+1][x-8] && this->BO[n][y+1][x-7] && this->BO[n][y+1][x-6] && this->BO[n][y+1][x-5] && this->BO[n][y+1][x-4] && this->BO[n][y+1][x-3] && this->BO[n][y+1][x-2] && this->BO[n][y+1][x-1] && this->BO[n][y+1][x+0] && this->BO[n][y+2][x-8] && this->BO[n][y+2][x-7] && this->BO[n][y+2][x-6] && this->BO[n][y+2][x-5] && this->BO[n][y+2][x-4] && this->BO[n][y+2][x-3] && this->BO[n][y+2][x-2] && this->BO[n][y+2][x-1] && this->BO[n][y+2][x+0])
		{
			this->ShowError(cs);
			*osx = x-8-3;
			*osy = y+2-3;
			*odx = x-8+3;
			*ody = y+2+3;
			if (8 < x && x < 40 && -2 < y && y< 34)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK13:
		if (this->BO[n][y-5][x-12] && this->BO[n][y-5][x-11] && this->BO[n][y-5][x-10] && this->BO[n][y-4][x-10] && this->BO[n][y-4][x-9] && this->BO[n][y-4][x-8] && this->BO[n][y-3][x-8] && this->BO[n][y-3][x-7] && this->BO[n][y-3][x-6] && this->BO[n][y-2][x-6] && this->BO[n][y-2][x-5] && this->BO[n][y-2][x-4] && this->BO[n][y-1][x-4] && this->BO[n][y-1][x-3] && this->BO[n][y-1][x-2] && this->BO[n][y+0][x-2] && this->BO[n][y+0][x-1] && this->BO[n][y+0][x+0])
		{
			this->ShowError(cs);
			*osx = x-12-3;
			*osy = y-5-3;
			*odx = x-12+3;
			*ody = y-5+3;
			if (12 < x && x < 44 && 5 < y && y < 41)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK14:
		if (this->BO[n][y-7][x-7] && this->BO[n][y-7][x-6] && this->BO[n][y-6][x-7] && this->BO[n][y-6][x-6] && this->BO[n][y-6][x-5] && this->BO[n][y-5][x-6] && this->BO[n][y-5][x-5] && this->BO[n][y-5][x-4] && this->BO[n][y-4][x-5] && this->BO[n][y-4][x-4] && this->BO[n][y-4][x-3] && this->BO[n][y-3][x-4] && this->BO[n][y-3][x-3] && this->BO[n][y-3][x-2] && this->BO[n][y-2][x-3] && this->BO[n][y-2][x-2] && this->BO[n][y-2][x-1] && this->BO[n][y-1][x-2] && this->BO[n][y-1][x-1] && this->BO[n][y-1][x+0] && this->BO[n][y+0][x-1] && this->BO[n][y+0][x+0])
		{
			this->ShowError(cs);
			*osx = x-8-3;
			*osy = y-8-3;
			*odx = x-8+3;
			*ody = y-8+3;
			if (8 < x && x < 40 && 8 < y && y < 44)
			{
				return TRUE;
			}
		}
		break;
	case CLOCK15:
		if (this->BO[n][y-12][x-5] && this->BO[n][y-11][x-5] && this->BO[n][y-10][x-5] && this->BO[n][y-10][x-4] && this->BO[n][y-9][x-4] && this->BO[n][y-8][x-4] && this->BO[n][y-8][x-3] && this->BO[n][y-7][x-3] && this->BO[n][y-6][x-3] && this->BO[n][y-6][x-2] && this->BO[n][y-5][x-2] && this->BO[n][y-4][x-2] && this->BO[n][y-4][x-1] && this->BO[n][y-3][x-1] && this->BO[n][y-2][x-1] && this->BO[n][y-2][x+0] && this->BO[n][y-1][x+0] && this->BO[n][y+0][x+0])
		{
			this->ShowError(cs);
			*osx = x-5-3;
			*osy = y-12-3;
			*odx = x-5+3;
			*ody = y-12+3;
			if (5 < x && x < 37 && 12 < y && y < 48)
			{
				return TRUE;
			}
		}
		break;
	default:
		break;
	}
	
	
	return FALSE;
}




BOOL DealPic::ShowError(char *cs)
{
#ifdef DEBUG
		AfxMessageBox(cs);
#endif
	return TRUE;
}
BOOL DealPic::ShowError(CString cs)
{
#ifdef DEBUG
		AfxMessageBox(cs);
#endif
	return TRUE;
}
BOOL DealPic::ShowGesturePath(int n,Gestures *G)
{
	Gestures pG;
	pG.pnext = G;
	char str[200] = {0};
sprintf(str,"%d",n);
	while (pG.pnext != NULL)
	{
		pG = *(pG.pnext);
		if (strlen(str) > 200)
		{
			AfxMessageBox("str长度已经越界");
		}
		sprintf(str,"%s,(%d,%d:%d)",str,pG.x,pG.y,pG.Gesture);
	}

	AfxMessageBox(str);
	return TRUE;
}