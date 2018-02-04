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

//-----------------------------
// �N���X��`
//-----------------------------
class cNormalStarData :public cBaseStarData{
public:


};

class cNormalStar :public cBaseStar{

public:
	void Update();
	void Draw();
	~cNormalStar();
	cNormalStar();

	//--- �ԂƂ̏��� ---
	void SetNetData(cNet* data);
	void OnCollidToNet(int num);
	
	//--- �u���b�N�z�[���Ƃ̏��� ---
	void SetBlackHoleData(cBlackHole* data);
	void OnCollidToBlackHole(int Normal,int Black);
	void OnCollidToDelete(int Normal);
	
	void Create();		// ����
	void Destroy();		// �폜
	void Respawn();		// ���X�|�[��

private:
	cNormalStarData*	m_pStarData;		// �K�v�f�[�^
	cNormalStarData*	m_pRoot;			// �擪�A�h���X�i�[�p
	cBlackHole*			m_pBlackHoleData;	// �u���b�N�z�[���̃f�[�^���i�[
	cNet*				m_pNetData;			// �Ԃ̃f�[�^�i�[


	//Set&Get
public:

	// Getter
	cNormalStarData* GetStarData(){
		return m_pRoot;
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
#endif	//!___NORMAL_STARS_H___