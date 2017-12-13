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

#include "Star.h"


//-----------------------------
//�}�N����`
//-----------------------------
//*************
// ���̏����l
//*************
#define ROUND_TIME	(5)														// �������̂ɂ����鎞��
#define STAR_SIZE	(D3DXVECTOR2(20.0f,20.0f))								// ���̃T�C�Y
#define STAR_CENTER	(D3DXVECTOR2(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f))		// ���̋O���̒��S
#define STAR_RADIUS	(D3DXVECTOR2(200.0f,100.0f))							// �O�����a

//*************
// �P���֘A
//*************
#define FIXED_STAR_SIZE_MAX		(200)		// �P���̍ő�T�C�Y
#define FIXED_STAR_SIZE_RANGE	(60)		// �P���̃T�C�Y�̕ω���
#define FIXED_STAR_SIZE_SPEED	(0.4f)		// �P���̃T�C�Y�̕ω��X�s�[�h
#define FIXED_STAR_ROTATE_SPEED	(0.01f)		// �P���̉�]�X�s�[�h


//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cCircleOrbitMovement::cCircleOrbitMovement(){

	// ������
	m_center	= D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);	// �~�O���̒��S
	m_radius	= D3DXVECTOR2(200.0f, 200.0f);								// ���a
	m_fRad		= 0.0f;														// �p�x
	m_fSpeed	= 2 * D3DX_PI / (5 * 60.0f);								// ����
}


//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cCircleOrbitMovement::~cCircleOrbitMovement(){
}

//=======================================================================================
//
//		Move
//
//=======================================================================================
D3DXVECTOR2 cCircleOrbitMovement::GetMove(){

	// �ړ���̍��W�i�[�p
	D3DXVECTOR2	pos;

	// �p�x�X�V
	m_fRad += m_fSpeed;

	// ���W�X�V
	pos.x = m_center.x - m_radius.x*cos(m_fRad);
	pos.y = m_center.y - m_radius.y*sin(m_fRad);

	return pos;
}



//****************************************************************************************************************
// ���ʂ̐�
//****************************************************************************************************************
//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cNormalStar::cNormalStar(){

	// Sprite
	m_sprite.SetPos(D3DXVECTOR2(0.0f,0.0f));	
	m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR));
	m_sprite.SetVtxColorA(200);

}	

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cNormalStar::~cNormalStar(){

}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cNormalStar::Update(){

	// ���W�X�V
	m_sprite.SetPos(moveCircle.GetMove());

}
//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cNormalStar::Draw(){
	m_sprite.Draw();
}

//=======================================================================================
//
//		���̐ݒ�
//
//=======================================================================================
void cNormalStar::SetCircleOrbitStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

}

//=======================================================================================
//
//		���������邩�����Ȃ����̐ݒ�
//
//=======================================================================================
void cNormalStar::StarVisibility(float distance){

	// ���l�̕ω�
	if (distance != 0){
		m_sprite.SetVtxColorA(255 / distance * 20);
	}
	else{
		m_sprite.SetVtxColorA(255);
	}
}

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
void cFixedStar::SetFixedStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

}