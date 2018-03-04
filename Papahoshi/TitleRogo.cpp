//======================================================================
//	TitleRogo
//	
//	概要＿：タイトルロゴ
//	制作者：安藤 光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>		//HRESULT他

#include "debugproc.h"		//printdebug
#include "TitleRogo.h"
#include "Texture.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define TITLEROGO_SIZE_X (120)
#define TITLEROGO_SIZE_Y (120)

#define TITLEROGO_POS_X ((SCREEN_WIDTH / 2 - (TITLEROGO_SIZE_X * ((MAX_TITLEROGO) / 2))) + 60)
#define TITLEROGO_POS_Y (SCREEN_HEIGHT / 2 - 160.0f)

#define TITLEROGO_SPACE_X (-20)

#define TITLEROGO_HOP_COUNT (20)	//タイトルロゴの動作タイマー

#define TITLEROGO_MOVE (-20.0f)		//タイトルロゴの移動量

#define PUSHBUTTON_POS_X (SCREEN_WIDTH / 2)
#define PUSHBUTTON_POS_Y (SCREEN_HEIGHT / 2 + 100)

#define PUSHBUTTON_SIZE_X (500)
#define PUSHBUTTON_SIZE_Y (90)

#define PUSHBUTTON_SCALE_MAG (0.125f)		//タイトルロゴの移動量

#define PUSHBUTTON_ALPHACHANGE_TIMER (10)	//アルファ値切り替えのタイマー

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
//		インクリメント
//
//=======================================================================================
cTitleRogo::cTitleRogo()
{
	m_Pushsprite.LoadTexture("Image/GameUI/press_any_button.png");
}

//=======================================================================================
//
//		デクリメント
//
//=======================================================================================
cTitleRogo::~cTitleRogo()
{

}

