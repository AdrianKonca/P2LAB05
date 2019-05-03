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

char Room::getSymbol()
{
	if (nullptr != item && item->wasSeen())
	{
		return item->getName()[0];
	}
	return '#';
}

bool Room::placeItem(Item* item)
{
	if (this->item != nullptr)
	{
		return false;
	}
	this->item = item;
	item->setOwner(this);
	return true;
}

std::string Room::createMap(std::vector <Room*> &rooms)
{
	int horizontalSpread = (maxX - minX + 2);
	int verticalSpread = (maxY - minY + 1);
	int horizontalOffset =  - minX;
	int verticalOffset =  - minY;
	std::string map = std::string(horizontalSpread * verticalSpread, ' ');
	for (auto room : rooms)
	{
		map[(room->x + horizontalOffset) + ((room->y + verticalOffset) * horizontalSpread)] = room->getSymbol();
		int neighborX;
		int neighborY;
		if (room->getNeighborN() == nullptr)
		{
			neighborY = room->y + verticalOffset - 1;
			if (neighborY >= (minY + verticalOffset))
			{
				map[(room->x + horizontalOffset) + (neighborY * horizontalSpread)] = 'X';
			}
		}
		if (room->getNeighborS() == nullptr)
		{
			neighborY = room->y + verticalOffset + 1;
			if (neighborY <= (maxY + verticalOffset))
			{
				map[(room->x + horizontalOffset) + (neighborY * horizontalSpread)] = 'X';
			}
		}
		if (room->getNeighborW() == nullptr)
		{
			neighborX = room->x + horizontalOffset - 1;
			if (neighborX >= (minX + horizontalOffset))
			{
				map[(neighborX) + ((room->y + verticalOffset) * horizontalSpread)] = 'X';
			}
		}
		if (room->getNeighborE() == nullptr)
		{
			neighborX = room->x + horizontalOffset + 1;
			if (neighborX <= (maxX + horizontalOffset))
			{
				map[(neighborX)+((room->y + verticalOffset) * horizontalSpread)] = 'X';
			}
		}
	}
	for (auto i = 1; i <= verticalSpread; i++)
	{
		map[horizontalSpread * i - 1] = '\n';
	}
	//map[horizontalSpread * verticalSpread] = '\0';
	return map;
}

std::vector<Room*> Room::getNeighbors()
{
	std::vector<Room*> neighbors;
	if (neighborN != nullptr)
	{
		neighbors.push_back(neighborN);
	}
	if (neighborE != nullptr)
	{
		neighbors.push_back(neighborE);
	}
	if (neighborS != nullptr)
	{
		neighbors.push_back(neighborS);
	}
	if (neighborW != nullptr)
	{
		neighbors.push_back(neighborW);
	}
	return neighbors;
}

float Room::getHDistanceBetweenRooms(const Room *roomA, const Room *roomB)
{
	return ((roomA->x * roomB->x) + (roomA->y * roomB->y))^1/2;
}

Room* findClosestRoom(std::vector <Room*> &openNodes, Room* &room)
{
	Room* closestRoom = openNodes[0];
	float currentShortestDistance = Room::getHDistanceBetweenRooms(room, closestRoom);
	float potentialShortestDistance = 0;
	for (Room* currentRoom : openNodes)
	{
		potentialShortestDistance = Room::getHDistanceBetweenRooms(room, currentRoom);
		if (potentialShortestDistance < currentShortestDistance)
		{
			closestRoom = currentRoom;
		}
	}
	return closestRoom;
}

void Room::clearAfterPathfinding(std::vector <Room*> &rooms)
{
	for (auto room : rooms)
	{
		room->g = 0;
		room->wasEvaluated = false;
		room->parent = nullptr;
	}
}

std::vector <Room*> Room::rebuildPath(std::vector <Room*> &rooms, Room* &endRoom)
{
	std::vector <Room*> path;
	Room *currentNode = endRoom;
	while (currentNode->parent != nullptr)
	{
		path.insert(path.begin(), currentNode);
		currentNode = currentNode->parent;
	}
	Room::clearAfterPathfinding(rooms); 
	return path;
}



std::vector <Room*> Room::getShortestPathBetweenRooms(std::vector <Room*> &rooms, Room* startRoom, Room* endRoom)
{

	std::vector <Room*> openNodes;
	Room* currentNode;
	bool isTentativeBetter;
	float tentativeG;

	openNodes.push_back(startRoom);
	while (openNodes.size() != 0)
	{
		currentNode = findClosestRoom(openNodes, endRoom);
		if (currentNode == endRoom)
		{
			return rebuildPath(rooms, endRoom);
		}
		openNodes.erase(std::find(openNodes.begin(), openNodes.end(), currentNode));
		currentNode->wasEvaluated = true;

		for (auto neighbor : currentNode->getNeighbors())
		{
			if (neighbor->wasEvaluated)
				continue;
			tentativeG = currentNode->g + 1.0; //1.0 because distance between neigbhors is always 1.0
			isTentativeBetter = false;
			if (std::count(openNodes.begin(), openNodes.end(), neighbor) == 0)
			{
				openNodes.push_back(neighbor);
				neighbor->h = Room::getHDistanceBetweenRooms(neighbor, endRoom);
				isTentativeBetter = true;
			}
			else if (tentativeG < neighbor->g)
			{
				isTentativeBetter = true;
			}
			if (isTentativeBetter)
			{
				neighbor->parent = currentNode;
				neighbor->g = tentativeG;
				neighbor->f = neighbor->g + neighbor->f;
			}
		}
	}
	return std::vector <Room*>();
}
