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
#include <Windows.h>		//HRESULT��
#include "SceneManeger.h"	//BaseScene
#include "debugproc.h"		//printdebug

#include "Input.h"
#include "Enemy.h"
#include"Texture.h"

//-----------------------------
//�}�N����`
//-----------------------------
//----�G�l�~�[�֘A----
#define ENEMY_MOVE_SPEED	(D3DXVECTOR2(4.0f,4.0f))
#define ENEMY_DEFAULT_POS	(D3DXVECTOR2(500.0f,500.0f))

//=======================================================================================
//
//		������
//
//=======================================================================================
void cEnemy::Init(){
	
	sprite.SetPos(ENEMY_DEFAULT_POS);
	sprite.SetTexPatternDevide(4, 4);
	sprite.SetCurrentAnimPattern(0);
	//sprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_JELLY));

	collider.SetCircleCollider(sprite.GetPos(), sprite.GetSizeX() / 2.0f);
	collider.SetType(cCollider::CollisionType::CIRCLE);
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cEnemy::Unit(){

}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cEnemy::Update(){
	collider.SetCircleCollider(sprite.GetPos(), sprite.GetSizeX() / 2.0f);
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cEnemy::Draw(){

	sprite.Draw();
	collider.Draw();

	//�f�o�b�O
#ifdef _DEBUG
	PrintDebugProc("�G�l�~�[���S���W(%f,%f)\n", sprite.GetPosX(), sprite.GetPosY());
#endif
}
