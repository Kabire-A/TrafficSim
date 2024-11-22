
#include <iostream>
#include "Bus.h"
#include "Vehicle.h"
#include "Place.h"

using namespace std;

Bus::Bus()
{
	name = " ";
	npassengers = 0;
	for (int i = 0; i < 4; i++)
		placeptr[i] = NULL;
}

Bus::Bus(pair<int, int> & loc, float w, float sp, char d, string na,
	int n) : Vehicle(loc, w, sp, d)
{
	name = na;
	npassengers = n;

	for (int i = 0; i < 4; i++)
		placeptr[i] = NULL;
}

Bus::~Bus()
{
	placeptr[0]->setvehicle(NULL);
	placeptr[1]->setvehicle(NULL);
	placeptr[2]->setvehicle(NULL);
	placeptr[3]->setvehicle(NULL);

	placeptr[0] = NULL;
	placeptr[1] = NULL;
	placeptr[2] = NULL;
	placeptr[3] = NULL;
}


void Bus::setname(string na)
{
	name = na;
}

string Bus::getname() const
{
	return name;
}

void Bus::setnpassenger(int n)
{
	npassengers = n;
}

int Bus::getnpassengers() const
{
	return npassengers;
}

void Bus::setplace(Place* front, Place* p1, Place* p2, Place* back)
{
	placeptr[0] = front;
	placeptr[1] = p1;
	placeptr[2] = p2;
	placeptr[3] = back;
}

Place** Bus::getplace()
{
	return placeptr;
}

void Bus::move()
{
	char dir;
	pair<int, int> loc;

	Place* temp_placeptr;

	dir = getdirection();
	loc = getlocation();

	if (dir == 'N')
	{
		temp_placeptr = placeptr[3];

		loc.second += 1;
		for (int i = 3; i > 0; i--)
			placeptr[i] = placeptr[i - 1];
		placeptr[0] = placeptr[0]->getnorth();

		// place pointed to by placeptr[0] point to the bus "this"
		// place pointed to by the old placeptr[3] point to NULL
		temp_placeptr->setvehicle(NULL);
		placeptr[0]->setvehicle(this);
		this->incrementDistance();


	}
	else if (dir == 'S')
	{
		temp_placeptr = placeptr[3];

		loc.second -= 1;
		for (int i = 3; i > 0; i--)
			placeptr[i] = placeptr[i - 1];
		placeptr[0] = placeptr[0]->getsouth();

		// place pointed to by placeptr[0] point to the bus "this"
		// place pointed to by the old placeptr[3] point to NULL
		temp_placeptr->setvehicle(NULL);
		placeptr[0]->setvehicle(this);
		this->incrementDistance();
	}
	else if (dir == 'E')
	{
		temp_placeptr = placeptr[3];

		loc.first += 1;
		for (int i = 3; i > 0; i--)
			placeptr[i] = placeptr[i - 1];
		placeptr[0] = placeptr[0]->geteast();

		// place pointed to by placeptr[0] point to the bus "this"
		// place pointed to by the old placeptr[3] point to NULL
		temp_placeptr->setvehicle(NULL);
		placeptr[0]->setvehicle(this);
		this->incrementDistance();
	}
	else
	{
		temp_placeptr = placeptr[3];

		loc.first -= 1;
		for (int i = 3; i > 0; i--)
			placeptr[i] = placeptr[i - 1];
		placeptr[0] = placeptr[0]->getwest();

		// place pointed to by placeptr[0] point to the bus "this"
		// place pointed to by the old placeptr[3] point to NULL
		temp_placeptr->setvehicle(NULL);
		placeptr[0]->setvehicle(this);
		this->incrementDistance();
	}

	setlocation(loc);
}