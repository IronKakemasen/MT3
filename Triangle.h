#pragma once
#include "ObjectManager.h"


class Triangle:TriangleShape,GameObject
{
private:

	TriangleShape renderShape;
	inline static int instantiatedCounter = -1;

public:

	Triangle() {};

	Triangle(Triangle const& triangle_)
	{
		*this = triangle_;
		Triangle::instantiatedCounter++;
		name = "Triangle[" + std::to_string(instantiatedCounter) + "]Copy";
	};

	Triangle(Vec4<float> Tv_, Vec4<float> Rv_, Vec4<float> Lv_, Vec4<float> pos_)
	{
		renderShape.SetVertex(Tv_, Rv_, Lv_);
		name = "Triangle[" + std::to_string(instantiatedCounter) + "]Copy";
		updatePriNo = 1;
		trans.pos = pos_;
	}

	~Triangle() {};


	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Render(Mat4 vpMat, Mat4 viewportMat, Vec4<float> camerDir) override;

	Mat4 Get_MyMat() { return trans.mat; };
	Vec4<float> Get_MyPos() { return trans.pos; };



#if defined(_DEBUG)
	virtual void Debug() override;
#endif // DEBUG


};

