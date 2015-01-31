// GLFont.cpp: implementation of the CGLFont class.
//程序设计：唐明理	2005.2
//E_mail cqtml@163.com
//////////////////////////////////////////////////////////////////////
#include "common.h"

#include "GLFont.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
//unsigned int Base;
//////////////////////////////////////////////////////////////////////

CGLFont::CGLFont()
{
}
CGLFont::~CGLFont()
{
}
void CGLFont::entext( float x,float y, char*  str, HFONT hFont,
					  float r, float g, float b) 
{ 	HDC hdc = wglGetCurrentDC();  
	SelectObject(hdc, hFont); 
	unsigned int Base = glGenLists(96);
	wglUseFontBitmaps(hdc, 32, 96,Base);
	glDisable(GL_TEXTURE_2D); 
	glDisable(GL_LIGHTING); 
	glPushAttrib(GL_LIST_BIT);  
	glColor3f(r,g,b);
	glRasterPos2f(x/100, y/100); 
		glListBase(Base - 32); 
		glCallLists(strlen((char *)str), GL_UNSIGNED_BYTE, str); 
	glPopAttrib(); 
	glEnable(GL_LIGHTING); 
	glEnable(GL_TEXTURE_2D); 
	glDeleteLists(Base, 96); 
}

//////////////////////////////////////////////////////////////////
void CGLFont::c3dtext(char*  str,HFONT hFont,float z)
{	glDisable(GL_TEXTURE_2D); 
	glDisable(GL_LIGHTING);
	Printfc3d("立体汉字",hFont,z);
	glEnable(GL_LIGHTING);   
	glEnable(GL_TEXTURE_2D);
}
void CGLFont::Printfc3d(char*  strText,HFONT hFont,float z)
{	HDC hdc = wglGetCurrentDC();
	HFONT hOldFont=(HFONT)::SelectObject(hdc,hFont);
	UCHAR * pChar=(UCHAR*)strText;
	int   nListNum;  
	DWORD dwChar;  
	GLYPHMETRICSFLOAT pgmf[1]; 
	glPushMatrix();   
	for(int i = 0; i < sizeof(strText); i++)
	{ if(IsDBCSLeadByte((BYTE)pChar[i]))
		{ dwChar=(DWORD)((pChar[i]<<8)|pChar[i+1]);
		  i++;
		}
	  else	dwChar = pChar[i];
	  nListNum = glGenLists(1);  
	  wglUseFontOutlines( hdc,	
						  dwChar,	
						  1,
						  nListNum,	
						  0.0f, 
						  z,
						  WGL_FONT_POLYGONS,
						  pgmf	
						);
	  glCallList(nListNum);  
	  glDeleteLists(nListNum, 1);   
	}	
	glPopMatrix();    
	memset(strText,0x00,sizeof(strText));
	::SelectObject(hdc,hOldFont); 
}
////////////////////////////////////////////////////////////////////////
void CGLFont:: settext (float x,float y,char*  str,HFONT Font,float r,float g,float b)
  
{   glLoadIdentity();
	glPushAttrib(GL_CURRENT_BIT);
	glDisable(GL_TEXTURE_2D); 
	glDisable(GL_LIGHTING); 
	glColor3f(r,g,b);  
	  glTranslatef(-(420-x)/800,(260-y)/600,-1.0f);
	  Printftext (0,0, str,Font);    
	glEnable(GL_LIGHTING);     
	glEnable(GL_TEXTURE_2D);
	glPopAttrib();
}
void CGLFont:: Printftext (int x, int y, char* lpszText,HFONT hFont)
{ 
	/*
	BITMAP bitmap;
  BITMAP bm;
  SIZE size; 
  HDC MDC = ::CreateCompatibleDC(0);
  SelectObject(MDC,hFont);	
  ::GetTextExtentPoint32(MDC,(LPCWSTR)lpszText,strlen(lpszText),&size);
  bitmap.CreateBitmap(size.cx, size.cy, 1, 1, NULL);
  HBITMAP oldBmp=(HBITMAP)SelectObject(MDC,bitmap);
  SetBkColor  (MDC, RGB(0,     0,   0));
  SetTextColor(MDC, RGB(255, 255, 255));
  TextOut(MDC, 0, 0, (LPCWSTR)lpszText, strlen(lpszText));
  bitmap.GetBitmap(&bm);
  size.cx = (bm.bmWidth + 31) & (~31);
  int bufsize =size.cy * size.cx;
  struct {  BITMAPINFOHEADER bih;
			RGBQUAD col[2];
 		 }bic; 
  BITMAPINFO *binf = (BITMAPINFO *)&bic; 
  binf->bmiHeader.biSize     = sizeof(binf->bmiHeader);//
  binf->bmiHeader.biWidth    = bm.bmWidth;
  binf->bmiHeader.biHeight   = bm.bmHeight;
  binf->bmiHeader.biPlanes   = 1;   
  binf->bmiHeader.biBitCount = 1;
  binf->bmiHeader.biCompression = BI_RGB;
  binf->bmiHeader.biSizeImage   = bufsize; 
  UCHAR* Bits = new UCHAR;	
  ::GetDIBits(MDC,bitmap,0,bm.bmHeight,Bits,binf,DIB_RGB_COLORS); 
                                      
  glPixelStorei(GL_UNPACK_ALIGNMENT ,1);
  glRasterPos2i(x,y); 
  glBitmap(size.cx,size.cy,0,0,0,0,Bits); 
  delete Bits;    
  SelectObject(MDC, oldBmp);  
  ::DeleteDC(MDC);
  */
}
