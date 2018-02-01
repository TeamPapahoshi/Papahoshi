//======================================================================
//	Collision.cpp
//	
//	概要＿：Collisionの処理
//	制作者：加藤　遼
//	
//======================================================================
#include "Collision.h"
#include "Sprite.h"
#include <cmath>	//少数の絶対値用
#include "MathEX.h"

using namespace std;

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

	//三角形の頂点
	m_tColBody.TriangleVertexPos[0] = D3DXVECTOR2(0.0f, 0.0f);	
	m_tColBody.TriangleVertexPos[1] = D3DXVECTOR2(0.0f, 0.0f);
	m_tColBody.TriangleVertexPos[2] = D3DXVECTOR2(0.0f, 0.0f);

	sprite.LoadTexture(TEXTURE_FILENAME_CIRCLE_COLLIDER);

	sprite.SetVtxColorA(100.0f);	// 半透明でセット
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
	}
	if (m_type == QUAD){
		sprite.SetPos(m_tColBody.QuadPos);
		sprite.SetSize(m_tColBody.QuadSize);
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

//====================================================================
//
//  円と三角の当たり判定
//
//====================================================================
bool cCollider::CheckCollisionCircleToTriangle(cCollider circle, cCollider triangle){

	//--------- 変数宣言 ----------
	D3DXVECTOR2 triVector[3];	//三角形を構成するベクトル
	D3DXVECTOR2 TtoCVector[3];	//三角形の頂点から円の中心点へ向かうベクトル
	int i, next;	//ループ用

	//------ ベクトルの計算 --------
	for (i = 0; i < 3; i++){
		//次の値を設定
		next = i + 1;
		if (next == 3)
			next = 0;

		//三角形を構成するベクトル　*** もしエラー出たらここの向きかえる *** うちが変えます！！
		triVector[i].x = triangle.GetCollider().TriangleVertexPos[next].x - triangle.GetCollider().TriangleVertexPos[i].x;
		triVector[i].y = triangle.GetCollider().TriangleVertexPos[next].y - triangle.GetCollider().TriangleVertexPos[i].y;
		//三角形の頂点から円の中心点へ向かうベクトル
		TtoCVector[i].x = circle.GetCollider().CirclePos.x - triangle.GetCollider().TriangleVertexPos[i].x;
		TtoCVector[i].y = circle.GetCollider().CirclePos.y - triangle.GetCollider().TriangleVertexPos[i].y;
	}
	//triVector[0].x = triangle.GetCollider().TriangleVertexPos[1].x - triangle.GetCollider().TriangleVertexPos[0].x;
	//triVector[0].y = triangle.GetCollider().TriangleVertexPos[1].y - triangle.GetCollider().TriangleVertexPos[0].y;
	//triVector[1].x = triangle.GetCollider().TriangleVertexPos[2].x - triangle.GetCollider().TriangleVertexPos[1].x;
	//triVector[1].y = triangle.GetCollider().TriangleVertexPos[2].y - triangle.GetCollider().TriangleVertexPos[1].y;
	//triVector[2].x = triangle.GetCollider().TriangleVertexPos[2].x - triangle.GetCollider().TriangleVertexPos[0].x;
	//triVector[2].y = triangle.GetCollider().TriangleVertexPos[2].y - triangle.GetCollider().TriangleVertexPos[0].y;


	//---------- 三角形の線分との当たり判定 --------------
	for (int i = 0; i < 3; i++){

		//次の値を設定
		next = i + 1;
		if (next == 3)
			next = 0;
		//判定
		/*
		① 線分の内側？
		　　V[n]・M[n]≧0（鋭角）且つV[n]・M[n+1]≦0（鈍角）で|V[n]×M[n]|/|V[n]|≦rならば衝突を起こしている。
		② 線分の外側の例外ケース
		　　①ではない時、(xc-xp[n])^2+(yc-yp[n])^2≦r^2もしくは(xc-xp[n+1])^2+(yc-yp[n+1])^2≦r^2ならば衝突を起こしている。
			*/
		//①
		if (VectorDotProduct(triVector[i], TtoCVector[i]) >= 0 &&
			VectorDotProduct(triVector[i], TtoCVector[next]) <= 0 &&
			fabs(VectorCrossProduct(triVector[i], TtoCVector[i])) / VectorSize(triVector[i]) <= circle.GetCollider().fRadius)
			return true;



		//②☆
		if ((circle.GetCollider().CirclePos.x - triangle.GetCollider().TriangleVertexPos[i].x) 
			* (circle.GetCollider().CirclePos.x - triangle.GetCollider().TriangleVertexPos[i].x) 
			+ (circle.GetCollider().CirclePos.y - triangle.GetCollider().TriangleVertexPos[i].y)
			* (circle.GetCollider().CirclePos.y - triangle.GetCollider().TriangleVertexPos[i].y) 
			<= circle.GetCollider().fRadius * circle.GetCollider().fRadius ||
			(circle.GetCollider().CirclePos.x - triangle.GetCollider().TriangleVertexPos[next].x)
			* (circle.GetCollider().CirclePos.x - triangle.GetCollider().TriangleVertexPos[next].x)
			+ (circle.GetCollider().CirclePos.y - triangle.GetCollider().TriangleVertexPos[next].y)
			* (circle.GetCollider().CirclePos.y - triangle.GetCollider().TriangleVertexPos[next].y)
			<= circle.GetCollider().fRadius * circle.GetCollider().fRadius)
			return true;

	}
	for (int i = 0; i < 3; i++){
		//次の値を設定
		next = i + 1;
		if (next == 3)
			next = 0;
		//③ ①と②がすべての辺で成り立っていない時に、
		//V[n]×M[n]≦0（線分の右側に頂点がある）
		//がすべての辺について言えるなら衝突を起こしている。
		//③
		float test = VectorCrossProduct(triVector[i], TtoCVector[i]);
		if (VectorCrossProduct(triVector[i], TtoCVector[i]) <= 0)
			return false;
	}
	return true;
}


float CalculateDistanceAtoB(D3DXVECTOR2 posA, D3DXVECTOR2 posB){

	float ans;// 答え格納用
	ans = sqrt((posA.x - posB.x)*(posA.x - posB.x) + (posA.y - posB.y)*(posA.y - posB.y));
	return ans;
}


// 線分と円の衝突判定
bool CheckCollisionCircleToLine(D3DXVECTOR2 circle, float Cradius, D3DXVECTOR2 leftpos, D3DXVECTOR2 rightpos){

	// 各ベクトル
	// 線分ベクトル 
	D3DXVECTOR2 VecS, VecA, VecB;
	float d;
	VecS = rightpos - leftpos;
	VecA = circle - leftpos;
	VecB = circle - rightpos;


	d = cCollider::VectorCrossProduct(VecS, VecA) / cCollider::VectorSize(VecS);

	if (d <= Cradius){

		if (cCollider::VectorDotProduct(VecA, VecS)*cCollider::VectorDotProduct(VecB, VecS) <= 0){
			return true;
		}
		if (Cradius > cCollider::VectorSize(VecA) || Cradius > cCollider::VectorSize(VecB)){

			return true;
		}
	}
	return false;

}

//=====================================================
//
//  ベクトルの内積を求める関数
//
//=====================================================
float cCollider::VectorDotProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2){

	//Dot = v1・v2 = x1*x2 + y1*y2 = |v1||v2|cos(θ)

	return (v1.x * v2.x + v1.y * v2.y);
}

//====================================================
//
//  ベクトルの外積を求める関数
//
//====================================================
float cCollider::VectorCrossProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2){

	//v1×v2= x1*y2-x2*y1 = |v1||v2|sin(θ)

	return (v1.x * v2.y - v2.x * v1.y);

}

//====================================================
//
// ベクトルの長さを求める関数
//
//====================================================
float cCollider::VectorSize(D3DXVECTOR2 v){

	//ルート(x二乗 + y二乗)

	return sqrt(v.x * v.x + v.y * v.y);

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

