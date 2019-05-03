#pragma once
class Room;

class Item
{
	Room* ownerRoom;
	std::string name;
	int value;
	bool seen = false;
public:
	std::string getName() { return name; }
	void setSeen(bool seen) { this->seen = seen; }
	bool wasSeen() { return this->seen; }
	void setOwner(Room* ownerRoom) { this->ownerRoom = ownerRoom; }
	Room* getOwner() { return this->ownerRoom; }
	Item(std::string name, int value);
	~Item();
};

