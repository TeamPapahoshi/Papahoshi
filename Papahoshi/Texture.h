//======================================================================
//	Texture
//
//	�T�v�Q�F�e�N�X�`���[�Ǘ�
//	����ҁF���� ��
//	
//======================================================================
#ifndef ___TEXTURE_H___
#define ___TEXTURE_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>		//HRESULT��
#include "debugproc.h"		//printdebug
#include<vector>
#include<iostream>
#include "Common.h"
#include"SceneManeger.h"




//-----------------------------
// �O���[�o��
//-----------------------------

// ���O��Ԃ̎w��
using namespace std;


//-----------------------------
//�N���X��`
//-----------------------------
//---- �e�N�X�`���[�Ǘ��N���X ------
// �N���X��`
class cTextureManager {
public:

	// �����ɂ��ǉ�
	enum TEX_TITLE{
		TEX_TITLE_KING_JELLY,
		TEX_TITLE_JELLY,
		TEX_TITLE_MAX
	};
	enum TEX_GAME{
		TEX_GAME_JELLY,
		TEX_GAME_STAR_LIGHT,
		TEX_GAME_STAR,
		TEX_GAME_FE,
		TEX_GAME_FE02,
		TEX_GAME_NET,
		TEX_GAME_UKI,
		TEX_GAME_ARROW,
		TEX_GAME_MAX
	};
	/*
	enum TEX_SAMPLE{
	TEX_SAMPLE_ENEMY,
	TEX_SAMPLE_MAX
	};
	*/

	// �e�N�X�`����ǂݍ���
	void LoadTexture(cSceneManeger::SCENE scene);

	// �e�N�X�`�����擾����
	static LPDIRECT3DTEXTURE9* GetTextureTitle(TEX_TITLE texNum);
	static LPDIRECT3DTEXTURE9* GetTextureGame(TEX_GAME texNum);

	cTextureManager(){}
	~cTextureManager(){}

private:
	static vector<LPDIRECT3DTEXTURE9> p_texture;	// �e�N�X�`���̃|�C���^�̓��I�z��
};

#endif	//!___TEXTURE_H___