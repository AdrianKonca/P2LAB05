#pragma once
#include "Item.h"

class Room
{
	std::string description;
	int x;
	int y;
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
	Room();
	~Room();
};
