//======================================================================
//	NormalStars
//	
//	�T�v�Q�F���N���X�Ȃ�
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___NORMAL_STARS_H___
#define ___NORMAL_STARS_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"
#include "Sprite.h"
#include "Net_Type2.h"
#include "BlackHole.h"

#include <vector>
#include <fstream>

struct SetNormalStar{
	D3DXVECTOR2 center;
	D3DXVECTOR2 radius;
	D3DXVECTOR2 size;
	float		speed;
};

//-----------------------------
// �}�N����`
//-----------------------------
#define STAGE_01_STAR_NUM	(5)
#define MAX_NORMAL_STAR		(50)


//-----------------------------
// �\���̒�`
//-----------------------------
// ���u���̃f�[�^
typedef struct _tNormalStarData{

	cSpriteParam			t_Sprite;			// �`��p
	cCollider				t_Collider;			// ������
	cCircleOrbitMovement	t_MoveCircle;		// �~�O���p����
	bool					t_bUse;				// �g�p�t���O
	D3DXVECTOR2				t_Move;				// �ړ���
	bool					t_bVibration;		// �U���p
	int						t_nVibrationFrame;
	int						t_nRespawnFrame;	// ���X�|�[���t���[��
	bool					t_bRespawn;			// ���X�|�[���t���O
	
}tNormalStarData;

//-----------------------------
// �N���X��`
//-----------------------------
//******���u��********
class cNormalStar :public cBaseStar{

public:
	void Update();
	void Draw();
	~cNormalStar();
	cNormalStar();

	//--- �ԂƂ̏��� ---
	void SetNetData();
	void OnCollidToNet(int count);
	

	//--- �u���b�N�z�[���Ƃ̏��� ---
	void SetBlackHoleData(cBlackHole*);
	void OnCollidToBlackHole(int Normal,int Black);
	void OnCollidToDelete(int Normal);
	

	//--- ���̃����_������ ---
	void CreateRamdom();

	//--- ���̃��X�|�[�� ---
	void Respawn(int num);

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
	tNormalStarData* GetStarData(){
		return m_pStarData;
	}

private:
	cNet*				m_pNetData;
	tNormalStarData*	m_pStarData;
	cBlackHole*			m_pBlackHoleData;

	

};
#endif	//!___NORMAL_STARS_H___