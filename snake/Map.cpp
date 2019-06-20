#include "common.h"
#include "Header.h"


Map::Map(unsigned int size) {
	map = std::vector<std::vector<int>>(size);
	for (int i = 0; i < size; i++)
	{
		map[i] = std::vector<int>(size);
	}
	running = true;
}


void Map::print_map() {
	std::string outputStr;
	for (int i = 0; i < map.size(); i++)
	{
		outputStr += "___";
	}
	outputStr += "__\n";

	for (int i = 0; i < map.size(); i++)
	{
		outputStr += "|";

		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j] == 1)
			{
				//outputStr += " " + std::to_string(map[i][j]) + " ";
				outputStr += " X ";
			}
			else if (map[i][j] == 2)
			{
				outputStr += " O ";
			}
			else
			{
				outputStr += "   ";

			}

		}
		outputStr += "|\n";
	}

	for (int i = 0; i < map.size(); i++)
	{
		outputStr += "___";
	}
	outputStr += "__\n";

	std::cout << outputStr;
}

void Map::keyboard() {
	while (running)
	{
		char chrInput;
		chrInput = _getch(); // tested on windows
		//std::cout << chrInput << std::endl;
		key_strokes.push_back(chrInput);
		// for(std::vector<char>::const_iterator i = key_strokes.begin(); i != key_strokes.end(); ++i)
		//	std::cout << *i << ' ';
		//std::cout << std::endl;
	}
}

void Map::clearKeyInputs() {
	key_strokes.clear();
}

bool Map::isRunning() const {
	return running;
}

std::vector<int>& Map::operator[](int i) {
	return map[i];
}

std::vector<char> Map::getKeystrokes() const {
	return key_strokes;
}

int& Map::get(int i, int j) {
	return map[i][j];
}

void Map::endGame() {
	running = false;
}

unsigned int Map::width() const {
	return (map[0]).size();
}

unsigned int Map::height() const {
	return map.size();
}

void Map::place_food() {
	int x_rand = rand() % width();
	int y_rand = rand() % height();
	while (get(y_rand, x_rand))
	{
		x_rand = rand() % width();
		y_rand = rand() % height();
	}
	get(y_rand, x_rand) = 2;
}

bool Map::out_of_border(int y, int x) {
	return (y < 0 || y > height() - 1 || x < 0 || x > width() - 1);
}
