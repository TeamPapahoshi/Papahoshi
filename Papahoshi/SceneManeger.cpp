//======================================================================
//	SceneManeger
//	
//	�T�v�Q�F�V�[���Ǘ�
//	����ҁF���� ��
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include<stdio.h>
#include<iostream>

#include"SceneManeger.h"
#include"debugproc.h"
#include"Texture.h"

// �e�V�[��
#include"SceneTitle.h"
#include"SceneStageSelect.h"
#include"SceneGame.h"
//#include"SceneResult.h"

//-----------------------------
//�O���[�o��
//-----------------------------
cBaseScene* cSceneManeger::m_pScene = NULL;							//���݂̃V�[���̏�����
cSceneManeger::SCENE cSceneManeger::m_nCurrentSceneNum = TITLE;		//���݂̃V�[���ԍ��̏�����

// texture�̃C���X�^���X
cTextureManeger* tex = new cTextureManeger();

//=======================================================================================
//
//	�V�[���`�F���W�֐�
//	�����ɃV�[������������΂�����
//	
//	����
//	scene �C���X�^���X���������V�[��
//=======================================================================================
void cSceneManeger::ChangeScene(SCENE scene){


	if (m_pScene != NULL){
		delete m_pScene;	// �V�[���̉��
	}

	//���݂̃V�[���ԍ��̍X�V
	SetSceneNum(scene);

	switch (scene){
	case TITLE:
		tex->LoadTexture(TITLE);			// �e�N�X�`���̃��[�h
		m_pScene = new cSceneTitle();		// ���I�C���X�^���X&������
		break;
	case STAGE_SELECT:
		tex->LoadTexture(STAGE_SELECT);		// �e�N�X�`���̃��[�h
		m_pScene = new cSceneStageSelect();
		break;
	case GAME:
		tex->LoadTexture(GAME);				// �e�N�X�`���̃��[�h
		m_pScene = new cSceneGame();		// ���I�C���X�^���X&������
		break;
	//case RESULT:
	//	m_pScene = new cResultScene();		// ���I�C���X�^���X&������
	//	break;
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
void cSceneManeger::Uninit() {

	if (m_pScene != NULL){
		delete m_pScene;	//Uninit
		m_pScene = NULL;
		delete tex;
		tex = NULL;
	}


}

//=======================================================================================
//
//	
//	�X�V
//	
//	
//=======================================================================================
void cSceneManeger::Update(){


	if (m_pScene == NULL){
		//�Ȃ񂩃��b�Z�[�W�{�b�N�X�o�����ق����������ȁH
	}

	else
		m_pScene->Update();	//���݂̃V�[���̍X�V�֐����Ăяo��

	PrintDebugProc("space�ŃV�[���؂�ւ�\n");
}

//=======================================================================================
//
//	
//	�`��
//	
//	
//=======================================================================================
void cSceneManeger::Draw(){

	if (m_pScene == NULL){
		//�Ȃ񂩃��b�Z�[�W�{�b�N�X�o�����ق����������ȁH
	}

	else
		m_pScene->Draw();	//���݂̃V�[���̕`��֐����Ăяo��

//�f�o�b�O�p
#ifdef _DEBUG
	PrintDebugProc("�V�[���ԍ�:%d\n",m_nCurrentSceneNum);
#endif

}

//=======================================================================================
//
//	���݂̃V�[���ԍ���ݒ�
//
//=======================================================================================
void cSceneManeger::SetSceneNum(SCENE secene){
	m_nCurrentSceneNum = secene;
}