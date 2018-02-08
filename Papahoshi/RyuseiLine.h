//======================================================================
//	RyuseiLine
//
//	概要＿：流星の軌跡
//	制作者：加藤　遼
//
//======================================================================
#ifndef ___RYUSEI_LINE_H___
#define ___RYUSEI_LINE_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Common.h"


//-----------------------------
//マクロ定義
//-----------------------------


//-----------------------------
//列挙型定義
//-----------------------------
typedef struct _tRyuseiLine{
	cSpriteParam	t_sprite;
	bool			t_bUse;
	float			t_LifeTime;
}tRyuseiLine;

//-----------------------------
//クラス定義
//-----------------------------
class cRyuseiLine
{
public:
	cRyuseiLine();	//コンストラクタ
	~cRyuseiLine();	//デストラクタ
	void Update(D3DXVECTOR2 pos);
	void Draw(void);
private:	
	tRyuseiLine*	m_pRyuseiLine;
	tRyuseiLine*	m_pRoot;


	tRyuseiLine*	m_pRyuseiLineOut;
	tRyuseiLine*	m_pRootOut;

	

};

#endif	//!___RYUSEI_LINE_H___