
#include "pch.h"

#include "Room.h"

void printRooms(std::vector <Room*> rooms)
{
	char roomRender[8][3];
	for (Room* room : rooms)
	{
		//roomRender
	}
	std::cout << roomRender;
}

int main()
{
	std::vector <Room*> rooms;
	rooms.push_back(new Room(0, 1));
	rooms.push_back(new Room(0, 2));
	rooms.push_back(new Room(0, 4));
	rooms.push_back(new Room(0, 6));
	rooms.push_back(new Room(0, 7));
	rooms.push_back(new Room(0, 8));
	rooms.push_back(new Room(1, 2));
	rooms.push_back(new Room(1, 3));
	rooms.push_back(new Room(1, 4));
	rooms.push_back(new Room(1, 5));
	rooms.push_back(new Room(1, 6));
	rooms.push_back(new Room(1, 8));
	rooms.push_back(new Room(2, 1));
	rooms.push_back(new Room(2, 2));
	rooms.push_back(new Room(2, 4));
	rooms.push_back(new Room(2, 6));
	rooms.push_back(new Room(2, 7));
	rooms.push_back(new Room(2, 8));



    std::cout << "Hello World!\n"; 
}
