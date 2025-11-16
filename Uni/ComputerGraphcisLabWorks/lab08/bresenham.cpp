#include "bresenham.h"

//Detects in which octant a line is situated
int getOctant(BresenhamLine line) {

	int deltaY = static_cast<int>(line.endY - line.startY);
	int deltaX = static_cast<int>(line.endX - line.startX);

	//Slope		
	float m = abs(deltaY) / (float)abs(deltaX);

	if ((m < 1) && (deltaX > 0) && (deltaY <= 0)) //first octant
		return 1;

	if ((m >= 1) && (deltaX > 0) && (deltaY <= 0))  // second octant
		return 2;

	if ((m >= 1) && (deltaX < 0) && (deltaY < 0)) // third octant
		return 3;

	if ((m < 1) && (deltaX < 0) && (deltaY < 0)) // fourth octant
		return 4;
	if ((m < 1) && (deltaX < 0) && (deltaY > 0)) // fifth octant
		return 5;
	if ((m >= 1) && (deltaX < 0) && (deltaY > 0)) // sixth octant
		return 6;
	if ((m >= 1) && (deltaX > 0) && (deltaY > 0)) // seventh octant
		return 7;
	if ((m < 1) && (deltaX > 0) && (deltaY > 0)) // eighth octant
		return 8;

	return 0;
}

//Draws a new raster line using Bresenham's algorithm
void BresenhamDraw(BresenhamLine line, SDL_Renderer* renderer) {
	int tmpStartX = 0;
	int tmpStartY = 0;
	int tmpEndX = 0;
	int tmpEndY = 0;
	int tmpCurrentX = 0;
	int tmpCurrentY = 0;

	int dy = static_cast<int>(fabs(line.endY - line.startY));
	int dx = static_cast<int>(fabs(line.endX - line.startX));

	int d, inc1, inc2;

	int octant = getOctant(line);

	switch (octant)
	{
	case 1:
		tmpStartX = tmpCurrentX = static_cast<int>(line.startX);
		tmpEndX = static_cast<int>(line.endX);
		tmpStartY = tmpCurrentY = static_cast<int>(line.startY);
		tmpEndY = static_cast<int>(line.endY);

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX < tmpEndX)
		{
			//Draw current point
			SDL_RenderPoint(renderer, static_cast<float>(tmpCurrentX), static_cast<float>(tmpCurrentY));
			++tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentY;
			}
		}
		break;
	case 2:
		tmpStartX = tmpCurrentX = static_cast<int>(line.startX);
		tmpEndX = static_cast<int>(line.endX);
		tmpStartY = tmpCurrentY = static_cast<int>(line.startY);
		tmpEndY = static_cast<int>(line.endY);

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY > tmpEndY)
		{
			//Draw current point
			SDL_RenderPoint(renderer, static_cast<float>(tmpCurrentX), static_cast<float>(tmpCurrentY));
			--tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentX;
			}
		}
		break;
	case 3:
			tmpStartX = tmpCurrentX = static_cast<int>(line.startX);
			tmpEndX = static_cast<int>(line.endX);
			tmpStartY = tmpCurrentY = static_cast<int>(line.startY);
			tmpEndY = static_cast<int>(line.endY);

			d = 2 * dx - dy;
			inc1 = 2 * dx;
			inc2 = 2 * (dx - dy);

			while (tmpCurrentY > tmpEndY)
			{
				SDL_RenderPoint(renderer, static_cast<float>(tmpCurrentX), static_cast<float>(tmpCurrentY));
				--tmpCurrentY;

				if (d < 0)
					d += inc1;
				else
				{
					d += inc2;
					--tmpCurrentX;
				}
			}
		break;
	case 4:
			tmpStartX = tmpCurrentX = static_cast<int>(line.startX);
			tmpEndX = static_cast<int>(line.endX);
			tmpStartY = tmpCurrentY = static_cast<int>(line.startY);
			tmpEndY = static_cast<int>(line.endY);

			d = 2 * dy - dx;
			inc1 = 2 * dy;
			inc2 = 2 * (dy - dx);

			while (tmpCurrentX > tmpEndX)
			{
				//Draw current point
				SDL_RenderPoint(renderer, static_cast<float>(tmpCurrentX), static_cast<float>(tmpCurrentY));
				--tmpCurrentX;

				if (d < 0)
					d += inc1;
				else
				{
					d += inc2;
					--tmpCurrentY;
				}
			}
		break;
	case 5:
			tmpStartX = tmpCurrentX = static_cast<int>(line.startX);
			tmpEndX = static_cast<int>(line.endX);
			tmpStartY = tmpCurrentY = static_cast<int>(line.startY);
			tmpEndY = static_cast<int>(line.endY);

			d = 2 * dy - dx;
			inc1 = 2 * dy;
			inc2 = 2 * (dy - dx);

			while (tmpCurrentX > tmpEndX)
			{
				//Draw current point
				SDL_RenderPoint(renderer, static_cast<float>(tmpCurrentX), static_cast<float>(tmpCurrentY));
				--tmpCurrentX;

				if (d < 0)
					d += inc1;
				else
				{
					d += inc2;
					++tmpCurrentY;
				}
			}
		break;
		case 6:
			tmpStartX = tmpCurrentX = static_cast<int>(line.startX);
			tmpEndX = static_cast<int>(line.endX);
			tmpStartY = tmpCurrentY = static_cast<int>(line.startY);
			tmpEndY = static_cast<int>(line.endY);

			d = 2 * dx - dy;
			inc1 = 2 * dx;
			inc2 = 2 * (dx - dy);

			while (tmpCurrentY < tmpEndY)
			{
				//Draw current point
				SDL_RenderPoint(renderer, static_cast<float>(tmpCurrentX), static_cast<float>(tmpCurrentY));
				++tmpCurrentY;

				if (d < 0)
					d += inc1;
				else
				{
					d += inc2;
					--tmpCurrentX;
				}
			}
			break;
		case 7:
			tmpStartX = tmpCurrentX = static_cast<int>(line.startX);
			tmpEndX = static_cast<int>(line.endX);
			tmpStartY = tmpCurrentY = static_cast<int>(line.startY);
			tmpEndY = static_cast<int>(line.endY);

			d = 2 * dx - dy;
			inc1 = 2 * dx;
			inc2 = 2 * (dx - dy);

			while (tmpCurrentY < tmpEndY)
			{
				//Draw current point
				SDL_RenderPoint(renderer, static_cast<float>(tmpCurrentX), static_cast<float>(tmpCurrentY));
				++tmpCurrentY;

				if (d < 0)
					d += inc1;
				else
				{
					d += inc2;
					++tmpCurrentX;
				}
			}
			break;
		case 8:
			tmpStartX = tmpCurrentX = static_cast<int>(line.startX);
			tmpEndX = static_cast<int>(line.endX);
			tmpStartY = tmpCurrentY = static_cast<int>(line.startY);
			tmpEndY = static_cast<int>(line.endY);

			d = 2 * dy - dx;
			inc1 = 2 * dy;
			inc2 = 2 * (dy - dx);

			while (tmpCurrentX < tmpEndX)
			{
				//Draw current point
				SDL_RenderPoint(renderer, static_cast<float>(tmpCurrentX), static_cast<float>(tmpCurrentY));
				++tmpCurrentX;

				if (d < 0)
					d += inc1;
				else
				{
					d += inc2;
					++tmpCurrentY;
				}
			}
			break;


	default:
		break;
	}
}

//void plot

//Draws a new raster circle using Bresenham's algorithm
void BresenhamDraw(BresenhamCircle circle, SDL_Renderer* renderer) {

}