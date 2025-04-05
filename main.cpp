#include <Novice.h>
#include <vector>
#include <algorithm>
#include "VectorAndMat.h"
#include <iostream>
#include <functional>
#include "Camera.h"
#include "ObjectManager.h"


const char kWindowTitle[] = "Title";


struct Triangle
{
	TriangleShape renderShape;
	Transform trans;

	Triangle(Vec4<float> Tv_, Vec4<float> Rv_, Vec4<float> Lv_,Vec4<float> pos_)
	{
		renderShape.SetVertex(Tv_, Rv_, Lv_);
		trans.pos = pos_;
	}
};

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
	objManager.Instantiate2(*original_camera);

	//テスト三角形
	Vec4<float> pT = { 0,200,1.0f,1 };
	Vec4<float> pL = { -200,0, 1.0f,1 };
	Vec4<float> pR = { 200,0,1.0f,1 };
	Vec4<float> pos_ = { 0.0f,0.0f,500.0f,1.0f};
	//コンストラクタでローカル座標の設定
	Triangle testTri(pT, pL, pR, pos_);


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		//オブジェクトの更新処理（カメラ含む）
		for (auto const itr : objManager.GetObjData())
		{
			(*itr).Update();
#if defined(_DEBUG)

			ImGui::Begin((*itr).name.c_str());
			(*itr).Debug();
			ImGui::End();

#endif // DEBUG
		}

		//vp行列の作成
		Camera camera = *reinterpret_cast<Camera*>(objManager.GetObjData()[0]);
		
		Mat4 vPMat = Get_VPMat(camera.Get_MyPos(), camera.Get_MyMat());
		//viewport行列の作成
		static Mat4 const viewportMat = Get_ViewportTransformation3D();
		


		//三角形と行列たちの演算
		//SRT行列をセット
		testTri.trans.mat = Get_SRTMat3D(testTri.trans.scale, testTri.trans.rotateTheta, testTri.trans.pos);

		//World変換
		testTri.renderShape.Tv = testTri.renderShape.local_Tv.GetMultipliedByMat(testTri.trans.mat);
		testTri.renderShape.Lv = testTri.renderShape.local_Lv.GetMultipliedByMat(testTri.trans.mat);
		testTri.renderShape.Rv = testTri.renderShape.local_Rv.GetMultipliedByMat(testTri.trans.mat);

		//同次座標変換
		testTri.renderShape.Tv = testTri.renderShape.Tv.GetMultipliedByMat(vPMat);
		testTri.renderShape.Lv = testTri.renderShape.Lv.GetMultipliedByMat(vPMat);
		testTri.renderShape.Rv = testTri.renderShape.Rv.GetMultipliedByMat(vPMat);

		//perspectDivide
		Vec4<float> screenTv = 
		{
			testTri.renderShape.Tv.x / testTri.renderShape.Tv.w,
			testTri.renderShape.Tv.y / testTri.renderShape.Tv.w,
			testTri.renderShape.Tv.z / testTri.renderShape.Tv.w ,
			1.0f
		};
		Vec4<float> screenLv =
		{
			testTri.renderShape.Lv.x / testTri.renderShape.Lv.w,
			testTri.renderShape.Lv.y / testTri.renderShape.Lv.w,
			testTri.renderShape.Lv.z / testTri.renderShape.Lv.w ,
			1.0f
		};
		Vec4<float> screenRv =
		{
			testTri.renderShape.Rv.x / testTri.renderShape.Rv.w,
			testTri.renderShape.Rv.y / testTri.renderShape.Rv.w,
			testTri.renderShape.Rv.z / testTri.renderShape.Rv.w ,
			1.0f
		};

									
		//ビューポート変換
		screenTv = screenTv.GetMultipliedByMat(viewportMat);
		screenLv = screenLv.GetMultipliedByMat(viewportMat);
		screenRv = screenRv.GetMultipliedByMat(viewportMat);

#if defined(_DEBUG)
		ImGui::Begin("Tri_Vertexes");
		ImGui::DragFloat4("Pos", reinterpret_cast<float*>(&testTri.trans.pos), 0.25f);
		ImGui::DragFloat4("T", reinterpret_cast<float*>(&testTri.renderShape.Tv), 0.25f);
		ImGui::DragFloat4("L", reinterpret_cast<float*>(&testTri.renderShape.Lv), 0.25f);
		ImGui::DragFloat4("R", reinterpret_cast<float*>(&testTri.renderShape.Rv), 0.25f);

		ImGui::End();
#endif // DEBUG

		//描画
		Novice::DrawTriangle(
			(int)screenTv.x, (int)screenTv.y,
			(int)screenLv.x, (int)screenLv.y,
			(int)screenRv.x, (int)screenRv.y,
			0x88FFAAFF, kFillModeSolid);





		




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
