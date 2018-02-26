//======================================================================
//	BaseStar
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
#include "BaseStar.h"
#include "Input.h"



//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cBaseStarData::cBaseStarData(){


	// ������
	m_bUse = false;
	m_bDraw = false;
	m_bCreateEvent = false;
	m_bCreateEnd = false;
	m_bDestroyEvent = false;
	m_bDestroyEnd = false;
	m_bRespawnEvent = false;
	m_bRespawnEnd = false;
	m_nRespawnFrame = 0;
	m_Move = D3DXVECTOR2(0.0f, 0.0f);
	m_Destination = D3DXVECTOR2(0, 0);
	m_bCaptured = false;

	m_bEffectSetFlag = false;
}


//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cCircleOrbitMovement::cCircleOrbitMovement(){

	// ������
	m_center = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);	// �~�O���̒��S
	m_radius = D3DXVECTOR2(200.0f, 200.0f);								// ���a
	m_fRad = 0.0f;														// �p�x
	m_fSpeed = 2 * D3DX_PI / (5 * 60.0f);								// ����
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