#pragma once
#include "stdafx.h"

#define PI (float)3.14159265358979323846264338327950288
namespace math {
	template<typename T>
	struct vector3_;

	template<typename T>
	struct vector2 {
		T x;
		T y;

		vector2<T>() {}

		vector2<T>(T in_x, T in_y)
			: x(in_x), y(in_y) {}

		vector2<T> operator*(float value) {
			return vector2<T>(x * value, y * value);
		}

		vector2<T> operator*=(float value) {
			return vector2<T>(x * value, y * value);
		}

		vector2<T> operator*(vector2<T>& value) {
			return vector2<T>(x * value.x, y * value.y);
		}

		vector2<T> operator+=(vector2<T>& value) {
			x += value.x;
			y += value.y;
			return vector2<T>(x, y);
		}

		vector2<T> operator-(float value) {
			return vector2<T>(x - value, y - value);
		}

		vector2<T> operator-=(float value) {
			return vector2<T>(x - value, y - value);
		}

		vector2<T> operator-(vector2<T>& value) {
			return vector2<T>(x - value.x, y - value.y);
		}

		vector2<T> operator+(float value) {
			return vector2<T>(x + value, y + value);
		}

		vector2<T> operator+=(float value) {
			return vector2<T>(x + value, y + value);
		}

		vector2<T> operator+(vector2<T>& value) {
			return vector2<T>(x + value.x, y + value.y);
		}

		vector2<T> operator/(float value) {
			if (value == 0.f || x == 0 || y == 0) return vector2<T>(0, 0);
			return vector2<T>(x / value, y / value);
		}

		vector2<T> operator/=(float value) {
			if (value == 0.f || x == 0 || y == 0) return vector2<T>(0, 0);
			return vector2<T>(x / value, y / value);
		}

		vector2<T> operator/(vector2<T>& value) {
			return vector2<T>(x / value.x, y / value.y);
		}

		bool operator==(vector2<T>& value) {
			return x == value.x && y == value.y;
		}

		float get_distance(vector2<T>& value) {
			return ((float)sqrt(pow(value.x - x, 2) + pow(value.y - y, 2) * 1.0));
		}

		float get_length() {
			return (float)sqrt((x * x) + (y * y));
		}

		void normalize() {
			float Length = get_length();
			x /= Length;
			y /= Length;
		}
	};

	template<typename T>
	struct vector3 {
		T x;
		DWORD AAAAA;
		T y;
		DWORD BBBBB;
		T z;
		DWORD CCCCC;

		vector3<T>() {}

		vector3<T>(T in_x, T in_y, T in_z)
			: x(in_x), y(in_y), z(in_z) {}

		vector3<T> operator*(float value) {
			return vector3<T>(x * value, y * value, z * value);
		}

		vector3<T> operator*=(float value) {
			return vector3<T>(x * value, y * value, z * value);
		}

		vector3<T> operator*(vector3<T>& value) {
			return vector3<T>(x * value.x, y * value.y, z * value.z);
		}

		vector3<T> operator+=(vector3<T>& value) {
			return vector3<T>(x + value.x, y + value.y, z + value.z);
		}

		vector3<T> operator-(float value) {
			return vector3<T>(x - value, y - value, z - value);
		}

		vector3<T> operator-=(float value) {
			return vector3<T>(x - value, y - value, z - value);
		}

		vector3<T> operator-(vector3<T>& value) {
			return vector3<T>(x - value.x, y - value.y, z - value.z);
		}

		vector3<T> operator+(float value) {
			return vector3<T>(x + value, y + value, z + value);
		}

		vector3<T> operator+=(float value) {
			return vector3<T>(x + value, y + value, z + value);
		}

		vector3<T> operator-=(vector3<T>& value) {
			return vector3<T>(x - value.x, y - value.y, z - value.z);
		}

		vector3<T> operator+(vector3<T>& value) {
			return vector3<T>(x + value.x, y + value.y, z + value.z);
		}

		vector3<T> operator/(float value) {
			if (value == 0.f || x == 0 || y == 0 || z == 0) return vector3<T>(0, 0);
			return vector3<T>(x / value, y / value, z / value);
		}

		vector3<T> operator/=(float value) {
			if (value == 0.f || x == 0 || y == 0) return vector3<T>(0, 0);
			return vector3<T>(x / value, y / value, z / value);
		}

		vector3<T> operator/(vector3<T>& value) {
			return vector3<T>(x / value.x, y / value.y, z / value.z);
		}

		bool operator==(vector3<T>& value) {
			return x == value.x && y == value.y && z == value.z;
		}

