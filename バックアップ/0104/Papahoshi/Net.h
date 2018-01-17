//=============================================================================
//  Net.h
//
//  ����F�㓡 ����
//  �T�v�F�Ԃ̏���
//=============================================================================
#ifndef _NET_H_
#define _NET_H_

//#define _TYPE_1_
#ifdef  _TYPE_1_

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
	
	enum POST_ANGLE{	//�\���p�x
		ANG_LEFT = 1,
		ANG_STRAIGHT,
		ANG_RIGHT,
	};

	enum POST_PHASE{
		POST_NON,
		POST_PULL,
		POST_N,
		POST_PUSH,
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
	//�L�[���͌n
	bool	m_bPressButton[4];	//�l�{�^���̃v���X��
	bool	m_bAllPress;		//�S�{�^���v���X��
	int		m_nLeverDirection;	//���o�[���͕����A�e���L�[�\�L�Ŋi�[
	//�`��n
	bool	m_bDrawArrow;		//����`�悷�邩�ǂ���
	//�\�����
	int		m_nPostAngle;		//�\���p�x
	int		m_nFrameCnt;
	float	m_fThrowSpeed;		//�X�s�[�h
	POST_PHASE	m_postPhase;	//�\���t�F�C�Y
	//�������
	bool	m_bThrow[4];		//True�Ȃ瓊�����̒��_
	float	m_afSpeedFourse[4];		//�l���_�̃X�s�[�h

	//---- �v���g�^�C�v�錾 ----
	void SetNet();	//�e���_�ɍ��킹�Ă��݂�\��
	void Input();	//�R���g���[���[���͂��擾
	void PostPhaseUpdate();
	void ShoutPhaseUpdate();
	void PullPhaseUpdate();
};

#endif
#endif