
#include <iostream>
#include "Place.h"
#include "Vehicle.h"
#include "Constants.h"

using namespace std;

Place::Place()
{
	loc = pair<int, int>(-1, -1);
	veh = NULL;
	N = NULL;
	S = NULL;
	E = NULL;
	W = NULL;
}

Place::Place(pair<int, int> location)
{
	loc = location;
	veh = NULL;
	N = NULL;
	S = NULL;
	E = NULL;
	W = NULL;
}

pair<int, int> Place::getlocation() const
{
	return loc;
}

void Place::setlocation(pair<int, int> location)
{
	loc = location;
}

void Place::setvehicle(Vehicle* v)
{
	veh = v;
}

Vehicle* Place::getvehicle()
{
	return veh;
}

void Place::setnorth(Place* north)
{
	N = north;
}

Place* Place::getnorth()
{
	return N;
}

void Place::setsouth(Place* south)
{
	S = south;
}

Place* Place::getsouth()
{
	return S;
}

void Place::seteast(Place* east)
{
	E = east;
}

Place* Place::geteast()
{
	return E;
}

void Place::setwest(Place* west)
{
	W = west;
}

Place* Place::getwest()
{
	return W;
}

void Place::setdirection(Place* north, Place* south, Place* east,
	Place* west)
{
	N = north;
	S = south;
	E = east;
	W = west;
}

bool Place::isoccupied() const
{
	return (veh != NULL);
}

bool Place::isintersection() const
{
	if ((loc.first >= XMAX / 2) &&
		(loc.first <= (XMAX / 2 + 1)) &&
		(loc.second <= YMAX / 2 + 1) &&
		(loc.second >= (YMAX / 2))
		)
		return true;
	else
		return false;
}



