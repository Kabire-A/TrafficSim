
#include <iostream>
#include <cstdlib>
#include "Car.h"
#include "Constants.h"
#include "Place.h"

Car::Car()
{
	int n;
	n = rand() % 12;
	color = COLORS[n];
	placeptr[0] = NULL;  // front
	placeptr[1] = NULL;  // back
}

Car::Car(pair<int, int>& loc, float w, float sp, char d) :
	Vehicle(loc, w, sp, d)
{
	int n = rand() % 12;

	color = COLORS[n];
	placeptr[0] = NULL;
	placeptr[1] = NULL;
}

Car::~Car()
{
	placeptr[0]->setvehicle(NULL);
	placeptr[1]->setvehicle(NULL);

	placeptr[0] = NULL;
	placeptr[1] = NULL;
}

string Car::getcolor() const
{
	return color;
}

void Car::setcolor(string c)
{
	color = c;
}

void Car::setplace(Place* front, Place* back)
{
	placeptr[0] = front;
	placeptr[1] = back;
}

Place** Car::getplace()
{
	return placeptr;
}

// this function assumes that we have determined that the next
// place is unoccupied
void Car::move()
{
	char dir;
	pair<int, int> loc;

	Place* temp_placeptr;

	loc = getlocation();
	dir = getdirection();

	if (dir == 'N')
	{
		temp_placeptr = placeptr[1];

		loc.second = loc.second + 1;
		placeptr[1] = placeptr[0];
		placeptr[0] = placeptr[0]->getnorth();

		// place pointed to by placeptr[0] point to the bus "this"
		// place pointed to by the old placeptr[3] point to NULL
		temp_placeptr->setvehicle(NULL);
		placeptr[0]->setvehicle(this);
		this->incrementDistance();
	}
	else if (dir == 'S')
	{
		temp_placeptr = placeptr[1];

		loc.second = loc.second - 1;
		placeptr[1] = placeptr[0];
		placeptr[0] = placeptr[0]->getsouth();

		// place pointed to by placeptr[0] point to the bus "this"
		// place pointed to by the old placeptr[3] point to NULL
		temp_placeptr->setvehicle(NULL);
		placeptr[0]->setvehicle(this);
		this->incrementDistance();
	}
	else if (dir == 'E')
	{
		temp_placeptr = placeptr[1];

		loc.first = loc.first + 1;
		placeptr[1] = placeptr[0];
		placeptr[0] = placeptr[0]->geteast();

		// place pointed to by placeptr[0] point to the bus "this"
		// place pointed to by the old placeptr[3] point to NULL
		temp_placeptr->setvehicle(NULL);
		placeptr[0]->setvehicle(this);
		this->incrementDistance();
	}
	else
	{
		temp_placeptr = placeptr[1];

		loc.first = loc.first - 1;
		placeptr[1] = placeptr[0];
		placeptr[0] = placeptr[0]->getwest();

		// place pointed to by placeptr[0] point to the bus "this"
		// place pointed to by the old placeptr[3] point to NULL
		temp_placeptr->setvehicle(NULL);
		placeptr[0]->setvehicle(this);
		this->incrementDistance();
	}

	setlocation(loc);
}