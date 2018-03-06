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
#include <stdio.h>
#include <iostream>

#include "SceneManeger.h"
#include "debugproc.h"
#include "Texture.h"

// �e�V�[��
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneTraning.h"

//-----------------------------
//�O���[�o��
//-----------------------------
cBaseScene* cSceneManeger::m_pScene = NULL;							//���݂̃V�[���̏�����
cSceneManeger::SCENE cSceneManeger::m_nCurrentSceneNum = TITLE;		//���݂̃V�[���ԍ��̏�����
cTransition* pTransition = NULL;									//�g�����W�V����

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
		delete m_pScene;				// �V�[���̉��
		GetEffectManeger()->Uninit();	// �G�t�F�N�g�̏I������
	}

	//���݂̃V�[���ԍ��̍X�V
	SetSceneNum(scene);
	switch (scene){
	case TITLE:
		tex->LoadTexture(TITLE);			// �e�N�X�`���̃��[�h
		m_pScene = new cSceneTitle();		// ���I�C���X�^���X&������
		break;;
	case GAME:
		tex->LoadTexture(GAME);				// �e�N�X�`���̃��[�h
		m_pScene = new cSceneGame();		// ���I�C���X�^���X&������
		break;
	case RESULT:
		tex->LoadTexture(RESULT);
		m_pScene = new cSceneResult();		// ���I�C���X�^���X&������
		break;
	case TRANING:
		tex->LoadTexture(GAME);				// �e�N�X�`���̃��[�h
		m_pScene = new cSceneTraning();
	default:
		break;
	}


}


//=======================================================================================
//
//	�g�����W�V�����t���̃V�[���`�F���W�֐�
//	��ʐ؂�ւ����ʕt���ŌĂяo���Ƃ���
//	
//	����
//	scene �C���X�^���X���������V�[��
//  transition �Z�b�g����g�����W�V�����ԍ�
//=======================================================================================
void cSceneManeger::ChangeSceneSetTransition(SCENE scene, cTransition::TRANSITION_TYPE transition){

	switch (transition)
	{
	case cTransition::TRANSITION_FADE:
		pTransition = new cTransitonFade();
		pTransition->SetTransition(scene);
		break;
	case cTransition::TRANSITION_DICE_SCALE_CHANGE:
		pTransition = new cTransitonDiceScaleChange();
		pTransition->SetTransition(scene);
		break;
	case cTransition::TRANSITION_ONCE_ROTATION:
		pTransition = new cTransitonOnceRotation();
		pTransition->SetTransition(scene);
		break;
	case cTransition::TRANSITION_TILE_CREATE_RANDOM:
		pTransition = new cTransitionTileCreateRandom();
		pTransition->SetTransition(scene);
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

	//�g�����W�V����������ꍇ�͎��s
	if (pTransition){
		pTransition->Update();
		if (pTransition->FinishCall()){
			delete pTransition;
			pTransition = NULL;
		}
	}

	
}

//=======================================================================================
//
//	
//	�`��
//	
//	
//=======================================================================================
void cSceneManeger::Draw(){


//�f�o�b�O�p
#ifdef _DEBUG
	PrintDebugProc("���������V�[����������\n");
	PrintDebugProc("space�ŃV�[���؂�ւ�\n");
	PrintDebugProc("�V�[���ԍ�:%d\n", m_nCurrentSceneNum);
	PrintDebugProc("����������������������\n");
#endif

	if (m_pScene == NULL){
		//�Ȃ񂩃��b�Z�[�W�{�b�N�X�o�����ق����������ȁH
	}

	else
		m_pScene->Draw();	//���݂̃V�[���̕`��֐����Ăяo��

	//�g�����W�V����������ꍇ�͎��s
	if (pTransition)
		pTransition->Draw();
}

//=======================================================================================
//
//	���݂̃V�[���ԍ���ݒ�
//
//=======================================================================================
void cSceneManeger::SetSceneNum(SCENE secene){
	m_nCurrentSceneNum = secene;
}

//=======================================================================================
//
//	���݂̃V�[���ԍ����󂯎��
//
//=======================================================================================
cSceneManeger::SCENE cSceneManeger::GetSceneNum(void){
	return m_nCurrentSceneNum;
}