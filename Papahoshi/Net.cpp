//=============================================================================
//  Net.cpp
//
//  制作：後藤 愛生
//  概要：網の処理
//
//	****** 素材プッシュしましたか！？！？！？ ******
//
//  レバー入力方向はテンキーに見立てて格納（格闘ゲームの1Pコマンド表記）
//	789
//	456
//	123
//=============================================================================
/*
・あみのはりかたの調整　12/15  クリア！
・まっすぐ飛ばせて指を離したら頂点広がる　12/18

次やること
あみのアンダーのデバック
おそらくy関係に問題あり
*/


//-------------------------------------
// インクルード部
//-------------------------------------
#include "Net.h"
#include "Texture.h"
#include "SceneGame.h"
#include "Input.h"

#ifdef  _TYPE_1_

//-------------------------------------
// 定数・マクロ定義
//-------------------------------------
//使用ボタン
#define BOTTON_NET_UPLEFT		(AC_CON_BUTTON_A)
#define BOTTON_NET_UPRIGHT		(AC_CON_BUTTON_B)
#define BOTTON_NET_DOWNLEFT		(AC_CON_BUTTON_E)
#define BOTTON_NET_DOWNRIGHT	(AC_CON_BUTTON_F)
//テクスチャサイズ
#define UKI_SIZE (20.0f)	//うきのサイズ
#define ARROW_SIZE_X (300.0f)	//矢印のサイズ
#define ARROW_SIZE_Y (120.0f)
//スピード
#define MAX_SPEED	(10.0f)
#define DECRE_SPEED (0.1f)	//１フレームごとに初速減らす量
#define DECRE_THROW_SPEED	(0.1f)	//まさつ
//待ち時間
#define INTERVAL_THOROW_PULL	(90)	//投げから引き上げまでの待ち時間

//=====================================================
//
//  網のコンストラクタ
//
//=====================================================
cNet::cNet() :
//---- イニシャライザ ----
gamePhase(PHASE_POST),
m_bDrawArrow(false),
m_bAllPress(false),
m_nLeverDirection(5),	//ニュートラル
m_nFrameCnt(0),
m_postPhase(POST_NON),
m_fThrowSpeed(0.0f)
{

	//---- 中心点の初期化 ----
	m_centerPos = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT + 30.0f);

	//---- 四頂点の初期化 ----
	for (int i = 0; i < 4; i++)
		m_aPos[i] = m_centerPos;

	//---- スプライトの初期化 ----

	//あみ
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
				m_aNet[z][y][x].SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_NET));	// テクスチャのセット
			}
		}
	}

	//うき・四頂点
	for (int i = 0; i < 4; i++){
		m_aFourUki[i].SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_UKI));
		m_aFourUki[i].SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));
	}

	//うき・センター
	m_center.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_UKI));
	m_center.SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));

	//矢印
	m_arrow.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_ARROW));
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

	//入力を受付
	Input();

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
	if (m_bDrawArrow)
		m_arrow.Draw();

}


