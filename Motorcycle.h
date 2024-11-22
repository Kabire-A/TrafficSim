#pragma once

#ifndef MOTORCYCLE_H

#include <iostream>
#include "Vehicle.h"
#include "Place.h"

using namespace std;

#define MOTORCYCLE_H

class Motorcycle : public Vehicle
{
private:
	string brand_name;
	Place* placeptr;

public:
	Motorcycle();
	Motorcycle(pair<int, int> loc, float w, float sp, char d,
		string bn);
	~Motorcycle();
	string getbrandname() const;
	void setbrandname(string bn);
	Place* getplace();
	void setplace(Place* p);
	void move();
};

#endif
