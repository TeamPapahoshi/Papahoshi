//======================================================================
//	Star
//	
//	概要＿：星クラスなど
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___STAR_H___
#define ___STAR_H___

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
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void UnInit() = 0;
	virtual ~cBaseStar(){}
	cBaseStar():m_center(D3DXVECTOR2(100.0f, 100.0f)), m_radius(D3DXVECTOR2(50.0f, 50.0f)), m_rad(D3DX_PI){}

protected:

	// 円軌道する際に必要
	cSpriteParam	m_sprite;		// 描画用
	cCollider		m_collision;	// あたり判定	
	D3DXVECTOR2		m_center;		// 軌道の中心座標
	D3DXVECTOR2		m_radius;		// 半径
	float			m_rad;			// 角度
	int				m_second;		// 一周にかかる時間(秒)

	//

};


//-----星の光------
//class cStarLight{
//
//public:
//
//	cStarLight(){
//
//	}
//	~cStarLight(){
//
//	}
//
//	void Init();
//	void Update();
//	void Draw();
//	void UnInit();
//
//	void SetPos(D3DXVECTOR2 pos);
//private:
//	cSpriteParam m_sprite;
//
//
//};


//******円軌道星********
class cCircleOrbitStar :public cBaseStar{

public:
	 void Init();
	 void Update();
	 void Draw();
	 void UnInit();

	 ~cCircleOrbitStar(){}
	 cCircleOrbitStar(){}

	 // 星の設定
	 void SetCircleOrbitStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

private:

	//bool			m_lightSwitch;	// 自分が光るか 
	//cStarLight		m_Light;		// 光
};


//******恒星********
class cFixedStar:public cBaseStar{

public:
	void Init();
	void Update();
	void Draw();
	void UnInit();

	~cFixedStar(){}
	cFixedStar() :m_bSizeSwitch(true){}

	// 星の設定
	void SetFixedStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);
private:
	bool m_bSizeSwitch;
};

#endif	//!___STAR_H___