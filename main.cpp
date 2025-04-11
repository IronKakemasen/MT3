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
	Camera* original_camera = new Camera({ 0.0f,160.0f,-70.0f,1.0f });
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
	Cube* original_cube = new Cube(100, 100, 100, { 0,0,500,1 });
	//球体のオリジン
	Sphere* original_sphere = new Sphere(200.0f, { 0,0,500,1 });


	//ゲームオブジェクトを管理する箱			
	ObjectManager objManager; 
	//プレハブ登録
	objManager.prefab.camera = original_camera;				//キャメラ
	objManager.prefab.triangle = original_triangle;			//三角形
	objManager.prefab.rectangle = original_rectangle;		//四角形
	objManager.prefab.cube = original_cube;					//直方体
	objManager.prefab.sphere = original_sphere;				//球体
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
		//NAW
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
				
				else if (key == "Sphere")
				{
					objManager.Instantiate2(*objManager.prefab.sphere);
				}

				value = false;

			}
		}

		Mat4 a = 
		{
			3.2f,0.7f,9.6f,4.4f,
			5.5f,1.3f,7.8f,2.1f,
			6.9f,8.0f,2.6f,1.0f,
			0.5f,7.2f,5.1f,3.3f
		};

		Mat4 b =
		{
			4.1f,6.5f,3.3f,2.2f,
			8.8f,0.6f,9.9f,7.7f,
			1.1f,5.5f,6.6f,0.0f,
			3.3f,9.9f,8.8f,2.2f
		};

		Mat4 c = a ;
		Mat4 d = a ;

		c += b;
		d -= b;

		ImGui::Begin("ADD");
		for (int i = 0; i < 4; ++i)
		{
			ImGui::DragFloat4(std::to_string(i).c_str(), reinterpret_cast<float*>(&c.m[i]));
		}
		ImGui::End();

		ImGui::Begin("Sub");
		for (int i = 0; i < 4; ++i)
		{
			ImGui::DragFloat4(std::to_string(i).c_str(), reinterpret_cast<float*>(&d.m[i]));
		}
		ImGui::End();

		ImGui::Begin("Multiple");
		for (int i = 0; i < 4; ++i)
		{
			ImGui::DragFloat4(std::to_string(i).c_str(), reinterpret_cast<float*>(&a.Multiply(b).m[i]));
		}
		ImGui::End();

		ImGui::Begin("inv_M1");
		for (int i = 0; i < 4; ++i)
		{
			ImGui::DragFloat4(std::to_string(i).c_str(), reinterpret_cast<float*>(&a.GetInversed().m[i]));
		}
		ImGui::End();

		ImGui::Begin("inv_M2");
		for (int i = 0; i < 4; ++i)
		{
			ImGui::DragFloat4(std::to_string(i).c_str(), reinterpret_cast<float*>(&b.GetInversed().m[i]));
		}
		ImGui::End();

		ImGui::Begin("identity_M1");
		for (int i = 0; i < 4; ++i)
		{
			ImGui::DragFloat4(std::to_string(i).c_str(), reinterpret_cast<float*>(&a.Multiply(a.GetInversed()).m[i]));
		}
		ImGui::End();

		auto transpose = [](Mat4 const& src)
			{
				Mat4 ret =
				{
					src.m[0][0],src.m[1][0],src.m[2][0],src.m[3][0],
					src.m[0][1],src.m[1][1],src.m[2][1],src.m[3][1],
					src.m[0][2],src.m[1][2],src.m[2][2],src.m[3][2],
					src.m[0][3],src.m[1][3],src.m[2][3],src.m[3][3],
				};

				return ret;
			};

		ImGui::Begin("transpose_M1");
		for (int i = 0; i < 4; ++i)
		{
			ImGui::DragFloat4(std::to_string(i).c_str(), reinterpret_cast<float*>(&transpose(a).m[i]));
		}
		ImGui::End();

		ImGui::Begin("transpose_M2");
		for (int i = 0; i < 4; ++i)
		{
			ImGui::DragFloat4(std::to_string(i).c_str(), reinterpret_cast<float*>(&transpose(b).m[i]));
		}
		ImGui::End();






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
