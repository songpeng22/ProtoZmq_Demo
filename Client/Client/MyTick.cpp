// MyTick.cpp: implementation of the CMyTick class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyTick.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int	CMyTick::m_nCount = 0;

CMyTick::CMyTick()
{
	m_cChar = 0;

	OnBegin();
	m_bPainted = false;
}

CMyTick::CMyTick(char cChar)
{
	m_cChar = cChar;

	OnBegin();
	m_bPainted = false;
}

CMyTick::~CMyTick()
{
	if (!m_bPainted)
		OnEnd();
}

DWORD CMyTick::OnBegin()
{
	m_Tick = ::GetTickCount();
	return m_Tick;
}

DWORD CMyTick::OnGet()
{
	static DWORD dwCurTick = 0;
	dwCurTick = ::GetTickCount() - m_Tick;
	return ( dwCurTick );
}

void CMyTick::OnEnd()
{
	m_OldTick = GetTickCount();
	OnPaint();
	m_bPainted = TRUE;
}

void CMyTick::OnPaint()
{
	m_nCount++;
	if ( m_cChar )
	{
//		CMyPrint::Instance()->Print( TEXT("%c:%d_Takes:%d(ms).\r\n"),m_cChar,m_nCount,m_OldTick - m_Tick );
//		TRACE( TEXT("%c%d_Takes:%d.\r\n"),m_cChar,m_nCount,m_OldTick - m_Tick );
        TCHAR buf[200];
        swprintf( buf,TEXT("%c:%d_Takes:%d(ms).\r\n"),m_cChar,m_nCount,m_OldTick - m_Tick );
        OutputDebugString( buf );
	}
	else
	{
//		TRACE( TEXT("%d_Takes:%d(ms).\r\n"),m_nCount,m_OldTick - m_Tick );
	}
}

void CMyTick::Wait( DWORD dwMs )
{
//	BOOL bWait = TRUE;

	DWORD dwStart = ::GetTickCount();
	DWORD dwEnd;
//	int nCount = 0;
	for (;;)	//bWait//while( TRUE )
	{
		if ( ::GetTickCount() - dwStart >= dwMs )
		{
//			TRACE2("Tick:%d %d.\n",dwStart,::GetTickCount());
			return;
		}
		else
		{
//			TRACE2("Tick:%d %d.\n",dwStart,::GetTickCount());
//			TRACE1("nCount:%d.\n",nCount);
		}
	}
}

void CMyTick::Wait1ms()
{
	//	BOOL bWait = TRUE;

	DWORD dwStart = ::GetTickCount();
	DWORD dwEnd;
	//	int nCount = 0;
	for (;;)	//bWait//while( TRUE )
	{
		dwEnd = ::GetTickCount();
		if ( dwEnd ^ dwStart )
		{
//			TRACE2("Tick:%d %d.\n",dwStart,dwEnd);//::GetTickCount()
			return;
		}
	}
}

DWORD CMyTick::OnDiff()
{
	DWORD dwDiff = ( ::GetTickCount() - m_Tick );
	return dwDiff;
}
