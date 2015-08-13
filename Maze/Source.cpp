#include <iostream>
#include <conio.h>
using namespace std;

#include "Maze.h"

#define SIZE 20
struct Player {
	unsigned x, y;
};
Maze maze;
Player player;

bool quit;
bool next_level;

void Initialize() {
	quit = false;
	next_level = false;
	player.x = 1;
	player.y = SIZE-1;
	maze.Generate(SIZE);
	maze.data[player.x + (player.y*SIZE)] = 2;
}

void Render() {
	//render the maze.
	system("cls");
	cout << "\t\t\t\t    Random Mazes By Anurup Dey.\n\n\t\t\t\t    w,a,s,d to move, e to exit.\n\n";
	for (unsigned y = 0; y < SIZE; ++y) {
		cout << "\n\t\t\t\t\t";
		for (unsigned x = 0; x < SIZE; ++x) {
			if (maze.data[x + (y*SIZE)] == WALL) {
				cout << char(33);
			} else if ((maze.data[x + (y*SIZE)] == 2))
				cout << char(169);
			else cout << " ";
			
		}
	}
}

void Update() {

	//first we remove the player from prev position.
	maze.data[player.x + (player.y*SIZE)] = SPACE;

	if ((player.x + (player.y*SIZE)) == maze.exit) {
		next_level = true;
	}

	char in = _getch();
	switch (in) {
	case 'w':
		if (maze.data[(player.x + (player.y - 1)*SIZE)] != WALL)
			player.y--;
		break;
	case 's':
		if (player.y == SIZE-1) break;
		if (maze.data[(player.x + (player.y + 1)*SIZE)] != WALL)
			player.y++;
		break;
	case 'a':
		if (maze.data[((player.x-1) + (player.y)*SIZE)] != WALL)
			player.x--;
		break;
	case 'd':
		if (maze.data[((player.x+1) + (player.y)*SIZE)] != WALL)
			player.x++;
		break;
	case 'e':
		quit = true;
	}

	maze.data[player.x + (player.y*SIZE)] = 2;
}
int main() {
	Initialize();
	while (!quit) {
		if (next_level) Initialize();
		Render();
		Update();
	}
	return 0;
}