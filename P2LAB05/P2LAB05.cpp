#include "pch.h"
#include "Room.h"

void randomizeItems(std::vector <Room*> &rooms, std::vector <Item *> &items)
{
	srand((unsigned int)time(NULL));

	int randomRoomIndex;
	bool result;
	while (items.size() > 0)
	{
		randomRoomIndex = rand() % rooms.size();
		result = rooms[randomRoomIndex]->placeItem(items.back());
		if (result)
			items.pop_back();
	}
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

	std::vector <Item *> items;
	items.push_back(new Item("Silver sword", 10));
	items.push_back(new Item("Golden bow", 20));
	items.push_back(new Item("Platinium shield", 50));

	randomizeItems(rooms, items);
	std::string map = Room::createMap(rooms);


    std::cout << map;
}
