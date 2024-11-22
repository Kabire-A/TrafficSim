#pragma once

#ifndef CAR_H

#include <iostream>
#include <string>
#include "Vehicle.h"
#include "Place.h"
#include "Constants.h"

using namespace std;

#define CAR_H

class Car : public Vehicle
{
private:
	string color;
	Place* placeptr[2];

public:
	Car();
	Car(pair<int, int> & loc, float w, float sp, char d);
	~Car();
	string getcolor() const;
	void setcolor(string c);
	void setplace(Place*, Place*);
	Place** getplace();
	void move();

};

#endif