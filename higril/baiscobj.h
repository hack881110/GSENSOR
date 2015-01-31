// baiscobj.h: interface for the baiscobj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BAISCOBJ_H__6F90C6A0_F5E4_4482_BA6B_136D5C922B31__INCLUDED_)
#define AFX_BAISCOBJ_H__6F90C6A0_F5E4_4482_BA6B_136D5C922B31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class baiscobj  
{
public:
	baiscobj();
	virtual ~baiscobj();
public:
		
		int			m_Time,m_Fram;
		int			mybitmap;
private:GLdouble	g_eye[3];		//
		GLdouble	g_look[3];		//
		float		rad_xz;	
		float		g_Angle;
		float		g_elev;	
		
		UINT g_cactus[16];
		GLUquadricObj *g_text; 
public:	GLvoid		DrawGround();
		BOOL		DisplayScene();	
		void		light0();
		void		picter(float x,float y,float z);
		void		Box(float x,float y,float z);
		void		cube(float a,float x,float y,float z);
		void		airplane(float x,float y,float z);
		bool		LoadT8(LPCWSTR filename, GLuint &texture);
};

#endif // !defined(AFX_BAISCOBJ_H__6F90C6A0_F5E4_4482_BA6B_136D5C922B31__INCLUDED_)
