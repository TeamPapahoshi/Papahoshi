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
#include <d3d9.h>
#include "SceneManeger.h"

// ���̃V�[���Ŏg���I�u�W�F�N�g
#include "BG.h"
#include "Star.h"
#include "Pause.h"

#define STAR_NUM		(5)	//��
#define FIXED_STAR_NUM	(1)	//��

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

private:
	// ���̃V�[���ŃC���X�^���X������̂̃|�C���^
	cBG*				m_pBG;
	cCircleOrbitStar*	pStar[STAR_NUM];
	cFixedStar*			pFixedStar[FIXED_STAR_NUM];
	cPause*				m_pPause;

};
#endif //!___SCENE_TITLE_H___