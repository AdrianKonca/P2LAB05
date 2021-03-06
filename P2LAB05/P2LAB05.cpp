#include "pch.h"
#include "Room.h"

void randomizeItems(std::vector <Room*> &rooms, std::vector <Item *> items)
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

std::vector <Room*> loadMap()
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

	return rooms;
}

void findFastestWayToGetItems(std::vector <Room*> rooms, std::vector <Item *> items)
{
	std::vector <int> itemsIndex;
	int x = 0;
	for (auto item : items)
	{
		itemsIndex.push_back(x++);
	}
	int minimalStepCount = INT_MAX;
	std::vector <int> bestItemsIndex;
	std::vector <Room*> shortPath;
	int stepCount = 0;
	int previousItem = 0;
	do
	{
		stepCount = 0;
		previousItem = -1;
		for (auto i : itemsIndex)
		{
			if (previousItem == -1)
			{
				shortPath = Room::getShortestPathBetweenRooms(rooms, rooms[0], items[i]->getOwner());
				stepCount += shortPath.size();
				//std::cout << "START TO " << items[i]->getName() << ":" << shortPath.size() << " TOTAL" << stepCount << std::endl;
			}
			else
			{
				shortPath = Room::getShortestPathBetweenRooms(rooms, items[previousItem]->getOwner(), items[i]->getOwner());
				stepCount += shortPath.size();
				//std::cout << items[prevItem]->getName() << " TO " << items[i]->getName() << ":" << shortPath.size() << " TOTAL" << stepCount << std::endl;
			}
			previousItem = i;

		}
		//std::cout << std::endl;

		if (stepCount < minimalStepCount)
		{
			//std::cout << "BEFORE:" << minimalStepCount << " AFTER:" << stepCount << std::endl;
			bestItemsIndex = itemsIndex;
			minimalStepCount = stepCount;
		}
	} while (std::next_permutation(itemsIndex.begin(), itemsIndex.end()));
	std::cout << "Minimal amount of steps to get all the items: " << minimalStepCount << std::endl;
	std::cout << "The order of the items: " << std::endl;
	for (auto i : bestItemsIndex)
	{
		std::cout << items[i]->getName() << std::endl;
	}
	std::cout << std::endl;
}

void takeSteps(std::vector <Room*> rooms, std::vector <Item *> items, std::string steps)
{
	int stepCounter = 0;
	Room * currentRoom = rooms[0];
	for (auto character : steps)
	{
		if (currentRoom->getItem() != nullptr && !currentRoom->getItem()->wasSeen())
		{
			std::cout << "Nazwa przedmiotu: " << currentRoom->getItem()->getName() << std::endl;
			std::cout << "Krok[" << stepCounter << "]" << std::endl;
			currentRoom->getItem()->setSeen(true);
		}
		stepCounter++;
		switch (character)
		{
			case 'n':
				currentRoom = currentRoom->getNeighborN();
				break;
			case 's':
				currentRoom = currentRoom->getNeighborS();
				break;
			case 'w':
				currentRoom = currentRoom->getNeighborW();
				break;
			case 'e':
				currentRoom = currentRoom->getNeighborE();
				break;
			default:
				break;
		}
	}
	if (currentRoom->getItem() != nullptr)
	{
		std::cout << "Nazwa przedmiotu: " << currentRoom->getItem()->getName() << std::endl;
		std::cout << "Krok[" << stepCounter << "]" << std::endl;
	}

}

int main()
{
	std::vector <Room*> rooms = loadMap();
	std::vector <Item *> items;

	items.push_back(new Item("Silver sword", 10));
	items.push_back(new Item("Golden bow", 20));
	items.push_back(new Item("Platinium shield", 50));
	randomizeItems(rooms, items);

	std::cout << Room::createMap(rooms) << std::endl;
	takeSteps(rooms, items, "essweneesnnseeneewwssee");

	std::cout << Room::createMap(rooms) << std::endl;
	findFastestWayToGetItems(rooms, items);

}