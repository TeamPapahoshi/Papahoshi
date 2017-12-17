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

protected:
	cSpriteParam	m_sprite;		// 描画用
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


// 星の設定用構造体
typedef struct _tSetCircleOrbitStar{

	D3DXVECTOR2		center;		// 軌道の中心座標
	D3DXVECTOR2		radius;		// 半径
	float			rad;		// 角度
	int				second;		// 一周にかかる時間(秒)

}tSetCircleOrbitStaretStar;

typedef struct _tFixedStar{

	D3DXVECTOR2		center;		// 軌道の中心座標
	D3DXVECTOR2		radius;		// 半径
	float			rad;		// 角度
	int				second;		// 一周にかかる時間(秒)

}tFixedStar;

// 星の設定用
//vector<tFixedStar>					a_SetFixedStarData;
//vector<tSetCircleOrbitStaretStar>	a_SetCircleOrbitStaretStar;

#endif	//!___BASE_STAR_H___