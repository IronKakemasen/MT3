#pragma once
#include "Catmull.h"

class Rail : public CatmullBehavior
{
private:

public:
	virtual void Update() override;
	virtual void DrawPoints(Matrix4 vpMat_, Matrix4 viewportMat_) override;
	virtual void Initialize() override{};
	virtual void Debug()override;
	virtual void ControllPoints(Vector4<float>& edPoint, float rate, int No)override;

	Rail();

};

