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
#include "Net_Type2.h"
#include "sound.h"

#define MAX_LINE_EFFECT	(1)





//-----------------------------
// �N���X��`
//-----------------------------
class cRyuseiData :public cBaseStarData{
public:

	// ����鏈���p
	bool			m_bStream=true;		// �����ǂ���
	D3DXVECTOR2		m_StreamStartPos;	// �����X�^�[�g�ʒu
	D3DXVECTOR2		m_StreamGoalPos;	// �����S�[���ʒu
	D3DXVECTOR2		m_VecStreamMove;	// ���������̃x�N�g��
	float			m_StremCos;			// �v�Z�p
	float			m_StreamRad;		// �v�Z�p
	D3DXVECTOR2		m_MoveSpped;		// �����X�s�[�h�x�N�g��

	cSpriteParam	m_MeteorLight;		// ���̕\��



	//


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
	void OnCollidToNetArea(int num);
	void SetStream(bool a ,int num){
		m_pStarData = m_pRoot;
		m_pStarData += num;

		m_pStarData->m_bStream = a;
	}

	void Create();		// ����
	void Destroy();		// �폜
	void Respawn();		// ���X�|�[��

	void SetFeverStar(){

		// ������
		PlaySound(SOUND_LABEL_SE_STREAM_METEOR);

		m_bFever = true;

		m_pStarData = m_pRoot;

		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

			if (m_pStarData->m_bUse)
				continue;

			m_pStarData->m_bCreateEvent = true;
		}
		
	}

	void SetFeverEnd(){
		m_bFever = false;
	}


private:
	cRyuseiData*	m_pStarData;		// �K�v�f�[�^
	cRyuseiData*	m_pRoot;			// �擪�A�h���X�i�[�p
	cNet*			m_pNetData;			// �Ԃ̃f�[�^�i�[

	bool			m_bFever;



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