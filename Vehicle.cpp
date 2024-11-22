
#include <iostream>
#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle()
{
	location.first = -1;
	location.second = -1;
	weight = 0;
	speed = 0;
	direction = ' ';
	idle = 0;
	distance = 0;
	existTime = 0;
}

Vehicle::Vehicle(pair<int,int> &loc, float w, float sp, char d)
{
	location = loc;
	weight = w;
	speed = sp;
	direction = d;
	idle = 0;
	distance = 0;
	existTime = 0;
}

pair<int, int> Vehicle::getlocation() const
{
	return location;
}

void Vehicle::setlocation(pair<int, int> & loc)
{
	location = loc;
}

void Vehicle::setweight(float w)
{
	weight = w;
}

float Vehicle::getweight() const
{
	return weight;
}

float Vehicle::getspeed() const
{
	return speed;
}

void Vehicle::setspeed(float sp)
{
	speed = sp;
}

void Vehicle::setdirection(char d)
{
	direction = d;
}

char Vehicle::getdirection() const
{
	return direction;
}

void Vehicle::incrementIdle()
{
	idle++;
}

void Vehicle::incrementExist()
{
	existTime++;
}

void Vehicle::incrementDistance()
{
	distance++;
}

int Vehicle::getdistance() const
{
	return distance;
}

void Vehicle::setdistance(int dIn)
{
	distance = dIn;
}

int Vehicle::getidle() const
{
	return idle;
}

void Vehicle::setidle(int iIn)
{
	idle = iIn;
}

int Vehicle::getexisttime() const
{
	return existTime;
}

void Vehicle::setexisttime(int eIn)
{
	existTime = eIn;
}