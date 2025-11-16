#include "mat4.h"
#include "mat3.h"
namespace egc
{
    mat4& mat4::operator =(const mat4& srcMatrix)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                (*this).at(i, j) = srcMatrix.at(i, j);
            }
        }
        return *this;
    }


    mat4 mat4::operator *(float scalarValue) const
    {
        mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.at(i, j) = this->at(i, j) * scalarValue;
            }
        }
        return result;
    }


    mat4 mat4::operator *(const mat4& srcMatrix) const
    {
        mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float sum = 0;
                for (int k = 0; k < 4; k++)
                {
                    sum += (*this).at(i, k) * srcMatrix.at(k, j);
                }
                result.at(i, j) = sum;
            }
        }
        return result;
    }


    vec4 mat4::operator *(const vec4& srcVector) const
    {
        vec4 result;

        result.x = (*this).at(0, 0) * srcVector.x + (*this).at(0, 1) * srcVector.y + (*this).at(0, 2) * srcVector.z + (*this).at(0, 3) * srcVector.w;
        result.y = (*this).at(1, 0) * srcVector.x + (*this).at(1, 1) * srcVector.y + (*this).at(1, 2) * srcVector.z + (*this).at(1, 3) * srcVector.w;
        result.z = (*this).at(2, 0) * srcVector.x + (*this).at(2, 1) * srcVector.y + (*this).at(2, 2) * srcVector.z + (*this).at(2, 3) * srcVector.w;
        result.w = (*this).at(3, 0) * srcVector.x + (*this).at(3, 1) * srcVector.y + (*this).at(3, 2) * srcVector.z + (*this).at(3, 3) * srcVector.w;

        return result;
    }


    mat4 mat4::operator +(const mat4& srcMatrix) const
    {
        mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.at(i, j) = (*this).at(i, j) + srcMatrix.at(i, j);
            }
        }
        return result;
    }


    float& mat4::at(int i, int j)
    {
        return matrixData[4 * j + i];
    }

    const float& mat4::at(int i, int j) const
    {
        return matrixData[4 * j + i];
    }


    float mat4::determinant() const {
        float det = 0.0f;
        for (int j = 0; j < 4; j++)
        {
            mat3 minor;
            for (int row = 1; row < 4; row++)
            {
                int minorCol = 0;
                for (int col = 0; col < 4; col++)
                {
                    if (col == j)
                    {
                        continue;
                    }
                    minor.at(row - 1, minorCol) = (*this).at(row, col);
                    minorCol++;
                }
            }
            float cofactor = ((j % 2 == 0) ? 1 : -1) * (*this).at(0, j) * minor.determinant();
            det += cofactor;
        }
        return det;
    }


    mat4 mat4::inverse() const
    {
        float det = (*this).determinant();
        if (det == 0)
        {
            throw std::invalid_argument("determinant cannot be zero");
        }

        float invDet = 1.0f / det;
        mat4 cofactor;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat3 minor;
                int minorRow = 0;
                for (int row = 0; row < 4; row++)
                {
                    if (row == i)
                    {
                        continue;
                    }
                    int minorCol = 0;
                    for (int col = 0; col < 4; col++) {
                        if (col == j)
                        {
                            continue;
                        }
                        minor.at(minorRow, minorCol) = (*this).at(row, col);
                        minorCol++;
                    }
                    minorRow++;
                }
                cofactor.at(i, j) = ((i + j) % 2 == 0 ? 1 : -1) * minor.determinant();
            }
        }

        mat4 adj = cofactor.transpose();

        return adj * invDet;
    }


    mat4 mat4::transpose() const
    {
        mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.at(i, j) = (*this).at(j, i);
            }
        }
        return result;
    }


}