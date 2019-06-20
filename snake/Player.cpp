#include "common.h"
#include "Header.h"


Player::Player(char up, char right, char down, char left, Map* map, Game* game, int x_start, int id) : game(game), map(map), up(up), right(right), down(down), left(left), id(id) {
	direction_keys = { up, right, down, left };
	x_pos = x_start;
	y_pos = 4;
	length = 3;
	direction = 2;
	alive = true;


	Player::map->get(y_pos, x_pos) = 1;

	for (int i = 1; i < (int) length; i++)
	{
		Player::map->get(y_pos - i, x_pos) = 1;
		// std::cout << (*map)[y_pos - i][x_pos] << std::endl;
	}
	for (int i = length - 1; i >= 0; i--)
	{
		path.push_back({ y_pos - i, x_pos });
	}
}

void Player::operator()() {
	while (map->isRunning())
	{

	}
}

bool Player::move(std::vector<char>& keyStrokes) {

	bool dirChanged = false;
	//std::vector<char> keyStrokes = map->getKeystrokes();
	// keyStrokes = map->getKeystrokes();
	// std::vector<char> keyStrokes = game->getKeystrokes();
	for (auto key = keyStrokes.rbegin(); key != keyStrokes.rend() && !dirChanged; key++)
	{
		if (*key == up && direction % 2 != 0)
		{
			direction = 0;
			break;
		}
		else if (*key == right && direction % 2 != 1)
		{
			direction = 1;
			break;

		}
		else if (*key == down && direction % 2 != 0)
		{
			direction = 2;
			break;

		}
		else if (*key == left && direction % 2 != 1)
		{
			direction = 3;
			break;

		}
	}

	switch (direction)
	{
	case 0: --y_pos; break;
	case 1:	++x_pos; break;
	case 2:	++y_pos; break;
	case 3:	--x_pos; break;
	}
	if (map->out_of_border(y_pos, x_pos))
	{
		die();
	}
	else
	{


		if (map->get(y_pos, x_pos) == 2) {
			++length;
			map->place_food();
		}
		else {
			map->get((path.front()).first, (path.front()).second) = 0;
			path.pop_front();
		}

		if (map->get(y_pos, x_pos) == 1)
		{
			die();
		}
		else
		{
			map->get(y_pos, x_pos) = 1;
			path.push_back({ y_pos, x_pos });
		}

	}
	return alive;
}

void Player::die() {
	alive = false;
	for (int i = 0; i < 7; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		for (std::pair<int, int> x_y : path)
		{
			map->get(x_y.first, x_y.second) = map->get(x_y.first, x_y.second) ^ 1;
		}
		map->print_map();
	}
}

unsigned int Player::getScore() {
	return length;
}

int Player::getId() {
	return id;
}
