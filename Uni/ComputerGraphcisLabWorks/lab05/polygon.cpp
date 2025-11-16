#include <stdio.h>
#include <valarray>
#include <cmath>

#include "polygon.h"
#include "mat3.h"
#include "mat4.h"
#include "vec2.h"
#include "transform.h"


namespace egc {

    polygon::polygon() {
        addVertex(vec3(100, 100, 1));
        addVertex(vec3(400, 100, 1));
        addVertex(vec3(400, 200, 1));
        addVertex(vec3(100, 200, 1));
    }

    void polygon::addVertex(vec3 vertex) {

        this->vertices.push_back(vertex);
    }

    void polygon::clearVertices() {

        this->vertices.clear();
    }

    void polygon::transformVertices()
    {
        this->transformedVertices = this->vertices;
    }

    void polygon::scale(float scaleFactor) {
        vec3 topLeft = vertices[0]; 

        mat3 translateToOrigin, translateBack, scaleMatrix;

        translateToOrigin.at(0, 0) = 1; translateToOrigin.at(0, 1) = 0; translateToOrigin.at(0, 2) = -topLeft.x;
        translateToOrigin.at(1, 0) = 0; translateToOrigin.at(1, 1) = 1; translateToOrigin.at(1, 2) = -topLeft.y;
        translateToOrigin.at(2, 0) = 0; translateToOrigin.at(2, 1) = 0; translateToOrigin.at(2, 2) = 1;

        translateBack.at(0, 0) = 1; translateBack.at(0, 1) = 0; translateBack.at(0, 2) = topLeft.x;
        translateBack.at(1, 0) = 0; translateBack.at(1, 1) = 1; translateBack.at(1, 2) = topLeft.y;
        translateBack.at(2, 0) = 0; translateBack.at(2, 1) = 0; translateBack.at(2, 2) = 1;

        scaleMatrix.at(0, 0) = scaleFactor; scaleMatrix.at(0, 1) = 0; scaleMatrix.at(0, 2) = 0;
        scaleMatrix.at(1, 0) = 0; scaleMatrix.at(1, 1) = scaleFactor; scaleMatrix.at(1, 2) = 0;
        scaleMatrix.at(2, 0) = 0; scaleMatrix.at(2, 1) = 0; scaleMatrix.at(2, 2) = 1;

        mat3 transform = translateBack * scaleMatrix * translateToOrigin;

        for (auto& v : vertices) {
            v = transform * v;
        }
    }


    void polygon::rotate(float angle) {
        float radians = angle * PI / 180.0f;

        vec3 center = (vertices[0] + vertices[2]) * 0.5f;

        mat3 translateToOrigin, translateBack, rotationMatrix;

        translateToOrigin.at(0, 0) = 1; translateToOrigin.at(0, 1) = 0; translateToOrigin.at(0, 2) = -center.x;
        translateToOrigin.at(1, 0) = 0; translateToOrigin.at(1, 1) = 1; translateToOrigin.at(1, 2) = -center.y;
        translateToOrigin.at(2, 0) = 0; translateToOrigin.at(2, 1) = 0; translateToOrigin.at(2, 2) = 1;

        translateBack.at(0, 0) = 1; translateBack.at(0, 1) = 0; translateBack.at(0, 2) = center.x;
        translateBack.at(1, 0) = 0; translateBack.at(1, 1) = 1; translateBack.at(1, 2) = center.y;
        translateBack.at(2, 0) = 0; translateBack.at(2, 1) = 0; translateBack.at(2, 2) = 1;

        rotationMatrix.at(0, 0) = cos(radians); rotationMatrix.at(0, 1) = -sin(radians); rotationMatrix.at(0, 2) = 0;
        rotationMatrix.at(1, 0) = sin(radians); rotationMatrix.at(1, 1) = cos(radians); rotationMatrix.at(1, 2) = 0;
        rotationMatrix.at(2, 0) = 0; rotationMatrix.at(2, 1) = 0; rotationMatrix.at(2, 2) = 1;

        mat3 transform = translateBack * rotationMatrix * translateToOrigin;

        for (auto& v : vertices) {
            v = transform * v;
        }
    }



    void polygon::draw(SDL_Renderer* renderer) {
        transformVertices(); 

        if (this->transformedVertices.size() < 2) {
            return; 
        }

        SDL_SetRenderDrawColor(renderer, this->polygonColor.r, this->polygonColor.g, this->polygonColor.b, this->polygonColor.a);

        for (size_t i = 0; i < transformedVertices.size(); i++) {
            vec3 v1 = transformedVertices[i];
            vec3 v2 = transformedVertices[(i + 1) % transformedVertices.size()];

            SDL_RenderLine(renderer, v1.x, v1.y, v2.x, v2.y);
        }
    }



}