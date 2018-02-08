//======================================================================
//	RyuseiLine
//
//	�T�v�Q�F�����̋O��
//	����ҁF�����@��
//
//======================================================================
#ifndef ___RYUSEI_LINE_H___
#define ___RYUSEI_LINE_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Common.h"


//-----------------------------
//�}�N����`
//-----------------------------


//-----------------------------
//�񋓌^��`
//-----------------------------
typedef struct _tRyuseiLine{
	cSpriteParam	t_sprite;
	bool			t_bUse;
	float			t_LifeTime;
}tRyuseiLine;

//-----------------------------
//�N���X��`
//-----------------------------
class cRyuseiLine
{
public:
	cRyuseiLine();	//�R���X�g���N�^
	~cRyuseiLine();	//�f�X�g���N�^
	void Update(D3DXVECTOR2 pos);
	void Draw(void);
private:	
	tRyuseiLine*	m_pRyuseiLine;
	tRyuseiLine*	m_pRoot;


	tRyuseiLine*	m_pRyuseiLineOut;
	tRyuseiLine*	m_pRootOut;

	

};

#endif	//!___RYUSEI_LINE_H___