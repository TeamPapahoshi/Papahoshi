//======================================================================
//	Scenegame
//	
//	�T�v�Q�F�Q�[�����C��(��)
//	����ҁF
//	
//======================================================================

#ifndef ___SCENE_GAME_H___
#define ___SCENE_GAME_H___

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "SceneManeger.h"

//------------------------------
// �N���X��`
//------------------------------
//----�V�[���Q�[��-----
class cSceneGame :public cBaseScene{

public:
	void Draw();	//�`��
	void Update();	//�X�V
	cSceneGame();	//�R���X�g���N�^
	~cSceneGame();	//�f�X�g���N�^

	// ���̃V�[���Ŏg���e�N�X�`��
	enum Texture{
		MAX_TEXTURE,
	};

	void LoadTextureFromFile();

private:
	//LPDIRECT3DTEXTURE9 m_pTex[MAX_TEXTURE];	// ���̃V�[���Ŏg���e�N�X�`���̃|�C���^�z��


};
#endif //!___SCENE_TITLE_H___