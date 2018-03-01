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
//
//  ABの傾きが0.0fの時垂線を求めるときに
//  0除算が行われてエラーが起きて、表示されなくなる。
//  Y軸に平行な直線の傾きは定義できない？
//
//=============================================================================


//-------------------------------------
// インクルード部
//-------------------------------------
#include "Net_Type2.h"
#include "Texture.h"
#include "SceneGame.h"
#include "Input.h"
#include "debugproc.h"
#include "MathEX.h"
#include "sound.h"

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
#define MAX_SPEED	(15.5f)
#define DECRE_SPEED (0.1f)	//１フレームごとに初速減らす量
#define DECRE_THROW_SPEED	(0.1f)	//まさつ
//待ち時間
#define INTERVAL_THOROW_PULL	(20)	//投げから引き上げまでの待ち時間
//引くとき
#define PULL_WAIT	(15)	//待ち時間？
//半円
#define MIN_SPEED	(1.0f)	//最低スピード
#define SPEED_HALFCIRCLE	(5)	//10/1進む
//斜め投げ補正
#define ANG_NUM		(200.0f)
//縦補正値
#define ANG_Y_FIRST		(100.0f)
#define ANG_Y_SECOND	(ANG_Y_FIRST * 2.0f)
//制御点を求める
#define CP_DIVIDE	(4)			//線分の分割数
#define CP_DISTANCE	((float)SCREEN_HEIGHT / 4.0f)	//線分との距離

