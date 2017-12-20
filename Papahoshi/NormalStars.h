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

#include <vector>
#include <fstream>

struct SetNormalStar{
	D3DXVECTOR2 center;
	D3DXVECTOR2 radius;
	D3DXVECTOR2 size;
	float		speed;
};

// �}�N����`
#define STAGE_01_STAR_NUM	(5)



//-----------------------------
//�N���X��`
//-----------------------------
//******���u��********
class cNormalStar :public cBaseStar{

public:
	void Update();
	void Draw();

	~cNormalStar();
	cNormalStar();

	// ���̐ݒ�
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

	// �t�@�C���œǂݍ��񂾃f�[�^���Z�b�g
	void SetStarFromFile(int loop);

	// �P���Ƃ̋����ɂ���Ă݂��邩�����Ȃ�����ς��鏈��
	void StarVisibility(float distance);

	// �v�Z�p�̈ʒu���擾
	D3DXVECTOR2 GetPos(){
		return m_sprite.GetPos();
	}

	// ��
	enum STAFGE_NUM{
		STAGE_01,
		STAGE_MAX,
	};


private:
	cCircleOrbitMovement moveCircle;	// �~�O�����邽�߂ɕK�v
	vector<SetNormalStar> a_Data;
	STAFGE_NUM stageNum = STAGE_01; //��

};
#endif	//!___NORMAL_STARS_H___