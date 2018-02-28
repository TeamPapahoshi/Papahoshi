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

typedef struct _HSVCOLOR{

	unsigned int h;
	unsigned char s;
	unsigned char v;

}HSVCOLOR;


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
	D3DXCOLOR	m_vtxColor[4];	// 頂点カラー
	HSVCOLOR	m_HSVColor[4];	// HSVカラー
	bool		m_bUseHSVColor;	// HSVカラー使用フラグ
	bool		m_texUV;		// テクスチャUV使用フラグ
	bool		m_texRoll;		// テクスチャスクロール使用フラグ

	// テクスチャUV
	bool	m_bTexAnimationLoop;		// テクスチャアニメーションを使用(Loopのみ)
	int		m_texPatternDivideX;		// テクスチャ内での分割数(X方向)
	int		m_texPatternDivideY;		// テクスチャ内での分割数(Y方向)
	int		m_intervalChangePattern;	// アニメーションの切り替わるタイミング(フレーム数)
	int		m_CountAnimationFrame;		// アニメーションカウント用
	int		m_currentAnimPattern;		// アニメーションパターン番号
	D3DXVECTOR2   m_texUVRatio;			// テクスチャUVの割合
	D3DXVECTOR2   m_texRollNum;			// テクスチャスクロールの移動量		

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
		for (int i = 0; i < 4; i++)
			m_vtxColor[i] = data;
	}
	void SetVtxColorOne(D3DXCOLOR data,int number){
		m_vtxColor[number] = data;
	}
	void SetHSVColorOne(unsigned int h, unsigned char s, unsigned char v, int number){
		m_HSVColor[number].h = h;
		m_HSVColor[number].s = s;
		m_HSVColor[number].v = v;
	}
	void SetHSVColorFlag(bool flag){
		m_bUseHSVColor = flag;
	}

	void SetVtxColorR(float data){
		for (int i = 0; i < 4; i++)
			m_vtxColor[i].r = data;
	}
	void SetVtxColorG(float data){
		for (int i = 0; i < 4; i++)
			m_vtxColor[i].g = data;
	}
	void SetVtxColorB(float data){
		for (int i = 0; i < 4; i++)
			m_vtxColor[i].b = data;
	}
	void SetVtxColorA(float data){
		for (int i = 0; i < 4; i++)
			m_vtxColor[i].a = data;
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

	void SetTexRollFlag(bool data)
	{
		m_texRoll = data;
	}
	void SetTexRollNum(D3DXVECTOR2 data)
	{
		m_texRollNum = data;
		if (m_texRollNum.x > 1.0f)
			m_texRollNum.x = 0.0f;
		if (m_texRollNum.x < 0.0f)
			m_texRollNum.x = 1.0f;

		if (m_texRollNum.y > 1.0f)
			m_texRollNum.y = 0.0f;
		if (m_texRollNum.y < 0.0f)
			m_texRollNum.y = 1.0f;

	}
	void SetTexRollNumX(float data)
	{
		m_texRollNum.x = data;

		if (m_texRollNum.x > 2.0f)
			m_texRollNum.x = 0.0f;
		if (m_texRollNum.x < 0.0f)
			m_texRollNum.x = 2.0f;
	}
	void SetTexRollNumY(float data)
	{
		m_texRollNum.y = data;

		if (m_texRollNum.y > 2.0f)
			m_texRollNum.y = 0.0f;
		if (m_texRollNum.y < 0.0f)
			m_texRollNum.y = 2.0f;
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
	float GetVtxColor(){	// vexcolor
		return (float)m_vtxColor[0];
	}
	float GetVtxColorR(){
		return  (float)m_vtxColor[0].r;
	}
	float GetVtxColorG(){
		return  (float)m_vtxColor[0].g;
	}
	float GetVtxColorB(){
		return  (float)m_vtxColor[0].b;
	}
	float GetVtxColorA(){
		return  (float)m_vtxColor[0].a;
	}
	float GetVtxColorOne(int number){
		return  (float)m_vtxColor[number];
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

	bool GetTexRollFlag()
	{
		return m_texRoll;
	}
	D3DXVECTOR2 GetTexRollNum()
	{
		return m_texRollNum;
	}
	float GetTexRollNumX()
	{
		return m_texRollNum.x;
	}
	float GetTexRollNumY()
	{
		return m_texRollNum.y;
	}
};
#endif	//!___SPRITE_H___