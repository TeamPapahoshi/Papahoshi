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

	cSpriteParam			t_Sprite;		// �`��p
	cCollider				t_Collider;		// ������
	cCircleOrbitMovement	t_MoveCircle;	// �~�O���p����
	bool					t_bUse;			// �g�p�t���O
	D3DXVECTOR2				t_Move;
	
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
	void OnCollidToNet(int count);
	void SetNetData();

	//--- �u���b�N�z�[���Ƃ̏��� ---
	void OnCollidToBlackHole(int Normal,int Black);
	void OnCollidToDelete(int Normal);
	void SetBlackHoleData(cBlackHole*);


	//--- ���̃����_������ ---
	void CreateRamdom();

	//--- ���̃��X�|�[�� ---
	void Respawn();


	//--- ���̐ݒ� ---
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);


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