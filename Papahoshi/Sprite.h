//======================================================================
//	Sprite
//	
//	概要＿：スプライト
//	制作者：加藤　遼
//	
//======================================================================

#ifndef ___SPRITE_H___
#define ___SPRITE_H___

//---------------------------------
// インクルードファイル
//---------------------------------
#include "Common.h"		
#include <Windows.h>	//HRESULT他
#include "d3dx9.h"		//D3DXVECTOR2他

//---------------------------------
// プロトタイプ宣言
//---------------------------------
HRESULT CreateBufferSprite(void);	// スプライトの頂点バッファの設定
void	ReleaseBufferSprite(void);	// スプライトの頂点バッファの解放


//---------------------------------
// クラス定義
//---------------------------------
//スプライトパラメータクラス
class cSpriteParam {

private:

	// (使う時だけ値をセットする)

	// スプライト
	LPDIRECT3DTEXTURE9 m_pTex;	// テクスチャのポインタ

	D3DXVECTOR2 m_pos;			// 座標位置
	D3DXVECTOR2 m_posFree[4];	// 座標位置(正方形にしない時はこっち使う)
	D3DXVECTOR2 m_size;			// 大きさ
	D3DXVECTOR2 m_scale;		// 拡大率
	D3DXVECTOR2 m_move;			// 移動量(追加)
	float		m_rad;			// 角度
	D3DXCOLOR	m_vtxColor;		// 頂点カラー
	bool		m_texUV;		// テクスチャUV使用フラグ

	// テクスチャUV
	bool	m_bTexAnimationLoop;		// テクスチャアニメーションを使用(Loopのみ)
	int		m_texPatternDivideX;		// テクスチャ内での分割数(X方向)
	int		m_texPatternDivideY;		// テクスチャ内での分割数(Y方向)
	int		m_intervalChangePattern;	// アニメーションの切り替わるタイミング(フレーム数)
	int		m_CountAnimationFrame;		// アニメーションカウント用
	int		m_currentAnimPattern;		// アニメーションパターン番号
	D3DXVECTOR2   m_texUVRatio;			// テクスチャUVの割合

	//アルファブレンドスイッチ
	bool	m_bAddBlend;		//加算合成

public:

	cSpriteParam();									// コンストラクタ
	void Draw();									// 描画
	void DrawFreePos();								// 正方形じゃない描画
	void LoadTexture(LPCSTR fileName);				// テクスチャのロード
	void SetTexture(LPDIRECT3DTEXTURE9* pTex);		// テクスチャのセット
	void AnimationLoop();							// アニメーションループのみ

	D3DXVECTOR2 AffinTranceform(float x, float y);	// アフィン変換

	//----設定用-----
	void SetTexPatternDevide(int x, int y){
		m_texPatternDivideX = x;
		m_texPatternDivideY = y;
	}
	void SetIntervalChangePattern(int data){
		m_intervalChangePattern = data;
	}
	void SetCurrentAnimPattern(int data){
		m_currentAnimPattern = data;
	}
	void SetAnimationFlag(bool data){
		m_bTexAnimationLoop = true;
	}


	void SetPosFree(D3DXVECTOR2 data1, D3DXVECTOR2 data2, D3DXVECTOR2 data3, D3DXVECTOR2 data4){
		m_posFree[0] = data1;
		m_posFree[1] = data2;
		m_posFree[2] = data3;
		m_posFree[3] = data4;
	}
	void SetPos(D3DXVECTOR2 data){		// pos
		m_pos = data;
	}
	void SetPosX(float data){
		m_pos.x = data;
	}
	void SetPosY(float data){
		m_pos.y = data;
	}
	void SetSize(D3DXVECTOR2 data){		// size
		m_size = data;
	}
	void SetSizeX(float data){
		m_size.x = data;
	}
	void SetSizeY(float data){
		m_size.y = data;
	}
	void SetScale(D3DXVECTOR2 data){	// scale
		m_scale = data;
	}

	//追加
	void SetMove(D3DXVECTOR2 data){
		m_move = data;
	}

	void SetMoveX(float data){
		m_move.x = data;
	}

	void SetMoveY(float data){
		m_move.y = data;
	}
	//追加ここまで

	void SetScaleX(float data){
		m_scale.x = data;
	}
	void SetScaleY(float data){
		m_scale.y = data;
	}
	void SetRad(float data){
		m_rad = data;
	}
	void SetVtxColor(D3DXCOLOR data){
		m_vtxColor = data;
	}
	void SetVtxColorR(float data){
		m_vtxColor.r = data;
	}
	void SetVtxColorG(float data){
		m_vtxColor.g = data;
	}
	void SetVtxColorB(float data){
		m_vtxColor.b = data;
	}
	void SetVtxColorA(float data){
		m_vtxColor.a = data;
	}

	void SetTexUVFlag(void)
	{
		m_texUV = true;
	}
	void SetTexUVRatio(D3DXVECTOR2 data)
	{
		m_texUVRatio = data;
	}
	void SetTexUVRatioX(float data)
	{
		m_texUVRatio.x = data;
	}
	void SetTexUVRatioY(float data)
	{
		m_texUVRatio.y = data;
	}
	void SetAddBlend(bool data){
		m_bAddBlend = data;
	}


	//----取得用----
	int GetCurrentAnimPattern(){
		return m_currentAnimPattern;
	}
	D3DXVECTOR2 GerPosFree0(){
		return m_posFree[0];
	}
	D3DXVECTOR2 GerPosFree1(){
		return m_posFree[1];
	}
	D3DXVECTOR2 GerPosFree2(){
		return m_posFree[2];
	}
	D3DXVECTOR2 GerPosFree3(){
		return m_posFree[3];
	}
	D3DXVECTOR2 GetPos(){		// pos
		return m_pos;
	}
	float GetPosX(){
		return m_pos.x;
	}
	float GetPosY(){
		return m_pos.y;
	}
	D3DXVECTOR2 GetSize(){		// size
		return m_size;
	}
	float GetSizeX(){
		return m_size.x;
	}
	float GetSizeY(){
		return m_size.y;
	}
	D3DXVECTOR2 GetScale(){		// scale
		return m_scale;
	}
	float GetScaleX(){
		return m_scale.x;
	}
	float GetScaleY(){
		return m_scale.y;
	}

	//追加
	D3DXVECTOR2 GetMove(){		// scale
		return m_move;
	}
	float GetMoveX(){
		return m_move.x;
	}
	float GetMoveY(){
		return m_move.y;
	}
	//追加ここまで

	float GetRad(){	// rad
		return m_rad;
	}
	D3DXCOLOR GetVtxColor(){	// vexcolor
		return m_vtxColor;
	}
	float GetVtxColorR(){
		return m_vtxColor.r;
	}
	float GetVtxColorG(){
		return m_vtxColor.g;
	}
	float GetVtxColorB(){
		return m_vtxColor.b;
	}
	float GetVtxColorA(){
		return m_vtxColor.a;
	}

	D3DXVECTOR2 GetTexUVRatio()
	{
		return m_texUVRatio;
	}
	float GetTexUVRatioX()
	{
		return m_texUVRatio.x;
	}
	float GetTexUVRatioY()
	{
		return m_texUVRatio.y;
	}
	
};
#endif	//!___SPRITE_H___