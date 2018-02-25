//======================================================================
//	Title
//	
//	�T�v�Q�F�^�C�g��
//	����ҁF
//	
//======================================================================


//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "SceneTitle.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"
#include "sound.h"
#include "Transition.h"

// ���̃V�[���Ŏg���I�u�W�F�N�g


//-----------------------------
// �O���[�o��
//-----------------------------
// ���̃V�[���Ŏg���I�u�W�F�N�g�̃|�C���^��p��(�����ŃC���X�^���X�����Ȃ�)


//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneTitle::cSceneTitle() : 
m_bChange(false)
{

	// �g���I�u�W�F�N�g�̃C���X�^���X
	m_pTitleRogo = new cTitleRogo();	//�^�C�g�����S
	m_pTitleWave = new cTitleWave();	//�g
	m_pTitleShip = new cTitleShip();	//�D
	m_pMeteor = new cMeteor();
	// �w�i
	m_pBG = new cBG();
	m_pBG->SetBG(cBG::TITLE);
	//for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++)	pCircleOrbitStar[i] = new cCircleOrbitStar();	// �~�O����

	//����������
	m_pTitleRogo->Init();
	m_pTitleWave->Init();
	m_pTitleShip->Init();
	m_pMeteor->Init();
	/*
	for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++)
	{
		pCircleOrbitStar[i]->Init();
		if (!i)
			pCircleOrbitStar[i]->SetCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 100),
			D3DXVECTOR2(350.0f, 180.0f),
			D3DXVECTOR2(40.0f, 40.0f),
			5);
		else
			pCircleOrbitStar[i]->SetCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 100),
			D3DXVECTOR2(350.0f, 180.0f),
			D3DXVECTOR2(40.0f, 40.0f),
			10);
	}
	*/
	
	//----- BGM�̍Đ� ----
	PlaySound(SOUND_LABEL::SOUND_LABEL_BGM_TITLE);
	SetVolume(TITLE_BGM_VOLUME, SOUND_LABEL::SOUND_LABEL_BGM_TITLE);

	// �V�[���`�F���W�t���O�̏�����
	bSceneChangeFlag = false;
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
cSceneTitle::~cSceneTitle(){
	
	//�I������
	m_pTitleRogo->UnInit();
	m_pTitleWave->UnInit();
	m_pTitleShip->UnInit();
	m_pMeteor->UnInit();
	//for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++) pCircleOrbitStar[i]->UnInit();

	//StopSound(SOUND_LABEL_BGM000);

	// ���I�C���X�^���X����Ȃ�delete��Unit�Ƃ͕ʂɂ�����
	delete m_pTitleRogo;
	m_pTitleRogo = NULL;
	delete m_pTitleWave;
	m_pTitleWave = NULL;
	delete m_pTitleShip;
	m_pTitleShip = NULL;
	delete m_pMeteor;
	m_pMeteor = NULL;
	delete m_pBG;
	m_pBG = NULL;

	//----- BGM�̒�~ ----
	StopSound(SOUND_LABEL::SOUND_LABEL_BGM_TITLE);
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneTitle::Update(){
	//�X�V����
	m_pTitleRogo->Update(bSceneChangeFlag);
	m_pTitleShip->Update(bSceneChangeFlag);
	m_pTitleWave->Update();
	m_pMeteor->Update();
	m_pBG->Update();
	//for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++) pCircleOrbitStar[i]->Update();

	// �X�y�[�X�ŃV�[���`�F���W�t���O�𗧂Ă�
	if (GetKeyboardTrigger(DIK_SPACE)){
		bSceneChangeFlag = true;
	}

	//�D����ʊO�ɏo����V�[���`�F���W
	if (m_pTitleShip->GetShipOutFlag() && !m_bChange)
	{
		m_bChange = true;
		cSceneManeger::ChangeSceneSetTransition(cSceneManeger::GAME, cTransition::TRANSITION_DICE_SCALE_CHANGE);
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cSceneTitle::Draw(){
	//�`�揈��
	m_pBG->Draw();
	m_pMeteor->Draw();
	m_pTitleRogo->Draw();
	m_pTitleWave->Draw();
	m_pTitleShip->Draw();
	//for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++) pCircleOrbitStar[i]->Draw();
}


