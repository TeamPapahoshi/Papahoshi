//======================================================================
//	Common
//	
//	�T�v�Q�F���ʕ���
//	����ҁF�Ԉ�@�Y��
//	
//======================================================================

#ifndef ___COMMON_H___
#define ___COMMON_H___

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "d3dx9.h"		// D3DXVECTOR2��
#include "rand.h"		// ���������p�N���X
#include "GameMain.h"	// �G�t�F�N�g�N���X�擾�p

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
#define SCREEN_WIDTH (950)	//����
#define SCREEN_HEIGHT (650) //����

//----- ���S���W -------
#define SCREEN_CENTER (D3DXVECTOR2(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f))

#endif //!___COMMON_H___