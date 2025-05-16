#include "Sphere.h"

void Sphere::Update()
{
	//SRT行列をセット
	trans.mat = Get_SRTMat3D({ commonScale,commonScale,commonScale,1.0f },
		trans.rotateTheta, trans.pos);

}

void Sphere::Render(Mat4 vpMat, Mat4 viewportMat, [[maybe_unused]] Vec4<float> camerDir)
{
	float const kSubdivision = 24;
	float const delta_t = Torima::kPi / kSubdivision;
	float const delta_p = Torima::kPi * 2.0f / kSubdivision;

	auto VecConverter = [this](float cur_t, float delta_t, float cur_p, float delta_p, int type_)
	{
		Vec4<float> ret_vec;

		switch (type_)
		{
		case 0:
		{
			Mat4 const aConverter =
			{
				1.0f,0.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,0.0f,
				0.0f,0.0f,1.0f,0.0f,
				cosf(cur_t) * cosf(cur_p) * radius , sinf(cur_t) * radius , cosf(cur_t) * sinf(cur_p) * radius , 1.0f,
			};

			ret_vec = ret_vec.GetMultipliedByMat(aConverter);

			break;
		}//case0

		case 1:
		{
			Mat4 const bConverter =
			{
				1.0f,0.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,0.0f,
				0.0f,0.0f,1.0f,0.0f,
				cosf(cur_t + delta_t)* cosf(cur_p)* radius,sinf(cur_t + delta_t)* radius,
				cosf(cur_t + delta_t)* sinf(cur_p)* radius,1.0f,
			};

			ret_vec = ret_vec.GetMultipliedByMat(bConverter);

			break;
		}//case1

		case 2:
		{
			Mat4 const cConverter =
			{
				1.0f,0.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,0.0f,
				0.0f,0.0f,1.0f,0.0f,
				cosf(cur_t)* cosf(cur_p + delta_p)* radius,
				sinf(cur_t)* radius,cosf(cur_t)* sinf(cur_p + delta_p)* radius,1.0f,
			};

			ret_vec = ret_vec.GetMultipliedByMat(cConverter);

			break;

		}//case2

		}//end	

		return ret_vec;
	};

	//緯度の方向に分割(-0.5Pi <= cur_t <= 0.5Pi)
	for (uint8_t latIndex = 0; latIndex < kSubdivision; ++latIndex)
	{
		Vec4<float> p[3];

		//currentLat
		float cur_t = -Torima::kPi * 0.5f + delta_t * latIndex;

		//経度の方向に分割(0.0 <= cur_p <= 2Pi)
		for (uint8_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex)
		{
			//currentLon
			float cur_p = delta_p * lonIndex;

			//座標を変換
			for (int i = 0; i < 3; ++i)
			{
				//ローカル上の軌跡を計算
				p[i] = VecConverter(cur_t, delta_t, cur_p, delta_p, i);
			}

			//描画
			Drawin::DrawLine(p[0], p[2], current_color, kBlendModeNormal, 
				vpMat, viewportMat, trans.mat);
			Drawin::DrawLine(p[0], p[1], current_color, kBlendModeNormal,
				vpMat, viewportMat, trans.mat);


		}

	}


}

void Sphere::Initialize()
{

}

#if defined(_DEBUG)

void Sphere::Debug()
{
	if (ImGui::Button("isActive"))isActive = !isActive;
	ImGui::DragFloat4("Pos", reinterpret_cast<float*>(&trans.pos),0.05f);
	ImGui::DragFloat4("rotate", reinterpret_cast<float*>(&trans.rotateTheta), 0.5f);
	ImGui::DragFloat("commonScale", &commonScale, 0.01f);

}
#endif // DEBUG
