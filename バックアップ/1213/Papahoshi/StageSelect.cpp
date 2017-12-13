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

//-----------------------------
//�}�N����`
//-----------------------------
#define STAGESELECT_POS_X (100.0f)
#define STAGESELECT_POS_Y (100.0f)

#define STAGESELECT_SPACE_POS_X (150.0f)	//�������̊Ԋu
#define STAGESELECT_SPACE_POS_Y (300.0f)	//�c�����̊Ԋu

#define STAGECLEAR_POS_X (200.0f)
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
void cStageSelect::Init(LPDIRECT3DTEXTURE9* pTex)
{
	//�|�C���^�̐ݒ�
	cSpriteParam* pStageSprite = m_StageSprite;
	
	for (int HorizonLoop = 0; HorizonLoop < MAX_STAGE / (MAX_STAGE / 2); HorizonLoop++)	//�s�̃��[�v
	{
		for (int VarticalLoop = 0; VarticalLoop < MAX_STAGE / 2; VarticalLoop++, pStageSprite++) //��̃��[�v
		{
			pStageSprite->SetTexture(pTex);
			pStageSprite->SetPos(D3DXVECTOR2(STAGESELECT_POS_X + VarticalLoop * STAGESELECT_SPACE_POS_X,
											 STAGESELECT_POS_Y + HorizonLoop  * STAGESELECT_SPACE_POS_Y));
			pStageSprite->SetTexPatternDevide(1, 1);
			pStageSprite->SetCurrentAnimPattern(0);
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

	for (int DrawSpriteLoop = 0; DrawSpriteLoop < MAX_STAGE ; DrawSpriteLoop++, pStageSprite++)
	{
		pStageSprite->Draw();
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