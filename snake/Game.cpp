#include "common.h"
#include "Header.h"


Game::Game() {
	running = true;
	next_x_spawn = 4;
}

Game::~Game() {
	for (auto p : alive_players) {
		delete p;
	}
	for (auto p : dead_players) {
		delete p;
	}
	delete map;
}

void Game::operator()() {
	std::cout << "Welcome to sanke.\nHow many players are you? (Min 1, max 6)\n";
	int numPlayers;
	while (true)
	{
		if (std::cin >> numPlayers && numPlayers > 0 && numPlayers <= 6)
			break;
		else {
			std::cout << "Please enter a valid integer within the range.\n";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
	}

	int mapWidth;
	int minMapWidth = numPlayers * 4 + 4;
	std::cout << "Please enter the desired map width. Minimum is " << minMapWidth << " and maximum is 50\n";
	while (true)
	{
		if (std::cin >> mapWidth && mapWidth > 0 && mapWidth <= 100)
			break;
		else {
			std::cout << "Please enter a valid integer within the range.\n";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
	}

	map = new Map(mapWidth);

	for (int i = 0; i < numPlayers; i++)
	{
		std::cout << "Please enter four characters that respresent up, right, down and left button for player " << i + 1 << " (in that order without spaces.)\n";
		char directions[4];
		for (int j = 0; j < 4; j++)
		{
			std::cin >> directions[j];
		// 	std::cout << chr << "\n";
		}
		addPlayer(directions[0], directions[1], directions[2], directions[3]);
	}


	std::thread t1(&Game::keyboard, this);

	while (alive_players.size() > 0)
	{
		for (int i = 0; i < alive_players.size(); i++) {
			if (!((alive_players[i])->move(key_strokes))) {
				dead_players.push_back(alive_players[i]);
				alive_players.erase(alive_players.begin() + i);
			}
		}
		map->print_map();
		map->clearKeyInputs();
		clearKeyInputs();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	running = false;
	map->endGame();
		
	std::cout << "\n\n\n\n\n\n\nThe game has ended. The final scores are:\n";
	printScores();
	std::cout << "\nPress any key to continue. \n";
	t1.join();
	
}

void Game::printScores() {
	for (int i = dead_players.size() - 1; i >= 0 ; i--)
	{
		std::cout << "Player " << dead_players[i]->getId() << ": " << dead_players[i]->getScore() << "\n";
	}

}

void Game::keyboard() {
	while (running)
	{
		char chrInput;
		chrInput = _getch(); // tested on windows
		key_strokes.push_back(chrInput);
		// for(std::vector<char>::const_iterator i = key_strokes->begin(); i != key_strokes->end(); ++i)
		//	std::cout << *i << ' ';
		//std::cout << std::endl;
	}
}

void Game::clearKeyInputs() {
	key_strokes.clear();
}

void Game::endGame() {
	running = false;
}

void Game::addPlayer(char up, char right, char down, char left) {
	Player* newPlayer = new Player(up, right, down, left, map, this, next_x_spawn, alive_players.size() + 1);
	alive_players.push_back(newPlayer);
	next_x_spawn += 4;
}


std::vector<char> Game::getKeystrokes() {
	return key_strokes;
}