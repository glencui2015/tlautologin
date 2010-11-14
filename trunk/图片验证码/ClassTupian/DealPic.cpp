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
	return true;
}
//////////////////////////////////////////////////////////////////////////
//功能： 将位图图片进行一次性处理 所有的处理工作都在这里进行 其他的函数在进行分析。 
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
Default:
					break;
		}
		i++;
	}
	//下面进行优化 如果存在多个相识度高的数字 进行优化排序 这个需要根据以往多次对比的经验总结 需要后续开发的内容

	return iRet;
}

//////////////////////////////////////////////////////////////////////////
//参数n表示 要比较的第几个数是不是0
//功能：判断制定的图片是不是0
//////////////////////////////////////////////////////////////////////////
BOOL DealPic::IsZero(int n)
{
	int osx = 0;
	int osy = 0;
	int odx = 0;
	int ody = 0;

	if (InZoneRich(n,CLOCK7,8,0,23,17,&osx,&osy,&odx,&ody))
	{
		
	}
	return true;
}

BOOL DealPic::IsOne(int n)
{
	return true;
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
	return true;
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
//功能：判断 制定坐标的周围有没有iclock制定的倾斜的直线 宽度现在默认是4 
//参数：
//		int *ox   如果有直线 返回直线另一端的x坐标
//		int *oy   如果有直线 返回直线另一端的y坐标
//		int x     指定坐标的x坐标
//		int y	  指定坐标的y坐标
//		int iclock  指定倾斜的方向 这里用整点数来做区别 用宏clock0-clock11来表示0点到11点的方向
//		int n	  用来表示判断第几个数
//////////////////////////////////////////////////////////////////////////

BOOL DealPic::IsLine(int n, int iclock, IN int x,IN int y)
{
	switch(iclock)
	{
	case CLOCK0:
		if (this->BO[n][y-7][x-1] && this->BO[n][y-7][x-2] && this->BO[n][y-7][x] && this->BO[n][y-7][x+1] && this->BO[n][y-7][x+2] && 
			this->BO[n][y-6][x-1] && this->BO[n][y-6][x-2] && this->BO[n][y-6][x] && this->BO[n][y-6][x+1] && this->BO[n][y-6][x+2] && 
			this->BO[n][y-5][x-1] && this->BO[n][y-5][x-2] && this->BO[n][y-5][x] && this->BO[n][y-5][x+1] && this->BO[n][y-5][x+2] && 
			this->BO[n][y-4][x-1] && this->BO[n][y-4][x-2] && this->BO[n][y-4][x] && this->BO[n][y-4][x+1] && this->BO[n][y-4][x+2] && 
			this->BO[n][y-3][x-1] && this->BO[n][y-3][x-2] && this->BO[n][y-3][x] && this->BO[n][y-3][x+1] && this->BO[n][y-3][x+2] && 
			this->BO[n][y-2][x-1] && this->BO[n][y-2][x-2] && this->BO[n][y-2][x] && this->BO[n][y-2][x+1] && this->BO[n][y-2][x+2] && 
			this->BO[n][y-1][x-1] && this->BO[n][y-1][x-2] && this->BO[n][y-1][x] && this->BO[n][y-1][x+1] && this->BO[n][y-1][x+2] && 
			this->BO[n][y][x-1]   && this->BO[n][y][x-1]   && this->BO[n][y][x]   && this->BO[n][y][x+1]   && this->BO[n][y][x+1])
		{
			return TRUE;
		}
		break;
	case CLOCK1:
		if (this->BO[n][y-14][x+5] && this->BO[n][y-13][x+5] && this->BO[n][y-12][x+4] && this->BO[n][y-12][x+5] && 
			this->BO[n][y-11][x+4] && this->BO[n][y-11][x+5] && this->BO[n][y-10][x+3] && this->BO[n][y-10][x+4] && this->BO[n][y-10][x+5] && 
			this->BO[n][y-9][x+3] && this->BO[n][y-9][x+4] && this->BO[n][y-8][x+2] && this->BO[n][y-8][x+3] && this->BO[n][y-8][x+4] && 
			this->BO[n][y-7][x+2] && this->BO[n][y-7][x+3] && this->BO[n][y-6][x+1] && this->BO[n][y-6][x+2] && this->BO[n][y-6][x+3] && 
			this->BO[n][y-5][x+1] && this->BO[n][y-5][x+2] && this->BO[n][y-4][x] && this->BO[n][y-4][x+1] && this->BO[n][y-4][x+2] && 
			this->BO[n][y-3][x] && this->BO[n][y-3][x+1] && this->BO[n][y-2][x] && this->BO[n][y-2][x+1] && 
			this->BO[n][y-1][x] && this->BO[n][y][x])
		{
			return TRUE;
		}
		break;
	case CLOCK2:
		if (this->BO[n][y-9][x+5] && this->BO[n][y-8][x+4] && this->BO[n][y-8][x+5] && this->BO[n][y-7][x+3] && this->BO[n][y-7][x+4] && 
			this->BO[n][y-7][x+5] && this->BO[n][y-6][x+2] && this->BO[n][y-6][x+3] && this->BO[n][y-6][x+4] && this->BO[n][y-6][x+5] && 
			this->BO[n][y-5][x+1] && this->BO[n][y-5][x+2] && this->BO[n][y-5][x+3] && this->BO[n][y-5][x+4] && this->BO[n][y-5][x+5] && 
			this->BO[n][y-4][x+0] && this->BO[n][y-4][x+1] && this->BO[n][y-4][x+2] && this->BO[n][y-4][x+3] && this->BO[n][y-4][x+4] && 
			this->BO[n][y-3][x+0] && this->BO[n][y-3][x+1] && this->BO[n][y-3][x+2] && this->BO[n][y-3][x+3] && this->BO[n][y-2][x+0] && 
			this->BO[n][y-2][x+1] && this->BO[n][y-2][x+2] && this->BO[n][y-1][x+0] && this->BO[n][y-1][x+1] && this->BO[n][y+0][x+0])
		{
			return TRUE;
		}
		break;
	case CLOCK3:
		if (this->BO[n][y-4][x+0] && this->BO[n][y-4][x+1] && this->BO[n][y-4][x+2] && this->BO[n][y-4][x+3] && this->BO[n][y-4][x+4] && 
			this->BO[n][y-4][x+5] && this->BO[n][y-4][x+6] && this->BO[n][y-4][x+7] && this->BO[n][y-3][x+0] && this->BO[n][y-3][x+1] && 
			this->BO[n][y-3][x+2] && this->BO[n][y-3][x+3] && this->BO[n][y-3][x+4] && this->BO[n][y-3][x+5] && this->BO[n][y-3][x+6] && 
			this->BO[n][y-3][x+7] && this->BO[n][y-2][x+0] && this->BO[n][y-2][x+1] && this->BO[n][y-2][x+2] && this->BO[n][y-2][x+3] && 
			this->BO[n][y-2][x+4] && this->BO[n][y-2][x+5] && this->BO[n][y-2][x+6] && this->BO[n][y-2][x+7] && this->BO[n][y-1][x+0] && 
			this->BO[n][y-1][x+1] && this->BO[n][y-1][x+2] && this->BO[n][y-1][x+3] && this->BO[n][y-1][x+4] && this->BO[n][y-1][x+5] && 
			this->BO[n][y-1][x+6] && this->BO[n][y-1][x+7] && this->BO[n][y+0][x+0] && this->BO[n][y+0][x+1] && this->BO[n][y+0][x+2] && 
			this->BO[n][y+0][x+3] && this->BO[n][y+0][x+4] && this->BO[n][y+0][x+5] && this->BO[n][y+0][x+6] && this->BO[n][y+0][x+7])
		{
			return TRUE;
		}
		break;
	case CLOCK4:
		if (this->BO[n][y+0][x+0] && this->BO[n][y+1][x+0] && this->BO[n][y+1][x+1] && this->BO[n][y+2][x+0] && this->BO[n][y+2][x+1] && 
			this->BO[n][y+2][x+2] && this->BO[n][y+3][x+0] && this->BO[n][y+3][x+1] && this->BO[n][y+3][x+2] && this->BO[n][y+3][x+3] && 
			this->BO[n][y+4][x+0] && this->BO[n][y+4][x+1] && this->BO[n][y+4][x+2] && this->BO[n][y+4][x+3] && this->BO[n][y+4][x+4] && 
			this->BO[n][y+5][x+1] && this->BO[n][y+5][x+2] && this->BO[n][y+5][x+3] && this->BO[n][y+5][x+4] && this->BO[n][y+5][x+5] && 
			this->BO[n][y+6][x+2] && this->BO[n][y+6][x+3] && this->BO[n][y+6][x+4] && this->BO[n][y+6][x+5] && this->BO[n][y+7][x+3] && 
			this->BO[n][y+7][x+4] && this->BO[n][y+7][x+5] && this->BO[n][y+8][x+4] && this->BO[n][y+8][x+5] && this->BO[n][y+9][x+5])
		{
			return TRUE;
		}
		break;
	case CLOCK5:
		if (this->BO[n][y+0][x+0] && this->BO[n][y+1][x+0] && this->BO[n][y+2][x+0] && this->BO[n][y+2][x+1] && this->BO[n][y+3][x+0] && 
			this->BO[n][y+3][x+1] && this->BO[n][y+4][x+0] && this->BO[n][y+4][x+1] && this->BO[n][y+4][x+2] && this->BO[n][y+5][x+1] && 
			this->BO[n][y+5][x+2] && this->BO[n][y+6][x+1] && this->BO[n][y+6][x+2] && this->BO[n][y+6][x+3] && this->BO[n][y+7][x+2] && 
			this->BO[n][y+7][x+3] && this->BO[n][y+8][x+2] && this->BO[n][y+8][x+3] && this->BO[n][y+8][x+4] && this->BO[n][y+9][x+3] && 
			this->BO[n][y+9][x+4] && this->BO[n][y+10][x+3] && this->BO[n][y+10][x+4] && this->BO[n][y+10][x+5] && this->BO[n][y+11][x+4] && 
			this->BO[n][y+11][x+5] && this->BO[n][y+12][x+4] && this->BO[n][y+12][x+5] && this->BO[n][y+13][x+5] && this->BO[n][y+14][x+5])
		{
			return TRUE;
		}
		break;
	case CLOCK6:
		if (this->BO[n][y+0][x+0] && this->BO[n][y+0][x+1] && this->BO[n][y+0][x+2] && this->BO[n][y+0][x+3] && this->BO[n][y+0][x+4] && 
			this->BO[n][y+1][x+0] && this->BO[n][y+1][x+1] && this->BO[n][y+1][x+2] && this->BO[n][y+1][x+3] && this->BO[n][y+1][x+4] && 
			this->BO[n][y+2][x+0] && this->BO[n][y+2][x+1] && this->BO[n][y+2][x+2] && this->BO[n][y+2][x+3] && this->BO[n][y+2][x+4] && 
			this->BO[n][y+3][x+0] && this->BO[n][y+3][x+1] && this->BO[n][y+3][x+2] && this->BO[n][y+3][x+3] && this->BO[n][y+3][x+4] && 
			this->BO[n][y+4][x+0] && this->BO[n][y+4][x+1] && this->BO[n][y+4][x+2] && this->BO[n][y+4][x+3] && this->BO[n][y+4][x+4] && 
			this->BO[n][y+5][x+0] && this->BO[n][y+5][x+1] && this->BO[n][y+5][x+2] && this->BO[n][y+5][x+3] && this->BO[n][y+5][x+4] && 
			this->BO[n][y+6][x+0] && this->BO[n][y+6][x+1] && this->BO[n][y+6][x+2] && this->BO[n][y+6][x+3] && this->BO[n][y+6][x+4] && 
			this->BO[n][y+7][x+0] && this->BO[n][y+7][x+1] && this->BO[n][y+7][x+2] && this->BO[n][y+7][x+3] && this->BO[n][y+7][x+4])
		{
			return TRUE;
		}
		break;
	case CLOCK7:
		if (this->BO[n][y+0][x+0] && this->BO[n][y+1][x+0] && this->BO[n][y+2][x-1] && this->BO[n][y+2][x+0] && this->BO[n][y+3][x-1] && 
			this->BO[n][y+3][x+0] && this->BO[n][y+4][x-2] && this->BO[n][y+4][x-1] && this->BO[n][y+4][x+0] && this->BO[n][y+5][x-2] && 
			this->BO[n][y+5][x-1] && this->BO[n][y+6][x-3] && this->BO[n][y+6][x-2] && this->BO[n][y+6][x-1] && this->BO[n][y+7][x-3] && 
			this->BO[n][y+7][x-2] && this->BO[n][y+8][x-4] && this->BO[n][y+8][x-3] && this->BO[n][y+8][x-2] && this->BO[n][y+9][x-4] && 
			this->BO[n][y+9][x-3] && this->BO[n][y+10][x-5] && this->BO[n][y+10][x-4] && this->BO[n][y+10][x-3] && this->BO[n][y+11][x-5] && 
			this->BO[n][y+11][x-4] && this->BO[n][y+12][x-5] && this->BO[n][y+12][x-4] && this->BO[n][y+13][x-5] && this->BO[n][y+14][x-5])
		{
			return TRUE;
		}
		break;
	case CLOCK8:
		if (this->BO[n][y+0][x+0] && this->BO[n][y+1][x-1] && this->BO[n][y+1][x+0] && this->BO[n][y+2][x-2] && this->BO[n][y+2][x-1] && 
			this->BO[n][y+2][x+0] && this->BO[n][y+3][x-3] && this->BO[n][y+3][x-2] && this->BO[n][y+3][x-1] && this->BO[n][y+3][x+0] && 
			this->BO[n][y+4][x-4] && this->BO[n][y+4][x-3] && this->BO[n][y+4][x-2] && this->BO[n][y+4][x-1] && this->BO[n][y+4][x+0] && 
			this->BO[n][y+5][x-5] && this->BO[n][y+5][x-4] && this->BO[n][y+5][x-3] && this->BO[n][y+5][x-2] && this->BO[n][y+5][x-1] && 
			this->BO[n][y+6][x-5] && this->BO[n][y+6][x-4] && this->BO[n][y+6][x-3] && this->BO[n][y+6][x-2] && this->BO[n][y+7][x-5] && 
			this->BO[n][y+7][x-4] && this->BO[n][y+7][x-3] && this->BO[n][y+8][x-5] && this->BO[n][y+8][x-4] && this->BO[n][y+9][x-5])
		{
			return TRUE;
		}
		break;
	case CLOCK9:
		if (this->BO[n][y+0][x-7] && this->BO[n][y+0][x-6] && this->BO[n][y+0][x-5] && this->BO[n][y+0][x-4] && this->BO[n][y+0][x-3] && 
			this->BO[n][y+0][x-2] && this->BO[n][y+0][x-1] && this->BO[n][y+0][x+0] && this->BO[n][y+1][x-7] && this->BO[n][y+1][x-6] && 
			this->BO[n][y+1][x-5] && this->BO[n][y+1][x-4] && this->BO[n][y+1][x-3] && this->BO[n][y+1][x-2] && this->BO[n][y+1][x-1] && 
			this->BO[n][y+1][x+0] && this->BO[n][y+2][x-7] && this->BO[n][y+2][x-6] && this->BO[n][y+2][x-5] && this->BO[n][y+2][x-4] && 
			this->BO[n][y+2][x-3] && this->BO[n][y+2][x-2] && this->BO[n][y+2][x-1] && this->BO[n][y+2][x+0] && this->BO[n][y+3][x-7] && 
			this->BO[n][y+3][x-6] && this->BO[n][y+3][x-5] && this->BO[n][y+3][x-4] && this->BO[n][y+3][x-3] && this->BO[n][y+3][x-2] && 
			this->BO[n][y+3][x-1] && this->BO[n][y+3][x+0] && this->BO[n][y+4][x-7] && this->BO[n][y+4][x-6] && this->BO[n][y+4][x-5] && 
			this->BO[n][y+4][x-4] && this->BO[n][y+4][x-3] && this->BO[n][y+4][x-2] && this->BO[n][y+4][x-1] && this->BO[n][y+4][x+0])
		{
			return TRUE;
		}
		break;
	case CLOCK10:
		if (this->BO[n][y-9][x-5] && this->BO[n][y-8][x-5] && this->BO[n][y-8][x-4] && this->BO[n][y-7][x-5] && this->BO[n][y-7][x-4] && 
			this->BO[n][y-7][x-3] && this->BO[n][y-6][x-5] && this->BO[n][y-6][x-4] && this->BO[n][y-6][x-3] && this->BO[n][y-6][x-2] && 
			this->BO[n][y-5][x-5] && this->BO[n][y-5][x-4] && this->BO[n][y-5][x-3] && this->BO[n][y-5][x-2] && this->BO[n][y-5][x-1] && 
			this->BO[n][y-4][x-4] && this->BO[n][y-4][x-3] && this->BO[n][y-4][x-2] && this->BO[n][y-4][x-1] && this->BO[n][y-4][x+0] && 
			this->BO[n][y-3][x-3] && this->BO[n][y-3][x-2] && this->BO[n][y-3][x-1] && this->BO[n][y-3][x+0] && this->BO[n][y-2][x-2] && 
			this->BO[n][y-2][x-1] && this->BO[n][y-2][x+0] && this->BO[n][y-1][x-1] && this->BO[n][y-1][x+0] && this->BO[n][y+0][x+0])
		{
			return TRUE;
		}
		break;
	case CLOCK11:
		if (this->BO[n][y-14][x-5] && this->BO[n][y-13][x-5] && this->BO[n][y-12][x-5] && this->BO[n][y-12][x-4] && this->BO[n][y-11][x-5] &&
			this->BO[n][y-11][x-4] && this->BO[n][y-10][x-5] && this->BO[n][y-10][x-4] && this->BO[n][y-10][x-3] && this->BO[n][y-9][x-4] &&
			this->BO[n][y-9][x-3] && this->BO[n][y-8][x-4] && this->BO[n][y-8][x-3] && this->BO[n][y-8][x-2] && this->BO[n][y-7][x-3] && 
			this->BO[n][y-7][x-2] && this->BO[n][y-6][x-3] && this->BO[n][y-6][x-2] && this->BO[n][y-6][x-1] && this->BO[n][y-5][x-2] && 
			this->BO[n][y-5][x-1] && this->BO[n][y-4][x-2] && this->BO[n][y-4][x-1] && this->BO[n][y-4][x+0] && this->BO[n][y-3][x-1] && 
			this->BO[n][y-3][x+0] && this->BO[n][y-2][x-1] && this->BO[n][y-2][x+0] && this->BO[n][y-1][x+0] && this->BO[n][y+0][x+0])
		{
			return TRUE;
		}
		break;
Default:
		break;
	}
	
	
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//功能：用来判断在指定区域内是否有指定 比划的线条 
//参数： int iclock 斜率
//sx xy 原坐标 dx dy 目标坐标 这两个点形成一个矩形区域 
//n 用来判断第几个 数字阵列 
//////////////////////////////////////////////////////////////////////////
BOOL DealPic::InZoneRich(int n,int iclock,int sx,int xy,int dx,int dy,OUT int *osx,OUT int *osy, OUT int *odx,OUT int *ody)
{
	int x = sx;
	int y = xy;
	while (y <= dy )
	{
		while (x <= dx)
		{
			if (this->IsLine(n,iclock,x,y))
			{
				*osx = x;
				*osy = y;
				switch (iclock)
				{
				case CLOCK0:
					*odx = x+4;
					*ody = y-7;
					break;
				case CLOCK1:
					*odx = x+5;
					*ody = y-14;
					break;
				case CLOCK2:
					*odx = x+5;
					*ody = y-9;
					break;
				case CLOCK3:
					*odx = x+7;
					*ody = y-4;
					break;
				case CLOCK4:
					*odx = x+5;
					*ody = y+9;
					break;
				case CLOCK5:
					*odx = x+5;
					*ody = y+14;
					break;
				case CLOCK6:
					*odx = x+4;
					*ody = y+7;
					break;
				case CLOCK7:
					*odx = x-5;
					*ody = y+14;
					break;
				case CLOCK8:
					*odx = x-5;
					*ody = y+9;
					break;
				case CLOCK9:
					*odx = x-7;
					*ody = y+4;
					break;
				case CLOCK10:
					*odx = x-5;
					*ody = y-9;
					break;
				case CLOCK11:
					*odx = x-5;
					*ody = y-14;
					break;
				default:
					break;

				}
				return TRUE;
			}
			x++;
		}
		x = sx;
		y++;
	}
	return FALSE;
}