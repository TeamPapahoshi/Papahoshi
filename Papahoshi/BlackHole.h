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

//struct SetNormalStar{
//	D3DXVECTOR2 center;
//	D3DXVECTOR2 radius;
//	D3DXVECTOR2 size;
//	float		speed;
//};



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

	// ���̐ݒ�
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

	// �t�@�C���œǂݍ��񂾃f�[�^���Z�b�g
	//void SetStarFromFile(int loop);

	// �P���Ƃ̋����ɂ���Ă݂��邩�����Ȃ�����ς��鏈��
	//void StarVisibility(float distance);

	// �v�Z�p�̈ʒu���擾
	D3DXVECTOR2 GetPos(){
		return m_sprite.GetPos();
	}

private:
	cCircleOrbitMovement moveCircle;	// �~�O�����邽�߂ɕK�v


};
#endif	//!___BLACK_HOLE_H___