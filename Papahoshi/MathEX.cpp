//====================================================
//  Papahoshi   MathEX.cpp
//
//  ���w�I�Ȋ֐��Q
//
//====================================================

//-------------------------
// �C���N���[�h��
//-------------------------
#include "MathEX.h"

//=============================================
//
// �ݏ�(float)
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
// �ݏ�(int)
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
//  �x�W�F�Ȑ���̒l�����߂�
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
//  �����̕����_�����߂�
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
//  �����̌X�������߂�
//
//=====================================================
float LineSlope(D3DXVECTOR2 p1, D3DXVECTOR2 p2){

	float a;

	a = (p2.y - p1.y) / (p2.x - p1.x);

	return a;

}

//=====================================================
//
//  �����̐ؕЂ����߂�
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
//  �����̈�_����_�Ƃ��������̌X�������߂�
//
//=====================================================
float VerticalLineSlope(float slope){

	float ans;

	ans = -1 / slope;

	return ans;
}

//=====================================================
//
//  �����̈�_����_�Ƃ��������̐ؕЂ����߂�
//
//=====================================================
float VerticalLineIntercept(D3DXVECTOR2 crossP, float slope){

	float ans;

	ans = crossP.y + crossP.x / slope;

	return ans;
}

//=====================================================
//
//  �����̏�̓_��Y���W�����߂�
//
//=====================================================
float LineY(float x, float slope, float intersept){

	float ans;

	ans = slope * x + intersept;

	return ans;

}

//=====================================================
//
//  �����̏�̓_��X���W�����߂�
//
//=====================================================
float LineX(float y, float slope, float intersept){

	float ans;

	ans = (y - intersept) / slope;

	return ans;

}

//=====================================================
//
//  �x�N�g���̓��ς����߂�֐�
//
//=====================================================
float VectorDotProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2){

	//Dot = v1�Ev2 = x1*x2 + y1*y2 = |v1||v2|cos(��)

	return (v1.x * v2.x + v1.y * v2.y);
}

//====================================================
//
//  �x�N�g���̊O�ς����߂�֐�
//
//====================================================
float VectorCrossProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2){

	//v1�~v2= x1*y2-x2*y1 = |v1||v2|sin(��)

	return (v1.x * v2.y - v2.x * v1.y);

}

//====================================================
//
// �x�N�g���̒��������߂�֐�
//
//====================================================
float VectorSize(D3DXVECTOR2 v){

	//���[�g(x��� + y���)

	return sqrt(v.x * v.x + v.y * v.y);

}

//====================================================
//
// �P�ʃx�N�g�������߂�
//
//====================================================
D3DXVECTOR2 UnitVector(D3DXVECTOR2 v){

	//
	D3DXVECTOR2 ans;
	ans = v /VectorSize(v);

	return ans;

}