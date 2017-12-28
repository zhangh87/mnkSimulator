#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include "Board.h"
#include "Move.h"
#include "Common.h"
#include "Game.h"
#include "PlayerFactory.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <cassert>
#include <typeinfo>

void boardTest() {
	Board b(15,15, 3);
	b.setGrid(&Move(2, 2, 1));
	b.setGrid(&Move(1, 1, 2));
	b.setGrid(&Move(7,10, 1));
	b.setGrid(&Move(13,10, 2));
	Board c(b); //copy constructor
	for (int i = 0; i < c.getNumRows(); i++) {
			c.setGrid(&Move(i, i, 1));
	}
	std::cout << b << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << c <<std::endl;	
}

void testBoardMemoryLeak() {
	Board b(15, 15, 3);
	std::array <Board*, 10000> arr{};
	for (int j = 0; j < 10000; j++) {
		Board* c = new Board(b);
		arr[j] = c;
	}
	std::cout << "Done" << std::endl; //memory usage of mnkSimulator.exe: 58 mb
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(5s);  //memory usage after function returns: almost nothing
}

char getYNInput() {
	char a = 0;
	while (a != 'n' && a != 'y') {
		std::cout << "Would you like to play again(y / n) ? ";
		std::cin >> a;
		std::cin.ignore(32767, '\n');
	}
	return a;
}

int promptInt(const char* name, int minimum) {
	int a = 0;
	while (a < minimum) {
		std::cout << "Enter a value for "<<name<<", (" <<  name << ">="<<minimum<<"): ";
		std::cin >> a;
		if (std::cin.fail()) {
			std::cin.clear();
			a = 0;
		}
		std::cin.ignore(32767, '\n');
	}
	return a;
}

PlayerType promptPlayer(int number) {
	std::cout << "Available Players:" << std::endl;
	for (int i = 0; i < playerNames.size(); i++) {
		std::cout << '\t' << i << ". " << playerNames.at(i) << std::endl;
	}
	int ans = -1;	
	while (!(ans >= 0 && ans < playerNames.size())) {
		std::cout << "Select a player for player " << number << ": ";
		std::cin >> ans;
		if (std::cin.fail()) {
			std::cin.clear();
			ans = -1;
		}
		std::cin.ignore(32767, '\n');

	}
	return playerNameToType.at(playerNames.at(ans));
}

int reverseSearchFactoryArray(PlayerType p) {
	for (int i = 0; i < playerNames.size(); i++) {
		if (mapping[i].playerType == p) {
			return i;
		}
	}
	assert(true && "Player not registered properly.");
}


int main()
{
	srand(static_cast<unsigned int>(std::time(0)));
	//boardTest();
	//testBoardMemoryLeak();
	int k = promptInt("k", 3);
	int m = promptInt("m", k);
	int n = promptInt("n", k);
	int timeLimit = promptInt("TimeLimit(ms)", 500);
	PlayerType p1 = promptPlayer(1);
	PlayerType p2 = promptPlayer(2);
	Player* player1 = mapping[reverseSearchFactoryArray(p1)].constructor(m, n, k, timeLimit, 1); //on the stack
	Player* player2 = mapping[reverseSearchFactoryArray(p2)].constructor(m, n, k, timeLimit, 2); //on the stack
	Game g(m, n, k, player1, player2); //on the stack
	g.startGame();
    return 0;
}