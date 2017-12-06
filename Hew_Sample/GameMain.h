//======================================================================
//	GameMain
//	
//	TvQFInit, UnInit, Update, Draw
//	ง์าFิไ@Y๎
//	
//======================================================================

#ifndef ___GAME_MAIN_H___
#define ___GAME_MAIN_H___

//------------------------------
//CN[ht@C
//------------------------------
#include <Windows.h>	//HRESULTผ


//-----------------------------
// ๑ฬ้พ
//-----------------------------
// V[๑ฬ
enum eScene {

	SCENE_TITLE = 0,
	SCENE_STAGE_SELECT,
	SCENE_GAME,
	SCENE_RESULT,

};	//Q[V[Jฺ

//------------------------------
//vg^Cv้พ
//------------------------------
//๚ป
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindowed);
//Iน
void UnInit(void);
//XV
void Update(void);
//`ๆ
void Draw(void);
void SetScene(int nScene);

#endif //!___GAME_MAIN_H___