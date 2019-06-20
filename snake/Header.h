#pragma once
#include "common.h"

class Map;
class Player;
class Game;


// Game functor
class Game {
	std::vector<Player*> all_players;
	std::vector<Player*> alive_players;
	std::vector<Player*> dead_players;
	Map* map;
	std::vector<char> key_strokes;
	bool running;
	int next_x_spawn;

public:
	Game();
	~Game();
	void operator()();
	void keyboard();
	void clearKeyInputs();
	void endGame();
	void addPlayer(char up, char right, char down, char left);
	std::vector<char> getKeystrokes();
	void printScores();
};

class Map {

	std::vector<std::vector<int>> map;
	std::vector<std::pair<int, int>> head_on_collisions;
	std::vector<char> key_strokes;
	bool running;


public:
	Map(unsigned int size);
	void print_map();
	void keyboard();
	void clearKeyInputs();
	bool isRunning() const;
	std::vector<int>& operator[](int i);
	std::vector<char> getKeystrokes() const;
	int& get(int i, int j);
	void endGame();
	unsigned int width() const;
	unsigned int height() const;
	void place_food();
	bool out_of_border(int y, int x);
};

class Player {
	std::vector<char> direction_keys; // index - direction : 0 - up : 1 - right : 2 - down : 3 - left
	Map* map;

	unsigned int length;
	unsigned int x_pos;
	unsigned int y_pos;
	unsigned int direction;
	bool alive;
	char up;
	char right;
	char down;
	char left;
	std::deque<std::pair<int, int>> path;
	Game* game;
	int id;

public:
	Player(char up, char right, char down, char left, Map* map, Game* game, int x_start, int id);
	void operator()();
	bool move(std::vector<char>& keyStrokes);
	void die();
	unsigned int getScore();
	int getId();

};
