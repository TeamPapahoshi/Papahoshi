//======================================================================
//	SceneStageSelect
//	
//	�T�v�Q�F�X�e�[�W�I��(��)
//	����ҁF���� ����
//	
//======================================================================

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "SceneStageSelect.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"

// �I�u�W�F�N�g
#include "StageSelect.h"

//------------------------------
// �}�N����`
//------------------------------
#define TEXTURE_FILNAME_STAGE (NULL)

//-----------------------------
// �O���[�o��
//-----------------------------
cStageSelect* pStageSelect = NULL;

//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneStageSelect::cSceneStageSelect(){

	//�g�p����I�u�W�F�N�g�̓��I�m��
	pStageSelect = new cStageSelect();

	// �e�N�X�`���̓ǂݍ���
	LoadTextureFromFile();

	pStageSelect->Init(m_pTex);		//�X�e�[�W�Z���N�g�p�I�u�W�F�N�g�̏�����


}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
cSceneStageSelect::~cSceneStageSelect()
{
	pStageSelect->Uninit();		//�X�e�[�W�Z���N�g�p�I�u�W�F�N�g�̏I������

	delete pStageSelect;		//���I�m�ۂ����I�u�W�F�N�g�̉��
	pStageSelect = NULL;

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneStageSelect::Update()
{
	pStageSelect->Update();

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		cSceneManeger::ChangeScene(cSceneManeger::GAME);
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cSceneStageSelect::Draw()
{
	pStageSelect->Draw();
}

//=======================================================================================
//
//		���̃V�[���Ŏg���e�N�X�`���̓Ǎ�
//		�w�b�_�[��enum�Ƃ��̊֐���char*�z��ɒǉ�����΃e�N�X�`�������[�h����܂�
//		���w�b�_�[��enum��char�z��̃t�@�C�����̏��Ԃ���v����悤�ɂ��Ă�������
//		�V�[�����ς��ƃe�N�X�`�����������Ⴄ�̂ł̂œ����I�u�W�F�N�g��ʃV�[���ŌĂ�
//		���͂�����x�g���e�N�X�`���������Ă�������
//
//=======================================================================================
void cSceneStageSelect::LoadTextureFromFile(){

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	char* pTexture[MAX_TEXTURE] = { { TEXTURE_FILENAME_STAGESELECT },
									{ TEXTURE_FILENAME_STAGECLEAR} }; //���̃e�N�X�`��

	// ���[�h
	for (int TexLoadLoop = 0; TexLoadLoop < MAX_TEXTURE; TexLoadLoop++){
		D3DXCreateTextureFromFile(pDevice, pTexture[TexLoadLoop], &m_pTex[TexLoadLoop]);
	}
}