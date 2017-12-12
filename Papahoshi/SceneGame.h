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

#define STAR_NUM		(5)	//��
#define FIXED_STAR_NUM	(1)	//��

//------------------------------
// �N���X��`
//------------------------------
//----�V�[���Q�[��-----
class cSceneGame :public cBaseScene{

public:
	//---- �񋓌^�錾 ----
	enum GAME_PHASE{	//�Q�[���t�F�C�Y
		PHASE_POST,	//�\��
		PHASE_SHOUT,	//��΂�
		PHASE_PULL,		//����

		PHASE_MAX,
	};

	//---- �v���g�^�C�v�錾 ----
	void Draw();	//�`��
	void Update();	//�X�V
	cSceneGame();	//�R���X�g���N�^
	~cSceneGame();	//�f�X�g���N�^

	GAME_PHASE GetGamePhase();

private:
	// ���̃V�[���ŃC���X�^���X������̂̃|�C���^
	cBG*				m_pBG;
	cCircleOrbitStar*	pStar[STAR_NUM];
	cFixedStar*			pFixedStar[FIXED_STAR_NUM];

	GAME_PHASE			m_gamePhase;	//�Q�[���t�F�C�Y��ۊ�

};
#endif //!___SCENE_TITLE_H___