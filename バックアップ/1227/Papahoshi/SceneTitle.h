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
#include "Star.h"
#include "TitleRogo.h"
#include "TitleWave.h"
#include "TitleShip.h"

//------------------------------
// �}�N����`
//------------------------------
#define TEXTURE_FILNAME_ENEMY ("Image/Character/KingJelly.jpg")
#define TEXTURE_FILNAME_PLAYER ("Image/Character/Jelly.png")

#define CIRCLE_ORBIT_STAR_NUM (2)

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
	cTitleRogo* pTitleRogo;
	cTitleWave* pTitleWave;
	cTitleShip* pTitleShip;
	cCircleOrbitStar*	pCircleOrbitStar[CIRCLE_ORBIT_STAR_NUM];

};
#endif //!___SCENE_TITLE_H___