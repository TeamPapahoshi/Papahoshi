//======================================================================
//	FixedStars
//	
//	�T�v�Q�F���N���X�Ȃ�
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___FIXED_STARS_H___
#define ___FIXED_STARS_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"

//-----------------------------
//�N���X��`
//-----------------------------

//******�P��********
class cFixedStar :public cBaseStar{

public:
	void Update();
	void Draw();

	~cFixedStar();
	cFixedStar();

	// ���̐ݒ�
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

	void SetCounAndUse(bool flag){}
private:
	cCollider		m_Collider;			// �����蔻��
	cCircleOrbitMovement moveCircle;
	bool m_bSizeSwitch;

};


#endif	//!___FIXED_STARS_H___