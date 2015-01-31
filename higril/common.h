// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>	// Windows��ͷ�ļ�

#include <mmsystem.h>
#include <stdlib.h>
//#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <gl\gl.h>		// OpenGL32���ͷ�ļ�
#include <gl\glu.h>		// GLu32���ͷ�ļ�
#include <gl\glaux.h>	// GLaux���ͷ�ļ�
#include <gl\glut.h>
#include "queue.h"
//#include <afxwin.h>
extern int iCull ;
extern int iOutline ;
extern int iDepth ;

#pragma comment( lib, "winmm.lib")
#pragma comment( lib, "opengl32.lib")	// OpenGL32���ӿ�
#pragma comment( lib, "glu32.lib")		// GLu32���ӿ�
#pragma comment( lib, "glaux.lib")		// GLaux���ӿ�

#define FRAND   (((float)rand()-(float)rand())/RAND_MAX)
//#define MAP_W       16.0f       // size of map along x-axis 32 
//#define MAP_SCALE   16.0f     // the scale of the terrain map24
#define MAP		40//	MAP_W*MAP_SCALE/2
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
