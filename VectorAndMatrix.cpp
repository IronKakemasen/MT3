#include "VectorAndMatrix.h"

//[ Matrix3 ]
Matrix3 Matrix3::operator+=(Matrix3 other)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			m[i][k] += other.m[i][k];
		}
	}

	return *this;
}
Matrix3 Matrix3 ::operator-=(Matrix3 other)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			m[i][k] -= other.m[i][k];
		}
	}

	return *this;
}
Matrix3 Matrix3::GetMultiply(Matrix3* const other)
{
	Matrix3 ret_mat;

	ret_mat.m[0][0] = m[0][0] * other->m[0][0] + m[0][1] * other->m[1][0] + m[0][2] * other->m[2][0];
	ret_mat.m[0][1] = m[0][0] * other->m[0][1] + m[0][1] * other->m[1][1] + m[0][2] * other->m[2][1];
	ret_mat.m[0][2] = m[0][0] * other->m[0][2] + m[0][1] * other->m[1][2] + m[0][2] * other->m[2][2];
	ret_mat.m[1][0] = m[1][0] * other->m[0][0] + m[1][1] * other->m[1][0] + m[1][2] * other->m[2][0];
	ret_mat.m[1][1] = m[1][0] * other->m[0][1] + m[1][1] * other->m[1][1] + m[1][2] * other->m[2][1];
	ret_mat.m[1][2] = m[1][0] * other->m[0][2] + m[1][1] * other->m[1][2] + m[1][2] * other->m[2][2];
	ret_mat.m[2][0] = m[2][0] * other->m[0][0] + m[2][1] * other->m[1][0] + m[2][2] * other->m[2][0];
	ret_mat.m[2][1] = m[2][0] * other->m[0][1] + m[2][1] * other->m[1][1] + m[2][2] * other->m[2][1];
	ret_mat.m[2][2] = m[2][0] * other->m[0][2] + m[2][1] * other->m[1][2] + m[2][2] * other->m[2][2];

	return ret_mat;
}

