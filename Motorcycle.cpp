
#include <iostream>
#include "Motorcycle.h"
#include "Place.h"

using namespace std;

Motorcycle::Motorcycle()
{
	brand_name = " ";
	placeptr = NULL;
}

Motorcycle::Motorcycle(pair<int, int> loc, float w, float sp, char d,
	string bn) : Vehicle(loc, w, sp, d)
{
	brand_name = bn;
	placeptr = NULL;
}

Motorcycle::~Motorcycle()
{
	placeptr->setvehicle(NULL);
	placeptr = NULL;
}

string Motorcycle::getbrandname() const
{
	return brand_name;
}

void Motorcycle::setbrandname(string bn)
{
	brand_name = bn;
}

Place* Motorcycle::getplace()
{
	return placeptr;
}

void Motorcycle::setplace(Place* p)
{
	placeptr = p;
}

void Motorcycle::move()
{
	char dir;
	pair<int, int> loc;

	Place* temp_placeptr;

	loc = getlocation();
	dir = getdirection();

	if (dir == 'N')
	{
		temp_placeptr = placeptr;

		loc.second = loc.second + 1;
		placeptr = placeptr->getnorth();

		temp_placeptr->setvehicle(NULL);
		placeptr->setvehicle(this);
		this->incrementDistance();
	}
	else if (dir == 'S')
	{
		temp_placeptr = placeptr;

		loc.second = loc.second - 1;
		placeptr = placeptr->getsouth();

		temp_placeptr->setvehicle(NULL);
		placeptr->setvehicle(this);
		this->incrementDistance();
	}
	else if (dir == 'E')
	{
		temp_placeptr = placeptr;

		loc.first = loc.first + 1;
		placeptr = placeptr->geteast();

		temp_placeptr->setvehicle(NULL);
		placeptr->setvehicle(this);
		this->incrementDistance();
	}
	else
	{
		temp_placeptr = placeptr;

		loc.first = loc.first - 1;
		placeptr = placeptr->getwest();

		temp_placeptr->setvehicle(NULL);
		placeptr->setvehicle(this);
		this->incrementDistance();
	}

	setlocation(loc);
}