//======================================================================
//	Star
//	
//	�T�v�Q�F������
//	����ҁF�����@��
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>
#include <math.h>
#include "debugproc.h"
#include "Common.h"
#include "Texture.h"

#include "NormalStars.h"
#include <fstream>


//-----------------------------
//�}�N����`
//-----------------------------



//****************************************************************************************************************
// ���ʂ̐�
//****************************************************************************************************************
//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cNormalStar::cNormalStar(){

	// Sprite
	m_sprite.SetPos(D3DXVECTOR2(0.0f, 0.0f));
	m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR));
	m_sprite.SetVtxColorA(200);

}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cNormalStar::~cNormalStar(){

}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cNormalStar::Update(){

	// �Q�[���t�F�C�Y�����炤�\��!!!
	
	// �ʏ���(�Q�[��)
	// ���W�X�V
	m_sprite.SetPos(moveCircle.GetMove());

	// �m�ے�

	// �u���b�N�z�[���z������->�z�����񂾂������H

	// ������

	// �Ԉ����グ��

}
//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cNormalStar::Draw(){
	m_sprite.Draw();
}

//=======================================================================================
//
//		���̐ݒ�
//
//=======================================================================================
void cNormalStar::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

	moveCircle.SetCenter(center);
	moveCircle.SetRadius(radius);
	m_sprite.SetSize(size);
	moveCircle.SetSpped(second);

}

//=======================================================================================
//
//		���������邩�����Ȃ����̐ݒ�
//
//=======================================================================================
void cNormalStar::StarVisibility(float distance){

	// ���l�̕ω�
	m_sprite.SetVtxColorA(255 / distance * 15);
	
}



//=======================================================================================
//
//		���̃t�@�C���ǂݍ���
//
//=======================================================================================
void cNormalStar::SetStarFromFile(int loop){


	// �Ǎ���p�Ńt�@�C�����J��
	fstream file;
	file.open("data/StarData/NormalStarData_Stage1.bin", ios::binary | ios::in);


	// �X�e�[�W�̐��̐��ɍ��킹�ă��T�C�Y
	// ����̓X�e�[�W�ԍ��͊O������炤
	switch (stageNum){

	case STAGE_01:
		a_Data.resize(STAGE_01_STAR_NUM);
		break;

	default:
		break;
	}


	// �Ǎ�
	for (int i = 0; i < (int)a_Data.size(); i++){
		file.read((char*)&a_Data[i], sizeof(a_Data[i]));
	}

	// �ǂݍ��񂾃f�[�^�̈����Ԗڂ�������
	Set(a_Data[loop].center, a_Data[loop].radius, a_Data[loop].size, a_Data[loop].speed);
}



//�T��
/*m_pNomalStar[0]->Set(D3DXVECTOR2(100, 100), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
m_pNomalStar[1]->Set(D3DXVECTOR2(200, 250), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
m_pNomalStar[2]->Set(D3DXVECTOR2(300, 200), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
m_pNomalStar[3]->Set(D3DXVECTOR2(700, 400), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
m_pNomalStar[4]->Set(D3DXVECTOR2(500, 500), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
*/