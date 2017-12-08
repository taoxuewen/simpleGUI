#include "BWindows.h"
class CThreading
{

	
private:
	HANDLE thread_t;
	DWORD t_threadID;
	

public:
	CThreading();
	~CThreading();
	void start_t();
	void exit_t();
	void stop_t();
	HANDLE getCurrentThread_handle();
	static DWORD WINAPI run(LPVOID lpParameter);

};
