#pragma once
#include "ObjectManager.h"

class Cube : GameObject
{
	//底面 = 0 , 上面 = 1 , 側面(右) = 2 , 側面(左) = 3 , 側面(奥) = 4 , 側面(手前) = 5
	RectShape local_surfaces[6];
	inline static int instantiatedCounter = -1;

public:

	Cube() {};

	Cube(Cube const& cube_)
	{
		*this = cube_;
		Cube::instantiatedCounter++;
		name = "Cube[" + std::to_string(instantiatedCounter) + "]Copy";
	};

	Cube(float width_, float height_,float depth_, Vec4<float> pos_)
	{
		SetSurface(width_, height_, depth_);
		name = "Cube[" + std::to_string(instantiatedCounter) + "]Copy";
		updatePriNo = 3;
		trans.pos = pos_;
		current_color = { 255,150,150,255 };
	}

	~Cube() {};

	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Render(Mat4 vpMat, Mat4 viewportMat, Vec4<float> camerDir) override;

	Mat4 Get_MyMat() { return trans.mat; };
	Vec4<float> Get_MyPos() { return trans.pos; };

	void SetSurface(float width_, float height_, float depth_);

#if defined(_DEBUG)
	virtual void Debug() override;
#endif // DEBUG


};

