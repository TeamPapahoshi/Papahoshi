//======================================================================
//	Frame
//	
//	�T�v�Q�F�t���[���Ǘ��֘A
//	����ҁF�Ԉ�@�Y��
//	
//======================================================================


#ifndef ___FRAME_H___
#define ___FRAME_H___

#include <Windows.h>	//HRESULT��
#include "Common.h"		//FPS�v���@�\�I���I�t�̊m�F


HRESULT InitFrame(void);
void UnInitFrame(void);
BOOL CheckFrameUpdate(void);
DWORD Frame_timeGetTime(void);

#endif //!___FRAME_H___
