//======================================================================
//	SceneStageSelect
//	
//	�T�v�Q�F�X�e�[�W�I�����
//	����ҁF���� ����
//	
//======================================================================

#ifndef ___SCENE_STAGESELECT_H___
#define ___SCENE_STAGESELECT_H___

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include <d3d9.h>
#include "SceneManeger.h"
#include "StageSelect.h"

#define TEXTURE_FILENAME_STAGESELECT ("Image/Character/KingJelly.jpg")	//���̃e�N�X�`��
#define TEXTURE_FILENAME_STAGECLEAR  ("data/texture/akira000.png")	//���̃e�N�X�`��2

//------------------------------
// �N���X��`
//------------------------------
//----�V�[���Q�[��-----
class cSceneStageSelect :public cBaseScene{

public:
	void Draw();	//�`��
	void Update();	//�X�V
	cSceneStageSelect();	//�R���X�g���N�^
	~cSceneStageSelect();	//�f�X�g���N�^

	// ���̃V�[���Ŏg���e�N�X�`��
	enum Texture{
		STAGESELECT_TEXTURE,
		STAGECLEAR_TEXTURE,
		MAX_TEXTURE
	};

	void LoadTextureFromFile();

	cStageSelect* GetStage(void);	//�X�e�[�W���̎擾�p(�b��)

private:
	LPDIRECT3DTEXTURE9 m_pTex[MAX_TEXTURE];	// ���̃V�[���Ŏg���e�N�X�`���̃|�C���^�z��


};
#endif //!___SCENE_STAGESELECT_H___