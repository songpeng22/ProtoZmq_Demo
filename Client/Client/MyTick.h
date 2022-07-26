// MyTick.h: interface for the CMyTick class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTICK_H__A167C58D_99E2_43D8_9F26_8CBEFE40EEDE__INCLUDED_)
#define AFX_MYTICK_H__A167C58D_99E2_43D8_9F26_8CBEFE40EEDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "windows.h" // for ::GetTickCount();

class CMyTick  
{
public:
	CMyTick();
	CMyTick(char cChar);
	virtual ~CMyTick();
public:
	int m_Tick;
	int m_OldTick;
	BOOL m_bPainted;
	DWORD OnBegin();
	void OnEnd();
	DWORD OnDiff();
	void OnPaint();
	DWORD OnGet();
public:
	static void Wait( DWORD dwMs );
	static void Wait1ms();
public:
	static int m_nCount;
	char m_cChar;
};


#endif // !defined(AFX_MYTICK_H__A167C58D_99E2_43D8_9F26_8CBEFE40EEDE__INCLUDED_)