//[ Matrix4 ]
Matrix4 Matrix4::operator+=(Matrix4 other)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int k = 0; k < 4; ++k)
		{
			m[i][k] += other.m[i][k];
		}
	}

	return *this;
}
Matrix4 Matrix4::operator-=(Matrix4 other)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int k = 0; k < 4; ++k)
		{
			m[i][k] -= other.m[i][k];
		}
	}

	return *this;
}
Matrix4 Matrix4::Multiply(Matrix4 const& other)
{
	Matrix4 ret_mat;

	ret_mat.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] +
		m[0][2] * other.m[2][0] + m[0][3] * other.m[3][0];
	ret_mat.m[0][1] = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] +
		m[0][2] * other.m[2][1] + m[0][3] * other.m[3][1];
	ret_mat.m[0][2] = m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] +
		m[0][2] * other.m[2][2] + m[0][3] * other.m[3][2];
	ret_mat.m[0][3] = m[0][0] * other.m[0][3] + m[0][1] * other.m[1][3] +
		m[0][2] * other.m[2][3] + m[0][3] * other.m[3][3];

	ret_mat.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] +
		m[1][2] * other.m[2][0] + m[1][3] * other.m[3][0];
	ret_mat.m[1][1] = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] +
		m[1][2] * other.m[2][1] + m[1][3] * other.m[3][1];
	ret_mat.m[1][2] = m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] +
		m[1][2] * other.m[2][2] + m[1][3] * other.m[3][2];
	ret_mat.m[1][3] = m[1][0] * other.m[0][3] + m[1][1] * other.m[1][3] +
		m[1][2] * other.m[2][3] + m[1][3] * other.m[3][3];

	ret_mat.m[2][0] = m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] +
		m[2][2] * other.m[2][0] + m[2][3] * other.m[3][0];
	ret_mat.m[2][1] = m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] +
		m[2][2] * other.m[2][1] + m[2][3] * other.m[3][1];
	ret_mat.m[2][2] = m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] +
		m[2][2] * other.m[2][2] + m[2][3] * other.m[3][2];
	ret_mat.m[2][3] = m[2][0] * other.m[0][3] + m[2][1] * other.m[1][3] +
		m[2][2] * other.m[2][3] + m[2][3] * other.m[3][3];

	ret_mat.m[3][0] = m[3][0] * other.m[0][0] + m[3][1] * other.m[1][0] +
		m[3][2] * other.m[2][0] + m[3][3] * other.m[3][0];
	ret_mat.m[3][1] = m[3][0] * other.m[0][1] + m[3][1] * other.m[1][1] +
		m[3][2] * other.m[2][1] + m[3][3] * other.m[3][1];
	ret_mat.m[3][2] = m[3][0] * other.m[0][2] + m[3][1] * other.m[1][2] +
		m[3][2] * other.m[2][2] + m[3][3] * other.m[3][2];
	ret_mat.m[3][3] = m[3][0] * other.m[0][3] + m[3][1] * other.m[1][3] +
		m[3][2] * other.m[2][3] + m[3][3] * other.m[3][3];

	return ret_mat;

}
float Matrix4::GetDeterminant4x4()
{
	const float a11 = m[0][0];
	const float a12 = m[0][1];
	const float a13 = m[0][2];
	const float a14 = m[0][3];

	const float a21 = m[1][0];
	const float a22 = m[1][1];
	const float a23 = m[1][2];
	const float a24 = m[1][3];

	const float a31 = m[2][0];
	const float a32 = m[2][1];
	const float a33 = m[2][2];
	const float a34 = m[2][3];

	const float a41 = m[3][0];
	const float a42 = m[3][1];
	const float a43 = m[3][2];
	const float a44 = m[3][3];


	return a11 * a22 * a33 * a44 + a11 * a23 * a34 * a42 + a11 * a24 * a32 * a43
		+ a12 * a21 * a34 * a43 + a12 * a23 * a31 * a44 + a12 * a24 * a33 * a41
		+ a13 * a21 * a32 * a44 + a13 * a22 * a34 * a41 + a13 * a24 * a31 * a42
		+ a14 * a21 * a33 * a42 + a14 * a22 * a31 * a43 + a14 * a23 * a32 * a41
		- a11 * a22 * a34 * a43 - a11 * a23 * a32 * a44 - a11 * a24 * a33 * a42
		- a12 * a21 * a33 * a44 - a12 * a23 * a34 * a41 - a12 * a24 * a31 * a43
		- a13 * a21 * a34 * a42 - a13 * a22 * a31 * a44 - a13 * a24 * a32 * a41
		- a14 * a21 * a32 * a43 - a14 * a22 * a33 * a41 - a14 * a23 * a31 * a42;

}//4x4行列の行列式を返す関数
Matrix4 Matrix4::GetInversed()
{
	Matrix4 ret_mat;

	const float a11 = m[0][0];
	const float a12 = m[0][1];
	const float a13 = m[0][2];
	const float a14 = m[0][3];

	const float a21 = m[1][0];
	const float a22 = m[1][1];
	const float a23 = m[1][2];
	const float a24 = m[1][3];

	const float a31 = m[2][0];
	const float a32 = m[2][1];
	const float a33 = m[2][2];
	const float a34 = m[2][3];

	const float a41 = m[3][0];
	const float a42 = m[3][1];
	const float a43 = m[3][2];
	const float a44 = m[3][3];

	ret_mat.m[0][0] = a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43 - a22 * a34 * a43 - a23 * a32 * a44 - a24 * a33 * a42;
	ret_mat.m[0][1] = a12 * a34 * a43 + a13 * a32 * a44 + a14 * a33 * a42 - a12 * a33 * a44 - a13 * a34 * a42 - a14 * a32 * a43;
	ret_mat.m[0][2] = a12 * a23 * a44 + a13 * a24 * a42 + a14 * a22 * a43 - a12 * a24 * a43 - a13 * a22 * a44 - a14 * a23 * a42;
	ret_mat.m[0][3] = a12 * a24 * a33 + a13 * a22 * a34 + a14 * a23 * a32 - a12 * a23 * a34 - a13 * a24 * a32 - a14 * a22 * a33;
	ret_mat.m[1][0] = a21 * a34 * a43 + a23 * a31 * a44 + a24 * a33 * a41 - a21 * a33 * a44 - a23 * a34 * a41 - a24 * a31 * a43;
	ret_mat.m[1][1] = a11 * a33 * a44 + a13 * a34 * a41 + a14 * a31 * a43 - a11 * a34 * a43 - a13 * a31 * a44 - a14 * a33 * a41;
	ret_mat.m[1][2] = a11 * a24 * a43 + a13 * a21 * a44 + a14 * a23 * a41 - a11 * a23 * a44 - a13 * a24 * a41 - a14 * a21 * a43;
	ret_mat.m[1][3] = a11 * a23 * a34 + a13 * a24 * a31 + a14 * a21 * a33 - a11 * a24 * a33 - a13 * a21 * a34 - a14 * a23 * a31;
	ret_mat.m[2][0] = a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42 - a21 * a34 * a42 - a22 * a31 * a44 - a24 * a32 * a41;
	ret_mat.m[2][1] = a11 * a34 * a42 + a12 * a31 * a44 + a14 * a32 * a41 - a11 * a32 * a44 - a12 * a34 * a41 - a14 * a31 * a42;
	ret_mat.m[2][2] = a11 * a22 * a44 + a12 * a24 * a41 + a14 * a21 * a42 - a11 * a24 * a42 - a12 * a21 * a44 - a14 * a22 * a41;
	ret_mat.m[2][3] = a11 * a24 * a32 + a12 * a21 * a34 + a14 * a22 * a31 - a11 * a22 * a34 - a12 * a24 * a31 - a14 * a21 * a32;
	ret_mat.m[3][0] = a21 * a33 * a42 + a22 * a31 * a43 + a23 * a32 * a41 - a21 * a32 * a43 - a22 * a33 * a41 - a23 * a31 * a42;
	ret_mat.m[3][1] = a11 * a32 * a43 + a12 * a33 * a41 + a13 * a31 * a42 - a11 * a33 * a42 - a12 * a31 * a43 - a13 * a32 * a41;
	ret_mat.m[3][2] = a11 * a23 * a42 + a12 * a21 * a43 + a13 * a22 * a41 - a11 * a22 * a43 - a12 * a23 * a41 - a13 * a21 * a42;
	ret_mat.m[3][3] = a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a11 * a23 * a32 - a12 * a21 * a33 - a13 * a22 * a31;

	float det = GetDeterminant4x4();

	if (det != 0.0f)
	{
		float inv_det = 1.0f / det;

		for (int i = 0; i < 4; i++)
		{
			for (int k = 0; k < 4; k++)
			{
				ret_mat.m[i][k] *= inv_det;
			}
		}
	}

	return ret_mat;

}//4x4行列の逆行列を取得

