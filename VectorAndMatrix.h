#pragma once
#include <math.h>
#include "GlobalVariable.h"

enum ProjectionType
{
	kPerspective,
	kParallel
};

enum AffineMatrixType
{
	kSRT,
	kSTR
};


//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
//Matrix3x3　　　　 　　　　　　　　　　　　　　　　　　　　□
//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
struct Matrix3
{
	float m[3][3] =
	{
		{1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f},
	};

	Matrix3 operator+=(Matrix3 other);
	Matrix3 operator-=(Matrix3 other);

	Matrix3() {};

	Matrix3(float zero_)
	{
		zero_;

		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
	};

	Matrix3(float a0, float a1, float a2, float a3, float a4, float a5,
		float a6, float a7, float a8)
	{
		m[0][0] = a0; m[0][1] = a1; m[0][2] = a2;
		m[1][0] = a3; m[1][1] = a4; m[1][2] = a5;
		m[2][0] = a6; m[2][1] = a7; m[2][2] = a8;
	}

	Matrix3 GetMultiply(Matrix3* const other);
};


//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
//Matrix4x4　　　　 　　　　　　　　　　　　　　　　　　　　□
//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
class Matrix4
{

public:

	float m[4][4] =
	{
		{1.0f,0.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f,0.0f},
		{0.0f,0.0f,1.0f,0.0f},
		{0.0f,0.0f,0.0f,1.0f},
	};

	Matrix4 operator+=(Matrix4 other);
	Matrix4 operator-=(Matrix4 other);

	Matrix4() {};

	Matrix4(float zero_)
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
		zero_;
	};

	Matrix4(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9,
		float a10, float a11, float a12, float a13, float a14, float a15)
	{
		m[0][0] = a0; m[0][1] = a1; m[0][2] = a2; m[0][3] = a3;
		m[1][0] = a4; m[1][1] = a5; m[1][2] = a6; m[1][3] = a7;
		m[2][0] = a8; m[2][1] = a9; m[2][2] = a10; m[2][3] = a11;
		m[3][0] = a12; m[3][1] = a13; m[3][2] = a14; m[3][3] = a15;

	}

	//マトリックス同士の積
	Matrix4 Multiply(Matrix4 const& other);
	//****************************************
	//https://suzulang.com/inverse-matrix-44/
	//****************************************
	//4x4行列の行列式を返す関数
	float GetDeterminant4x4();
	//4x4行列の逆行列を取得
	Matrix4 GetInversed();

};



//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
//Vector2  　　　　 　　　　　　　　　　　　　　　　　　　　□
//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
struct Vector2
{
	float u;
	float v;

	Vector2() {};
	Vector2(float entries[2]) : u(entries[0]), v(entries[1]) {}
	Vector2(float u_, float v_) : u(u_), v(v_) {}

};

//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
//Vector3　　　　 　　　　　　　　　　　　　　　　　　　　  □
//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
struct Vector3
{
	float x;
	float y;
	float z;

	Vector3() {}
	Vector3(float entries[3]) : x(entries[0]), y(entries[1]), z(entries[2]) {}
	Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

	Vector3 GetMultiply(Matrix3 src_mat);
};


//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
//Vector4  　　　　 　　　　　　　　　　　　　　　　　　　　□
//□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
template<typename T>
class Vector4
{

public:

	T x = 0;
	T y = 0;
	T z = 0;
	T w = 1;

	//============Constractor==============
	Vector4() {};
	Vector4(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}
	Vector4(T entries[4]) : x(entries[0]), y(entries[1]), z(entries[2]), w(entries[3]) {}
	//=====================================

	Vector4<float> operator+=(float const addNum);
	Vector4<float> operator=(float const num);

	//大きさをセット
	float GetMagnitutde();
	//正規化ベクトルを返す
	Vector4<float> GetNormalizedVec();
	//内積を計算して返す
	float GetDotProductionResult(Vector4<float> src1_Vector4, Vector4<float> src2_Vector4);
	//差分単位ベクトルを返す
	Vector4<float> GetNormalizedDiffVector4(Vector4<float> dst_pos, Vector4<float> my_pos);
	//マトリックスとベクタの積
	Vector4<float> GetMultiply(Matrix4 src_mat);
	//クロス積を返す
	Vector4<float> GetCross(Vector4<float> other);

};

//==================================Operand============================================================
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓Operand↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
template<typename T>
Vector4<T> operator+(Vector4<T> const& lVec, Vector4<T> const& rVec2)
{
	Vector4<T> ret_vec = { lVec.x + rVec2.x,lVec.y + rVec2.y ,lVec.z + rVec2.z ,1 };

	return ret_vec;
}

template<typename T>
Vector4<T> operator-(Vector4<T> const& lVec, Vector4<T> const& rVec2)
{
	Vector4<T> ret_vec = { lVec.x - rVec2.x,lVec.y - rVec2.y ,lVec.z - rVec2.z ,1 };

	return ret_vec;
}

template<typename T>
Vector4<T> operator*(Vector4<T> const& dst_vec, T const multipleNum)
{
	Vector4<T> ret_vec = { dst_vec.x * multipleNum,dst_vec.y * multipleNum ,dst_vec.z * multipleNum ,1 };

	return ret_vec;
}

Matrix4 operator*(Matrix4 const& dst_mat, float multipleNum);
Vector3 operator*(Vector3 const& dst_vec, float const multipleNum);
Vector3 operator*(Vector3 const& dst_vec, float const multipleNum);



//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑Operator↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
//==================================Operator============================================================


//SRT行列の作成・取得
Matrix4 Get_SRTMat3D(const Vector4<float>& scale_, const Vector4<float>& rotateTheta_,
	const Vector4<float>& translate_);
//STR行列の作成・取得
Matrix4 Get_STRMat3D(const Vector4<float>& scale_, const Vector4<float>& movementTheta_,
	const Vector4<float>& translate_);
//正射影行列3D
Matrix4 Get_Orthographic3D(
	const float l_, const float r_,
	const float t_, const float b_,
	const float zn_, const float zf_);
//ビューポート変換3D
Matrix4 Get_ViewportTransformation3D(
	const float left_ = 0.0f, const float top_ = 0.0f,
	const float windowWidth_ = Torima::windowWidth, const float windowHeight_ = Torima::windowHeight,
	const float minDepth_ = 0.0f, const float maxDepth_ = 1.0f);
//透視投影行列
Matrix4 Get_PerspectiveFOV(float fovY_, float aspectRatio_, float nearClip_ = 0.1f, float farClip_ = 1000.0f);
//VP行列
Matrix4 Get_VPMat(Matrix4 cameraMat, Vector4<float> cameraPos = {0,0,0,1},ProjectionType type_ = kPerspective );
//STR行列の作成・取得
Matrix3 Get_SRTMat2D(const float& delta_scaleX_, const float& delta_scaleY_, const float& delta_rotateTheta_,
	const Vector3& delta_pos_);

static Vector4<float> right = { 1.0f,0.0f,0.0f,1.0f };
static Vector4<float> up = { 0.0f,1.0f,0.0f,1.0f };
static Vector4<float> zAxis = { 0.0f,0.0f,1.0f,1.0f };
