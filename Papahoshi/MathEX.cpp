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

//---------------------------------------------------
//
//  �x�W�F�Ȑ���̒l�����߂�
//
//---------------------------------------------------
D3DXVECTOR2 BezierCurve(float t, D3DXVECTOR2 cp1, D3DXVECTOR2 cp2, D3DXVECTOR2 cp3, D3DXVECTOR2 cp4){

	D3DXVECTOR2 work;

	//work.x = (1 - t)

	return work;

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