#pragma once
#include "BaseClass.h"
#include "ObjectManager.h"

class Camera:GameObject
{
private:

public:


	Camera() {};

	Camera(Vec4<float> pos_)
	{
		updatePriNo = 0;
		renderPriNo = 0;
		name = "camera";
		trans.pos = pos_;
		colRect.SetVertex(Torima::windowWidth, Torima::windowHeight);
	}


	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Render() override;
	virtual void GetOwnMatrix() override;

#if defined(_DEBUG)
		virtual void Debug() override;
#endif // DEBUG


};

