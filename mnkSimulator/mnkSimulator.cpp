#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include "Board.h"
#include "Move.h"
#include "Common.h"
#include "Game.h"
#include "PlayerFactory.h"
#include "GameManager.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <cassert>
#include <typeinfo>

void boardTest() {
	Board b(15,15, 3);
	b.setGrid(Move(2, 2, 1));
	b.setGrid(Move(1, 1, 2));
	b.setGrid(Move(7,10, 1));
	b.setGrid(Move(13,10, 2));
	Board c(b); //copy constructor
	for (int i = 0; i < c.getNumRows(); i++) {
			c.setGrid(Move(i, i, 1));
	}
	std::cout << b << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << c <<std::endl;	
}

void isTerminalTest() {
	Board b(3, 3, 3);
	/*
	. . O 
	X O X
	O X X	
	*/
	b.setGrid(Move(0,2, 2));
	b.setGrid(Move(1,1, 2));
	b.setGrid(Move(2,0, 2));
	b.setGrid(Move(2,1, 1));
	b.setGrid(Move(1,2, 1));
	b.setGrid(Move(2,2, 1));
	b.setGrid(Move(0,1, 1));
	std::cout << b << std::endl;
	auto a = GameManager::isTerminal(b);
	std::cout << b << std::endl;
}

void validMovesTest() {
	Board b(3,4, 3);
	Player* p1 = mapping[0].constructor(3, 3, 4, 100000, 1);
	Player* p2 = mapping[0].constructor(3, 3, 4, 100000, 2);
	/*
	X . . .
	. . . .
	. . . .
	*/
	b.setGrid(Move(0, 0, 1));
	std::cout << b << std::endl;
	auto a = GameManager::getValidMoves(b, p2);
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
	return 0;
}


int main()
{
	//boardTest();
	//isTerminalTest();
	//validMovesTest();
	int k = promptInt("k", 3);
	int m = promptInt("m", k);
	int n = promptInt("n", k);
	int timeLimit = promptInt("TimeLimit(ms)", 500);
	PlayerType p1 = promptPlayer(1);
	PlayerType p2 = promptPlayer(2);
	Player* player1 = mapping[reverseSearchFactoryArray(p1)].constructor(m, n, k, timeLimit, 1); //on the stack
	Player* player2 = mapping[reverseSearchFactoryArray(p2)].constructor(m, n, k, timeLimit, 2); //on the stack
	Game g(m, n, k, timeLimit, player1, player2); //on the stack
	g.startGame();
    return 0;
}