// baiscobj.cpp: implementation of the baiscobj class.
//程序设计：唐明理	2005.2
//E_mail cqtml@163.com
//////////////////////////////////////////////////////////////////////
#include "common.h"
#include "baiscobj.h"
#include "Font.h"
#include "DealUartData.h"

bool bCull;
bool bDepth;


/*
线宽
*/
GLfloat fSize[2];
GLfloat fCurrSize;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
baiscobj::baiscobj()
{	g_eye[0]= MAP;//
	g_eye[2]=-MAP;//
	g_Angle=0;
	g_elev=0;
	g_text = gluNewQuadric();
	LoadT8(TEXT("data/aa.bmp"),g_cactus[7]);
	LoadT8(TEXT("data/bb.BMP"),g_cactus[6]);
	LoadT8(TEXT("data/before.BMP"),g_cactus[0]);
	LoadT8(TEXT("data/up.BMP"),g_cactus[1]);
	LoadT8(TEXT("data/Left.BMP"),g_cactus[2]);
	LoadT8(TEXT("data/after.BMP"),g_cactus[3]);
	LoadT8(TEXT("data/down.BMP"),g_cactus[4]);
	LoadT8(TEXT("data/right.BMP"),g_cactus[5]);
	glGetFloatv(GL_LINE_WIDTH_RANGE,fSize);
	fCurrSize=fSize[0]+5;
	glLineWidth(fCurrSize);
	baiscobj::mybitmap=1;
}
baiscobj::~baiscobj()
{

}
void baiscobj::light0()
{	GLfloat light_position[] = {1.0,10.0,-51.0,10.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}
BOOL baiscobj::DisplayScene()
{ 
 
  if (KEY_DOWN(VK_LEFT)) 
  {
		  yaw+=0.3;
		  if(yaw>=360)
			  yaw=0;  
  }
  if (KEY_DOWN(VK_RIGHT)) 
  {
	  yaw-=0.3;
	  if(yaw<=0)
		  yaw=360;  
  }
  if (KEY_DOWN(VK_UP))
  {
	  pitch+=0.3;
	  if(pitch>=360)
		  pitch=0;
  }
  if (KEY_DOWN(VK_DOWN))
  {
	   pitch-=0.3;
	   if(pitch<=0)
		   pitch=360;
  }
  if(KEY_DOWN(VK_SPACE))
  {
	  if(baiscobj::mybitmap==0)
	  {
		  baiscobj::mybitmap=1;
	  }
	  else
	  {
		 baiscobj::mybitmap=1;
	  }
  }
  if(KEY_DOWN(VK_F1))
  {
	  if(bCull)
	  bCull=FALSE;
	  else
	  bCull=TRUE;

  }
  if(KEY_DOWN(VK_F2))
  {
	  if(bDepth)
		  bDepth=FALSE;
	  else
		  bDepth=TRUE;

  }
  return TRUE;
}
GLvoid baiscobj::DrawGround()
{ glPushAttrib(GL_CURRENT_BIT);
  glEnable(GL_BLEND);
  glPushMatrix();
  glColor3f(0.5f, 0.7f, 1.0f);
  glTranslatef(0,0.0f,0);
  int size0=(int)(MAP*2);
  glBegin(GL_LINES);
	for (int x = -size0; x < size0;x+=4)
		{glVertex3i(x, 0, -size0); glVertex3i(x, 0,  size0);}
	for (int z = -size0; z < size0;z+=4)
		{glVertex3i(-size0, 0, z); glVertex3i( size0, 0, z);}
  glEnd();
  glPopMatrix();
  glDisable(GL_BLEND);
  glPopAttrib();
}
//==========================================================================
void baiscobj::picter(float x,float y,float z)
{glPushAttrib(GL_CURRENT_BIT);
 glPushMatrix();
	glTranslatef(x,y+0.5f,z);
	glColor3f(0.0f,1.0f,0.2f);
	auxSolidCube(1);
	glTranslatef(0.0f,0.8f,0.0f);
	glColor3f(0.0f,0.0f,1.0f);
	auxSolidBox(.2f,1.3f,.2f);
 glPopMatrix();
 glPushMatrix();
	glTranslatef(x,y+2.5f,z);
//	glRotatef(r-90,0.0,1.0,0.0);
	//=======================================
	glColor3f(1.0f,1.0f,1.0f);
	glRotatef(45, 1.0, 0.0, 0.0);
	auxWireCone(1.5,0.6f);	
	//=======================================
	glRotatef(180, 1.0, 0.0, 0.0);
	glTranslatef(0.0f,0.0f,-0.7f);
	auxWireCone(0.2f,2.0f);	
	glColor3f(FRAND,0,0);
	glTranslatef(0.0f,0.0f,2.0f);
	auxSolidSphere(0.1f);
 glPopMatrix();
/* glPushMatrix();
	glTranslatef(x,y+10.0f,z);
	glRotatef(r, 0.0, 1.0, 0.0);
	glTranslatef(x/15,0,0);
	//=============================================
	glColor3f(1.0f,0.0f,0.0f);
	glRotatef(180, 0.0, 1.0, 0.0);
	auxSolidCone(.2,0.6);
	//=============================================
	glColor3f(1.0f,1.0f,1.0f);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(0.0f,-1.0f,0);	
	auxSolidCylinder(.2f,1);
	glRotatef(-270, 1.0, 0.0, 0.0);
	glColor3f(FRAND+.6f,0.2f,0.0f);
	glTranslatef(0.0f,-0.0f,-0.2f); 
	auxSolidCone(.2,1.5);
 glPopMatrix();
 glEnable(GL_TEXTURE_2D);*/
 glPopAttrib();
 
 //r+=0.1f;if(r>360) r=0;

}

void baiscobj::cube(float a,float x,float y,float z)
{


	//glScalef(x,y,z);
	glPushMatrix();
	//glTranslatef(x,y,z);
	glRotatef(k2*pitch, 1.0, 0.0, 0.0);
	glRotatef(k1*yaw, 0.0, 1.0, 0.0);
	glRotatef(k3*roll, 0.0, 0.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	
	//glTranslatef(30,0,0);
if(baiscobj::mybitmap==1)
{
	glBindTexture(GL_TEXTURE_2D, g_cactus[0]);//
	glColor3f(0.5,0.8,0.9);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -1.0f,  2.0f);// 前
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, -1.0f,  2.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  1.0f,  2.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  1.0f,  2.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, g_cactus[3]);//
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -1.0f, -2.0f);// 后
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f,  1.0f, -2.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.0f,  1.0f, -2.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.0f, -1.0f, -2.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, g_cactus[1]);//
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  1.0f, -2.0f);// 上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f,  1.0f,  2.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f,  1.0f,  2.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  1.0f, -2.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, g_cactus[4]);//
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.0f, -1.0f,  -2.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.0f, -1.0f, 2.0f);
	
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f, -1.0f, 2.0f);// 下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -1.0f,  -2.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, g_cactus[5]);//
	glColor3f(0.7,0.5,0.1);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, -1.0f, -2.0f);// 左
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  1.0f, -2.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.0f,  1.0f,  2.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.0f, -1.0f,  2.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, g_cactus[2]);//
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -1.0f, -2.0f);// 右
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -1.0f,  2.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f,  1.0f,  2.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  1.0f, -2.0f);
	glEnd();

}
else
{
	glutSolidCube(2);
}

