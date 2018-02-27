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
#include "SceneResult.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"
#include "sound.h"
#include "Transition.h"

// ���̃V�[���Ŏg���I�u�W�F�N�g
#include "Score.h"

//-----------------------------
// �}�N����`
//-----------------------------
#define SCORE_POS_X  (SCREEN_WIDTH - 430.0f)
#define SCORE_POS_Y	 (SCREEN_HEIGHT - 470.0f)
#define SCORE_SIZE_X (80.0f)
#define SCORE_SIZE_Y (100.0f)

//-----------------------------
// �O���[�o��
//-----------------------------
// ���̃V�[���Ŏg���I�u�W�F�N�g�̃|�C���^��p��(�����ŃC���X�^���X�����Ȃ�)


//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneResult::cSceneResult()
{
	//�I�u�W�F�N�g�̓��I�m��
	m_pRanking = new cRanking();

	m_pBG = new cBG();
	m_pBG->SetBG(m_pBG->RESULT);

	m_pResultgirl = new cResultgirl();

	m_pResultFont = new cResultFont();
	m_pResultFont->GetRankingData(m_pRanking);

	m_pResultStar = new cResultStar();
	m_pResultStar->GetResultGirlData(m_pResultgirl);
	m_pResultStar->Init();

	//----- �\���X�R�A�̏����� -----
	ResetPrintScore();
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
cSceneResult::~cSceneResult(){

	// ���I�C���X�^���X����Ȃ�delete��Unit�Ƃ͕ʂɂ�����
	delete m_pRanking;
	delete m_pBG;
	delete m_pResultgirl;
	delete m_pResultFont;
	delete m_pResultStar;
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneResult::Update(){
	//�X�V����
	m_pRanking->Update();

	m_pBG->Update();

	m_pResultgirl->Update();

	m_pResultFont->Update();

	m_pResultStar->Update();

	UpdateScore();

	// �V�[���X�V
	if (GetKeyboardTrigger(DIK_SPACE)){
		cSceneManeger::ChangeScene(cSceneManeger::TITLE);
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cSceneResult::Draw(){
	//�`�揈��
	m_pBG->Draw();
	m_pRanking->Draw();
	m_pResultgirl->Draw();
	m_pResultFont->Draw();
	m_pResultStar->Draw();
	DrawScore(D3DXVECTOR2(SCORE_POS_X, SCORE_POS_Y), D3DXVECTOR2(SCORE_SIZE_X, SCORE_SIZE_Y));
}


