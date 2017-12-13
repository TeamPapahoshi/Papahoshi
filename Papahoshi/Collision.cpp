//======================================================================
//	Collision.cpp
//	
//	概要＿：Collisionの処理
//	制作者：加藤　遼
//	
//======================================================================
#include "Collision.h"
#include "Sprite.h"


//------------------------------
//グローバル 
//------------------------------

//======================================================================
//	
//
//		コンストラクタ
//		
//
//======================================================================
cCollider::cCollider(){

	m_type = CIRCLE;								// 設定しない場合は円
	m_tColBody.QuadPos = D3DXVECTOR2(0.0f, 0.0f);	// 四角の中心座標
	m_tColBody.QuadSize = D3DXVECTOR2(0.0f, 0.0f);	// 四角のサイズ
	m_tColBody.CirclePos = D3DXVECTOR2(0.0f, 0.0f);	// 円の中心座標
	m_tColBody.fRadius = 0.0f;						// 円の半径
	sprite.SetVtxColorA(100.0f);					// 半透明でセット
}


//======================================================================
//	
//
//		描画
//		
//
//======================================================================
void cCollider::Draw(){

	// spriteの座標にcoliderの座標をセット
	if (m_type == CIRCLE){
		sprite.SetPos(m_tColBody.CirclePos);
		sprite.SetSize(D3DXVECTOR2(m_tColBody.fRadius*2.0f, m_tColBody.fRadius*2.0f));
		sprite.LoadTexture(TEXTURE_FILENAME_CIRCLE_COLLIDER);
	}
	if (m_type == QUAD){
		sprite.SetPos(m_tColBody.QuadPos);
		sprite.SetSize(m_tColBody.QuadSize);
		sprite.LoadTexture(TEXTURE_FILENAME_CIRCLE_QUAD);
	}

	// 描画
	sprite.Draw();
}

//======================================================================
//	
//		円と円のあたり判定
//
//		引数
//		
//
//====================================================================== 
bool cCollider::CheckCollisionCircleToCircle(cCollider obj1, cCollider obj2){

	//-----判定-----
	if ((obj1.GetCollider().CirclePos.x - obj2.GetCollider().CirclePos.x)*(obj1.GetCollider().CirclePos.x - obj2.GetCollider().CirclePos.x) +
		(obj1.GetCollider().CirclePos.y - obj2.GetCollider().CirclePos.y)*(obj1.GetCollider().CirclePos.y - obj2.GetCollider().CirclePos.y)
		<= (obj1.GetCollider().fRadius + obj2.GetCollider().fRadius)*(obj1.GetCollider().fRadius + obj2.GetCollider().fRadius)){

		return true;
	}
	return false;
}


float CalculateDistanceAtoB(D3DXVECTOR2 posA, D3DXVECTOR2 posB){

	float ans;// 答え格納用
	ans = sqrt((posA.x - posB.x)*(posA.x - posB.x) + (posA.y - posB.y)*(posA.y - posB.y));
	return ans;
}





// 後に追加よてい

