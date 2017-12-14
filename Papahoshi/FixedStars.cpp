//======================================================================
//	Star
//	
//	�T�v�Q�F������
//	����ҁF�����@��
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>
#include <math.h>
#include "debugproc.h"
#include "Common.h"
#include "Texture.h"

#include "FixedStars.h"


//-----------------------------
//�}�N����`
//-----------------------------
//*************
// �P���֘A
//*************
#define FIXED_STAR_SIZE_MAX		(200)		// �P���̍ő�T�C�Y
#define FIXED_STAR_SIZE_RANGE	(60)		// �P���̃T�C�Y�̕ω���
#define FIXED_STAR_SIZE_SPEED	(0.4f)		// �P���̃T�C�Y�̕ω��X�s�[�h
#define FIXED_STAR_ROTATE_SPEED	(0.01f)		// �P���̉�]�X�s�[�h



//****************************************************************************************************************
// �P��
//****************************************************************************************************************
//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cFixedStar::cFixedStar(){

	// Sprite
	m_sprite.SetPos(D3DXVECTOR2(0.0f, 0.0f));	// ���W�Z�b�g
	m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR_LIGHT));	 // �e�N�X�`���̃Z�b�g
	m_sprite.SetVtxColorA(255);

	m_bSizeSwitch = true;

	// �P���̐F
	//m_sprite.SetVtxColor(D3DXCOLOR(125,0,0,255));

}
//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cFixedStar::~cFixedStar(){

}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cFixedStar::Update(){

	//-------------
	// �~�O������
	//-------------
	m_sprite.SetPos(moveCircle.GetMove());

	//-------------
	// �P���̓���
	//-------------
	if (m_sprite.GetSizeX() >= FIXED_STAR_SIZE_MAX){
		m_bSizeSwitch = true;
	}
	else if (m_sprite.GetSizeX() <= FIXED_STAR_SIZE_MAX - FIXED_STAR_SIZE_RANGE){
		m_bSizeSwitch = false;
	}

	if (m_bSizeSwitch){
		m_sprite.SetSize(D3DXVECTOR2(m_sprite.GetSizeX() - FIXED_STAR_SIZE_SPEED, m_sprite.GetSizeY() - FIXED_STAR_SIZE_SPEED));
		m_sprite.SetVtxColorA(m_sprite.GetVtxColorA() - 0.5f);
		m_sprite.SetRad(m_sprite.GetRad() + FIXED_STAR_ROTATE_SPEED);

	}
	else{
		m_sprite.SetSize(D3DXVECTOR2(m_sprite.GetSizeX() + FIXED_STAR_SIZE_SPEED, m_sprite.GetSizeY() + FIXED_STAR_SIZE_SPEED));
		m_sprite.SetVtxColorA(m_sprite.GetVtxColorA() + 0.5f);
		m_sprite.SetRad(m_sprite.GetRad() - FIXED_STAR_ROTATE_SPEED);

	}
}
//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cFixedStar::Draw(){
	m_sprite.Draw();
}

//=======================================================================================
//
//		���̐ݒ�
//
//=======================================================================================
void cFixedStar::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

}