#pragma once

#include "Play.h"
#include "paddle.h"

void SpawnBall();
void SetupScene();
void StepFrame(float elapsedTime);
void LoadGame();
void colliding(Paddle& paddle);