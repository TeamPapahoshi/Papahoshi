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
// value 値
// power 累乗数

//---- 累乗(整数) -----
int PowerN(int value, int power);
// value 値
// power 累乗数

//---- ベジェ曲線上の値を求める -----
D3DXVECTOR2 BezierCurve(float t, D3DXVECTOR2 cp1, D3DXVECTOR2 cp2, D3DXVECTOR2 cp3, D3DXVECTOR2 cp4);
// t 曲線上の位置。 0.0f～1.0f
//     (t = 0.0f なら cp1の位置。 t = 1.0f ならcp4の位置。)
// cp1 制御点１(始点)
// cp2 制御点２(この点は通らない)
// cp3 制御点３(この点は通らない)
// cp4 制御点４(終点)

//----- ベクトルの内積を求める -----
float VectorDotProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2);
// v1 , v2 ベクトル

//----- ベクトルの外積を求める -----
float VectorCrossProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2);
// v1 , v2 ベクトル

//----- ベクトルの長さを求める -----
float VectorSize(D3DXVECTOR2 v);
// v ベクトル

#endif