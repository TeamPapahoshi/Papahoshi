//=====================================================
//
//  Papahoshi  GameUI.cpp
//
//  Mei Goto.
//
//=====================================================


//----------------------------
// �C���N���[�h��
//----------------------------
#include "GameUI.h"


//----------------------------
// �萔�E�}�N����`
//----------------------------
#define WHITE_TEX_NAME		"Image/GameUI/white.png"	//���e�N�X�`��
#define UI_WIDTH_DIVIDE		(4.0f)
#define UI_HEIGHT_DIVIDE	(50.0f)
                                                                                                              

//====================================
//
// �R���X�g���N�^
//
//====================================
cGameUI::cGameUI(){

	//----- �x�[�X�A�C�e���̏����� ------
	for (int i = 0; i < 4; i++){
		m_baseSprite[i].LoadTexture(WHITE_TEX_NAME);
	}
	m_baseSprite[0].SetSize(D3DXVECTOR2(SCREEN_WIDTH / UI_WIDTH_DIVIDE, SCREEN_HEIGHT));
	m_baseSprite[0].SetPos(D3DXVECTOR2(m_baseSprite[0].GetSizeX() / 2.0f, m_baseSprite[0].GetSizeY() / 2.0f));
	m_baseSprite[1].SetSize(D3DXVECTOR2(SCREEN_WIDTH / UI_WIDTH_DIVIDE * (UI_WIDTH_DIVIDE - 1.0f), SCREEN_HEIGHT / UI_HEIGHT_DIVIDE));
	m_baseSprite[1].SetPos(D3DXVECTOR2(m_baseSprite[1].GetSizeX() / 2.0f + m_baseSprite[0].GetSizeX(), m_baseSprite[1].GetSizeY() / 2.0f));
	m_baseSprite[2].SetSize(m_baseSprite[1].GetSize());
	m_baseSprite[2].SetPos(D3DXVECTOR2(m_baseSprite[1].GetSizeX() / 2.0f + m_baseSprite[0].GetSizeX(), SCREEN_HEIGHT - m_baseSprite[1].GetSizeY() / 2.0f));
	m_baseSprite[3].SetSize(D3DXVECTOR2(m_baseSprite[1].GetSizeY(), SCREEN_HEIGHT));
	m_baseSprite[3].SetPos(D3DXVECTOR2(SCREEN_WIDTH - m_baseSprite[3].GetSizeX() / 2.0f, SCREEN_HEIGHT / 2.0f));

}

//====================================
//
// �f�X�g���N�^
//
//====================================
cGameUI::~cGameUI(){



}


//====================================
//
// �X�V�֐�
//
//====================================
void cGameUI::Update(){



}

//====================================
//
// �`��֐�
//
//====================================
void cGameUI::Draw(){

	for (int i = 0; i < 4; i++){
		m_baseSprite[i].Draw();
	}

}

