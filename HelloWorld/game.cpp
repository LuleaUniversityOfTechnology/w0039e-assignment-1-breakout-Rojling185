#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "game.h"
#include "constants.h"
#include "paddle.h"

float ballSpeed = 5.0f;


void LoadGame(){
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);

	for (int i = 0; i < 1; i++) {
		SpawnBall();
	}
	SetupScene();
}

void SpawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT/2 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;

}
void SetupScene() {
	for (int x = 24; x < DISPLAY_WIDTH-17; x+=18) {
		for (int y = DISPLAY_HEIGHT-80; y < DISPLAY_HEIGHT-15; y +=12 ) {
			const int objectId = Play::CreateGameObject(ObjectType::TYPE_BRICK, {x, y }, 6, "brick");
			GameObject& bricks = Play::GetGameObject(objectId);
		}
	}
}


void StepFrame(float elapsedTime) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> BricksIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	
	for (int i = 0; i < ballIds.size(); i++) {

		GameObject& balls = Play::GetGameObject(ballIds[i]);
		
		if (balls.pos.x > DISPLAY_WIDTH - 8 || balls.pos.x < 0) {
			balls.velocity.x = -balls.velocity.x;
		}
		else if (balls.pos.y > DISPLAY_HEIGHT -8 || balls.pos.y <0) {
			balls.velocity.y = -balls.velocity.y;
		}
	
		UpdateGameObject(balls);
		DrawObject(balls);
	}
	for (int i = 0; i < BricksIds.size(); i++) {
		Play::CentreAllSpriteOrigins();
		GameObject& bricks = Play::GetGameObject(BricksIds[i]);
		DrawObject(bricks);
		for (int y = 0; y < ballIds.size(); y++) {
			GameObject& balls = Play::GetGameObject(ballIds[y]);
			if (Play::IsColliding(Play::GetGameObject(BricksIds[i]), Play::GetGameObject(ballIds[y]))) {
				UpdateGameObject(bricks);
				if (balls.pos.x < bricks.pos.x + 16 && (balls.pos.y< bricks.pos.y + 1 || balls.pos.y + 4 > bricks.pos.y + 10)) {

					balls.velocity.y = -balls.velocity.y;
					Play::DestroyGameObject(BricksIds[i]);
				}
				else {

					balls.velocity.x = -balls.velocity.x;
					Play::DestroyGameObject(BricksIds[i]);
				}
			}
		}
	}
}
//Improve code that works for now. Upgraded version comes in assigment 1.2:)
void colliding(Paddle& paddle) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	for (int i = 0; i < ballIds.size(); i++) {
		GameObject& balls = Play::GetGameObject(ballIds[i]);
		if (balls.pos.x < paddle.position.x + paddle.width && balls.pos.x> paddle.position.x) {
			if (balls.pos.y-4 < paddle.position.y + paddle.height && balls.pos.y > paddle.position.y) {
				balls.velocity.y = -balls.velocity.y;
			}
		}
	}
}