/* 画坐标系	*/
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0,0.0,0.0);
	glLineWidth(fCurrSize);
	glBegin(GL_LINES);
	 glVertex3f(0, 0, 0);
	 glVertex3f(0+2*a, 0, 0);
	glEnd();
	glRasterPos2f(0+2*a,0.2);
	glPrint("Y");	// Print GL Text To The Screen
	glBegin(GL_TRIANGLES);
	glVertex3f(2*a+0.1, 0, 0);
	glVertex3f(2*a-0.3,0.2,0.0);
	glVertex3f(2*a-0.3,-0.2,0.0);
	glEnd();


	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0+a, 0);
	glEnd();
	glRasterPos2f(0,0+a);
	glPrint("Z");	// Print GL Text To The Screen
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0,a+0.1, 0);
	glVertex3f(0.2,a-0.3,0.0);
	glVertex3f(-0.2,a-0.3,0.0);
	glEnd();

	glColor3f(0.0,0.0,1.0);
	glLineWidth(fCurrSize);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0+2*a);
	glEnd();
	glRasterPos3f(0,0,2*a);
	glPrint("X");	// Print GL Text To The Screen
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0+2*a);
	glVertex3f(0, 0, 0+2*a);
	glEnd();
	glVertex3f(0.0,0.0,2*a+0.1);
	glVertex3f(0.0,0.2,2*a-0.3);
	glVertex3f(0.0,-0.2,2*a-0.3);
	glPopMatrix();
	//p+=0.05f;if(p>360) p=0;
	//c+=0.02f;if(c>360) c=0;
	//r+=0.01f;if(r>360) r=0;
}

