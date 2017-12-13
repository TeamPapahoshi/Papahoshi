//=============================================================================
//  Net.cpp
//
//  制作：後藤 愛生
//  概要：網の処理
//
//	****** 素材プッシュしましたか！？！？！？ ******
//
//=============================================================================
/*
・あみのはりかたの調整　12/15
　centerとの距離で図る。
 ・まっすぐ飛ばせて指を離したら頂点広がる　12/18
 */


//-------------------------------------
// インクルード部
//-------------------------------------
#include "Net.h"
#include "Texture.h"
#include "SceneGame.h"

//-------------------------------------
// 定数・マクロ定義
//-------------------------------------
#define UKI_SIZE (20.0f)	//うきのサイズ
#define ARROW_SIZE_X (300.0f)	//矢印のサイズ
#define ARROW_SIZE_Y (120.0f)

//=====================================================
//
//  網のコンストラクタ
//
//=====================================================
cNet::cNet() :
//---- イニシャライザ ----
gamePhase(PHASE_POST){

	//---- 四頂点の初期化 ----
	m_aPos[0].x = 100.0f;
	m_aPos[0].y = 180.0f;
	m_aPos[1].x = 400.0f;
	m_aPos[1].y = 100.0f;
	m_aPos[2].x = 100.0f;
	m_aPos[2].y = 400.0f;
	m_aPos[3].x = 400.0f;
	m_aPos[3].y = 400.0f;

	//---- 中心点の初期化 ----
	m_centerPos = D3DXVECTOR2(250.0f, 250.0f);

	//---- スプライトの初期化 ----

	//あみ
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
				m_aNet[z][y][x].SetTexture(cTextureManager::GetTextureGame(cTextureManager::TEX_GAME_NET));	// テクスチャのセット
			}
		}
	}

	//うき・四頂点
	for (int i = 0; i < 4; i++){
		m_aFourUki[i].SetTexture(cTextureManager::GetTextureGame(cTextureManager::TEX_GAME_UKI));
		m_aFourUki[i].SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));
	}

	//うき・センター
	m_center.SetTexture(cTextureManager::GetTextureGame(cTextureManager::TEX_GAME_UKI));
	m_center.SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));

	//矢印
	m_arrow.SetTexture(cTextureManager::GetTextureGame(cTextureManager::TEX_GAME_ARROW));
	m_arrow.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 80.0f));
	m_arrow.SetSize(D3DXVECTOR2(ARROW_SIZE_X, ARROW_SIZE_Y));
	m_arrow.SetRad(D3DX_PI);

}


//=====================================================
//
// 網のデストラクタ
//
//=====================================================
cNet::~cNet(){



}


//=====================================================
//
// 網の更新
//
//=====================================================
void cNet::Update(){

	//ゲームフェイズごとの更新
	switch (gamePhase)
	{
	case PHASE_POST:	//構え
		PostPhaseUpdate();
		break;
	case PHASE_SHOUT:	//投げ
		ShoutPhaseUpdate();
		break;
	case PHASE_PULL:	//引く
		PullPhaseUpdate();
		break;
	}

	//頂点情報に合わせてあみをはる
	SetNet();

}

//=====================================================
//
// 網の描画
//
//=====================================================
void cNet::Draw(){

	//あみ
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
				m_aNet[z][y][x].DrawFreePos();
			}
		}
	}

	//うき
	for (int i = 0; i < 4; i++){
		m_aFourUki[i].Draw();
	}

	//中心点
	m_center.Draw();

	//矢印(構え状態の時)
	m_arrow.Draw();

}


//====================================================
//
// 各頂点に合わせてあみを貼る
//
//====================================================
void cNet::SetNet(){

	D3DXVECTOR2 workPos[4];
	float tlx, ulx, trx, urx, tdisX, udisX, trY, tly, ury, uly, tdisY, udisY, yAng, xAng;
	tlx = ulx = m_aPos[0].x;
	trx = urx = m_aPos[1].x;
	tdisX = udisX = trx - tlx;
	tly = uly = m_aPos[0].y;
	trY = ury = m_aPos[1].y;
	trY >= tly ? tdisY = udisY = trY - tly : tdisY = udisY = tly - trY;
	trY >= tly ? yAng = 1.0f : yAng = 0.0f;

	//---- ウキの位置を設定 ----
	for (int i = 0; i < 4; i++){
		m_aFourUki[i].SetPos(m_aPos[i]);
	}
	m_center.SetPos(m_centerPos);

	//** TOP以外未反映 **//
	//----- あみのポジションを設定(とりあえず直線に) -----
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){

				switch (z)
				{
				case NET_PARTS_TOP://TOP
					//Xの調整
					if (x == 0){
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						urx = m_aPos[1].x - ((((m_aPos[1].x - m_aPos[0].x) / NET_Y_NUM) * (y + 1)) / 2.0f);
						ulx = m_aPos[0].x + ((((m_aPos[1].x - m_aPos[0].x) / NET_Y_NUM) * (y + 1)) / 2.0f);
						udisX = urx - ulx;

						//Yの調整
						tly = uly;
						trY = ury;
						tdisY = udisY;
						uly = m_aPos[0].y + ((((m_centerPos.y - m_aPos[0].y) / NET_Y_NUM) * (y + 1)));
						ury = m_aPos[1].y + ((((m_centerPos.y - m_aPos[1].y) / NET_Y_NUM) * (y + 1)));
						ury >= uly ? udisY = ury - uly : udisY = uly - ury;
						if (y == 0)
							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
					}

					//座標の設定
					workPos[0].x = tlx + ((tdisX / NET_X_NUM) * x);
					workPos[1].x = tlx + ((tdisX / NET_X_NUM) * (x + 1));
					workPos[2].x = ulx + ((udisX / NET_X_NUM) * x);
					workPos[3].x = ulx + ((udisX / NET_X_NUM) * (x + 1));

					if (yAng){	//みぎのほうが下にある
						workPos[0].y = tly + (tdisY / NET_X_NUM) * (x);
						workPos[1].y = tly + (tdisY / NET_X_NUM) * (x + 1);
						workPos[2].y = uly + (udisY / NET_X_NUM) * (x);
						workPos[3].y = uly + (udisY / NET_X_NUM) * (x + 1);
					}
					else{
						workPos[0].y = tly - (tdisY / NET_X_NUM) * (x);
						workPos[1].y = tly - (tdisY / NET_X_NUM) * (x + 1);
						workPos[2].y = uly - (udisY / NET_X_NUM) * (x);
						workPos[3].y = uly - (udisY / NET_X_NUM) * (x + 1);
					}
					break;
				case NET_PARTS_UNDER://UNDER
					break;
				case NET_PARTS_RIGHT://RIGHT
					break;
				case NET_PARTS_LEFT://LEFT
					break;
				}

				//あみのポジション決定
				m_aNet[z][y][x].SetPosFree(workPos[0], workPos[1], workPos[2], workPos[3]);
			}
		}
	}

}


//====================================================
//
// 『構え』中の更新
//
//====================================================
void cNet::PostPhaseUpdate(){



}


//====================================================
//
// 『投げる』中の更新
//
//====================================================
void cNet::ShoutPhaseUpdate(){



}


//====================================================
//
// 『引く』中の更新
//
//====================================================
void cNet::PullPhaseUpdate(){



}


