//======================================================================
//	Stage01(�`���[�g���A���X�e�[�W�H)
//	
//	�T�v�Q�F�X�e�[�W01(��)
//	����ҁF
//	
//======================================================================

#ifndef ___STAGE_01_H___
#define ___STAGE_01_H___

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "StageManager.h"
#include <d3d9.h>

// ���̃N���X�Ŏg���I�u�W�F�N�g
#include "BlackHole.h"

//------------------------------
// �}�N����`
//------------------------------


//------------------------------
// �N���X��`
//------------------------------
//----�V�[���^�C�g��-----
class cStage01 :public cBaseStage{

public:
	void Draw();				// �`��
	void Update();				// �X�V
	cStage01();					// �R���X�g���N�^
	~cStage01();				// �f�X�g���N�^
private:
	cBaseStar* m_pBlackHole;	// �u���b�N�z�[��(��)
};
#endif //!___STAGE_01_H___