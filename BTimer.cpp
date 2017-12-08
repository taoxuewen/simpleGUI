#include "BTimer.h"

UINT CBTimer::ms_uIDIncrement = 0;

CBTimer::CBTimer(HWND hWndAsso, UINT uElapse, TIMERPROC ptrFuncCallBack)
{
	m_uTimerID = 0;
	m_hWndAsso = NULL;
	m_uElapse = 0;
	m_pFuncCallBack = NULL;
	m_blEnabled = false;

	hWndAssoSet(hWndAsso);
	IntervalSet(uElapse);
	pFuncCallBackSet(ptrFuncCallBack);

	EnabledSet(true);
}

CBTimer::~CBTimer()
{
	EnabledSet(false);
}

bool CBTimer::Enabled()
{
	return m_blEnabled;
}

void CBTimer::EnabledSet(bool value)
{
	if (m_blEnabled == value ) 
		return;

	if (value)
	{
		if(m_pFuncCallBack!=NULL && m_uElapse!=0)
		{
			UINT ret = SetTimer(m_hWndAsso, m_uTimerID, m_uElapse, m_pFuncCallBack);
			if(ret)
			{
				m_uTimerID = ret;
				m_blEnabled= true;
			}
			else
			{
				m_blEnabled = false;
			}
		}
		else
		{
			m_blEnabled = false;
		}
	}
	else
	{
		BOOL bl=KillTimer(m_hWndAsso, m_uTimerID);
		m_blEnabled = false;
	}
}

UINT CBTimer::Interval()
{
	return m_uElapse;
}

void CBTimer::IntervalSet(UINT uInterval)
{
	if (m_uElapse==uInterval) 
		return;

	m_uElapse = uInterval;

	if(m_blEnabled)
	{
		EnabledSet(false);
		EnabledSet(true);
	}
}

UINT CBTimer::Identifier()
{
	if (m_blEnabled)
		return m_uTimerID;
	else
		return 0;
}

TIMERPROC CBTimer::pFuncCallBack()
{
	return m_pFuncCallBack;
}

void CBTimer::pFuncCallBackSet( TIMERPROC ptrFuncCallBack )
{
	if (m_pFuncCallBack == ptrFuncCallBack)
		return;

	m_pFuncCallBack = ptrFuncCallBack;

	if (m_blEnabled)
	{
		EnabledSet(false);
		EnabledSet(true);
	}
}

HWND CBTimer::hWndAsso()
{
	return m_hWndAsso;
}

void CBTimer::hWndAssoSet( HWND hWnd )
{
	if (m_hWndAsso == hWnd)
		return;

	bool blLastEnabled = m_blEnabled;
	if (m_blEnabled)
		EnabledSet(false);

	m_hWndAsso = hWnd;

	if (m_hWndAsso)
	{
		ms_uIDIncrement++;
		m_uTimerID = ms_uIDIncrement;
	}

	if (blLastEnabled)
	{
		EnabledSet(true);
	}
}






