#include "Threading.h"
CThreading::CThreading()
{
	thread_t=CreateThread(NULL,0,run,NULL,CREATE_SUSPENDED,&t_threadID);
}

CThreading::~CThreading()
{
	BOOL re=CloseHandle(thread_t);
}

void CThreading::start_t()
{
	auto re=ResumeThread(thread_t);	
}

void CThreading::stop_t()
{
	auto re=SuspendThread(thread_t);
}

void CThreading::exit_t()
{
	ExitThread(t_threadID);
	BOOL re=CloseHandle(thread_t);
}

DWORD WINAPI CThreading::run(LPVOID lpParameter)
{
	return 0; 
}
