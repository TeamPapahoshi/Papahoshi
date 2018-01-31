//====================================================
//  Papahoshi   MathEX.h
//
//  ���w�I�Ȋ֐��Q
//
//====================================================

#ifndef __MATH_EX_H__
#define __MATH_EX_H__

//----------------------------------------
// �C���N���[�h��
//----------------------------------------
#include "Common.h"
#include "Sprite.h"
#include "Collision.h"

//------------------------------------
// �v���g�^�C�v�錾
//------------------------------------

//---- �ݏ�(����) -----
float PowerF(float value, int power);

//---- �ݏ�(����) -----
int PowerN(int value, int power);

//---- �x�W�F�Ȑ���̒l�����߂� -----
D3DXVECTOR2 BezierCurve(float t, D3DXVECTOR2 cp1, D3DXVECTOR2 cp2, D3DXVECTOR2 cp3, D3DXVECTOR2 cp4);

float VectorDotProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2);

float VectorCrossProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2);

float VectorSize(D3DXVECTOR2 v);


#endif