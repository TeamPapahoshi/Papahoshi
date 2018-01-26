//======================================================================
//	BlackHole
//	
//	�T�v�Q�F�u���b�N�z�[��
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
#include "rand.h"

#include "BlackHole.h"
#include <fstream>

#define STAR_SIZE	(100)

#define VACUUM_RANGE	(200)
#define DELETE_RANGE	(20)

//****************************************************************************************************************
// �u���b�N�z�[��
//****************************************************************************************************************
//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cBlackHole::cBlackHole(){

	// �����̏�����
	CRandam::InitRand();

	// ���̍ő吔�@��Ƀt�@�C������Ǎ�������
	m_nMaxNum = MAX_BLACK_HOLE_NUM;
	m_nCurrentNum = MAX_BLACK_HOLE_NUM;

	// ���I�m��
	m_pStarData = new tBlackHoleData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// ������
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_BLACK_HOLE));
		m_pStarData[nCuntStar].t_bUse = false;

		// �����蔻��
		m_pStarData[nCuntStar].t_VacuumCollider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_VacuumCollider.SetCircleCollider(m_pStarData->t_Sprite.GetPos(), VACUUM_RANGE);

		m_pStarData[nCuntStar].t_DeleteCollider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_DeleteCollider.SetCircleCollider(m_pStarData->t_Sprite.GetPos(), DELETE_RANGE);
	}

	//�@�t���[���J�E���g
	m_nRespawnFream = 0;

	// 
	m_bCapchared = false;


}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cBlackHole::~cBlackHole(){

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cBlackHole::Update(){

}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cBlackHole::Draw(){
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		m_pStarData[nCuntStar].t_Sprite.Draw();
		m_pStarData[nCuntStar].t_VacuumCollider.Draw();
		m_pStarData[nCuntStar].t_DeleteCollider.Draw();
	}
}

//=======================================================================================
//
//		���̐ݒ�
//
//=======================================================================================
void cBlackHole::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

}
