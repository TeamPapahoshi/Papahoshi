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
// �C���N���[�h��
//-----------------------------
#include <Windows.h>		//HRESULT��
#include "Common.h"

//-----------------------------
// �v���g�^�C�v�錾
//-----------------------------
int GetScore();
void SetScore(int score);
void AddScore(int score);
void UpdateScore();
void DrawScore(D3DXVECTOR2 pos, D3DXVECTOR2 size);
void ResetPrintScore();	//�\�����̃X�R�A���O�Ƀ��Z�b�g

#endif