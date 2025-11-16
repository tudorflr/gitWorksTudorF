#include <stdio.h>
#include <valarray>

#include "transform.h"
#include "mat3.h"
#include "mat4.h"
#include "vec2.h"


namespace egc {

    /*
    //transformation matrices in 2D
    mat3 translate(const vec2 translateArray);
    mat3 translate(float tx, float ty);

    mat3 scale(const vec2 scaleArray);
    mat3 scale(float sx, float sy);

    mat3 rotate(float angle);

    //transformation matrices in 3D
    mat4 translate(const vec3 translateArray);
    mat4 translate(float tx, float ty, float tz);

    mat4 scale(const vec3 scaleArray);
    mat4 scale(float sx, float sy, float sz);

    mat4 rotateX(float angle);
    mat4 rotateY(float angle);
    mat4 rotateZ(float angle);
    */

    mat3 translate(const vec2 translateArray) {
        mat3 result;
		result.transpose();
		result.at(0, 2) = translateArray.x;
		result.at(1, 2) = translateArray.y;
		result.transpose();
		return result;
    }

     
    mat3 translate(float tx, float ty) {
        mat3 result;
        result.transpose();
        result.at(0, 2) = tx;
		result.at(1, 2) = ty;
		result.transpose();
		return result;
    }
    
    mat3 scale(const vec2 scaleArray) {
        mat3 result;
		result.at(0, 0) = scaleArray.x;
		result.at(1, 1) = scaleArray.y;
		return result;
    }
    
    mat3 scale(float sx, float sy) {
        mat3 result;
		result.at(0, 0) = sx;
		result.at(1, 1) = sy;
		return result;
    }
    
    mat3 rotate(float angle) {
		mat3 result;
		float rad = angle * PI / 180;
		result.at(0, 0) = cos(rad);
		result.at(0, 1) = -sin(rad);
		result.at(1, 0) = sin(rad);
		result.at(1, 1) = cos(rad);
		return result;
    }
    

    // 3D

    
    mat4 translate(const vec3 translateArray) {
		mat4 result;
        result.transpose();
		result.at(0, 3) = translateArray.x;
		result.at(1, 3) = translateArray.y;
		result.at(2, 3) = translateArray.z;
		result.transpose();
		return result;
    }
    
    mat4 translate(float tx, float ty, float tz) {
        mat4 result;
		result.transpose();
		result.at(0, 3) = tx;
		result.at(1, 3) = ty;
		result.at(2, 3) = tz;
		result.transpose();
		return result;
    }
    
    mat4 scale(const vec3 scaleArray) {
		mat4 result;
		result.at(0, 0) = scaleArray.x;
		result.at(1, 1) = scaleArray.y;
		result.at(2, 2) = scaleArray.z;
		return result;
    }
    
    mat4 scale(float sx, float sy, float sz) {
		mat4 result;
		result.at(0, 0) = sx;
		result.at(1, 1) = sy;
		result.at(2, 2) = sz;
		return result;
    }
    
    mat4 rotateX(float angle)
    {
        mat4 result = mat4();

        float angleRadians = angle * PI / 180;

        float cosAngle = cos(angleRadians);
        float sinAngle = sin(angleRadians);

        result.at(1, 1) = cosAngle;
        result.at(2, 2) = cosAngle;
        result.at(2, 1) = sinAngle;
        result.at(1, 2) = -sinAngle;

        return result;
    }
    
    mat4 rotateY(float angle)
    {
        mat4 result = mat4();

        float angleRadians = angle * PI / 180;

        float cosAngle = cos(angleRadians);
        float sinAngle = sin(angleRadians);

        result.at(0, 0) = cosAngle;
        result.at(2, 2) = cosAngle;
        result.at(2, 0) = -sinAngle;
        result.at(0, 2) = sinAngle;

        return result;
    }


    mat4 rotateZ(float angle)
    {
        mat4 result = mat4();

        float angleRadians = angle * PI / 180;

        float cosAngle = cos(angleRadians);
        float sinAngle = sin(angleRadians);

        result.at(0, 0) = cosAngle;
        result.at(1, 1) = cosAngle;
        result.at(0, 1) = -sinAngle;
        result.at(1, 0) = sinAngle;

        return result;
    }


}