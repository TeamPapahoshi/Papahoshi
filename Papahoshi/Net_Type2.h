//=============================================================================
//  Net.h
//
//  制作：後藤 愛生
//  概要：網の処理
//=============================================================================
#ifndef _NET_TYPE2_H_
#define _NET_TYPE2_H_

#define _TYPE_2_
#ifdef  _TYPE_2_

//----------------------------------------
// インクルード部
//----------------------------------------
#include "Common.h"
#include "Sprite.h"
#include "Collision.h"
//----------------------------------------
// 列挙型宣言
//----------------------------------------
enum{	//ネットの部品
	NET_PARTS_RIGHT,
	NET_PARTS_LEFT,
	NET_PARTS_MAX,
};


//----------------------------------------
// 定数・マクロ定義
//----------------------------------------
#define NET_X_NUM	(20)	//あみの横分割数
#define NET_Y_NUM	(20)	//あみの縦分割数

#define PULL_NUM	(3)		//ズッズッてなる回数
#define PULL_FRAME	(30)	//引く1回分のフレーム

//----------------------------------------
// クラス定義
//----------------------------------------
class cNet{

public:
	cNet();
	~cNet();

	void Update();	// 更新
	void Draw();	// 描画

	cCollider* GetCollider();	//網の当たり判定を取得

	//これが0のときに引いてます(待ち時間がない)
	int GetFrameCnt(){
		return m_nFrameCnt;
	}

	//引いている状態のときにtrueを返す
	bool GetPullFlug(){
		return (gamePhase == PHASE_PULL && !m_nFrameCnt);
	}

	D3DXVECTOR2 GetNetStart(){
		return m_centerPos;
	}

	D3DXVECTOR2 GetNetLeft(){
		return m_aPos[0];
	}

	D3DXVECTOR2 GetNetCenter(){
		return m_aPos[1];
	}

	D3DXVECTOR2 GetNetRight(){
		return m_aPos[2];
	}

private:
	//---- 列挙型宣言 -----
	enum GAME_PHASE{	//網のゲームフェイズ
		PHASE_POST,	//構え
		PHASE_SHOUT,	//飛ばし
		PHASE_PULL,		//引く

		PHASE_MAX,
	};

	enum POST_ANGLE{	//構え角度
		ANG_LEFT = 1,
		ANG_STRAIGHT,
		ANG_RIGHT,
	};

	enum POST_PHASE{
		POST_NON,
		POST_PULL,
		POST_N,
		POST_PUSH,
	};

	//---- スプライト ----
	cSpriteParam m_aNet[NET_PARTS_MAX][NET_Y_NUM][NET_X_NUM];	//あみ
	cSpriteParam m_aFourUki[3];	//三頂点のうき
	cSpriteParam m_center;		//中心点のうき
	cSpriteParam m_arrow;		//矢印
	cSpriteParam m_halfCircle;	//半円
	D3DXVECTOR2 m_aPos[3];		//四頂点
	D3DXVECTOR2 m_centerPos;	//中心点
	
	//---- 当たり判定 ------
	cCollider m_aCollider[2];	//当たり判定
								//２つの三角で構成される網

	//----- 変数宣言 -----
	GAME_PHASE gamePhase;	//ゲームフェイズ
	//キー入力系
	bool	m_bPressButton[3];	//三ボタンのプレス状況
	bool	m_bAllPress;		//全ボタンプレス中
	int		m_nLeverDirection;	//レバー入力方向、テンキー表記で格納
	//描画系
	bool	m_bDrawArrow;		//矢印を描画するかどうか
	//構え状態
	int		m_nPostAngle;		//構え角度
	int		m_nFrameCnt;
	float	m_fThrowSpeed;		//スピード
	POST_PHASE	m_postPhase;	//構えフェイズ
	//投げ状態
	bool	m_bThrow[3];		//Trueなら投げ中の頂点
	D3DXVECTOR2	m_ThreePurposePos[3];	//三頂点のポジション
	//引き状態
	D3DXVECTOR2	m_purposePos[3];	//目的位置
	bool		m_bPurpose;			//目的位置が設定されているか
	int			m_nPullNum;			//引いた回数
	int			m_nPullFrame;		//引くフレーム
	D3DXVECTOR2 m_oncePullPos[3];		//一度で引く距離
	D3DXVECTOR2 m_pullSpeed[3];		//引くスピード
	//半円
	float		m_fHalfCircleSize;	//半円のサイズ
	float		m_fSpeed;			//スピード
	float		m_fMaxHalfCircle;	//半円のマックスサイズ
	float		m_fDirectHalfCircle;	//方向

	//網のテクスチャカラー
	float		m_fNetHue;

	//---- プロトタイプ宣言 ----
	void SetNet();	//各頂点に合わせてあみを貼る
	void NetColorUpdate();	//あみのテクスチャカラー
	void Input();	//コントローラー入力を取得
	void PostPhaseUpdate();
	void ShoutPhaseUpdate();
	void PullPhaseUpdate();
};

#endif
#endif