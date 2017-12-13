//======================================================================
//	Timer
//	
//	概要＿：Timerの管理
//	制作者：花井　雄矢
//	
//======================================================================
#ifndef ___TIMER_H___
#define ___TIMER_H___

#include <Windows.h>

void Timer_Start(void);
void Timer_Reset(void);
void Timer_Stop(void);
DWORD Timer_GetTime(void);

#endif //!___TIMER_H___