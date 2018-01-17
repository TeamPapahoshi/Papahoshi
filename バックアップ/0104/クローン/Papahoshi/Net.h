//=============================================================================
//  Net.h
//
//  ����F�㓡 ����
//  �T�v�F�Ԃ̏���
//=============================================================================
#ifndef _NET_H_
#define _NET_H_

//----------------------------------------
// �C���N���[�h��
//----------------------------------------
#include "Common.h"
#include "Sprite.h"

//----------------------------------------
// �񋓌^�錾
//----------------------------------------
enum{
	NET_PARTS_TOP,
	NET_PARTS_UNDER,
	NET_PARTS_RIGHT,
	NET_PARTS_LEFT,
	NET_PARTS_MAX,
};


//----------------------------------------
// �萔�E�}�N����`
//----------------------------------------
#define NET_X_NUM	(5)
#define NET_Y_NUM	(5)

//----------------------------------------
// �N���X��`
//----------------------------------------
class cNet{

public:
	cNet();
	~cNet();

	void Update();	// �X�V
	void Draw();	// �`��

private:
	cSpriteParam m_aNet[NET_PARTS_MAX][NET_Y_NUM][NET_X_NUM];
	cSpriteParam m_aFourUki[4];	//�l���_
	cSpriteParam m_center;		//���S�_
	D3DXVECTOR2 m_aPos[4];	//�l���_
	D3DXVECTOR2 m_centerPos;	//���S�_

	void SetNet();	//�e���_�ɍ��킹�Ă��݂�\��

};

#endif
