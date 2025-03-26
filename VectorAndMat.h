#pragma once

template<typename T>
class Vec4
{
private:

	T x = 0;
	T y = 0;
	T z = 0;
	T w = 1;

	float magnitude = 0.0f;

public:

	Vec4() {};
	Vec4(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}
	Vec4(T entries[4]) : x(entries[0]), y(entries[1]), z(entries[2]), w(entries[3]) {}
	//Vec4(T entries[4])
	//{
	//	x = entries[0]; y = entries[1]; z = entries[2]; w = entries[3]);
	//}

	Vec4 GetMyVec()
	{
		return *this;
	}

	void SetMyVec(const Vec4<T>& src_vec)
	{
		x = src_vec.x;
		y = src_vec.y;
		z = src_vec.z;
		magnitude = src_vec.magnitude;
	}


	Vec4<T> operator+=(T const addNum)
	{
		x += addNum;
		y += addNum;
		z += addNum;

		return *this;
	}

	Vec4<T> operator=(T const num)
	{
		x = num;
		y = num;
		z = num;

		return *this;
	}

	//大きさをセット
	void SetMagnitutde()
	{
		magnitude = sqrtf(x * x + y * y + z * z);
	}

	//正規化ベクトルを返す
	Vec4<T> GetNormalizedVec()
	{
		SetMagnitutde();

		float inv_mag = 0;

		if (magnitude != 0) inv_mag = 1.0f / magnitude;

		Vec4<T> ret_normalizeVec = { x * inv_mag ,y * inv_mag,z * inv_mag };
		ret_normalizeVec.magnitude = magnitude;

		return ret_normalizeVec;
	}

	//内積を計算して返す
	float GetDotProductionResult(Vec4<T> src1_vec4, Vec4<T> src2_vec4)
	{
		float ret_cosTheta = 0.0f;

		//正規化する
		Vec4<T> normalized1 = src1_vec4.GetNormalizedVec();
		Vec4<T> normalized2 = src2_vec4.GetNormalizedVec();
		//cos(🍆角)
		ret_cosTheta = 
			normalized1.x * normalized2.x +
			normalized1.y * normalized2.y +
			normalized1.z * normalized2.z;

		return ret_cosTheta;
	}

	//差分単位ベクトルを返す
	Vec4 GetNormalizedDiffVec4(Vec4<T> dst_pos, Vec4<T> my_pos)
	{
		Vec4<T> diff;					

		//差分を計算
		diff = dst_pos - my_pos;
		//大きさを計算
		diff.SetMagnitutde();
		Vec4<T> normalized_diff = diff.GetNormalizedVec();

		return normalized_diff;
	}

};

template<typename T>
Vec4<T> operator+(Vec4<T> const& lVec, Vec4<T> const& rVec2)
{
	Vec4<T> ret_vec = { lVec.x + rVec2.x,lVec.y + rVec2.y ,lVec.z + rVec2.z ,1 };

	return ret_vec;
}

template<typename T>
Vec4<T> operator-(Vec4<T> const& lVec, Vec4<T> const& rVec2)
{
	Vec4<T> ret_vec = { lVec.x - rVec2.x,lVec.y - rVec2.y ,lVec.z - rVec2.z ,1 };

	return ret_vec;
}

template<typename T>
Vec4<T> operator*(Vec4<T> const& dst_vec, T const multipleNum)
{
	Vec4<T> ret_vec = { dst_vec.x * multipleNum,dst_vec.y * multipleNum ,dst_vec.z * multipleNum ,1 };

	return ret_vec;
}


