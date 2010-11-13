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
//�������ֵ����еı���
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
//���ܣ���hwnd�ƶ��Ľ�������ʾ��n������
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
//���ܣ���������ͼƬ ������ŵ�NUMBER��
//////////////////////////////////////////////////////////////////////////
BOOL DealPic::DealNum()
{
	this->DealFirst();
	return true;
}
//////////////////////////////////////////////////////////////////////////
//���ܣ� ��λͼͼƬ����һ���Դ��� ���еĴ���������������� �����ĺ����ڽ��з����� 
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
	//������ȥ�������ڲ��ĸ��ŵ�  ��һЩָ���ĵ� ����ȥ��
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
//���� �����ж�һ���������е����Ǽ�
int  DealPic::DealOne(int n)
{
	BOOL Ret[10] = {false};
	int iRet = 0;
	int i = 0;
	while (i < 10) // �Ƚ���һ�α��� �������Ǽ������� ���ƶ����
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
	//��������Ż� ������ڶ����ʶ�ȸߵ����� �����Ż����� �����Ҫ����������ζԱȵľ����ܽ� ��Ҫ��������������

	return iRet;
}

//////////////////////////////////////////////////////////////////////////
//����n��ʾ Ҫ�Ƚϵĵڼ������ǲ���0
//���ܣ��ж��ƶ���ͼƬ�ǲ���0
//////////////////////////////////////////////////////////////////////////
BOOL DealPic::IsZero(int n)
{
	
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
//���ܣ��ж� �ƶ��������Χ��û��iclock�ƶ�����б��ֱ�� �������Ĭ����4 
//������
//		int *ox   �����ֱ�� ����ֱ����һ�˵�x����
//		int *oy   �����ֱ�� ����ֱ����һ�˵�y����
//		int x     ָ�������x����
//		int y	  ָ�������y����
//		int iclock  ָ����б�ķ��� �������������������� �ú�clock0-clock11����ʾ0�㵽11��ķ���
//		int n	  ������ʾ�жϵڼ�����
//////////////////////////////////////////////////////////////////////////

BOOL DealPic::IsLine(int n, int iclock, IN int x,IN int y, OUT int *ox,OUT int *oy)
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
		if (this->BO[n][y][x] && this->BO[n][y][x] && this->BO[n][y][x] && )
		{
		}
		break;
	case CLOCK3:
		break;
	case CLOCK4:
		break;
	case CLOCK5:
		break;
	case CLOCK6:
		break;
	case CLOCK7:
		break;
	case CLOCK8:
		break;
	case CLOCK9:
		break;
	case CLOCK10:
		break;
	case CLOCK11:
		break;
Default:
		break;
	}
	
	
	return true;
}