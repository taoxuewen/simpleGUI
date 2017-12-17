#include "BWindows.h"
#include "BForm.h"
#include "BWndbase.h"
#include "resource.h"
#include "BControl.h"

const char* ImageMotor[8]={"请想象右手","请想象左手","请想象左右手","请想象左手右脚","请想象右手左脚"};

bool imaging_flag=true;
bool stop_flag=true;

CBForm form(ID_Dialog);
//change
void cmd_cancel();
void cmd_start();
void Form_resize()
{
	form.Control(ID_motor).Move((form.ClientWidth()-form.Control(ID_motor).Width())/2,(form.ClientHeight()-form.Control(ID_motor).Height())/2);
}



DWORD WINAPI run(LPVOID lpParameter)
{
	static int N=0;
	stop_flag=true;
	while (imaging_flag)
	{
		form.Control(ID_motor).TextSet("休息");
		Sleep(5000);
		form.Control(ID_motor).TextSet(ImageMotor[N]);
		Sleep(5000);
		if (N++>3)N=0;
	}
	stop_flag=false;
	return 1;
}

main()
{
	//form.BackColorSet();
	form.Control(ID_Btstart).BackColorSet(RGB(0,255,0));
	form.Control(ID_label).TextSet(100);
	form.Control(ID_motor).FontSizeSet(30);
	form.Show();
	form.EventAdd(ID_Btstart,eCommandButton_Click,cmd_start);
	form.EventAdd(ID_end,eCommandButton_Click,cmd_cancel);
	form.EventAdd(0,eForm_Resize,Form_resize);
	return 0;
}
void cmd_start()
{
	imaging_flag=true;
	form.Control(ID_flag).TextSet("");
	HANDLE thread_t=CreateThread(NULL,0,run,NULL,0,NULL);
	CloseHandle(thread_t);
	
}
void cmd_cancel()
{
	imaging_flag=false;
	//while(stop_flag);
	form.Control(ID_flag).TextSet("已结束");
}