		float get_distance(vector3<T> value) {
			return ((float)sqrt(pow(value.x - x, 2) + pow(value.y - y, 2) * 1.0));
		}

		bool is_null() {
			return (x == fabs(0.0f) && y == fabs(0.0f) && z == fabs(0.0f));
		}

		float get_2d_distance() {
			return (float)sqrt((x * x) + (z * z));
		}

		float get_length() {
			return (float)sqrt((x * x) + (y * y) + (z * z));
		}

		void normalize() {
			float Length = get_length();
			x /= Length;
			y /= Length;
			z /= Length;
		}

		static vector3_<T> to_serialized(vector3<T> value) {
			return vector3_<T>(value.x, value.y, value.z);
		}

		float dot(vector3<T> value) {
			return (x * x + y * y + z * z);
		}
	};

	template<typename T>
	struct vector3_ {
		T x;
		T y;
		T z;

		vector3_<T>() {}

		vector3_<T>(T in_x, T in_y, T in_z)
			: x(in_x), y(in_y), z(in_z) {}

		vector3_<T> operator*(float value) {
			return vector3_<T>(x * value, y * value, z * value);
		}

		vector3_<T> operator*=(float value) {
			return vector3_<T>(x * value, y * value, z * value);
		}

		vector3_<T> operator*(vector3_<T>& value) {
			return vector3_<T>(x * value.x, y * value.y, z * value.z);
		}

		vector3_<T> operator-(float value) {
			return vector3_<T>(x - value, y - value, z - value);
		}

		vector3_<T> operator-(vector3_<T> value) {
			return vector3_<T>(x - value.x, y - value.y, z - value.z);
		}

		vector3_<T> operator-=(float value) {
			return vector3_<T>(x - value, y - value, z - value);
		}

		vector3_<T> operator-(vector3_<T>& value) {
			return vector3_<T>(x - value.x, y - value.y, z - value.z);
		}

		vector3_<T> operator+(float value) {
			return vector3_<T>(x + value, y + value, z + value);
		}

		vector3_<T> operator+=(float value) {
			return vector3_<T>(x + value, y + value, z + value);
		}

		vector3_<T> operator+=(vector3_<T> value) {
			return vector3_<T>(x + value.x, y + value.y, z + value.z);
		}

		vector3_<T> operator+(vector3_<T>& value) {
			return vector3_<T>(x + value.x, y + value.y, z + value.z);
		}

		vector3_<T> operator/(float value) {
			if (value == 0.f || x == 0 || y == 0 || z == 0) return vector3_<T>(0, 0);
			return vector3_<T>(x / value, y / value, z / value);
		}

		vector3_<T> operator/=(float value) {
			if (value == 0.f || x == 0 || y == 0) return vector3_<T>(0, 0);
			return vector3_<T>(x / value, y / value, z / value);
		}

		vector3_<T> operator/(vector3_<T>& value) {
			return vector3_<T>(x / value.x, y / value.y, z / value.z);
		}

		bool operator==(vector3_<T>& value) {
			return x == value.x && y == value.y && z == value.z;
		}

		float get_distance(vector3_<T>& value) {
			return ((float)sqrt(pow(value.x - x, 2) + pow(value.y - y, 2) * 1.0));
		}

		static vector3<T> to_padded(vector3_<T> value) {
			return vector3<T>(value.x, value.y, value.z);
		}

		float get_length() {
			return (float)sqrt((x * x) + (y * y) + (z * z));
		}

		void normalize() {
			float Length = get_length();
			x /= Length;
			y /= Length;
			z /= Length;
		}
	};

	template<typename T>
	struct vector4 {
		T x;
		T y;
		T z;
		T w;
	};

	template<typename T>
	struct matrix {
		union {
			struct {
				vector4<T> m_left;
				vector4<T> m_up;
				vector4<T> m_forward;
				vector4<T> m_translation;
			};

			T m_elements[4][4];
		};

		matrix() {}

		T& operator () (int Row, int Col) {
			return m_elements[Row][Col];
		}
	};

	template<typename T>
	bool within(T val, T min, T max) {
		return val <= max && val >= min;
	}

	template<typename T>
	T clamp(T val, T min, T max) {
		return val < min ? min : val > max ? max : val;
	}

	inline float lerp(float toEase, float easeFrom, float percent) {
		return (toEase + percent * (easeFrom - toEase));
	}

	inline void ease(float& toEase, float& easeFrom, float multiplier) {
		toEase += toEase < easeFrom ? abs(toEase - easeFrom) / multiplier : -abs(toEase - easeFrom) / multiplier;
	}

	inline float repeat(float t, float length) {
		return clamp(t - (float)floor(t / length) * length, 0.f, length);
	}
}