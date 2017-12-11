//======================================================================
//	Texture
//	
//	�T�v�F�e�N�X�`�Ǘ�
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


//-----------------------------
// �O���[�o��
//-----------------------------
//----Title-----
vector<char*> texTitle = {
	TEXTURE_FILNAME_KING_JELLY,
	TEXTURE_FILNAME_JELLY		// �����摜�ł��V�[�����Ⴄ�Ƃ��͂�����񏑂���
};

//----Game-----
vector<char*> texGame = {
	TEXTURE_FILNAME_JELLY,		// �����摜�ł��V�[�����Ⴄ�Ƃ��͂�����񏑂���
	TEXTURE_FILNAME_STAR_LIGHT,
	TEXTURE_FILNAME_STAR,
	TEXTURE_FILNAME_EF,
	TEXTURE_FILNAME_EF02
};

/*
//----Sample-----
vector<char*> texSample = {
TEXTURE_FILNAME_JELLY,
};

*/

// �e�N�X�`���̃|�C���^
vector<LPDIRECT3DTEXTURE9>  cTextureManager::p_texture(1,NULL);	// ������(�v�f��,���g)



//=======================================================================================
//
//		�V�[�����Ƃ̃e�N�X�`���̃��[�h
//		����	�V�[��
//
//=======================================================================================
void cTextureManager::LoadTexture(cSceneManeger::SCENE scene){

	//----------------------------
	//���[�J���ϐ��錾
	//----------------------------
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// Direct3D�f�o�C�X
	vector<char*> filename;						// �t�@�C�����i�[


	//-----�V�[���ɂ���ēǂݍ��ރe�N�X�`���𕪂���-----
	switch (scene){

	case cSceneManeger::TITLE:

		// �t�@�C�������Z�b�g
		filename = texTitle;

		// �e�N�X�`���̃|�C���^�̃��T�C�Y
		p_texture.resize(TEX_TITLE_MAX);
	

		// ���[�h
		for (int i = 0; i < TEX_TITLE_MAX; i++){
			D3DXCreateTextureFromFile(pDevice, filename[i], &p_texture[i]);
		}
		break;

	case cSceneManeger::GAME:

		// �t�@�C�������Z�b�g
		filename = texGame;

		// �e�N�X�`���̃|�C���^�̃��T�C�Y
		p_texture.resize(TEX_GAME_MAX);

		// ���[�h
		for (int i = 0; i < TEX_GAME_MAX; i++){
			D3DXCreateTextureFromFile(pDevice, filename[i], &p_texture[i]);
		}
		break;

		/*
		case cSceneManeger::SAMPLE:
			// �t�@�C�������Z�b�g
			filename = texSample;
		
			// �e�N�X�`���̃|�C���^�̃��T�C�Y
			p_texture.resize(TEX_SAMPLE_MAX);

		for (int i = 0; i < TEX_SAMPLE_MAX; i++){
			D3DXCreateTextureFromFile(pDevice, filename[i], &p_texture[i]);
			}
		break;
		*/

	default:
		break;
	}
}


//=======================================================================================
//
//		�V�[�����Ƃ̃e�N�X�`���̎擾
//
//=======================================================================================
LPDIRECT3DTEXTURE9* cTextureManager::GetTextureTitle(TEX_TITLE texNum){
	return &p_texture[texNum];
}

LPDIRECT3DTEXTURE9* cTextureManager::GetTextureGame(TEX_GAME texNum){
	return &p_texture[texNum];
}

