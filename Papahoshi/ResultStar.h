//======================================================================
//	ResultStar.h
//	
//	概要＿：リザルト画面星表示
//	制作者：安藤 光樹
//	
//======================================================================
#ifndef ___RESULTSTAR_H___
#define ___RESULTSTAR_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Common.h"
#include "BaseStar.h"
#include "ResultGirl.h"

//-----------------------------
//マクロ定義
//-----------------------------

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------
class cResultStarData :public cBaseStarData{
public:
	int		m_nEffectFrame = 0;
	int		m_nStarColorNum = 0;
	int		m_nLifeTime = 0;

};

// 基底クラス:クラスサンプル
class cResultStar
{
private:	//外部から参照不可能
	cResultStarData* m_pStarData;	//星のデータ
	cResultStarData* m_pRoot;		//星のデータ先頭位置

	cResultgirl*   m_pResultGirl;
	int			   m_nStarNum;	//星の数

	//-----------------------------
protected:	//クラス内でのみ参照可能

	//-----------------------------
public:		//外部から参照可能

	cResultStar();	//コンストラクタ
	~cResultStar();	//デストラクタ

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void GetResultGirlData(cResultgirl* data)
	{
		m_pResultGirl = data;
	}
};

#endif	//!___SAMPLE_H___