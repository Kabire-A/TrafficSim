
#include <iostream>
#include "Road.h"
#include "Vehicle.h"
#include "Place.h"

using namespace std;

Road::Road()
{
	direction = ' ';
}

Road::Road(pair<int, int> locations[], int nplaces, int dir)
{
	// allocate memory for all the places corresponding to the 
	// locations inputed
	for (int i = 0; i < nplaces; i++)
	{
		Place* temp = new Place(locations[i]);
		lane.push_back(temp);
	}

	if (dir == 0)
		direction = 'N';
	else if (dir == 1)
		direction = 'S';
	else if (dir == 2)
		direction = 'E';
	else
		direction = 'W';

	// link the places together to form the lane
	switch (dir)
	{
	case 0:
		for (int i = 0; i < nplaces - 1; i++)
		{
			lane[i]->setnorth(lane[i + 1]);
		}
		lane[nplaces - 1]->setnorth(NULL);

		break;

	case 1:
		for (int i = 0; i < nplaces - 1; i++)
		{
			lane[i]->setsouth(lane[i + 1]);
		}
		lane[nplaces - 1]->setsouth(NULL);

		break;

	case 2:
		for (int i = 0; i < nplaces - 1; i++)
		{
			lane[i]->seteast(lane[i + 1]);
		}
		lane[nplaces - 1]->seteast(NULL);

		break;

	case 3:
		for (int i = 0; i < nplaces - 1; i++)
		{
			lane[i]->setwest(lane[i + 1]);
		}
		lane[nplaces - 1]->setwest(NULL);
	}
}

vector<Place*> Road::getlane()
{
	return lane;
}

void Road::setlane(vector<Place*> loc, int nplaces, int dir)
{
	lane = loc;

	if (dir == 0)
		direction = 'N';
	else if (dir == 1)
		direction = 'S';
	else if (dir == 2)
		direction = 'E';
	else
		direction = 'W';

	// link the places together to form the lane
	switch (dir)
	{
	case 0:
		for (int i = 0; i < nplaces - 1; i++)
		{
			lane[i]->setnorth(lane[i + 1]);
		}
		lane[nplaces - 1]->setnorth(NULL);

		break;

	case 1:
		for (int i = 0; i < nplaces - 1; i++)
		{
			lane[i]->setsouth(lane[i + 1]);
		}
		lane[nplaces - 1]->setsouth(NULL);

		break;

	case 2:
		for (int i = 0; i < nplaces - 1; i++)
		{
			lane[i]->seteast(lane[i + 1]);
		}
		lane[nplaces - 1]->seteast(NULL);

		break;

	case 3:
		for (int i = 0; i < nplaces - 1; i++)
		{
			lane[i]->setwest(lane[i + 1]);
		}
		lane[nplaces - 1]->setwest(NULL);
	}
}


char Road::getdirection() const
{
	return direction;
}

void Road::setdirection(char dir)
{
	direction = dir;
}


int Road::getfreeplace(int dir)
{
	if (dir == 0)  // North
	{
		for (int i = (YMAX/2) - 1; i >= 0; i--)
		{
			pair<int, int> loc = lane[i]->getlocation();

			if (lane[i]->isoccupied())
				continue;

			return i;
		}
	}
	else if (dir == 1) //south
	{
		for (int i = (YMAX / 2) - 3; i >= 0; i--)
		{
			pair<int, int> loc = lane[i]->getlocation();

			if (lane[i]->isoccupied())
				continue;

			return i;
		}
	}
	else if (dir == 2) //east
	{
		for (int i = (XMAX / 2) - 1; i >= 0; i--)
		{
			pair<int, int> loc = lane[i]->getlocation();

			if (lane[i]->isoccupied())
				continue;

			return i;
		}
	}
	else  // west
	{
		for (int i = (XMAX / 2) - 3; i >= 0; i--)
		{
			pair<int, int> loc = lane[i]->getlocation();

			if (lane[i]->isoccupied())
				continue;

			return i;
		}
	}

	return -1;
}