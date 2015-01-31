// OpenGL的程序框架.cpp : Defines the entry point for the application.
//程序设计：唐明理	2005.2
//E_mail cqtml@163.com
#include "windows.h"
#include "OpenGL.h"
#include "Serial.h"
#include "DealUartData.h"
#include "common.h"
#include "DrawGrp.h"
//////////////////////////////////////////////////////////

OpenGL* m_OpenGL;
CSerial *myport;
HDC		hDC;		// GDI设备句柄,将窗口连接到 GDI( 图形设备接口)
HGLRC	hRC=NULL;	// 渲染描述句柄,将OpenGL调用连接到设备描述表 
HWND	hWnd=NULL;	// 保存 Windows 分配给程序的窗口句柄
HWND	hWndPort=NULL;	// 保存 Windows 分配给程序的窗口句柄
HWND	hwndDraw=NULL;
int		Width = 850;// 窗口宽
int		Height= 600;// 窗口高
int		bits  = 16;	// 颜色深度

HINSTANCE hInstPort;
 HFONT hFont;


 long long Rectest=0;
 long long Dealtest=0;

#define IDM_FILE_Config  40001  
#define IDM_FILE_Close 40002  
#define IDM_EDIT_COPY 40003  
#define IDM_EDIT_CUT  40004  
#define IDM_EDIT_Cull 40005
#define IDM_EDIT_Depth 40006
#define IDM_EDIT_Outline 40007
#define IDM_FILE_Orthogonal 40008
#define IDM_FILE_Perspective 40009

#define IDM_FILE_Graph		40010
//#define IDM_EDIT_Cull 40008

#define IDC_COMBO1 0x9001
#define IDC_COMBO2 0x9002
#define IDC_COMBO3 0x9003
#define IDC_COMBO4 0x9004
#define IDC_COMBO5 0x9005
#define buttonOK  0x0005
#define buttonCancel 0x0006

static int nid;
 int Perspective;//透视
 int Orthogonal;//正交
////////////////////////////////
 //定义窗口类名
 static TCHAR MainWindow[]=TEXT("MainWindow");
 static TCHAR szAppName[] = TEXT ("SineWave") ;
 extern LRESULT WINAPI MainProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam );// 主界面 消息处理


 extern BOOL CALLBACK AboutDlgProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
 extern BOOL CALLBACK AnalyseProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
 extern BOOL CALLBACK ConfigProc2(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
 HINSTANCE hInst_S;
 HWND hDlgModeless ;
 HWND hDlgModelessGraph ;


 extern HMENU MenuCreate(void);
 extern void MainLoop();

 int		nX=0,nY=0;
 

INT WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInstance,LPSTR szCmdLine,INT iCmdShow)// WinMain程序入口
{   // 注册窗口类
	bool fullScreen =TRUE;
	DWORD	dwExStyle;		// Window 扩展风格
	DWORD	dwStyle;		// Window 窗口风格
	HMENU hMenu;

//	RECT	windowRect;		// 窗口尺寸
	
	//配置窗口属性
	{	
		dwExStyle=WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;	// 使窗口具有3D外观
		dwStyle=WS_OVERLAPPEDWINDOW;	// 使用标准窗口//禁止最大化  固定大小& ~WS_MAXIMIZEBOX& ~WS_THICKFRAME
		//WS_OVERLAPPEDWINDOW是有标题栏,窗口菜单,最大、小化按钮和可调整尺寸的窗口
		int wid=GetSystemMetrics(SM_CXSCREEN);		// 获取当前屏幕宽
		int hei=GetSystemMetrics(SM_CYSCREEN);		// 获取当前屏幕高
		nX=(wid-Width)/2;
		nY=(hei-Height)/2;			// 计算窗口居中用
	//	windowRect.
	}
	//根据窗口风格来调整窗口尺寸达到要求的大小
	//AdjustWindowRectEx(&windowRect,dwStyle,FALSE,dwExStyle);
	//注册主窗口								
	
	/*
    WNDCLASSEX wc = { sizeof(WNDCLASSEX),
						CS_CLASSDC, MsgProc, 0L, 0L, 
                      GetModuleHandle(NULL), NULL,  LoadCursor( NULL, IDC_ARROW ), NULL, NULL,
                      (LPCWSTR)cc, NULL };
	*/	
	hInst_S=hInst;

	WNDCLASSEX wc;
	wc.cbSize=  sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc =MainProc;
	wc.cbClsExtra =0L;
	wc.cbWndExtra =0L;
	wc.hInstance =GetModuleHandle(NULL);
	wc.hIcon =LoadIcon(hInst,TEXT("IDI_ICON1") );
	wc.hCursor =LoadCursor(NULL,IDC_ARROW);
	//wc.hbrBackground =(HBRUSH) GetStockObject( WHITE_BRUSH );
	wc.hbrBackground =NULL;
	wc.lpszMenuName =NULL;
	wc.lpszClassName =MainWindow;
	wc.hIconSm=NULL;
	  
    RegisterClassEx( &wc );//Main Window
	

	wc.style         =  CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; ;
	wc.lpfnWndProc   = WndProcDraw ;
	wc.cbClsExtra    = 0 ;
	wc.cbWndExtra    = 0 ;
	wc.hInstance     = GetModuleHandle(NULL) ;
	wc.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wc.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wc.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wc.lpszMenuName  = NULL ;
	wc.lpszClassName = szAppName ;//Graphics Window
	
	RegisterClassEx( &wc );

	hMenu=MenuCreate();
	
	m_OpenGL=new OpenGL();



	hWnd = CreateWindowEx(dwExStyle,MainWindow,TEXT("政通电子V1.0"),
						  dwStyle|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
						  nX, nY,Width, Height,
						  NULL,hMenu,hInst,NULL);	// 创建窗口
	ShowWindow( hWnd, SW_SHOWDEFAULT );				// 显示窗口
	UpdateWindow( hWnd );							// 刷新窗口

	MainLoop();										// 进入消息循环
    return 0;
}

