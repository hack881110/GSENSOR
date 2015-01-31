#include "windows.h"
#include "time.h"
#include "math.h"
#include "Chart.h"

#define MAX_LOADSTRING 100


#ifdef _DEBUG
//
#if defined(_UNICODE) || defined(UNICODE)
#pragma comment(lib, "PlotDll_ud.lib")
#else
#pragma comment(lib, "PlotDll_d.lib")
#endif
//
#else
//
#if defined(_UNICODE) || defined(UNICODE)
#pragma comment(lib, "PlotDll_u.lib")
#else
#pragma comment(lib, "PlotDll.lib")
#endif
//
#endif

#define ID_REALTIME_START               32771
#define ID_REALTIME_STOP                32772

 CChart chart;


#define TWOPI  (2*3.14159)

POINT CoordinateSystem[4];
POINT RandData[10001]={0};
int          cxClient, cyClient ;
static HPEN hpenSys,hpenRoll,hpenPitch,hpenYaw;

#define ID_TIMER_1S 0x00001000
VOID CALLBACK TimerProc(HWND,UINT,UINT,DWORD);


int CurrentX,CurrentY;
void DrawBezier (HDC hdc, POINT apt[])
{
	PolyBezier (hdc, apt, 4) ;
	MoveToEx (hdc, apt[0].x, apt[0].y, NULL) ;
	LineTo   (hdc, apt[1].x, apt[1].y) ;

	MoveToEx (hdc, apt[2].x, apt[2].y, NULL) ;
	LineTo   (hdc, apt[3].x, apt[3].y) ;
}



void Draw_CoordinateSystem(HDC hdc)
{
	SelectObject(hdc,hpenSys);

	CoordinateSystem[0].x=40;
	CoordinateSystem[0].y=20;
	MoveToEx (hdc, CoordinateSystem[0].x, CoordinateSystem[0].y, NULL) ;
	CoordinateSystem[1].x=40;
	CoordinateSystem[1].y=cyClient-20;
	LineTo(hdc,CoordinateSystem[1].x,CoordinateSystem[1].y);
	CoordinateSystem[2].x=cxClient-40;
	CoordinateSystem[2].y=cyClient-20;
	MoveToEx (hdc, CoordinateSystem[1].x, CoordinateSystem[1].y, NULL) ;
	LineTo(hdc,CoordinateSystem[2].x,CoordinateSystem[2].y);

	for(int i=0;i<5;i++)
	{
		TCHAR buf[10];
		int x,y;
		x=10;
		y=(cyClient-60)/4;
		wsprintf(buf,TEXT("%d"),(i)*90);
		TextOut(hdc,x,cyClient-y*i-20,buf,lstrlen(buf));
	}
	for(int i=0;i<101;i++)
	{
		int x,y;
		x=(cxClient-40)/100*i+40;
		y=(cyClient-20);
		MoveToEx (hdc,x, y, NULL) ;
		if(i%10==0)
		{
			LineTo(hdc,x,y-15);
		}
		else
		{
			LineTo(hdc,x,y-10);
		}
		

	}



//	Polyline(hdc,CoordinateSystem,3);
}


int temptest=0;
void CALLBACK TimerProc(HWND hwnd,UINT message, UINT iTimerID,DWORD dwTimer)
{
	HDC hdc;
	int tempx,tempy;
	for(int i=0;i<100;i++)
	{
		temptest++;
		srand(time(NULL));
		
		tempx=(cxClient-temptest%800);
		tempy=(cyClient-temptest%50);

		//temp=rand()%10/10;
	//	RandData[i].x =( i * (cxClient-40)/ 100+40);
	//	RandData[i].y = (int) ((cyClient-40) / 2 * (1 - sin (TWOPI * i / 100)))+20 ;

		//.x= (cxClient-40)/100*i+40;
		//.y = (cyClient-20)/360*rand()%360+20-i;
		RandData[i].x =( i * (tempx)/ 100+40);
		RandData[i].y = (int) ((tempy) / 2 * (1 - sin (TWOPI * i / 100)))+20 ;
	}
	SendMessage(hwnd,WM_PAINT,NULL,NULL);
}


