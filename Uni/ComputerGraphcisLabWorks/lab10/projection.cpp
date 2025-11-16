#include "projection.h"
#include <cmath>
#include <algorithm>

namespace egc {

mat4 defineViewTransformMatrix(int startX, int startY, int width, int height) {
    mat4 viewTransformMatrix;
    
    // Viewport transformation matrix
    viewTransformMatrix.at(0, 0) = width / 2.0f;
    viewTransformMatrix.at(0, 3) = startX + width / 2.0f;
    viewTransformMatrix.at(1, 1) = -height / 2.0f; // Negative Y because screen coordinates increase downward
    viewTransformMatrix.at(1, 3) = startY + height / 2.0f;
    viewTransformMatrix.at(2, 2) = 1.0f;
    viewTransformMatrix.at(3, 3) = 1.0f;
    
    return viewTransformMatrix;
}

mat4 defineCameraMatrix(Camera myCamera) {
    mat4 cameraMatrix;
    
    // Compute camera axes
    vec3 zAxis = normalize(myCamera.cameraPosition - myCamera.cameraTarget);
    vec3 xAxis = normalize(cross(myCamera.cameraUp, zAxis));
    vec3 yAxis = cross(zAxis, xAxis);
    
    // Create rotation matrix
    cameraMatrix.at(0, 0) = xAxis.x;
    cameraMatrix.at(0, 1) = xAxis.y;
    cameraMatrix.at(0, 2) = xAxis.z;
    cameraMatrix.at(1, 0) = yAxis.x;
    cameraMatrix.at(1, 1) = yAxis.y;
    cameraMatrix.at(1, 2) = yAxis.z;
    cameraMatrix.at(2, 0) = zAxis.x;
    cameraMatrix.at(2, 1) = zAxis.y;
    cameraMatrix.at(2, 2) = zAxis.z;
    
    // Add translation
    cameraMatrix.at(0, 3) = -dot(xAxis, myCamera.cameraPosition);
    cameraMatrix.at(1, 3) = -dot(yAxis, myCamera.cameraPosition);
    cameraMatrix.at(2, 3) = -dot(zAxis, myCamera.cameraPosition);
    cameraMatrix.at(3, 3) = 1.0f;
    
    return cameraMatrix;
}

mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar) {
    mat4 perspectiveProjectionMatrix;
    float f = 1.0f / tan(fov * 3.14159265f / 360.0f); // Convert fov to radians and compute focal length
    
    perspectiveProjectionMatrix.at(0, 0) = f / aspect;
    perspectiveProjectionMatrix.at(1, 1) = f;
    perspectiveProjectionMatrix.at(2, 2) = (zFar + zNear) / (zNear - zFar);
    perspectiveProjectionMatrix.at(2, 3) = (2.0f * zFar * zNear) / (zNear - zFar);
    perspectiveProjectionMatrix.at(3, 2) = -1.0f;
    
    return perspectiveProjectionMatrix;
}

void perspectiveDivide(vec4 &inputVertex) {
    if (inputVertex.w != 0.0f) {
        inputVertex.x /= inputVertex.w;
        inputVertex.y /= inputVertex.w;
        inputVertex.z /= inputVertex.w;
        inputVertex.w = 1.0f;
    }
}

bool clipPointInHomogeneousCoordinate(const egc::vec4 &vertex) {
    // Check if point is outside any of the clipping planes
    return (abs(vertex.x) > vertex.w || 
           (abs(vertex.y) > vertex.w || 
           (abs(vertex.z) > vertex.w ||
           (vertex.w <= 0);
}

bool clipTriangleInHomegeneousCoordinates(const std::vector<egc::vec4> &triangle) {
    // Check if all vertices are outside any single clipping plane
    for (int i = 0; i < 3; i++) {
        if (clipPointInHomogeneousCoordinate(triangle[i])) {
            bool allOutside = true;
            for (int j = 0; j < 3; j++) {
                if (!clipPointInHomogeneousCoordinate(triangle[j])) {
                    allOutside = false;
                    break;
                }
            }
            if (allOutside) return true;
        }
    }
    return false;
}

egc::vec3 findNormalVectorToTriangle(const std::vector<egc::vec4> &triangle) {
    vec3 v0(triangle[0].x, triangle[0].y, triangle[0].z);
    vec3 v1(triangle[1].x, triangle[1].y, triangle[1].z);
    vec3 v2(triangle[2].x, triangle[2].y, triangle[2].z);
    
    vec3 edge1 = v1 - v0;
    vec3 edge2 = v2 - v0;
    
    return cross(edge1, edge2).normalize();
}

egc::vec4 findCenterPointOfTriangle(const std::vector<egc::vec4> &triangle) {
    return vec4(
        (triangle[0].x + triangle[1].x + triangle[2].x) / 3.0f,
        (triangle[0].y + triangle[1].y + triangle[2].y) / 3.0f,
        (triangle[0].z + triangle[1].z + triangle[2].z) / 3.0f,
        1.0f
    );
}

bool isTriangleVisible(const std::vector<egc::vec4> &triangle, const egc::vec3 &normalVector) {
    // Compute vector from camera to triangle (using first vertex)
    vec3 viewDirection = normalize(vec3(triangle[0].x, triangle[0].y, triangle[0].z));
    
    // If dot product is negative, triangle is front-facing
    return dot(normalVector, viewDirection) < 0;
}

void displayNormalVectors(egc::vec3 &normalVector, egc::vec4 &triangleCenter, 
                        SDL_Renderer *renderer, egc::mat4 viewTransformMatrix, 
                        egc::mat4 perspectiveMatrix) {
    // Scale normal for visualization (10% of the triangle size)
    vec4 normalEnd = triangleCenter + vec4(normalVector * 0.1f, 0.0f);
    
    // Apply viewport transformation
    vec4 start = viewTransformMatrix * triangleCenter;
    vec4 end = viewTransformMatrix * normalEnd;
    
    // Draw the normal vector
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color for normals
    SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
}

} // namespace egc