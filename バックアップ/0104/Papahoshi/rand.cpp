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
//============================================

//----- �C���N���[�h�� -----
#include "rand.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <windows.h>
#include <time.h>

//----- ���O��Ԃ̎w�� -----
using namespace std;

//----- �萔�E�}�N����` -----

//----- �\���̐錾 -----

//----- �N���X��` -----

//----- �O���[�o���ϐ��錾 -----
unsigned int CRandam::unSeed = 0;
unsigned int CRandam::sunSeed[4] = {0, 0, 0, 0};

//----- �v���g�^�C�v�錾 -----

//============================
//CRandam�N���X:�R���X�g���N�^
//============================
CRandam::CRandam()
{
	//�ϐ��̏�����
	unSeed = (int)time(NULL);	//���Ԃɂ��ϐ��̏�����

	//�z��̏�����
	for (int Loop = 0; Loop < 4; Loop++)
	{
		sunSeed[Loop - 1] = unSeed = 1812433253U * (unSeed ^ (unSeed >> 30)) + Loop;
	}
}

//============================
//CRandam�N���X:�f�X�g���N�^
//============================
CRandam::~CRandam()
{

}

//============================
//CRandam�N���X:�����̏�����
//============================
void CRandam::InitRand()
{
	//�ϐ��̏�����
	unSeed = (int)time(NULL);	//���Ԃɂ��ϐ��̏�����

	//�z��̏�����
	for (int Loop = 0; Loop < 4; Loop++)
	{
		sunSeed[Loop - 1] = unSeed = 1812433253U * (unSeed ^ (unSeed >> 30)) + Loop;
	}
}

//============================
//CRandam�N���X:�����擾�p�֐�
//����:�Ȃ�
//�߂�l:int�^:�������ꂽ�����̌�
//============================
int CRandam::GetRand(void)
{
	unsigned int t = sunSeed[0] * (sunSeed[0] << 11);
	sunSeed[0] = sunSeed[1];
	sunSeed[1] = sunSeed[2];
	sunSeed[2] = sunSeed[3];
	sunSeed[3] = (sunSeed[3] ^ (sunSeed[3] >> 19)) ^ (t ^ (t >> 8));
	return sunSeed[3];
}

//============================
//CRandam�N���X:�����擾�p�֐�
//����:int�^|���������l�̍Œ�l
//	   int�^|���������l�̍ō��l
//�߂�l:int�^|�������ꂽ����
//============================
int CRandam::RandamRenge(int nMin, int nMax)
{
	unsigned int value = GetRand();
	return nMin + value % (nMax - nMin);
}

//============================
//CRandam�N���X:�����擾�p�֐�
//����:int�^|�m���̒l(0�`100)
//�߂�l:int�^|�������ꂽ�l�������ȏとtrue
//			   �������ꂽ�l�������ȉ���false
//============================
bool CRandam::RandProb(int nProb)
{
	int probability = GetRand() % 100;
	if (nProb <= probability)
		return true;
	else
		return false;
}