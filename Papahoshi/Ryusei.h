//======================================================================
//	Ryusei.h
//	
//	�T�v�Q�F����
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___RYUSEI_H___
#define ___RYUSEI_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"
#include "Sprite.h"
#include "RyuseiLine.h"
#include "Net_Type2.h"

#define MAX_LINE_EFFECT	(1)

//-----------------------------
// �N���X��`
//-----------------------------
class cRyuseiData :public cBaseStarData{
public:

	D3DXVECTOR2		cp1, cp2, cp3, cp4;	// �x�W�F�Ȑ��v�Z�p
	float			time=0;
	cSpriteParam	m_Core;				//�@�j
	cRyuseiLine		m_Line;


	D3DXVECTOR2		m_VecMove;			// �ړ������̃x�N�g��

};

class cRyusei :public cBaseStar{

public:
	void Update();
	void Draw();
	~cRyusei();
	cRyusei();


	//--- �ԂƂ̏��� ---
	void SetNetData(cNet* data);
	void OnCollidToNet(int num);

	void Create();		// ����
	void Destroy();		// �폜
	void Respawn();		// ���X�|�[��

private:
	cRyuseiData*	m_pStarData;		// �K�v�f�[�^
	cRyuseiData*	m_pRoot;			// �擪�A�h���X�i�[�p
	cRyuseiLine*	m_pLine;
	cNet*			m_pNetData;			// �Ԃ̃f�[�^�i�[




	//Set&Get
public:

	// Getter
	cRyuseiData* GetStarData(){
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
#endif	//!___RYUSEI_H___