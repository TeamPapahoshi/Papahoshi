//======================================================================
//	Collision.cpp
//	
//	�T�v�Q�FCollision�̏���
//	����ҁF�����@��
//	
//======================================================================
#include "Collision.h"
#include "Sprite.h"
#include <cmath>	//�����̐�Βl�p

using namespace std;

//------------------------------
//�O���[�o�� 
//------------------------------

//======================================================================
//	
//
//		�R���X�g���N�^
//		
//
//======================================================================
cCollider::cCollider(){

	m_type = CIRCLE;								// �ݒ肵�Ȃ��ꍇ�͉~
	m_tColBody.QuadPos = D3DXVECTOR2(0.0f, 0.0f);	// �l�p�̒��S���W
	m_tColBody.QuadSize = D3DXVECTOR2(0.0f, 0.0f);	// �l�p�̃T�C�Y
	m_tColBody.CirclePos = D3DXVECTOR2(0.0f, 0.0f);	// �~�̒��S���W
	m_tColBody.fRadius = 0.0f;						// �~�̔��a
	m_tColBody.TriangleVertexPos[0] = D3DXVECTOR2(0.0f, 0.0f);	//�O�p�`�̒��_
	m_tColBody.TriangleVertexPos[1] = D3DXVECTOR2(0.0f, 0.0f);
	m_tColBody.TriangleVertexPos[2] = D3DXVECTOR2(0.0f, 0.0f);
	sprite.SetVtxColorA(100.0f);					// �������ŃZ�b�g
}


//======================================================================
//	
//
//		�`��
//		
//
//======================================================================
void cCollider::Draw(){

	// sprite�̍��W��colider�̍��W���Z�b�g
	if (m_type == CIRCLE){
		sprite.SetPos(m_tColBody.CirclePos);
		sprite.SetSize(D3DXVECTOR2(m_tColBody.fRadius*2.0f, m_tColBody.fRadius*2.0f));
		sprite.LoadTexture(TEXTURE_FILENAME_CIRCLE_COLLIDER);
	}
	if (m_type == QUAD){
		sprite.SetPos(m_tColBody.QuadPos);
		sprite.SetSize(m_tColBody.QuadSize);
		sprite.LoadTexture(TEXTURE_FILENAME_CIRCLE_QUAD);
	}

	// �`��
	sprite.Draw();
}

//======================================================================
//	
//		�~�Ɖ~�̂����蔻��
//
//		����
//		
//
//====================================================================== 
bool cCollider::CheckCollisionCircleToCircle(cCollider obj1, cCollider obj2){

	//-----����-----
	if ((obj1.GetCollider().CirclePos.x - obj2.GetCollider().CirclePos.x)*(obj1.GetCollider().CirclePos.x - obj2.GetCollider().CirclePos.x) +
		(obj1.GetCollider().CirclePos.y - obj2.GetCollider().CirclePos.y)*(obj1.GetCollider().CirclePos.y - obj2.GetCollider().CirclePos.y)
		<= (obj1.GetCollider().fRadius + obj2.GetCollider().fRadius)*(obj1.GetCollider().fRadius + obj2.GetCollider().fRadius)){

		return true;
	}
	return false;
}

//====================================================================
//
//  �~�ƎO�p�̓����蔻��
//
//====================================================================
bool cCollider::CheckCollisionCircleToTriangle(cCollider circle, cCollider triangle){

	//--------- �ϐ��錾 ----------
	D3DXVECTOR2 triVector[3];	//�O�p�`���\������x�N�g��
	D3DXVECTOR2 TtoCVector[3];	//�O�p�`�̒��_����~�̒��S�_�֌������x�N�g��
	int i, next;	//���[�v�p
	D3DXVECTOR2 work1, work2, work3;	//�v�Z�p

	//------ �x�N�g���̌v�Z --------
	for (i = 0; i < 3; i++){
		//���̒l��ݒ�
		next = i + 1;
		if (next == 2)
			next = 0;
		//�O�p�`���\������x�N�g���@*** �����G���[�o���炱���̌��������� *** �������ς��܂��I�I
		triVector[i].x = triangle.GetCollider().TriangleVertexPos[next].x - triangle.GetCollider().TriangleVertexPos[i].x;
		triVector[i].y = triangle.GetCollider().TriangleVertexPos[next].y - triangle.GetCollider().TriangleVertexPos[i].y;
		//�O�p�`�̒��_����~�̒��S�_�֌������x�N�g��
		TtoCVector[i].x = circle.GetCollider().CirclePos.x - triangle.GetCollider().TriangleVertexPos[i].x;
		TtoCVector[i].y = circle.GetCollider().CirclePos.y - triangle.GetCollider().TriangleVertexPos[i].y;
	}

	//---------- �O�p�`�̐����Ƃ̓����蔻�� --------------
	for (int i = 0; i < 3; i++){

		//���̒l��ݒ�
		next = i + 1;
		if (next == 2)
			next = 0;
		//����
		work1.x = triVector[i].x * TtoCVector[i].x;
		work1.y = triVector[i].y * TtoCVector[i].y;
		work2.x = triVector[i].x * TtoCVector[next].x;
		work2.y = triVector[i].y * TtoCVector[next].y;
		work3.x = abs(triVector[i].x * TtoCVector[i].x) / abs(triVector[i].x);
		work3.y = abs(triVector[i].y * TtoCVector[i].y) / abs(triVector[i].y);
		//if (work1 >= 0 && work2 <= 0 && work3 <= circle.GetCollider().fRadius){
		//
		//}

	}
	return false;
}


