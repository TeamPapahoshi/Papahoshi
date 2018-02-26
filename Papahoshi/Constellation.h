//======================================================================
//	���Q
//	
//	�T�v�Q�F
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___CONSTELLATION_H___
#define ___CONSTELLATION_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"
#include "NormalStars.h"

//-----------------------------
// �񋓑̒�`
//-----------------------------
enum eConsellationType
{
	TYPE_01,
	TYPE_MAX,
};


//-----------------------------
//�N���X��`
//-----------------------------
//------- �\���݂̂����Ɏg�� ---------
class cConstellationData :public cBaseStarData{		// ���Q��S��
public:
	int m_nStarColorNum;
	cCircleOrbitMovement m_CircleMoveData;			// �~�O���ɕK�v�ȃf�[�^
	
};

//--- �V�[���ŃC���X�^���X��  --------
class cConstellation :public cBaseStar{

public:
	void Update();
	void Draw();
	~cConstellation();
	cConstellation();

	void Create();		// ����
	void Destroy();		// �폜
	void Respawn();		// ���X�|�[��

private:
	cConstellationData* m_pStarData;	// �K�v�f�[�^
	cConstellationData*	m_pRoot;	// �擪�A�h���X�i�[�p


	eConsellationType	m_eType;


	//Set&Get
public:

	cConstellationData* GetStarData(){
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
#endif //!___CONSTELLATION_H___