//======================================================================
//	Player
//	
//	�T�v�Q�F�v���C���[����(��)
//	����ҁF
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "SceneManeger.h"	//BaseScene
#include "debugproc.h"		//printdebug
#include "d3dx9.h"			//D3DXVECTOR2��

#include "Input.h"
#include "Player.h"
#include "Texture.h"


//-----------------------------
//�}�N����`
//-----------------------------
//----�v���C���[�֘A----
#define PLAYER_DEFAULT_POS	(D3DXVECTOR2(100.0f,100.0f))
#define PLAYER_MOVE_SPEED	(4.0f)


//-----------------------------
//�O���[�o��
//-----------------------------
bool g_hit = false;	//��

//=======================================================================================
//
//		������
//
//=======================================================================================
void cPlayer::Init(){ //pTex

	// �����ŏ��������Ȃ��Ƃ��ꂼ��̃N���X�̃R���X�g���N�^�̒l�ŏ����������

	// Sprite
	sprite.SetPos(PLAYER_DEFAULT_POS);										// ���W�Z�b�g
	sprite.SetTexPatternDevide(4, 4);										// �e�N�X�`���̕������̃Z�b�g
	sprite.SetCurrentAnimPattern(0);										// �e�N�X�`���̌��݂̃p�^�[���ԍ��Z�b�g
	sprite.SetTexture(cTextureManager::GetTextureTitle(TEX_TITLE_JELLY));	// �e�N�X�`���̃Z�b�g

	// Collider
	collider.SetType(cCollider::CollisionType::CIRCLE);						// �g�p���邠���蔻����w��
	collider.SetCircleCollider(sprite.GetPos(), sprite.GetSizeX() / 2.0f);	// �����蔻��̍��W�Z�b�g(Update�̂��킷�꒍��)
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cPlayer::Unit(){
	// StopSound�Ƃ��������̉���Ƃ�
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cPlayer::Update(){
	
	//�ړ�
	if (GetKeyboardPress(DIK_RIGHT)){
		sprite.SetPosX(sprite.GetPosX() + PLAYER_MOVE_SPEED);
	}
	else if (GetKeyboardPress(DIK_LEFT)){
		sprite.SetPosX(sprite.GetPosX() - PLAYER_MOVE_SPEED);
	}
	else if (GetKeyboardPress(DIK_UP)){
		sprite.SetPosY(sprite.GetPosY() - PLAYER_MOVE_SPEED);
	}
	else if (GetKeyboardPress(DIK_DOWN)){
		sprite.SetPosY(sprite.GetPosY() + PLAYER_MOVE_SPEED);
	}

	// �����蔻��̈ʒu�̍X�V
	collider.SetCircleCollider(sprite.GetPos(), sprite.GetSizeX() / 2.0f);

	// �A�j���[�V����
	// sprite.SetCurrentAnimPattern(sprite.GetCurrentAnimPattern() + 1);
	

	g_hit = false;

}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cPlayer::Draw(){

	//�`��
	sprite.Draw();
	collider.Draw();

//�f�o�b�O
#ifdef _DEBUG
	PrintDebugProc("�v���C���[���S���W(%f,%f)\n", sprite.GetPosX(), sprite.GetPosY());
	PrintDebugProc("��������:%d\n", g_hit);
#endif
}

//=======================================================================================
//
//		�v���C���[���G�l�~�[�ƏՓ˂����Ƃ��̃v���C���[�̏���
//
//=======================================================================================
void cPlayer::OnColidToEnemy(){
	g_hit = true;
}