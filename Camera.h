#pragma once
#include "BaseClass.h"
#include "ObjectManager.h"

class Camera:GameObject
{
private:

	Vec4<float> LT;
	Vec4<float> RT;
	Vec4<float> LB;
	Vec4<float> RB;

public:

	//💩
	inline static Mat4 ViewportMat;
	inline static Mat4 VpMat;
	inline static Vec4<float> Normalized_cVec;

	//Constructor
	Camera() {};

	Camera(Vec4<float> pos_)
	{
		count++;
		updatePriNo = 0;
		name = "Camera[" + std::to_string(count) + "]Copy";
		trans.pos = pos_;
		colRect.SetVertex(Torima::windowWidth, Torima::windowHeight);
	}

	//Destructor
	~Camera() {};

	Mat4 Get_MyMat() { return trans.mat; };
	Vec4<float> Get_MyPos() { return trans.pos; };


	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Render(Mat4 vpMat, Mat4 viewportMat, Vec4<float> camerDir) override;


#if defined(_DEBUG)
		virtual void Debug() override;
#endif // DEBUG

};

