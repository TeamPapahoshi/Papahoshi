//======================================================================
//	SpaceRock
//	
//	�T�v�Q�F覐�
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___SPACE_ROCK_H___
#define ___SPACE_ROCK_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"
#include <vector>
#include <fstream>


//-----------------------------
// �}�N����`
//-----------------------------
#define MAX_SPACE_ROCK_NUM	(5)



//-----------------------------
// �\���̒�`
//-----------------------------
// �u���b�N�z�[���̃f�[�^
typedef struct _tSpaceRockData{

	cSpriteParam			t_Sprite;				// �`��p
	cCollider				t_Collider;				// �����蔻��
	cCircleOrbitMovement	t_MoveCircle;			// �~�O���p����
	bool					t_bUse;					// �g�p�t���O
	int						t_nRespawnFrame;		// ���X�|�[���t���[��
	bool					t_bRespawn;				// ���X�|�[���t���O

}tSpaceRockData;

//-----------------------------
//�N���X��`
//-----------------------------
class cSpaceRock :public cBaseStar{

public:
	void Update();
	void Draw();
	~cSpaceRock();
	cSpaceRock();

	// Getter
	tSpaceRockData* GetStarData(){
		return m_pStarData;
	}


	//--- ���̃t���O�I�� & �J�E���g�A�b�v ----
	void CountUp(int num){

		if (!m_pStarData[num].t_bUse){
			m_pStarData[num].t_bUse = true;
			m_nCurrentNum++;
		}

	}
	//--- ���̃t���O�I�t & �J�E���g�_�E�� ----
	void CountDown(int num){

		if (m_pStarData[num].t_bUse){
			m_pStarData[num].t_bUse = false;
			m_nCurrentNum--;
		}
	}

	void Respawn(int num);

	// ���̐ݒ�
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

private:
	tSpaceRockData*	m_pStarData;
};
#endif //!___SPACE_ROCK_H___