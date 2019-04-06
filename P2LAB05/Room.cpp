#include "pch.h"
#include "Room.h"
int Room::minX;
int Room::minY;
int Room::maxX;
int Room::maxY;

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