HMENU MenuCreate(void)
{

	HMENU hMenu = CreateMenu(); //主菜单,水平  

	HMENU hMenuPop = CreateMenu(); //下拉的菜单,垂直  
	AppendMenu(hMenuPop,MF_STRING,IDM_FILE_Config,TEXT("串口配置"));  
	AppendMenu(hMenuPop,MF_STRING,IDM_FILE_Close,TEXT("关闭串口")); 	
	AppendMenu(hMenu,MF_POPUP,(unsigned int)hMenuPop,TEXT("File"));  



	hMenuPop = CreateMenu();  
	AppendMenu(hMenuPop,MF_STRING,IDM_FILE_Perspective,TEXT("Perspective"));  
	AppendMenu(hMenuPop,MF_STRING,IDM_FILE_Orthogonal,TEXT("Orthogonal"));
	AppendMenu(hMenuPop,MF_STRING,IDM_EDIT_Cull,TEXT("iCull"));  
	AppendMenu(hMenuPop,MF_STRING,IDM_EDIT_Depth,TEXT("iDepth"));
	AppendMenu(hMenuPop,MF_STRING,IDM_EDIT_Outline,TEXT("iOutline"));  
	AppendMenu(hMenu,MF_POPUP,(unsigned int)hMenuPop,TEXT("Edit"));

	hMenuPop = CreateMenu();
	AppendMenu(hMenuPop,MF_STRING,IDM_FILE_Graph,TEXT("数据分析"));  	
	AppendMenu(hMenu,MF_POPUP,(unsigned int)hMenuPop,TEXT("Analyse")); 

	return hMenu;
}
void MainLoop()
{   MSG msg; 
    BOOL fMessage;
	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while(msg.message != WM_QUIT)	// 消息循环
	{
		
			
			 //PM_NOREMOVE：PeekMessage处理后，消息不从队列里除掉。
			//PM_REMOVE：PeekMessage处理后，消息从队列里除掉。
		fMessage = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE);
		if (hDlgModeless == 0 || !IsDialogMessage (hDlgModeless, &msg))
			{
					if(fMessage)				//有消息
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
					else 
						m_OpenGL->Render();	//无消息
			}
		

		
	}
 
     return ;
}



