//======================================================================
//	Timer
//	
//	�T�v�Q�FTimer�̊Ǘ�
//	����ҁF�Ԉ�@�Y��
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