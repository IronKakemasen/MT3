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

	Triangle(Vector4<float> Tv_, Vector4<float> Rv_, Vector4<float> Lv_, Vector4<float> pos_)
	{
		renderShape.SetVertex(Tv_, Rv_, Lv_);
		name = "Triangle[" + std::to_string(instantiatedCounter) + "]Copy";
		updatePriNo = 1;
		trans.pos = pos_;
		current_color = { 0,200,50,255 };
	}

	~Triangle() {};


	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Render(Matrix4 vpMat, Matrix4 viewportMat, Vector4<float> camerDir) override;

	Matrix4 Get_MyMat() { return trans.mat; };
	Vector4<float> Get_MyPos() { return trans.pos; };



#if defined(_DEBUG)
	virtual void Debug() override;
#endif // DEBUG


};

