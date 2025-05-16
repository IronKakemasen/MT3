#include <Novice.h>
#include <vector>
#include <algorithm>
#include "VectorAndMat.h"
#include <iostream>
#include <functional>
#include "Camera.h"
#include "ObjectManager.h"
#include "Triangle.h"
#include "MyRectangle.h"
#include "MyDebug.h"
#include "Cube.h"
#include "Sphere.h"

const char kWindowTitle[] = "Title";

Vec4<float> GetPerpendiculer(Vec4<float> point_)
{
	Vec4<float> ret_vec;

	if (point_.x != 0.0f || point_.y != 0.0f)
	{
		ret_vec = { -point_.y ,point_.x,0.0f,1.0f };
	}

	else
	{
		ret_vec = { 0.0f ,-point_.z,point_.y,1.0f };
	}

	return ret_vec;
}

bool IsCollidedWithPlane(float radius,Vec4<float>cPos_,Vec4<float> normal_, Vec4<float> pos_)
{
	bool ret = false;
	float d = normal_.GetDotProductionResult(normal_,pos_);
	float d2 = cPos_.GetDotProductionResult(normal_, cPos_) - d;

	if (fabsf(d2) >= radius)
	{
		ret = true;
	}

	return ret;
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, int(Torima::windowWidth), int(Torima::windowHeight));

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//BaseDebugger
	MyDebug myDebug;
	//キャメラのorigin
	Camera* original_camera = new Camera({ 0.0f,2.5f,-2.5f,1.0f });
	//三角形のオリジン
	//Triangle* original_triangle = new Triangle
	//(
	//	{ 0.0f,1.0f,0.0f,1.0f },
	//	{ -1.0f, 0.0f,0.0f ,1.0f},
	//	{ 1.0f, 0.0f, 0.0f, 1.0f },
	//	{ 0.0f,0.0f,2.0f,1.0f }
	//);
	//四角形のオリジン
	//MyRectangle* original_rectangle = new MyRectangle(1, 1, { 0,0,2.0f,1 });
	//立方体のオリジン
	//Cube* original_cube = new Cube(1, 1, 1, { 0,0,2.0f,1 });
	Sphere sphere1(1.0f, {-1,0,0,1});
	sphere1.current_color = { 255,255,255,255 };
	MyRectangle rect;
	rect.trans.pos = { 0,2,-1,1 };

	//ゲームオブジェクトを管理する箱			
	ObjectManager objManager; 
	//プレハブ登録
	objManager.prefab.camera = original_camera;				//キャメラ
	//インスタンス化(カメラだけ)
	objManager.Instantiate2(*original_camera);


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		//===============================================更新処理=================================================
		//オブジェクトの更新処理（カメラ含む）
		objManager.SetIsUpdating(1);
		for (auto const itr : objManager.GetObjData())
		{
			if((*itr).isActive) (*itr).Update();
		}

		sphere1.Update();
		Vec4<float> normal = { 0,1,0,1 };
		Vec4<float> originP = { 0,0,0,1 };

		Vec4<float> pointA = GetPerpendiculer(normal);
		Vec4<float> pointB = pointA * -1.0f;
		//Vec4<float> A2origin = originP - pointA;
		//Vec4<float> origin2normal= normal - originP;

		Vec4<float> crossVec = normal.GetCross(pointA);
		Vec4<float> reversedCrossVec = crossVec * -1.0f;

		rect.localShape.LT = pointA ;
		rect.localShape.RT = crossVec ;
		rect.localShape.RB = pointB;
		rect.localShape.LB = reversedCrossVec;
		rect.Update();

		if (IsCollidedWithPlane(sphere1.radius, sphere1.trans.pos, normal, rect.trans.pos))
		{
			sphere1.current_color = { 255,0,0,255 };
		}

		else
		{
			sphere1.current_color = { 255,255,255,255 };

		}

		//===============================================デバッグ=================================================
#if defined(_DEBUG)
		ImGui::Begin("iroiro");
		for (int i = 0; i < myDebug.kFuncSum; ++i)
		{
			myDebug.myDebugFuncs[i]();
		}
		ImGui::End();


		if (DebugSwitcher::buttons["GameObj"])
		{
			for (auto const itr : objManager.GetObjData())
			{
				ImGui::Begin((*itr).name.c_str());
				(*itr).Debug();
				ImGui::End();
			}
		}

		ImGui::Begin("P1");
		rect.Debug();
		ImGui::End();



		
#endif // DEBUG

		//================================================描画=====================================================
		sphere1.Render(Camera::VpMat, Camera::ViewportMat, Camera::Normalized_cVec);
		rect.Render(Camera::VpMat, Camera::ViewportMat, Camera::Normalized_cVec);








		//=======================================インスタンス化(とりまmainで)=====================================================

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) 
		{
			break;
		}
	}

	//NAW
	if (objManager.prefab.camera != nullptr)delete objManager.prefab.camera;
	if (objManager.prefab.triangle != nullptr)delete objManager.prefab.triangle;
	if (objManager.prefab.rectangle != nullptr)delete objManager.prefab.rectangle;
	if (objManager.prefab.cube != nullptr)delete objManager.prefab.cube;
	if (objManager.prefab.sphere != nullptr)delete objManager.prefab.sphere;

	//ゲームオブジェクトの解放
	objManager.Destroy();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
