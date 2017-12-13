//======================================================================
//	Collision.h
//	
//	�T�v�Q�FCollision
//	����ҁF�����@��
//	
//======================================================================

#ifndef ___COLLISION_H___
#define ___COLLISION_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Common.h"
#include <Windows.h>
#include "Sprite.h"

//-----------------------------
//�}�N����`
//-----------------------------
#define TEXTURE_FILENAME_CIRCLE_COLLIDER	("Image/Collision/Circle/Circle.png")	// �~�̃R���C�_�[
#define TEXTURE_FILENAME_CIRCLE_QUAD		("Image/Collision/Quad/Quad.png")		// �l�p�̃R���C�_�[


//-----------------------------
//�\���̒�`
//-----------------------------
//----�����蔻��̗v�f(�T�C�Y�@�ʒu�@���a)���܂Ƃ߂�----
typedef struct _tCollisionBody{

	D3DXVECTOR2	QuadPos = D3DXVECTOR2(0.0f, 0.0f);		//�l�p�̒��S���W
	D3DXVECTOR2	QuadSize = D3DXVECTOR2(0.0f, 0.0f);		//�l�p�̃T�C�Y
	D3DXVECTOR2	CirclePos = D3DXVECTOR2(0.0f, 0.0f);	//�~�̒��S���W
	float	fRadius = 0.0f;								//�~�̔��a

}tCollisionBody;

//-----------------------------
//�N���X��`
//-----------------------------
// �R���C�_�[�N���X(�����蔻������N���X��private�ɂ������Ďg��player�݂Ă�������)
class cCollider{

public:

	// �����蔻��̎��
	enum CollisionType{
		CIRCLE,	// �~
		QUAD	// �l�p
	};

	cCollider();	// �R���X�g���N�^
	~cCollider(){}	// �f�X�g���N�^

	
	// �~�̃R���C�_�[�̃Z�b�g
	void SetCircleCollider(D3DXVECTOR2 pos ,float radius){
		m_tColBody.CirclePos = pos;
		m_tColBody.fRadius = radius;
	}
	
	// �l�p�̃R���C�_�[�̃Z�b�g
	void SetQuadCollider(D3DXVECTOR2 pos, D3DXVECTOR2 size){
		m_tColBody.QuadPos = pos;
		m_tColBody.QuadSize = size;
	}

	// �g�p���邠���蔻��̃Z�b�g
	void SetType(CollisionType type){
		m_type = type;
	}

	// �R���C�_�[�̎擾
	tCollisionBody GetCollider(){
		return m_tColBody;
	}

	// �~�Ɖ~�̂����蔻��
	static bool CheckCollisionCircleToCircle(cCollider obj1, cCollider obj2);	

	// �`��
	void Draw();	
	
private:
	tCollisionBody	m_tColBody;	// �����蔻��̗v�f
	cSpriteParam	sprite;		// �X�v���C�g�p�����[�^�[
	CollisionType	m_type;		// �����蔻��̎��

};
#endif	//!___COLLISION_H___