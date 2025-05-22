#pragma once
#include "ObjectManager.h"

class Sphere :public GameObject
{
public:

	inline static int instantiatedCounter = -1;
	float radius;
	float commonScale = 1.0f;

public:

	Sphere() {};

	Sphere(Sphere const& Sphere_)
	{
		*this = Sphere_;
		Sphere::instantiatedCounter++;
		name = "Sphere[" + std::to_string(instantiatedCounter) + "]Copy";
	};

	Sphere(float radius_, Vector4<float> pos_)
	{
		updatePriNo = 4;
		name = "Sphere[" + std::to_string(instantiatedCounter) + "]Copy";
		trans.pos = pos_;
		radius = radius_;
		current_color = { 100,100,100,255 };

	}

	~Sphere() {};

	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Render(Matrix4 vpMat, Matrix4 viewportMat, Vector4<float> camerDir) override;

	Matrix4 Get_MyMat() { return trans.mat; };
	Vector4<float> Get_MyPos() { return trans.pos; };
	bool SphereCollision(Sphere const& other_)
	{
		bool ret_flag = false;

		float sumRadius = radius + other_.radius;
		Vector4<float> diff = trans.pos - other_.trans.pos;
		float mag = diff.GetMagnitutde();
		if (mag <= sumRadius)
		{
			ret_flag = true;
		}

		return ret_flag;
	}

#if defined(_DEBUG)
	virtual void Debug() override;
#endif // DEBUG



};

