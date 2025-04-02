#include <Novice.h>
#include <vector>
#include <algorithm>
#include "VectorAndMat.h"
#include <iostream>
#include <functional>
#include "Camera.h"
#include "ObjectManager.h"


const char kWindowTitle[] = "Title";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, int(Torima::windowWidth), int(Torima::windowHeight));

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//キャメラのorigin
	Camera* original_camera = new Camera({ 0.0f,0.0f,0.0f,1.0f });
	//ゲームオブジェクトを管理する箱
	ObjectManager objManager;
	objManager.prefab.camera = original_camera;
	objManager.Instantiate2(*original_camera, { 600,1000,0.0f,1.0f });

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		for (auto const itr : objManager.GetUpdate_data())
		{
			(*itr).Update();

#if defined(_DEBUG)

			ImGui::Begin((*itr).name.c_str());
			(*itr).Debug();
			ImGui::End();

#endif // DEBUG


		}

		

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