//====================================================
//
// 各頂点に合わせてあみを貼る
//
//====================================================
void cNet::SetNet(){

	D3DXVECTOR2 workPos[4];
	float tlx, ulx, trx, urx, tdisX, udisX, trY, tly, ury, uly, tdisY, udisY, yAng, xAng, LtoCdisX, CtoRdisX;


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
					//値の調整
					if (x == 0){
						//必要情報を計算
						if (y == 0){
							tlx = ulx = m_aPos[0].x;
							trx = urx = m_aPos[1].x;
							tdisX = udisX = trx - tlx;
							tly = uly = m_aPos[0].y;
							trY = ury = m_aPos[1].y;
							trY >= tly ? tdisY = udisY = trY - tly : tdisY = udisY = tly - trY;
							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.x - m_aPos[0].x;
							CtoRdisX = m_aPos[1].x - m_centerPos.x;
							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.x - m_aPos[0].x;
							CtoRdisX = m_aPos[1].x - m_centerPos.x;
						}

						//Xの調整
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						urx = m_aPos[1].x - ((((CtoRdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						ulx = m_aPos[0].x + ((((LtoCdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						udisX = urx - ulx;

						//Yの調整
						tly = uly;
						trY = ury;
						tdisY = udisY;
						uly = m_aPos[0].y + ((((m_centerPos.y - m_aPos[0].y) / NET_Y_NUM) * (y + 1)));
						ury = m_aPos[1].y + ((((m_centerPos.y - m_aPos[1].y) / NET_Y_NUM) * (y + 1)));
						ury >= uly ? udisY = ury - uly : udisY = uly - ury;
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
					//値の調整
					if (x == 0){
						//必要情報を計算
						if (y == 0){
							tlx = ulx = m_aPos[2].x;
							trx = urx = m_aPos[3].x;
							tdisX = udisX = trx - tlx;
							tly = uly = m_aPos[2].y;
							trY = ury = m_aPos[3].y;
							trY >= tly ? tdisY = udisY = trY - tly : tdisY = udisY = tly - trY;
							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.x - m_aPos[2].x;
							CtoRdisX = m_aPos[3].x - m_centerPos.x;

							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_aPos[2].x - m_centerPos.x;
							CtoRdisX = m_centerPos.x - m_aPos[3].x;
						}

						//Xの調整
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						urx = m_aPos[3].x + ((((CtoRdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						ulx = m_aPos[2].x - ((((LtoCdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						udisX = urx - ulx;

						//Yの調整
						tly = uly;
						trY = ury;
						tdisY = udisY;
						uly = m_aPos[2].y + ((((m_centerPos.y - m_aPos[2].y) / NET_Y_NUM) * (y + 1)));
						ury = m_aPos[3].y + ((((m_centerPos.y - m_aPos[3].y) / NET_Y_NUM) * (y + 1)));
						ury >= uly ? udisY = ury - uly : udisY = uly - ury;
					}

					//座標の設定
					workPos[2].x = tlx + ((tdisX / NET_X_NUM) * x);
					workPos[3].x = tlx + ((tdisX / NET_X_NUM) * (x + 1));
					workPos[0].x = ulx + ((udisX / NET_X_NUM) * x);
					workPos[1].x = ulx + ((udisX / NET_X_NUM) * (x + 1));

					if (yAng){	//みぎのほうが下にある
						workPos[2].y = tly + (tdisY / NET_X_NUM) * (x);
						workPos[3].y = tly + (tdisY / NET_X_NUM) * (x + 1);
						workPos[0].y = uly + (udisY / NET_X_NUM) * (x);
						workPos[1].y = uly + (udisY / NET_X_NUM) * (x + 1);
					}
					else{
						workPos[2].y = tly - (tdisY / NET_X_NUM) * (x);
						workPos[3].y = tly - (tdisY / NET_X_NUM) * (x + 1);
						workPos[0].y = uly - (udisY / NET_X_NUM) * (x);
						workPos[1].y = uly - (udisY / NET_X_NUM) * (x + 1);
					}
					break;
				case NET_PARTS_RIGHT://RIGHT
					//値の調整
					if (x == 0){
						//必要情報を計算
						if (y == 0){
							tlx = ulx = m_aPos[1].x;
							trx = urx = m_aPos[3].x;
							trx >= tlx ? tdisX = udisX = trx - tlx : tdisX = udisX = tlx - trx;
							tly = uly = m_aPos[1].y;
							trY = ury = m_aPos[3].y;
							tdisY = udisY = trY - tly;
							trx >= tlx ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.y - m_aPos[1].y;
							CtoRdisX = m_aPos[3].y - m_centerPos.y;
						}

						//Yの調整
						tly = uly;
						trY = ury;
						tdisY = udisY;
						ury = m_aPos[3].y - ((((CtoRdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						uly = m_aPos[1].y + ((((LtoCdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						udisY = ury - uly;

						//Xの調整
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						ulx = m_aPos[1].x + ((((m_centerPos.x - m_aPos[1].x) / NET_Y_NUM) * (y + 1)));
						urx = m_aPos[3].x + ((((m_centerPos.x - m_aPos[3].x) / NET_Y_NUM) * (y + 1)));
						urx >= ulx ? udisX = urx - ulx : udisX = ulx - urx;
					}

					//座標の設定
					workPos[1].y = tly + (tdisY / 6) * (x);
					workPos[3].y = tly + (tdisY / 6) * (x + 1);
					workPos[0].y = uly + (udisY / 6) * (x);
					workPos[2].y = uly + (udisY / 6) * (x + 1);

					if (yAng){	//みぎのほうが下にある
						workPos[1].x = tlx + (tdisX / 6) * (x);
						workPos[3].x = tlx + (tdisX / 6) * (x + 1);
						workPos[0].x = ulx + (udisX / 6) * (x);
						workPos[2].x = ulx + (udisX / 6) * (x + 1);
					}
					else{
						workPos[1].x = tlx - (tdisX / 6) * (x);
						workPos[3].x = tlx - (tdisX / 6) * (x + 1);
						workPos[0].x = ulx - (udisX / 6) * (x);
						workPos[2].x = ulx - (udisX / 6) * (x + 1);
					}
					break;
				case NET_PARTS_LEFT://LEFT
					//値の調整
					if (x == 0){
						//必要情報を計算
						if (y == 0){
							tlx = ulx = m_aPos[0].x;
							trx = urx = m_aPos[2].x;
							trx >= tlx ? tdisX = udisX = trx - tlx : tdisX = udisX = tlx - trx;
							tly = uly = m_aPos[0].y;
							trY = ury = m_aPos[2].y;
							tdisY = udisY = trY - tly;
							trx >= tlx ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.y - m_aPos[0].y;
							CtoRdisX = m_aPos[2].y - m_centerPos.y;
						}

						//Yの調整
						tly = uly;
						trY = ury;
						tdisY = udisY;
						ury = m_aPos[2].y - ((((CtoRdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						uly = m_aPos[0].y + ((((LtoCdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						udisY = ury - uly;

						//Xの調整
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						ulx = m_aPos[0].x + ((((m_centerPos.x - m_aPos[0].x) / NET_Y_NUM) * (y + 1)));
						urx = m_aPos[2].x + ((((m_centerPos.x - m_aPos[2].x) / NET_Y_NUM) * (y + 1)));
						urx >= ulx ? udisX = urx - ulx : udisX = ulx - urx;
					}

					//座標の設定
					workPos[0].y = tly + (tdisY / 6) * (x);
					workPos[2].y = tly + (tdisY / 6) * (x + 1);
					workPos[1].y = uly + (udisY / 6) * (x);
					workPos[3].y = uly + (udisY / 6) * (x + 1);

					if (yAng){	//みぎのほうが下にある
						workPos[0].x = tlx + (tdisX / 6) * (x);
						workPos[2].x = tlx + (tdisX / 6) * (x + 1);
						workPos[1].x = ulx + (udisX / 6) * (x);
						workPos[3].x = ulx + (udisX / 6) * (x + 1);
					}
					else{
						workPos[0].x = tlx - (tdisX / 6) * (x);
						workPos[2].x = tlx - (tdisX / 6) * (x + 1);
						workPos[1].x = ulx - (udisX / 6) * (x);
						workPos[3].x = ulx - (udisX / 6) * (x + 1);
					}
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
// 入力取得
//
//====================================================
void cNet::Input(){

	//---------------------------
	// レバー入力
	//---------------------------
	if (GetInputArrowPress(DIK_W, 0, PAD_ARROW_UP) && GetInputArrowPress(DIK_A, 0, PAD_ARROW_LEFT))
		m_nLeverDirection = 7;
	else if (GetInputArrowPress(DIK_W, 0, PAD_ARROW_UP) && GetInputArrowPress(DIK_D, 0, PAD_ARROW_RIGHT))
		m_nLeverDirection = 9;
	else if (GetInputArrowPress(DIK_S, 0, PAD_ARROW_DOWN) && GetInputArrowPress(DIK_D, 0, PAD_ARROW_RIGHT))
		m_nLeverDirection = 3;
	else if (GetInputArrowPress(DIK_S, 0, PAD_ARROW_DOWN) && GetInputArrowPress(DIK_A, 0, PAD_ARROW_LEFT))
		m_nLeverDirection = 1;
	else if (GetInputArrowPress(DIK_W, 0, PAD_ARROW_UP))
		m_nLeverDirection = 8;
	else if (GetInputArrowPress(DIK_A, 0, PAD_ARROW_LEFT))
		m_nLeverDirection = 4;
	else if (GetInputArrowPress(DIK_D, 0, PAD_ARROW_RIGHT))
		m_nLeverDirection = 6;
	else if (GetInputArrowPress(DIK_S, 0, PAD_ARROW_DOWN))
		m_nLeverDirection = 2;
	else
		m_nLeverDirection = 5;

	//----------------------------
	// ボタン入力
	//----------------------------
	if (GetInputButtonPress(DIK_N, 0, BOTTON_NET_DOWNLEFT))
		m_bPressButton[2] = true;
	else
		m_bPressButton[2] = false;
	if (GetInputButtonPress(DIK_U, 0, BOTTON_NET_UPLEFT))
		m_bPressButton[0] = true;
	else
		m_bPressButton[0] = false;
	if (GetInputButtonPress(DIK_8, 0, BOTTON_NET_UPRIGHT))
		m_bPressButton[1] = true;
	else
		m_bPressButton[1] = false;
	if (GetInputButtonPress(DIK_9, 0, BOTTON_NET_DOWNRIGHT))
		m_bPressButton[3] = true;
	else
		m_bPressButton[3] = false;

	//---- 全ボタンプッシュ状態かどうか ----
	for (int i = 0; i < 4; i++){
		if (!m_bPressButton[i])
			break;
		if (i == 3)
			m_bAllPress = true;
	}

}

//====================================================
//
// 『構え』中の更新
//
//====================================================
void cNet::PostPhaseUpdate(){

	//----- 全ボタンプレス中以外リターン -----
	if (!m_bAllPress){
		m_bDrawArrow = false;
		m_postPhase = POST_NON;
		return;
	}

	switch (m_postPhase)
	{
	//------ 何もしてないとき -----
	case POST_NON:
		//-----	レバーを引いて角度調整 -----
		if (m_nLeverDirection <= 3){

			//矢印の表示
			m_bDrawArrow = true;

			//角度の設定
			m_nPostAngle = m_nLeverDirection;

			//引き中を設定
			m_postPhase = POST_PULL;

		}

		//----- 矢印角度も調整 -----
		if (m_nPostAngle == 1){
			m_arrow.SetRad(D3DX_PI + (D3DX_PI / 4.0f));
		}
		else if (m_nPostAngle == 3){
			m_arrow.SetRad(D3DX_PI - (D3DX_PI / 4.0f));
		}
		else{
			m_arrow.SetRad(D3DX_PI);
		}
		break;
	//------- 引き中 ------
	case POST_PULL:
		//-----	レバーを引いて角度調整 -----
		if (m_nLeverDirection <= 3){

			//矢印の表示
			m_bDrawArrow = true;

			//角度の設定
			m_nPostAngle = m_nLeverDirection;
		}

		//----- 矢印角度も調整 -----
		if (m_nPostAngle == 1){
			m_arrow.SetRad(D3DX_PI + (D3DX_PI / 4.0f));
		}
		else if (m_nPostAngle == 3){
			m_arrow.SetRad(D3DX_PI - (D3DX_PI / 4.0f));
		}
		else{
			m_arrow.SetRad(D3DX_PI);
		}

		//----- レバーニュートラル状態のときに経過フレームを計測
		if (m_nLeverDirection < 7 && m_nLeverDirection > 3){
			m_nFrameCnt++;
			m_postPhase = POST_N;
		}

		break;
	//----- ニュートラル状態 -----
	case POST_N:
		//----- レバーニュートラル状態のときに経過フレームを計測 -----
		if (m_nLeverDirection < 7 && m_nLeverDirection > 3){
			m_nFrameCnt++;
		}

		//----- レバー前倒しでフェイズ移行 -----
		if (m_nLeverDirection > 6){
			m_postPhase = POST_PUSH;
		}

		break;
	//------- 前倒し状態 -------
	case POST_PUSH:

		//----- スピードを計算 -----
		m_fThrowSpeed = MAX_SPEED - (DECRE_SPEED * m_nFrameCnt);
		if (m_fThrowSpeed < 0.0f)
			m_fThrowSpeed = 0.0f;

		//----- 構え状態終了 -----
		gamePhase = PHASE_SHOUT;
		m_bDrawArrow = false;
		m_nFrameCnt = 0;		//フレームカウントの初期化
		for (int i = 0; i < 4; i++)
			m_bThrow[i] = false;
		break;
	}

}


//====================================================
//
// 『投げる』中の更新
//
//====================================================
void cNet::ShoutPhaseUpdate(){

	//------ 中心点を飛ばす ------
	m_centerPos.y -= m_fThrowSpeed;
	//ななめにとばすならXも

	//------ ボタン離したかチェック ------
	for (int i = 0; i < 4; i++){
		if (!m_bPressButton[i] && !m_bThrow[i]){
			m_bThrow[i] = true;
		}
	}

	//----- 各四頂点の処理 ------
	for (int i = 0; i < 4; i++){

		//------ ボタン離していない頂点を追従 -----
		if (!m_bThrow[i]){
			m_aPos[i].y -= m_fThrowSpeed;
			continue;
		}

		//----- ボタンリリースで頂点とばせっ！ -----
		m_afSpeedFourse[i] = m_fThrowSpeed;	//スピードを代入
		float fDisX = 1.0f, fDisY = 1.0f;
		//飛ばす方向の調整
		if (!(i % 2))
			fDisX = -1.0f;
		if (i < 2)
			fDisY = -2.0f;
		//飛ばす
		m_aPos[i].x = m_aFourUki[i].GetPosX() + m_afSpeedFourse[i] * fDisX;
		m_aPos[i].y = m_aFourUki[i].GetPosY() + m_afSpeedFourse[i] * fDisY;

		//----- 自然に見えるように頂点間の最大処理とか -----

	}

	//------ 減速 ----------
	m_fThrowSpeed -= DECRE_THROW_SPEED;
	if (m_fThrowSpeed < 0)
		m_fThrowSpeed = 0.0f;

	//------ 減速しきって数秒したら引き上げ ------
	if (m_fThrowSpeed <= 0.0f){
		m_nFrameCnt++;
		if (m_nFrameCnt >= INTERVAL_THOROW_PULL)
			gamePhase = PHASE_PULL;
	}

}


//====================================================
//
// 『引く』中の更新
//
//====================================================
void cNet::PullPhaseUpdate(){



}



#endif