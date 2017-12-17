//======================================================================
//	Texture
//	
//	�T�v�F�e�N�X�`���Ǘ�
//		�g���� 
//		�O���[�o���ɂ���V�[�����Ƃ̃t�@�C�����p�z��ɁA�}�N���Œ�`����
//		�t�@�C����ǉ����Ă���
//		�w�b�_�[�ɂ���V�[�����Ƃ�enum�ɂ��t�@�C�����Ɠ������O�Œǉ�
//		
//		�V�[�����ƂŃt�@�C����ǂݍ��ނ̂œ����t�@�C�����ł��V�[�����Ƃ�
//		�ǉ����Ă�������
//
//		�܂��Q�b�g�p�֐����V�[�����Ƃɕ������̂Œ��ӂ��Ă�������
//
//		���Ɣw�i�Ƃ����炩�ɓ����V�[���ŕ����񃍁[�h���Ȃ��Ƃ킩���Ă�����̂�
//		sprite.LoadTexture�Œ��ڃ��[�h�����ق�����������
//
//	����ҁF���� ��
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>		//HRESULT��
#include "debugproc.h"		//printdebug
#include<vector>
#include<iostream>
#include "Common.h"
#include"SceneManeger.h"
#include"Texture.h"


//-----------------------------
// �}�N��
//-----------------------------
// �e�N�X�`���t�@�C��
#define TEXTURE_FILNAME_KING_JELLY	("Image/Character/KingJelly.jpg")
#define TEXTURE_FILNAME_JELLY		("Image/Character/Jelly.png")
#define TEXTURE_FILNAME_STAR_LIGHT	("Image/Star/light.png")
#define TEXTURE_FILNAME_STAR		("Image/Star/Star.png")
#define TEXTURE_FILNAME_EF			("Image/Star/Effect.png")
#define TEXTURE_FILNAME_EF02		("Image/Star/Effect2.png")
#define TEXTURE_FILENAME_NET		("Image/Net/Net.png")
#define TEXTURE_FILENAME_UKI		("Image/Net/uki.jpg")
#define TEXTURE_FILENAME_ARROW		("Image/Net/arrow.png")

#define TEXTURE_FILENAME_STAGECLEAR  ("data/texture/akira000.png")	//���̃e�N�X�`��

//-----------------------------
// �O���[�o��
//-----------------------------
//----Title-----
vector<char*> texTitle = {
	TEXTURE_FILNAME_KING_JELLY,
	TEXTURE_FILNAME_JELLY,		// �����摜�ł��V�[�����Ⴄ�Ƃ��͂�����񏑂���
};

//----StageSelect-----
vector<char*> texStageSelect = {
	TEXTURE_FILENAME_STAGECLEAR,// �����摜�ł��V�[�����Ⴄ�Ƃ��͂�����񏑂���
	TEXTURE_FILNAME_JELLY,
};

//----Game-----
vector<char*> texGame = {
	TEXTURE_FILNAME_JELLY,		// �����摜�ł��V�[�����Ⴄ�Ƃ��͂�����񏑂���
	TEXTURE_FILNAME_STAR_LIGHT,
	TEXTURE_FILNAME_STAR,
	TEXTURE_FILNAME_EF,
	TEXTURE_FILNAME_EF02,
	TEXTURE_FILENAME_NET,
	TEXTURE_FILENAME_UKI,
	TEXTURE_FILENAME_ARROW,
};

/*
//----Sample-----
vector<char*> texSample = {
TEXTURE_FILNAME_JELLY,
};

*/

// �e�N�X�`���̃|�C���^
vector<LPDIRECT3DTEXTURE9>  cTextureManeger::p_texture(1,NULL);	// ������(�v�f��,���g)


//=======================================================================================
//
//		�V�[�����Ƃ̃e�N�X�`���̃��[�h
//		����	�V�[��
//
//=======================================================================================
void cTextureManeger::LoadTexture(cSceneManeger::SCENE scene){

	//----------------------------
	//���[�J���ϐ��錾
	//----------------------------
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// Direct3D�f�o�C�X
	vector<char*> filename;						// �t�@�C�����i�[

	// ����������
	p_texture.clear();
	p_texture.shrink_to_fit();	// �m�ۂ�����������z��̃T�C�Y�ɍ��킹��
	filename.clear();
	filename.shrink_to_fit();	// �m�ۂ�����������z��̃T�C�Y�ɍ��킹��


	//-----�V�[���ɂ���ēǂݍ��ރe�N�X�`���𕪂���-----
	switch (scene){

	case cSceneManeger::TITLE:
		filename = texTitle;	// �t�@�C�������Z�b�g
		break;
	case cSceneManeger::STAGE_SELECT:
		filename = texStageSelect;	// �t�@�C�������Z�b�g
		break;
	case cSceneManeger::GAME:
		filename = texGame;		// �t�@�C�������Z�b�g
		break;
		/*
		case cSceneManeger::SAMPLE:
			// �t�@�C�������Z�b�g
			filename = texSample;
		*/
	default:
		break;
	}

	// �e�N�X�`���̃|�C���^�̃��T�C�Y
	p_texture.resize(filename.size());

	// ���[�h
	for (int i = 0; i < (int)filename.size(); i++){
		D3DXCreateTextureFromFile(pDevice, filename[i], &p_texture[i]);
	}
}


//=======================================================================================
//
//		�V�[�����Ƃ̃e�N�X�`���̎擾
//
//=======================================================================================
LPDIRECT3DTEXTURE9* cTextureManeger::GetTextureTitle(TEX_TITLE texNum){	//�^�C�g��
	return &p_texture[texNum];
}

LPDIRECT3DTEXTURE9* cTextureManeger::GetTextureStageSelect(TEX_STAGE_SELECT texNum){	//�X�e�[�W�Z���N�g
	return &p_texture[texNum];
}

LPDIRECT3DTEXTURE9* cTextureManeger::GetTextureGame(TEX_GAME texNum){	//�Q�[�����C��
	return &p_texture[texNum];
}

