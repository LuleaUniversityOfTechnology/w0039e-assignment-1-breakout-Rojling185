#include "game.h"
#include "paddle.h"
#include "constants.h"

Paddle paddle;


// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE ){
	
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	readLinesAmount();
	LoadGame(paddle);
	
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime ){
	
	Play::ClearDrawingBuffer( Play::cBlack );
	colliding(paddle);
	DrawPaddle(paddle);
	MovePaddle(paddle);
	StepFrame(elapsedTime, paddle);
	DrawHighScores();
	Play::PresentDrawingBuffer();

	return Play::KeyDown( Play::KEY_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void ){
	save();
	Play::DestroyManager();
	return PLAY_OK;
}