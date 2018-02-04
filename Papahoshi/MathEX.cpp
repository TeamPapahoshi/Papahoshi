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

//=====================================================
//
//  ベジェ曲線上の値を求める
//
//=====================================================
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
//  線分の分割点を求める
//
//=====================================================
D3DXVECTOR2 LineSplitPoint(D3DXVECTOR2 p1, D3DXVECTOR2 p2, int m, int n){

	D3DXVECTOR2 work;

	work.x = (n * p1.x + m * p2.x) / (m + n);
	work.y = (n * p1.y + m * p2.y) / (m + n);

	return work;

}

//=====================================================
//
//  線分の傾きを求める
//
//=====================================================
float LineSlope(D3DXVECTOR2 p1, D3DXVECTOR2 p2){

	float a;

	a = (p2.y - p1.y) / (p2.x - p1.x);

	return a;

}

//=====================================================
//
//  線分の切片を求める
//
//=====================================================
float LineIntercept(D3DXVECTOR2 p1, D3DXVECTOR2 p2){

	float a, b;

	a = LineSlope(p1, p2);
	b = a * p1.x - p1.y;

	return b;
}

//=====================================================
//
//  線分の一点を交点とした垂線の傾きを求める
//
//=====================================================
float VerticalLineSlope(float slope){

	float ans;

	ans = -1 / slope;

	return ans;
}

//=====================================================
//
//  線分の一点を交点とした垂線の切片を求める
//
//=====================================================
float VerticalLineIntercept(D3DXVECTOR2 crossP, float slope){

	float ans;

	ans = crossP.y + crossP.x / slope;

	return ans;
}

//=====================================================
//
//  線分の上の点のY座標を求める
//
//=====================================================
float LineY(float x, float slope, float intersept){

	float ans;

	ans = slope * x + intersept;

	return ans;

}

//=====================================================
//
//  線分の上の点のX座標を求める
//
//=====================================================
float LineX(float y, float slope, float intersept){

	float ans;

	ans = (y - intersept) / slope;

	return ans;

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

//====================================================
//
// 単位ベクトルを求める
//
//====================================================
D3DXVECTOR2 UnitVector(D3DXVECTOR2 v){

	//
	D3DXVECTOR2 ans;
	ans = v /VectorSize(v);

	return ans;

}