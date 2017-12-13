//=============================================================================
//  Net.cpp
//
//  制作：後藤 愛生
//  概要：網の処理
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

//-------------------------------------
// 定数・マクロ定義
//-------------------------------------
#define UKI_SIZE (20.0f)

//=====================================================
//
//  網のコンストラクタ
//
//=====================================================
cNet::cNet(){

	//四頂点の初期化
	m_aPos[0].x = 100.0f;
	m_aPos[0].y = 100.0f;
	m_aPos[1].x = 400.0f;
	m_aPos[1].y = 100.0f;
	m_aPos[2].x = 100.0f;
	m_aPos[2].y = 400.0f;
	m_aPos[3].x = 400.0f;
	m_aPos[3].y = 400.0f;

	//中心点の初期化
	m_centerPos = D3DXVECTOR2(250.0f, 250.0f);

	//スプライトの初期化
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
				m_aNet[z][y][x].SetTexture(cTextureManager::GetTextureTitle(TEX_NET));	// テクスチャのセット
			}
		}
	}
	for (int i = 0; i < 4; i++){
		m_aFourUki[i].SetTexture(cTextureManager::GetTextureTitle(TEX_UKI));
		m_aFourUki[i].SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));
	}
	m_center.SetTexture(cTextureManager::GetTextureTitle(TEX_UKI));
	m_center.SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));

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

}


//====================================================
//
// 各頂点に合わせてあみを貼る
//
//====================================================
void cNet::SetNet(){

	D3DXVECTOR2 workPos[4];
	float tlx, ulx, trx, urx, tdisX, udisX, ry, ly, ydis;
	tlx = ulx = m_aPos[0].x;
	trx = urx = m_aPos[1].x;
	tdisX = udisX = trx - tlx;
	ly = m_aPos[0].y;
	ry = m_aPos[1].y;
	ydis = ry - ly;

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
				case 0://TOP
					//Xの調整
					if (x == 0){
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						urx = m_aPos[1].x - ((((m_aPos[1].x - m_aPos[0].x) / NET_Y_NUM) * (y + 1)) / 2.0f);
						ulx = m_aPos[0].x + ((((m_aPos[1].x - m_aPos[0].x) / NET_Y_NUM) * (y + 1)) / 2.0f);
						udisX = urx - ulx;

						//Yの調整
						ly = m_aPos[0].y + ((((m_aPos[1].y - m_aPos[0].x) / NET_X_NUM) * (x + 1)) / 2.0f);
						ry = m_aPos[1].y + ((((m_aPos[1].y - m_aPos[0].x) / NET_X_NUM) * (x + 1)) / 2.0f);
					}

					//座標の設定
					workPos[0].x = tlx + ((tdisX / NET_X_NUM) * x);
					workPos[1].x = tlx + ((tdisX / NET_X_NUM) * (x + 1));
					workPos[2].x = ulx + ((udisX / NET_X_NUM) * x);
					workPos[3].x = ulx + ((udisX / NET_X_NUM) * (x + 1));

					workPos[0].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * y;
					workPos[1].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * y;
					workPos[2].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * (y + 1);
					workPos[3].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * (y + 1);
					break;
				case 1://UNDER
					//Xの調整
					if (x == 0){
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						urx = m_aPos[2].x - ((((m_aPos[3].x - m_aPos[2].x) / NET_Y_NUM) * (y + 1)) / 2.0f);
						ulx = m_aPos[3].x + ((((m_aPos[3].x - m_aPos[2].x) / NET_Y_NUM) * (y + 1)) / 2.0f);
						udisX = urx - ulx;

						//Yの調整
						ly = m_aPos[2].y + ((((m_aPos[3].y - m_aPos[2].x) / NET_X_NUM) * (x + 1)) / 2.0f);
						ry = m_aPos[3].y + ((((m_aPos[3].y - m_aPos[2].x) / NET_X_NUM) * (x + 1)) / 2.0f);
					}

					//座標の設定
					workPos[0].x = tlx + ((tdisX / NET_X_NUM) * x);
					workPos[1].x = tlx + ((tdisX / NET_X_NUM) * (x + 1));
					workPos[2].x = ulx + ((udisX / NET_X_NUM) * x);
					workPos[3].x = ulx + ((udisX / NET_X_NUM) * (x + 1));

					workPos[0].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * y;
					workPos[1].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * y;
					workPos[2].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * (y + 1);
					workPos[3].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * (y + 1);
					break;
				case 2://RIGHT
					break;
				case 3://LEFT
					break;
				}

				//あみのポジション決定
				m_aNet[z][y][x].SetPosFree(workPos[0], workPos[1], workPos[2], workPos[3]);
			}
		}
	}

}