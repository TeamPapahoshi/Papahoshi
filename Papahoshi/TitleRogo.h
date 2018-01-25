//======================================================================
//	TitleRogo
//	
//	�T�v�Q�F�^�C�g�����S�w�b�_
//	����ҁF���� ����
//	
//======================================================================
#ifndef ___TITLEROGO_H___
#define ___TITLEROGO_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Common.h"

//-----------------------------
//�}�N����`
//-----------------------------
#define  MAX_TITLEROGO (10)

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�\���̒�`
//-----------------------------
typedef struct
{

	cSpriteParam	Rogosprite;			// �X�v���C�g�̃X�e�[�^�X(���S)
	int				nHopTimer;				// �^�C�}�[
	float			fRadian;
}TITLEROGO;

//-----------------------------
//�N���X��`
//-----------------------------

class cTitleRogo{
private:
	TITLEROGO       m_aTitlerogo[MAX_TITLEROGO];
	cSpriteParam    m_Pushsprite;
	int				m_nAlphaTimer;
//----------------------------------------------------------
protected:

//----------------------------------------------------------
public:
	cTitleRogo();	// �R���X�g���N�^
	~cTitleRogo();	// �f�X�g���N�^

	// �����͉�������p�������Ă����������I�[�o���C�h
	void Init();	// ������ �e�N�X�`���̃|�C���^���󂯎����
	void UnInit();	// �I��
	void Update(bool bSceneChangeFlag);	// �X�V
	void Draw();	// �`��
};

#endif	//!___TITLEROGO_H___