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
	Camera* original_camera = new Camera({ 0.0f,0.0f,1.0f,1.0f });
	//三角形のオリジン
	Triangle* original_triangle = new Triangle
	(
		{ 0.0f,200.0f,1.0f,1.0f },
		{ -200,0, 1.0f,1.0f },
		{ 200.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f,-100,500.0f,1.0f }
	);
	//四角形のオリジン
	MyRectangle* original_rectangle = new MyRectangle(100, 100, { 0,0,500,1 });
	//立方体のオリジン
	Cube* original_cube = new Cube(200, 200, 200, { 0,0,500,1 });


	//ゲームオブジェクトを管理する箱			
	ObjectManager objManager; 
	//プレハブ登録
	objManager.prefab.camera = original_camera;
	objManager.prefab.triangle = original_triangle;
	objManager.prefab.rectangle = original_rectangle;
	objManager.prefab.cube = original_cube;
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
#endif // DEBUG

		//================================================描画=====================================================
		//ゲームオブジェクト
		for (auto const itr : objManager.GetObjData())
		{
			if ((*itr).isActive) (*itr).Render(Camera::VpMat, Camera::ViewportMat,
				Camera::Normalized_cVec);
		}
		objManager.SetIsUpdating(0);



		//=======================================インスタンス化(とりまmainで)=====================================================

		for (auto& [key, value] : myDebug.prefabInsta.prefabDic)
		{
			if (value)
			{
				if (key == "Rectangle")
				{
					objManager.Instantiate2(*objManager.prefab.rectangle);
				}

				else if (key == "Triangle")
				{
					objManager.Instantiate2(*objManager.prefab.triangle);
				}

				else if (key == "Cube")
				{
					objManager.Instantiate2(*objManager.prefab.cube);
				}
				
				value = false;

			}
		}



		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) 
		{
			break;
		}
	}

	//💩
	if (objManager.prefab.camera != nullptr)delete objManager.prefab.camera;
	if (objManager.prefab.triangle != nullptr)delete objManager.prefab.triangle;
	if (objManager.prefab.rectangle != nullptr)delete objManager.prefab.rectangle;
	if (objManager.prefab.cube != nullptr)delete objManager.prefab.cube;

	//ゲームオブジェクトの解放
	objManager.Destroy();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
