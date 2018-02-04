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
#include "Net_Type2.h"
#include <vector>
#include <fstream>

//-----------------------------
// �N���X��`
//-----------------------------
class cBlackHoleData :public cBaseStarData{
public:
};


class cBlackHole :public cBaseStar{

public:
	void Update();
	void Draw();
	~cBlackHole();
	cBlackHole();

	//--- �ԂƂ̏��� ---
	void SetNetData(cNet* data);
	void OnCollidToNet(int num);

	void Create();		// ����
	void Destroy();		// �폜
	void Respawn();		// ���X�|�[��

private:
	cBlackHoleData* m_pStarData;	// �K�v�f�[�^
	cBlackHoleData*	m_pRoot;	// �擪�A�h���X�i�[�p
	cNet*			m_pNetData;

	//Set&Get
public:

	// Getter
	cBlackHoleData* GetStarData(){
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