//======================================================================
//	
//		円と四角のあたり判定
//
//		引数
//		circlePos	円の中心座標
//		radius		円の半径
//		quadPos		四角形座標
//		quadSize	四角形のサイズ
//
//======================================================================
//bool CheckCollisionCircleToQuad2(D3DXVECTOR2 circlePos, float radius, D3DXVECTOR2 quadPos, D3DXVECTOR2  quadSize){
//
//
//	//-----変数宣言-----
//	float Xc, Yc;		//円の中心座標
//	float X1, Y1;		//四角形の左上座標
//	float X2, Y2;		//四角形の左上座標
//	float r;			//円の半径
//
//	//-----値の代入-----
//	Xc = circlePos.x;
//	Yc = circlePos.y;
//	X1 = quadPos.x - quadSize.x / 2.0f;
//	Y1 = quadPos.y - quadSize.y / 2.0f;
//	X2 = quadPos.x + quadSize.x / 2.0f;
//	Y2 = quadPos.y + quadSize.y / 2.0f;
//	r = radius;
//
//
//	//向きはとらずにあたっているかどうかだけ
//	if ((Xc >= X1) && (Xc <= X2) && (Yc >= Y1 - r) && (Yc <= Y2 - r) || (Xc <= X2 + r) && (Xc >= X1 - r)
//		&& (Yc >= Y1) && (Yc <= Y2) || (X1 - Xc)*(X1 - Xc) + (Y1 - Yc)*(Y1 - Yc) < r*r ||
//		(X2 - Xc)*(X2 - Xc) + (Y1 - Yc)*(Y1 - Yc) < r*r || (X2 - Xc)*(X2 - Xc) + (Y2 - Yc)*(Y2 - Yc) < r*r
//		|| (X1 - Xc)*(X1 - Xc) + (Y2 - Yc)*(Y2 - Yc) < r*r){
//
//		return true;
//
//	}
//
//	//当たらなかったとき
//	return false;
//}
//
////======================================================================
////	
////		円と四角のあたり判定
////
////		引数
////		circlePos	円の中心座標
////		radius		円の半径
////		quadPos		四角形座標
////		quadSize	四角形のサイズ
////
////======================================================================
//int CheckCollisionCircleToQuad(D3DXVECTOR2 circlePos, float radius ,D3DXVECTOR2 quadPos, D3DXVECTOR2  quadSize){
//
//
//	//-----変数宣言-----
//	float Xc, Yc;		//円の中心座標
//	float X1, Y1;		//四角形の左上座標
//	float X2, Y2;		//四角形の左上座標
//	float r;			//円の半径
//
//	//-----値の代入-----
//	Xc = circlePos.x;
//	Yc = circlePos.y;
//	X1 = quadPos.x - quadSize.x / 2.0f;
//	Y1 = quadPos.y - quadSize.y / 2.0f;
//	X2 = quadPos.x + quadSize.x / 2.0f;
//	Y2 = quadPos.y + quadSize.y / 2.0f;
//	r = radius;
//
//
//	//----上----
//	if ((Xc >= X1) && (Xc <= X2) && (Yc >= Y1 - r) && (Yc <= Y2))//Y1->Y2
//		return COL_UP;
//
//	//----下----
//	if ((Xc >= X1) && (Xc <= X2) && (Yc <= Y2 + r) && (Yc >= Y1))//Y2->Y1
//		return COL_DOWN;
//
//	//----右----
//	if ((Xc <= X2 + r) && (Xc >= X1) && (Yc >= Y1) && (Yc <= Y2))//X2->X1
//		return COL_RIGHT;
//
//	//----左----
//	if ((Xc >= X1 - r) && (Xc <= X2) && (Yc >= Y1) && (Yc <= Y2))//X1->x2
//		return COL_LEFT;
//
//	//当たらなかったとき
//	return false;
//}
//
////======================================================================
////	
////		四角と四角のあたり判定
////
////		引数
////		オブジェクト1判定用パラメータ,オブジェクト2判定用パラメータ
////
////======================================================================
//bool CheckCollisionQuadToQuad(tQuadCollider q1, tQuadCollider q2){
//
//	//左上座標格納
//	float Quad1_X = q1.pos.x - q1.size.x / 2.0f;
//	float Quad2_X = q2.pos.x - q2.size.x / 2.0f;
//
//	float Quad1_Y = q1.pos.y - q1.size.y / 2.0f;
//	float Quad2_Y = q2.pos.y - q2.size.y / 2.0f;
//
//	if (Quad2_X <= Quad1_X + q1.size.x &&
//		Quad2_X + q2.size.x >= Quad1_X &&
//		Quad2_Y <= Quad1_Y + q1.size.y &&
//		Quad2_Y + q2.size.y >= Quad1_Y){
//
//		return true;
//
//	}
//
//	return false;
//}

