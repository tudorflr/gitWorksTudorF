#include "clip.h"
#include <iostream>

namespace egc {

    // Cyrus-Beck clipping algorithm
    // clipWindow specifies the vertices that define the clipping area in counterclockwise order
    // and can represent any convex polygon
    // function returns -1 if the line segment cannot be clipped

	std::vector<vec3> normalizeClipWindow(std::vector<vec3> clipWindow)
	{
		std::vector<vec3> result;
		for (int i = 0; i < 4; i++)
		{
			vec3 v0 = clipWindow[i];
			vec3 v1 = clipWindow[(i + 1) % 4];

			vec3 edge = v1 - v0;

			vec3 normal = crossProduct(edge, vec3(0, 0, 1));

			normal.normalize();

			printf("normal %f %f %f\n", normal.x, normal.y, normal.z);

			result.push_back(normal);
		}
		return result;
	}

    int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
        std::vector<vec3> normalizedClipWindow = normalizeClipWindow(clipWindow);
        vec3 D = p2 - p1; 

        if (p1 == p2) {
            return 0; 
        }
        else {
            float tE = 0.0f, tL = 1.0f;

            for (int i = 0; i < clipWindow.size(); i++) {
                vec3 Ni = normalizedClipWindow[i]; 
                vec3 PEi = clipWindow[i];

                vec3 P0_minus_PEi = p1 - PEi;
                float numerator = dotProduct(Ni, P0_minus_PEi);
                float denominator = dotProduct(Ni, D);

                if (denominator == 0) {
                    if (numerator > 0) return -1;
                    else continue;
                }

                float t = -numerator / denominator;

                if (denominator < 0) {
                    if (t > tE) tE = t;
                }
                else { 
                    if (t < tL) tL = t;
                }
            }

            if (tE > tL) return -1; 

            p1 = p1 + D * tE;
            p2 = p1 + D * (tL - tE);

            return 0;
        }
    }

}
