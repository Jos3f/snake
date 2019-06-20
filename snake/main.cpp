// snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "common.h"
#include "Header.h"

std::mutex map_matrix_mutex;



int main()
{

    std::cout << "Hello World!\n";

	// Map* map = new Map(26);
	// Map map = Map(26);

	// Player p1('w', 'd', 's', 'a', map, 4);
	// Player p2('i', 'l', 'k', 'j', map, 8);


	// map->print_map();

	//std::thread t1(&Map::keyboard, &map);

	Game * game = new Game();
	
	// game->addPlayer('w', 'd', 's', 'a');
	// game->addPlayer('i', 'l', 'k', 'j');
	// game->addPlayer('8', '6', '2', '4');

	(*game)();
	// map->keyboard();

	/*
	while (p1.move())
	{
		map->print_map();
		map->clearKeyInputs();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	*/

	// map->endGame();
	// t1.join();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
