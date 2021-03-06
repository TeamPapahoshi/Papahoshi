//=============================================================================
//
// デバッグ表示処理 [debugproc.h]
// Author : Takuya Kato
//
//=============================================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "Direct3D.h"	//HESULT

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitDebugProc(void);
void UninitDebugProc(void);
void UpdateDebugProc(void);
void DrawDebugProc(void);

void PrintDebugProc(char *fmt,...);

#endif