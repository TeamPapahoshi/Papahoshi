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
#define SCORE_POS_X  (SCREEN_WIDTH - 587.0f)
#define SCORE_POS_Y	 (SCREEN_HEIGHT - 520.0f)
#define SCORE_SIZE_X (100.0f)
#define SCORE_SIZE_Y (140.0f)

#define SCORE_RESULTBGM_MIN (300)
#define SCORE_RESULTBGM_MAX (480)

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
	m_pResultgirl->GetRankingDara(m_pRanking);
	m_pResultgirl->Init();

	m_pResultFont = new cResultFont();
	m_pResultFont->GetRankingData(m_pRanking);

	m_pResultStar = new cResultStar();
	m_pResultStar->GetResultGirlData(m_pResultgirl);
	m_pResultStar->Init();

	if (m_pRanking->GetChangeScoreFlag())
		m_nResultBGMFlame = SCORE_RESULTBGM_MAX;
	else
		m_nResultBGMFlame = SCORE_RESULTBGM_MIN;

	SetVolume(RESULT_BGM_VOLUME, SOUND_LABEL::SOUND_LABEL_BGM_RESULT_MAX);
	SetVolume(RESULT_BGM_VOLUME, SOUND_LABEL::SOUND_LABEL_BGM_RESULT_MIN);

	m_bBGMFlag = false;

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

	//----- BGM�̒�~ ----
	StopSound(SOUND_LABEL::SOUND_LABEL_BGM_RESULT_MAX);
	StopSound(SOUND_LABEL::SOUND_LABEL_BGM_RESULT_MIN);
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

	//BGM�Đ��t���[���̌���
	m_nResultBGMFlame--;

	if (m_nResultBGMFlame < 0 && !m_bBGMFlag)
	{
		if (m_pRanking->GetChangeScoreFlag())
			PlaySound(SOUND_LABEL::SOUND_LABEL_BGM_RESULT_MAX);
		else
			PlaySound(SOUND_LABEL::SOUND_LABEL_BGM_RESULT_MIN);

		m_bBGMFlag = true;
	}

	// �V�[���X�V
	if (GetInputButtonPress(DIK_SPACE, 0, AC_CON_BUTTON_A) ||
		GetInputButtonPress(DIK_SPACE, 0, AC_CON_BUTTON_B) ||
		GetInputButtonPress(DIK_SPACE, 0, AC_CON_BUTTON_C) ||
		GetInputButtonPress(DIK_SPACE, 0, AC_CON_BUTTON_D) ||
		GetInputButtonPress(DIK_SPACE, 0, AC_CON_BUTTON_E) ||
		GetInputButtonPress(DIK_SPACE, 0, AC_CON_BUTTON_F) ||
		GetInputButtonPress(DIK_SPACE, 0, AC_CON_BUTTON_G) ||
		GetInputButtonPress(DIK_SPACE, 0, AC_CON_BUTTON_H)
	)
	{
		cSceneManeger::ChangeSceneSetTransition(cSceneManeger::TITLE, cTransition::TRANSITION_DICE_SCALE_CHANGE);
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
	m_pResultStar->Draw();
	m_pResultFont->Draw();
	DrawScore(D3DXVECTOR2(SCORE_POS_X, SCORE_POS_Y), D3DXVECTOR2(SCORE_SIZE_X, SCORE_SIZE_Y));
}


