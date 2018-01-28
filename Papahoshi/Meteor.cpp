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

#define METEOR_ALPHA_SUB    (50.0f)

#define RANDAM_METEOR_POS_X (100)
#define RANDAM_METEOR_POS_Y (100)

#define RANDAM_METEOR_SET_X ((float)CRandam::RandamRenge(RANDAM_METEOR_POS_X, SCREEN_WIDTH - RANDAM_METEOR_POS_X))
#define RANDAM_METEOR_SET_Y ((float)CRandam::RandamRenge(RANDAM_METEOR_POS_Y, SCREEN_HEIGHT - RANDAM_METEOR_POS_Y))
#define RANDAM_METEOR_TIME (CRandam::RandamRenge(100, 250))

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
void cMeteor::Init()
{
	//このタイミングでm_aMeteorの参照位置がずれる->エラーの原因
	
	for (int loop = 0; loop < MAX_METEOR; loop++)
	{
		m_aMeteor[loop].SetMakeTime(RANDAM_METEOR_TIME);
		m_aMeteor[loop].SetLifeTime(METEOR_LIFETIME);

		//スプライトの設定
		for (int Spriteloop = 0; Spriteloop < MAX_METEOR_SPRITE_NUM; Spriteloop++)
		{
			m_aMeteor[loop].Sprite[Spriteloop].SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_SPHERE_LIGHT));
			m_aMeteor[loop].Sprite[Spriteloop].SetVtxColorA(255.0f / (Spriteloop + 1));
			m_aMeteor[loop].Sprite[Spriteloop].SetMove(D3DXVECTOR2(-METEOR_MOVE, METEOR_MOVE));
			m_aMeteor[loop].Sprite[Spriteloop].SetSize(D3DXVECTOR2(METEOR_SIZE, METEOR_SIZE));
		}
	}
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cMeteor::UnInit()
{

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cMeteor::Update(){

	for (int loop = 0; loop < MAX_METEOR; loop++)
	{
		if (m_aMeteor[loop].GetUseFlag())
		{//使用中の処理
			for (int Spriteloop = MAX_METEOR_SPRITE_NUM - 1; Spriteloop >= 0; Spriteloop--)
			{
				if (Spriteloop == 0)
				{
					m_aMeteor[loop].Sprite[Spriteloop].SetPos(m_aMeteor[loop].Sprite[Spriteloop].GetPos() + m_aMeteor[loop].Sprite[Spriteloop].GetMove());
				}
				else
				{
					m_aMeteor[loop].Sprite[Spriteloop].SetPos(m_aMeteor[loop].Sprite[Spriteloop - 1].GetPos());
				}

				if (m_aMeteor[loop].GetLifeTime() <= 0)
				{
					m_aMeteor[loop].Sprite[Spriteloop].SetVtxColorA(m_aMeteor[loop].Sprite[Spriteloop].GetVtxColorA() - METEOR_ALPHA_SUB);
					if (m_aMeteor[loop].Sprite[Spriteloop].GetVtxColorA() < 0.0f)
						m_aMeteor[loop].Sprite[Spriteloop].SetVtxColorA(0.0f);
				}
			}

			m_aMeteor[loop].SetLifeTime(m_aMeteor[loop].GetLifeTime() - 1);		//生存時間の減少


			if (m_aMeteor[loop].Sprite[0].GetVtxColorA() <= 0)
			{
				m_aMeteor[loop].SetUseFlag(false);
				m_aMeteor[loop].SetLifeTime(METEOR_LIFETIME);
			}
		}
		else
		{//未使用の場合の処理
			m_aMeteor[loop].SetMakeTime(m_aMeteor[loop].GetMakeTime() - 1);	//生成時間の減少

			if (m_aMeteor[loop].GetMakeTime() <= 0)
				SetMeteor();
		}
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cMeteor::Draw(){

	for (int loop = 0; loop < MAX_METEOR; loop++)
	{
		if (!m_aMeteor[loop].GetUseFlag())	return;	//未使用の場合は処理しない

		for (int Spriteloop = 0; Spriteloop < MAX_METEOR_SPRITE_NUM; Spriteloop++)
		{
			m_aMeteor[loop].Sprite[Spriteloop].Draw();
		}
	}
}

//=======================================================================================
//
//		流星の設定
//
//=======================================================================================
void cMeteor::SetMeteor(){

	for (int loop = 0; loop < MAX_METEOR; loop++)
	{
		//使用中の場合はスルー
		if (m_aMeteor[loop].GetUseFlag())	return;

		m_aMeteor[loop].Sprite[0].SetPos(D3DXVECTOR2(RANDAM_METEOR_SET_X, RANDAM_METEOR_SET_Y));	//出現座標をランダムに設定

		m_aMeteor[loop].SetUseFlag(true);					//使用フラグを建てる
		m_aMeteor[loop].SetMakeTime(RANDAM_METEOR_TIME);	//生成時間の再設定

		//スプライトの設定
		for (int Spriteloop = 0; Spriteloop < MAX_METEOR_SPRITE_NUM; Spriteloop++)
		{
			m_aMeteor[loop].Sprite[Spriteloop].SetVtxColorA(255.0f / (Spriteloop + 1));
			m_aMeteor[loop].Sprite[Spriteloop].SetMove(D3DXVECTOR2(-METEOR_MOVE, METEOR_MOVE));
			m_aMeteor[loop].Sprite[Spriteloop].SetSize(D3DXVECTOR2(METEOR_SIZE, METEOR_SIZE));
		}

		//一つ生成したらループを抜ける
		break;
	}
}

//避難先
/*
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

	for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++)
	{
		//このタイミングでm_aMeteorの参照位置がずれる->エラーの原因
		
		m_nMakeTime[Meteorloop] = RANDAM_METEOR_TIME;
		m_nLifeTime[Meteorloop] = METEOR_LIFETIME;
		
		//スプライトの設定
		for (int Spriteloop = 0; Spriteloop < MAX_METEOR_SPRITE_NUM; Spriteloop++)
		{
			m_aMeteor[Meteorloop].m_Sprite[Spriteloop].SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_SPHERE_LIGHT));
			m_aMeteor[Meteorloop].m_Sprite[Spriteloop].SetVtxColorA(255.0f / Spriteloop + 1);
			m_aMeteor[Meteorloop].m_Sprite[Spriteloop].SetMove(D3DXVECTOR2(-METEOR_MOVE, METEOR_MOVE));
			m_aMeteor[Meteorloop].m_Sprite[Spriteloop].SetSize(D3DXVECTOR2(METEOR_SIZE, METEOR_SIZE));
		}
	}
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

	for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++)
	{
		if (m_bUseFlag[Meteorloop])
		{//使用中の処理

			for (int Spriteloop = MAX_METEOR_SPRITE_NUM; Spriteloop > 0; Spriteloop--)
			{
				if (Spriteloop == 1)
				{
					m_aMeteor[Meteorloop].m_Sprite[Spriteloop].SetPos(m_aMeteor[Meteorloop].m_Sprite[Spriteloop].GetPos() + m_aMeteor[Meteorloop].m_Sprite[Spriteloop].GetMove());
				}
				else
				{
					m_aMeteor[Meteorloop].m_Sprite[Spriteloop].SetPos(m_aMeteor[Meteorloop].m_Sprite[Spriteloop - 1].GetPos());
				}

			}

			m_nLifeTime[Meteorloop]--;		//生存時間の減少
			if (m_nLifeTime[Meteorloop] <= 0)
			{
				m_bUseFlag[Meteorloop] = false;
				m_nLifeTime[Meteorloop] = METEOR_LIFETIME;
			}
		}
		else
		{//未使用の場合の処理
			m_nMakeTime[Meteorloop]--;	//生成時間の減少

			if (m_nMakeTime[Meteorloop] <= 0)
				SetMeteor();
		}
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cMeteor::Draw(){

	for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++)
	{
		if (!m_bUseFlag[Meteorloop])	return;	//未使用の場合は処理しない

		for (int Spriteloop = 0; Spriteloop < MAX_METEOR_SPRITE_NUM; Spriteloop++)
		{
			m_aMeteor[Meteorloop].m_Sprite[Spriteloop].Draw();
		}
	}
}

//=======================================================================================
//
//		流星の設定
//
//=======================================================================================
void cMeteor::SetMeteor(){

	for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++)
	{
		//使用中の場合はスルー
		if (m_bUseFlag[Meteorloop])	return;

		m_aMeteor[Meteorloop].m_Sprite[0].SetPos(D3DXVECTOR2(RANDAM_METEOR_SET, RANDAM_METEOR_SET));	//出現座標をランダムに設定

		m_bUseFlag[Meteorloop] = true;					//使用フラグを建てる
		m_nMakeTime[Meteorloop] = RANDAM_METEOR_TIME;	//生成時間の再設定

		break;	//一つセットしたらループを抜ける
	}
}
*/

/*

//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cMeteor::Init(){

for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++)
{
//このタイミングでm_aMeteorの参照位置がずれる->エラーの原因

m_aMeteor[Meteorloop].SetMakeTime(RANDAM_METEOR_TIME);
m_aMeteor[Meteorloop].SetLifeTime(METEOR_LIFETIME);

//スプライトの設定
for (int Spriteloop = 0; Spriteloop < MAX_METEOR_SPRITE_NUM; Spriteloop++)
{
m_aMeteor[Meteorloop].GetMeteorSprite(Spriteloop).SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_SPHERE_LIGHT));
m_aMeteor[Meteorloop].GetMeteorSprite(Spriteloop).SetVtxColorA(255.0f / Spriteloop + 1);
m_aMeteor[Meteorloop].GetMeteorSprite(Spriteloop).SetMove(D3DXVECTOR2(-METEOR_MOVE, METEOR_MOVE));
m_aMeteor[Meteorloop].GetMeteorSprite(Spriteloop).SetSize(D3DXVECTOR2(METEOR_SIZE, METEOR_SIZE));
}
}
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

for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++)
{
if (m_aMeteor[Meteorloop].GetUseFlag())
{//使用中の処理

for (int Spriteloop = MAX_METEOR_SPRITE_NUM; Spriteloop > 0; Spriteloop--)
{
if (Spriteloop == 1)
{
m_aMeteor[Meteorloop].GetMeteorSprite(Spriteloop).SetPos(m_aMeteor[Meteorloop].GetMeteorSprite(Spriteloop).GetPos() + m_aMeteor[Meteorloop].GetMeteorSprite(Spriteloop).GetMove());
}
else
{
m_aMeteor[Meteorloop].GetMeteorSprite(Spriteloop).SetPos(m_aMeteor[Meteorloop].GetMeteorSprite(Spriteloop - 1).GetPos());
}

}

m_aMeteor[Meteorloop].SetLifeTime(m_aMeteor[Meteorloop].GetLifeTime() - 1);		//生存時間の減少
if (m_aMeteor[Meteorloop].GetLifeTime() <= 0)
{
m_aMeteor[Meteorloop].SetUseFlag(false);
m_aMeteor[Meteorloop].SetLifeTime(METEOR_LIFETIME);
}
}
else
{//未使用の場合の処理
m_aMeteor[Meteorloop].SetMakeTime(m_aMeteor[Meteorloop].GetMakeTime() - 1);	//生成時間の減少

if (m_aMeteor[Meteorloop].GetMakeTime() <= 0)
SetMeteor();
}
}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cMeteor::Draw(){

for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++)
{
if (!m_aMeteor[Meteorloop].GetUseFlag())	return;	//未使用の場合は処理しない

for (int Spriteloop = 0; Spriteloop < MAX_METEOR_SPRITE_NUM; Spriteloop++)
{
m_aMeteor[Meteorloop].GetMeteorSprite(Spriteloop).Draw();
}
}
}

//=======================================================================================
//
//		流星の設定
//
//=======================================================================================
void cMeteor::SetMeteor(){

for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++)
{
//使用中の場合はスルー
if (m_aMeteor[Meteorloop].GetUseFlag())	return;

m_aMeteor[Meteorloop].GetMeteorSprite(0).SetPos(D3DXVECTOR2(RANDAM_METEOR_SET, RANDAM_METEOR_SET));	//出現座標をランダムに設定

m_aMeteor[Meteorloop].SetUseFlag(true);					//使用フラグを建てる
m_aMeteor[Meteorloop].SetMakeTime(RANDAM_METEOR_TIME);	//生成時間の再設定

break;	//一つセットしたらループを抜ける
}
}
*/

//退避先2
/*
//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cMeteor::Init(){

	for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++)
	{
		//このタイミングでm_aMeteorの参照位置がずれる->エラーの原因
		
		m_aMeteor[Meteorloop].m_nMakeTime = RANDAM_METEOR_TIME;
		m_aMeteor[Meteorloop].m_nLifeTime = METEOR_LIFETIME;
		
		//スプライトの設定
		for (int Spriteloop = 0; Spriteloop < MAX_METEOR_SPRITE_NUM; Spriteloop++)
		{
			m_aMeteor[Meteorloop].m_Sprite[Spriteloop].SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_SPHERE_LIGHT));
			m_aMeteor[Meteorloop].m_Sprite[Spriteloop].SetVtxColorA(255.0f / Spriteloop + 1);
			m_aMeteor[Meteorloop].m_Sprite[Spriteloop].SetMove(D3DXVECTOR2(-METEOR_MOVE, METEOR_MOVE));
			m_aMeteor[Meteorloop].m_Sprite[Spriteloop].SetSize(D3DXVECTOR2(METEOR_SIZE, METEOR_SIZE));
		}
	}
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

	for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++)
	{
		if (m_aMeteor[Meteorloop].m_bUseFlag)
		{//使用中の処理

			for (int Spriteloop = MAX_METEOR_SPRITE_NUM; Spriteloop > 0; Spriteloop--)
			{
				if (Spriteloop == 1)
				{
					m_aMeteor[Meteorloop].m_Sprite[Spriteloop].SetPos(m_aMeteor[Meteorloop].m_Sprite[Spriteloop].GetPos() + m_aMeteor[Meteorloop].m_Sprite[Spriteloop].GetMove());
				}
				else
				{
					m_aMeteor[Meteorloop].m_Sprite[Spriteloop].SetPos(m_aMeteor[Meteorloop].m_Sprite[Spriteloop - 1].GetPos());
				}

			}

			m_aMeteor[Meteorloop].m_nLifeTime--;		//生存時間の減少
			if (m_aMeteor[Meteorloop].m_nLifeTime <= 0)
			{
				m_aMeteor[Meteorloop].m_bUseFlag = false;
				m_aMeteor[Meteorloop].m_nLifeTime = METEOR_LIFETIME;
			}
		}
		else
		{//未使用の場合の処理
			m_aMeteor[Meteorloop].m_nMakeTime--;	//生成時間の減少

			if (m_aMeteor[Meteorloop].m_nMakeTime <= 0)
				SetMeteor();
		}
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cMeteor::Draw(){

	for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++)
	{
		if (!m_aMeteor[Meteorloop].m_bUseFlag)	return;	//未使用の場合は処理しない

		for (int Spriteloop = 0; Spriteloop < MAX_METEOR_SPRITE_NUM; Spriteloop++)
		{
			m_aMeteor[Meteorloop].m_Sprite[Spriteloop].Draw();
		}
	}
}

//=======================================================================================
//
//		流星の設定
//
//=======================================================================================
void cMeteor::SetMeteor(){

	for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++)
	{
		//使用中の場合はスルー
		if (m_aMeteor[Meteorloop].m_bUseFlag)	return;

		m_aMeteor[Meteorloop].m_Sprite[0].SetPos(D3DXVECTOR2(RANDAM_METEOR_SET, RANDAM_METEOR_SET));	//出現座標をランダムに設定

		m_aMeteor[Meteorloop].m_bUseFlag = true;					//使用フラグを建てる
		m_aMeteor[Meteorloop].m_nMakeTime = RANDAM_METEOR_TIME;	//生成時間の再設定

		break;	//一つセットしたらループを抜ける
	}
}

*/