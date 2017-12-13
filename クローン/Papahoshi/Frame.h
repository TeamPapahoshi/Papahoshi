//======================================================================
//	Frame
//	
//	概要＿：フレーム管理関連
//	制作者：花井　雄矢
//	
//======================================================================


#ifndef ___FRAME_H___
#define ___FRAME_H___

#include <Windows.h>	//HRESULT他
#include "Common.h"		//FPS計測機能オンオフの確認


HRESULT InitFrame(void);
void UnInitFrame(void);
BOOL CheckFrameUpdate(void);
DWORD Frame_timeGetTime(void);

#endif //!___FRAME_H___
