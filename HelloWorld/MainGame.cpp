#include "game.h"
#include "paddle.h"

Paddle paddle;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE ){

	LoadGame();
	paddle.width = 46;
	paddle.height = 8;
	paddle.position = { 320 - paddle.width / 2,40 };
	paddle.bottomRight = { paddle.position.x+paddle.width,paddle.position.y };
	paddle.topLeft = {paddle.position.x, paddle.position.y+paddle.height};
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime ){
	
	Play::ClearDrawingBuffer( Play::cBlack );
	DrawPaddle(paddle);
	MovePaddle(paddle);
	colliding(paddle);
	StepFrame(elapsedTime);
	Play::PresentDrawingBuffer();
	return Play::KeyDown( Play::KEY_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void ){

	Play::DestroyManager();
	return PLAY_OK;
}