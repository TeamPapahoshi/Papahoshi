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
#include "Gage.h"
#include <vector>
#include <fstream>
#include "Score.h"

//-----------------------------
// �N���X��`
//-----------------------------
class cNormalStarData :public cBaseStarData{
public:
	bool	m_bVibration = true;
	int		m_nVibrationFrame = 0;
	int		m_nEffectFrame = 0;
	int		m_nStarColorNum = 0;
	bool	m_bAddScore = false;
	int		m_nLifeTime = 0;

	// �u���b�N�z�[��
	bool	m_bHitBlackHoleDelete=false;

	// �������Ԃŏ���
	bool	m_DeleteToLifeTime=false;

	// 覐�
	bool	m_bHitSpaceRock = false;


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
	void OnCollidToBlackHoleVacumeRange(int Normal,int Black);
	void OnCollidToBlackHoleDeleteRange(int Normal);

	//--- 覐΂Ƃ̏����Ƃ̏��� ---
	void SetSpaceRockData(cBlackHole* data);
	void OnCollidToSpaceRock(int num);
	
	//--- �Q�[�W�Ƃ̏��� ---
	void SetGageData(cGage* data);
	
	void Create();		// ����
	void Destroy();		// �폜
	void Respawn();		// ���X�|�[��

private:
	cNormalStarData*	m_pStarData;		// �K�v�f�[�^
	cNormalStarData*	m_pRoot;			// �擪�A�h���X�i�[�p
	cBlackHole*			m_pBlackHoleData;	// �u���b�N�z�[���̃f�[�^���i�[
	cNet*				m_pNetData;			// �Ԃ̃f�[�^�i�[
	cGage*				m_pGageData;		// �Q�[�W�̃f�[�^�i�[

	// ���X�|�[������Ƃ��ɏ������������
	void Init();
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