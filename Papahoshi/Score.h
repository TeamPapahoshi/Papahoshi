//=====================================================
//
//	MasicSplitGirl		Score.h
//
//	Mei Goto.
//
//=====================================================

#ifndef __SCORE_H__
#define __SCORE_H__

//-----------------------------
// インクルード部
//-----------------------------
#include <Windows.h>		//HRESULT他
#include "Common.h"

//-----------------------------
// プロトタイプ宣言
//-----------------------------
int GetScore();
void SetScore(int score);
void AddScore(int score);
void UpdateScore();
void DrawScore(D3DXVECTOR2 pos, D3DXVECTOR2 size);
void ResetPrintScore();	//表示中のスコアを０にリセット

#endif