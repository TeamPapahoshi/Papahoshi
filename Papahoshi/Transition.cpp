//======================================================================
//	Transition
//	
//	�T�v�Q�F��ʐ؂�ւ�����
//	����ҁF�㓡 ����
//	
//======================================================================

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Transition.h"
#include "Common.h"
#include "SceneManeger.h"
#include <stdlib.h>
#include <time.h>

//-----------------------------
// �萔�E�}�N����`
//-----------------------------
//�e�N�X�`��
#define TEX_FILENAME_STAR "Image/Transition/Star.png"
#define TEX_FILENAME_WHITE "Image/Transition/White.png"

//�_�C�X�n
#define MAX_SIZE_DICE (300.0f)
#define NEXT_MOVE_SIZE_DICE (80.0f)
#define INCREMENT_SIZE_DICE (5.0f)

//�t�F�[�h�n
#define INCREMENT_ALPHA (10)

//�g��n
#define MAX_SIZE_ONCE (SCREEN_WIDTH * 5.0f)
#define INCREMENT_SIZE_ONCE (60.0f)

//��]�n
#define ROTATION_SPEED (0.04f)

//�����n
#define UPDATE_FRAME (2)

bool cTransition::m_bFinish = false;

//====================================
// �I���񍐊֐�
//====================================
bool cTransition::FinishCall(){
	return m_bFinish;
}

//====================================
// ���̃V�[���ԍ����Z�b�g
//====================================
void cTransition::SetTransition(int nextScene){
	m_nextScene = nextScene;
}


//***************************************************************************//
//******************************** �t�F�[�h *********************************//
//***************************************************************************//

//========================================
// �R���X�g���N�^
//========================================
cTransitonFade::cTransitonFade() : cTransition(){

	spriteParam.LoadTexture(TEX_FILENAME_WHITE);
	spriteParam.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
	spriteParam.SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	spriteParam.SetTexPatternDevide(1, 1);
	spriteParam.SetCurrentAnimPattern(0);
	spriteParam.SetVtxColorA(0);

}

//========================================
// �f�X�g���N�^
//========================================
cTransitonFade::~cTransitonFade(){



}

//========================================
// �X�V����
//========================================
void cTransitonFade::Update(){

	if (!m_bOut){
		spriteParam.SetVtxColorA(spriteParam.GetVtxColorA() + INCREMENT_ALPHA);
		if (spriteParam.GetVtxColorA() >= 255){
			spriteParam.SetVtxColorA(255);
			m_bOut = true;
			cSceneManeger::ChangeScene((cSceneManeger::SCENE)m_nextScene);
		}
	}
	else{
		spriteParam.SetVtxColorA(spriteParam.GetVtxColorA() - INCREMENT_ALPHA);
		if (spriteParam.GetVtxColorA() <= 0){
			spriteParam.SetVtxColorA(0);
			m_bFinish = true;
		}
	}

}

//========================================
// �`�揈��
//========================================
void cTransitonFade::Draw(){

	spriteParam.Draw();

}



//***************************************************************************//
//******************* �����̖ڂ̉摜���g��k�������� **********************//
//***************************************************************************//

//========================================
// �R���X�g���N�^
//========================================
cTransitonDiceScaleChange::cTransitonDiceScaleChange() : cTransition(){

	D3DXVECTOR2 work;

	//�摜���̏�����
	for (int y = 0; y < DICE_Y_NUM; y++){
		for (int x = 0; x < DICE_X_NUM; x++){
			spriteParam[y][x].LoadTexture(TEX_FILENAME_STAR);
			work.x = (SCREEN_WIDTH / (DICE_X_NUM * 2)) + (SCREEN_WIDTH / DICE_X_NUM * x);
			work.y = (SCREEN_HEIGHT / (DICE_Y_NUM * 2)) + (SCREEN_HEIGHT / DICE_Y_NUM * y);
			spriteParam[y][x].SetPos(work);
			spriteParam[y][x].SetSize(D3DXVECTOR2(0.0f, 0.0f));
			spriteParam[y][x].SetTexPatternDevide(1, 1);
			spriteParam[y][x].SetCurrentAnimPattern(0);
		}
	}

}

//========================================
// �f�X�g���N�^
//========================================
cTransitonDiceScaleChange::~cTransitonDiceScaleChange(){



}

//========================================
// �X�V����
//========================================
void cTransitonDiceScaleChange::Update(){

	//�傫���Ȃ��
	if (!m_bOut){
		for (int y = 0; y < DICE_Y_NUM; y++){
			if (y == 0 || spriteParam[y - 1][0].GetSizeX() >= NEXT_MOVE_SIZE_DICE){
				for (int x = 0; x < DICE_X_NUM; x++){
					spriteParam[y][x].SetSize(D3DXVECTOR2(spriteParam[y][0].GetSizeX() + INCREMENT_SIZE_DICE, spriteParam[y][0].GetSizeY() + INCREMENT_SIZE_DICE));
				}
			}
		}
		if (spriteParam[DICE_Y_NUM - 1][0].GetSizeX() >= MAX_SIZE_DICE){
			cSceneManeger::ChangeScene((cSceneManeger::SCENE)m_nextScene);
			m_bOut = true;
		}
	}
	//�������Ȃ��
	else{
		for (int y = 0; y < DICE_Y_NUM; y++){
			for (int x = 0; x < DICE_X_NUM; x++){
				spriteParam[y][x].SetSize(D3DXVECTOR2(spriteParam[y][0].GetSizeX() - INCREMENT_SIZE_DICE, spriteParam[y][0].GetSizeY() - INCREMENT_SIZE_DICE));
				if (spriteParam[y][x].GetSizeX() < 0.0f)
					spriteParam[y][x].SetSize(D3DXVECTOR2(0.0f, 0.0f));
			}
		}
		if (spriteParam[0][0].GetSizeX() <= 0.0f)
			m_bFinish = true;
	}

}

