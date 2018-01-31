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
// value �l
// power �ݏ搔

//---- �ݏ�(����) -----
int PowerN(int value, int power);
// value �l
// power �ݏ搔

//---- �x�W�F�Ȑ���̒l�����߂� -----
D3DXVECTOR2 BezierCurve(float t, D3DXVECTOR2 cp1, D3DXVECTOR2 cp2, D3DXVECTOR2 cp3, D3DXVECTOR2 cp4);
// t �Ȑ���̈ʒu�B 0.0f�`1.0f
//     (t = 0.0f �Ȃ� cp1�̈ʒu�B t = 1.0f �Ȃ�cp4�̈ʒu�B)
// cp1 ����_�P(�n�_)
// cp2 ����_�Q(���̓_�͒ʂ�Ȃ�)
// cp3 ����_�R(���̓_�͒ʂ�Ȃ�)
// cp4 ����_�S(�I�_)

//----- �x�N�g���̓��ς����߂� -----
float VectorDotProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2);
// v1 , v2 �x�N�g��

//----- �x�N�g���̊O�ς����߂� -----
float VectorCrossProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2);
// v1 , v2 �x�N�g��

//----- �x�N�g���̒��������߂� -----
float VectorSize(D3DXVECTOR2 v);
// v �x�N�g��

#endif