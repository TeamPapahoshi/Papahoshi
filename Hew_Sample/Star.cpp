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
#include "debugproc.h"		//printdebug
#include <math.h>
#include "Common.h"

#include"Star.h"


//-----------------------------
//�}�N����`
//-----------------------------
#define ROUND_TIME	(5)														// �������̂ɂ����鎞��
#define STAR_SIZE	(D3DXVECTOR2(20.0f,20.0f))								// ���̃T�C�Y
#define STAR_CENTER	(D3DXVECTOR2(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f))		// ���̋O���̒��S
#define STAR_RADIUS	(D3DXVECTOR2(200.0f,100.0f))							// �O�����a


//=======================================================================================
//
//		������
//
//=======================================================================================
void cCircleOrbitStar::Init(LPDIRECT3DTEXTURE9* pTex){

	// Sprite
	m_sprite.SetPos(D3DXVECTOR2(0.0f,0.0f));	// ���W�Z�b�g
	m_sprite.SetTexPatternDevide(4, 4);			// �e�N�X�`���̕������̃Z�b�g
	m_sprite.SetCurrentAnimPattern(0);			// �e�N�X�`���̌��݂̃p�^�[���ԍ��Z�b�g
	m_sprite.SetTexture(pTex);					// �e�N�X�`���̃Z�b�g

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
void cCircleOrbitStar::SetcCircleOrbitStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

	// ��
	m_center = center;
	m_radius = radius;
	m_sprite.SetSize(size);
	m_second = second;
}
