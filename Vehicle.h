#pragma once

#ifndef VEHICLE_H

#include <iostream>
#include <utility>

using namespace std;

#define VEHICLE_H

class Vehicle
{
private:
	pair<int, int> location;
	float weight, speed;
	char direction;  // N, S, E, W
	int idle;
	int distance;
	int existTime;

public:
	Vehicle();
	Vehicle(pair<int, int>&, float w, float sp, char d);

	pair<int, int> getlocation() const;
	void setlocation(pair<int, int>&);
	virtual float getweight() const;
	virtual void setweight(float);
	float getspeed() const;
	void setspeed(float);
	char getdirection() const;
	void setdirection(char);
	int getdistance() const;
	void setdistance(int);
	int getidle() const;
	void setidle(int);
	int getexisttime() const;
	void setexisttime(int);
	void incrementIdle();
	void incrementDistance();
	void incrementExist();
};


#endif
