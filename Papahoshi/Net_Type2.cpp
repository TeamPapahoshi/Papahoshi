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
#include "Net_Type2.h"
#include "Texture.h"
#include "SceneGame.h"
#include "Input.h"
#include "debugproc.h"

#ifdef  _TYPE_2_


//-------------------------------------
// 定数・マクロ定義
//-------------------------------------
//使用ボタン
#define BOTTON_NET_LEFT			(AC_CON_BUTTON_E)
#define BOTTON_NET_RIGHT		(AC_CON_BUTTON_A)
#define BOTTON_NET_CENTER		(AC_CON_BUTTON_B)
//テクスチャサイズ
#define UKI_SIZE (20.0f)	//うきのサイズ
#define ARROW_SIZE_X (300.0f)	//矢印のサイズ
#define ARROW_SIZE_Y (120.0f)
//スピード
#define MAX_SPEED	(12.5f)
#define DECRE_SPEED (0.1f)	//１フレームごとに初速減らす量
#define DECRE_THROW_SPEED	(0.1f)	//まさつ
//待ち時間
#define INTERVAL_THOROW_PULL	(90)	//投げから引き上げまでの待ち時間
//引くとき
#define PULL_NUM	(3)		//ズッズッてなる回数
#define PULL_FRAME	(50)	//引くフレーム
#define PULL_WAIT	(30)	//待ち時間？
//半円
#define MIN_SPEED	(1.0f)	//最低スピード
#define SPEED_HALFCIRCLE	(10)	//10/1進む

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
	for (int i = 0; i < 3; i++)
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
	for (int i = 0; i < 3; i++){
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

	//半円
	m_halfCircle.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_HALFCIRCLE));
	m_halfCircle.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT));
	m_halfCircle.SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	m_halfCircle.SetScale(D3DXVECTOR2(0.0f, 0.0f));

	//--------- 当たり判定の初期化 --------------
	m_aCollider[0].SetType(cCollider::CollisionType::TRIANGLE);
	m_aCollider[1].SetType(cCollider::CollisionType::TRIANGLE);
	m_aCollider[0].SetTriangleCollider(m_aPos[1], m_centerPos, m_aPos[0]);
	m_aCollider[1].SetTriangleCollider(m_aPos[2], m_centerPos, m_aPos[1]);

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

	//当たり判定情報の更新
	m_aCollider[0].SetTriangleCollider(m_aPos[1], m_centerPos, m_aPos[0]);
	m_aCollider[1].SetTriangleCollider(m_aPos[2], m_centerPos, m_aPos[1]);

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
	for (int i = 0; i < 3; i++){
		m_aFourUki[i].Draw();
	}

	//中心点
	m_center.Draw();

	//矢印(構え状態の時)
	if (m_bDrawArrow)
		m_arrow.Draw();

	//半円(投げ状態の時)
	if (gamePhase == PHASE_SHOUT)
		m_halfCircle.Draw();

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
	for (int i = 0; i < 3; i++){
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
				case NET_PARTS_RIGHT://RIGHT
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
				case NET_PARTS_LEFT://LEFT
					//値の調整
					if (x == 0){
						//必要情報を計算
						if (y == 0){
							tlx = ulx = m_aPos[1].x;
							trx = urx = m_aPos[2].x;
							tdisX = udisX = trx - tlx;
							tly = uly = m_aPos[1].y;
							trY = ury = m_aPos[2].y;
							trY >= tly ? tdisY = udisY = trY - tly : tdisY = udisY = tly - trY;
							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.x - m_aPos[1].x;
							CtoRdisX = m_aPos[2].x - m_centerPos.x;
							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.x - m_aPos[1].x;
							CtoRdisX = m_aPos[2].x - m_centerPos.x;
						}

						//Xの調整
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						urx = m_aPos[2].x - ((((CtoRdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						ulx = m_aPos[1].x + ((((LtoCdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						udisX = urx - ulx;

						//Yの調整
						tly = uly;
						trY = ury;
						tdisY = udisY;
						uly = m_aPos[1].y + ((((m_centerPos.y - m_aPos[2].y) / NET_Y_NUM) * (y + 1)));
						ury = m_aPos[2].y + ((((m_centerPos.y - m_aPos[1].y) / NET_Y_NUM) * (y + 1)));
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
	if (GetInputButtonPress(DIK_N, 0, BOTTON_NET_LEFT))
		m_bPressButton[0] = true;
	else
		m_bPressButton[0] = false;
	if (GetInputButtonPress(DIK_U, 0, BOTTON_NET_RIGHT))
		m_bPressButton[1] = true;
	else
		m_bPressButton[1] = false;
	if (GetInputButtonPress(DIK_8, 0, BOTTON_NET_CENTER))
		m_bPressButton[2] = true;
	else
		m_bPressButton[2] = false;

	//---- 全ボタンプッシュ状態かどうか ----
	for (int i = 0; i < 3; i++){
		if (!m_bPressButton[i])
			break;
		if (i == 2)
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

		//----- 半円の情報を計算 ------
		m_fMaxHalfCircle = m_fThrowSpeed / 10.0f;
		if (m_fMaxHalfCircle > 1.0f)
			m_fMaxHalfCircle = 1.0f;
		m_fDirectHalfCircle = 1.0f;
		m_fSpeed = m_fThrowSpeed * 0.001f;
		m_fHalfCircleSize = 0.0f;

		//----- 構え状態終了 -----
		gamePhase = PHASE_SHOUT;
		m_bDrawArrow = false;
		m_nFrameCnt = 0;		//フレームカウントの初期化
		for (int i = 0; i < 3; i++)
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

	//------ ボタン離したかチェック ------
	for (int i = 0; i < 3; i++){
		if (!m_bPressButton[i] && !m_bThrow[i]){
			//------- 離した瞬間に目的位置を代入 ----------
			if (i == 1)
				m_ThreePurposePos[i].x = SCREEN_WIDTH / 2.0f;
			else if (i == 0)
				m_ThreePurposePos[i].x = (SCREEN_WIDTH / 2.0f) - ((SCREEN_WIDTH * m_fHalfCircleSize) / 2.0f);
			else
				m_ThreePurposePos[i].x = (SCREEN_WIDTH / 2.0f) + ((SCREEN_WIDTH * m_fHalfCircleSize) / 2.0f);
			m_ThreePurposePos[i].y = SCREEN_HEIGHT - (SCREEN_HEIGHT * m_fHalfCircleSize);
			m_bThrow[i] = true;
			
			//****** デバック *******
			//m_aPos[i] = m_ThreePurposePos[i];
			//gamePhase = GAME_PHASE::PHASE_MAX;
		}
	}

	//----- 各四頂点の処理 ------
	for (int i = 0; i < 3; i++){

		if (m_bThrow[i]){
			//----- ボタンリリースで頂点とばせっ！ -----
			float fSp;	//スピード
			//Y方向
			fSp = (m_aPos[i].y - m_ThreePurposePos[i].y) / SPEED_HALFCIRCLE;
			if (fSp < MIN_SPEED)
				fSp = MIN_SPEED;
			m_aPos[i].y -= fSp;
			if (m_aPos[i].y < m_ThreePurposePos[i].y)
				m_aPos[i].y = m_ThreePurposePos[i].y;
			//X方向
			if (m_ThreePurposePos[i].x < m_aPos[i].x){
				fSp = (m_aPos[i].x - m_ThreePurposePos[i].x) / SPEED_HALFCIRCLE;
				if (fSp < MIN_SPEED)
					fSp = MIN_SPEED;
				m_aPos[i].x -= fSp;
				if (m_aPos[i].x < m_ThreePurposePos[i].x)
					m_aPos[i].x = m_ThreePurposePos[i].x;
			}
			else{
				fSp = (m_ThreePurposePos[i].x - m_aPos[i].x) / SPEED_HALFCIRCLE;
				if (fSp < MIN_SPEED)
					fSp = MIN_SPEED;
				m_aPos[i].x += fSp;
				if (m_aPos[i].x > m_ThreePurposePos[i].x)
					m_aPos[i].x = m_ThreePurposePos[i].x;
			}
		}

	}

	//------ 半円の拡大縮小 ----------
	m_fHalfCircleSize += (m_fSpeed * m_fDirectHalfCircle);
	if (m_fHalfCircleSize > m_fMaxHalfCircle)
		m_fDirectHalfCircle = -1.0f;
	if (m_fHalfCircleSize <= 0.0f)
		m_fDirectHalfCircle = 0.0f;
	m_halfCircle.SetScale(D3DXVECTOR2(m_fHalfCircleSize, m_fHalfCircleSize));
	m_halfCircle.SetPosY(SCREEN_HEIGHT -  m_halfCircle.GetSizeY() * m_halfCircle.GetScaleY() * 0.5f);


	//------ 減速しきって数秒したら引き上げ ------
	if (m_fHalfCircleSize <= 0.0f){
		m_nFrameCnt++;
		if (m_nFrameCnt >= INTERVAL_THOROW_PULL){
			m_nFrameCnt = 0;	//初期化
			m_bPurpose = false;
			gamePhase = PHASE_PULL;
		}
	}

}


//====================================================
//
// 『引く』中の更新
//
//====================================================
void cNet::PullPhaseUpdate(){

	//------ 待ち時間がある場合は実行しない --------
	if (m_nFrameCnt){
		m_nFrameCnt--;
		return;
	}

	//------ 目的位置をセット --------
	if (!m_bPurpose){

		//引き上げ回数一定以上で終了
		if (m_nPullNum >= PULL_NUM){
			//シーン移動？
			gamePhase = PHASE_MAX;
		}

		//初回設定
		if (!m_nPullNum){
			for (int i = 0; i < 3; i++){
				if (m_aPos[i].x < m_centerPos.x)
					m_oncePullPos[i].x = (m_centerPos.x - m_aPos[i].x) / PULL_NUM;
				else
					m_oncePullPos[i].x = -(m_aPos[i].x - m_centerPos.x) / PULL_NUM;
				m_oncePullPos[i].y = (m_centerPos.y - m_aPos[i].y) / PULL_NUM;
				m_pullSpeed[i].x = m_oncePullPos[i].x / PULL_FRAME;
				m_pullSpeed[i].y = m_oncePullPos[i].y / PULL_FRAME;
			}
		}

		//引き上げ回数を加算
		m_nPullNum++;
		m_bPurpose = true;

		//目的位置を設定
		for (int i = 0; i < 3; i++){
			m_purposePos[i].x = m_aPos[i].x + m_oncePullPos[i].x;
			m_purposePos[i].y = m_aPos[i].y + m_oncePullPos[i].y;
		}

	}

	//------ 目的位置に近づける --------
	for (int i = 0; i < 3; i++){
		m_aPos[i].x += m_pullSpeed[i].x;
		m_aPos[i].y += m_pullSpeed[i].y;
	}
	m_nPullFrame++;

	//------ 目的位置に着いたら次へ --------
	if (m_nPullFrame >= PULL_FRAME){
		m_nFrameCnt = PULL_WAIT;
		m_nPullFrame = 0;
		m_bPurpose = false;
	}

}



//====================================================
//
//  網の当たり判定を取得
//
//====================================================
cCollider* cNet::GetCollider(){
	return m_aCollider;
}

#endif