LRESULT CALLBACK WndProcDraw (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT apt[4] ;
	HDC          hdc ;

	int wmId, wmEvent;

	static unsigned int nCount;
	static bool bRun;
	static int nTimer;

	PAINTSTRUCT  ps ;

	switch (message)
	{
	case WM_COMMAND:
		wmId	 = LOWORD(wParam);
		wmEvent  = HIWORD(wParam);
		switch(wmId)
		{
		case ID_REALTIME_START:
			

			break;
		case ID_REALTIME_STOP:
			
			break;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
		break;

	case WM_SIZE:
		cxClient = LOWORD (lParam) ;
		cyClient = HIWORD (lParam) ;
		return 0 ;	
		
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MOUSEMOVE:
		//if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)
		{
		//	if (wParam & MK_LBUTTON)
			{
				CurrentX = LOWORD (lParam) ;
				CurrentY = HIWORD (lParam) ;
			}

			hdc = GetDC (hwnd) ;
			SelectObject (hdc,hpenYaw) ;
			
			ReleaseDC (hwnd, hdc);
		}
		return 0 ;
		
	case WM_ERASEBKGND:
		return 0;

	case WM_PAINT:
	
		RECT rt;
		hdc = BeginPaint(hwnd, &ps);
		// TODO: Add any drawing code here...
		
		GetClientRect(hwnd, &rt);
		//DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
		chart.OnDraw(hdc, rt);
		EndPaint(hwnd, &ps);
		break;


/*

		InvalidateRect (hwnd, NULL, TRUE) ;

		hdc = BeginPaint (hwnd, &ps) ;
		Draw_CoordinateSystem(hdc);
		SelectObject(hdc,hpenRoll);
		Polyline(hdc,RandData,100);
		MoveToEx (hdc, CurrentX, CurrentY-200, NULL) ;
	
	
		EndPaint (hwnd, &ps) ;
			*/
		return 0 ;
	case WM_CREATE:
		chart.SetType(kTypeXY);
		chart.SetUseLegend(true);
		chart.SetAxisTitle(_T("时间(分)"), 1);
		chart.SetAxisTitle(_T("角度(度)"), 0);
		chart.SetTitle(_T("九轴角度实时变化图"));

		nCount = 0;
		bRun = false;
		nTimer = 0;

		srand( (unsigned)time( NULL ) );
		nTimer =SetTimer(hwnd,1,20,0);
		bRun=true;

		/*

		hpenSys=CreatePen(PS_SOLID,1,RGB(255,0,0));
		hpenPitch=CreatePen(PS_DASH,1,RGB(0,255,125));
		hpenRoll=CreatePen(PS_DASH,1,RGB(0,135,125));
		hpenYaw=CreatePen(PS_DASH,1,RGB(125,20,125));
		SetTimer(hwnd,ID_TIMER_1S,100,TimerProc);
		*/
		break;

	case WM_TIMER:

		if(bRun)
			{
				double Pi = 3.1415926536;

				double x, y1, y2, y3;
				nCount++;
				x = nCount/10.0;
				y1 = 20.0 * sin(2.0*Pi/400.0*nCount) + 40.0 + (2.0*rand()/RAND_MAX-1.0);
				y2 = 20.0 + (2.0*rand()/RAND_MAX-1.0)/2.0;
				y3 = 40.0 + (3.0*rand()/RAND_MAX-1.0)/2.0;
/*				if(nCount == 1)
				{
					double pX[1], pY[1];
					pX[0] = x;
					pY[0] = y1;
					chart.AddCurve(pX, pY, 1);
					pY[0] = y2;
					chart.AddCurve(pX, pY, 1);
					chart.SetDataTitle(_T("加热温度"), 0);
					chart.SetDataTitle(_T("环境温度"), 1);
					break;
				}*/
				
				chart.AddPoint2D(x, y1, 0);
				chart.AddPoint2D(x, y2, 1);
				chart.AddPoint2D(x, y3, 2);
				if(nCount == 1)
				{
					chart.SetDataTitle(_T("Pitch  俯仰角"), 0);
					chart.SetDataTitle(_T("Yaw    航向角"), 1);
					chart.SetDataTitle(_T("Roling 横滚角"), 2);
				}

				RECT rt;
				GetClientRect(hwnd, &rt);
				InvalidateRect(hwnd, &rt, TRUE);
			}

		break;
	case WM_DESTROY:
		DestroyWindow(hwnd);
		//PostQuitMessage (0) ;
		return 0 ;
	case WM_CLOSE:
		if(nTimer>0)
		{
			KillTimer(hwnd, nTimer);
			nTimer = 0;
		}
		bRun = false;

		KillTimer(hwnd,ID_TIMER_1S);
		DestroyWindow(hwnd);
		return 0;
	default:
		break;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
