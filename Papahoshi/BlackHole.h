//======================================================================
//	BlackHole
//	
//	�T�v�Q�F�u���b�N�z�[��
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___BLACK_HOLE_H___
#define ___BLACK_HOLE_H___

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
#define MAX_BLACK_HOLE_NUM	(5)



//-----------------------------
// �\���̒�`
//-----------------------------
// �u���b�N�z�[���̃f�[�^
typedef struct _tBlackHoleData{

	cSpriteParam			t_Sprite;				// �`��p
	cCollider				t_VacuumCollider;		// �z�����ݔ͈�
	cCollider				t_DeleteCollider;		// ���Ŕ͈�
	cCircleOrbitMovement	t_MoveCircle;			// �~�O���p����
	bool					t_bUse;					// �g�p�t���O
	int						t_nRespawnFrame;		// ���X�|�[���t���[��
	bool					t_bRespawn;				// ���X�|�[���t���O

}tBlackHoleData;

//-----------------------------
//�N���X��`
//-----------------------------
//******�u���b�N�z�[��********
class cBlackHole :public cBaseStar{

public:
	void Update();
	void Draw();
	~cBlackHole();
	cBlackHole();


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

	// Getter
	tBlackHoleData* GetStarData(){
		return m_pStarData;
	}

	void Create(int num);

	// ���̐ݒ�
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

private:
	tBlackHoleData*	m_pStarData;
};
#endif //!___BLACK_HOLE_H___