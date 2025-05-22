#pragma once
#include "BaseClass.h"
#include "ObjectManager.h"

class Camera:public GameObject
{
private:

	Vector4<float> LT;
	Vector4<float> RT;
	Vector4<float> LB;
	Vector4<float> RB;

public:

	//NAW
	inline static Matrix4 ViewportMat;
	inline static Matrix4 VpMat;
	inline static Vector4<float> Normalized_cVec;

	//Constructor
	Camera() {};

	Camera(Vector4<float> pos_)
	{
		updatePriNo = static_cast<int>(ObjectUpdatePriorityNo::kCamera);
		name = "Camera[" + std::to_string(count) + "]Copy";
		colRect.SetVertex(Torima::windowWidth, Torima::windowHeight);
		trans.pos = pos_;
		trans.rotateTheta.x = 180.0f / 5.0f;

	}

	//Destructor
	~Camera() {};

	Matrix4 Get_MyMat() { return trans.mat; };
	Vector4<float> Get_MyPos() { return trans.pos; };
	Camera* GetAddress()
	{
		return this;
	}

	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Render(Matrix4 vpMat, Matrix4 viewportMat, Vector4<float> camerDir) override;


#if defined(_DEBUG)
		virtual void Debug() override;
#endif // DEBUG

};

