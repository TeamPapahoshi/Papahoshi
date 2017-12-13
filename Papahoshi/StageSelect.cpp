//======================================================================
//	StageSelect
//	
//	�T�v�Q�F�X�e�[�W�I������
//	����ҁF�����@����
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "StageSelect.h"
#include "SceneManeger.h"	//BaseScene

#include "Input.h"
#include "debugproc.h"		//printdebug

#include <iostream>			//�t�@�C���������ݗp
#include <fstream>			//�t�@�C���ǂݍ��ݗp

#include "Texture.h"

//----- ���O��Ԃ̎w�� -----
using namespace std;

//-----------------------------
//�}�N����`
//-----------------------------
#define STAGESELECT_POS_X (100.0f)
#define STAGESELECT_POS_Y (100.0f)

#define STAGESELECT_SPACE_POS_X (150.0f)	//�������̊Ԋu
#define STAGESELECT_SPACE_POS_Y (300.0f)	//�c�����̊Ԋu

#define STAGECLEAR_POS_X (100.0f)
#define STAGECLEAR_POS_Y (200.0f)

#define STAGECLEAR_SPACE_POS_X (150.0f)	//�������̊Ԋu
#define STAGECLEAR_SPACE_POS_Y (300.0f)	//�c�����̊Ԋu

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------

//-----------------------------
//�O���[�o��
//-----------------------------


