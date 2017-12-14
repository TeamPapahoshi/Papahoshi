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

	// �P���Ƃ̋����ɂ���Ă݂��邩�����Ȃ�����ς��鏈��
	void StarVisibility(float distance);

	// �v�Z�p�̈ʒu���擾
	D3DXVECTOR2 GetPos(){
		return m_sprite.GetPos();
	}

private:
	cCircleOrbitMovement moveCircle;	// �~�O�����邽�߂ɕK�v

};

#endif	//!___NORMAL_STARS_H___