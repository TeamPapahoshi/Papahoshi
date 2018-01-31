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
	virtual void SetCountAndUse(bool flag)=0;


protected:
	int					m_nMaxNum;
	int					m_nCurrentNum=0;
};


// 継承して構造体みたいに使う
class cBaseStarData{

public:
	virtual ~cBaseStarData(){}

	cBaseStarData(){
		m_bUse = false;
		m_bDraw = false;
		m_bCreateEvent = false;
		m_bCreateEnd	= false;
		m_bDestroyEvent = false;
		m_bDestroyEnd = false;
		m_bRespawnEvent = false;
		m_bRespawnEnd = false;
		m_nRespawnFrame = 0;
	}

	// どの星でも使うやつ
	cSpriteParam	m_sprite;
	cCollider		m_Collision;

	
	bool			m_bUse;			// ゲームないで有効かあたり判定とか
	bool			m_bDraw;		// 描画フラグ

	bool			m_bCreateEvent;	// 生成イベント
	bool			m_bCreateEnd;

	bool			m_bDestroyEvent;// 削除イベント
	bool			m_bDestroyEnd;

	bool			m_bRespawnEvent;// リスポーンイベント
	bool			m_bRespawnEnd;
	int				m_nRespawnFrame;
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