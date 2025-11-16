#include "rasterization.h"
#include <algorithm>
#include <cmath>
#include <limits>

namespace egc {
    extern float depthBuffer[WINDOW_WIDTH][WINDOW_HEIGHT]; // Declare external depth buffer

    void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma) {
        vec2 v0(triangleVertices[0].x, triangleVertices[0].y);
        vec2 v1(triangleVertices[1].x, triangleVertices[1].y);
        vec2 v2(triangleVertices[2].x, triangleVertices[2].y);

        float area = (v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y);
        alpha = ((v1.y - v2.y) * (pixel.x - v2.x) + (v2.x - v1.x) * (pixel.y - v2.y)) / area;
        beta = ((v2.y - v0.y) * (pixel.x - v2.x) + (v0.x - v2.x) * (pixel.y - v2.y)) / area;
        gamma = 1.0f - alpha - beta;
    }

    void rasterizeTriangle(SDL_Renderer *renderer, const std::vector<egc::vec4> &triangleVertices, const std::vector<egc::vec4> &triangleColors) {
        float minX = std::min({triangleVertices[0].x, triangleVertices[1].x, triangleVertices[2].x});
        float maxX = std::max({triangleVertices[0].x, triangleVertices[1].x, triangleVertices[2].x});
        float minY = std::min({triangleVertices[0].y, triangleVertices[1].y, triangleVertices[2].y});
        float maxY = std::max({triangleVertices[0].y, triangleVertices[1].y, triangleVertices[2].y});

        for (int y = static_cast<int>(std::floor(minY)); y <= static_cast<int>(std::ceil(maxY)); y++) {
            for (int x = static_cast<int>(std::floor(minX)); x <= static_cast<int>(std::ceil(maxX)); x++) {
                vec2 pixel(x + 0.5f, y + 0.5f);
                float alpha, beta, gamma;
                computeAlphaBetaGamma(triangleVertices, pixel, alpha, beta, gamma);

                if (alpha >= 0 && beta >= 0 && gamma >= 0) {
                    float depth = alpha * triangleVertices[0].z + beta * triangleVertices[1].z + gamma * triangleVertices[2].z;

                    if (depth > depthBuffer[y][x]) {
                        depthBuffer[y][x] = depth;
                        float r = alpha * triangleColors[0].x + beta * triangleColors[1].x + gamma * triangleColors[2].x;
                        float g = alpha * triangleColors[0].y + beta * triangleColors[1].y + gamma * triangleColors[2].y;
                        float b = alpha * triangleColors[0].z + beta * triangleColors[1].z + gamma * triangleColors[2].z;

                        SDL_SetRenderDrawColor(renderer,
                            static_cast<Uint8>(r * 255),
                            static_cast<Uint8>(g * 255),
                            static_cast<Uint8>(b * 255),
                            255);
                        SDL_RenderDrawPoint(renderer, x, y);
                    }
                }
            }
        }
    }

    void clearDepthBuffer() {
        for (int i = 0; i < WINDOW_HEIGHT; ++i) {
            for (int j = 0; j < WINDOW_WIDTH; ++j) {
                depthBuffer[i][j] = -std::numeric_limits<float>::infinity();
            }
        }
    }
}