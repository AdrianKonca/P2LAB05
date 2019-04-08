#include "pch.h"
#include "Room.h"
int Room::minX = INT_MAX;
int Room::minY = INT_MAX;
int Room::maxX = INT_MIN;
int Room::maxY = INT_MIN;

Room::Room(int x, int y)
{
	this->x = x;
	this->y = y;
	if (x < minX)
	{
		minX = x;
	}
	if (y < minY)
	{
		minY = y;
	}
	if (x > maxX)
	{
		maxX = x;
	}
	if (y > maxY)
	{
		maxY = y;
	}
}

Room::~Room()
{
}

Room* Room::findRoomByCoordinates(std::vector <Room*> &rooms, int x, int y)
{
	
	//sanity checks
	if (x < minX || x > maxX || y < minY || y > maxY)
	{
		return nullptr;
	}

	for (auto room : rooms)
	{
		if (room->x == x && room->y == y)
		{
			return room;
		}
	}

	return nullptr;
}

void Room::assignNeighbors(std::vector <Room*> &rooms)
{
	this->neighborN = findRoomByCoordinates(rooms, this->x, this->y - 1);
	this->neighborW = findRoomByCoordinates(rooms, this->x - 1, this->y);
	this->neighborE = findRoomByCoordinates(rooms, this->x + 1, this->y);
	this->neighborS = findRoomByCoordinates(rooms, this->x, this->y + 1);
}

void Room::findNeighbors(std::vector <Room*> &rooms)
{
	for (auto room : rooms)
	{
		room->assignNeighbors(rooms);
	}
}

char* Room::createMap(std::vector <Room*> &rooms)
{
	int horizontalSpread = (maxX - minX + 2);
	int verticalSpread = (maxY - minY + 1);
	int horizontalOffset =  - minX;
	int verticalOffset =  - minY;
	char* map = new char[horizontalSpread * verticalSpread + 1];
	for (auto room : rooms)
	{
		map[(room->x + horizontalOffset) + ((room->y + verticalOffset) * (horizontalSpread))] = '#';
	}
	for (auto i = 1; i <= verticalSpread; i++)
	{
		map[horizontalSpread * i - 1] = '\n';

	}
	map[horizontalSpread * verticalSpread] = '\0';
	return map;
}