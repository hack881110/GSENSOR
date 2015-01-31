// OpenGL.cpp: implementation of the OpenGL class.
//程序设计：唐明理	2005.2
//E_mail cqtml@163.com
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
#include "OpenGL.h"
#include "DealUartData.h"
//////////////////////////////////////////////////////////////////////
extern HWND	hWnd;
extern HDC		hDC;		// GDI设备句柄,将窗口连接到 GDI( 图形设备接口)
GLfloat	cnt1=0;				// 1st Counter Used To Move Text & For Coloring
GLfloat	cnt2=0;				// 2nd Counter Used To Move Text & For Coloring
extern int		Width;// 窗口宽
extern int		Height;// 窗口高

extern long long Rectest;
extern long long Dealtest;

extern int Perspective;//透视
extern int Orthogonal;//正交
//////////////////////////////////////////////////////////////////////
int iCull = 0;
int iOutline = 0;
int iDepth = 0;

void ProcessMenu(int value)
{
	switch(value)
	{
	case 1:
		iDepth = !iDepth;
		break;

	case 2:
		iCull = !iCull;
		break;

	case 3:
		iOutline = !iOutline;
	default:
		break;
	}

	glutPostRedisplay();
}

OpenGL::OpenGL()
{
}
OpenGL::~OpenGL()
{	CleanUp();
}
BOOL OpenGL::SetupPixelFormat(HDC hDC0)//检测安装OpenGL
{
	int nPixelFormat;					  // 象素点格式
	hDC=hDC0;
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
		1,                                // 版本号 
		PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
		PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
		PFD_DOUBLEBUFFER,                 // 双缓存模式 
		PFD_TYPE_RGBA,                    // RGBA 颜色模式 
		16,                               // 24 位颜色深度 
		0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
		0,                                // 没有非透明度缓存 
		0,                                // 忽略移位位 
		0,                                // 无累加缓存 
		0, 0, 0, 0,                       // 忽略累加位 
		16,                               // 32 位深度缓存     
		0,                                // 无模板缓存 
		0,                                // 无辅助缓存 
		PFD_MAIN_PLANE,                   // 主层 
		0,                                // 保留 
		0, 0, 0                           // 忽略层,可见性和损毁掩模 
	}; 
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{ 
		MessageBox(NULL,TEXT("没找到合适的显示模式"),TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	SetPixelFormat(hDC,nPixelFormat,&pfd);//设置当前设备的像素点格式
	hRC = wglCreateContext(hDC);          //获取渲染描述句柄
	wglMakeCurrent(hDC, hRC);             //激活渲染描述句柄
	/*
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Toggle depth test",1);
	glutAddMenuEntry("Toggle cull backface",2);
	glutAddMenuEntry("Toggle outline back",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	*/
	m_baiscobj=new baiscobj();
	//m_baiscobj->light0();

	m_bsipic =new bsipic();
	m_Font = new CGLFont();

	Perspective=1;
	iDepth=1;
	iCull=1;
	
	return TRUE;
}
void OpenGL::init(int Width, int Height)
{	

	if(Perspective)
	{
		glViewport(0,0,Width,Height);			// 设置OpenGL视口大小。	
		glMatrixMode(GL_PROJECTION);			// 设置当前矩阵为投影矩阵。
		glLoadIdentity();						// 重置当前指定的矩阵为单位矩阵
		gluPerspective							// 设置透视图
			( 45.0f,							// 透视角设置为 45 度
			(GLfloat)Width/(GLfloat)Height,	// 窗口的宽与高比
			0.1f,								// 视野透视深度:近点1.0f
			100.0f							// 视野透视深度:始点0.1f远点1000.0f
			);
		// 这和照象机很类似，第一个参数设置镜头广角度，第二个参数是长宽比，后面是远近剪切。
		glMatrixMode(GL_MODELVIEW);				// 设置当前矩阵为模型视图矩阵
		glLoadIdentity();						// 重置当前指定的矩阵为单位矩阵

	}
	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	//glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	//glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	//glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	else if(Orthogonal)
	{
		GLfloat nRange=2.0f;
		glViewport(0,0,Width, Height); //按照窗体大小制作OpenGL屏幕
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (Width <= Height)
			glOrtho(-nRange, nRange, -nRange * (GLfloat)Height/(GLfloat)Width, nRange * (GLfloat)Height/(GLfloat)Width, -nRange, nRange);
		else
			glOrtho(-nRange*(GLfloat)Width/(GLfloat)Height, nRange*(GLfloat)Width/(GLfloat)Height, -nRange, nRange, -nRange, nRange);
		glMatrixMode(GL_MODELVIEW);				// 设置当前矩阵为模型视图矩阵
		glLoadIdentity();						// 重置当前指定的矩阵为单位矩阵

	}

	pHeadofRx_Buffer=Rx_buffer;
	pTailofRx_Buffer=Rx_buffer;

	BuildFont();										// Build The Font


	//====================================================
}
void OpenGL::Render()//OpenGL图形处理
{	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			 // 设置刷新背景色
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// 刷新背景
	glLoadIdentity();								 // 重置当前的模型观察矩阵
	//glEnable(GL_BLEND);
	//glBendFunc(GL_SRC_ALPHA，GL_ONE_MINUS_SRC_ALPHA);
	//glHint(GL_LINE_SMOOTH,GL_DONT_CARE);
	//glLineWidth(1.5);

	if(iCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// Enable depth testing if flag is set
	if(iDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	// Draw back side as a polygon only, if flag is set
	if(iOutline)
		glPolygonMode(GL_BACK,GL_LINE);
	else
		glPolygonMode(GL_BACK,GL_FILL);
	//
	
	m_baiscobj->DisplayScene();
	play();
	/*
	m_baiscobj->DrawGround();
	m_baiscobj->picter(MAP+10,0,-MAP);
	m_baiscobj->airplane(MAP+50,15,-MAP);
	*/
	
	glFlush();										 // 更新窗口
	SwapBuffers(hDC);								 // 切换缓冲区
		
}
void OpenGL::CleanUp()
{	
	wglMakeCurrent(hDC, NULL);                       //清除OpenGL
	wglDeleteContext(hRC);                           //清除OpenGL
}
void OpenGL::play()
{	
	
	float k;
	if(Height==0)
		Height=1;
	if(Width==0)
		Width=1;
	if(Height>Width)
		k=Height/Width;
	else
		k=Width/Height;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(0.0f,0.0f,-10.0f);						// Move One Unit Into The Screen
	//glColor3f(0.0,0.5,0.5);

	/*
		一般定义载体的右、前、上三个方向构成右手系，绕向前(z)的轴旋转就是横滚角，绕向右的轴旋转就是俯仰角(x)，绕向上的轴旋转就是航向角(y)。
		
		Pitch  俯仰  x
		Yaw    航向  y
		Roling 横滚  z

	*/
	int wid=GetSystemMetrics(SM_CXSCREEN);		// 获取当前屏幕宽
	int hei=GetSystemMetrics(SM_CYSCREEN);		// 获取当前屏幕高
	if(Rectest!=0)
	Dealtest++;
	glRasterPos2f(-6*k,4*k-0.5);
	glPrint("Pitch Angle(X): %7.2f", k2*pitch);	// Print GL Text To The Screen
	glRasterPos2f(-6*k,4*k-1);
	glPrint("Yaw Angle(Y): %7.2f", k1*yaw);	// Print GL Text To The Screen
	glRasterPos2f(-6*k,4*k-1.5);
	glPrint("Roling  Angle(Z): %7.2f", k3*roll);	// Print GL Text To The Screen
	
	glRasterPos2f(-6*k,4*k-2);
	glPrint("Rectest: %d", Rectest);	// Print GL Text To The Screen
	glRasterPos2f(-6*k,4*k-2.5);
	glPrint("Dealtest: %d", Dealtest);	// Print GL Text To The Screen
	//glColor3f(1.0,0.0,0.0);
	
	//glutSolidSphere(1.0, 20, 16);
	//
	//glTranslatef(5.0f,0.0f,-10.0f);						// Move One Unit Into The Screen
	//m_baiscobj->DrawGround();
	m_baiscobj->cube(2,2,0.7,1);
		//m_baiscobj->Box(2,1,0.5);
	//glLoadIdentity();									// Reset The Current Modelview Matrix
	//glTranslatef(0.0f,0.0f,-10.0f);						// Move One Unit Into The Screen


}
/*
hwnd = CreateWindow( 

	WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX& ~WS_THICKFRAME搜索,	// window style,禁止最大化，禁止改变窗口大小。这是第三个参数

	1000,	// initial x size//这是第五个参数 这里面的数值就是你要设的窗口大小
	750,	// initial y size
	）
	*/


