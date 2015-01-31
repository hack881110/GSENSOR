// GLFont.h: interface for the CGLFont class.

#if !defined(AFX_GLFONT_H__88F1F000_50F5_452A_B95E_60ED83712FA5__INCLUDED_)
#define AFX_GLFONT_H__88F1F000_50F5_452A_B95E_60ED83712FA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGLFont  
{
public:
	void entext(float x,float y, char* str,HFONT hFont,float r,float g,float b);
	void c3dtext(char* str,HFONT hFont,float z);
	void Printfc3d(char* strText,HFONT hFont,float z=0.05f);
	void Printftext(int x, int y, char* lpszText,HFONT hFont);
	void settext(float x,float y,char* str,HFONT Font,float r,float g,float b);

	CGLFont();
	virtual ~CGLFont();
protected:
	HFONT hFont;
};

#endif // !defined(AFX_GLFONT_H__88F1F000_50F5_452A_B95E_60ED83712FA5__INCLUDED_)
