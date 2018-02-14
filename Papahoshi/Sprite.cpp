//======================================================================
//	Sprite
//	
//	概要＿：スプライトの設定と描画
//	制作者：加藤　遼
//	
//======================================================================

//------------------------------
// インクルードファイル
//------------------------------
#include <math.h>

#include "Sprite.h"
#include "Direct3D.h"

//---------------------------
// マクロ定義
//---------------------------
//頂点フォーマット
#define FVF_VERTEX_2D_TEXTURE (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//描画頂点数
#define NUM_VERTEX_SPRITE	(4)

//描画ポリゴン数
#define NUM_POLYGON_SPRITE	(2)


//---------------------------------
//構造体定義
//---------------------------------
//頂点情報
typedef struct _tVertex2D{

	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//テクスチャのパースペクティブコネクト
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標

} tVertex2D;


//---------------------------
//グローバル変数
//---------------------------
//頂点バッファ
static LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffSprite = NULL;

//=======================================================================================
//
//		スプライト管理初期化
//
//	[戻り値]	S_OK ： 初期化成功		E_FAIL : 初期化失敗
//
//=======================================================================================
cSpriteParam::cSpriteParam(){

	// 初期値(使わない場合はこのままで)
	m_pos = D3DXVECTOR2(100.0f, 100.0f);
	m_posFree[0] = D3DXVECTOR2(100.0f, 100.0f);
	m_posFree[1] = D3DXVECTOR2(100.0f, 100.0f);
	m_posFree[2] = D3DXVECTOR2(100.0f, 100.0f);
	m_posFree[3] = D3DXVECTOR2(100.0f, 100.0f);
	m_size		= D3DXVECTOR2(100.0f, 100.0f);
	m_scale		= D3DXVECTOR2(1.0f, 1.0f);
	m_texUVRatio = D3DXVECTOR2(1.0f, 1.0f);
	m_vtxColor	= D3DXCOLOR(255, 255, 255, 255);
	m_rad		= 0.0f;
	m_texUV		= false;
	m_pTex		= NULL;
	

	// 初期値(使わない場合はこのままで)
	m_texPatternDivideX=1;		
	m_texPatternDivideY=1;		
	m_intervalChangePattern = 999;			
	m_currentAnimPattern=0;	
	m_bTexAnimationLoop = false;
	m_CountAnimationFrame = 0;

	m_bAddBlend = false;

}

