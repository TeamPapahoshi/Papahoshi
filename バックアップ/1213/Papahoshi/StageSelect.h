//======================================================================
//	Sample
//	
//	概要＿：ステージセレクト処理
//	制作者：安藤 光樹
//	
//======================================================================
#ifndef ___STAGESELECT_H___
#define ___STAGESELECT_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Common.h"		
#include <Windows.h>	//HRESULT他
#include "d3dx9.h"		//D3DXVECTOR2他
#include "Sprite.h"		//CSpriteクラスの導入

//-----------------------------
//マクロ定義
//-----------------------------
#define MAX_STAGE (12)	//ステージ数(仮)
//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------
class cStageSelect
{
private:
	cSpriteParam m_StageSprite[MAX_STAGE];	//スプライト情報
	bool		 m_bClearFlag[MAX_STAGE];	//ステージのクリアフラグ

	int			 m_nSelectStageNum;	//現在選択中のステージ番号

//-----------------------------
protected:

//-----------------------------
public:

	cStageSelect(){}		// コンストラクタ
	~cStageSelect(){}	// デストラクタ

	// ここは何かから継承させてもいいかもオーバライド
	void Init(LPDIRECT3DTEXTURE9* pTex);	// 初期化 テクスチャのポインタを受け取って
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

	int GetSelectStageNum(void);	//ステージ番号の引き渡し関数
};

#endif	//!___STAGESELECT_H___