//====================================================
//  Papahoshi   MathEX.h
//
//  数学的な関数群
//
//====================================================

#ifndef __MATH_EX_H__
#define __MATH_EX_H__

//----------------------------------------
// インクルード部
//----------------------------------------
#include "Common.h"
#include "Sprite.h"
#include "Collision.h"

//------------------------------------
// プロトタイプ宣言
//------------------------------------

//---- 累乗(小数) -----
float PowerF(float value, int power);

//---- 累乗(整数) -----
int PowerN(int value, int power);

//---- ベジェ曲線上の値を求める -----
D3DXVECTOR2 BezierCurve(float t, D3DXVECTOR2 cp1, D3DXVECTOR2 cp2, D3DXVECTOR2 cp3, D3DXVECTOR2 cp4);

float VectorDotProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2);

float VectorCrossProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2);

float VectorSize(D3DXVECTOR2 v);


#endif