//[ Vector3 ]
Vector3 Vector3::GetMultiply(Matrix3 src_mat)
{
	Vector3 ret_Vector3 = { 0,0,1 };

	ret_Vector3.x = x * src_mat.m[0][0] + y * src_mat.m[1][0] + z * src_mat.m[2][0];
	ret_Vector3.y = x * src_mat.m[0][1] + y * src_mat.m[1][1] + z * src_mat.m[2][1];

	return ret_Vector3;
}

Vector3 operator*(Vector3 const& dst_vec, float const multipleNum)
{
	return { dst_vec.x * multipleNum, dst_vec.y * multipleNum, dst_vec.z * multipleNum };
}

//[ Vector4 ]
Vector4<float> Vector4<float>::operator+=(float const addNum)
{
	x += addNum;
	y += addNum;
	z += addNum;

	return *this;
}
Vector4<float> Vector4<float>::operator=(float const num)
{
	x = num;
	y = num;
	z = num;

	return *this;
}
//大きさをゲット
float Vector4<float>::GetMagnitutde()
{
	return sqrtf(x * x + y * y + z * z);
}
//正規化ベクトルを返す
Vector4<float> Vector4<float>::GetNormalizedVec()
{
	float mag = GetMagnitutde();
	float inv_mag = 0;

	if (mag != 0) inv_mag = 1.0f / mag;

	Vector4<float> ret_normalizeVec = { x * inv_mag ,y * inv_mag,z * inv_mag,1.0f };

	return ret_normalizeVec;
}
//内積を計算して返す
float Vector4<float>::GetDotProductionResult(Vector4<float> src1_Vector4, Vector4<float> src2_Vector4)
{
	float ret_cosTheta = 0.0f;

	//cos(🍆角)
	ret_cosTheta =
		src1_Vector4.x * src2_Vector4.x +
		src1_Vector4.y * src2_Vector4.y +
		src1_Vector4.z * src2_Vector4.z;

	return ret_cosTheta;
}
//差分単位ベクトルを返す
Vector4<float> Vector4<float>::GetNormalizedDiffVector4(Vector4<float> dst_pos, Vector4<float> my_pos)
{
	Vector4<float> diff;

	//差分を計算
	diff = dst_pos - my_pos;

	return diff.GetNormalizedVec();
}
//マトリックスとベクタの積
Vector4<float> Vector4<float>::GetMultiply(Matrix4 src_mat)
{
	Vector4<float> ret_Vector4;

	ret_Vector4.x = x * src_mat.m[0][0] + y * src_mat.m[1][0] +
		z * src_mat.m[2][0] + w * src_mat.m[3][0];

	ret_Vector4.y = x * src_mat.m[0][1] + y * src_mat.m[1][1] +
		z * src_mat.m[2][1] + w * src_mat.m[3][1];

	ret_Vector4.z = x * src_mat.m[0][2] + y * src_mat.m[1][2] +
		z * src_mat.m[2][2] + w * src_mat.m[3][2];

	ret_Vector4.w = x * src_mat.m[0][3] + y * src_mat.m[1][3] +
		z * src_mat.m[2][3] + w * src_mat.m[3][3];

	return ret_Vector4;
}
//クロス積を返す
Vector4<float> Vector4<float>::GetCross(Vector4<float> other)
{
	Vector4<float> ret_Vector4;

	ret_Vector4.x = y * other.z - z * other.y;
	ret_Vector4.y = z * other.x - x * other.z;
	ret_Vector4.z = x * other.y - y * other.x;

	return ret_Vector4;
}



