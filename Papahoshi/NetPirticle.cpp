//=================================================
//
//  Papahoshi  NetPirticle.cpp
//
//  Mei Goto.
//
//  �ԓ������̃p�[�e�B�N��
//
//=================================================


//------------------------
// �C���N���[�h��
//------------------------
#include "NetPirticle.h"
#include "Texture.h"
#include "rand.h"

//-----------------------
// define 
//-----------------------
#define DECREMENT_SIZE_SPEED	(2.0f)
#define ROT_SPEED				(D3DX_PI * 0.05f)

//����
#define MAX_MOVE	(1000)	//50.0f
#define MIN_MOVE	(100)	//10.0f

#define MAX_SIZE	(10000)
#define MIN_SIZE	(5000)

#define MAX_COLOR	(255)
#define MIN_COLOR	(199)

//============================================================================================
//
// cNetPirticle Class
//
//============================================================================================

//========================================
//
// �R���X�g���N�^
//
//========================================
cNetPirticle::cNetPirticle(D3DXVECTOR2 pos, D3DXVECTOR2 move, D3DXCOLOR color, D3DXVECTOR2 size){

	m_sprite.SetPos(pos);
	m_sprite.SetVtxColor(color);
	m_sprite.SetSize(size);
	m_moveSpeed = move;

	m_finFlug = false;
	m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_NET_PIRTICLE));
}

//========================================
//
// �f�X�g���N�^
//
//========================================
cNetPirticle::~cNetPirticle(){

}

//========================================
//
// �X�V�֐�
//
//========================================
void cNetPirticle::Update(){

	//---- �T�C�Y�̒��� ------
	m_sprite.SetSizeX(m_sprite.GetSizeX() - DECREMENT_SIZE_SPEED);
	m_sprite.SetSizeY(m_sprite.GetSizeY() - DECREMENT_SIZE_SPEED);

	//---- �I�� ------
	if (m_sprite.GetSizeX() <= 0.0f){
		m_finFlug = true;
		return;
	}

	//--- �ړ� ----
	m_sprite.SetPosX(m_sprite.GetPosX() + m_moveSpeed.x);
	m_sprite.SetPosY(m_sprite.GetPosY() + m_moveSpeed.y);

	//---- ��] ----
	m_sprite.SetRad(m_sprite.GetRad() + ROT_SPEED);

	//�������
	if (m_sprite.GetRad() >= 2 * D3DX_PI){
		m_sprite.SetRad(m_sprite.GetRad() - (2 * D3DX_PI));
	}
}

//========================================
//
// �`��֐�
//
//========================================
void cNetPirticle::Draw(){
	m_sprite.Draw();
}


//===========================================================================================
//
// cNetPirticleManage Class
//
//===========================================================================================

//========================================
//
// �R���X�g���N�^
//
//========================================
cNetPirticleManage::cNetPirticleManage(D3DXVECTOR2 pos){

	D3DXVECTOR2 move, size;
	D3DXCOLOR color;

	//�����̏�����
	CRandam::InitRand();

	//����
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){

		//�T�C�Y
		size.x = (float)CRandam::RandamRenge(MIN_SIZE, MAX_SIZE) / 100.0f;
		size.y = size.x;

		//���[�u
		move.x = (float)CRandam::RandamRenge(MIN_MOVE, MAX_MOVE) / 100.0f;
		move.y = (float)CRandam::RandamRenge(MIN_MOVE, MAX_MOVE) / 100.0f;
		if (CRandam::RandProb(50))
			move.x *= -1.0f;
		if (CRandam::RandProb(50))
			move.y *= -1.0f;

		//�F
		color = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		switch (CRandam::RandamRenge(1,3))
		{
		case 1:
			color.g = (float)CRandam::RandamRenge(MIN_COLOR, MAX_COLOR);
			break;
		case 2:
			color.r = (float)CRandam::RandamRenge(MIN_COLOR, MAX_COLOR);
			break;
		case 3:
			color.b = (float)CRandam::RandamRenge(MIN_COLOR, MAX_COLOR);
			break;
		}

		//����
		m_aPirticle[i] = new cNetPirticle(pos, move, color, size);
		
	}

	//�ϐ��̏�����
	m_finFlug = false;

}

//========================================
//
// �f�X�g���N�^
//
//========================================
cNetPirticleManage::~cNetPirticleManage(){

}

//========================================
//
// �X�V�֐�
//
//========================================
void cNetPirticleManage::Update(){
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){
		if (!m_aPirticle[i])
			continue;

		m_aPirticle[i]->Update();

		if (m_aPirticle[i]->GetFinFlug()){
			delete m_aPirticle[i];
			m_aPirticle[i] = NULL;
		}

	}

	//�I��
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){
		if (m_aPirticle[i])
			return;
	}

	m_finFlug = true;
}

//========================================
//
// �`��֐�
//
//========================================
void cNetPirticleManage::Draw(){
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){
		if (m_aPirticle[i])
			m_aPirticle[i]->Draw();
	}
}