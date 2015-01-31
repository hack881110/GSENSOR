// OpenGL.cpp: implementation of the OpenGL class.
//������ƣ�������	2005.2
//E_mail cqtml@163.com
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
#include "OpenGL.h"
#include "DealUartData.h"
//////////////////////////////////////////////////////////////////////
extern HWND	hWnd;
extern HDC		hDC;		// GDI�豸���,���������ӵ� GDI( ͼ���豸�ӿ�)
GLfloat	cnt1=0;				// 1st Counter Used To Move Text & For Coloring
GLfloat	cnt2=0;				// 2nd Counter Used To Move Text & For Coloring
extern int		Width;// ���ڿ�
extern int		Height;// ���ڸ�

extern long long Rectest;
extern long long Dealtest;

extern int Perspective;//͸��
extern int Orthogonal;//����
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
BOOL OpenGL::SetupPixelFormat(HDC hDC0)//��ⰲװOpenGL
{
	int nPixelFormat;					  // ���ص��ʽ
	hDC=hDC0;
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
		1,                                // �汾�� 
		PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ 
		PFD_SUPPORT_OPENGL |              // ֧�� OpenGL 
		PFD_DOUBLEBUFFER,                 // ˫����ģʽ 
		PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ 
		16,                               // 24 λ��ɫ��� 
		0, 0, 0, 0, 0, 0,                 // ������ɫλ 
		0,                                // û�з�͸���Ȼ��� 
		0,                                // ������λλ 
		0,                                // ���ۼӻ��� 
		0, 0, 0, 0,                       // �����ۼ�λ 
		16,                               // 32 λ��Ȼ���     
		0,                                // ��ģ�建�� 
		0,                                // �޸������� 
		PFD_MAIN_PLANE,                   // ���� 
		0,                                // ���� 
		0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ 
	}; 
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{ 
		MessageBox(NULL,TEXT("û�ҵ����ʵ���ʾģʽ"),TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	SetPixelFormat(hDC,nPixelFormat,&pfd);//���õ�ǰ�豸�����ص��ʽ
	hRC = wglCreateContext(hDC);          //��ȡ��Ⱦ�������
	wglMakeCurrent(hDC, hRC);             //������Ⱦ�������
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
		glViewport(0,0,Width,Height);			// ����OpenGL�ӿڴ�С��	
		glMatrixMode(GL_PROJECTION);			// ���õ�ǰ����ΪͶӰ����
		glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����
		gluPerspective							// ����͸��ͼ
			( 45.0f,							// ͸�ӽ�����Ϊ 45 ��
			(GLfloat)Width/(GLfloat)Height,	// ���ڵĿ���߱�
			0.1f,								// ��Ұ͸�����:����1.0f
			100.0f							// ��Ұ͸�����:ʼ��0.1fԶ��1000.0f
			);
		// �������������ƣ���һ���������þ�ͷ��Ƕȣ��ڶ��������ǳ���ȣ�������Զ�����С�
		glMatrixMode(GL_MODELVIEW);				// ���õ�ǰ����Ϊģ����ͼ����
		glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����

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
		glViewport(0,0,Width, Height); //���մ����С����OpenGL��Ļ
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (Width <= Height)
			glOrtho(-nRange, nRange, -nRange * (GLfloat)Height/(GLfloat)Width, nRange * (GLfloat)Height/(GLfloat)Width, -nRange, nRange);
		else
			glOrtho(-nRange*(GLfloat)Width/(GLfloat)Height, nRange*(GLfloat)Width/(GLfloat)Height, -nRange, nRange, -nRange, nRange);
		glMatrixMode(GL_MODELVIEW);				// ���õ�ǰ����Ϊģ����ͼ����
		glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����

	}

	pHeadofRx_Buffer=Rx_buffer;
	pTailofRx_Buffer=Rx_buffer;

	BuildFont();										// Build The Font


	//====================================================
}
void OpenGL::Render()//OpenGLͼ�δ���
{	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			 // ����ˢ�±���ɫ
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// ˢ�±���
	glLoadIdentity();								 // ���õ�ǰ��ģ�͹۲����
	//glEnable(GL_BLEND);
	//glBendFunc(GL_SRC_ALPHA��GL_ONE_MINUS_SRC_ALPHA);
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
	
	glFlush();										 // ���´���
	SwapBuffers(hDC);								 // �л�������
		
}
void OpenGL::CleanUp()
{	
	wglMakeCurrent(hDC, NULL);                       //���OpenGL
	wglDeleteContext(hRC);                           //���OpenGL
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
		һ�㶨��������ҡ�ǰ�����������򹹳�����ϵ������ǰ(z)������ת���Ǻ���ǣ������ҵ�����ת���Ǹ�����(x)�������ϵ�����ת���Ǻ����(y)��
		
		Pitch  ����  x
		Yaw    ����  y
		Roling ���  z

	*/
	int wid=GetSystemMetrics(SM_CXSCREEN);		// ��ȡ��ǰ��Ļ��
	int hei=GetSystemMetrics(SM_CYSCREEN);		// ��ȡ��ǰ��Ļ��
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

	WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX& ~WS_THICKFRAME����,	// window style,��ֹ��󻯣���ֹ�ı䴰�ڴ�С�����ǵ���������

	1000,	// initial x size//���ǵ�������� ���������ֵ������Ҫ��Ĵ��ڴ�С
	750,	// initial y size
	��
	*/


