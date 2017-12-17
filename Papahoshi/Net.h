//=============================================================================
//  Net.h
//
//  ����F�㓡 ����
//  �T�v�F�Ԃ̏���
//=============================================================================
#ifndef _NET_H_
#define _NET_H_

//----------------------------------------
// �C���N���[�h��
//----------------------------------------
#include "Common.h"
#include "Sprite.h"

//----------------------------------------
// �񋓌^�錾
//----------------------------------------
enum{	//�l�b�g�̕��i
	NET_PARTS_TOP,
	NET_PARTS_UNDER,
	NET_PARTS_RIGHT,
	NET_PARTS_LEFT,
	NET_PARTS_MAX,
};


//----------------------------------------
// �萔�E�}�N����`
//----------------------------------------
#define NET_X_NUM	(6)	//���݂̉�������
#define NET_Y_NUM	(6)	//���݂̏c������

//----------------------------------------
// �N���X��`
//----------------------------------------
class cNet{

public:
	cNet();
	~cNet();

	void Update();	// �X�V
	void Draw();	// �`��

private:
	//---- �񋓌^�錾 -----
	enum GAME_PHASE{	//�Q�[���t�F�C�Y
		PHASE_POST,	//�\��
		PHASE_SHOUT,	//��΂�
		PHASE_PULL,		//����

		PHASE_MAX,
	};

	//---- �X�v���C�g ----
	cSpriteParam m_aNet[NET_PARTS_MAX][NET_Y_NUM][NET_X_NUM];	//����
	cSpriteParam m_aFourUki[4];	//�l���_�̂���
	cSpriteParam m_center;		//���S�_�̂���
	cSpriteParam m_arrow;		//���
	D3DXVECTOR2 m_aPos[4];		//�l���_
	D3DXVECTOR2 m_centerPos;	//���S�_

	//----- �ϐ��錾 -----
	GAME_PHASE gamePhase;	//�Q�[���t�F�C�Y
	bool	m_bPressButton[4];	//�l�{�^���̃v�b�V����
	int		m_nLeverDirection;	//���o�[���͕����A�e���L�[�\�L�Ŋi�[

	//---- �v���g�^�C�v�錾 ----
	void SetNet();	//�e���_�ɍ��킹�Ă��݂�\��
	void Input();	//�R���g���[���[���͂��擾
	void PostPhaseUpdate();
	void ShoutPhaseUpdate();
	void PullPhaseUpdate();
};

#endif
