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
#include "Texture.h"


//----------------------------
// �萔�E�}�N����`
//----------------------------
#define WHITE_TEX_NAME		"Image/GameUI/white.png"	//���e�N�X�`��

//�w�i�J���[
#define START_COLOR			(D3DXCOLOR(255.0f, 199.0f, 199.0f, 255.0f))
#define START_CHANGE_COL	(3)	//R1 G2 B3
#define START_UNDER_COL		(199.0f)
#define COLOR_CHANGE_SPEED	(1.0f)                                                                         

//====================================
//
// �R���X�g���N�^
//
//====================================
cGameUI::cGameUI(){

	//----- �x�[�X�A�C�e���̏����� ------
	for (int i = 0; i < 4; i++){
		m_baseSprite[i].LoadTexture(WHITE_TEX_NAME);
		m_baseSprite[i].SetVtxColor(START_COLOR);
	}
	m_baseSprite[0].SetSize(D3DXVECTOR2(SCREEN_WIDTH / UI_WIDTH_DIVIDE, SCREEN_HEIGHT));
	m_baseSprite[0].SetPos(D3DXVECTOR2(m_baseSprite[0].GetSizeX() / 2.0f, m_baseSprite[0].GetSizeY() / 2.0f));
	m_baseSprite[1].SetSize(D3DXVECTOR2(SCREEN_WIDTH / UI_WIDTH_DIVIDE * (UI_WIDTH_DIVIDE - 1.0f), SCREEN_HEIGHT / UI_HEIGHT_DIVIDE));
	m_baseSprite[1].SetPos(D3DXVECTOR2(m_baseSprite[1].GetSizeX() / 2.0f + m_baseSprite[0].GetSizeX(), m_baseSprite[1].GetSizeY() / 2.0f));
	m_baseSprite[2].SetSize(m_baseSprite[1].GetSize());
	m_baseSprite[2].SetPos(D3DXVECTOR2(m_baseSprite[1].GetSizeX() / 2.0f + m_baseSprite[0].GetSizeX(), SCREEN_HEIGHT - m_baseSprite[1].GetSizeY() / 2.0f));
	m_baseSprite[3].SetSize(D3DXVECTOR2(m_baseSprite[1].GetSizeY(), SCREEN_HEIGHT));
	m_baseSprite[3].SetPos(D3DXVECTOR2(SCREEN_WIDTH - m_baseSprite[3].GetSizeX() / 2.0f, SCREEN_HEIGHT / 2.0f));

	//----- �ϐ��̏����� ------
	m_nChangeColorBaseUI = START_CHANGE_COL;
	m_fDirectColorBaseUI = COLOR_CHANGE_SPEED;

	for (int i = 0; i < MAX_BASEUI_ITEM; i++){
		m_aItem[i] = NULL;
	}

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

	//----- �x�[�XUI�̐F��ύX ------
	ChangeColorBaseUI();

	//----- �A�C�e���̊Ǘ� ------
	UpdateItem();

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

	/*for (int i = 0; i < MAX_BASEUI_ITEM; i++){
		if (m_aItem[i])
			m_aItem[i]->Draw();
	}*/

}

//===========================================
//
// �w�i�F��ς���
//
//===========================================
void cGameUI::ChangeColorBaseUI(){

	// �ϐ��錾
	float work;

	//----- �F�̕ύX ------
	for (int i = 0; i < 4; i++){
		switch (m_nChangeColorBaseUI)
		{
		case 1:
			m_baseSprite[i].SetVtxColorR(m_baseSprite[i].GetVtxColorR() + m_fDirectColorBaseUI);
			work = m_baseSprite[i].GetVtxColorR();
			break;
		case 2:
			m_baseSprite[i].SetVtxColorG(m_baseSprite[i].GetVtxColorG() + m_fDirectColorBaseUI);
			work = m_baseSprite[i].GetVtxColorG();
			break;
		case 3:
			m_baseSprite[i].SetVtxColorB(m_baseSprite[i].GetVtxColorB() + m_fDirectColorBaseUI);
			work = m_baseSprite[i].GetVtxColorB();
			break;
		}
	}

	//----- �I�������玟�̐F�� -------
	if ((work >= 255.0f && m_fDirectColorBaseUI > 0) ||
		(work <= START_UNDER_COL && m_fDirectColorBaseUI < 0)){

		//�`�F���W����F��ύX
		m_nChangeColorBaseUI++;
		if (m_nChangeColorBaseUI > 3)
			m_nChangeColorBaseUI = 1;

		//�F�̕�����I��
		switch (m_nChangeColorBaseUI)
		{
		case 1:
			if (m_baseSprite[0].GetVtxColorR() == START_UNDER_COL)
				m_fDirectColorBaseUI = COLOR_CHANGE_SPEED;
			else
				m_fDirectColorBaseUI = -COLOR_CHANGE_SPEED;
			break;
		case 2:
			if (m_baseSprite[0].GetVtxColorG() == START_UNDER_COL)
				m_fDirectColorBaseUI = COLOR_CHANGE_SPEED;
			else
				m_fDirectColorBaseUI = -COLOR_CHANGE_SPEED;
			break;
		case 3:
			if (m_baseSprite[0].GetVtxColorB() == START_UNDER_COL)
				m_fDirectColorBaseUI = COLOR_CHANGE_SPEED;
			else
				m_fDirectColorBaseUI = -COLOR_CHANGE_SPEED;
			break;
		}

	}

}


//===========================================
//
// �A�C�e���̊Ǘ�
//
//===========================================
void cGameUI::UpdateItem(){

	for (int i = 0; i < MAX_BASEUI_ITEM; i++){

		//--------- �V�K�A�C�e�����쐬 -----------
		if (!m_aItem[i]){
		
		}

		//--------- ���łɂ���A�C�e�����X�V --------
		else{

		}

	}
}



//================================================================================================
//
//    UI Item
//
//================================================================================================
cUIItem::cUIItem(ITEM_TYPE Tex, D3DXVECTOR2 pos, float size, D3DXCOLOR col, float speed){

	//------- �ϐ��̏����� ---------
	m_bFin = false;

	//------- �e�N�X�`���̐ݒ� ---------
	m_sprite.SetTexture(cTextureManeger::GetTextureGame((TEX_GAME)(TEX_GAME::TEX_KIRA_CIRCLE1 + Tex)));
	
	//------- �|�W�V�����ƃT�C�Y --------
	m_sprite.SetPos(pos);
	m_sprite.SetSize(D3DXVECTOR2(size, size));

	//------- �F --------
	m_sprite.SetVtxColor(col);

	//------- �X�s�[�h --------
	m_fSpeed = speed;

}