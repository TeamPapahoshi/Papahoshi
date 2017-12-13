//======================================================================
//	Player
//	
//	�T�v�Q�F�v���C���[(��)
//	����ҁF
//	
//======================================================================
#ifndef ___PLAYER_H___
#define ___PLAYER_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Sprite.h"
#include "Collision.h"


//-----------------------------
//�N���X��`
//-----------------------------
class cPlayer{

public:
	cPlayer(){}		// �R���X�g���N�^
	~cPlayer(){}	// �f�X�g���N�^

	// �����͉�������p�������Ă����������I�[�o���C�h
	void Init(LPDIRECT3DTEXTURE9* pTex);	// ������ �e�N�X�`���̃|�C���^���󂯎����
	void Unit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

	// �G�l�~�[�Ɠ����������̏���
	void OnColidToEnemy();

	// �v���C���[�̂����蔻��̎擾
	cCollider GetCollider(){
		return collider;
	}

private:
	// �v���C���[�ɕK�v�Ȃ���
	cSpriteParam	sprite;			// �X�v���C�g�̃X�e�[�^�X
	cCollider		collider;		// �����蔻��
};
#endif	//!___PLAYER_H___



