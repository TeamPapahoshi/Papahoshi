//======================================================================
//	Title
//	
//	�T�v�Q�F���U���g(��)
//	����ҁF
//	
//======================================================================

#ifndef ___SCENE_RESULT_H___
#define ___SCENE_RESULT_H___

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "SceneManeger.h"
#include <d3d9.h>

//------ �g�p����I�u�W�F�N�g -------
#include "Ranking.h"
#include "BG.h"

//------------------------------
// �}�N����`
//------------------------------

//------------------------------
// �N���X��`
//------------------------------
//----�V�[���^�C�g��-----
class cSceneResult :public cBaseScene{

public:
	void Draw();	//�`��
	void Update();	//�X�V
	cSceneResult();	//�R���X�g���N�^
	~cSceneResult();	//�f�X�g���N�^

private:
	cRanking* m_pRanking;
	cBG*	  m_pBG;

};
#endif //!___SCENE_RESULT_H___