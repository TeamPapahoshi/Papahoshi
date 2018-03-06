//======================================================================
//	Common
//	
//	�T�v�Q�F���ʕ���
//	����ҁF�����@��
//	
//======================================================================

#ifndef ___COMMON_H___
#define ___COMMON_H___

// �f�o�b�O�p�@�C�x���g�X�L�b�v�E�^�C���X�g�b�v
//#define _DEBUG_DKIP_

// �v���[���e�[�V����
//#define _PRESEN_KEY_

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "d3dx9.h"		// D3DXVECTOR2��
#include "rand.h"		// ���������p�N���X
#include "Sprite.h"		// CSprite�N���X�̓���
#include <iostream>		// cout
#include <fstream>		// fstream
#include <vector>		// vector

//------------------------------
// ���O��Ԃ̎w��
//------------------------------
using namespace std;

//------------------------------
// �}�N����`
//------------------------------
//----- �X�N���[���̑傫�� ------------
#define SCREEN_WIDTH (1366)	//����
#define SCREEN_HEIGHT (768) //����

// ��ʔ䗦���킹����
//#define SCREEN_WIDTH (950)	//����
//#define SCREEN_HEIGHT (550)	//����

//���F1366  �~  �c : 768

//----- ���S���W -------
#define SCREEN_CENTER (D3DXVECTOR2(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f))

#define SINCURVE(UnderFloat, RandFloat, Radian) (UnderFloat + (RandFloat * sinf(Radian * 3.14f)))	//�T�C���J�[�u
#define COSCURVE(UnderFloat, RandFloat, Radian) (UnderFloat + (RandFloat * cosf(Radian * 3.14f)))	//�R�T�C���J�[�u

#define MAX_RADIUS (200)	//Radius�̍ō��l

//----- SAFE DELETE ------
#define SAFE_DELETE(x)	if(x!=NULL){delete x; x=NULL})

#define _FPS_MEASURE_		//FPS�v���@�\



#endif //!___COMMON_H___