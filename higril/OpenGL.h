// OpenGL.h: interface for the OpenGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGL_H__17B7289C_7956_41C5_89B9_621E3C435389__INCLUDED_)
#define AFX_OPENGL_H__17B7289C_7956_41C5_89B9_621E3C435389__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>	// Windows的头文件
#include "common.h"
#include "baiscobj.h"
#include "bsipic.h"
#include "GLFont.h"
#include "Font.h"

extern Queue Rx_Queue;

class OpenGL  
{	public:	OpenGL();
	virtual ~OpenGL();
	public:


	HFONT	hFont;
	CGLFont *m_Font; 
	baiscobj* m_baiscobj;
	bsipic *m_bsipic;
	HDC		hDC;			// GDI设备描述表
	HGLRC	hRC;		// 永久着色描述表
	BOOL	SetupPixelFormat(HDC hDC);
	void	init(int Width, int Height);
	void	Render();
	void	CleanUp();
	void	play();
	int		mybitmap;
	//void ProcessMenu(int value);
};

#endif // !defined(AFX_OPENGL_H__17B7289C_7956_41C5_89B9_621E3C435389__INCLUDED_)
