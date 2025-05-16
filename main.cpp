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
	Camera* original_camera = new Camera({ 0.0f,2.5f,-1.5f,1.0f });
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

	Sphere sphere2(1.0f, { 1,0,0,1 });
	sphere2.current_color = { 255,255,255,255 };


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
		sphere2.Update();
		if (sphere1.SphereCollision(sphere2))
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

		ImGui::Begin("S1");
		sphere1.Debug();
		ImGui::End();

		ImGui::Begin("S2");
		sphere2.Debug();
		ImGui::End();


		
#endif // DEBUG

		//================================================描画=====================================================
		sphere1.Render(Camera::VpMat, Camera::ViewportMat, Camera::Normalized_cVec);
		sphere2.Render(Camera::VpMat, Camera::ViewportMat, Camera::Normalized_cVec);









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