//========================================
// �`�揈��
//========================================
void cTransitonDiceScaleChange::Draw(){

	for (int y = 0; y < DICE_Y_NUM; y++){
		for (int x = 0; x < DICE_X_NUM; x++){
			spriteParam[y][x].Draw();
		}
	}

}


//***************************************************************************//
//************************ ��]���Ȃ���傫���Ȃ�� *************************//
//***************************************************************************//

//========================================
// �R���X�g���N�^
//========================================
cTransitonOnceRotation::cTransitonOnceRotation() : cTransition(){

	spriteParam.LoadTexture(TEX_FILENAME_STAR);
	spriteParam.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
	spriteParam.SetSize(D3DXVECTOR2(0.0f, 0.0f));
	spriteParam.SetTexPatternDevide(1, 1);
	spriteParam.SetCurrentAnimPattern(0);

}

//========================================
// �f�X�g���N�^
//========================================
cTransitonOnceRotation::~cTransitonOnceRotation(){



}

//========================================
// �X�V����
//========================================
void cTransitonOnceRotation::Update(){

	if (!m_bOut){
		spriteParam.SetSize(D3DXVECTOR2(spriteParam.GetSizeX() + INCREMENT_SIZE_ONCE, spriteParam.GetSizeY() + INCREMENT_SIZE_ONCE));
		if (spriteParam.GetSizeX() >= MAX_SIZE_ONCE){
			m_bOut = true;
			cSceneManeger::ChangeScene((cSceneManeger::SCENE)m_nextScene);
		}
	}
	else{
		spriteParam.SetSize(D3DXVECTOR2(spriteParam.GetSizeX() - INCREMENT_SIZE_ONCE, spriteParam.GetSizeY() - INCREMENT_SIZE_ONCE));
		if (spriteParam.GetSizeX() <= 0.0f){
			m_bFinish = true;
		}
	}

	//��]
	spriteParam.SetRad(spriteParam.GetRad() + ROTATION_SPEED);

}

//========================================
// �`�揈��
//========================================
void cTransitonOnceRotation::Draw(){

	spriteParam.Draw();

}



//***************************************************************************//
//******************* �����_���^�C������ ************************************//
//***************************************************************************//

//========================================
// �R���X�g���N�^
//========================================
cTransitionTileCreateRandom::cTransitionTileCreateRandom() : cTransition(), m_nPutNum(0), m_nFrame(0){

	D3DXVECTOR2 work;

	//�摜���̏�����
	for (int y = 0; y < DICE_Y_NUM; y++){
		for (int x = 0; x < DICE_X_NUM; x++){
			spriteParam[y][x].LoadTexture(TEX_FILENAME_WHITE);
			work.x = (SCREEN_WIDTH / (DICE_X_NUM * 2)) + (SCREEN_WIDTH / DICE_X_NUM * x);
			work.y = (SCREEN_HEIGHT / (DICE_Y_NUM * 2)) + (SCREEN_HEIGHT / DICE_Y_NUM * y);
			spriteParam[y][x].SetPos(work);
			spriteParam[y][x].SetSize(D3DXVECTOR2(SCREEN_WIDTH / DICE_X_NUM, SCREEN_HEIGHT / DICE_Y_NUM));
			spriteParam[y][x].SetTexPatternDevide(1, 1);
			spriteParam[y][x].SetCurrentAnimPattern(0);
			m_bPut[y][x] = false;
		}
	}

}

//========================================
// �f�X�g���N�^
//========================================
cTransitionTileCreateRandom::~cTransitionTileCreateRandom(){



}

//========================================
// �X�V����
//========================================
void cTransitionTileCreateRandom::Update(){

	//�����̃V�[�h�l�ݒ�
	srand((unsigned)time(NULL));

	//�t���[���̉��Z
	m_nFrame++;

	if (m_nFrame < UPDATE_FRAME)
		return;

	m_nFrame = 0;

	int x, y,cnt = 0;

	while (true)
	{
		//�����Ő���
		x = rand() % DICE_X_NUM;
		y = rand() % DICE_Y_NUM;

		if (!m_bOut){
			if (!m_bPut[y][x]){
				m_bPut[y][x] = true;
				m_nPutNum++;
				if (m_nPutNum >= DICE_X_NUM * DICE_Y_NUM){
					cSceneManeger::ChangeScene((cSceneManeger::SCENE)m_nextScene);
					m_bOut = true;
				}
				return;
			}
		}
		else{
			if (m_bPut[y][x]){
				m_bPut[y][x] = false;
				m_nPutNum--;
				if (m_nPutNum <= 0){
					m_bFinish = true;
				}
				return;
			}
		}

		cnt++;

	}

}

//========================================
// �`�揈��
//========================================
void cTransitionTileCreateRandom::Draw(){

	for (int y = 0; y < DICE_Y_NUM; y++){
		for (int x = 0; x < DICE_X_NUM; x++){
			if (m_bPut[y][x])
				spriteParam[y][x].Draw();
		}
	}

}