#pragma once
#include "Cube.h"


//なつかしききゃとまる
struct CatmullBehavior
{
	//オブジェクトの基準座標
	Vector4<float> setPos;
	//制御点
	std::vector<Vector4<float>> points;
	std::vector<std::unique_ptr<Cube>> pointBox;

	//制御点の個数(実際には+3)
	float numCorners = 4;
	//張力（0.5できゃとまる曲線）
	float tension = 0.5f;
	float radius = 4.0f;
	float dt = 0.25f;
	float kNumModel = (1.0f / dt) * (numCorners + 3.0f);


	virtual void Update() = 0;
	virtual void DrawPoints(Matrix4 vpMat_, Matrix4 viewportMat_) = 0;
	virtual void Initialize() = 0;
	Vector4<float> GetComputedNum(size_t index_, float t_);
	CatmullBehavior() = default;
	void Set(float dt_, float numCorners_, float radius_, Vector4<float> setPos_);
	//補間された点を利用する（あなた次第）
	virtual void ControllPoints(Vector4<float>& edPoint, float rate, int No) = 0;


#ifdef _DEBUG
	virtual void Debug() = 0;
#endif // _DEBUG

	//virtual ~CatmullBehavior() = 0;
};

