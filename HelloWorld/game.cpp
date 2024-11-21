#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "game.h"
#include "constants.h"
#include "paddle.h"
#include <iostream>
#include <fstream>
using namespace std;


float ballSpeed = 5.0f;
int score;
class arrayOfInts {
	public:
		int* data = nullptr;
		size_t size = 0;
		size_t capacity = 5;
		
		arrayOfInts() {
			data = new int[capacity];
		}
		~arrayOfInts() {
			delete[] data;
		}

		void push_back(int value) {
			while (size <= value) {
				size++;
				if (data == nullptr) {
					data = new int[size] {};
				}
				if (size > capacity) {
					capacity *= 2;
					int* newData = new int[capacity] {};
					for (size_t i = 0; i < size - 1; i++) {
						newData[i] = data[i];
					}
					delete[] data;
					data[size - 1] = value;
					data = newData;
					
				}
				
			}
			
		}
};

arrayOfInts scoress;

void save() {
	ofstream MyFile("Highscores.txt");
	if (scoress.size < 5) {
		for (int i = 0; i <= scoress.size; i++) {
			MyFile  << scoress.data[i] << endl;
		}
		for (int i = scoress.size; i < 5; i++) {
			MyFile << 0 <<endl;
		}
		MyFile << 0;
	}
	MyFile << scoress.data[0];
	for (int i = 1; i < scoress.size-1; i++) {
		MyFile << endl << scoress.data[i];
	}
	MyFile.close();
	
}

void readLinesAmount() {
	int i = 0;
	ifstream MyReadFile("Highscores.txt");
	string line;
	
	while (getline(MyReadFile, line)) {
		i++;
	
	}
	if (i < 5) {
		i = 5;
	}
	MyReadFile.close();
	scoress.push_back(i);
	scoresAdd();
}
void scoresAdd() {
	ifstream MyReadFile("Highscores.txt");
	string line;
	int i = 0;
	while (getline(MyReadFile, line)) {
		int temp = stoi(line);
		scoress.data[i] = temp;
		i++;
		
	}
	MyReadFile.close();
	for (int i = 0; i <= scoress.size; i++) {
		if (scoress.data[i] < 0) {
			scoress.data[i] = 0;
		}
	}
	int y = 0; 
	while (y < scoress.size) {

		for (int x = scoress.size; x > 0; x--) {
			if (scoress.data[x] > scoress.data[x - 1]) {
				int tempscore = scoress.data[x];
				scoress.data[x] = scoress.data[x - 1];
				scoress.data[x - 1] = tempscore;
			}
		}
		y++;
	}
}


void LoadGame(Paddle& paddle){
	
	for (int i = 0; i < 1; i++) {
		SpawnBall();
	}
	SetupScene();
	paddle.width = 64;
	paddle.height = 8;
	paddle.position = { 320 - paddle.width / 2,40 };
	paddle.bottomRight = { paddle.position.x + paddle.width,paddle.position.y };
	paddle.topLeft = { paddle.position.x, paddle.position.y + paddle.height };
}

void SpawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 4, DISPLAY_HEIGHT/2 }, 4, "ball");
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


void StepFrame(float elapsedTime, Paddle& paddle) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> BricksIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	
	for (int i = 0; i < ballIds.size(); i++) {

		GameObject& balls = Play::GetGameObject(ballIds[i]);
		
		if (balls.pos.x > DISPLAY_WIDTH - 8 || balls.pos.x < 0) {
			balls.velocity.x = -balls.velocity.x;
		}
		else if (balls.pos.y > DISPLAY_HEIGHT -8 ) {
			balls.velocity.y = -balls.velocity.y;
		}
		else if (balls.pos.y < 0) {
			reset(paddle);
			return;
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
				score++;
			}
		}
	}
}

void colliding(Paddle& paddle) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	for (int i = 0; i < ballIds.size(); i++) {
		GameObject& balls = Play::GetGameObject(ballIds[i]);
		if (balls.pos.x < paddle.position.x + paddle.width/2 && balls.pos.x > paddle.position.x - paddle.width/2) {
			if (balls.pos.y < paddle.position.y + paddle.height && balls.pos.y > paddle.position.y) {
				balls.velocity.y = -balls.velocity.y;
			}
		}
	}
}


void highScores() {
	bool exist = false;
	for (int i = 0; i < scoress.size; i++) {
		if (score == scoress.data[i]) {
			exist = false;
			return;
		}
		else {
			exist = true;
		}

	}
	
	if (exist) {
		if (score > scoress.data[5]) {
			scoress.data[5] = score;
		}
		for (int x = 5; x > 0; x--) {
			if (scoress.data[x] > scoress.data[x - 1]) {
				int tempscore = scoress.data[x];
				scoress.data[x] = scoress.data[x-1];
				scoress.data[x - 1] = tempscore;
			}
		}
	}

}
void DrawHighScores() {
	Play::DrawDebugText(Play::Point2D{ DISPLAY_WIDTH - 40,120 }, "HIGHSCORES", Play::cWhite, true);
	std::string tempScore = std::to_string(score);
	char const* cScore = tempScore.c_str();
	Play::DrawDebugText(Play::Point2D{ 40,40 }, cScore, Play::cWhite, true);
	int space = 20;
	for (int i = 0; i < 5 ; i++) {
		std::string tempScores = std::to_string(scoress.data[i]);
		char const* cScores = tempScores.c_str();
		Play::DrawDebugText(Play::Point2D{ DISPLAY_WIDTH - 40,120 - space }, cScores, Play::cWhite, true);
		space += 20;
	}
}
void reset(Paddle& paddle) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> BricksIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for (int i = 0; i < BricksIds.size(); i++) {
		Play::DestroyGameObject(BricksIds[i]);
		
	}
	for (int i = 0; i < ballIds.size(); i++) {
		Play::DestroyGameObject(ballIds[i]);
	}
	
	highScores();
	score = 0;
	LoadGame(paddle);
	
}