Matrix4 operator*(Matrix4 const& dst_mat, float multipleNum)
{
	Matrix4 ret_mat;

	for (int i = 0; i < 4; ++i)
	{
		for (int k = 0; k < 4; ++k)
		{
			ret_mat.m[i][k] = dst_mat.m[i][k] * multipleNum;
		}
	}

	return ret_mat;
}

Matrix4 Get_VPMat(Matrix4 cameraMat, Vector4<float> cameraPos , ProjectionType type_)
{
	Matrix4 ret_mat;

	//ビュー行列作成
	Matrix4 viewMat = cameraMat.GetInversed();
	//射影行列
	Matrix4 projectionMat;

	//平行投影
	if (type_ == kParallel)
	{
		projectionMat = Get_Orthographic3D(
			cameraPos.x - (Torima::windowWidth * 0.5f), cameraPos.x + (Torima::windowWidth * 0.5f),
			cameraPos.y + (Torima::windowHeight * 0.5f), cameraPos.y - (Torima::windowHeight * 0.5f),
			0.1f, 1000.0f);
	}

	//中心投影
	else if (type_ == kPerspective)
	{
		float aspectRatio = Torima::windowWidth / Torima::windowHeight;
		projectionMat = Get_PerspectiveFOV(Torima::torimaFOVy, aspectRatio);
	}

	//viewMat⇔PerspectiveMat
	ret_mat = viewMat.Multiply(projectionMat);

	return  ret_mat;
}

