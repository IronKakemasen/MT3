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


const char kWindowTitle[] = "Title";

float t = 0.0f;

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
	//立方体のオリジン
	Cube cube1(1, 1, 1, { 1,0,2.0f,1 });
	Cube cube2(1, 1, 1, { -1,0,2.0f,1 });


	Sphere sphere1(1.0f, {0,0,1,1});
	sphere1.current_color = { 255,255,255,255 };

	MyRectangle rect;
	rect.trans.pos = { 0,2,1,1 };
	Vector4<float> normal = { 0,1,0,1 };
	Vector4<float> pointA = GetPerpendiculer(normal);
	Vector4<float> pointB = pointA * -1.0f;
	Vector4<float> crossVec = normal.GetCross(pointA);
	Vector4<float> reversedCrossVec = crossVec * -1.0f;

	rect.localShape.LT = pointA;
	rect.localShape.RT = crossVec;
	rect.localShape.RB = pointB;
	rect.localShape.LB = reversedCrossVec;

	Segment segAB = { {-1.0f,0.0f,1.0f,1.0f},{1.0f,2.0f,1.0f,1.0f} };

	//ゲームオブジェクトを管理する箱			
	ObjectManager objManager; 
	objManager.RegisterAsGameObject(camera->GetAddress());

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

		cube1.Update();
		Rect3D thisRect;
		thisRect.SetCube(cube1.Get_MyPos(), cube1.cubeShape.width, cube1.cubeShape.height, cube1.cubeShape.depth);
		sphere1.Update();
		Vector3 min = { thisRect.left,thisRect.bottom,thisRect.front };
		Vector3 max = { thisRect.right,thisRect.top,thisRect.back };

		if (CollisionDetection::CubeAndSphere(min, max, sphere1.Get_MyPos(), sphere1.radius))
		{
			cube1.current_color = { 255,0,0,255 };
			sphere1.current_color = { 255,0,0,255 };
		}

		else
		{
			cube1.current_color = { 0,0,255,255 };
			sphere1.current_color = { 0,0,255,255 };

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


		ImGui::Begin("cube1");
		cube1.Debug();
		ImGui::End();

		ImGui::Begin("sphere1");
		sphere1.Debug();
		ImGui::End();





		
#endif // DEBUG

		//================================================描画=====================================================
		sphere1.Render(Camera::VpMat, Camera::ViewportMat, Camera::Normalized_cVec);
		cube1.Render(Camera::VpMat, Camera::ViewportMat, Camera::Normalized_cVec);







		//=======================================インスタンス化(とりまmainで)=====================================================

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
