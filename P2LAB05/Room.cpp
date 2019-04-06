#include "pch.h"
#include "Room.h"


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

void Room::assignNeighbors(std::vector <Room*> rooms)
{
	Room* mappedRooms = []

}