Matrix4 Get_PerspectiveFOV(float fovY_, float aspectRatio_, float nearClip_ , float farClip_ )
{
	const float cotTheta{ 1.0f / tanf(fovY_ * 0.5f) };
	const float inv_frustumHeight{ 1.0f / (farClip_ - nearClip_) };

	return Matrix4
	{
		cotTheta / aspectRatio_ , 0.0f, 0.0f, 0.0f,
		0.0f, cotTheta, 0.0f, 0.0f,
		0.0f, 0.0f, farClip_ * inv_frustumHeight, 1.0f,
		0.0f, 0.0f, -nearClip_ * farClip_ * inv_frustumHeight, 0.0f,
	};


}
Matrix4 Get_ViewportTransformation3D(
	const float left_ , const float top_ ,
	const float windowWidth_ , const float windowHeight_ ,
	const float minDepth_ , const float maxDepth_ )
{
	return Matrix4
	{
		windowWidth_ * 0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -windowHeight_ * 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, maxDepth_ - minDepth_, 0.0f,
		left_ + windowWidth_ * 0.5f, top_ + windowHeight_ * 0.5f, minDepth_, 1.0f,
	};
}
Matrix4 Get_Orthographic3D(
	const float l_, const float r_,
	const float t_, const float b_,
	const float zn_, const float zf_)
{
	const float inv_W{ 1.0f / (r_ - l_) };
	const float inv_H{ 1.0f / (t_ - b_) };
	const float inv_D{ 1.0f / (zf_ - zn_) };

	return Matrix4
	{
		2.0f * inv_W, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f * inv_H, 0.0f, 0.0f,
		0.0f, 0.0f, inv_D, 0.0f,
		-(l_ + r_) * inv_W, -(t_ + b_) * inv_H, -zn_ * inv_D, 1.0f,
	};
}
Matrix4 Get_SRTMat3D(const Vector4<float>& scale_, const Vector4<float>& rotateTheta_,
	const Vector4<float>& translate_)
{
	Matrix4 ret_mat;

	//回転角をradianに変換
	static float const degreeConverter = 3.141592653589f / 180.0f;
	Vector4<float> rotateRad = rotateTheta_ * degreeConverter;

	//3つの回転軸に対応した行列を作成
	//角度を三角関数に代入して返すラムダ式
	auto substituteRad = [](float rotateRad_) {
		Vector4<float> ret_vec = { cosf(rotateRad_),sinf(rotateRad_),1.0f,1.0f };
		return ret_vec; };

	//x軸
	Vector4<float> circularFunc = substituteRad(rotateRad.x);

	Matrix4 rotateMatX(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, circularFunc.x, circularFunc.y, 0.0f,
		0.0f, -circularFunc.y, circularFunc.x, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	//y軸
	circularFunc = substituteRad(rotateRad.y);
	Matrix4 rotateMatY =
	{
		circularFunc.x,0.0f,-circularFunc.y,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		circularFunc.y,0.0f,circularFunc.x,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	//z軸
	circularFunc = substituteRad(rotateRad.z);
	Matrix4 rotateMatZ =
	{
		circularFunc.x,circularFunc.y,0.0f,0.0f,
		-circularFunc.y,circularFunc.x,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	//3つの回転マトリックスを合成する
	Matrix4 concentratedRotateMat = rotateMatX.Multiply(rotateMatY.Multiply(rotateMatZ));

	//SRT行列の作成
	//ScaleMatrix
	Matrix4 scaleMat =
	{
		scale_.x,0.0f,0.0f,0.0f,
		0.0f,scale_.y,0.0f,0.0f,
		0.0f,0.0f,scale_.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	//TranslateMat
	Matrix4 translateMat =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		translate_.x,translate_.y,translate_.z,1.0f
	};

	//S⇔R
	ret_mat = scaleMat.Multiply(concentratedRotateMat);
	//SR⇔T
	ret_mat = ret_mat.Multiply(translateMat);

	return ret_mat;		//SRT

}//SRT行列の作成・取得
Matrix4 Get_STRMat3D(const Vector4<float>& scale_, const Vector4<float>& movementTheta_,
	const Vector4<float>& translate_)
{
	Matrix4 ret_mat;

	//回転角をradianに変換
	static float const degreeConverter = Torima::kPi / 180.0f;
	Vector4<float> rotateRad = movementTheta_ * degreeConverter;

	//3つの回転軸に対応した行列を作成
	//角度を三角関数に代入して返すラムダ式
	auto substituteRad = [](float movementTheta_) {
		Vector4<float> ret_vec = { cosf(movementTheta_),sinf(movementTheta_),1.0f,1.0f };
		return ret_vec; };

	//x軸
	Vector4<float> circularFunc = substituteRad(rotateRad.x);
	Matrix4 movementMatX =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,circularFunc.x,circularFunc.y,0.0f,
		0.0f,-circularFunc.y,circularFunc.x,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	//y軸
	circularFunc = substituteRad(rotateRad.y);
	Matrix4 movementMatY =
	{
		circularFunc.x,0.0f,-circularFunc.y,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		circularFunc.y,0.0f,circularFunc.x,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	//z軸
	circularFunc = substituteRad(rotateRad.z);
	Matrix4 movementMatZ =
	{
		circularFunc.x,circularFunc.y,0.0f,0.0f,
		-circularFunc.y,circularFunc.x,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	//3つの回転マトリックスを合成する
	Matrix4 concentratedRotateMat = movementMatX.Multiply(movementMatY.Multiply(movementMatZ));

	//SRT行列の作成
	//ScaleMatrix
	Matrix4 scaleMat =
	{
		scale_.x,0.0f,0.0f,0.0f,
		0.0f,scale_.y,0.0f,0.0f,
		0.0f,0.0f,scale_.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	//TranslateMat
	Matrix4 translateMat =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		translate_.x,translate_.y,translate_.z,1.0f
	};

	//S⇔T
	ret_mat = scaleMat.Multiply(translateMat);
	//ST⇔R
	ret_mat = ret_mat.Multiply(concentratedRotateMat);

	return ret_mat;		//STR

}
Matrix3 Get_SRTMat2D(const float& delta_scaleX_, const float& delta_scaleY_, const float& delta_rotateTheta_,
	const Vector3& delta_pos_)
{
	Matrix3 ret_mat;

	//回転角をradianに変換
	static float const degreeConverter = Torima::kPi / 180.0f;
	float delta_rotateRad = delta_rotateTheta_ * degreeConverter;
	float cosT = cosf(delta_rotateRad);
	float sinT = sinf(delta_rotateRad);


	Matrix3 rotateMat =
	{
		cosT,sinT,0.0f,
		-sinT,cosT,0.0f,
		0.0f,0.0f,1.0f,
	};

	//SRT行列の作成
	//ScaleMatrix
	Matrix3 scaleMat =
	{
		delta_scaleX_,0.0f,0.0f,
		0.0f,delta_scaleY_,0.0f,
		0.0f,0.0f,1.0f
	};

	//TranslateMat
	Matrix3 translateMat =
	{
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		delta_pos_.x,delta_pos_.y,1.0f
	};

	//S⇔R
	ret_mat = scaleMat.GetMultiply(&rotateMat);
	//ST⇔R
	ret_mat = ret_mat.GetMultiply(&translateMat);

	return ret_mat;		//STR

}//SRT行列の作成・取得



