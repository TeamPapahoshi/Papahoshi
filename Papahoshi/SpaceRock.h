//======================================================================
//	SpaceRock
//	
//	�T�v�Q�F覐�
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___SPACE_ROCK_H___
#define ___SPACE_ROCK_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"
#include "Net_Type2.h"
#include "NormalStars.h"


//-----------------------------
// �\���̒�`
//-----------------------------
//-----------------------------
// �N���X��`
//-----------------------------
class cSpaceRockData :public cBaseStarData{
public:
	int				m_nDestroyStarNum;	// �j�󂷂鐔


	cSpriteParam	m_ExplosionAnim;	// ���j��G�t�F�N�g�p
	int				m_ExplosionFrame;	// ��������
	bool			m_bExplosion;		// �J�n�p�t���O
};


//-----------------------------
//�N���X��`
//-----------------------------
class cSpaceRock :public cBaseStar{

public:
	void Update();
	void Draw();
	~cSpaceRock();
	cSpaceRock();

	//--- �ԂƂ̏��� ---
	void SetNetData(cNet* data);
	void OnCollidToNet(int num);

	//--- ���u���Ƃ̏��� ----
	void SetNormalStarData(cNormalStar* data);
	void OnCollidToNormalStar(int num);

	//--- ��{���� ---
	void Create();		// ����
	void Destroy();		// �폜
	void Respawn();		// ���X�|�[��

private:
	cSpaceRockData* m_pStarData;	// �K�v�f�[�^
	cSpaceRockData*	m_pRoot;		// �擪�A�h���X�i�[�p
	cNet*			m_pNetData;
	cNormalStar*	m_pNormalStarData;

	//Set&Get
public:

	// Getter
	cSpaceRockData* GetStarData(){
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
#endif //!___SPACE_ROCK_H___