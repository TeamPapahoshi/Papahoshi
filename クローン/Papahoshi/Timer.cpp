//======================================================================
//	Timer
//	
//	�T�v�Q�FTimer�̊Ǘ�
//	����ҁF�Ԉ�@�Y��
//	
//======================================================================
#include "Timer.h"
#include "Frame.h"

static DWORD g_dwStartTime;
static DWORD g_dwErupsedTime;

void Timer_Start(void){
	g_dwStartTime = Frame_timeGetTime();

}
void Timer_Reset(void){

	g_dwErupsedTime = 0;
	g_dwStartTime = Frame_timeGetTime();

}

void Timer_Stop(void){
	DWORD dwStopTime = Frame_timeGetTime();
	g_dwErupsedTime += dwStopTime - g_dwStartTime;
}

DWORD Timer_GetTime(void){
	return g_dwErupsedTime;
}
