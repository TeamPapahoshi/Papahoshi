//======================================================================
//	RearStar
//	
//	�T�v�Q�F���A��
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___REAR_STAR_H___
#define ___REAR_STAR_H___

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
// �񋓑̒�`
//-----------------------------
enum eRearStarType{
	PANET_01,
	PANET_02,
	PANET_03,
	SUN,
	REAR_TYPE_MAX
};
//-----------------------------
// �N���X��`
//-----------------------------
class cRearStarData :public cBaseStarData{
public:
	cCollider		m_VacumeRange;		// �z�����ݔ͈�
	cCollider		m_DeleteRange;		// �폜�͈�

	eRearStarType	m_eType;			// ���
};


class cRearStar :public cBaseStar{

public:
	void Update();
	void Draw();
	~cRearStar();
	cRearStar();

	//--- �ԂƂ̏��� ---
	void SetNetData(cNet* data);
	void OnCollidToNet(int num);

	//---- �����X�^�[�g ----
	void SetCreateStart(){
		m_pStarData = m_pRoot;
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
			m_pStarData->m_bCreateEvent = true;
		}
	}

	


	bool GetCapturedFlag(){
		return m_pStarData->m_bCaptured;
	}

	void Create();		// ����
	void Destroy();		// �폜
	void Respawn();		// ���X�|�[��

private:
	cRearStarData* m_pStarData;	// �K�v�f�[�^
	cRearStarData*	m_pRoot;	// �擪�A�h���X�i�[�p
	cNet*			m_pNetData;

	//Set&Get
public:

	// Getter
	cRearStarData* GetStarData(){
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

#endif //!___BLACK_HOLE_H___