//=======================================================================================
//
//		スプライト描画関数
//
//=======================================================================================
void cSpriteParam::Draw(){

	//----------------------------
	// 透明度0のとき、skip
	//----------------------------
	if (m_vtxColor.a <= 0)
		return;

	//----------------------------
	// ローカル変数宣言
	//----------------------------
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス情報
	tVertex2D *pVtx;							// 頂点情報

	//---------------------------
	// アルファブレンドを設定
	//---------------------------
	if (m_bAddBlend){
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// αデスティネーションカラーの指定
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z比較なし
	}

	//----------------------------
	// 頂点バッファの頂点情報を更新
	//----------------------------
	//----- 頂点バッファ　ロック ------------
	g_pVtxBuffSprite->Lock(0, 0, (void **)&pVtx, 0);	//ポインタのポインタ

	//---- 座標計算計算 -----
	// アフィン変換
	D3DXVECTOR2 vtxPos0[4];
	vtxPos0[0] = AffinTranceform(-m_size.x / 2.0f * m_scale.x, -m_size.y / 2.0f * m_scale.y);
	vtxPos0[1] = AffinTranceform( m_size.x / 2.0f * m_scale.x, -m_size.y / 2.0f * m_scale.y);
	vtxPos0[2] = AffinTranceform(-m_size.x / 2.0f * m_scale.x,  m_size.y / 2.0f * m_scale.y);
	vtxPos0[3] = AffinTranceform( m_size.x / 2.0f * m_scale.x,  m_size.y / 2.0f * m_scale.y);

	// 座標位置(後でカメラの座標を差し込む)
	D3DXVECTOR2 vtxPos1[4];
	vtxPos1[0] = D3DXVECTOR2(m_pos.x + vtxPos0[0].x, m_pos.y + vtxPos0[0].y);
	vtxPos1[1] = D3DXVECTOR2(m_pos.x + vtxPos0[1].x, m_pos.y + vtxPos0[1].y);
	vtxPos1[2] = D3DXVECTOR2(m_pos.x + vtxPos0[2].x, m_pos.y + vtxPos0[2].y);
	vtxPos1[3] = D3DXVECTOR2(m_pos.x + vtxPos0[3].x, m_pos.y + vtxPos0[3].y);

	//----- 頂点座標　更新 ------------
	pVtx[0].pos = D3DXVECTOR3(vtxPos1[0].x, vtxPos1[0].y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(vtxPos1[1].x, vtxPos1[1].y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(vtxPos1[2].x, vtxPos1[2].y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(vtxPos1[3].x, vtxPos1[3].y, 0.0f);

	//----- テクスチャ座標 更新 ------------
	float fPosXLeft, fPosXRight, fPosYUp, fPosYDown;	
	int		NumAnimPattern = m_texPatternDivideX*m_texPatternDivideY;// アニメーションの総パターン数
	float	TexPatternSizeX = 1.0f / m_texPatternDivideX;			 // 1パターンのテクスチャサイズ割合(X方向)
	float	TexPatternSizeY = 1.0f / m_texPatternDivideY;			 // 1パターンのテクスチャサイズ割合(Y方向)

	fPosXLeft = (float)(m_currentAnimPattern % m_texPatternDivideX) * TexPatternSizeX;
	fPosXRight = fPosXLeft + TexPatternSizeX;
	fPosYUp = (float)(m_currentAnimPattern / (NumAnimPattern / m_texPatternDivideY)) * TexPatternSizeY;
	fPosYDown = fPosYUp + TexPatternSizeY;

	if (m_texUV)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_texUVRatio.x, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, m_texUVRatio.y);
		pVtx[3].tex = D3DXVECTOR2(m_texUVRatio.x, m_texUVRatio.y);
	}
	else
	{
		pVtx[0].tex = D3DXVECTOR2(fPosXLeft, fPosYUp);
		pVtx[1].tex = D3DXVECTOR2(fPosXRight, fPosYUp);
		pVtx[2].tex = D3DXVECTOR2(fPosXLeft, fPosYDown);
		pVtx[3].tex = D3DXVECTOR2(fPosXRight, fPosYDown);
	}

	//----- rhw 更新 ------------
	pVtx[0].rhw = pVtx[1].rhw = pVtx[2].rhw = pVtx[3].rhw = 1.0f;

	//----- 頂点カラー 更新 ------------
	pVtx[0].col = pVtx[1].col = pVtx[2].col = pVtx[3].col = 
		D3DCOLOR_RGBA((unsigned char)m_vtxColor.r, (unsigned char)m_vtxColor.g,
		(unsigned char)m_vtxColor.b, (unsigned char)m_vtxColor.a);

	//----- 頂点バッファ　アンロック ------------
	g_pVtxBuffSprite->Unlock();

	//----------------------------
	// 描画準備
	//----------------------------
	// 頂点バッファをデバイスのデータストリームへバインド
	pDevice->SetStreamSource(0, g_pVtxBuffSprite, 0, sizeof(tVertex2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D_TEXTURE);

	// テクスチャの設定
	pDevice->SetTexture(0,m_pTex);

	//----------------------------
	// 描画
	//----------------------------
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON_SPRITE);

	//----------------------------
	// 描画設定を初期化
	//----------------------------
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			// Z比較あり
}


//=======================================================================================
//
//		スプライト描画関数(正方形じゃない場合)
//
//=======================================================================================
void cSpriteParam::DrawFreePos(){

	//----------------------------
	// 透明度0のとき、skip
	//----------------------------
	if (m_vtxColor.a <= 0)
		return;

	//----------------------------
	// ローカル変数宣言
	//----------------------------
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス情報
	tVertex2D *pVtx;							// 頂点情報

	//---------------------------
	// アルファブレンドを設定
	//---------------------------
	if (m_bAddBlend){
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// αデスティネーションカラーの指定
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z比較なし
	}

	//----------------------------
	// 頂点バッファの頂点情報を更新
	//----------------------------
	//----- 頂点バッファ　ロック ------------
	g_pVtxBuffSprite->Lock(0, 0, (void **)&pVtx, 0);	//ポインタのポインタ

	//----- 頂点座標　更新 ------------
	pVtx[0].pos = D3DXVECTOR3(m_posFree[0].x, m_posFree[0].y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posFree[1].x, m_posFree[1].y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posFree[2].x, m_posFree[2].y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posFree[3].x, m_posFree[3].y, 0.0f);

	//----- テクスチャ座標 更新 ------------
	float fPosXLeft, fPosXRight, fPosYUp, fPosYDown;
	int		NumAnimPattern = m_texPatternDivideX*m_texPatternDivideY;// アニメーションの総パターン数
	float	TexPatternSizeX = 1.0f / m_texPatternDivideX;			 // 1パターンのテクスチャサイズ割合(X方向)
	float	TexPatternSizeY = 1.0f / m_texPatternDivideY;			 // 1パターンのテクスチャサイズ割合(Y方向)

	fPosXLeft = (float)(m_currentAnimPattern % m_texPatternDivideX) * TexPatternSizeX;
	fPosXRight = fPosXLeft + TexPatternSizeX;
	fPosYUp = (float)(m_currentAnimPattern / (NumAnimPattern / m_texPatternDivideY)) * TexPatternSizeY;
	fPosYDown = fPosYUp + TexPatternSizeY;

	if (m_texUV)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f			, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_texUVRatio.x, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f		    , m_texUVRatio.y);
		pVtx[3].tex = D3DXVECTOR2(m_texUVRatio.x, m_texUVRatio.y);
	}
	else
	{
		pVtx[0].tex = D3DXVECTOR2(fPosXLeft, fPosYUp);
		pVtx[1].tex = D3DXVECTOR2(fPosXRight, fPosYUp);
		pVtx[2].tex = D3DXVECTOR2(fPosXLeft, fPosYDown);
		pVtx[3].tex = D3DXVECTOR2(fPosXRight, fPosYDown);
	}

	//----- rhw 更新 ------------
	pVtx[0].rhw = pVtx[1].rhw = pVtx[2].rhw = pVtx[3].rhw = 1.0f;

	//----- 頂点カラー 更新 ------------
	pVtx[0].col = pVtx[1].col = pVtx[2].col = pVtx[3].col =
		D3DCOLOR_RGBA((unsigned char)m_vtxColor.r, (unsigned char)m_vtxColor.g,
		(unsigned char)m_vtxColor.b, (unsigned char)m_vtxColor.a);

	//----- 頂点バッファ　アンロック ------------
	g_pVtxBuffSprite->Unlock();

	//----------------------------
	// 描画準備
	//----------------------------
	// 頂点バッファをデバイスのデータストリームへバインド
	pDevice->SetStreamSource(0, g_pVtxBuffSprite, 0, sizeof(tVertex2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D_TEXTURE);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTex);

	//----------------------------
	// 描画
	//----------------------------
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON_SPRITE);

	//----------------------------
	// 描画設定を初期化
	//----------------------------
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			// Z比較あり

}

