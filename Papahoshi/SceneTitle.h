//======================================================================
//	Title
//	
//	�T�v�Q�F�^�C�g��(��)
//	����ҁF
//	
//======================================================================

#ifndef ___SCENE_TITLE_H___
#define ___SCENE_TITLE_H___

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "SceneManeger.h"
#include <d3d9.h>

//------------------------------
// �}�N����`
//------------------------------
#define TEXTURE_FILNAME_ENEMY ("Image/Character/KingJelly.jpg")
#define TEXTURE_FILNAME_PLAYER ("Image/Character/Jelly.png")

//------------------------------
// �N���X��`
//------------------------------
//----�V�[���^�C�g��-----
class cSceneTitle :public cBaseScene{

public:
	void Draw();	//�`��
	void Update();	//�X�V
	cSceneTitle();	//�R���X�g���N�^
	~cSceneTitle();	//�f�X�g���N�^


private:

};
#endif //!___SCENE_TITLE_H___