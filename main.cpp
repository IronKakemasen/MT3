#include <Novice.h>
#include <vector>
#include <algorithm>
#include "VectorAndMatrix.h"
#include <iostream>
#include <functional>
#include "Camera.h"
#include "ObjectManager.h"
#include "Triangle.h"
#include "MyRectangle.h"
#include "MyDebug.h"
#include "Cube.h"
#include "Sphere.h"
#include "Collision.h"
#include "KadaiHierarchy.h"
#include "SpringAndBall.h"
#include "CircularMotion.h"

const char kWindowTitle[] = "Title";



Vector4<float> GetPerpendiculer(Vector4<float> point_)
{
	Vector4<float> ret_vec;

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

bool IsCollidedWithPlane(float radius,Vector4<float>sphere_cPos_,Vector4<float> normal_, Vector4<float> pos_)
{
	bool ret = false;

	float d = normal_.GetDotProductionResult(normal_, pos_);
	float nande = sphere_cPos_.GetDotProductionResult(normal_, sphere_cPos_);
	float d2 = nande - d;
	

	if (fabsf(d2) <= radius)
	{
		ret = true;
	}
	return ret;
}

bool IsCollidedWithSegment(Vector4<float> plane_pos_, Vector4<float> plane_normal_, 
	Vector4<float> segStart_, Vector4<float> segEnd_)
{
	bool ret = false;

	Vector4<float> start2End = segEnd_ - segStart_;
	float t = 0.0f;

	float d = plane_normal_.GetDotProductionResult(plane_normal_, plane_pos_);
	float startDotNormal = segStart_.GetDotProductionResult(segStart_, plane_normal_);
	float segVecDotNormal = start2End.GetDotProductionResult(start2End, plane_normal_);

	if (segVecDotNormal != 0)	t = (d - startDotNormal) / segVecDotNormal;
	else return false;

	if (t >= 0.0f && t <= 1.0)
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
	//キャメラ
	Camera* camera = new Camera({ 0.0f,2.5f,-2.5f,1.0f });


	//ゲームオブジェクトを管理する箱			
	ObjectManager objManager; 
	objManager.RegisterAsGameObject(camera->GetAddress());

	CircularMotionSimulation c;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		//===============================================更新処理=================================================
		//オブジェクトの更新処理（カメラ含む）
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



		c.UpdateAndDraw(Camera::VpMat, Camera::ViewportMat);



		
#endif // DEBUG

		//================================================描画=====================================================





		//===;====================================インスタンス化(とりまmainで)=====================================================

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) 
		{
			break;
		}
	}


	//ゲームオブジェクトの解放
	objManager.Destroy();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
