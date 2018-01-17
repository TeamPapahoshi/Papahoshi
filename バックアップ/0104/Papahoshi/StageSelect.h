//======================================================================
//	Sample
//	
//	�T�v�Q�F�X�e�[�W�Z���N�g����
//	����ҁF���� ����
//	
//======================================================================
#ifndef ___STAGESELECT_H___
#define ___STAGESELECT_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Common.h"		
#include <Windows.h>	//HRESULT��
#include "d3dx9.h"		//D3DXVECTOR2��
#include "Sprite.h"		//CSprite�N���X�̓���

//-----------------------------
//�}�N����`
//-----------------------------
#define MAX_STAGE (10)	//�X�e�[�W��(��)
//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------
class cStageSelect
{
private:
	cSpriteParam m_StageSprite[MAX_STAGE];		//�X�e�[�W�I��p�̃X�v���C�g���
	cSpriteParam m_StageClearSprite[MAX_STAGE];	//�X�e�[�W�N���A�\���̃X�v���C�g���
	bool		 m_bClearFlag[MAX_STAGE];		//�X�e�[�W�̃N���A�t���O

	int			 m_nSelectStageNum;	//���ݑI�𒆂̃X�e�[�W�ԍ�

//-----------------------------
protected:

//-----------------------------
public:

	cStageSelect(){}		// �R���X�g���N�^
	~cStageSelect(){}	// �f�X�g���N�^

	// �����͉�������p�������Ă����������I�[�o���C�h
	void Init();	// ������ �e�N�X�`���̃|�C���^���󂯎����
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

	void SaveClearFlag(void);	//�N���A�t���O�̏�������
	void LoadClearFlag(void);	//�N���A�t���O�̓ǂݍ���

	int GetSelectStageNum(void);	//�X�e�[�W�ԍ��̈����n���֐�
	bool* GetStageClearFlag(void);	//�X�e�[�W�N���A�t���O�̈����n���֐�
};

#endif	//!___STAGESELECT_H___