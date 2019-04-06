
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
	rooms.push_back(new Room(1, 1));
	rooms.push_back(new Room(2, 1));
	rooms.push_back(new Room(4, 1));
	rooms.push_back(new Room(6, 1));
	rooms.push_back(new Room(7, 1));
	rooms.push_back(new Room(8, 1));
	rooms.push_back(new Room(2, 2));
	rooms.push_back(new Room(3, 2));
	rooms.push_back(new Room(4, 2));
	rooms.push_back(new Room(5, 2));
	rooms.push_back(new Room(6, 2));
	rooms.push_back(new Room(8, 2));
	rooms.push_back(new Room(1, 3));
	rooms.push_back(new Room(2, 3));
	rooms.push_back(new Room(4, 3));
	rooms.push_back(new Room(6, 3));
	rooms.push_back(new Room(7, 3));
	rooms.push_back(new Room(8, 3));

	Room::findNeighbors(rooms);
	char* map = Room::createMap(rooms);


    std::cout << map;
}
