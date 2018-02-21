//======================================================================
//	Meteor
//	
//	�T�v�Q�F�^�C�g���I�u�W�F�N�g/����
//	����ҁF���� ����
//	
//======================================================================
#ifndef ___METEOR_H___
#define ___METEOR_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Common.h"

//-----------------------------
//�}�N����`
//-----------------------------
#define MAX_METEOR (10)
#define MAX_METEOR_SPRITE_NUM (3)
#define METEOR_LIFETIME (60)

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�\���̒�`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------

class cObjMETEOR
{
private:	//�O������Q�ƕs��
	int nMakeTime;	//�����̐����܂ł̎���
	int nLifeTime;	//�����̐�������
	bool bUseFlag;	//�g�p�t���O

	//----------------------------
protected:	//�N���X���ł̂ݎQ�Ɖ�

	//-----------------------------
public:		//�ǂ�����ł��Q�Ɖ�

	cObjMETEOR(){}	// �R���X�g���N�^
	~cObjMETEOR(){}	// �f�X�g���N�^

	//------- �Q�b�^ --------
	int GetMakeTime(void)
	{
		return nMakeTime;
	}
	int GetLifeTime(void)
	{
		return nLifeTime;
	}
	bool GetUseFlag(void)
	{
		return bUseFlag;
	}
	//------- �Z�b�^ --------
	void SetLifeTime(int LifeTime)
	{
		nLifeTime = LifeTime;
	}
	void SetMakeTime(int MakeTime)
	{
		nMakeTime = MakeTime;
	}
	void SetUseFlag(bool Flag)
	{
		bUseFlag = Flag;
	}

	cSpriteParam Sprite[MAX_METEOR_SPRITE_NUM];
};

//�N���X�e���v���[�g
class cMeteor
{
private:	//�O������Q�ƕs��
	cObjMETEOR m_aMeteor[MAX_METEOR];

	//-----------------------------
protected:	//�N���X���ł̂ݎQ�Ɖ�

	//-----------------------------
public:		//�ǂ�����ł��Q�Ɖ�

	cMeteor();	// �R���X�g���N�^
	~cMeteor();	// �f�X�g���N�^

	// �����͉�������p�������Ă����������I�[�o���C�h
	void Init();	// ������ �e�N�X�`���̃|�C���^���󂯎����
	void UnInit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

	void SetMeteor();	//�����̐ݒ�
};

#endif	//!___METEOR_H___