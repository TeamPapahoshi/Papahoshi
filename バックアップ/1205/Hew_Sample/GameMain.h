//======================================================================
//	GameMain
//	
//	概要＿：Init, UnInit, Update, Draw
//	制作者：花井　雄矢
//	
//======================================================================

#ifndef ___GAME_MAIN_H___
#define ___GAME_MAIN_H___

//------------------------------
//インクルードファイル
//------------------------------
#include <Windows.h>	//HRESULT他


//-----------------------------
// 列挙体宣言
//-----------------------------
// シーン列挙体
enum eScene {

	SCENE_TITLE = 0,
	SCENE_STAGE_SELECT,
	SCENE_GAME,
	SCENE_RESULT,

};	//ゲームシーン遷移

//------------------------------
//プロトタイプ宣言
//------------------------------
//初期化
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindowed);
//終了処理
void UnInit(void);
//更新
void Update(void);
//描画
void Draw(void);
void SetScene(int nScene);

#endif //!___GAME_MAIN_H___