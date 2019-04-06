#pragma once
#include "Item.h"

class Room
{
	std::string description;
	int x;
	int y;
	static int minX;
	static int maxX;
	static int minY;
	static int maxY;
	Room *neighborN;
	Room *neighborW;
	Room *neighborE;
	Room *neighborS;
	Item *item;
public:
	std::string getDescription()	{ return description; };
	Room *getNeighborN()			{ return neighborN; };
	Room *getNeighborW()			{ return neighborW; };
	Room *getNeighborE()			{ return neighborE; };
	Room *getNeighborS()			{ return neighborS; };
	bool hasItem()					{ return (item != nullptr); };
	Item *getItem()					{ return item; };

	static Room* findRoomByCoordinates(std::vector <Room*> rooms, int x, int y);
	void assignNeighbors(Room* room);
	static void assignNeighbors(std::vector <Room*> rooms);
	Room(int x, int y);
	~Room();
};

