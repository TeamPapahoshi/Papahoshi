//====================================================
//  Papahoshi   MathEX.cpp
//
//  数学的な関数群
//
//====================================================

//-------------------------
// インクルード部
//-------------------------
#include "MathEX.h"

//=============================================
//
// 累乗(float)
//
//=============================================
float PowerF(float value, int power){

	float ans = value;

	while (power){
		ans = ans * value;
		power--;
	}

	return ans;
}

//=============================================
//
// 累乗(int)
//
//=============================================
int PowerN(int value, int power){

	int ans = value;

	while (power){
		ans = ans * value;
		power--;
	}

	return ans;
}

//---------------------------------------------------
//
//  ベジェ曲線上の値を求める
//
//---------------------------------------------------
D3DXVECTOR2 BezierCurve(float t, D3DXVECTOR2 cp1, D3DXVECTOR2 cp2, D3DXVECTOR2 cp3, D3DXVECTOR2 cp4){

	D3DXVECTOR2 work;

	work.x = PowerF((1.0f - t), 3) * cp1.x +
		3 * PowerF((1.0f - t), 2) * t * cp2.x +
		3 * (1.0f - t) * PowerF(t, 2) * cp3.x +
		PowerF(t, 3) * cp4.x;

	work.y = PowerF((1.0f - t), 3) * cp1.y +
		3 * PowerF((1.0f - t), 2) * t * cp2.y +
		3 * (1.0f - t) * PowerF(t, 2) * cp3.y +
		PowerF(t, 3) * cp4.y;

	return work;

}


//=====================================================
//
//  ベクトルの内積を求める関数
//
//=====================================================
float VectorDotProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2){

	//Dot = v1・v2 = x1*x2 + y1*y2 = |v1||v2|cos(θ)

	return (v1.x * v2.x + v1.y * v2.y);
}

//====================================================
//
//  ベクトルの外積を求める関数
//
//====================================================
float VectorCrossProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2){

	//v1×v2= x1*y2-x2*y1 = |v1||v2|sin(θ)

	return (v1.x * v2.y - v2.x * v1.y);

}

//====================================================
//
// ベクトルの長さを求める関数
//
//====================================================
float VectorSize(D3DXVECTOR2 v){

	//ルート(x二乗 + y二乗)

	return sqrt(v.x * v.x + v.y * v.y);

}