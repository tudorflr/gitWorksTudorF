#include "clip.h"

namespace egc {

	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p) {
		std::vector<int> code;
		//TO DO - compute the code for the point given as argument
		/*if (p.y < clipWindow[0].y) {
			code.push_back(1);
		}
		else {
			code.push_back(0);
		}*/
		
		if (p.y > clipWindow[2].y) {
			code.push_back(1);
		}
		else {
			code.push_back(0);
		}

		if (p.y < clipWindow[0].y) {
			code.push_back(1);
		}
		else {
			code.push_back(0);
		}

		if (p.x > clipWindow[2].x) {
			code.push_back(1);
		}
		else {
			code.push_back(0);
		}

		if (p.x < clipWindow[0].x) {
			code.push_back(1);
		}
		else {
			code.push_back(0);
		}

		/*for (int i = 0; i < code.size(); i++) {
			printf("%d ", code[i]);
		}*/
		return code;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {
		for (int i = 0; i < cod1.size(); i++) {
			if (cod1[i] == 1 && cod2[i] == 1) {
				return true;
			}
		}
		return false;
	}

	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
		for (int i = 0; i < cod1.size(); i++) {
			if (cod1[i] == 1 || cod2[i] == 1) {
				return false;
			}
		}
		return true;
	}

	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		float xmin = clipWindow[0].x;
		float ymin = clipWindow[0].y;
		float xmax = clipWindow[2].x;
		float ymax = clipWindow[2].y;

		bool finished = false;
		bool accept = false;

		while (!finished) {
			std::vector<int> cod1 = computeCSCode(clipWindow, p1);
			std::vector<int> cod2 = computeCSCode(clipWindow, p2);

			if (simpleRejection(cod1, cod2)) {
				finished = true;
			}
			else if (simpleAcceptance(cod1, cod2)) {
				finished = true;
				accept = true;
			}
			else {
				if (cod1 == std::vector<int>{0, 0, 0, 0}) {
					std::swap(p1, p2);
					std::swap(cod1, cod2);
				}

				float x = p1.x;
				float y = p1.y;
				float dx = p2.x - p1.x;
				float dy = p2.y - p1.y;

				if (cod1[0] == 1 && dy != 0) { // Above
					y = ymax;
					x = p1.x + dx * (ymax - p1.y) / dy;
				}
				else if (cod1[1] == 1 && dy != 0) { // Below
					y = ymin;
					x = p1.x + dx * (ymin - p1.y) / dy;
				}
				else if (cod1[2] == 1 && dx != 0) { // Right
					x = xmax;
					y = p1.y + dy * (xmax - p1.x) / dx;
				}
				else if (cod1[3] == 1 && dx != 0) { // Left
					x = xmin;
					y = p1.y + dy * (xmin - p1.x) / dx;
				}

				p1.x = x;
				p1.y = y;
			}
		}

		if (accept) return 1;
		return -1;
	}

}

