#include "pch.h"
#include "Room.h"
int Room::minX = 0;
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

Room* Room::findRoomByCoordinates(std::vector <Room*> rooms, int x, int y)
{
	
	//sanity checks
	if (x < minX || x > maxX || y < minY || y > maxY)
	{
		return nullptr;
	}

	for (Room* room : rooms)
	{
		if (room->x == x && room->y == y)
		{
			return room;
		}
	}

	return nullptr;
}

void assignNeighbors(Room* room)
{

}

void Room::assignNeighbors(std::vector <Room*> rooms)
{




}