LRESULT WINAPI MainProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam )// 消息处理
{	
	
	switch(message)
	{
		case WM_COM_RECEIVE:
			{
	
				CHAR temp_rx_buffer[1024];
				int i=0;
			
				memset(temp_rx_buffer,0x00,sizeof(temp_rx_buffer));
				myport->ReadData(temp_rx_buffer,1,100);
				if(temp_rx_buffer[0]!='\0')
				{
					UART2_Get_IMU(temp_rx_buffer);
					Rectest++;
				}
				myport->Write(temp_rx_buffer,10);
				/*
				for(int i=0;i<10;i++)
				{
					*pTailofRx_Buffer++=temp_rx_buffer[i++];
					iEndFlag0fRx_Buffer++;
					if(pTailofRx_Buffer-Rx_buffer>=RX_BUFFER_SIZE)
					{
						pTailofRx_Buffer=Rx_buffer;

					}
				}
				
				*/
				
				//myport->Write(RecBuff,sizeof(RecBuff));
			}
			break;
		case WM_CREATE:						// 建立窗口

		  //  hInst_S = ((LPCREATESTRUCT) lParam)->hInstance ;

			hDC = GetDC(hWnd);				// 获取当前窗口的设备句柄
			m_OpenGL->SetupPixelFormat(hDC);// 调用显示模式安装功能

			myport =new CSerial();
			/*
			{
				DWORD dwId;
				HANDLE m_hThread;
				m_hThread = CreateThread(NULL, 0, SerialDealData, NULL, 0, &dwId);
				if(m_hThread == NULL)
				{
				
					return FALSE;
				}
			}
			*/
			return 0;		break;
		case WM_CLOSE:						// 关闭窗口
			m_OpenGL->CleanUp();			// 结束处理
			PostQuitMessage(0);
		//	DestroyWindow(hWnd);
			return 0;		break;
		case WM_SIZE:						// 窗口尺寸变化


			Height = HIWORD(lParam);		// 窗口的高
			Width  = LOWORD(lParam);		// 窗口的宽

	

			if (Height==0)	Height=1;		// 防止被0 除
			m_OpenGL->init(Width,Height);
			
			return 0;		break;
		case WM_PAINT:
			{

			/*
				HDC         hdc ;
				PAINTSTRUCT ps ;
				RECT        rect ;
				hdc = BeginPaint (hWnd, &ps) ;

				GetClientRect (hWnd, &rect) ;

				DrawText (hdc, TEXT ("Hello, Windows 98!"), -1, &rect,
					DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;

				EndPaint (hWnd, &ps) ;
			*/	
			}
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				
			case IDM_FILE_Graph:
				//hDlgModeless=CreateDialog (hInst_S, TEXT ("GraphDialog"), hWnd, AnalyseProc) ;


				hwndDraw = CreateWindow (szAppName, TEXT ("数据分析"),
					WS_OVERLAPPEDWINDOW|WS_HSCROLL,
					CW_USEDEFAULT, CW_USEDEFAULT,
					CW_USEDEFAULT, CW_USEDEFAULT,
					NULL, NULL, NULL, NULL) ;
				ShowWindow( hwndDraw, SW_SHOWDEFAULT );				// 显示窗口
				UpdateWindow( hwndDraw );							// 刷新窗口
				//ShowWindow (hDlgModeless, SW_SHOW) ;
			
				break;
			case IDM_FILE_Config:
			//	ConfigLoop();
				//DialogLOOP();
				hDlgModeless=CreateDialog (hInst_S, TEXT ("ABOUTBOX2"), hWnd, ConfigProc2) ;
				break;
			case IDM_FILE_Close:
				{
					myport->Close();
					yaw=roll=pitch=0;
				}
				break;
				//MessageBox(hWnd,TEXT("动态菜单File里的Open"),TEXT("菜单"),MB_OK); break;  
			case IDM_EDIT_COPY:
				MessageBox(hWnd,TEXT("动态菜单Edit里的Copy"),TEXT("菜单"),MB_OK); break;  
			case IDM_EDIT_CUT:
				MessageBox(hWnd,TEXT("动态菜单Edit里的Cut"),TEXT("菜单"),MB_OK); break; 
			case IDM_FILE_Perspective:
				Orthogonal=1;
				Perspective=0;
				break;
		
			case IDM_FILE_Orthogonal:
				Orthogonal=0;
				Perspective=1;
				break;
			case IDM_EDIT_Depth:
				iDepth=!iDepth;
				break;
			case IDM_EDIT_Outline:
				iOutline=!iOutline;
				break;
			case IDM_EDIT_Cull:
				iCull=!iCull;
				break;
			default:
				break;
			}
			return 0 ;
		case WM_DESTROY:					// 退出消息
            PostQuitMessage(0);
            return 0;		break;
        case WM_KEYUP:						// 按ESC退出，全屏模式必需要加入的退出方式。
            switch (wParam)
            { case VK_ESCAPE:
					m_OpenGL->CleanUp();	// 结束处理
				    PostQuitMessage(0);
				    return 0;break;
            } 

		default:			break;
	}
	return (DefWindowProc(hWnd, message, wParam, lParam));
}