//=======================================================================================
//
//		������
//
//=======================================================================================
void cStageSelect::Init()
{
	//�|�C���^�̐ݒ�
	cSpriteParam* pStageSprite = m_StageSprite;
	cSpriteParam* pStageClearSprite = m_StageClearSprite;
	
	for (int HorizonLoop = 0; HorizonLoop < MAX_STAGE / (MAX_STAGE / 2); HorizonLoop++)	//�s�̃��[�v
	{
		for (int VarticalLoop = 0; VarticalLoop < MAX_STAGE / 2; VarticalLoop++, pStageSprite++, pStageClearSprite++) //��̃��[�v
		{
			//�X�e�[�W�I��p�X�v���C�g�̏�����
			pStageSprite->SetTexture(cTextureManeger::GetTextureStageSelect(TEX_STAGESELECT_KING_JELLY));	//�e�N�X�`���̐ݒ�
			pStageSprite->SetPos(D3DXVECTOR2(STAGESELECT_POS_X + VarticalLoop * STAGESELECT_SPACE_POS_X,	//���W�̐ݒ�
											 STAGESELECT_POS_Y + HorizonLoop  * STAGESELECT_SPACE_POS_Y));
			pStageSprite->SetTexPatternDevide(1, 1);
			pStageSprite->SetCurrentAnimPattern(0);

			//�X�e�[�W�N���A�\���X�v���C�g�̏�����
			pStageClearSprite->SetTexture(cTextureManeger::GetTextureStageSelect(TEX_STAGESELECT_STAGE));	//�e�N�X�`���̐ݒ�
			pStageClearSprite->SetPos(D3DXVECTOR2(STAGECLEAR_POS_X + VarticalLoop * STAGECLEAR_SPACE_POS_X,	//���W�̐ݒ�
												  STAGECLEAR_POS_Y + HorizonLoop  * STAGECLEAR_SPACE_POS_Y));
			pStageClearSprite->SetTexPatternDevide(1, 1);
			pStageClearSprite->SetCurrentAnimPattern(0);

			//�N���A�t���O�̏�����(�b��)
			LoadClearFlag();
		}
	}

	//�X�e�[�W�ԍ��̏����ݒ�
	m_nSelectStageNum = 0;
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cStageSelect::Uninit()
{
	//�t���O�̕ۑ�(�b��̏���)
	SaveClearFlag();
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cStageSelect::Update()
{
	//�|�C���^�̐ݒ�
	cSpriteParam* pStageSprite = m_StageSprite;
	cSpriteParam* pStageClearSprite = m_StageClearSprite;

	if (GetKeyboardTrigger(DIK_RIGHT)){	//�E�ֈړ�
		m_nSelectStageNum = (m_nSelectStageNum + 1 + MAX_STAGE) % MAX_STAGE;
	}
	else if (GetKeyboardTrigger(DIK_LEFT)){	//���ֈړ�
		m_nSelectStageNum = (m_nSelectStageNum - 1 + MAX_STAGE) % MAX_STAGE;
	}
	else if (GetKeyboardTrigger(DIK_UP)){	//��ֈړ�
		m_nSelectStageNum = (m_nSelectStageNum + (MAX_STAGE / 2) + MAX_STAGE) % MAX_STAGE;
	}
	else if (GetKeyboardTrigger(DIK_DOWN)){	//���ֈړ�
		m_nSelectStageNum = (m_nSelectStageNum + (MAX_STAGE / 2) + MAX_STAGE) % MAX_STAGE;
	}

	//�I�𒆂̃X�e�[�W�����g��\��
	for (int UpdateSpriteLoop = 0; UpdateSpriteLoop < MAX_STAGE; UpdateSpriteLoop++, pStageSprite++)
	{
		if (m_nSelectStageNum == UpdateSpriteLoop)
		{
			pStageSprite->SetScale(D3DXVECTOR2(1.5f, 1.5f));
		}
		else
		{
			pStageSprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		}
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cStageSelect::Draw()
{
	//�|�C���^�̐ݒ�
	cSpriteParam* pStageSprite = m_StageSprite;
	cSpriteParam* pStageClearSprite = m_StageClearSprite;

	for (int DrawSpriteLoop = 0; DrawSpriteLoop < MAX_STAGE ; DrawSpriteLoop++, pStageSprite++, pStageClearSprite++)
	{
		pStageSprite->Draw();
		//�N���A�ς݂̃X�e�[�W�̉��ɕ\��
		if (m_bClearFlag[DrawSpriteLoop])
			pStageClearSprite->Draw();
	}
}


//=======================================================================================
//
//		�N���A�t���O�̏�������
//
//=======================================================================================
void cStageSelect::SaveClearFlag(void)
{
	ofstream ofs;	//�t�@�C���������ݗp

	//�t�@�C����V�K�쐬���ď������݊J�n
	ofs.open("Test.txt", ios_base::out | ios_base::trunc);

	//���s���Ă�����G���[���̕\��
	if (!ofs) {
		cerr << "�t�@�C���I�[�v���Ɏ��s" << endl;
		exit(1);
	}

	//char*�^�ɕϊ����ăN���A���̏�������
	for (int SaveFlagLoop = 0; SaveFlagLoop < MAX_STAGE; SaveFlagLoop++)
	{
		ofs << m_bClearFlag[MAX_STAGE] << endl;
	}
	//�t�@�C���͎����I�ɕ�����
}

//=======================================================================================
//
//		�N���A�t���O�̓ǂݍ���
//
//=======================================================================================
void cStageSelect::LoadClearFlag(void)
{
	ifstream ifs("Test.txt");	//�t�@�C���ǂݍ��ݗp

	//���s������G���[���̕\��
	if (!ifs) {
		cerr << "�t�@�C���I�[�v���Ɏ��s" << endl;
		exit(1);
	}

	//�t�@�C���̒��g��ǂݍ���
	for (int LoadFlagLoop = 0; LoadFlagLoop < MAX_STAGE; LoadFlagLoop++)
	{
		ifs >> m_bClearFlag[MAX_STAGE];
	}
}

//=======================================================================================
//
//		�X�e�[�W�ԍ��̈����n���֐�
//		�����F�Ȃ�
//		�߂�l�Fint�^ �X�e�[�W�ԍ�
//
//=======================================================================================
int cStageSelect::GetSelectStageNum(void)
{
	return m_nSelectStageNum;
}

//=======================================================================================
//
//		�X�e�[�W�N���A�t���O�̈����n���֐�
//		�����F�Ȃ�
//		�߂�l�Fbool�^ �X�e�[�W�N���A�t���O
//
//=======================================================================================
bool* cStageSelect::GetStageClearFlag(void)
{
	return m_bClearFlag;	//�z��̐擪��������n��
}