#pragma once

#include "Play.h"
#include "paddle.h"

void SpawnBall();
void SetupScene();
void StepFrame(float elapsedTime, Paddle& paddle);
void LoadGame(Paddle& paddle);
void colliding(Paddle& paddle);
void highScores();
void DrawHighScores();
void reset(Paddle& paddle);
void readLinesAmount();
void save();
void scoresAdd();