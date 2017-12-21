//======================================================================
//	StageManeger
//	
//	概要＿：ステージ管理
//
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___STAGE_MANEGER_H___
#define ___STAGE_MANEGER_H___

//-----------------------------
//インクルードファイル
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------
//----継承用 ステージ基本クラス----
class cBaseStage{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual ~cBaseStage(){}
};

//----ステージ管理用クラス----
class cStageManager{

public:
	//シーン番号用列挙体
	enum STAGE{
		STAGE_01,		// ステージ01
		STAGE_02,		// ステージ02
		STAGE_MAX,
	};

	 static void	ChangeStage(STAGE stage);	// ステージを引数のステージへ更新
	 void	Update();					// 現在のステージの更新関数
	 void	Draw();						// 現在のステージの描画関数

	 void	Uninit();

	 static void	SetStageNum(STAGE stage);	// 現在のステージ番号の設定

private:
	static cBaseStage* m_pStage;			// 現在のステージ
	static STAGE		m_nCurrentStageNum;	// 現在のステージ番号
};
#endif	//!___STAGE_MANEGER_H___