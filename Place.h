#pragma once

#ifndef PLACE_H

#include <iostream>
#include <utility>
#include <string>
#include "Vehicle.h"

using namespace std;

#define PLACE_H

class Place
{
private:
	pair<int, int> loc;
	Place* N, * S, * E, * W;
	Vehicle* veh;

public:
	Place();
	Place(pair<int, int> loc);

	bool isoccupied() const;
	bool isintersection() const;
	pair<int, int> getlocation() const;
	void setlocation(pair<int, int> loc);
	void setvehicle(Vehicle*);
	Vehicle* getvehicle();
	void setdirection(Place* north, Place* south, Place* east,
		Place* west);
	Place* getnorth();
	Place* getsouth();
	Place* geteast();
	Place* getwest();
	void setnorth(Place* north);
	void setsouth(Place* south);
	void seteast(Place* east);
	void setwest(Place* west);
};

#endif
