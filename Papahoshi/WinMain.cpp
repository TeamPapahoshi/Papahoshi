//======================================================================
//	WinMain
//	
//	制作者：WinMain
//	概要　：花井　雄矢
//======================================================================



//------------------------------
// インクルードファイル
//------------------------------
#include "Common.h"
#include "GameMain.h"
#include "Frame.h"

//------------------------------
// マクロ定義
//------------------------------
//----- Windows関連 ------------
#define CLASS_NAME	"パパ、お星さまとって！"	// ウィンドウクラス名
#define WINDOW_NAME	"パパ、お星さまとって！"	// キャプション名

#define WINDOW_MODE	(TRUE)		//FALSEでフルスクリーン

//-----------------------------
// プロトタイプ宣言
//-----------------------------
//ウインドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//=======================================================================================
//
//		main関数
//
//=======================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//----------------------------
	// ローカル変数宣言
	//----------------------------
	//----- Windows関連 ------------
	// ウインドウクラス
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0, 0,
		hInstance, LoadIcon(hInstance, "ICON_JELLY"), LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1), NULL, CLASS_NAME, NULL
	};
	HWND hWnd;	// ウインドウハンドル
	MSG msg;	// メッセージ


	//----------------------------
	// 初期化、ウインドウ表示
	//----------------------------
	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//ウィンドウの作成
	hWnd = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL, NULL, hInstance, NULL);

	// --- 初期化処理 --------------------
	if (FAILED(Init(hInstance, hWnd, WINDOW_MODE))){
		// --- ＜初期化失敗時＞　終了処理 ----
		UnregisterClass(CLASS_NAME, wcex.hInstance);
		UnInit();
		// --- ＜初期化失敗時＞　メッセージ表示 ----
		MessageBox(hWnd, "DirectXの初期化に失敗しました。\nDirectXの設定などを確認してください。", "DirectX初期化失敗", MB_OK | MB_ICONERROR);
		return (-1);
	}

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//----------------------------
	//メッセージループ
	//----------------------------
	while (1){

		//----- Windowsとしての処理 ------------
 		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0){

			// <Windowsから　アプリケーション終了依頼時> 終了
			if (msg.message == WM_QUIT)
				break;

			// <終了依頼以外のWindowメッセージ受信時> メッセージの翻訳と送出
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		//----- DirectXとしての処理 ------------
		else {
			if (CheckFrameUpdate()) {
				//更新処理
				Update();
				//描画処理

				Draw();
			}
		}
	}

	//----------------------------
	// 終了処理
	//----------------------------
	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//終了処理
	UnInit();

	//----------------------------
	// WinMain終了
	//----------------------------
	return (int)msg.wParam;
}

//=======================================================================================
//
//		ウインドウプロシージャ（コールバック関数）
//
//=======================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	//----------------------------
	// ローカル変数宣言
	//----------------------------
	int nID; //終了確認メッセージボックス用



	//----------------------------
	// メッセージ毎の処理
	//----------------------------
	switch (uMsg) {

	//----- ウインドウ消去時　------------
	case WM_DESTROY:

		// 【発行】 WM_QUIT
		PostQuitMessage(0);
		break;



	//----- ×ボタンクリック時　------------
	case WM_CLOSE:

		//終了確認メッセージ表示
		nID = MessageBox(hWnd, "ゲームを終了しています。\nよろしいですか？", "ゲーム終了", (MB_YESNO | MB_DEFBUTTON1 | MB_ICONQUESTION));

		// ---- [YES]----- / ---- 【発行】 WM_DESTROY ----
		if (nID == IDYES) {
			DestroyWindow(hWnd);
		}
		// ---- [NO]----- / ---- ウインドウクローズをキャンセル ----
		else {
			return 0;
		}
		break;
	


	// ---- エスケープキー押下時 ------------
	case WM_KEYDOWN:

		switch (wParam) {
		case VK_ESCAPE:

			//【発行】 WM_CLOSE
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		}
		break; 
	}

	//----------------------------
	//ウィンドウプロシージャ終了
	//----------------------------
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
