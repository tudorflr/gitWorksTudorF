

#include "vec4.h"
namespace egc
{
    vec4& vec4::operator =(const vec4& srcVector)
    {
        x = srcVector.x;
        y = srcVector.y;
        z = srcVector.z;
        w = srcVector.w;
        return *this;
    }


    vec4 vec4::operator +(const vec4& srcVector) const
    {
        vec4 result;
        result.x = x + srcVector.x;
        result.y = y + srcVector.y;
        result.z = z + srcVector.z;
        result.w = w + srcVector.w;
        return result;
    }


    vec4& vec4::operator +=(const vec4& srcVector)
    {
        (*this).x += srcVector.x;
        (*this).y += srcVector.y;
        (*this).z += srcVector.z;
        (*this).w += srcVector.w;
        return *this;
    }


    vec4 vec4::operator *(float scalarValue) const
    {
        vec4 result;
        result.x = x * scalarValue;
        result.y = y * scalarValue;
        result.z = z * scalarValue;
        result.w = w * scalarValue;
        return result;
    }


    vec4 vec4::operator -(const vec4& srcVector) const
    {
        vec4 result;                  //vec4 a, b, c; c = a - b;
        result.x = x - srcVector.x;   //a -> this
        result.y = y - srcVector.y;   //b -> srcVec
        result.z = z - srcVector.z;
        result.w = w - srcVector.w;
        return result;                //c -> result
    }


    vec4& vec4::operator -=(const vec4& srcVector)
    {
        //vec3 a, b; a -= b; (a = a - b)
        (*this).x -= srcVector.x;
        (*this).y -= srcVector.y;
        (*this).z -= srcVector.z;
        (*this).w -= srcVector.w;
        return *this;
    }


    vec4 vec4::operator -() const
    {
        //vec4 a; a *= -1;
        vec4 result;
        result.x = x * (-1);
        result.y = y * (-1);
        result.z = z * (-1);
        result.w = w * (-1);
        return result;
    }


    float vec4::length() const
    {
        float result;
        result = sqrt(x * x + y * y + z * z + w * w);
        return result;
    }


    vec4& vec4::normalize()
    {
        float length = (*this).length();
        (*this).x /= length;
        (*this).y /= length;
        (*this).z /= length;
        (*this).w /= length;
        return *this;
    }
}