//テクスチャカラー
#define NET_TEX_SATURATION		(90.0f)
#define NET_TEX_VALUE			(100.0f)
#define NET_TEX_MAX_HUE			(360.0f)
#define NET_TEX_MIN_HUE			(0.0f)
#define NET_TEX_INCREMENT_HUE	(10.0f)

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
	//m_centerPos = D3DXVECTOR2(SCREEN_WIDTH / 4.0f + (SCREEN_WIDTH / 4.0f * 3.0f / 2.0f), SCREEN_HEIGHT + 30.0f);
	m_centerPos = D3DXVECTOR2(GAME_SCREEN_LEFT + (GAME_SCREEN_RIGHT - GAME_SCREEN_LEFT) / 2.0f, SCREEN_HEIGHT + 30.0f);

	//---- 四頂点の初期化 ----
	for (int i = 0; i < 3; i++)
		m_aPos[i] = m_centerPos;

	//---- スプライトの初期化 ----

	//あみ
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
				m_aNet[z][y][x].SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_NET));	// テクスチャのセット
				m_aNet[z][y][x].SetAddBlend(true);
			}
		}
	}

	//うき・四頂点
	for (int i = 0; i < 3; i++){
		m_aFourUki[i].SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_UKI));
		m_aFourUki[i].SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));
	}
	m_aFourUki[0].LoadTexture("Image/Net/red.png");
	m_aFourUki[1].LoadTexture("Image/Net/blue.png");
	m_aFourUki[2].LoadTexture("Image/Net/yellow.png");

	//うき・センター
	m_center.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_UKI));
	m_center.SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));

	//矢印
	m_arrow.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_ARROW));
	m_arrow.SetPos(D3DXVECTOR2(m_centerPos.x, SCREEN_HEIGHT - 80.0f));
	m_arrow.SetSize(D3DXVECTOR2(ARROW_SIZE_X, ARROW_SIZE_Y));
	m_arrow.SetRad(D3DX_PI);

	//半円
	m_halfCircle.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_HALFCIRCLE));
	m_halfCircle.SetPos(D3DXVECTOR2(GAME_SCREEN_LEFT + ((GAME_SCREEN_RIGHT - GAME_SCREEN_LEFT) / 2.0f), SCREEN_HEIGHT));
	m_halfCircle.SetSize(D3DXVECTOR2(GAME_SCREEN_RIGHT - GAME_SCREEN_LEFT, GAME_SCREEN_UNDER - GAME_SCREEN_TOP));
	m_halfCircle.SetScale(D3DXVECTOR2(0.0f, 0.0f));

	//--------- 当たり判定の初期化 --------------
	m_aCollider[0].SetType(cCollider::CollisionType::TRIANGLE);
	m_aCollider[1].SetType(cCollider::CollisionType::TRIANGLE);
	m_aCollider[0].SetTriangleCollider(m_aPos[1], m_centerPos, m_aPos[0]);
	m_aCollider[1].SetTriangleCollider(m_aPos[2], m_centerPos, m_aPos[1]);

	//--- テクスチャカラー ---
	m_fNetHue = NET_TEX_MIN_HUE;
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
				m_aNet[z][y][x].SetHSVColorFlag(true);
			}
		}
	}

	//波紋
	for (int i = 0; i < MAX_RIPPLE; i++){
		m_aRipple[i] = NULL;
	}

	//パーティクル
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){
		m_aPirticle[i] = NULL;
	}
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

	//テクスチャカラーの更新
	NetColorUpdate();

	//波紋の更新
	for (int i = 0; i < MAX_RIPPLE; i++){
		if (m_aRipple[i]){
			m_aRipple[i]->Update();
			if (m_aRipple[i]->GetFinFlug()){
				delete m_aRipple[i];
				m_aRipple[i] = NULL;
			}
		}
	}

	//パーティクルの更新
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){
		if (m_aPirticle[i]){
			m_aPirticle[i]->Update();
			if (m_aPirticle[i]->GetFinFlug()){
				delete m_aPirticle[i];
				m_aPirticle[i] = NULL;
			}
		}
	}

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

	//はもん
	for (int i = 0; i < MAX_RIPPLE; i++){
		if (m_aRipple[i])
			m_aRipple[i]->Draw();
	}

	//パーティクル
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){
		if (m_aPirticle[i])
			m_aPirticle[i]->Draw();
	}

	//あみ
	//******
	// z = 0
	// y < NET_Y_NUM
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
				if (m_centerPos <= m_aPos[z] ||
					m_centerPos <= m_aPos[z + 1]){
					y = NET_Y_NUM + 1;
					break;
				}
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

	//---- ローカル変数 ----
	D3DXVECTOR2 workPos[4];	//最終ポジション
	bool skip;	//計算スキップフラブ
	D3DXVECTOR2 cp1, cp2;	//縦ラインの制御点
	D3DXVECTOR2 cp3, cp4;	//横ラインの制御点
	D3DXVECTOR2	topXleft, topXright;		//上のXの両端
	D3DXVECTOR2	underXleft, underXright;	//下の
	D3DXVECTOR2	leftYtop, leftYunder;		//左の
	D3DXVECTOR2	rightYtop, rightYunder;		//右の
	float regula;	//引き状態に合わせて調整

	//---- ウキの位置を設定 ----
	for (int i = 0; i < 3; i++){
		m_aFourUki[i].SetPos(m_aPos[i]);
	}
	m_center.SetPos(m_centerPos);

	//---- 曲線状に座標を設定 -----
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){

				//---- 変数の初期化 ----
				for (int i = 0; i < 4; i++){
					workPos[i] = m_centerPos;
				}
				skip = false;

				switch (z)
				{
				case NET_PARTS_RIGHT://RIGHT

					//------ 網張りが必要ない場合は処理を行わない ------
					if (m_centerPos == m_aPos[0] ||
						m_centerPos == m_aPos[1]){
						skip = true;
						break;
					}

					//------- 値の調整 --------------
					if (x == 0){

						//------ 最初の一回のみ計算 ---------
						if (y == 0){

							//****** 線分AOの制御点を計算 *******
							//変数宣言
							D3DXVECTOR2 d, e;
							float aoSlop, aoInter, dfSlop, dfInter, egSlop, egInter;
							//分割点d,fを求める
							d = LineSplitPoint(m_aPos[0], m_centerPos, 1, CP_DIVIDE - 1);
							e = LineSplitPoint(m_aPos[0], m_centerPos, CP_DIVIDE - 1, 1);
							//線分AOの式を求める
							aoSlop = LineSlope(m_aPos[0], m_centerPos);
							aoInter = LineIntercept(m_aPos[0], m_centerPos);
							//線分AOと、分割点dを交点とした垂線DFを求める
							dfSlop = VerticalLineSlope(aoSlop);
							dfInter = VerticalLineIntercept(d, aoSlop);
							//線分AOと、分割点eを交点とした垂線EGを求める
							egSlop = VerticalLineSlope(aoSlop);
							egInter = VerticalLineIntercept(e, aoSlop);
							//引き状態に合わせて調整値を求める
							if (gamePhase == GAME_PHASE::PHASE_PULL){
								switch (m_nPullNum)
								{
								case 1:
									regula = 1.0f - (0.4f * ((float)m_nPullFrame / (float)PULL_FRAME));
									if (m_nFrameCnt)
										regula = 0.6f;
									break;
								case 2:
									regula = 1.0f - (0.3f * ((float)m_nPullFrame / (float)PULL_FRAME)) - 0.4f;
									if (m_nFrameCnt)
										regula = 0.3f;
									break;
								case 3:
									regula = 1.0f - (0.3f * ((float)m_nPullFrame / (float)PULL_FRAME)) - 0.7f;
									if (m_nFrameCnt)
										regula = 0.0f;
									break;
								default:
									regula = 1.0f;
									break;
								}
							}
							else{
								regula = 1.0f;
							}
							//制御点F
							cp1.x = d.x - ((m_aPos[0].y - CP_DISTANCE) * regula);
							cp1.y = LineY(cp1.x, dfSlop, dfInter);
							//制御点G
							cp2.x = e.x - ((m_aPos[0].y - CP_DISTANCE) * regula);
							cp2.y = LineY(cp2.x, egSlop, egInter);

							//********* 線分ABの制御点を計算 *******
							//分割点d,fを求める
							d = LineSplitPoint(m_aPos[0], m_aPos[1], 1, CP_DIVIDE - 1);
							e = LineSplitPoint(m_aPos[0], m_aPos[1], CP_DIVIDE - 1, 1);
							//線分ABの式を求める
							aoSlop = LineSlope(m_aPos[0], m_aPos[1]);
							aoInter = LineIntercept(m_aPos[0], m_aPos[1]);
							//線分ABと、分割点dを交点とした垂線DFを求める
							dfSlop = VerticalLineSlope(aoSlop);
							dfInter = VerticalLineIntercept(d, aoSlop);
							//線分ABと、分割点eを交点とした垂線EGを求める
							egSlop = VerticalLineSlope(aoSlop);
							egInter = VerticalLineIntercept(e, aoSlop);
							//制御点F
							cp3.y = d.y + ((m_aPos[1].y - m_aPos[0].y) / 2.0f);
							cp3.x = LineX(cp3.y, dfSlop, dfInter);
							//制御点G
							cp4.y = e.y + ((m_aPos[1].y - m_aPos[0].y) / 2.0f);
							cp4.x = LineY(cp4.y, egSlop, egInter);

						}

						//----- 行ごとに計算 ----

						//***** 上のXラインの両端を求める *****
						topXleft = BezierCurve((float)y / (float)NET_Y_NUM, m_aPos[0], cp1, cp2, m_centerPos);
						topXright = LineSplitPoint(m_aPos[1], m_centerPos, y, NET_Y_NUM - y);

						//***** 下のXラインの両端を求める *****
						underXleft = BezierCurve(((float)y + 1.0f) / (float)NET_Y_NUM, m_aPos[0], cp1, cp2, m_centerPos);
						underXright = LineSplitPoint(m_aPos[1], m_centerPos, y + 1, NET_Y_NUM - (y + 1));

					}

					//---- 毎回計算を行う -----

					//***** 左のYラインの両端を求める *****
					leftYtop = BezierCurve((float)x / (float)NET_X_NUM, m_aPos[0], cp3, cp4, m_aPos[1]);
					leftYunder = m_centerPos;

					//***** 右のYラインの両端を求める *****
					rightYtop = BezierCurve(((float)x + 1.0f) / (float)NET_X_NUM, m_aPos[0], cp3, cp4, m_aPos[1]);
					rightYunder = m_centerPos;

					//***** 最終ポジション決定 *****
					workPos[0].x = LineSplitPoint(topXleft, topXright, x, NET_X_NUM - x).x;
					workPos[1].x = LineSplitPoint(topXleft, topXright, x + 1, NET_X_NUM - (x + 1)).x;
					workPos[2].x = LineSplitPoint(underXleft, underXright, x, NET_X_NUM - x).x;
					workPos[3].x = LineSplitPoint(underXleft, underXright, x + 1, NET_X_NUM - (x + 1)).x;

					workPos[0].y = LineSplitPoint(leftYtop, leftYunder, y, NET_Y_NUM - y).y;
					workPos[1].y = LineSplitPoint(rightYtop, rightYunder, y, NET_Y_NUM - y).y;
					workPos[2].y = LineSplitPoint(leftYtop, leftYunder, y + 1, NET_Y_NUM - (y + 1)).y;
					workPos[3].y = LineSplitPoint(rightYtop, rightYunder, y + 1, NET_Y_NUM - (y + 1)).y;
					break;

				case NET_PARTS_LEFT:

					//網張りが必要ない場合は処理を行わない
					if (m_centerPos == m_aPos[2] ||
						m_centerPos == m_aPos[1]){
						skip = true;
						break;
					}

					//値の調整
					if (x == 0){
						//必要情報を計算
						if (y == 0){

							//****** 線分COの制御点を計算 *******
							//変数宣言
							D3DXVECTOR2 d, e;
							float aoSlop, aoInter, dfSlop, dfInter, egSlop, egInter;
							//分割点d,fを求める
							d = LineSplitPoint(m_aPos[2], m_centerPos, 1, CP_DIVIDE - 1);
							e = LineSplitPoint(m_aPos[2], m_centerPos, CP_DIVIDE - 1, 1);
							//線分COの式を求める
							aoSlop = LineSlope(m_aPos[2], m_centerPos);
							aoInter = LineIntercept(m_aPos[2], m_centerPos);
							//線分COと、分割点dを交点とした垂線DFを求める
							dfSlop = VerticalLineSlope(aoSlop);
							dfInter = VerticalLineIntercept(d, aoSlop);
							//線分COと、分割点eを交点とした垂線EGを求める
							egSlop = VerticalLineSlope(aoSlop);
							egInter = VerticalLineIntercept(e, aoSlop);
							//引き状態に合わせて調整値を求める
							if (gamePhase == GAME_PHASE::PHASE_PULL){
								switch (m_nPullNum)
								{
								case 1:
									regula = 1.0f - (0.4f * ((float)m_nPullFrame / (float)PULL_FRAME));
									if (m_nFrameCnt)
										regula = 0.6f;
									break;
								case 2:
									regula = 1.0f - (0.3f * ((float)m_nPullFrame / (float)PULL_FRAME)) - 0.4f;
									if (m_nFrameCnt)
										regula = 0.3f;
									break;
								case 3:
									regula = 1.0f - (0.3f * ((float)m_nPullFrame / (float)PULL_FRAME)) - 0.7f;
									if (m_nFrameCnt)
										regula = 0.0f;
									break;
								default:
									regula = 1.0f;
									break;
								}
							}
							else{
								regula = 1.0f;
							}
							//制御点F
							cp1.x = d.x + ((m_aPos[2].y - CP_DISTANCE) * regula);
							cp1.y = LineY(cp1.x, dfSlop, dfInter);
							//制御点G
							cp2.x = e.x + ((m_aPos[2].y - CP_DISTANCE) * regula);
							cp2.y = LineY(cp2.x, egSlop, egInter);

							//********* 線分BCの制御点を計算 *******
							//分割点d,fを求める
							d = LineSplitPoint(m_aPos[1], m_aPos[2], 1, CP_DIVIDE - 1);
							e = LineSplitPoint(m_aPos[1], m_aPos[2], CP_DIVIDE - 1, 1);
							//線分ABの式を求める
							aoSlop = LineSlope(m_aPos[1], m_aPos[2]);
							aoInter = LineIntercept(m_aPos[1], m_aPos[2]);
							//線分ABと、分割点dを交点とした垂線DFを求める
							dfSlop = VerticalLineSlope(aoSlop);
							dfInter = VerticalLineIntercept(d, aoSlop);
							//線分ABと、分割点eを交点とした垂線EGを求める
							egSlop = VerticalLineSlope(aoSlop);
							egInter = VerticalLineIntercept(e, aoSlop);
							//制御点F
							cp3.y = d.y + ((m_aPos[1].y - m_aPos[2].y) / 2.0f);
							cp3.x = LineY(cp3.y, dfSlop, dfInter);
							//制御点G
							cp4.y = e.y + ((m_aPos[1].y - m_aPos[2].y) / 2.0f);
							cp4.x = LineY(cp4.y, egSlop, egInter);
						}

						//----- 行ごとに計算 ----

						//***** 上のXラインの両端を求める *****
						topXleft = LineSplitPoint(m_aPos[1], m_centerPos, y, NET_Y_NUM - y);
						topXright = BezierCurve((float)y / (float)NET_Y_NUM, m_aPos[2], cp1, cp2, m_centerPos);

						//***** 下のXラインの両端を求める *****
						underXleft = LineSplitPoint(m_aPos[1], m_centerPos, y + 1, NET_Y_NUM - (y + 1));
						underXright = BezierCurve(((float)y + 1.0f) / (float)NET_Y_NUM, m_aPos[2], cp1, cp2, m_centerPos);
					}

					//---- 毎回計算を行う -----

					//***** 左のYラインの両端を求める *****
					leftYtop = BezierCurve((float)x / (float)NET_X_NUM, m_aPos[1], cp3, cp4, m_aPos[2]);
					leftYunder = m_centerPos;

					//***** 右のYラインの両端を求める *****
					rightYtop = BezierCurve(((float)x + 1.0f) / (float)NET_X_NUM, m_aPos[1], cp3, cp4, m_aPos[2]);
					rightYunder = m_centerPos;

					//***** 最終ポジション決定 *****
					workPos[0].x = LineSplitPoint(topXleft, topXright, x, NET_X_NUM - x).x;
					workPos[1].x = LineSplitPoint(topXleft, topXright, x + 1, NET_X_NUM - (x + 1)).x;
					workPos[2].x = LineSplitPoint(underXleft, underXright, x, NET_X_NUM - x).x;
					workPos[3].x = LineSplitPoint(underXleft, underXright, x + 1, NET_X_NUM - (x + 1)).x;

					workPos[0].y = LineSplitPoint(leftYtop, leftYunder, y, NET_Y_NUM - y).y;
					workPos[1].y = LineSplitPoint(rightYtop, rightYunder, y, NET_Y_NUM - y).y;
					workPos[2].y = LineSplitPoint(leftYtop, leftYunder, y + 1, NET_Y_NUM - (y + 1)).y;
					workPos[3].y = LineSplitPoint(rightYtop, rightYunder, y + 1, NET_Y_NUM - (y + 1)).y;

					break;

				} //switch 

				//あみのポジション決定
				if (!skip)
					m_aNet[z][y][x].SetPosFree(workPos[0], workPos[1], workPos[2], workPos[3]);
			}
		}
	} //曲線終了

}


