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
#include <Windows.h>		//HRESULT��
#include <math.h>
#include "debugproc.h"		//printdebug
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

// ���private
//float nearDist=99999;						// ��ԋ߂��P���̋���
//float nowDist=0;							// ����������󂯎��������


//****************************************************************************************************************
// �~�O���̐�
//****************************************************************************************************************
//=======================================================================================
//
//		������
//
//=======================================================================================
void cCircleOrbitStar::Init(){

	// Sprite
	m_sprite.SetPos(D3DXVECTOR2(0.0f,0.0f));	// ���W�Z�b�g
	m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR));					// �e�N�X�`���̃Z�b�g
	m_sprite.SetVtxColorA(200);

	// �������l(�Z�b�g�Ȃ��̎�)
	m_center = STAR_CENTER;
	m_radius = STAR_RADIUS;
	m_sprite.SetSize(STAR_SIZE);
	m_second = ROUND_TIME;
}	

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cCircleOrbitStar::UnInit(){

}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cCircleOrbitStar::Update(){

	
	if (m_second != 0){
		// �p�x�X�V
		m_rad += 2 * D3DX_PI / ((float)m_second * 60.0f);

		// ���W�X�V
		m_sprite.SetPosX(m_center.x - m_radius.x*cos(m_rad));
		m_sprite.SetPosY(m_center.y - m_radius.y*sin(m_rad));
	}
	else{
		m_sprite.SetPosX(m_center.x - m_radius.x);
		m_sprite.SetPosY(m_center.y - m_radius.y);
	}
}
//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cCircleOrbitStar::Draw(){
	m_sprite.Draw();
}

//=======================================================================================
//
//		���̐ݒ�
//
//=======================================================================================
void cCircleOrbitStar::SetCircleOrbitStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

	// ��
	m_center = center;
	m_radius = radius;
	m_sprite.SetSize(size);
	m_second = second;

	//// �t�@�C���p
	////**********************************************************************************
	//// �i�[�pwork
	//tSetCircleOrbitStaretStar work;
	//work.center = m_center;
	//work.rad = m_rad;
	//work.radius = m_radius;
	//work.second = m_second;

	//// �ݒ�p�z��ɂ��ǉ�
	//a_SetCircleOrbitStaretStar.push_back(work);
	////**********************************************************************************
}
//=======================================================================================
//
//		���������邩�����Ȃ����̐ݒ�
//
//=======================================================================================
void cCircleOrbitStar::StarVisibility(float distance){

	//// ��ԋ߂��P���Ƃ̔�����Ƃ�
	//nowDist = distance;	// �������i�[
	//if (nearDist > nowDist){	// ���������ŒZ�����̂ق����傫���Ȃ�X�V
	//	nearDist = nowDist;
	//}

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
//		������
//
//=======================================================================================
void cFixedStar::Init(){

	// Sprite
	m_sprite.SetPos(D3DXVECTOR2(0.0f, 0.0f));	// ���W�Z�b�g
	m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR_LIGHT));	 // �e�N�X�`���̃Z�b�g
	m_sprite.SetVtxColorA(200);

	// �P���̐F
	m_sprite.SetVtxColor(D3DXCOLOR(125,0,0,255));

	// �������l(�Z�b�g�Ȃ��̎�)
	m_center = STAR_CENTER;
	m_radius = STAR_RADIUS;
	m_sprite.SetSize(STAR_SIZE);
	m_second = ROUND_TIME;

}
//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cFixedStar::UnInit(){

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
	if (m_second != 0){
		// �p�x�X�V
		m_rad += 2 * D3DX_PI / ((float)m_second * 60.0f);

		// ���W�X�V
		m_sprite.SetPosX(m_center.x - m_radius.x*cos(m_rad));
		m_sprite.SetPosY(m_center.y - m_radius.y*sin(m_rad));
	}
	else{
		m_sprite.SetPosX(m_center.x - m_radius.x);
		m_sprite.SetPosY(m_center.y - m_radius.y);
	}

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

	m_center = center;
	m_radius = radius;
	m_sprite.SetSize(size);
	m_second = second;

}