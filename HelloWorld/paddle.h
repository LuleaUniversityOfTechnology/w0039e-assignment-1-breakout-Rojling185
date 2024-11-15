#pragma once
#include "Play.h"



struct Paddle {
	int width;
	int height;
	Play::Point2D position;
	Play::Point2D bottomRight;
	Play::Point2D topLeft;
};


void DrawPaddle(Paddle& paddle);
void MovePaddle(Paddle& paddle);