float CalculateDistanceAtoB(D3DXVECTOR2 posA, D3DXVECTOR2 posB){

	float ans;// �����i�[�p
	ans = sqrt((posA.x - posB.x)*(posA.x - posB.x) + (posA.y - posB.y)*(posA.y - posB.y));
	return ans;
}





// ��ɒǉ���Ă�

//======================================================================
//	
//		�~�Ǝl�p�̂����蔻��
//
//		����
//		circlePos	�~�̒��S���W
//		radius		�~�̔��a
//		quadPos		�l�p�`���W
//		quadSize	�l�p�`�̃T�C�Y
//
//======================================================================
//bool CheckCollisionCircleToQuad2(D3DXVECTOR2 circlePos, float radius, D3DXVECTOR2 quadPos, D3DXVECTOR2  quadSize){
//
//
//	//-----�ϐ��錾-----
//	float Xc, Yc;		//�~�̒��S���W
//	float X1, Y1;		//�l�p�`�̍�����W
//	float X2, Y2;		//�l�p�`�̍�����W
//	float r;			//�~�̔��a
//
//	//-----�l�̑��-----
//	Xc = circlePos.x;
//	Yc = circlePos.y;
//	X1 = quadPos.x - quadSize.x / 2.0f;
//	Y1 = quadPos.y - quadSize.y / 2.0f;
//	X2 = quadPos.x + quadSize.x / 2.0f;
//	Y2 = quadPos.y + quadSize.y / 2.0f;
//	r = radius;
//
//
//	//�����͂Ƃ炸�ɂ������Ă��邩�ǂ�������
//	if ((Xc >= X1) && (Xc <= X2) && (Yc >= Y1 - r) && (Yc <= Y2 - r) || (Xc <= X2 + r) && (Xc >= X1 - r)
//		&& (Yc >= Y1) && (Yc <= Y2) || (X1 - Xc)*(X1 - Xc) + (Y1 - Yc)*(Y1 - Yc) < r*r ||
//		(X2 - Xc)*(X2 - Xc) + (Y1 - Yc)*(Y1 - Yc) < r*r || (X2 - Xc)*(X2 - Xc) + (Y2 - Yc)*(Y2 - Yc) < r*r
//		|| (X1 - Xc)*(X1 - Xc) + (Y2 - Yc)*(Y2 - Yc) < r*r){
//
//		return true;
//
//	}
//
//	//������Ȃ������Ƃ�
//	return false;
//}
//
////======================================================================
////	
////		�~�Ǝl�p�̂����蔻��
////
////		����
////		circlePos	�~�̒��S���W
////		radius		�~�̔��a
////		quadPos		�l�p�`���W
////		quadSize	�l�p�`�̃T�C�Y
////
////======================================================================
//int CheckCollisionCircleToQuad(D3DXVECTOR2 circlePos, float radius ,D3DXVECTOR2 quadPos, D3DXVECTOR2  quadSize){
//
//
//	//-----�ϐ��錾-----
//	float Xc, Yc;		//�~�̒��S���W
//	float X1, Y1;		//�l�p�`�̍�����W
//	float X2, Y2;		//�l�p�`�̍�����W
//	float r;			//�~�̔��a
//
//	//-----�l�̑��-----
//	Xc = circlePos.x;
//	Yc = circlePos.y;
//	X1 = quadPos.x - quadSize.x / 2.0f;
//	Y1 = quadPos.y - quadSize.y / 2.0f;
//	X2 = quadPos.x + quadSize.x / 2.0f;
//	Y2 = quadPos.y + quadSize.y / 2.0f;
//	r = radius;
//
//
//	//----��----
//	if ((Xc >= X1) && (Xc <= X2) && (Yc >= Y1 - r) && (Yc <= Y2))//Y1->Y2
//		return COL_UP;
//
//	//----��----
//	if ((Xc >= X1) && (Xc <= X2) && (Yc <= Y2 + r) && (Yc >= Y1))//Y2->Y1
//		return COL_DOWN;
//
//	//----�E----
//	if ((Xc <= X2 + r) && (Xc >= X1) && (Yc >= Y1) && (Yc <= Y2))//X2->X1
//		return COL_RIGHT;
//
//	//----��----
//	if ((Xc >= X1 - r) && (Xc <= X2) && (Yc >= Y1) && (Yc <= Y2))//X1->x2
//		return COL_LEFT;
//
//	//������Ȃ������Ƃ�
//	return false;
//}
//
////======================================================================
////	
////		�l�p�Ǝl�p�̂����蔻��
////
////		����
////		�I�u�W�F�N�g1����p�p�����[�^,�I�u�W�F�N�g2����p�p�����[�^
////
////======================================================================
//bool CheckCollisionQuadToQuad(tQuadCollider q1, tQuadCollider q2){
//
//	//������W�i�[
//	float Quad1_X = q1.pos.x - q1.size.x / 2.0f;
//	float Quad2_X = q2.pos.x - q2.size.x / 2.0f;
//
//	float Quad1_Y = q1.pos.y - q1.size.y / 2.0f;
//	float Quad2_Y = q2.pos.y - q2.size.y / 2.0f;
//
//	if (Quad2_X <= Quad1_X + q1.size.x &&
//		Quad2_X + q2.size.x >= Quad1_X &&
//		Quad2_Y <= Quad1_Y + q1.size.y &&
//		Quad2_Y + q2.size.y >= Quad1_Y){
//
//		return true;
//
//	}
//
//	return false;
//}

