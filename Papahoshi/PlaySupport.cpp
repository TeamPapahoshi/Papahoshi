//============================================
//
// Papahoshi  PlaySupport.cpp
//
// Mei Goto.
//
//============================================

//-----------------------
// �C���N���[�h��
//-----------------------
#include "PlaySupport.h"
#include "Texture.h"

//-----------------------
// define 
//-----------------------



//==========================================================
//
// �R���X�g���N�^
//
//==========================================================
cPlaySupport::cPlaySupport(){

	//----- �ӂ����� -----
	m_fukidashiSprite.LoadTexture("Image/GameUI/fukidashi/fukidashi.png");
	m_fukidashiSprite.SetSize(D3DXVECTOR2(220.0f, 180.f));
	m_fukidashiSprite.SetPos(D3DXVECTOR2(230.0f, 360.0f));

	//----- ���b�Z�[�W -----
	m_messageSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_SUPPORT_1));
	m_messageSprite.SetSize(D3DXVECTOR2(450.0f, 319.f));
	m_messageSprite.SetScale(D3DXVECTOR2(0.7f, 0.7f));
	m_messageSprite.SetPos(D3DXVECTOR2(295.0f, 410.0f));
}

//=========================================================
//
// �f�X�g���N�^
//
//=========================================================
cPlaySupport::~cPlaySupport(){



}

//=========================================================
//
// �X�V�֐�
//
//=========================================================
void cPlaySupport::Update(){



}

//=========================================================
//
// �`��֐�
//
//=========================================================
void cPlaySupport::Draw(){
	
	//�����o��
	m_fukidashiSprite.Draw();

	//���b�Z�[�W
	m_messageSprite.Draw();

}