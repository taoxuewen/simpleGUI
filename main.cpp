#include "BWindows.h"
#include "BForm.h"
#include "BWndbase.h"
#include "resource.h"
#include "BControl.h"

CBForm form(ID_Dialog);

void cmd_cancel();
/*
class Th: public CThreading
{
public:
	Th(){};
	DWORD WINAPI run(LPVOID lpParameter)
	{
		int N=1;
		while (N++<10)
		{
			form.Control(ID_label).TextSet(N);
			Sleep(5);
		}
	}
};

Th th1;
*/

DWORD WINAPI run(LPVOID lpParameter)
{
	int N=1;
	while (N++<10)
	{
		form.Control(ID_label).TextSet(N);
		Sleep(1000);
	}
	return 1;
}

main()
{
	form.BackColorSet(RGB(255,255,255));
	form.Control(ID_BtCANCEL).BackColorSet(RGB(0,255,0));
	form.Control(ID_label).TextSet(100);
	form.Show();
	form.EventAdd(ID_BtCANCEL,eCommandButton_Click,cmd_cancel);
	return 0;
}

void cmd_cancel()
{
	HANDLE thread_t=CreateThread(NULL,0,run,NULL,0,NULL);
}