//=======================================================================================
//
//		アニメーション
//
//=======================================================================================
void cSpriteParam::AnimationLoop(){


	if (!m_bTexAnimationLoop)
		return;

	m_CountAnimationFrame++;

	if (m_currentAnimPattern > m_texPatternDivideX*m_texPatternDivideY-1){
		m_currentAnimPattern = 0;
	}

	if (m_CountAnimationFrame >= m_intervalChangePattern){

		m_CountAnimationFrame = 0;

		m_currentAnimPattern++;
	}


	
}


//=======================================================================================
//
//		テクスチャロード
//
//=======================================================================================
void cSpriteParam::LoadTexture(LPCSTR fileName){

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// Direct3Dデバイス
	D3DXCreateTextureFromFile(pDevice, fileName, &m_pTex);
}


//=======================================================================================
//
//		テクスチャセット
//
//=======================================================================================
void cSpriteParam::SetTexture(LPDIRECT3DTEXTURE9* pTex){
	m_pTex = *pTex;
}



//=======================================================================================
//
//		スプライトのバッファの作成
//
//	[戻り値]	S_OK ： 初期化成功		E_FAIL : 初期化失敗
//
//=======================================================================================
HRESULT CreateBufferSprite(void){

	//----------------------------
	// オブジェクトの頂点バッファを生成
	//----------------------------
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// Direct3Dデバイス

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(tVertex2D) * NUM_VERTEX_SPRITE,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D_TEXTURE, D3DPOOL_MANAGED, &g_pVtxBuffSprite, NULL)))
		return E_FAIL;

	//----------------------------
	//初期化完了
	//----------------------------
	return S_OK;
}

//=======================================================================================
//
//		スプライトのバッファの解放
//
//=======================================================================================
void	ReleaseBufferSprite(void){

	//----------------------------
	//頂点バッファの解放
	//----------------------------
	if (g_pVtxBuffSprite != NULL)
	{
		g_pVtxBuffSprite->Release();
		g_pVtxBuffSprite = NULL;
	}
}

//=======================================================================================
//
//		アフィン変換
//
//=======================================================================================
D3DXVECTOR2 cSpriteParam:: AffinTranceform(float x, float y){

	D3DXVECTOR2 affin;
	affin.x = x*cosf(m_rad) - y*sinf(m_rad);
	affin.y = x*sinf(m_rad) + y*cosf(m_rad);

	return affin;
}