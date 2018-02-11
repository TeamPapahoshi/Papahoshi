//======================================================================
//	BaseStar
//	
//	概要＿：星クラスなど
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___BASE_STAR_H___
#define ___BASE_STAR_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "Common.h"
//-----------------------------
//クラス定義
//-----------------------------
//----継承用 星基本クラス----
class cBaseStar{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ~cBaseStar(){}
	cBaseStar(){}

	// フラグのオンオフと星の数を数える
	//virtual void SetCountAndUse(bool flag)=0;

	int GetMaxNum(){ return m_nMaxNum; }
	int GetCurrentNum(){return 	m_nCurrentNum;}

protected:
	int					m_nMaxNum;
	int					m_nCurrentNum=0;
};


// 継承して構造体みたいに使う
class cBaseStarData{

public:
	virtual ~cBaseStarData(){}
	cBaseStarData();

	// どの星でも使うやつ
	cSpriteParam	m_sprite;
	cCollider		m_Collision;

	bool			m_bUse;				// ゲームないで有効かあたり判定とか
	bool			m_bDraw;			// 描画フラグ

	bool			m_bCreateEvent;		// 生成イベント
	bool			m_bCreateEnd;

	bool			m_bDestroyEvent;	// 削除イベント
	bool			m_bDestroyEnd;

	bool			m_bRespawnEvent;	// リスポーンイベント
	bool			m_bRespawnEnd;
	int				m_nRespawnFrame;

	int				m_nEffectSetTime;	// エフェクト設定間隔

	D3DXVECTOR2		m_Move;				// 移動量
	D3DXVECTOR2		m_Destination;		// 目的位置記憶
	D3DXVECTOR2		m_PurPosDist;		// 目的位置までの距離記憶
	D3DXVECTOR2		m_VecStarToDest;	// 星から目的地方向のベクトル
};

//----円軌道移動クラス------円軌道させたいクラスにもたせる(星以外にも使えます)
class cCircleOrbitMovement{

public:
	cCircleOrbitMovement();
	~cCircleOrbitMovement();

	D3DXVECTOR2 GetMove();	// 移動後の座標を取得


	//----セット用-----
	void SetCenter(D3DXVECTOR2 data){
		m_center = data;
	}
	void SetRadius(D3DXVECTOR2 data){	// こいつは基本０でいいはず
		m_radius = data;
	}
	void SetRad(float data){
		m_fRad = data;
	}
	void SetSpped(float data){
		m_fSpeed = data;
	}

private:
	D3DXVECTOR2	m_center;	// 円軌道の中心
	D3DXVECTOR2	m_radius;	// 半径
	float		m_fRad;		// 角度
	float		m_fSpeed;	// 速さ
};

#endif	//!___BASE_STAR_H___