#include <cmath>
#include <iostream>
#include "vec2.h";

namespace egc {
	

	vec2 &vec2::operator =(const vec2& srcVector) {
		x = srcVector.x;   // vec2  a,b  -> a = b
		(*this).y = srcVector.y;   // a->this  b->srcVec
		return *this;
	}



	vec2 vec2::operator +(const vec2& srcVector) const {
		vec2 result;   // vec2 a,b,c    c = a + b
		result.x = x + srcVector.x;
		result.y = y + srcVector.y; //  a -> this  b -> srcVector   c -> result
		return result;

	}

	vec2 &vec2::operator +=(const vec2& srcVector) {
		x = srcVector.x + x;
		(*this).y = srcVector.y + y;
		return *this;
	}


	vec2 vec2::operator *(float scalarValue) const {
		vec2 result;
		result.x = x * scalarValue;
		result.y = y * scalarValue;
		return result;
	}


	vec2 vec2::operator -(const vec2& srcVector) const {
		vec2 result;
		result.x = x - srcVector.x;
		result.y = y - srcVector.y;
		return result;
	}

	
	vec2 &vec2::operator -=(const vec2& srcVector) {
		x = x - srcVector.x;
		(*this).y = y - srcVector.y;
		return *this;
	}

	
	vec2 vec2::operator -() const {
		vec2 result;
		result.x = x * (-1);
		result.y = y * (-1);
		return result;
	}
	
	float vec2::length() const {
		float result;
		result = sqrt(x * x + y * y);
		return result;
	}

	vec2& vec2::normalize() {
		vec2 result;
		float length;
		length = sqrt(x * x + y * y);
		x = x / length;
		(*this).y = y / length;
		return *this;
	}

	float dotProduct(const vec2& v1, const vec2& v2) {
		float result;
		result = v1.x * v2.x + v1.y * v2.y;
		return result;
	}

}