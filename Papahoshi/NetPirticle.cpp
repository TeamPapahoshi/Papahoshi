//=================================================
//
//  Papahoshi  NetPirticle.cpp
//
//  Mei Goto.
//
//  網投げ時のパーティクル
//
//=================================================


//------------------------
// インクルード部
//------------------------
#include "NetPirticle.h"
#include "Texture.h"
#include "rand.h"

//-----------------------
// define 
//-----------------------
#define DECREMENT_SIZE_SPEED	(2.0f)
#define ROT_SPEED				(D3DX_PI * 0.05f)

//乱数
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
// コンストラクタ
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
// デストラクタ
//
//========================================
cNetPirticle::~cNetPirticle(){

}

//========================================
//
// 更新関数
//
//========================================
void cNetPirticle::Update(){

	//---- サイズの調整 ------
	m_sprite.SetSizeX(m_sprite.GetSizeX() - DECREMENT_SIZE_SPEED);
	m_sprite.SetSizeY(m_sprite.GetSizeY() - DECREMENT_SIZE_SPEED);

	//---- 終了 ------
	if (m_sprite.GetSizeX() <= 0.0f){
		m_finFlug = true;
		return;
	}

	//--- 移動 ----
	m_sprite.SetPosX(m_sprite.GetPosX() + m_moveSpeed.x);
	m_sprite.SetPosY(m_sprite.GetPosY() + m_moveSpeed.y);

	//---- 回転 ----
	m_sprite.SetRad(m_sprite.GetRad() + ROT_SPEED);

	//上限処理
	if (m_sprite.GetRad() >= 2 * D3DX_PI){
		m_sprite.SetRad(m_sprite.GetRad() - (2 * D3DX_PI));
	}
}

//========================================
//
// 描画関数
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
// コンストラクタ
//
//========================================
cNetPirticleManage::cNetPirticleManage(D3DXVECTOR2 pos){

	D3DXVECTOR2 move, size;
	D3DXCOLOR color;

	//乱数の初期化
	CRandam::InitRand();

	//生成
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){

		//サイズ
		size.x = (float)CRandam::RandamRenge(MIN_SIZE, MAX_SIZE) / 100.0f;
		size.y = size.x;

		//ムーブ
		move.x = (float)CRandam::RandamRenge(MIN_MOVE, MAX_MOVE) / 100.0f;
		move.y = (float)CRandam::RandamRenge(MIN_MOVE, MAX_MOVE) / 100.0f;
		if (CRandam::RandProb(50))
			move.x *= -1.0f;
		if (CRandam::RandProb(50))
			move.y *= -1.0f;

		//色
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

		//生成
		m_aPirticle[i] = new cNetPirticle(pos, move, color, size);
		
	}

	//変数の初期化
	m_finFlug = false;

}

//========================================
//
// デストラクタ
//
//========================================
cNetPirticleManage::~cNetPirticleManage(){

}

//========================================
//
// 更新関数
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

	//終了
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){
		if (m_aPirticle[i])
			return;
	}

	m_finFlug = true;
}

//========================================
//
// 描画関数
//
//========================================
void cNetPirticleManage::Draw(){
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){
		if (m_aPirticle[i])
			m_aPirticle[i]->Draw();
	}
}