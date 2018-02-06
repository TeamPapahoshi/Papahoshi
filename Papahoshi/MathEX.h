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

//---- �����̕����_�����߂� -----
D3DXVECTOR2 LineSplitPoint(D3DXVECTOR2 p1, D3DXVECTOR2 p2, int m, int n);
// p1 �����̊J�n�_
// p2 �����̏I�_
// m,n ����p1p2�� m:n �ɕ��������_(x,y)�̒l��Ԃ��܂�

//---- �����̌X�������߂� -----
float LineSlope(D3DXVECTOR2 p1, D3DXVECTOR2 p2);
// p1 �����̊J�n�_
// p2 �����̏I�_

//---- �����̐ؕЂ����߂� -----
float LineIntercept(D3DXVECTOR2 p1, D3DXVECTOR2 p2);
// p1 �����̊J�n�_
// p2 �����̏I�_

//---- �����̈�_����_�Ƃ��������̌X�������߂� -----
float VerticalLineSlope(float slope);
// slope  �����̌X��

//---- �����̈�_����_�Ƃ��������̐ؕЂ����߂� -----
float VerticalLineIntercept(D3DXVECTOR2 crossP, float slope);
// crossP ��_
// slope �����̌X��

//---- ������̓_Y�����߂� -----
float LineY(float x, float slope, float intersept);
// x X���W
// slope �����̌X��
// intersept �����̐ؕ�

//---- ������̓_X�����߂� -----
float LineX(float y, float slope, float intersept);
// y Y���W
// slope �����̌X��
// intersept �����̐ؕ�

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

//----- �P�ʃx�N�g�������߂� -----
D3DXVECTOR2 UnitVector(D3DXVECTOR2 v);
// v �x�N�g��

#endif