struct
{
     int     iStyle ;
     TCHAR * szText ;
}
button[] =
{
     CBS_DROPDOWNLIST,      TEXT ("端口号"),
     CBS_DROPDOWNLIST,      TEXT ("波特率"),
     CBS_DROPDOWN,          TEXT ("数据位"),
     CBS_DROPDOWN,		    TEXT ("校  验"),
     CBS_DROPDOWN,          TEXT ("停止位")
	 
} ;

#define NUM (sizeof button / sizeof button[0]) 
static HWND  hwndButton[NUM] ;
static HWND  statictext[NUM] ;
static HWND	 pushbutton[2];

char* ConvertLPWSTRToLPSTR (LPWSTR lpwszStrIn)  
{  
    LPSTR pszOut = NULL;  
    if (lpwszStrIn != NULL)  
    {  
        int nInputStrLen = wcslen (lpwszStrIn);  
  
        // Double NULL Termination  
        int nOutputStrLen = WideCharToMultiByte (CP_ACP, 0, lpwszStrIn, nInputStrLen, NULL, 0, 0, 0) + 2;  
        pszOut = new char [nOutputStrLen];  
  
        if (pszOut)  
        {  
            memset (pszOut, 0x00, nOutputStrLen);  
            WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, pszOut, nOutputStrLen, 0, 0);  
        }  
    }  
    return pszOut;  
}  


LRESULT CALLBACK DlgProc(HWND hwndDlg ,UINT uMsg ,WPARAM wParam ,LPARAM lParam) 
{ 
	
    switch(uMsg) 
    { 
    case WM_CREATE: 
//	 HWND       hwndParent, hCtrl ;
	//	 hCtrl =GetDlgItem(hwndDlg,IDC_COMBO1);
		 
		// ComboBox_AddString();
		// SendMessage (hwndList, LB_ADDSTRING, 0, (LPARAM) pVarName) ;
		// SetDlgItemInt(hwnd,IDC_COMBO1,1,true);
        break; 
    case WM_INITDIALOG: 
            OutputDebugString(TEXT("收到了WM_InitDialog消息\n")); 
            break; 
    case WM_COMMAND: 
        switch(LOWORD(wParam)) 
        { 
        case IDOK: 
            break; 
        case IDCANCEL: 
            DestroyWindow(hwndDlg); 
            //EndDialog(hwndDlg , 1); 
            return true; 
        } 
        break; 
        case WM_CLOSE: 
            DestroyWindow(hwndDlg); 
        //  EndDialog(hwndDlg , 0); 
            return true; 
        case WM_DESTROY: 
            OutputDebugString(TEXT("对话框即将被销毁\n")); 
            PostQuitMessage(0); 
            return true; 
        default: 
            break; 
 
    } 
}


BOOL CALLBACK AboutDlgProc (HWND hDlg, UINT message, 
                            WPARAM wParam, LPARAM lParam)
{
	HWND hCtrl[5];
     switch (message)
     {
	 case WM_INITDIALOG:

			hCtrl[0]=GetDlgItem(hDlg,IDC_COMBO1);
			hCtrl[1]=GetDlgItem(hDlg,IDC_COMBO2);
			hCtrl[2]=GetDlgItem(hDlg,IDC_COMBO3);
			hCtrl[3]=GetDlgItem(hDlg,IDC_COMBO4);
			hCtrl[4]=GetDlgItem(hDlg,IDC_COMBO5);

		   SendMessage(hCtrl[1],CB_ADDSTRING,0,(LPARAM)TEXT("115200"));      
		   SendMessage(hCtrl[1],CB_ADDSTRING,0,(LPARAM)TEXT("9600"));     
		   SendMessage(hCtrl[1],CB_SELECTSTRING,0,(LPARAM)TEXT("115200"));    

		   SendMessage(hCtrl[2],CB_ADDSTRING,0,(LPARAM)TEXT("8"));       
		   SendMessage(hCtrl[2],CB_SELECTSTRING,0,(LPARAM)TEXT("8"));   

		   SendMessage(hCtrl[3],CB_ADDSTRING,0,(LPARAM)TEXT("NONE"));  
		   SendMessage(hCtrl[3],CB_ADDSTRING,0,(LPARAM)TEXT("ODD"));     
		   SendMessage(hCtrl[3],CB_ADDSTRING,0,(LPARAM)TEXT("EVEN"));      
		   SendMessage(hCtrl[3],CB_SELECTSTRING,0,(LPARAM)TEXT("NONE"));   

		   SendMessage(hCtrl[4],CB_ADDSTRING,0,(LPARAM)TEXT("1"));   
		   SendMessage(hCtrl[4],CB_SELECTSTRING,0,(LPARAM)TEXT("1"));   

	 case WM_CREATE:
		 SetDlgItemText ( hDlg , LOWORD (wParam) ,TEXT("yundao") ) ;
		 break;
  
     case WM_COMMAND :
          switch (LOWORD (wParam))
          {
          case IDOK :
          case IDCANCEL :
               EndDialog (hDlg, 0) ;
               return TRUE ;
          }
          break ;
     }
     return FALSE ;
}


