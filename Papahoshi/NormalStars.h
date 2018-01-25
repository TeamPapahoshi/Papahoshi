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
	cCollider				t_Collider;		// �����蔻��
	cCircleOrbitMovement	t_MoveCircle;	// �~�O���p
	bool					t_bUse;			// �g�p�t���O
	
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
	tNormalStarData*	m_pStarData;
	int					m_nMaxNum;

	cNet*				m_pNetData;

	//--- �t���O ---
	bool	m_bCapchared;	// �m�ۊ���



	//--- �t���[���֘A ---
	int m_nRespawnFream;	// ���X�|�[��


};
#endif	//!___NORMAL_STARS_H___