//====================================================
//
// 網のテクスチャカラーの更新
//
//====================================================
void cNet::NetColorUpdate(){

	float hue;

	m_fNetHue += NET_TEX_INCREMENT_HUE;
	if (m_fNetHue > NET_TEX_MAX_HUE){
		m_fNetHue = NET_TEX_MIN_HUE;
	}

	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){

				m_aNet[z][y][x].SetHSVColorFlag(true);

				hue = m_fNetHue + (NET_TEX_INCREMENT_HUE * y);
				while (hue > NET_TEX_MAX_HUE){
					hue -= NET_TEX_MAX_HUE;
				}

				m_aNet[z][y][x].SetHSVColorOne(hue, NET_TEX_SATURATION, NET_TEX_VALUE, 0);
				m_aNet[z][y][x].SetHSVColorOne(hue, NET_TEX_SATURATION, NET_TEX_VALUE, 1);
				//m_aNet[z][y][x].SetVtxColor(D3DXCOLOR(100.0f, 00.0f, 100.0f, 155.0f));

				hue += NET_TEX_INCREMENT_HUE;
				while (hue > NET_TEX_MAX_HUE){
					hue -= NET_TEX_MAX_HUE;
				}

				m_aNet[z][y][x].SetHSVColorOne(hue, NET_TEX_SATURATION, NET_TEX_VALUE, 2);
				m_aNet[z][y][x].SetHSVColorOne(hue, NET_TEX_SATURATION, NET_TEX_VALUE, 3);

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
		if (i == 2){
			m_bAllPress = true;
			return;
		}
	}
	m_bAllPress = false;

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
		PlaySound(SOUND_LABEL::SOUND_LABEL_SE_NET_GAGE);
		m_bDrawArrow = false;
		m_nFrameCnt = 0;		//フレームカウントの初期化
		for (int i = 0; i < 3; i++){
			m_bThrow[i] = false;
			m_bRipple[i] = false;
		}
		break;
	}

}


