//======================================================================
//	SampleStar
//	
//	�T�v�Q�F�R�s�[�p��
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___SAMPLE_STAR_H___
#define ___SAMPLE_STAR_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"


//-----------------------------
//�N���X��`
//-----------------------------
//------- �\���݂̂����Ɏg�� ---------
class cSampleStarData :public cBaseStarData{
public:
	// ���̐�����(��)
	cCollider		m_VacuumCollider;				// �z�����ݔ͈�
	cCollider		m_DeleteCollider;
	float rad;										// �e�X�g�p���o�m�F
};

//--- �V�[���ŃC���X�^���X��  --------
class cSampleStar :public cBaseStar{		

public:
	void Update();
	void Draw();
	~cSampleStar();
	cSampleStar();

	void Create();		// ����
	void Destroy();		// �폜

private:
	cSampleStarData* m_pStarData;	// �K�v�f�[�^
	cSampleStarData*	m_pRoot;	// �擪�A�h���X�i�[�p

//Set&Get
public:

	cSampleStarData* GetStarData(){
		return m_pStarData;
	}

	// �����Ƃ��Ńt���O�𑀍삷��Ƃ��͂��̊֐����g����
	//����������������������������������������������������������������
	void SetCountAndUse(bool flag){
		if (flag){
			if (!m_pStarData->m_bUse){
				m_pStarData->m_bUse = true;
				m_nCurrentNum++;
			}
		}
		else{
			if (m_pStarData->m_bUse){
				m_pStarData->m_bUse = false;
				m_nCurrentNum--;
			}
		}
	}
	//����������������������������������������������������������������
};
#endif //!___BLACK_HOLE_H___