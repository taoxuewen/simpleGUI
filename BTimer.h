#include <windows.h>

class  CBTimer
{
private:
	static UINT ms_uIDIncrement;

public:
	CBTimer(HWND hWndAsso=NULL, UINT uElapse=1000, TIMERPROC ptrFuncCallBack=NULL);

	~CBTimer();

	bool Enabled();
	void EnabledSet(bool value);

	UINT Interval();
	void IntervalSet(UINT uInterval);

	TIMERPROC pFuncCallBack();
	void pFuncCallBackSet(TIMERPROC ptrFuncCallBack);

	HWND hWndAsso();
	void hWndAssoSet(HWND hWnd);

	UINT Identifier();

private:
	UINT m_uTimerID;
	HWND m_hWndAsso;
	UINT m_uElapse;
	TIMERPROC m_pFuncCallBack;
	bool m_blEnabled;
};
//我是