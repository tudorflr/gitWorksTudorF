#include "vec2.h"
namespace egc {
	vec2& vec2::operator =(const vec2& srcVector) {
		x = srcVector.x;
		y = srcVector.y;		

		return *this;
	}
}