//====================================================
//
// 『投げる』中の更新
//
//====================================================
void cNet::ShoutPhaseUpdate(){

	bool xFin[3];
	bool yFin[3];

	for (int i = 0; i < 3; i++){
		xFin[i] = false;
		yFin[i] = false;
	}

	//------ ボタン離したかチェック ------
	for (int i = 0; i < 3; i++){
		if (!m_bPressButton[i] && !m_bThrow[i]){
			//------- 離した瞬間に目的位置を代入 ----------
			if (i == 1)
				m_ThreePurposePos[i].x = m_centerPos.x;
			else if (i == 0)
				m_ThreePurposePos[i].x = (m_centerPos.x) - ((SCREEN_WIDTH * m_fHalfCircleSize) / 2.0f);
			else
				m_ThreePurposePos[i].x = (m_centerPos.x) + ((SCREEN_WIDTH * m_fHalfCircleSize) / 2.0f);
			m_ThreePurposePos[i].y = SCREEN_HEIGHT - (SCREEN_HEIGHT * m_fHalfCircleSize);
			m_bThrow[i] = true;

			//---------- 斜め投げ補正 ------------
			if (m_nPostAngle == ANG_LEFT)
				m_ThreePurposePos[i].x += ANG_NUM;
			else if (m_nPostAngle == ANG_RIGHT)
				m_ThreePurposePos[i].x -= ANG_NUM;

			//------- Yの補正値 ------
			if (m_nPostAngle == ANG_STRAIGHT){
				if (i != 1){
					m_ThreePurposePos[i].y += ANG_Y_FIRST;
				}
			}
			else if (m_nPostAngle == ANG_RIGHT){
				if (i == 0){
					m_ThreePurposePos[i].y += ANG_Y_SECOND;
				}
				else if (i == 1){
					m_ThreePurposePos[i].y += ANG_Y_FIRST;
				}
			}
			else if (m_nPostAngle == ANG_LEFT){
				if (i == 2){
					m_ThreePurposePos[i].y += ANG_Y_SECOND;
				}
				else if (i == 1){
					m_ThreePurposePos[i].y += ANG_Y_FIRST;
				}
			}

			//------ SEの再生 ------
			PlaySound(SOUND_LABEL::SOUND_LABEL_SE_NET_SHOOT);

			//--- パーティクルの生成 ---
			SetPirticle(D3DXVECTOR2(m_centerPos.x, m_centerPos.y - 100.0f));
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
			if (m_aPos[i].y < m_ThreePurposePos[i].y){
				m_aPos[i].y = m_ThreePurposePos[i].y;
				yFin[i] = true;
			}
			//X方向
			if (m_ThreePurposePos[i].x < m_aPos[i].x){
				fSp = (m_aPos[i].x - m_ThreePurposePos[i].x) / SPEED_HALFCIRCLE;
				if (fSp < MIN_SPEED)
					fSp = MIN_SPEED;
				m_aPos[i].x -= fSp;
				if (m_aPos[i].x < m_ThreePurposePos[i].x){
					m_aPos[i].x = m_ThreePurposePos[i].x;
					xFin[i] = true;
				}
			}
			else{
				fSp = (m_ThreePurposePos[i].x - m_aPos[i].x) / SPEED_HALFCIRCLE;
				if (fSp < MIN_SPEED)
					fSp = MIN_SPEED;
				m_aPos[i].x += fSp;
				if (m_aPos[i].x > m_ThreePurposePos[i].x){
					m_aPos[i].x = m_ThreePurposePos[i].x;
					xFin[i] = true;
				}
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
	m_halfCircle.SetPosY(SCREEN_HEIGHT - m_halfCircle.GetSizeY() * m_halfCircle.GetScaleY() * 0.5f);

	//---- 投げ終了で引き上げ -----
	for (int i = 0; i < 3; i++){
		if (!xFin[i] || !yFin[i])
			break;
		if (!m_bRipple[i]){ //波紋生成
			SetRipple(m_aPos[i]);
			m_bRipple[i] = true;
		}
		if (i == 2){
			m_fHalfCircleSize = 0.0f;
			StopSound(SOUND_LABEL::SOUND_LABEL_SE_NET_GAGE);
		}
	}

	//------ 減速しきって数秒したら引き上げ ------
	if (m_fHalfCircleSize <= 0.0f){

		//投げきっていない場合はゲージがもう一度拡大
		if (!m_bThrow[0] || !m_bThrow[1] || !m_bThrow[2]){
			m_fDirectHalfCircle = 1.0f;
		}
		else{
			m_nFrameCnt++;
			if (m_nFrameCnt >= INTERVAL_THOROW_PULL){
				m_nFrameCnt = 0;	//初期化
				m_bPurpose = false;
				gamePhase = PHASE_PULL;
				StopSound(SOUND_LABEL::SOUND_LABEL_SE_NET_GAGE);
			}
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
		if (m_nFrameCnt)
			return;
	}

	//------ 目的位置をセット --------
	if (!m_bPurpose){

		//引き上げ回数一定以上で終了
		if (m_nPullNum >= PULL_NUM){
			//シーン移動？
			m_nPullNum = -1;
			m_bPurpose = false;
			gamePhase = PHASE_POST;
			m_aPos[0] = m_aPos[1] = m_aPos[2] = m_centerPos;
			m_postPhase = POST_NON;
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

		//SEの再生
		if (m_nPullNum)
			PlaySound(SOUND_LABEL::SOUND_LABEL_SE_NET_PULL);

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

//===========================================
//
// 波紋生成
//
//===========================================
void cNet::SetRipple(D3DXVECTOR2 pos){

	for (int i = 0; i < MAX_RIPPLE; i++){

		if (m_aRipple[i])
			continue;


		m_aRipple[i] = new cRipple(pos);

		return;

	}

}

//===========================================
//
// パーティクル生成
//
//===========================================
void cNet::SetPirticle(D3DXVECTOR2 pos){

	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){

		if (m_aPirticle[i])
			continue;

		m_aPirticle[i] = new cNetPirticleManage(pos);

		return;
	}
}


#endif