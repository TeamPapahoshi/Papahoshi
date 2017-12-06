//======================================================================
//	SceneManeger
//	
//	概要＿：シーン管理
//			こことcppにシーンを追加していくmainを変える必要はありません。
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___SCENE_MANEGER_H___
#define ___SCENE_MANEGER_H___

//-----------------------------
//インクルードファイル
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------
//----継承用 シーン基本クラス----
class cBaseScene{
public:
	virtual void Update() = 0;	// 必須
	virtual void Draw() = 0;	// 必須
 
	virtual ~cBaseScene(){}		// デストラクタをオーバライドさせるため
};

//----シーン管理用クラス----
class cSceneManeger{

public:
	//シーン番号用列挙体
	enum SCENE{
		TITLE,	//タイトル
		GAME,	//ゲームメイン
		//RESULT,	//リザルト
	};

	static void ChangeScene(SCENE scene);	// 現在のシーンを引数のシーンへ更新
	static void	Update();					// 現在のシーンの更新関数
	static void	Draw();						// 現在のシーンの描画関数

	static void Uninit();

	static void SetSceneNum(SCENE scene);	// 現在のシーン番号の設定

private:
	static	cBaseScene* m_pScene;			// 現在のシーン
	static  SCENE		m_nCurrentSceneNum;	// 現在のシーン番号
};
#endif	//!___SCENE_MANEGER_H___