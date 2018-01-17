//======================================================================
//	Meteor
//	
//	概要＿：タイトルオブジェクト/流星
//	制作者：安藤 光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>		//HRESULT他

#include "debugproc.h"		//printdebug
#include "Meteor.h"
#include "Texture.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define METEOR_LIFETIME (60)
#define METEOR_SIZE (10.0f)
#define METEOR_MOVE (2.5f)

#define RANDAM_METEOR_POS (300)

#define RANDAM_METEOR_SET ((float)CRandam::RandamRenge(RANDAM_METEOR_POS, SCREEN_WIDTH - RANDAM_METEOR_POS))
#define RANDAM_METEOR_TIME (CRandam::RandamRenge(200, 400))

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------

//-----------------------------
//グローバル
//-----------------------------


//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cMeteor::cMeteor(){

}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cMeteor::~cMeteor(){

}

//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cMeteor::Init(){
	
	//ポインタの設定
	cSpriteParam* pSprite = m_Sprite;

	for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop ++, pSprite++)
	{
		pSprite->SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_SPHERE_LIGHT));
		pSprite->SetVtxColorA(255.0f / Meteorloop + 1);
		pSprite->SetMove(D3DXVECTOR2(-METEOR_MOVE, METEOR_MOVE));
		pSprite->SetSize(D3DXVECTOR2(METEOR_SIZE, METEOR_SIZE));
	}

	m_nLifeTime = METEOR_LIFETIME;
	m_nMakeTime = RANDAM_METEOR_TIME;
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cMeteor::UnInit(){

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cMeteor::Update(){

	//ポインタの設定
	cSpriteParam* pSprite = m_Sprite;
	cSpriteParam* pOldSprite = m_Sprite;

	if (m_bUseFlag)
	{//使用中の処理

		for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++, pSprite++)
		{
			if (Meteorloop == 0)
			{
				pSprite->SetPos(pSprite->GetPos() + pSprite->GetMove());
			}
			else
			{
				pSprite->SetPos(pOldSprite->GetPos());
			}

			pOldSprite = pSprite;	//過去座標の保存
		}

		m_nLifeTime--;			//生存時間の減少
		if (m_nLifeTime <= 0)
		{
			m_bUseFlag = false;
			m_nLifeTime = METEOR_LIFETIME;
		}
	}
	else
	{//未使用の場合の処理
		m_nMakeTime--;	//生成時間の減少

		if (m_nMakeTime <= 0)
			SetMeteor();
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cMeteor::Draw(){

	//ポインタの設定
	cSpriteParam* pSprite = m_Sprite;

	if (!m_bUseFlag)	return;	//未使用の場合は処理しない

	for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++, pSprite++)
	{
		pSprite->Draw();
	}
}

//=======================================================================================
//
//		流星の設定
//
//=======================================================================================
void cMeteor::SetMeteor(){

	//ポインタの設定
	cSpriteParam* pSprite = m_Sprite;

	pSprite->SetPos(D3DXVECTOR2(RANDAM_METEOR_SET, RANDAM_METEOR_SET));	//出現座標をランダムに設定

	m_bUseFlag = true;					//使用フラグを建てる
	m_nMakeTime = RANDAM_METEOR_TIME;	//生成時間の再設定
}