BOOL CALLBACK ConfigProc2(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	 static int   cxChar, cyChar ;
	 int i;
	switch (message)
	{

	case WM_INITDIALOG:
	case WM_CREATE:
		
	//	hDC = GetDC(hwnd);				// 获取当前窗口的设备句柄
				   			   
	//	SetBkColor(hDC,0x0000FF);


		//LoadBitmap(((LPCREATESTRUCT) lParam)->hInstance,TEXT("before.bmp"));
	    hFont=CreateFont(14, 0, 0, 0, 100, FALSE, FALSE, 0, 
                  GB2312_CHARSET, OUT_DEFAULT_PRECIS,
                  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                  DEFAULT_PITCH | FF_MODERN, TEXT("Arial" ));

        cxChar = LOWORD (GetDialogBaseUnits ()) ;
	    cyChar = HIWORD (GetDialogBaseUnits ()) ;
          for (i = 0 ; i <NUM  ; i++)
		  {
				
			    statictext[i] = CreateWindow ( TEXT("STATIC"), 
                                   button[i].szText,
                                   SS_CENTER | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 
                                   cxChar, cyChar * (1 + 2 * i),
                                   10 * cxChar, 7 * cyChar / 4,
                                   hwnd, (HMENU) i,
                                   NULL, NULL) ;
				SendMessage(statictext[i],WM_SETFONT,(WPARAM)hFont,MAKELPARAM(TRUE,0));
			//	SendMessage(statictext[i],WM_SETFONT,(WPARAM)hFont,1);  //设置控件字体  
                hwndButton[i] = CreateWindow ( TEXT("COMBOBOX"), 
                                   button[i].szText,
                                   WS_CHILD | WS_VISIBLE |WS_VSCROLL |WM_SETTEXT| WS_BORDER| button[i].iStyle, 
                                   cxChar+100, cyChar * (1 + 2 * i),
                                   15 * cxChar, 20 * cyChar / 4,
                                   hwnd, (HMENU) i,
                                   NULL, NULL) ;
					
		  }
		   SendMessage(hwndButton[1],CB_ADDSTRING,0,(LPARAM)TEXT("115200"));      
		   SendMessage(hwndButton[1],CB_ADDSTRING,0,(LPARAM)TEXT("9600"));     
		   SendMessage(hwndButton[1],CB_SELECTSTRING,0,(LPARAM)TEXT("115200"));    

		   SendMessage(hwndButton[2],CB_ADDSTRING,0,(LPARAM)TEXT("8"));       
		   SendMessage(hwndButton[2],CB_SELECTSTRING,0,(LPARAM)TEXT("8"));   

		   SendMessage(hwndButton[3],CB_ADDSTRING,0,(LPARAM)TEXT("NONE"));  
		   SendMessage(hwndButton[3],CB_ADDSTRING,0,(LPARAM)TEXT("ODD"));     
		   SendMessage(hwndButton[3],CB_ADDSTRING,0,(LPARAM)TEXT("EVEN"));      
		   SendMessage(hwndButton[3],CB_SELECTSTRING,0,(LPARAM)TEXT("NONE"));   

		   SendMessage(hwndButton[4],CB_ADDSTRING,0,(LPARAM)TEXT("1"));   
		   SendMessage(hwndButton[4],CB_SELECTSTRING,0,(LPARAM)TEXT("1"));   
		   

		  pushbutton[0] = CreateWindow ( TEXT("button"), 
                                   TEXT("确定"),
                                   WS_CHILD | WS_VISIBLE |BS_PUSHBUTTON , 
                                   cxChar+30, cyChar * (1 + 2 * 5.5),
                                   9 * cxChar, 6 * cyChar / 4,
                                   hwnd, NULL,
								  NULL, NULL) ;
		//  GetDlgItem(pushbutton[0],buttonOK);
		  SetWindowLong( pushbutton[0],GWL_ID,buttonOK);
		  SendMessage(pushbutton[0],WM_SETFONT,(WPARAM)hFont,MAKELPARAM(TRUE,0));
		  
		  pushbutton[1] = CreateWindow ( TEXT("button"), 
                                   TEXT("取消"),
                                   WS_CHILD | WS_VISIBLE| BS_PUSHBUTTON, 
                                   cxChar+130, cyChar * (1 + 2 * 5.5),
                                   9 * cxChar, 6 * cyChar / 4,
                                   hwnd, NULL,
                                  NULL, NULL) ; //
		   SetWindowLong( pushbutton[1],GWL_ID,buttonCancel);
		   SendMessage(pushbutton[1],WM_SETFONT,(WPARAM)hFont,MAKELPARAM(TRUE,0));

		//   GetDlgItem(pushbutton[1],buttonCancel);
		   HKEY hKey;
		  if(RegOpenKeyEx(  HKEY_LOCAL_MACHINE, TEXT("Hardware\\DeviceMap\\SerialComm"), NULL, KEY_READ, &hKey )   ==   ERROR_SUCCESS )   //打开串口注册表对应的键值   
			  {  
				  int i=0;  
				  TCHAR portName[256],commName[256];    
				  DWORD dwLong,dwSize;    
				  while(1)    
				  {    
					  dwLong   =   dwSize   =   sizeof(portName);    
					  if(RegEnumValue(hKey,    
						  i,    
						  portName,    
						  &dwLong,    
						  NULL,    
						  NULL,    
						  (PUCHAR)commName,    
						  &dwSize   )   ==   ERROR_NO_MORE_ITEMS )//   枚举串口    
						  break;    
					  SendMessage(hwndButton[0],CB_ADDSTRING,0,(LPARAM)commName);   // commName就是串口名字
					  SendMessage(hwndButton[0],CB_SELECTSTRING,0,(LPARAM)commName);   
					  i++;  
				  }  
			   
					 RegCloseKey(hKey);  
			  }
		  else
		  {
			MessageBox(hWnd,TEXT("无串口"),TEXT("菜单"),MB_OK);  
		  }
		

			  
		break;
		

		

	case WM_PAINT:		
		break;
	case WM_DESTROY:
		DestroyWindow(hwnd);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_SIZE:
		break;
	case WM_COMMAND:
		  switch(LOWORD(wParam)) 
        { 
        case buttonOK: 
			{
			//	char *buf;
					TCHAR szText[128] = {0};
					char *sztest;
					int index;
					index =(int )SendMessage(hwndButton[0], CB_GETCURSEL , 0, 0);				    
				    SendMessage(hwndButton[0], CB_GETLBTEXT , index, LPARAM(szText));			
					sztest=ConvertLPWSTRToLPSTR(szText);
					int port =atoi(&sztest[3]);
				
					
	
					index =(int )SendMessage(hwndButton[1], CB_GETCURSEL , 0, 0);				    
				    SendMessage(hwndButton[1], CB_GETLBTEXT , index, LPARAM(szText));
					sztest=ConvertLPWSTRToLPSTR(szText);
					int baudrate =atoi(sztest);
					//baudrate=strtod((char*)szText,NULL);
					myport->SetWnd(hWnd);
					myport->SetNotifyNum(1);
					myport->Open(port,baudrate);
					
					

					char buff[100]="hello port!";
					myport->Write(buff,sizeof(buff));
			}
			 // MessageBox(hWnd,TEXT("确定"),TEXT("菜单"),MB_OK); 
			  	DestroyWindow(hwnd);
            break; 
        case buttonCancel: 
			//MessageBox(hWnd,TEXT("取消"),TEXT("菜单"),MB_OK); 
			
			DestroyWindow(hwnd);
        
         
            return true; 
        } 

		break;
	 default:
		break;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}


