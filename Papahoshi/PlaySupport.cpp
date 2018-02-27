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
void cPlaySupport::Update(cNet::GAME_PHASE phase, bool allPress, int rever){

	switch (phase)
	{
	case cNet::PHASE_POST:
		if (!allPress){
			m_messageSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_SUPPORT_1));
			m_messageSprite.SetScale(D3DXVECTOR2(0.7f, 0.7f));
			m_messageSprite.SetPos(D3DXVECTOR2(295.0f, 410.0f));
		}
		else{
			if (rever == 5){
				m_messageSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_SUPPORT_2));
				m_messageSprite.SetScale(D3DXVECTOR2(0.6f, 0.6f));
				m_messageSprite.SetPos(D3DXVECTOR2(270.0f, 410.0f));
			}
			else if (rever <= 3){
				m_messageSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_SUPPORT_3));
				m_messageSprite.SetScale(D3DXVECTOR2(0.53f, 0.53f));
				m_messageSprite.SetPos(D3DXVECTOR2(253.0f, 390.0f));
			}
		}
		break;
	case cNet::PHASE_SHOUT:
		m_messageSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_SUPPORT_4));
		m_messageSprite.SetScale(D3DXVECTOR2(0.57f, 0.57f));
		m_messageSprite.SetPos(D3DXVECTOR2(266.0f, 405.0f));
		break;
	case cNet::PHASE_PULL:
		break;
	}

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