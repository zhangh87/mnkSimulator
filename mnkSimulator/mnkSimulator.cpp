#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include "Board.h"
#include "Move.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <array>

void boardTest() {
	Board b(15,15);
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
	Board b(15, 15);
	std::array <Board*, 10000> arr{};
	for (int j = 0; j < 10000; j++) {
		Board* c = new Board(b);
		arr[j] = c;
	}
	std::cout << "Done" << std::endl; //memory usage of mnkSimulator.exe: 58 mb
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(5s);  //memory usage after function returns: almost nothing
}

int main()
{
	srand(static_cast<unsigned int>(std::time(0)));
	//boardTest();
	//testBoardMemoryLeak();

    return 0;
}


