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

private:
	cCollider		m_Collider;			// �����蔻��
	int				m_nVacuumStar;		// �z�����ސ��̐�
	D3DXVECTOR2		move;				// �ړ���
};
#endif //!___BLACK_HOLE_H___