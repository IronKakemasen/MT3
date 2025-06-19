#include "Rail.h"

void Rail::Update()
{
	int k = 0;
	for (size_t i = 1; i <= numCorners; i++)
	{
		//配置する点の数
		for (float t = dt; t < 1.0f; t += dt,++k)
		{
			//終点
			Vector4<float> endPoint = GetComputedNum(i, t) + setPos;
			//ControllPoints(endPoint, t,(int)i);
			pointBox[k]->trans.pos = endPoint;
			pointBox[k]->Update();
		}
	}
}

void Rail::DrawPoints(Matrix4 vpMat_, Matrix4 viewportMat_)
{
	for (auto itr = pointBox.begin(); itr != pointBox.end(); ++itr)
	{
		(*itr)->Render(vpMat_, viewportMat_, { 0,0,0,1 });
	}

}

void Rail::Debug()
{
	ImGui::Begin("Rail");
	ImGui::DragFloat("tension", &tension,0.01f);
	ImGui::End();
}

Rail::Rail()
{
	Set(0.025f, 4,30.0f,{0,5,0,1.0f});
	float divAng = 360.0f / numCorners;

	//制御点の初期化
	for (int i = -1; i <= numCorners + 1; i++)
	{
		float radian = GetConvertedDegree(45.0f + divAng * (float)i);
		Vector4<float> tmp = { sinf(radian) * radius ,0.0f,-cosf(radian) * radius,1.0f };
		points.emplace_back(tmp);
	}

	for (int i = 0; i < kNumModel; ++i)
	{
		pointBox.emplace_back(new Cube(1, 1, 1, { 0,0,0,1 }));
	}
}

void Rail::ControllPoints(Vector4<float>& edPoint, float rate, int No)
{
	No;
	float kPi = 3.14159265359f;
	edPoint.y += cosf(kPi*rate) ;
}

