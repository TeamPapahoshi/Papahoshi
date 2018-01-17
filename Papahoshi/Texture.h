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
#include <vector>
#include <iostream>
#include "debugproc.h"
#include "Common.h"
#include "SceneManeger.h"

//-----------------------------
// �O���[�o��
//-----------------------------

//-----------------------------
// �񋓑�
//-----------------------------
//***************************************
// �V�[�����Ƃ̃e�N�X�`���̃|�C���^�ԍ�
//***************************************
	enum TEX_TITLE{
		TEX_TITLE_KING_JELLY,
		TEX_TITLE_JELLY,
		TEX_TITLE_SPHERE_LIGHT,
		TEX_TITLE_SHIP,
		TEX_TITLE_WAVE,
		TEX_TITLE_MAX
	};

enum TEX_STAGE_SELECT{
	TEX_STAGESELECT_STAGE,
	TEX_STAGESELECT_KING_JELLY,
	TEX_STAGESELECT_MAX
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
		TEX_GAME_HALFCIRCLE,
		TEX_GAME_BLACK_HOLE,
		TEX_GAME_MAX
	};
	/*
	enum TEX_SAMPLE{
	TEX_SAMPLE_ENEMY,
	TEX_SAMPLE_MAX
	};
	*/



//-----------------------------
//�N���X��`
//-----------------------------
//---- �e�N�X�`���[�Ǘ��N���X ------
class cTextureManeger {
public:

	// �e�N�X�`����ǂݍ���
	void LoadTexture(cSceneManeger::SCENE scene);

	// �e�N�X�`�����擾����
	static LPDIRECT3DTEXTURE9* GetTextureTitle(TEX_TITLE texNum);
	static LPDIRECT3DTEXTURE9* GetTextureStageSelect(TEX_STAGE_SELECT texNum);
	static LPDIRECT3DTEXTURE9* GetTextureGame(TEX_GAME texNum);

	cTextureManeger(){}
	~cTextureManeger(){}

private:
	static vector<LPDIRECT3DTEXTURE9> p_texture;	// �e�N�X�`���̃|�C���^�̓��I�z��
};

#endif	//!___TEXTURE_H___