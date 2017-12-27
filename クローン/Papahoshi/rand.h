//============================================
//
//	XorShift���������֐��w�b�_
//	���e  :XorShift�ɂ�闐���̐����Ɨ��p
//	�Ή�  :rand.cpp	
//
//	�쐬��:2017/11/09
//	�쐬��:���� ����
//
//--------------------------------------------
//	<�X�V���e>
//	2017/11/09	�쐬�J�n
//  2017/11/11  ���������֐��̊���
//--------------------------------------------
//	<�^�p���@>
//	rand.h���g������cpp�ɃC���N���[�h����
//	1.�����̐������������ꍇ
//	CRandam::RandamRange(�ŏ��l,�ő�l)
//	2.�m���̔�����������ꍇ
//	CRandam::RandProb(�m��)
//============================================

#ifndef _RAND_H_
#define _RAND_H_

//----- �萔�E�}�N����` -----

//----- �\���̐錾 -----

//----- �N���X��` -----

class CRandam
{
private:
	static unsigned int unSeed;	//�����i�[�p�ϐ�
	static unsigned int sunSeed[4];//���������p�z��

//-------------------------------
protected:
	static int GetRand(void);		//�����擾�p�֐�
//-------------------------------
public:
	//�R���X�g���N�^
	CRandam();
	//�f�X�g���N�^
	~CRandam();
	//����������
	static void InitRand();
	//���͈͓��ł̗����̐���
	static int RandamRenge(int nMin, int nMax);
	//�m���ɂ�鍇�۔���
	static bool RandProb(int nProb);
};

//----- ���O��Ԃ̎w�� -----

//----- �v���g�^�C�v�錾 -----

#endif