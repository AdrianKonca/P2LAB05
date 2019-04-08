#pragma once
class Item
{
	std::string name;
	int value;
public:
	std::string getName() { return name; }
	Item(std::string name, int value);
	~Item();
};

