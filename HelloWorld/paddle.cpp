#pragma once
#include "paddle.h"
#include "constants.h"


void DrawPaddle(Paddle& paddle) {
	const Play::Point2D bottomLeft = { paddle.position.x - (paddle.width / 2), paddle.position.y };
	const Play::Point2D topRight = { paddle.position.x + (paddle.width / 2), paddle.position.y + paddle.height };
	Play::DrawRect(bottomLeft, topRight, Play::cBlue, true);
}
void MovePaddle(Paddle& paddle) {
	int paddleSpeed = 6;
	if (Play::KeyDown(Play::KEY_LEFT) && paddle.position.x > paddle.width/2 ) {
		paddle.position.x -= paddleSpeed;
	}
	if (Play::KeyDown(Play::KEY_RIGHT) && paddle.position.x < DISPLAY_WIDTH - (paddle.width/2)-2) {
		paddle.position.x += paddleSpeed;
	}
}