//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cTitleRogo::Init()
{
	for (int Initloop = 0; Initloop < MAX_TITLEROGO; Initloop++)
	{
		switch (Initloop)
		{
		case 0://パ
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x - 298.0f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO01));
			break;
		case 1://パ
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x - 205.0f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO02));
			break;
		case 2://、
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x - 158.0f, TITLEROGO_POS_Y + 10.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X / 3.0f, TITLEROGO_SIZE_Y / 1.6f));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO03));
			break;
		case 3://お
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x - 108.0f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO04));
			break;
		case 4://星(大きめ)
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x - 22.0f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X , TITLEROGO_SIZE_Y * 1.1f));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO05));
			break;
		case 5://さ
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 55.0f, TITLEROGO_POS_Y + 4.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO06));
			break;
		case 6://ま
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 130.0f, TITLEROGO_POS_Y - 6.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO07));
			break;
		case 7://と
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 203.0f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO08));
			break;
		case 8://っ
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 260.0f, TITLEROGO_POS_Y + 5.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X / 3.0f, TITLEROGO_SIZE_Y / 1.5f));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO09));
			break;
		case 9://て
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 300.0f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO10));
			break;
		case 10://！(上)
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 354.0f, TITLEROGO_POS_Y + 2.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X / 1.4f, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO11));
			break;
		case 11://！(下)
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 350.0f, TITLEROGO_POS_Y + 50.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(35.0f, 35.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO12));
			break;
		case 12://虹
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x - 10.0f, TITLEROGO_POS_Y + 55.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(720.0f, 30.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO13));
			break;
		default:
			break;
		}
		//元の座標を保存
		m_aTitlerogo[Initloop].fOriginPosY = m_aTitlerogo[Initloop].Rogosprite.GetPosY();
		m_aTitlerogo[Initloop].nHopTimer = TITLEROGO_HOP_COUNT * Initloop;
		m_aTitlerogo[Initloop].bMoveFlag = false;
		m_aTitlerogo[Initloop].fRadian = 0;
	}
	m_Pushsprite.SetPos(D3DXVECTOR2(PUSHBUTTON_POS_X, PUSHBUTTON_POS_Y));
	m_Pushsprite.SetSize(D3DXVECTOR2(PUSHBUTTON_SIZE_X, PUSHBUTTON_SIZE_Y));

	m_nAlphaTimer = PUSHBUTTON_ALPHACHANGE_TIMER;
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cTitleRogo::UnInit()
{

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cTitleRogo::Update(bool bSceneChangeFlag)
{
	static float s_Radian = 0.0f;
	static float fwork;

	//ラジアン値の更新
	s_Radian = ((float)(((int)s_Radian + 1) % MAX_RADIUS));

	//ラジアン値を基に移動量・拡大率の設定
	for (int Updateloop = 0; Updateloop < MAX_TITLEROGO - 1; Updateloop++)
	{
		//タイマー処理
		if (m_aTitlerogo[Updateloop].nHopTimer >= 0)
		{//タイマーの値減少
			m_aTitlerogo[Updateloop].nHopTimer--;
		}
		else
		{
			//移動フラグをオンに
			m_aTitlerogo[Updateloop].bMoveFlag = true;
		}

		//移動フラグがオンになっていれば移動処理の開始
		if (m_aTitlerogo[Updateloop].bMoveFlag)
		{
			if (Updateloop >= 0 && Updateloop < 10)
			{	//文字部分の移動処理
				m_aTitlerogo[Updateloop].fRadian = ((float)(((int)m_aTitlerogo[Updateloop].fRadian + 2) % MAX_RADIUS));

				//座標の更新
				m_aTitlerogo[Updateloop].Rogosprite.SetPosY(SINCURVE(m_aTitlerogo[Updateloop].fOriginPosY, TITLEROGO_MOVE, m_aTitlerogo[Updateloop].fRadian / (MAX_RADIUS / 2)));

				//元座標より下に移動した場合
				if (m_aTitlerogo[Updateloop].fRadian >= MAX_RADIUS / 2)
				{
					//元座標に戻す
					m_aTitlerogo[Updateloop].Rogosprite.SetPosY(m_aTitlerogo[Updateloop].fOriginPosY);
					//タイマーの再設定
					m_aTitlerogo[Updateloop].nHopTimer = TITLEROGO_HOP_COUNT * (MAX_TITLEROGO - 2);
					//ラジアン値の初期化
					m_aTitlerogo[Updateloop].fRadian = 0;
					//移動フラグをオフに
					m_aTitlerogo[Updateloop].bMoveFlag = false;
				}
			}
			else if (Updateloop == 11)
			{//星部分の移動処理
				m_aTitlerogo[Updateloop].fRadian = ((float)(((int)m_aTitlerogo[Updateloop].fRadian + 2) % MAX_RADIUS));

				m_aTitlerogo[Updateloop].Rogosprite.SetRad(m_aTitlerogo[Updateloop].fRadian / 16);

				//一回転した場合
				if (m_aTitlerogo[Updateloop].fRadian == MAX_RADIUS / 2)
				{
					//タイマーの再設定
					m_aTitlerogo[Updateloop].nHopTimer = TITLEROGO_HOP_COUNT * (MAX_TITLEROGO - 2);
					//ラジアン値の初期化
					m_aTitlerogo[Updateloop].fRadian = 0;
					//移動フラグをオフに
					m_aTitlerogo[Updateloop].bMoveFlag = false;
				}
			}
		}
	}

	fwork = COSCURVE(1.0f, PUSHBUTTON_SCALE_MAG, s_Radian / (MAX_RADIUS / 2));

	m_Pushsprite.SetScale(D3DXVECTOR2(fwork, fwork));


	//シーンチェンジのフラグが立てばα値の切り替え開始
	if (bSceneChangeFlag)
	{
		//タイマーの値減少
		m_nAlphaTimer--;
		if (m_nAlphaTimer <= 0)
		{
			m_Pushsprite.SetVtxColorA(0);
		}
		if (m_nAlphaTimer <= -PUSHBUTTON_ALPHACHANGE_TIMER)
		{
			m_Pushsprite.SetVtxColorA(255);
			m_nAlphaTimer = PUSHBUTTON_ALPHACHANGE_TIMER;
		}
	}
	
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cTitleRogo::Draw()
{
	for (int Drawloop = MAX_TITLEROGO - 1; Drawloop >= 0; Drawloop--)
	{
		m_aTitlerogo[Drawloop].Rogosprite.Draw();
	}
	m_Pushsprite.Draw();
}