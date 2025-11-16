//#include <cmath>
//#include <iostream>
#include "mat3.h"

namespace egc {

    mat3& mat3::operator =(const mat3& srcMatrix)
    {
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                (*this).at(i, j) = srcMatrix.at(i, j);
            }
        }
        return *this;
    }


    mat3 mat3::operator*(float scalarValue) const
    {
        //scalar multiplication -> each element * scalar
        mat3 result;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                result.at(i, j) = this->at(i, j) * scalarValue;
            }
        }
        return result;
    }


    vec3 mat3::operator *(const vec3& srcVector) const
    {
        vec3 result;

        result.x = (*this).at(0, 0) * srcVector.x + (*this).at(0, 1) * srcVector.y + (*this).at(0, 2) * srcVector.z;
        result.y = (*this).at(1, 0) * srcVector.x + (*this).at(1, 1) * srcVector.y + (*this).at(1, 2) * srcVector.z;
        result.z = (*this).at(2, 0) * srcVector.x + (*this).at(2, 1) * srcVector.y + (*this).at(2, 2) * srcVector.z;

        return result;
    }
 

    mat3 mat3::operator *(const mat3& srcMatrix) const {

		mat3 result;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				result.at(i, j) = 0;
				for (int k = 0; k < 3; k++) {
					result.at(i, j) += (*this).at(i, k) * srcMatrix.at(k, j);
				}
			}
		}

		return result;
    }


    mat3 mat3::operator +(const mat3& srcMatrix) const {
        mat3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.at(i, j) = (*this).at(i, j) + srcMatrix.at(i, j);
            }
        }
        return result;
    }


    float mat3::determinant() const {
		return matrixData[0] * (matrixData[4] * matrixData[8] - matrixData[5] * matrixData[7]) -
			matrixData[1] * (matrixData[3] * matrixData[8] - matrixData[5] * matrixData[6]) +
			matrixData[2] * (matrixData[3] * matrixData[7] - matrixData[4] * matrixData[6]);
    }
    

	mat3 mat3::inverse() const {
		mat3 result;
		float det = (*this).determinant();
		if (det == 0) {
			std::cout << "not invertible" << std::endl;
			return result;
		}
		float invDet = 1 / det;
        result.at(0, 0) = (*this).at(1, 1) * (*this).at(2, 2) - (*this).at(1, 2) * (*this).at(2, 1);
        result.at(0, 1) = -((*this).at(0, 1) * (*this).at(2, 2) - (*this).at(0, 2) * (*this).at(2, 1));
        result.at(0, 2) = (*this).at(0, 1) * (*this).at(1, 2) - (*this).at(0, 2) * (*this).at(1, 1);

        result.at(1, 0) = -((*this).at(1, 0) * (*this).at(2, 2) - (*this).at(1, 2) * (*this).at(2, 0));
        result.at(1, 1) = (*this).at(0, 0) * (*this).at(2, 2) - (*this).at(0, 2) * (*this).at(2, 0);
        result.at(1, 2) = -((*this).at(0, 0) * (*this).at(1, 2) - (*this).at(0, 2) * (*this).at(1, 0));

        result.at(2, 0) = (*this).at(1, 0) * (*this).at(2, 1) - (*this).at(1, 1) * (*this).at(2, 0);
        result.at(2, 1) = -((*this).at(0, 0) * (*this).at(2, 1) - (*this).at(0, 1) * (*this).at(2, 0));
        result.at(2, 2) = (*this).at(0, 0) * (*this).at(1, 1) - (*this).at(0, 1) * (*this).at(1, 0);

        return result * invDet;

	}


    mat3 mat3::transpose() const {
		mat3 result;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				result.at(i, j) = (*this).at(j, i);
			}
		}
		return result;
    }


    /*
    mat3 operator *(const mat3& srcMatrix) const; // ok
    //get element by (row, column);
    const float& at(int i, int j) const; // ok
    float determinant() const; // ok
    mat3 inverse() const;
    mat3 transpose() const;
    */

    float& mat3::at(int i, int j)
    {
        return matrixData[3 * j + i];
    }

    const float& mat3::at(int i, int j) const {
        return matrixData[3 * j + i];
    }

}