void baiscobj::airplane(float x,float y,float z)
{
	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(-roll, 0.0, 1.0, 0.0);
	glTranslatef(30,0,0);
	glRotatef(30, 0.0, 0.0, 1.0);
	//=============================================
	glPushMatrix();//
		glRotatef(-roll*30, 0.0, 0.0, 1.0);
		glColor3f(0.0, 0.0, 1.0);
		Box(1.0f,0.1f,0.02f);
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[1]);//
	glTranslatef(0.0f,0.0f,-0.5f);
	gluSphere(g_text, 0.4f, 8, 8);
	//=============================================
	glTranslatef(0.0f,-0.0f,-2);
	gluCylinder(g_text,0.4,0.4,2.0,8,4);
	//=====================================================
	glRotatef(-180, 1.0, 0.0, 0.0);
	glTranslatef(0.0f,-0.0f,0.0f);
	gluCylinder(g_text,0.4,0.1,1.5,8,4);
	//======================================================
	glBindTexture(GL_TEXTURE_2D, g_cactus[0]);//
	glTranslatef(0.0f,-0.8f,1.2f);
	Box(1.0,0.05f,0.3f);
	glTranslatef(0.0f,0.1f,0.0f);
	Box(0.05f,0.6f,0.30f);
	//======================================================
	glTranslatef(0.0f,0.7f,-1.9f);
	Box(3,0.05f,0.5f);
	//======================================================
	glDisable(GL_TEXTURE_2D);
 glPopMatrix();
}
void baiscobj::Box(float x,float y,float z)
{ glPushMatrix();
  glScalef(x,y,z);
  glRotatef(pitch, 1.0, 0.0, 0.0);
  glRotatef(yaw, 0.0, 1.0, 0.0);
  glRotatef(roll, 0.0, 0.0, 1.0);
 // glBindTexture(GL_TEXTURE_2D, g_cactus[0]);//
  glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);// 前
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 后
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);// 上
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 下
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);// 左
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 右
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
 glDisable(GL_TEXTURE_2D);
 glPopMatrix();
 pitch+=0.5f;if(pitch>360) pitch=0;
 yaw+=0.2f;if(yaw>360) yaw=0;
 roll+=0.1f;if(roll>360) roll=0;
}
bool baiscobj::LoadT8(LPCWSTR filename, GLuint &texture)
{	AUX_RGBImageRec *pImage = NULL;
	pImage = auxDIBImageLoad(filename);
	if(pImage == NULL)		return false;
	glGenTextures(1, &texture);	
	glBindTexture    (GL_TEXTURE_2D,texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4, pImage->sizeX, 
					  pImage->sizeY,GL_RGB, GL_UNSIGNED_BYTE,pImage->data);
	free(pImage->data);
	free(pImage);	
	return true;
}

