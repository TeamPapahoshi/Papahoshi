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
#define MAX_BLACK_HOLE_NUM	(100)



//-----------------------------
//�N���X��`
//-----------------------------

class cBlackHoleData :public cBaseStarData{

public:
	// �ǉ�������
	cCollider		m_VacuumCollider;				// �z�����ݔ͈�
	cCollider		m_DeleteCollider;


	float rad;			// �e�X�g�p���o�m�F

	
};

class cBlackHole :public cBaseStar{		//�g��Ȃ����������ǈꉞ�p������

public:
	void Update();
	void Draw();
	~cBlackHole();
	cBlackHole();


	// Getter
	cBlackHoleData* GetStarData(){
		return m_pStarData;
	}

	void Create();

private:
	cBlackHoleData* m_pStarData;	// �u���b�N�z�[���̕K�v�f�[�^
	cBlackHoleData*	m_pRoot;		// �擪�A�h���X�i�[�p

};
#endif //!___BLACK_HOLE_H___