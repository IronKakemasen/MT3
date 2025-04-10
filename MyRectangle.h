#pragma once
#include "ObjectManager.h"

class MyRectangle :GameObject
{
private:

	RectShape localShape;
	inline static int instantiatedCounter = -1;

public:

	MyRectangle() {};

	MyRectangle(MyRectangle const& rectangle_)
	{
		*this = rectangle_;
		MyRectangle::instantiatedCounter++;
		name = "Rectangle[" + std::to_string(instantiatedCounter) + "]Copy";
	};

	MyRectangle(float width_, float height_,Vec4<float> pos_)
	{
		localShape.SetVertex(width_, height_);
		name = "Rectangle[" + std::to_string(instantiatedCounter) + "]Copy";
		updatePriNo = 2;
		trans.pos = pos_;
	}

	~MyRectangle() {};


	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Render(Mat4 vpMat, Mat4 viewportMat, Vec4<float> camerDir) override;

	Mat4 Get_MyMat() { return trans.mat; };
	Vec4<float> Get_MyPos() { return trans.pos; };



#if defined(_DEBUG)
	virtual void Debug() override;
#endif // DEBUG


};

