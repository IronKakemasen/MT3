#pragma once
#include "ObjectManager.h"

class Sphere :GameObject
{
private:

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

	Sphere(float radius_, Vec4<float> pos_)
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
	virtual void Render(Mat4 vpMat, Mat4 viewportMat, Vec4<float> camerDir) override;

	Mat4 Get_MyMat() { return trans.mat; };
	Vec4<float> Get_MyPos() { return trans.pos; };


#if defined(_DEBUG)
	virtual void Debug() override;
#endif // DEBUG



};

