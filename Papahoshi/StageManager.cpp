//======================================================================
//	StageManeger
//	
//	�T�v�Q�F�X�e�[�W�Ǘ�
//	����ҁF���� ��
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include<stdio.h>
#include<iostream>

#include"StageManager.h"
#include"debugproc.h"
#include"Texture.h"

// �e�X�e�[�W
#include "Stage01.h"
#include "Stage02.h"


//-----------------------------
//�O���[�o��
//-----------------------------
cBaseStage* cStageManager::m_pStage = NULL;							//���݂̃X�e�[�W�̏�����
cStageManager::STAGE cStageManager::m_nCurrentStageNum = STAGE_01;	//���݂̃X�e�[�W�ԍ��̏�����


//=======================================================================================
//
//	�X�e�[�W�`�F���W�֐�
//
//	����
//	stage �C���X�^���X���������X�e�[�W
//=======================================================================================
void cStageManager::ChangeStage(STAGE stage){

	if (m_pStage != NULL){
		delete m_pStage;	// �X�e�[�W�̉��
		m_pStage = NULL;
	}

	//���݂̃X�e�[�W�ԍ��̍X�V
	SetStageNum(stage);

	switch (stage){

	case STAGE_01:
		m_pStage = new cStage01();
		break;
	case STAGE_02:
		m_pStage = new cStage02();
		break;
	default:
		break;
	}


}

//=======================================================================================
//
//	
//	�I��(�ꉞ)
//	
//	
//=======================================================================================
void cStageManager::Uninit() {

	if (m_pStage != NULL){
		delete m_pStage;
		m_pStage = NULL;
	}


}

//=======================================================================================
//
//	
//	�X�V
//	
//	
//=======================================================================================
void cStageManager::Update(){


	if (m_pStage == NULL){
		//�Ȃ񂩃��b�Z�[�W�{�b�N�X�o�����ق����������ȁH
	}

	else
		m_pStage->Update();	//���݂̃V�[���̍X�V�֐����Ăяo��

	PrintDebugProc("0�ŃX�e�[�W�؂�ւ�\n");
}

//=======================================================================================
//
//	
//	�`��
//	
//	
//=======================================================================================
void cStageManager::Draw(){

	if (m_pStage == NULL){
		//�Ȃ񂩃��b�Z�[�W�{�b�N�X�o�����ق����������ȁH
	}

	else
		m_pStage->Draw();	//���݂̃V�[���̕`��֐����Ăяo��

	//�f�o�b�O�p
#ifdef _DEBUG
	PrintDebugProc("�X�e�[�W�ԍ�:%d\n", m_nCurrentStageNum);
#endif

}

//=======================================================================================
//
//	���݂̃V�[���ԍ���ݒ�
//
//=======================================================================================
void cStageManager::SetStageNum(STAGE stage){
	m_nCurrentStageNum = stage;
}